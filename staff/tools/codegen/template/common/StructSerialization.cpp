#ifeq($(Struct.Extern),0) // do not serialize/deserialize extern type
#foreach $(Struct.Structs)
#cginclude "StructSerialization.cpp"
#end
#foreach $(Struct.Enums)
#cginclude "EnumSerialization.cpp"
#end
\
#ifeq($(Struct.Options.*abstract),true||1)

DataObject& operator<<(DataObject& rdoParam, const Abstract< $(Struct.NsName) >& tpAbstractStruct)
{
  const std::string& sInstanceType = tpAbstractStruct.GetType();
#var sThisStructNsName $(.NsName)
#foreach $(Interface.Structs) // check all top-level structs including external
#ifeq($(Struct.ParentNsName),$($sThisStructNsName))
  if (sInstanceType == "$(Struct.NsName.!dot)")
  {
    rdoParam << static_cast< const $(Struct.NsName)& >(*tpAbstractStruct);
  }
  else
#ifeqend
#end
  {
    RISE_THROWS(rise::CLogicNoItemException, "Can't serialize dynamic type [" + sInstanceType + "]");
  }
  rdoParam.SetInstanceType(sInstanceType);
  return rdoParam;
}

const DataObject& operator>>(const DataObject& rdoParam, Abstract< $(Struct.NsName) >& tpAbstractStruct)
{
  const std::string& sInstanceType = rdoParam.GetInstanceType();
#var sThisStructNsName $(.NsName)
#foreach $(Interface.Structs) // check all top-level structs including external
#ifeq($(Struct.ParentNsName),$($sThisStructNsName))
  if (sInstanceType == "$(Struct.NsName.!dot)")
  {
    tpAbstractStruct = new $(Struct.NsName);
    rdoParam >> static_cast< $(Struct.NsName)& >(*tpAbstractStruct);
  }
  else
#ifeqend
#end
  {
    RISE_THROWS(rise::CLogicNoItemException, "Can't deserialize dynamic type [" + sInstanceType + "]");
  }
  return rdoParam;
}
#ifeqend
\

DataObject& operator<<(DataObject& rdoParam, const $(Struct.NsName)& \
#ifeq($(Struct.Members.$Count),0)
/*\
#ifeqend
rstStruct\
#ifeq($(Struct.Members.$Count),0)
*/\
#ifeqend
)
{
#ifneq($(Struct.ParentName),)
  // serialize parent struct
  rdoParam << static_cast< const $(Struct.ParentNsName)& >(rstStruct);

#ifeqend
\
#foreach $(Struct.Members)
#context $(Param.DataType)
#var sParam rstStruct.$(Param.Name)
#var sParamName $(Param.Name)
#ifeq($(Param.Options.*useParentElement),true||1) // serialize to parent element?
#var sdoParam rdoParam
#else
#var sdoParam rdoParam.CreateChild("$(Param.Name)")
#ifeqend
#cginclude "TypeSerialization.cpp"
#contextend
#end
  return rdoParam;
}

const DataObject& operator>>(const DataObject& rdoParam, $(Struct.NsName)& \
#ifeq($(Struct.Members.$Count),0)
/*\
#ifeqend
rstStruct\
#ifeq($(Struct.Members.$Count),0)
*/\
#ifeqend
)
{
#ifneq($(Struct.ParentName),)
  // deserialize parent struct
  rdoParam >> static_cast< $(Struct.ParentNsName)& >(rstStruct);

#ifeqend
#foreach $(Struct.Members)
#context $(Param.DataType)
#var sParam rstStruct.$(Param.Name)
#var sParamName $(Param.Name)
#var sdoParam rdoParam
#cginclude "TypeDeserialization.cpp"
#contextend
#end
  return rdoParam;
}
#ifeqend
