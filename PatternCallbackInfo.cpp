#include "PatternCallbackInfo.h"

int DebugCallbackInfo(void* UserParameter)
{
	//add code here.	
	
	Digital.Pattern.Continue();
	return ERR_SUCCEED;
}

int PatternStopCallbackInfo(void* UserParameter)
{
	//add code here.
	
	return ERR_SUCCEED;
}

int EventCallbackInfo(CallbackParameter* Parameter, void* UserParameter)
{
	//add code here.
	
	return ERR_SUCCEED;
}

CallbackInfo ONESCallbackInfo(DebugCallbackInfo, PatternStopCallbackInfo, EventCallbackInfo);





