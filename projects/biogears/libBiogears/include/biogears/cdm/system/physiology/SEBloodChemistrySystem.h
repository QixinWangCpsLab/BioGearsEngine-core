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

#pragma once

#include <biogears/cdm/system/SESystem.h>
#include <biogears/exports.h>
#include <biogears/schema/biogears/BioGearsPhysiology.hxx>

namespace biogears {
class SEScalar;
class SEScalar0To1;
class SEScalarMass;
class MassUnit;
class SEScalarTime;
class TimeUnit;
class SEScalarMassPerVolume;
class MassPerVolumeUnit;
class SEScalarHeatCapacitancePerMass;
class HeatCapacitancePerMassUnit;
class SEScalarFraction;
class SEScalarVolume;
class VolumeUnit;
class SEScalarAmountPerVolume;
class AmountPerVolumeUnit;
class SEScalarPressure;
class PressureUnit;
class SEInflammatoryResponse;

namespace io {
  class Physiology;
}

/** @copydoc Physiology_BloodChemistrySystemData
  @nosubgrouping */
class BIOGEARS_API SEBloodChemistrySystem : public SESystem {
  friend io::Physiology;

public:
  SEBloodChemistrySystem(Logger* logger);
  ~SEBloodChemistrySystem() override;

  static size_t TypeHash() { return reinterpret_cast<size_t>(&TypeHash); }
  static constexpr char const* const TypeTag() { return "SEBloodChemistrySystem"; }
  const char* classname() const override { return TypeTag(); }
  size_t hash_code() const override { return TypeHash(); }

  void Clear() override; /**< @copydoc DOXY_CDM_CLEAR */

  const SEScalar* GetScalar(const char* name) override;
  const SEScalar* GetScalar(const std::string& name) override; /**< @copydoc DOXY_CDM_GET_SCALAR */

  /**  @name Serialization */ //@{
  bool Load(const CDM::BloodChemistrySystemData& in); /**< @copydoc DOXY_CDM_LOAD */
  CDM::BloodChemistrySystemData* Unload() const override; /**< @copydoc DOXY_CDM_UNLOAD */

  Tree<const char*> GetPhysiologyRequestGraph() const override;

  bool operator==(SEBloodChemistrySystem const&) const;
  bool operator!=(SEBloodChemistrySystem const&) const;

protected:
  void Unload(CDM::BloodChemistrySystemData& data) const; /**< @copydoc DOXY_CDM_UNLOAD_TO */ //@}
public:
  /**  @name BloodDensity */ //@{ @copybrief Physiology_BloodChemistrySystemData_BloodDensity
  bool HasBloodDensity() const; /**< @copydoc DOXY_CDM_HAS */
  SEScalarMassPerVolume& GetBloodDensity(); /**< @copydoc DOXY_CDM_GET */
  double GetBloodDensity(const MassPerVolumeUnit& unit) const; /**< @copydoc DOXY_CDM_GET_VALUE */ //@}

  /** @name ArterialBloodPH
   *  @brief @copybrief Physiology_BloodChemistrySystemData_ArterialBloodPH
   *  @{*/
  /// %Test if member has been allocated
  bool HasArterialBloodPH() const;
  /// Get member class, allocate if nullptr
  SEScalar& GetArterialBloodPH();
  double GetArterialBloodPH() const;
  //@}

  /** @name ArterialBloodPHBaseline
   *  @brief @copybrief Physiology_BloodChemistrySystemData_ArterialBloodPHBaseline
   *  @{*/
  /// %Test if member has been allocated
  bool HasArterialBloodPHBaseline() const;
  /// Get member class, allocate if nullptr
  SEScalar& GetArterialBloodPHBaseline();
  double GetArterialBloodPHBaseline() const;
  //@}

  /** @name VenousBloodPH
   *  @brief @copybrief Physiology_BloodChemistrySystemData_VenousBloodPH
   *  @{*/
  /// %Test if member has been allocated
  bool HasVenousBloodPH() const;
  /// Get member class, allocate if nullptr
  SEScalar& GetVenousBloodPH();
  double GetVenousBloodPH() const;
  //@}

