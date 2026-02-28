#include "MyTestDomainControlStrategy.h"
#include "interface/ONESInterfaceHeader.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"



MyTestDomainControlStrategy::MyTestDomainControlStrategy(TestDomainExecuteContext *aContext):TestDomainControlStrategy(aContext)
{
	//Do NOT Add Code here
}


MyTestDomainControlStrategy::~MyTestDomainControlStrategy()
{
	//Do NOT Add Code here
}

void MyTestDomainControlStrategy::BeforeSiteStart(TestDomainExecuteContext * aContext)
{
}

bool MyTestDomainControlStrategy::SystemInitialize(TestDomainExecuteContext * aContext)
{
	//Print("*****************************MyTestDomainControlStrategy::SystemInitialize");
	return true;
}

bool MyTestDomainControlStrategy::TestInitialize(TestDomainExecuteContext * aContext)
{
	//Print("*****************************MyTestDomainControlStrategy::TestInitialize");


	 //WaferId = aContext->GetWaferID();
	 //LotNumber = aContext->GetLotID();

	 WaferId = "B550064";
	 LotNumber = "B550064-14";


	



	DUT_LOOP_START

	dutx[dutz] = atoi((*item)->GetX().c_str());
	duty[dutz] = atoi((*item)->GetY().c_str());
	//printline("DUT%03d X/Y=%03d/%03d",dut,dutx[dutz],duty[dutz]);
	DUT_LOOP_END

	Get_Local_Time_1(local_time_s, sizeof(local_time_s));
	start_time_s = local_time_s;



	TestFlow = aContext->GetActiveFlowName();




	//test_num = "1350";
	//cp_ver = "Taiji1p8_CP_ProductionFlow_V1p1";
	//lotnum = "B550064";
	//wafernum = "B550064-14";
	//int Die_X = 0;
	//int Die_Y = 0;
	//testname;



	TheDevice.init();
	UniCusCOde.init();
	OlnTrim.init();



	Print("$$$$$$$$%%%%%%%%%%&&&&&&&&&&&&");

	return true;
}

void MyTestDomainControlStrategy::TestPause(TestDomainExecuteContext * aContext)
{
}

void MyTestDomainControlStrategy::TestResume(TestDomainExecuteContext * aContext)
{
}

void MyTestDomainControlStrategy::TestStop(TestDomainExecuteContext * aContext)
{
}

void MyTestDomainControlStrategy::TestExit(TestDomainExecuteContext * aContext)
{
	//Print("*****************************MyTestDomainControlStrategy::TestExit");
	Get_Local_Time_1(local_time_s, sizeof(local_time_s));
	end_time_s = local_time_s;
	PrintLogall(aContext);

}

void MyTestDomainControlStrategy::LotStart(TestDomainExecuteContext * aContext)
{
}

void MyTestDomainControlStrategy::WaferStart(TestDomainExecuteContext * aContext)
{
}

void MyTestDomainControlStrategy::WaferEnd(TestDomainExecuteContext * aContext)
{
}

void MyTestDomainControlStrategy::LotEnd(TestDomainExecuteContext * aContext)
{
}

void MyTestDomainControlStrategy::AfterSiteEnd(TestDomainExecuteContext * aContext)
{
}

REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(MyTestDomainControlStrategy, TestDomainExecuteContext *)
