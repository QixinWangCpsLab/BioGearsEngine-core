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

#include <biogears/cdm/properties/SEUnitScalar.h>

namespace biogears {
SEUnitScalar::SEUnitScalar(bool ro)
  : SEScalar(NaN,ro)
{
}

//------------------------------------------------------------------------------
SEUnitScalar::SEUnitScalar(const SEUnitScalar& obj)
  : SEScalar(obj)
{
}
//------------------------------------------------------------------------------
SEUnitScalar::~SEUnitScalar()
{
  //TODO:Convert Unit PTR to a shared_ptr or a non reference
}

}