#var aStdIncludes
#var aStaffIncludes
\
#foreach $(Interface.Structs)
#cginclude "DetectStructInclude.h"
#end       // foreach Interface.Structs
\
#foreach $(Interface.Typedefs)
#ifeq($(Typedef.Extern),false)
#context $(Typedef.DataType)
#cginclude "DetectTypeInclude.h"
#contextend
#ifeqend
#end       // foreach Interface.Typedefs
\
#foreach $(Interface.Classes)
#foreach $(Class.Members)
#foreach $(Member.Params)
#context $(Param.DataType)
#cginclude "DetectTypeInclude.h"
#contextend
#end // also check return type
#context $(Member.Return)
#cginclude "DetectTypeInclude.h"
#contextend
#end
#end       // foreach Interface.Classes
\
\
\
$($aStdIncludes.!replace/[/#include </.!replace/]/>\n/)\
$($aStaffIncludes.!replace/[/#include </.!replace/]/>\n/)\
\
#ifneq($(Interface.Classes.$Count),0)
#include <staff/common/IService.h>
#ifeqend
