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

#include <biogears/cdm/substance/SESubstanceTransport.h>

namespace biogears {

template class SESubstanceTransportAmount<SEScalarVolume, SEScalarFraction>;
template class SESubstanceTransportAmount<SEScalarMass, SEScalarMassPerVolume>;

template class SESubstanceTransportVertex<SEScalarVolume, SEScalarVolume, SEScalarFraction>;
template class SESubstanceTransportVertex<SEScalarVolume, SEScalarMass, SEScalarMassPerVolume>;

template class SESubstanceTransportEdge<SEScalarVolumePerTime, SEScalarVolume, SEScalarVolume, SEScalarFraction>;
template class SESubstanceTransportEdge<SEScalarVolumePerTime, SEScalarVolume, SEScalarMass, SEScalarMassPerVolume>;

template class SESubstanceTransportGraph<SEScalarVolumePerTime, SEScalarVolume, SEScalarVolume, SEScalarFraction>;
template class SESubstanceTransportGraph<SEScalarVolumePerTime, SEScalarVolume, SEScalarMass, SEScalarMassPerVolume>;

template class SESubstanceTransporter<SEGasTransportGraph, VolumePerTimeUnit, VolumeUnit, VolumeUnit, NoUnit>;
template class SESubstanceTransporter<SELiquidTransportGraph, VolumePerTimeUnit, VolumeUnit, MassUnit, MassPerVolumeUnit>;

template bool operator==(SESubstanceTransportVertex<SEScalarVolume, SEScalarVolume, SEScalarFraction> const& lhs, SESubstanceTransportVertex<SEScalarVolume, SEScalarVolume, SEScalarFraction> const& rhs);
template bool operator==(SESubstanceTransportVertex<SEScalarVolume, SEScalarMass, SEScalarMassPerVolume> const& lhs, SESubstanceTransportVertex<SEScalarVolume, SEScalarMass, SEScalarMassPerVolume> const& rhs);
template bool operator!=(SESubstanceTransportVertex<SEScalarVolume, SEScalarVolume, SEScalarFraction> const& lhs, SESubstanceTransportVertex<SEScalarVolume, SEScalarVolume, SEScalarFraction> const& rhs);
template bool operator!=(SESubstanceTransportVertex<SEScalarVolume, SEScalarMass, SEScalarMassPerVolume> const& lhs, SESubstanceTransportVertex<SEScalarVolume, SEScalarMass, SEScalarMassPerVolume> const& rhs);

}
