#include "BioGears.h"

#include <biogears/engine/Controller/BioGears.h>
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/engine/Equipment/ECG.h>
#include <biogears/version.h>

namespace biogears {
namespace io {

  // BioGears
  void BioGears::Marshall(const CDM::BioGearsStateData& in, BioGearsEngine& out, const SEScalarTime* simTime)
  {
    auto requests = out.GetEngineTrack()->GetDataRequestManager().GetDataRequests();
    auto resultsFile = out.GetEngineTrack()->GetDataRequestManager().GetResultsFilename();
    std::vector<std::unique_ptr<CDM::DataRequestData>> dataVector;
    for (auto& dr : requests) {
      dataVector.emplace_back(dr->Unload());
    }
    out.BioGears::SetUp();
    out.m_EngineTrack = PhysiologyEngineTrack(out);
    out.m_DataTrack = &out.m_EngineTrack.GetDataTrack();
    for (auto& data : dataVector) {
      out.m_EngineTrack.GetDataRequestManager().CreateFromBind(*data, *out.m_Substances);
    }
    out.m_EngineTrack.GetDataRequestManager().SetResultsFilename(resultsFile);
    out.m_ss.str("");
    out.m_ss.clear();

    out.m_State = EngineState::NotReady;

    // if (in.DataRequests().present()) {
    //   out.m_EngineTrack.GetDataRequestManager().Clear();
    //   out.m_EngineTrack.GetDataRequestManager().Load(in.DataRequests().get(), *out.m_Substances);
    //   out.m_EngineTrack.ForceConnection(); // I don't want to rest the file because I would loose all my data
    // }

    if (simTime != nullptr) {
      out.m_CurrentTime->Set(*simTime);
      out.m_SimulationTime->Set(*simTime);
    } else {
      if (in.SimulationTime().present()) {
        out.m_CurrentTime->Load(in.SimulationTime().get());
        out.m_SimulationTime->Load(in.SimulationTime().get());
      } else {
        out.m_CurrentTime->SetValue(0, TimeUnit::s);
        out.m_SimulationTime->SetValue(0, TimeUnit::s);
      }
    }
    out.m_AirwayMode = in.AirwayMode();
    out.m_Intubation = in.Intubation();

    /// Patient //
    if (!in.Patient().present()) {
      throw biogears::CommonDataModelException("BioGearsState must have a patient");
    } else if (!out.m_Patient->Load(in.Patient().get())) {
      throw biogears::CommonDataModelException("Error loading patient data");
    }
    // Conditions //
    out.m_Conditions->Clear();
    for (const CDM::ConditionData& cData : in.Condition()) {
      if (!out.m_Conditions->ProcessCondition(cData, out)) {
        throw biogears::CommonDataModelException("Unable to load condition");
      }
    }
    // Actions //
    out.m_Actions->Clear();
    for (const CDM::ActionData& cData : in.ActiveAction()) {
      if (!out.m_Actions->ProcessAction(cData, out)) {
        throw biogears::CommonDataModelException("Unable to load action");
      }
    }
    // Substances //
    for (const CDM::SubstanceData& subData : in.ActiveSubstance()) {
      SESubstance* sub = out.m_Substances->GetSubstance(subData.Name());
      if (sub == nullptr) {
        sub = new SESubstance(out.GetLogger());
        out.m_Substances->AddSubstance(*sub);
      }
      if (!sub->Load(subData)) {
        throw biogears::CommonDataModelException("Unable to load substance " + subData.Name());
      }
      out.m_Substances->AddActiveSubstance(*sub);
    }
    // Compounds //
    for (const CDM::SubstanceCompoundData& cmpdData : in.ActiveSubstanceCompound()) {
      SESubstanceCompound* cmpd = out.m_Substances->GetCompound(cmpdData.Name());
      if (cmpd == nullptr) {
        cmpd = new SESubstanceCompound(out.GetLogger());
        out.m_Substances->AddCompound(*cmpd);
      }
      if (!cmpd->Load(cmpdData, *out.m_Substances)) {
        throw biogears::CommonDataModelException("Unable to load compound " + cmpdData.Name());
      }
    }
    // Circuit Manager //
    if (!in.CircuitManager().present()) {
      throw biogears::CommonDataModelException("BioGearsState must have a circuit manager");
    } else {
      const CDM::CircuitManagerData* cmptMgrData = dynamic_cast<const CDM::CircuitManagerData*>(&in.CircuitManager().get());
      if (cmptMgrData == nullptr) {
        throw biogears::CommonDataModelException("BioGearsState must have a BioGears circuit manager");
      } else if (!out.m_Circuits->Load(*cmptMgrData)) {
        throw biogears::CommonDataModelException("Error loading circuit manager data");
      }
    }
    // Compartment Manager //
    if (!in.CompartmentManager().present()) {
      throw biogears::CommonDataModelException("BioGearsState must have a compartment manager");
    } else {
      const CDM::CompartmentManagerData* cmptMgrData = dynamic_cast<const CDM::CompartmentManagerData*>(&in.CompartmentManager().get());
      if (cmptMgrData == nullptr) {
        throw biogears::CommonDataModelException("BioGearsState must have a BioGears compartment manager");
      } else if (!out.m_Compartments->Load(*cmptMgrData, out.m_Circuits.get())) {
        throw biogears::CommonDataModelException("Error loading compartment manager data");
      }
    }
    // Configuration //
    if (!in.Configuration().present()) {
      throw biogears::CommonDataModelException("BioGearsState must have a configuration");
    } else {
      const CDM::BioGearsConfigurationData* confData = dynamic_cast<const CDM::BioGearsConfigurationData*>(&in.Configuration().get());
      if (confData == nullptr) {
        throw biogears::CommonDataModelException("BioGearsState must have a BioGears configuration");
      } else if (!out.m_Config->Load(*confData)) {
        throw biogears::CommonDataModelException("Error loading configuration data");
      }
    }
  }