  /** @name BloodSpecificHeat
   *  @brief @copybrief Physiology_BloodChemistrySystemData_BloodSpecificHeat
   *  @{*/
  /// %Test if member has been allocated
  bool HasBloodSpecificHeat() const;
  /// Get member class, allocate if nullptr
  SEScalarHeatCapacitancePerMass& GetBloodSpecificHeat();
  double GetBloodSpecificHeat(const HeatCapacitancePerMassUnit& unit) const;
  //@}

  /** @name BloodUreaNitrogenConcentration
   *  @brief @copybrief Physiology_BloodChemistrySystemData_BloodUreaNitrogenConcentration
   *  @{*/
  /// %Test if member has been allocated
  bool HasBloodUreaNitrogenConcentration() const;
  /// Get member class, allocate if nullptr
  SEScalarMassPerVolume& GetBloodUreaNitrogenConcentration();
  double GetBloodUreaNitrogenConcentration(const MassPerVolumeUnit& unit) const;
  //@}

  /** @name CarbonDioxideSaturation
   *  @brief @copybrief Physiology_BloodChemistrySystemData_CarbonDioxideSaturation
   *  @{*/
  /// %Test if member has been allocated
  bool HasCarbonDioxideSaturation() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetCarbonDioxideSaturation();
  double GetCarbonDioxideSaturation() const;
  //@}

  /** @name CarbonMonoxideSaturation
   *  @brief @copybrief Physiology_BloodChemistrySystemData_CarbonMonoxideSaturation
   *  @{*/
  /// %Test if member has been allocated
  bool HasCarbonMonoxideSaturation() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetCarbonMonoxideSaturation();
  double GetCarbonMonoxideSaturation() const;
  //@}

  /** @name Hematocrit
   *  @brief @copybrief Physiology_BloodChemistrySystemData_Hematocrit
   *  @{*/
  /// %Test if member has been allocated
  bool HasHematocrit() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetHematocrit();
  double GetHematocrit() const;
  //@}

  /** @name HemoglobinContent
   *  @brief @copybrief Physiology_BloodChemistrySystemData_HemoglobinContent
   *  @{*/
  /// %Test if member has been allocated
  bool HasHemoglobinContent() const;
  /// Get member class, allocate if nullptr
  SEScalarMass& GetHemoglobinContent();
  double GetHemoglobinContent(const MassUnit& unit) const;
  //@}

  /** @name HemoglobinLostToUrine
   *  @brief @copybrief Physiology_BloodChemistrySystemData_HemoglobinLostToUrine
   *  @{*/
  /// %Test if member has been allocated
  bool HasHemoglobinLostToUrine() const;
  /// Get member class, allocate if nullptr
  SEScalarMass& GetHemoglobinLostToUrine();
  double GetHemoglobinLostToUrine(const MassUnit& unit) const;
  //@}
  /** @name LymphocyteCellCount
   *  @brief @copybrief Physiology_BloodChemistrySystemData_LymphocyteCellCount
   *  @{*/
  /// %Test if member has been allocated
  bool HasLymphocyteCellCount() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetLymphocyteCellCount();
  double GetLymphocyteCellCount(const AmountPerVolumeUnit& unit) const;
  //@}
  /** @name NeutrophilCellCount
   *  @brief @copybrief Physiology_BloodChemistrySystemData_NeutrophilCellCount
   *  @{*/
  /// %Test if member has been allocated
  bool HasNeutrophilCellCount() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetNeutrophilCellCount();
  double GetNeutrophilCellCount(const AmountPerVolumeUnit& unit) const;
  //@}
  /** @name OxygenSaturation
   *  @brief @copybrief Physiology_BloodChemistrySystemData_OxygenSaturation
   *  @{*/
  /// %Test if member has been allocated
  bool HasOxygenSaturation() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetOxygenSaturation();
  double GetOxygenSaturation() const;
  //@}

  /** @name OxygenSaturation
   *  @brief @copybrief Physiology_BloodChemistrySystemData_OxygenVenousSaturation
   *  @{*/
  /// %Test if member has been allocated
  bool HasOxygenVenousSaturation() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetOxygenVenousSaturation();
  double GetOxygenVenousSaturation() const;
  //@}

  /** @name Phosphate
   *  @brief @copybrief Physiology_BloodChemistrySystemData_Phosphate
   *  @{*/
  /// %Test if member has been allocated
  bool HasPhosphate() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetPhosphate();
  double GetPhosphate(const AmountPerVolumeUnit& unit) const;
  //@}

