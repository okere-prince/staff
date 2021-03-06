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

#include <staff/utils/Log.h>
#include <staff/common/Exception.h>
#include <staff/security/Users.h>
#include <staff/security/Groups.h>
#include <staff/security/UsersToGroups.h>
#include "AccountAdminImpl.h"

namespace staff
{
namespace admin
{

AccountAdminImpl::AccountAdminImpl()
{
}

AccountAdminImpl::~AccountAdminImpl()
{
}

::staff::admin::UserList AccountAdminImpl::GetUsers()
{
  ::staff::admin::UserList tResult;
  staff::security::UsersList lsSecUsers;

  staff::security::Users::Inst().GetList(lsSecUsers);

  for (staff::security::UsersList::const_iterator itUser = lsSecUsers.begin();
      itUser != lsSecUsers.end(); ++itUser)
  {
    ::staff::admin::User tUser;
    tUser.nId = itUser->nId;
    tUser.sName = itUser->sName;
    tUser.sDescription = itUser->sDescription;

    tResult.push_back(tUser);
  }

  return tResult;  // result
}

::staff::admin::GroupList AccountAdminImpl::GetGroups()
{
  ::staff::admin::GroupList tResult;
  staff::security::GroupsList lsSecGroups;

  staff::security::Groups::Inst().GetList(lsSecGroups);

  for (staff::security::GroupsList::const_iterator itGroup = lsSecGroups.begin();
      itGroup != lsSecGroups.end(); ++itGroup)
  {
    ::staff::admin::Group tGroup;
    tGroup.nId = itGroup->nId;
    tGroup.sName = itGroup->sName;
    tGroup.sDescription = itGroup->sDescription;

    tResult.push_back(tGroup);
  }

  return tResult;  // result
}

::staff::admin::IdList AccountAdminImpl::GetUserGroups(int nUserId)
{
  ::staff::admin::IdList tResult;
//  staff::security::TIntList lsGroups;
  staff::security::UsersToGroups::Inst().GetUserGroups(nUserId, tResult);

  return tResult;  // result
}

int AccountAdminImpl::AddUser(const std::string& sUserName, const std::string& sDescription)
{
  int tResult = -1;

  staff::security::Users::Inst().Add(sUserName, "", sDescription, tResult);

  return tResult;  // result
}

void AccountAdminImpl::RemoveUser(int nUserId)
{
  staff::security::Users::Inst().Remove(nUserId);
}

void AccountAdminImpl::SetUserPassword(int nUserId, const std::string& sPass)
{
  staff::security::Users::Inst().SetPassword(nUserId, sPass);
}

int AccountAdminImpl::AddGroup(const std::string& sGroupName, const std::string& sDescription)
{
  int tResult = -1;

  staff::security::Groups::Inst().Add(sGroupName, sDescription, tResult);

  return tResult;  // result
}

void AccountAdminImpl::RemoveGroup(int nGroupId)
{
  staff::security::Groups::Inst().Remove(nGroupId);
}

void AccountAdminImpl::AddUserToGroup(int nUserId, int nGroupId)
{
  staff::security::UsersToGroups::Inst().AddUserToGroup(nUserId, nGroupId);
}

void AccountAdminImpl::AddUserToGroups(int nUserId, const ::staff::admin::IdList& rlsGroupIds)
{
  for(::staff::admin::IdList::const_iterator itGroupId = rlsGroupIds.begin();
      itGroupId != rlsGroupIds.end(); ++itGroupId)
  {
    staff::security::UsersToGroups::Inst().AddUserToGroup(nUserId, *itGroupId);
  }
}

void AccountAdminImpl::RemoveUserFromGroup(int nUserId, int nGroupId)
{
  staff::security::UsersToGroups::Inst().RemoveUserFromGroup(nUserId, nGroupId);
}

void AccountAdminImpl::RemoveUserFromGroups(int nUserId, const ::staff::admin::IdList& rlsGroupIds)
{
  for(::staff::admin::IdList::const_iterator itGroupId = rlsGroupIds.begin();
      itGroupId != rlsGroupIds.end(); ++itGroupId)
  {
    staff::security::UsersToGroups::Inst().RemoveUserFromGroup(nUserId, *itGroupId);
  }
}

}
}
