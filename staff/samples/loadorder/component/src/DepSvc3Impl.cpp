// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#include <staff/utils/Log.h>
#include "DepSvc3Impl.h"

namespace samples
{
namespace loadorder
{

DepSvc3Impl::DepSvc3Impl()
{
}

DepSvc3Impl::~DepSvc3Impl()
{
}

void DepSvc3Impl::OnCreate()
{
  staff::LogInfo() << "Service 3 is loaded";
}

void DepSvc3Impl::OnDestroy()
{
  // this function is called immediately before service instance destruction
}


}
}