  /** @name PlasmaVolume
   *  @brief @copybrief Physiology_BloodChemistrySystemData_PlasmaVolume
   *  @{*/
  /// %Test if member has been allocated
  bool HasPlasmaVolume() const;
  /// Get member class, allocate if nullptr
  SEScalarVolume& GetPlasmaVolume();
  double GetPlasmaVolume(const VolumeUnit& unit) const;
  //@}

  /** @name PulseOximetry
   *  @brief @copybrief Physiology_BloodChemistrySystemData_PulseOximetry
   *  @{*/
  /// %Test if member has been allocated
  bool HasPulseOximetry() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetPulseOximetry();
  double GetPulseOximetry() const;
  //@}

  /** @name RedBloodCellAcetylcholinesteraseConcentration
   *  @brief @copybrief Physiology_BloodChemistrySystemData_RedBloodCellAcetylcholinesteraseConcentration
   *  @{*/
  /// %Test if member has been allocated
  bool HasRedBloodCellAcetylcholinesterase() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetRedBloodCellAcetylcholinesterase();
  double GetRedBloodCellAcetylcholinesterase(const AmountPerVolumeUnit& unit) const;
  //@}

  /** @name RedBloodCellCount
   *  @brief @copybrief Physiology_BloodChemistrySystemData_RedBloodCellCount
   *  @{*/
  /// %Test if member has been allocated
  bool HasRedBloodCellCount() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetRedBloodCellCount();
  double GetRedBloodCellCount(const AmountPerVolumeUnit& unit) const;
  //@}

  /** @name StrongIonDifference
   *  @brief @copybrief Physiology_BloodChemistrySystemData_StrongIonDifference
   *  @{*/
  /// %Test if member has been allocated
  bool HasStrongIonDifference() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetStrongIonDifference();
  double GetStrongIonDifference(const AmountPerVolumeUnit& unit) const;
  //@}

  /** @name ShuntFraction
   *  @brief @copybrief Physiology_BloodChemistrySystemData_ShuntFraction
   *  @{*/
  /// %Test if member has been allocated
  bool HasShuntFraction() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetShuntFraction();
  double GetShuntFraction() const;
  //@}

  bool HasTotalBilirubin() const;
  SEScalarMassPerVolume& GetTotalBilirubin();
  double GetTotalBilirubin(const MassPerVolumeUnit& unit) const;

  /** @name TotalProteinConcentration
   *  @brief @copybrief Physiology_BloodChemistrySystemData_TotalProteinConcentration
   *  @{*/
  /// %Test if member has been allocated
  bool HasTotalProteinConcentration() const;
  /// Get member class, allocate if nullptr
  SEScalarMassPerVolume& GetTotalProteinConcentration();
  double GetTotalProteinConcentration(const MassPerVolumeUnit& unit) const;
  //@}

  /** @name RhTransfusionReactionVolume
   *  @brief @copybrief Physiology_BloodChemistrySystemData_RhTransfusionReactionVolume
   *  @{*/
  /// %Test if member has been allocated
  bool HasRhTransfusionReactionVolume() const;
  /// %Test if rh mismatch
  virtual SEScalarVolume& GetRhTransfusionReactionVolume();
  double GetRhTransfusionReactionVolume(const VolumeUnit& unit) const;
  //@}

  /** @name ViralLoad
   *  @brief @copybrief Physiology_BloodChemistrySystemData_ViralLoad
   *  @{*/
  /// %Test if member has been allocated
  bool HasViralLoad() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetViralLoad();
  double GetViralLoad() const;
  //@}

  /** @name VolumeFractionNeutralPhospholipidInPlasma
   *  @brief @copybrief Physiology_BloodChemistrySystemData_VolumeFractionNeutralPhospholipidInPlasma
   *  @{*/
  /// %Test if member has been allocated
  bool HasVolumeFractionNeutralPhospholipidInPlasma() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetVolumeFractionNeutralPhospholipidInPlasma();
  double GetVolumeFractionNeutralPhospholipidInPlasma() const;
  //@}

