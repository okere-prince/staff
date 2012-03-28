// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Client skeleton

#var HasAsynchOps $($nonblocking)
#ifeq($($HasAsynchOps),)
#foreach $(Project.Interfaces)
#foreach $(Interface.Classes)
#foreach $(Class.Members)
#foreach $(Member.Params)
#ifeq($(Param.DataType.Name),ICallback)
#var HasAsynchOps true
#ifeqend
#end
#end
#end
#end
#ifeqend
\
#include <memory>
#include <staff/utils/Log.h>
#ifneq($($HasAsynchOps),)
#include <staff/utils/Thread.h>
#include <staff/common/DataObject.h>
#include <staff/client/ICallback.h>
#ifeqend
#include <staff/common/Exception.h>
#include <staff/client/ServiceFactory.h>
#foreach $(Project.Interfaces)
#include "$(Interface.FilePath)$(Interface.Name).h"
#end

#ifneq($($HasAsynchOps),)
// callbacks

#foreach $(Project.Interfaces)
#ifneq($(Interface.Classes.$Count),0)
#foreach $(Interface.Classes)
#foreach $(Class.Members)
\
#var sCallbackType
#ifneq($($nonblocking),)
#var sCallbackType $(Member.Return.NsName)
#ifeqend
\
#foreach $(Member.Params)
#ifeq($(Param.DataType.Name),ICallback)
#var sCallbackType $(Param.DataType.TemplateParams.TemplateParam1)
#ifeqend
#end // member.params
\
#ifneq($($sCallbackType),)
// callback for $(Class.Name)::$(Member.Name)
class $(Class.Name)$(Member.Name)Callback: public staff::ICallback< $($sCallbackType) >
{
public:
  virtual void OnComplete(\
#ifneq($($sCallbackType),void)
$($sCallbackType) tResult\
#ifeqend
)
  {
    // process result here
#ifneq($($sCallbackType),void)
    // LogInfo() << "$(Member.Name)(asynch) result: " << tResult;
#ifeqend
  }

  void OnFault(const staff::DataObject& rFault)
  {
    // process error here
    LogError() << rFault.ToString();
  }
};

#ifeqend // sCallbackType
#end  // class.members
#end  // interface.classes
#ifeqend // ifneq((Interface.Classes.Count),0)
#end // Project.Interfaces

#ifeqend

int main(int /*nArgs*/, const char* /*paszArgs*/[])
{
  try
  {
#foreach $(Project.Interfaces)
#ifneq($(Interface.Classes.$Count),0)
#foreach $(Interface.Classes)
    std::auto_ptr< $(Class.NsName) > p$(Class.ServiceName)(::staff::ServiceFactory::Inst().GetService< $(Class.NsName) >());

    STAFF_ASSERT(p$(Class.ServiceName).get(), "Cannot get client for service $(Class.ServiceNsName)!");

    // Invoke Your service here:
#foreach $(Class.Members)

#foreach $(Member.Params)
#ifneq($(Param.DataType.Name),ICallback)
    // $(Param.DataType.NsName) $(Param.Name)\
#ifeq($(Param.DataType.Type),generic)
 = 0\
#ifeqend
;
#ifeqend
#end // Member.Params
#ifeq($(Member.IsAsynch)$($nonblocking),0) // blocking call
#var sResult $(Member.Options.*responseElement||Member.Options.*resultElement||"t$(Member.Name)Result")
    // \
#ifneq($(Member.Return.Name),void)
#ifeq($(Member.Return.Type),struct||typedef||template||string||dataobject)
const \
#ifeqend
$(Member.Return.NsName)\
#ifeq($(Member.Return.Type),struct||typedef||template||string||dataobject)
&\
#ifeqend
 $($sResult) = \
#ifeqend
p$(Class.ServiceName)->$(Member.Name)(\
#foreach $(Member.Params)
#ifneq($(Param.$Num),0)
, \
#ifeqend
$(Param.Name)\
#end // Member.Params
);
#ifneq($(Member.Return.Name),void)
    // LogInfo() << "$(Member.Name) result: " << $($sResult);
#else
    // LogInfo() << "$(Member.Name) called";
#ifeqend
#else // non blocking call
    // $(Class.Name)$(Member.Name)Callback t$(Class.Name)$(Member.Name)Callback;
    // p$(Class.ServiceName)->$(Member.Name)(\
#foreach $(Member.Params)
#ifneq($(Param.$Num),0)
, \
#ifeqend
#ifeq($(Param.DataType.Name),ICallback)
t$(Class.Name)$(Member.Name)Callback\
#else
$(Param.Name)\
#ifeqend // ICallback
#end // Member.Params
#ifneq($($nonblocking),)
, t$(Class.Name)$(Member.Name)Callback\
#ifeqend
);

    // // Wait for asynch call is completed
    // // Please note, that you cannot call any operation of this client
    // // until this asynchronous request is completed.
    // // To call operation while request is processing, please use another copy of client.
    // while (!t$(Class.Name)$(Member.Name)Callback.IsCompleted())
    // {
    //   staff::threading::Thread::Sleep(1000);
    // }

#ifeqend // blocking call
#end // class.members
#end // Interface.Classes
#ifeqend // (Interface.Classes.Count),0
#end // Project.Interfaces
  }
  STAFF_CATCH_ALL

  return 0;
}