  void BioGears::UnMarshall(const BioGearsEngine& in, CDM::BioGearsStateData& out)
  {


    out.contentVersion(biogears::branded_version_string());

    out.SimulationTime(std::unique_ptr<CDM::ScalarTimeData>(in.m_SimulationTime->Unload()));
    
    if (in.m_EngineTrack.GetDataRequestManager().HasDataRequests()) {
      out.DataRequests(std::unique_ptr<CDM::DataRequestManagerData>(in.m_EngineTrack.GetDataRequestManager().Unload()));
    }

    out.AirwayMode(in.m_AirwayMode);
    out.Intubation(in.m_Intubation);
    // Patient
    out.Patient(std::unique_ptr<CDM::PatientData>(in.m_Patient->Unload()));
    // Conditions
    std::vector<CDM::ConditionData*> conditions;
    in.m_Conditions->Unload(conditions);
    for (CDM::ConditionData* cData : conditions) {
      out.Condition().push_back(std::unique_ptr<CDM::ConditionData>(cData));
    }
    // Actions
    std::vector<CDM::ActionData*> activeActions;
    in.m_Actions->Unload(activeActions);
    for (CDM::ActionData* aData : activeActions) {
      out.ActiveAction().push_back(std::unique_ptr<CDM::ActionData>(aData));
    }
    // Active Substances/Compounds
    for (SESubstance* s : in.m_Substances->GetActiveSubstances()) {
      out.ActiveSubstance().push_back(std::unique_ptr<CDM::SubstanceData>(s->Unload()));
    }
    for (SESubstanceCompound* c : in.m_Substances->GetActiveCompounds()) {
      out.ActiveSubstanceCompound().push_back(std::unique_ptr<CDM::SubstanceCompoundData>(c->Unload()));
    }
    // Systems
    out.System().push_back(std::unique_ptr<CDM::BioGearsBloodChemistrySystemData>(in.m_BloodChemistrySystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsCardiovascularSystemData>(in.m_CardiovascularSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsDrugSystemData>(in.m_DrugSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsEndocrineSystemData>(in.m_EndocrineSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsEnergySystemData>(in.m_EnergySystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsGastrointestinalSystemData>(in.m_GastrointestinalSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsHepaticSystemData>(in.m_HepaticSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsNervousSystemData>(in.m_NervousSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsRenalSystemData>(in.m_RenalSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsRespiratorySystemData>(in.m_RespiratorySystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsTissueSystemData>(in.m_TissueSystem->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsEnvironmentData>(in.m_Environment->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsAnesthesiaMachineData>(in.m_AnesthesiaMachine->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsElectroCardioGramData>(in.m_ECG->Unload()));
    out.System().push_back(std::unique_ptr<CDM::BioGearsInhalerData>(in.m_Inhaler->Unload()));
    // Compartments
    out.CompartmentManager(std::unique_ptr<CDM::CompartmentManagerData>(in.m_Compartments->Unload()));
    // Configuration
    out.Configuration(std::unique_ptr<CDM::PhysiologyEngineConfigurationData>(in.m_Config->Unload()));
    // Circuitsk
    out.CircuitManager(std::unique_ptr<CDM::CircuitManagerData>(in.m_Circuits->Unload()));
  }
}
}