  /** @name VolumeFractionNeutralLipidInPlasma
   *  @brief @copybrief Physiology_BloodChemistrySystemData_VolumeFractionNeutralLipidInPlasma
   *  @{*/
  /// %Test if member has been allocated
  bool HasVolumeFractionNeutralLipidInPlasma() const;
  /// Get member class, allocate if nullptr
  SEScalarFraction& GetVolumeFractionNeutralLipidInPlasma();
  double GetVolumeFractionNeutralLipidInPlasma() const;
  //@}

  /** @name WhiteBloodCellCount
   *  @brief @copybrief Physiology_BloodChemistrySystemData_WhiteBloodCellCount
   *  @{*/
  /// %Test if member has been allocated
  bool HasWhiteBloodCellCount() const;
  /// Get member class, allocate if nullptr
  SEScalarAmountPerVolume& GetWhiteBloodCellCount();
  double GetWhiteBloodCellCount(const AmountPerVolumeUnit& unit) const;
  //@}

  /** @name ArterialCarbonDioxidePressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_ArterialCarbonDioxidePressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasArterialCarbonDioxidePressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetArterialCarbonDioxidePressure();
  double GetArterialCarbonDioxidePressure(const PressureUnit& unit) const;
  //@}

  /** @name ArterialOxygenPressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_ArterialOxygenPressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasArterialOxygenPressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetArterialOxygenPressure();
  double GetArterialOxygenPressure(const PressureUnit& unit) const;
  //@}

  /** @name PulmonaryArterialCarbonDioxidePressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_PulmonaryArterialCarbonDioxidePressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasPulmonaryArterialCarbonDioxidePressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetPulmonaryArterialCarbonDioxidePressure();
  double GetPulmonaryArterialCarbonDioxidePressure(const PressureUnit& unit) const;
  //@}

  /** @name PulmonaryArterialOxygenPressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_PulmonaryArterialOxygenPressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasPulmonaryArterialOxygenPressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetPulmonaryArterialOxygenPressure();
  double GetPulmonaryArterialOxygenPressure(const PressureUnit& unit) const;
  //@}

  /** @name PulmonaryVenousCarbonDioxidePressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_PulmonaryVenousCarbonDioxidePressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasPulmonaryVenousCarbonDioxidePressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetPulmonaryVenousCarbonDioxidePressure();
  double GetPulmonaryVenousCarbonDioxidePressure(const PressureUnit& unit) const;
  //@}

  /** @name PulmonaryVenousOxygenPressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_PulmonaryVenousOxygenPressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasPulmonaryVenousOxygenPressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetPulmonaryVenousOxygenPressure();
  double GetPulmonaryVenousOxygenPressure(const PressureUnit& unit) const;
  //@}

  /** @name VenousCarbonDioxidePressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_VenousCarbonDioxidePressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasVenousCarbonDioxidePressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetVenousCarbonDioxidePressure();
  double GetVenousCarbonDioxidePressure(const PressureUnit& unit) const;
  //@}
  /** @name VenousOxygenPressure
   *  @brief @copybrief Physiology_BloodChemistrySystemData_VenousOxygenPressure
   *  @{*/
  /// %Test if member has been allocated
  bool HasVenousOxygenPressure() const;
  /// Get member class, allocate if nullptr
  SEScalarPressure& GetVenousOxygenPressure();
  double GetVenousOxygenPressure(const PressureUnit& unit) const;
  //@}

  virtual bool HasInflammatoryResponse() const;
  virtual SEInflammatoryResponse& GetInflammatoryResponse();
  virtual SEInflammatoryResponse& GetInflammatoryResponse() const;

protected:
  SEScalarMassPerVolume* m_BloodDensity;
  SEScalar* m_ArterialBloodPH;
  SEScalar* m_ArterialBloodPHBaseline;
  SEScalar* m_VenousBloodPH;
  SEScalarHeatCapacitancePerMass* m_BloodSpecificHeat;
  SEScalarMassPerVolume* m_BloodUreaNitrogenConcentration;
  SEScalarFraction* m_CarbonDioxideSaturation;
  SEScalarFraction* m_CarbonMonoxideSaturation;
  SEScalarFraction* m_Hematocrit;
  SEScalarMass* m_HemoglobinContent;
  SEScalarMass* m_HemoglobinLostToUrine;
  SEScalarAmountPerVolume* m_LymphocyteCellCount;
  SEScalarAmountPerVolume* m_NeutrophilCellCount;
  SEScalarFraction* m_OxygenSaturation;
  SEScalarFraction* m_OxygenVenousSaturation;
  SEScalarAmountPerVolume* m_Phosphate;
  SEScalarVolume* m_PlasmaVolume;
  SEScalarFraction* m_PulseOximetry;
  SEScalarAmountPerVolume* m_RedBloodCellAcetylcholinesterase;
  SEScalarAmountPerVolume* m_RedBloodCellCount;
  SEScalarFraction* m_ShuntFraction;
  SEScalarAmountPerVolume* m_StrongIonDifference;
  SEScalarMassPerVolume* m_TotalBilirubin;
  SEScalarMassPerVolume* m_TotalProteinConcentration;
  SEScalarVolume* m_RhTransfusionReactionVolume;
  SEScalarAmountPerVolume* m_ViralLoad;
  SEScalarFraction* m_VolumeFractionNeutralPhospholipidInPlasma;
  SEScalarFraction* m_VolumeFractionNeutralLipidInPlasma;
  SEScalarAmountPerVolume* m_WhiteBloodCellCount;

