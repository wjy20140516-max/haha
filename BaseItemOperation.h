#pragma once
#include "interface/TestItemExecuteContext.h"
#define USER_AFTER_BIN

//该类是提供给用户使用的测试项基类，测试项类会继承该基类, 用户可以在该类中添加自己需要的方法，并在测试项类中使用这些方法.
class BaseItemOperation
{

public:
	/**
	* Init test
	*/
	bool UserInitialize(TestItemExecuteContext * aContext);

	/**
	* Run test
	*/
	void UserRun(TestItemExecuteContext * aContext);

	/**
	* Pause test
	*/
	void UserPause(TestItemExecuteContext * aContext);

	/**
	* Resume test
	*/
	void UserResume(TestItemExecuteContext * aContext);

	/**
	* Stop test
	*/
	void UserStop(TestItemExecuteContext * aContext);

	/**
	* Exit test
	*/
	void UserExit(TestItemExecuteContext * aContext);
	
	/**
	* AfterBin test
	*/
	void UserAfterBin(TestItemExecuteContext* aContext);

};
