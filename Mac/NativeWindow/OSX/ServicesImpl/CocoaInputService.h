//
//  CocoaInputService.h
//  GacTest
//
//  Created by Robert Bu on 12/2/14.
//  Copyright (c) 2014 Robert Bu. All rights reserved.
//

#ifndef __GAC_OSX_INPUT_SERVICE_H__
#define __GAC_OSX_INPUT_SERVICE_H__

#include "GacUI.h"
#include "../CocoaHelper.h"

#ifdef GAC_OS_OSX
#import <Quartz/Quartz.h>
#endif

namespace vl {
    
    namespace presentation {
        
        namespace osx {
            
            class EventTapException: public Exception
            {
            public:
                EventTapException(const WString& _message=WString::Empty):
                Exception(_message)
                {
                    
                }
            };
            
            // todo
#ifdef GAC_OS_OSX

            class CocoaInputService : public Object, public INativeInputService
            {
            public:
                typedef void (*TimerFunc)();
                typedef void (*MouseTapFunc)(CGEventType type, CGEventRef event);
                
            protected:
                collections::Dictionary<WString, vint>  keys;
                collections::Array<WString>             keyNames;
                
                CGEventSourceRef                        eventSource;
                bool                                    isTimerEnabled;
                bool                                    isHookingMouse;
                
                MouseTapFunc                            mouseTapFunc;
                TimerFunc                               timerFunc;
                
                CFMachPortRef                           inputTapPort;
                CFRunLoopSourceRef                      inputTapRunLoopSource;
                
                vint8_t                                 globalKeyStates[256];
                
            protected:
                void StartGCDTimer();
                // for global key states & mouse hooking
                void HookInput();
                
            public:
                CocoaInputService(MouseTapFunc mouseTap, TimerFunc timer);
                virtual ~CocoaInputService();
                
                void InitializeKeyMapping();
                void InvokeInputHook(CGEventType type, CGEventRef event);
                
                // INativeInputService
                
                void    StartHookMouse() override;
                void    StopHookMouse() override;
                bool    IsHookingMouse() override;
                void    StartTimer() override;
                void    StopTimer() override;
                bool    IsTimerEnabled() override;
                
                bool    IsKeyPressing(vint code) override;
                bool    IsKeyToggled(vint code) override;
                
                WString GetKeyName(vint code) override;
                vint    GetKey(const WString& name) override;
            };
#else
            class CocoaInputService : public Object, public INativeInputService
            {
            public:
                typedef void (*TimerFunc)();
                
            protected:
                collections::Dictionary<WString, vint>  keys;
                collections::Array<WString>             keyNames;
                
                TimerFunc                               timerFunc;
                bool                                    isTimerEnabled;

            protected:
                void StartGCDTimer();
                
            public:
                CocoaInputService(TimerFunc timer);
                virtual ~CocoaInputService();
                
                void InitializeKeyMapping();
                
                // INativeInputService
                
                void    StartHookMouse() override;
                void    StopHookMouse() override;
                bool    IsHookingMouse() override;
                void    StartTimer() override;
                void    StopTimer() override;
                bool    IsTimerEnabled() override;
                
                bool    IsKeyPressing(vint code) override;
                bool    IsKeyToggled(vint code) override;
                
                WString GetKeyName(vint code) override;
                vint    GetKey(const WString& name) override;
            };
            
#endif
        }

        
    }
    
}

#endif