  SEScalarPressure* m_ArterialCarbonDioxidePressure;
  SEScalarPressure* m_ArterialOxygenPressure;
  SEScalarPressure* m_PulmonaryArterialCarbonDioxidePressure;
  SEScalarPressure* m_PulmonaryArterialOxygenPressure;
  SEScalarPressure* m_PulmonaryVenousCarbonDioxidePressure;
  SEScalarPressure* m_PulmonaryVenousOxygenPressure;
  SEScalarPressure* m_VenousCarbonDioxidePressure;
  SEScalarPressure* m_VenousOxygenPressure;
  SEInflammatoryResponse* m_InflammatoryResponse;
};

class BIOGEARS_API SEInflammatoryResponse {
  friend io::Physiology;

  public:
    SEInflammatoryResponse();
    ~SEInflammatoryResponse();

    static size_t TypeHash() { return reinterpret_cast<size_t>(&TypeHash); }
    static constexpr char const* const TypeTag() { return "SEInflammatoryResponse"; }
    const char* classname() const { return TypeTag(); }
    size_t hash_code() const { return TypeHash(); }

    void Clear();

    bool Load(const CDM::InflammatoryResponseData& in);
    CDM::InflammatoryResponseData* Unload() const;
    bool IsValid();

    void Initialize();
    const SEScalar* GetScalar(const char* name);
    const SEScalar* GetScalar(const std::string& name);

    bool operator==(SEInflammatoryResponse const&) const;
    bool operator!=(SEInflammatoryResponse const&) const;

  protected:
    void Unload(CDM::InflammatoryResponseData& data) const;

  public:
    bool HasLocalPathogen() const;
    SEScalar& GetLocalPathogen();
    double GetLocalPathogen() const;

    bool HasLocalBarrier() const;
    SEScalar& GetLocalBarrier();
    double GetLocalBarrier() const;

    bool HasLocalMacrophage() const;
    SEScalar& GetLocalMacrophage();
    double GetLocalMacrophage() const;

    bool HasLocalNeutrophil() const;
    SEScalar& GetLocalNeutrophil();
    double GetLocalNeutrophil() const;

    bool HasActiveTLR() const { return m_ActiveTLR == CDM::enumOnOff::value(-1) ? false : true; };
    CDM::enumOnOff GetActiveTLR() { return m_ActiveTLR; };
    void SetActiveTLR(CDM::enumOnOff value) { m_ActiveTLR = value; };

    bool HasAutonomicResponseLevel() const;
    SEScalar& GetAutonomicResponseLevel();
    double GetAutonomicResponseLevel() const;

    bool HasCatecholamines() const;
    SEScalar& GetCatecholamines();
    double GetCatecholamines() const;

    bool HasConstitutiveNOS() const;
    SEScalar& GetConstitutiveNOS();
    double GetConstitutiveNOS() const;

    bool HasInducibleNOSPre() const;
    SEScalar& GetInducibleNOSPre();
    double GetInducibleNOSPre() const;

    bool HasInducibleNOS() const;
    SEScalar& GetInducibleNOS();
    double GetInducibleNOS() const;

    bool HasInterleukin6() const;
    SEScalar& GetInterleukin6();
    double GetInterleukin6() const;

