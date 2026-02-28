#pragma once
#include "interface/TestDomainControlStrategy.h"
#include "interface/TestDomainExecuteContext.h"

class MyTestDomainControlStrategy :public TestDomainControlStrategy
{
public:
	MyTestDomainControlStrategy(TestDomainExecuteContext *aContext);
	~MyTestDomainControlStrategy();
protected:

	/**
	* load文件成功SiteTest进程起来后,SystemInitialize前
	*
	* @par Description
	* 测试执行前的回调,用户可以在BeforeSiteStart函数中做测试前准备操作如：执行PB板相关的操作或日志输出. 用户不可以在BeforeSiteStart中使用VI、Digital、TMU、CBIT等对象.
	*
	* @param [in] aContext 测试上下文.
	*/

	void BeforeSiteStart(TestDomainExecuteContext *aContext);
	/**
	*load文件成功SiteTest进程起来后SendWaferInfo前上位触发
	*
	* @par Description
	*  系统初始化.
	*
	* @return 初始化结果,True表示成功,False表示失败
	*/
	bool SystemInitialize(TestDomainExecuteContext *aContext);
	/**
	*  测试初始化，Start按钮后触发
	*
	* @param [in] aContext 测试上下文.
	*/
	bool TestInitialize(TestDomainExecuteContext *aContext);
	/**
	*  测试暂停,暂停按钮时触发
	*
	* @param [in] aContext 测试上下文.
	*/
	void TestPause(TestDomainExecuteContext *aContext);
	/**
	*  测试继续，Resume按钮触发
	*
	* @param [in] aContext 测试上下文.
	*/
	void TestResume(TestDomainExecuteContext *aContext);
	/**
	*  测试终止，Stop按钮触发
	*
	* @param [in] aContext 测试上下文.
	*/
	void TestStop(TestDomainExecuteContext *aContext);
	/**
	*  测试退出，测试流测试结束时执行
	*
	* @param [in] aContext 测试上下文.
	*/
	void TestExit(TestDomainExecuteContext *aContext);
	/**
	*  Lot测试开始，扎针前，第一片Wafer的时候触发，只执行一次
	*
	* @param [in] aContext 测试上下文.
	*/
	void LotStart(TestDomainExecuteContext * aContext);
	/**
	*  Wafer测试开始，扎针前，每片Wafer开始测试时触发，一个Wafer只执行一次
	*
	* @param [in] aContext 测试上下文.
	*/
	void WaferStart(TestDomainExecuteContext * aContext);
	/**
	*  Wafer测试结束，针已抬起，无可测试的DUT触发
	*
	* @param [in] aContext 测试上下文.
	*/
	void WaferEnd(TestDomainExecuteContext * aContext);
	/**
	*  Lot测试结束，并会Stop测试流
	*
	* @param [in] aContext 测试上下文.
	*/
	void LotEnd(TestDomainExecuteContext * aContext);

	/**
	* Player关闭，系统退出的时候触发
	*
	* @par Description
	* 测试执行结束后的回调,用户可以在AfterSiteEnd函数中做测试执行结束后操作如：执行PB板相关的操作或日志输出.
	* 用户不可以在AfterSiteEnd中使用VI、Digital、TMU、CBIT等对象
	*(需要注意 由于logviewer已关闭输出日志需要在主控slot.userlog内查看).
	*
	* @param [in] aContext 测试上下文.
	*/
	void AfterSiteEnd(TestDomainExecuteContext *aContext);

};