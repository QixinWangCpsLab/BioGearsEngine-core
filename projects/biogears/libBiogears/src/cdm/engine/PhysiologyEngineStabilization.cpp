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
#include <biogears/cdm/engine/PhysiologyEngineStabilization.h>

#include <biogears/cdm/engine/PhysiologyEngineTrack.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/schema/cdm/EngineConfiguration.hxx>

namespace biogears {
//-------------------------------------------------------------------------------
PhysiologyEngineStabilization::PhysiologyEngineStabilization(Logger* logger)
  : Loggable(logger)
{
  m_StabilizationDuration = nullptr;
  m_currentTime = nullptr;
  
}
//-------------------------------------------------------------------------------
PhysiologyEngineStabilization::~PhysiologyEngineStabilization()
{
  Clear();
}
//-------------------------------------------------------------------------------
void PhysiologyEngineStabilization::Clear()
{
  m_LogProgress = true;
  m_Canceled = false;
  SAFE_DELETE(m_StabilizationDuration);
  SAFE_DELETE(m_currentTime);
}
//-------------------------------------------------------------------------------
bool PhysiologyEngineStabilization::Load(const CDM::PhysiologyEngineStabilizationData& in)
{
  Clear();
  if (in.Canceled().present()) {
    m_Canceled = in.Canceled().get();
  }
  if (in.LogProgress().present()) {
    m_LogProgress = in.LogProgress().get();
  }
  if (in.CurrentTime().present()) {
    GetCurrentTime().Load(in.CurrentTime().get());
  }
  if (in.StabilizationDuration().present()) {
    GetStabilizationDuration().Load(in.StabilizationDuration().get());
  }
  return true;
}
//-------------------------------------------------------------------------------
CDM::PhysiologyEngineStabilizationData* PhysiologyEngineStabilization::Unload() const
{
  CDM::PhysiologyEngineStabilizationData* data(new CDM::PhysiologyEngineStabilizationData());
  Unload(*data);
  return data;
}
//-------------------------------------------------------------------------------
void PhysiologyEngineStabilization::Unload(CDM::PhysiologyEngineStabilizationData& data) const
{
  data.Canceled(m_Canceled);
  data.LogProgress(m_LogProgress);
  if (HasCurrentTime()) {
    data.CurrentTime(std::unique_ptr<CDM::ScalarTimeData>(m_currentTime->Unload()));
  }
  if (HasStabilizationDuration()) {
    data.StabilizationDuration(std::unique_ptr<CDM::ScalarTimeData>(m_StabilizationDuration->Unload()));
  }
  data.CurrentTime();

}
//-------------------------------------------------------------------------------
void PhysiologyEngineStabilization::LogProgress(bool b)
{
  m_LogProgress = b;
}
//-------------------------------------------------------------------------------
void PhysiologyEngineStabilization::CancelStabilization()
{
  m_Canceled = true;
}
//-------------------------------------------------------------------------------
bool PhysiologyEngineStabilization::HasStabilizationDuration() const 
{
  return m_StabilizationDuration == nullptr ? false : m_StabilizationDuration->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarTime& PhysiologyEngineStabilization::GetStabilizationDuration()
{
  if (m_StabilizationDuration == nullptr)
    m_StabilizationDuration = new SEScalarTime();
  return *m_StabilizationDuration;
}
//-------------------------------------------------------------------------------
bool PhysiologyEngineStabilization::HasCurrentTime() const
{
  return m_currentTime == nullptr ? false : m_currentTime->IsValid();
}
//-------------------------------------------------------------------------------
SEScalarTime& PhysiologyEngineStabilization::GetCurrentTime()
{
  if (m_currentTime == nullptr)
    m_currentTime = new SEScalarTime();
  return *m_currentTime;
}
//-------------------------------------------------------------------------------
bool PhysiologyEngineStabilization::operator==(PhysiologyEngineStabilization const& rhs) const
{
  return m_Canceled == rhs.m_Canceled
    && rhs.m_LogProgress == rhs.m_LogProgress
    && ((m_currentTime && rhs.m_currentTime) ? m_currentTime->operator==(*rhs.m_currentTime) : m_currentTime == rhs.m_currentTime)
    && ((m_StabilizationDuration && rhs.m_StabilizationDuration) ? m_StabilizationDuration->operator==(*rhs.m_StabilizationDuration) : m_StabilizationDuration == rhs.m_StabilizationDuration);
}
bool PhysiologyEngineStabilization::operator!=(PhysiologyEngineStabilization const& rhs) const
{
  return !(*this == rhs);
}
//-------------------------------------------------------------------------------
}