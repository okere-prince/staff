// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// DO NOT EDIT

#ifneq($(Interface.Classes.$Count),0)
#include <staff/utils/SharedPtr.h>
#ifeqend
#include <staff/utils/Log.h>
#include <staff/utils/fromstring.h>
#include <staff/utils/tostring.h>
#include <staff/utils/HexBinary.h>
#include <staff/utils/Base64Binary.h>
#include <staff/common/Attribute.h>
#include <staff/common/Exception.h>
#include <staff/common/DataObject.h>
#ifneq($(Interface.Classes.$Count),0)
#include <staff/common/Operation.h>
#include <staff/common/IService.h>
#include <staff/component/ServiceInstanceManager.h>
#include <staff/component/Component.h>
#include "$(Interface.FilePath)$(Interface.Name)Impl.h"
#ifeqend // #ifneq($(Interface.Classes.$Count),0)
\
#foreach $(Interface.Structs) // headers for extern abstract types
#ifeq($(Struct.Extern),false)
#ifeq($(Struct.Options.*abstract),true||1)
#var sThisStructNsName $(Struct.NsName)
#var sThisInterfaceNsName $(Interface.NsName)
#var bThisInterfaceIncluded 0
#foreach $(Project.Interfaces)
#foreach $(Interface.Structs)
#ifeq($(Struct.ParentNsName)-$(Struct.Extern),$($sThisStructNsName)-false)
#ifneq($(Interface.NsName),$($sThisInterfaceNsName))
#ifeq($($bThisInterfaceIncluded),0)
#include "$(Interface.FilePath)$(Interface.Name)Wrapper.h"
#var bThisInterfaceIncluded 1
#ifeqend
#ifeqend
#ifeqend
#end
#end
#ifeqend
#ifeqend
#end
\
#include "$(Interface.FilePath)$(Interface.Name)Wrapper.h"

#cginclude <common/Serialization.cpp>

#ifneq($(Interface.Classes.$Count),0)
#foreach $(Interface.Classes)

$(Class.OpeningNs)

$(Class.Name)Wrapper::$(Class.Name)Wrapper(staff::Component* pComponent):
  m_pComponent(pComponent)
{
}

$(Class.Name)Wrapper::~$(Class.Name)Wrapper()
{
}

