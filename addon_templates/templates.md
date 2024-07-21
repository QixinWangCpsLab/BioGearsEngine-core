## 1. The infusion of the vasopressin
```cpp
#include <biogears/cdm/patient/actions/SESubstanceInfusion.h>

...

SESubstance* vas = bg->GetSubstanceManager().GetSubstance("Vasopressin");
vas->GetPlasmaConcentration().SetValue(0.0, MassPerVolumeUnit::ug_Per_L);
...

// Create a substance bolus action to administer the substance
SESubstanceInfusion infuse(*vas);
// Set the concentration
infuse.GetConcentration().SetValue(0.102, MassPerVolumeUnit::ug_Per_mL);
// Set the infusion speed (rate)
infuse.GetRate().SetValue(0.1, VolumePerTimeUnit::mL_Per_min);
bg->ProcessAction(infuse);
bg->AdvanceModelTime(3300, TimeUnit::s);

//Now we change the infusion concentration
infuse.GetConcentration().SetValue(0.292, MassPerVolumeUnit::ug_Per_mL); 
bg->ProcessAction(infuse);
bg->AdvanceModelTime(3300, TimeUnit::s);

//Change the rate and advance the time
infuse.GetRate().SetValue(0, VolumePerTimeUnit::mL_Per_min);
bg->ProcessAction(infuse);
bg->AdvanceModelTime(600, TimeUnit::s);
```

## 2. The definition, and infusion of compounds
```cpp
// Step1. Create the substances from the Substance manager
SESubstance* albumin = bg->GetSubstanceManager().GetSubstance("Albumin");
SESubstance* morphine = bg->GetSubstanceManager().GetSubstance("Morphine");
SESubstance* saline = bg->GetSubstanceManager().GetSubstance("Saline");

// Step2. Use the substance to create the concentration
if (albumin && morphine && saline) {
auto albuminConcentration = SESubstanceConcentration(*albumin);
auto morphineConcentration = SESubstanceConcentration(*morphine);
auto salineConcentration = SESubstanceConcentration(*saline);

// Step3. Set the properties of these concentrations
albuminConcentration.GetConcentration().SetValue (10.0, MassPerVolumeUnit::mg_Per_mL);
morphineConcentration.GetConcentration().SetValue(10.0, MassPerVolumeUnit::mg_Per_mL);
salineConcentration.GetConcentration().SetValue  (2.17, MassPerVolumeUnit::kg_Per_L);

// Step4. Define a new compound and move these concentrations to the compound
auto morphine_albumin_compound = std::make_unique<SESubstanceCompound>("morphine_albumin_compound", bg->GetLogger());
morphine_albumin_compound->SetClassification(CDM::enumSubstanceClass::Sedative);
morphine_albumin_compound->GetComponents().push_back(albuminConcentration);
morphine_albumin_compound->GetComponents().push_back(morphineConcentration);
morphine_albumin_compound->GetComponents().push_back(salineConcentration);

// Step 5. Put the definition of the coumpound to the manager
bg->GetSubstanceManager().AddCompound(*morphine_albumin_compound.release());
} else {
bg->GetLogger()->Error("Substance definitions for v, Morphine, and Saline required for this how-to.");
}


// Step6. Define the compound infusion action, and define the bag volume and rate of infusion
SESubstanceCompoundInfusion mac_infusion(*bg->GetSubstanceManager().GetCompound("morphine_albumin_compound"));
mac_infusion.GetBagVolume().SetValue(1.0, VolumeUnit::L);
mac_infusion.GetRate().SetValue(1.0, VolumePerTimeUnit::L_Per_day);

// Step7. Start the infusion
bg->ProcessAction(mac_infusion);//<Start Infusion
bg->AdvanceModelTime(10, TimeUnit::min);

// Step8. Step the infusion
mac_infusion.GetBagVolume().SetValue(1.0, VolumeUnit::L);
mac_infusion.GetRate().SetValue(0.0, VolumePerTimeUnit::L_Per_day);
bg->ProcessAction(mac_infusion);//<Stop Infusion

// Step9. Advance the time (or other further operations)
bg->AdvanceModelTime(10, TimeUnit::min);
bg->GetLogger()->Info("Finished");
return 0;
```