    bool HasInterleukin10() const;
    SEScalar& GetInterleukin10();
    double GetInterleukin10() const;

    bool HasInterleukin12() const;
    SEScalar& GetInterleukin12();
    double GetInterleukin12() const;

    bool HasMacrophageResting() const;
    SEScalar& GetMacrophageResting();
    double GetMacrophageResting() const;

    bool HasMacrophageActive() const;
    SEScalar& GetMacrophageActive();
    double GetMacrophageActive() const;

    bool HasNeutrophilResting() const;
    SEScalar& GetNeutrophilResting();
    double GetNeutrophilResting() const;

    bool HasNeutrophilActive() const;
    SEScalar& GetNeutrophilActive();
    double GetNeutrophilActive() const;

    bool HasNitrate() const;
    SEScalar& GetNitrate();
    double GetNitrate() const;

    bool HasNitricOxide() const;
    SEScalar& GetNitricOxide();
    double GetNitricOxide() const;

    bool HasBloodPathogen() const;
    SEScalar& GetBloodPathogen();
    double GetBloodPathogen() const;

    bool HasTissueIntegrity() const;
    SEScalar0To1& GetTissueIntegrity();
    double GetTissueIntegrity() const;

    bool HasTrauma() const;
    SEScalar& GetTrauma();
    double GetTrauma() const;

    bool HasTumorNecrosisFactor() const;
    SEScalar& GetTumorNecrosisFactor();
    double GetTumorNecrosisFactor() const;

    bool HasInflammationTime() const;
    SEScalarTime& GetInflammationTime();
    double GetInflammationTime(const TimeUnit& unit) const;

    bool HasInflammationSources() const;
    std::vector<CDM::enumInflammationSource>& GetInflammationSources();
    bool HasInflammationSource(CDM::enumInflammationSource::value src);

    Tree<const char*> GetPhysiologyRequestGraph() const;

    double GenerateRandomAIRParam(double basevalue);