void $(Class.Name)Wrapper::Invoke(staff::Operation& rOperation, const std::string& sSessionId, const std::string& sInstanceId)
{
  const staff::DataObject& rRequest = rOperation.Request();
  const std::string& sOperationName = rOperation.GetName();

  if (sOperationName == "GetServiceDescription")
  {
    rOperation.SetResponse(GetServiceDescription());
  }
  else
  if (sOperationName == "CreateInstance")
  {
    staff::ServiceInstanceManager::Inst().CreateServiceInstance(sSessionId, m_sName,
                                                                rRequest.GetChildTextByLocalName("sInstanceId"));
  }
  else
  if (sOperationName == "FreeInstance")
  {
    staff::ServiceInstanceManager::Inst().FreeServiceInstance(sSessionId, m_sName,
                                                              rRequest.GetChildTextByLocalName("sInstanceId"));
  }
  else
  {
    staff::SharedPtr<$(Class.Name)Impl> tpServiceImpl = GetImpl(sSessionId, sInstanceId);
#foreach $(Class.Members)
    if (sOperationName == "$(Member.Options.*requestElement||Member.Name)")
    {
#ifneq($(Member.Return.Type)-$(Member.Options.*useParentElement),dataobject-true||dataobject-1)
#ifneq($(Member.Options.*responseElement),)
      rOperation.SetResponseName("$(Member.Options.*responseElement)");
#else
#ifneq($(Member.Return.ResponseName),)
      rOperation.SetResponseName("$(Member.Return.ResponseName)");
#ifeqend
#ifeqend
#ifeqend
\
#ifneq($(Member.Options.*mep),in-only)
\
#var elementForm $(Interface.Options.*elementFormDefault)
#var attributeForm $(Interface.Options.*attributeFormDefault)
\
#ifneq($(Member.Options.*form),)
#ifeq($(Member.Options.*attribute),true||1)
#var attributeForm $(Member.Options.form)
#else
#var elementForm $(Member.Options.form)
#ifeqend
#ifeqend
\
#ifneq($($elementForm),)
  rOperation.GetResponse().SetElementFormQualified($($elementForm.!match/qualified/));
#ifeqend
\
#ifneq($($attributeForm),)
  rOperation.GetResponse().SetAttributeFormDefaultQualified($($attributeForm.!match/qualified/));
#ifeqend
#ifeqend
\
#ifneq($(Member.Options.*resultElement),)
      rOperation.SetResultName("$(Member.Options.*resultElement)");
#ifeqend
#foreach $(Member.Params)
#ifeq($(Param.DataType.Type),struct||typedef||template||generic||enum)
#ifneq($(Param.DataType.Name),Operation||MessageContext)
      $(Param.DataType.NsName) $(Param.Name)\
#ifeq($(Param.DataType.Type),generic)
 = 0\
#ifeqend
;
#ifeqend
#ifeqend
#end
\
#foreach $(Member.Params)  // ------------------- params ------------------------
#ifeq($(Param.Options.*useParentElement),)
#var sElementName
#else
#var sElementName $(Param.Options.*elementName||Param.Name)
#ifeqend
#ifeq($(Param.DataType.Type),struct||typedef||template||generic||enum)
#context $(Param.DataType)
#indent +2
#ifneq($(Param.Options.*useParentElement||Member.Options.*inlineRequestElement),)
#var sParam $(Param.Name)
#var sParamName
#var sdoParam rRequest
#else
#var sParam $(Param.Name)
#var sParamName $(Param.Name)
#var sdoParam rRequest
#ifeqend
\
#cginclude <common/TypeDeserialization.cpp>
#indent -2
#contextend
#ifeqend
#end       // ----------------- return -------------------
      \
#ifneq($(Member.Return.Name),void)      // !!not_void!!
#ifeq($(Member.Return.Type),struct||typedef||template||enum)
const $(Member.Return.NsName)& tResult = \
#else
#ifeq($(Member.Return.Type),enum)
$(Member.Return.NsName) tResult = \
#else
#ifeq($(Member.Return.Type),generic||string)    // !!generic!!
rOperation.Result().SetValue(\
#else
#ifeq($(Member.Return.Type),dataobject) // !!dataobject!!
#ifeq($(Member.Options.*useParentElement),true||1)
rOperation.Result() = \
#else
rOperation.Result().AppendChild(\
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend // invoke an function
\
tpServiceImpl->$(Member.Name)(\
#foreach $(Member.Params)
#ifneq($(Param.$Num),0) // param splitter
, \
#ifeqend // params
#ifeq($(Param.DataType.Name),MessageContext)
rOperation.GetMessageContext()\
#else
#ifeq($(Param.DataType.Name),Operation)
rOperation\
#else
#ifeq($(Param.DataType.Type),string||dataobject)
#context $(Param.DataType)
#ifneq($(Param.Options.*useParentElement||Member.Options.*inlineRequestElement),)
#var sParam $(Param.Name)
#var sParamName
#var sdoParam rRequest
#else
#var sParam
#var sParamName $(Param.Name)
#var sdoParam rRequest
#ifeqend
#cginclude <common/TypeDeserialization.cpp>
#contextend
#else
#ifeq($(Param.DataType.Type),struct||typedef||template||generic||enum)
$(Param.Name)\
#else
#cgerror "Param.DataType.Type = $(Param.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#end // end of function param list
\
#ifneq($(Member.Return.Name),void)
#ifeq($(Member.Return.Type),generic||string)
)\
#else
#ifeq($(Member.Return.Type),dataobject)
#ifneq($(Member.Options.*useParentElement),true||1)
)\
#ifeqend
#ifeqend
#ifeqend
#ifeqend
);
\
\
#ifneq($(Member.Return.Type),generic||string||dataobject)
#context $(Member.Return)
#indent +2
#var sParam tResult
#var sdoParam rOperation.Result()
#cginclude <common/TypeSerialization.cpp>
#indent -2
#contextend
#ifeqend
#ifeq($(Member.Return.Type)-$(Member.Options.*useParentElement),dataobject-true||dataobject-1)
#ifneq($(Member.Options.*responseElement),)
      rOperation.SetResponseName("$(Member.Options.*responseElement)");
#else
#ifneq($(Member.Return.ResponseName),)
      rOperation.SetResponseName("$(Member.Return.ResponseName)");
#ifeqend
#ifeqend
#ifeqend
#ifeq($(Member.Options.*dontSetResultNamespace),true)
      return;
#else
#ifneq($(Member.Options.*responseTargetNamespace),)
#ifneq($(Class.Options.*targetNamespacePrefix),)
    rOperation.GetResponse().SetNamespace("$(Member.Options.*responseTargetNamespace)", "$(Class.Options.*targetNamespacePrefix)");
#else
    rOperation.GetResponse().SetNamespaceUriGenPrefix("$(Member.Options.*responseTargetNamespace)");
#ifeqend
      return;
#else
#ifeq($(Member.Options.*mep),in-only)
      return;
#ifeqend
#ifeqend
#ifeqend
    }
    else
#end
    {
      STAFF_THROW(staff::RemoteException, "Unknown Operation: " + rOperation.GetName());
    }

#ifneq($(Class.Options.*targetNamespacePrefix),)
#ifneq($(Class.Options.*targetNamespace),)
    rOperation.GetResponse().SetNamespace("$(Class.Options.*targetNamespace)", "$(Class.Options.*targetNamespacePrefix)");
#else
    rOperation.GetResponse().SetNamespace("http://tempui.org/" + m_pComponent->GetName(), "$(Class.Options.*targetNamespacePrefix)");
#ifeqend
#else
#ifneq($(Class.Options.*targetNamespace),)
    rOperation.GetResponse().SetNamespaceUriGenPrefix("$(Class.Options.*targetNamespace)");
#else
    rOperation.GetResponse().SetNamespaceUriGenPrefix("http://tempui.org/" + m_pComponent->GetName());
#ifeqend
#ifeqend
  }
}

