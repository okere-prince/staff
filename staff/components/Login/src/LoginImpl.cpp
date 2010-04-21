/*
 *  Copyright 2009 Utkin Dmitry
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
/* 
 *  This file is part of the WSF Staff project.
 *  Please, visit http://code.google.com/p/staff for more information.
 */

// This file generated by staff_codegen
// Service Implementation

#include <staff/common/Exception.h>
#include <rise/common/exmacros.h>
#include <rise/common/ExceptionTemplate.h>
#include <staff/security/Sessions.h>
#include <staff/component/SessionManager.h>
#include "LoginImpl.h"

namespace staff
{

  CLoginImpl::~CLoginImpl()
  {
  }

  std::string CLoginImpl::Login(const std::string& sUserName, const std::string& sPassword)
  {
    std::string tResult;

    RISE_ASSERTES(IService::GetSessionId() == staff::security::CSessions::sNobodySessionId,
      rise::CLogicAlreadyExistsException, "Cannot login from non-nobody session");

    staff::CSessionManager::Inst().Login(sUserName, sPassword, tResult);

    return tResult;  // result
  }

  std::string CLoginImpl::OpenSession(const std::string& sUserName, const std::string& sPassword, bool bCloseExisting)
  {
    std::string tResult;

    RISE_ASSERTES(IService::GetSessionId() == staff::security::CSessions::sNobodySessionId,
      rise::CLogicAlreadyExistsException, "Cannot login from non-nobody session");

    staff::CSessionManager::Inst().Open(sUserName, sPassword, bCloseExisting, tResult);

    return tResult;  // result
  }

  void CLoginImpl::Logout()
  {
    staff::CSessionManager::Inst().Close(IService::GetSessionId());
  }

  void CLoginImpl::KeepAliveSession()
  {
    staff::CSessionManager::Inst().Keepalive(IService::GetSessionId());
  }

  std::string CLoginImpl::GetUserName()
  {
    std::string tResult;

    staff::security::CSessions::Inst().GetUserName(IService::GetSessionId(), tResult);

    return tResult;  // result
  }

  int CLoginImpl::GetSessionExpiration() const
  {
    return staff::security::CSessions::Inst().GetExpiration();
  }

  bool CLoginImpl::ValidateSession()
  {
    return staff::security::CSessions::Inst().Validate(IService::GetSessionId());
  }

}