    // Temporally move the inflammation params to public for now
    // Below parameters are taken from the Inflammatory Response Function of Blood Chemestry Class
    //------------------------------Model Parameters-----------------------------
    double scale = 1.0; //This parameter can be set very high to investigate state equation trajectores (i.e. set to 60 to simulate 30 hrs in 30 min).  Note that there is no guarantee of validity of other BG outputs
    //----Tissue parameters are taken from Dominguez2017Mathematical; kap = growth rate, psi = degradation rate, eps = inhibition, del = decay (other params defined)
    //Tissue pathogen
    double thetaP = 1.35e-4; //Rate of bacteria translocation from tissue to blood
    double epsPB = 3.1, psiPM = 6.3e-3, psiPN = 6.1e-4, kapP = 0.6;
    double uP = 3.7e4; //Saturation constant for bacteria
    //Tissue macrophage
    double Mv = 3.0e-1; //Resting macrophage pool
    double delM = 6.4e-5, epsMB = 3.6e1;
    double beta = 2.6e-2; //Activation of macrophages
    //Tissue neutrophil
    double Nv = 1e8; //Resting neutrophil pool
    double delN = 6.1e-2, epsNB = 3.6e1, epsNM = 1.6e-1;
    double alpha = 6.975e-7; //Activation of neutrophils
    //Local barrier
    double kapB = 4.6e-2, epsBP = 2.6e1, psiBP = 1.4e-1, psiBN = 4.0e-8;
    //TLR switch
    double pUpper = 2.0e6;
    double pLower = 1.0e3;
    //--Blood parameters are from Chow2005Diverse; kYZ = effect of Z on Y, xYZ = amount of Z to bring effect to half its max
    //Blood Source terms
    double sM = 1.0, sN = 1.0, s6 = 0.001, s10 = 0.01;
    //Blood Pathogen parameters
    double kPN = 5.8; //Phagocytic effect of activated neutrophils on pathogen, determined empirically
    double xPN = 0.5; //Level of pathogen that brings elimination of P by neutrophils to 50% of max
    double kPS = 6.9e3; //Background immune response to pathogen in blood
    double xPS = 1.3e4; //Saturation of background immune response
    //Trauma decay
    double kTr = 0.0; //Base value--will be adjusted during burn/hemorrhage (see below)
    double xTr = 0.67;
    //Volume and blood pressure effect
    double fB = 0.0; //0 except during hemorrhage
    //Macrophage interaction
    double kML = 1.01e2, kMTR = 0.04, kM6 = 0.1, kMB = 0.0495, kMR = 0.05, kMD = 0.05, xML = 37.5, xMD = 0.75, xMTNF = 0.4, xM6 = 1.0, xM10 = 0.297, xMCA = 0.9; //Note xMD was 1.0 for burn, see if this messes things up
    //Activate macrophage interactions
    double kMANO = 0.2, kMA = 0.2;
    //Neutrophil interactions -- kN6 and kNTNF tuned for infection
    double kNL = 3.375e1, kNTNF = 0.4, kN6 = 1.5, kNB = 0.1, kND = 0.05, kNTR = 0.02, kNTGF = 0.1, kNR = 0.05, kNNO = 0.4, kNA = 0.5, xNL = 56.25, xNTNF = 2.0, xN6 = 1.0, xND = 0.4, xN10 = 0.2; //xND was 0.4 for burn
    //Inducible nitric oxide synthase
    double kINOSN = 1.5, kINOSM = 0.1, kINOSEC = 0.1, kINOS6 = 2.0, kINOSd = 0.05, kINOS = 0.101, xINOS10 = 0.1, xINOSTNF = 0.05, xINOS6 = 0.1, xINOSNO = 0.3;
    //Constituitive nitric oxide synthase
    double kENOS = 4.0, kENOSEC = 0.05, xENOSTNF = 0.4, xENOSL = 1.015, xENOSTR = 0.1;
    //Nitric oxide
    double kNO3 = 0.46, kNOMA = 2.0;
    //TNF
    double kTNFN = 2.97, kTNFM = 0.1, kTNF = 1.4, xTNF6 = 0.059, xTNF10 = 0.079;
    //IL6
    double k6M = 3.03, k6TNF = 1.0, k62 = 3.4, k6NO = 2.97, k6 = 0.7, k6N = 0.2, x610 = 0.1782, x6TNF = 0.1, x66 = 0.5, x6NO = 0.4, h66 = 1.0;
    //IL10
    double k10MA = 0.1, k10N = 0.1, k10A = 62.87, k10TNF = 1.485, k106 = 0.051, k10 = 0.35, k10R = 0.1, x10TNF = 0.05, x1012 = 0.01, x106 = 0.08;
    //CA
    double kCA = 0.1, kCATR = 0.16;
    //IL12
    double k12M = 0.303, k12 = 0.05, x12TNF = 0.2, x126 = 0.2, x1210 = 0.2525;
    //Autonomic response
    double kAuto = 0.0, xAuto = 1.15;   //Base value--will be adjusted during burn/hemorrhage (see below)
    //Damage
    double kD6 = 0.125, kD = 0.15, kDB = 0.02, xD6 = 0.85, xDNO = 0.5, hD6 = 6.0;
    double kDTR = 0.0; //This is a base value that will be adjusted as a function of type and severity of trauma
    double tiMin = 0.2; //Minimum tissue integrity allowed

  protected:
    SEScalar* m_LocalPathogen;
    SEScalar* m_LocalMacrophage;
    SEScalar* m_LocalNeutrophil;
    SEScalar* m_LocalBarrier;
    CDM::enumOnOff::value m_ActiveTLR;
    SEScalar* m_AutonomicResponseLevel;
    SEScalar* m_Catecholamines;
    SEScalar* m_ConstitutiveNOS;
    SEScalar* m_InducibleNOSPre;
    SEScalar* m_InducibleNOS;
    SEScalar* m_Interleukin6;
    SEScalar* m_Interleukin10;
    SEScalar* m_Interleukin12;
    SEScalar* m_MacrophageResting;
    SEScalar* m_MacrophageActive;
    SEScalar* m_NeutrophilResting;
    SEScalar* m_NeutrophilActive;
    SEScalar* m_Nitrate;
    SEScalar* m_NitricOxide;
    SEScalar* m_BloodPathogen;
    std::unique_ptr<SEScalar0To1> m_TissueIntegrity;
    SEScalar* m_Trauma;
    SEScalar* m_TumorNecrosisFactor;
    SEScalarTime* m_InflammationTime;
    std::vector<CDM::enumInflammationSource> m_InflammationSources;
  };
}
