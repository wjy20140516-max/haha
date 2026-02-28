#pragma once
#include "interface/ONESInterfaceHeader.h"

extern int DebugCallbackInfo(void* UserParameter);

extern int PatternStopCallbackInfo(void* UserParameter);

extern int EventCallbackInfo(CallbackParameter* Parameter, void* UserParameter);

extern CallbackInfo ONESCallbackInfo;

#define ONES_CALLBACK &ONESCallbackInfo