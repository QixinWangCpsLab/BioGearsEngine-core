/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

// Include the various types you will be using in your code
#include <biogears/cdm/compartment/SECompartmentManager.h>
#include <biogears/cdm/engine/PhysiologyEngineTrack.h>
#include <biogears/cdm/patient/actions/SESubstanceBolus.h>
#include <biogears/cdm/properties/SEScalarTypes.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/system/physiology/SEBloodChemistrySystem.h>
#include <biogears/cdm/system/physiology/SECardiovascularSystem.h>
#include <biogears/cdm/system/physiology/SERespiratorySystem.h>
#include <biogears/cdm/utils/SEEventHandler.h>
#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/string/manipulation.h>

using namespace biogears;
//--------------------------------------------------------------------------------------------------
/// \brief
/// Usage for adminstering a substance to the patient via a bolus injection
///
/// \details
/// Refer to the SESubstanceBolus class
/// Refer to the SESubstanceManager class
//--------------------------------------------------------------------------------------------------
int HowToBolusDrug()
{
  // Create the engine and load the patient
  std::unique_ptr<PhysiologyEngine> bg = CreateBioGearsEngine("HowToBolusDrug.log");
  bg->GetLogger()->Info("HowToBolusDrug");
  if (!bg->LoadState("./states/StandardMale@0s.xml")) {
    bg->GetLogger()->Error("Could not load state, check the error");
    return 1;
  }

  // The tracker is responsible for advancing the engine time and outputting the data requests below at each time step

  // Create data requests for each value that should be written to the output log as the engine is executing
  // Physiology System Names are defined on the System Objects
  // defined in the Physiology.xsd file
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("HeartRate", FrequencyUnit::Per_min);
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("CardiacOutput", VolumePerTimeUnit::mL_Per_min);
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("MeanArterialPressure", PressureUnit::mmHg);
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("SystolicArterialPressure", PressureUnit::mmHg);
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("DiastolicArterialPressure", PressureUnit::mmHg);
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("RespirationRate", FrequencyUnit::Per_min);
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("TidalVolume", VolumeUnit::mL);
  bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("NeuromuscularBlockLevel");

  bg->GetEngineTrack()->GetDataRequestManager().SetResultsFilename("HowToBolusDrug.csv");

  bg->GetLogger()->Info("The patient is nice and healthy");
  bg->GetLogger()->Info(asprintf("Tidal Volume : %f %s", bg->GetRespiratorySystem()->GetTidalVolume(VolumeUnit::mL), "mL"));
  bg->GetLogger()->Info(asprintf("Systolic Pressure : %f %s", bg->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg), "mmHg"));
  bg->GetLogger()->Info(asprintf("Diastolic Pressure : %f %s", bg->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg), "mmHg"));
  bg->GetLogger()->Info(asprintf("Heart Rate : %f %s", bg->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min), "bpm"));
  bg->GetLogger()->Info(asprintf("Respiration Rate : %f %s", bg->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min), "bpm"));
  bg->GetLogger()->Info(asprintf("Oxygen Saturation : %f", bg->GetBloodChemistrySystem()->GetOxygenSaturation()));

  bg->AdvanceModelTime(50, TimeUnit::s);

  // Get the Succinylcholine substance from the substance manager
  const SESubstance* succs = bg->GetSubstanceManager().GetSubstance("Succinylcholine");

  // Create a substance bolus action to administer the substance
  SESubstanceBolus bolus(*succs);
  bolus.GetConcentration().SetValue(4820, MassPerVolumeUnit::ug_Per_mL);
  bolus.GetDose().SetValue(20, VolumeUnit::mL);
  bolus.SetAdminRoute(CDM::enumBolusAdministration::Intravenous);
  // BioGears also supports Intramuscular as an admin route as well
  bg->ProcessAction(bolus);
  bg->GetLogger()->Info("Giving the patient Succinylcholine.");

  bg->AdvanceModelTime(200, TimeUnit::s);

  bg->GetLogger()->Info("It has been 200s since the administration, not doing well...");
  bg->GetLogger()->Info(asprintf("Tidal Volume : %f %s", bg->GetRespiratorySystem()->GetTidalVolume(VolumeUnit::mL), "mL"));
  bg->GetLogger()->Info(asprintf("Systolic Pressure : %f %s", bg->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg), "mmHg"));
  bg->GetLogger()->Info(asprintf("Diastolic Pressure : %f %s", bg->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg), "mmHg"));
  bg->GetLogger()->Info(asprintf("Heart Rate : %f %s", bg->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min), "bpm"));
  bg->GetLogger()->Info(asprintf("Respiration Rate : %f %s", bg->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min), "bpm"));
  bg->GetLogger()->Info(asprintf("Oxygen Saturation : %f", bg->GetBloodChemistrySystem()->GetOxygenSaturation()));
  bg->GetLogger()->Info("Finished");
  return 0;
}

int main ( int argc, char* argv[] ) {
  return  HowToBolusDrug();
}