const std::string& $(Class.Name)Wrapper::GetName() const
{
  return m_sName;
}

const std::string& $(Class.Name)Wrapper::GetDescr() const
{
  return m_sDescr;
}

const staff::Component* $(Class.Name)Wrapper::GetComponent() const
{
  return m_pComponent;
}

staff::Component* $(Class.Name)Wrapper::GetComponent()
{
  return m_pComponent;
}

staff::PIService& $(Class.Name)Wrapper::GetImpl(const std::string& sSessionId, const std::string& sInstanceId)
{
  return staff::ServiceInstanceManager::Inst().GetServiceInstance(sSessionId, m_sName, sInstanceId);
}

staff::PIService $(Class.Name)Wrapper::NewImpl()
{
  return new $(Class.Name)Impl;
}

bool $(Class.Name)Wrapper::IsLoadAtStartup() const
{
  return \
#ifeq($(Class.Options.*loadAtStartup),true)
true;
#else
false;
#ifeqend
}

std::string $(Class.Name)Wrapper::GetDependencies() const
{
  return "$(Class.Options.*dependencies)";
}

staff::DataObject $(Class.Name)Wrapper::GetOperations() const
{
  staff::DataObject tOperations("Operations");

#foreach $(Class.Members)
  {// Operation: $(Member.Return.NsName) $(Member.Name)($(Member.Params))$(Member.Const)
    staff::DataObject tOp$(Member.Name) = tOperations.CreateChild("Operation");
    tOp$(Member.Name).CreateChild("Name", "$(Member.Name)");
    tOp$(Member.Name).CreateChild("RestMethod", "$(Member.Options.*restMethod)");
    tOp$(Member.Name).CreateChild("RestLocation", "$(Member.Options.*restLocation)");
  }
#end

  return tOperations;
}

staff::DataObject $(Class.Name)Wrapper::GetServiceDescription() const
{
  staff::DataObject tServiceDescription;

  tServiceDescription.Create("ServiceDescription");
  tServiceDescription.DeclareDefaultNamespace("http://tempui.org/staff/service-description");

  tServiceDescription.CreateChild("Name", m_sName);
  tServiceDescription.CreateChild("Description", m_sDescr);

  tServiceDescription.AppendChild(GetOperations());

  return tServiceDescription;
}

const std::string $(Class.Name)Wrapper::m_sName = "$(Class.ServiceNsName)";
const std::string $(Class.Name)Wrapper::m_sDescr = \
#ifneq($(Class.Description),)
"$(Class.Description)";
#else
"Staff service $(Class.ServiceName)";
#ifeqend

$(Class.EndingNs)
#end
#ifeqend // #ifneq($(Interface.Classes.$Count),0)

