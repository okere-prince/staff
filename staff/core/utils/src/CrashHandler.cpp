/*
 *  Copyright 2011 Utkin Dmitry
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


#include <stdlib.h>
#include <signal.h>
#include "Log.h"
#include "Thread.h"
#include "StackTracer.h"
#include "CrashHandler.h"

#if defined __linux__ && !defined __USE_GNU
#define sighandler_t __sighandler_t
#else
#if defined __FreeBSD__ || defined __APPLE__
#define sighandler_t sig_t
#else
#ifdef WIN32
typedef void (*sighandler_t)(int);
#endif
#endif
#endif


namespace staff
{
  class CrashHandlerImpl
  {
  public:
    static void OnSignal(int nSignal)
    {
      if (nSignal == SIGSEGV || nSignal == SIGABRT)
      {
        std::string sTracedStack;
        StackTracer::GetStackTraceStr(sTracedStack);
        LogError() << (nSignal == SIGSEGV ? "Segmentation fault" : "Aborted")
                   << " in thread " << Thread::GetCurrentId()
                   << ".\nTraced stack:\n" << sTracedStack;
        exit(1);
      }
    }

    static sighandler_t m_pPrevSigSegvHandler;
    static sighandler_t m_pPrevSigAbrtHandler;
  };
  sighandler_t CrashHandlerImpl::m_pPrevSigSegvHandler = NULL;
  sighandler_t CrashHandlerImpl::m_pPrevSigAbrtHandler = NULL;


  void CrashHandler::Enable()
  {
    CrashHandlerImpl::m_pPrevSigSegvHandler = signal(SIGSEGV, CrashHandlerImpl::OnSignal);
    CrashHandlerImpl::m_pPrevSigAbrtHandler = signal(SIGABRT, CrashHandlerImpl::OnSignal);
  }

  void CrashHandler::Disable()
  {
    signal(SIGSEGV, CrashHandlerImpl::m_pPrevSigSegvHandler);
    CrashHandlerImpl::m_pPrevSigSegvHandler = NULL;
    signal(SIGABRT, CrashHandlerImpl::m_pPrevSigAbrtHandler);
    CrashHandlerImpl::m_pPrevSigAbrtHandler = NULL;
  }
  
} // namespace staff
