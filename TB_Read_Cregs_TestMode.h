#pragma once
#include "PatternCallbackInfo.h"
#include "BaseItemOperation.h"
#include "interface/TestItem.h"
#include "interface/TestDomainExecuteContext.h"
class TB_Read_Cregs_TestMode :
	public TestItem, private BaseItemOperation
{
public:
	TB_Read_Cregs_TestMode(TestItemExecuteContext * aContext);
	~TB_Read_Cregs_TestMode();
protected:
	/**
	* Init test
	*/
	bool Initialize(TestItemExecuteContext * aContext);

	/**
	* Run test
	*/
	void Run(TestItemExecuteContext * aContext);

	/**
	* Pause test
	*/
	void Pause(TestItemExecuteContext * aContext);

	/**
	* Resume test
	*/
	void Resume(TestItemExecuteContext * aContext);

	/**
	* Stop test
	*/
	void Stop(TestItemExecuteContext * aContext);

	/**
	* Exit test
	*/
	void Exit(TestItemExecuteContext * aContext);

	#ifdef USER_AFTER_BIN
	/**
	* AfterBin test
	*/
	void AfterBin(TestItemExecuteContext * aContext);
	#endif
	
};