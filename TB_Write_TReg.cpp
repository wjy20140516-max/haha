#include "interface/ONESInterfaceHeader.h"
#include "TB_Write_TReg.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Write_TReg::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Write_TReg -- started");
    double ForceVoltage;
    int    TReg_Addr;
    int    TReg_Data;
    string pa;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceVoltage);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("Solid_Data s= %s", pa.c_str());
    TReg_Data = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = %d(dec) 0x%04x(hex)   ", TReg_Data, TReg_Data);
    }
    if (theParameters->TryGetParameter("Register_Address", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("Register_Address s= %s", pa.c_str());
    TReg_Addr = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Register_Address = %d(dec) 0x%04x(hex)   ", TReg_Addr, TReg_Addr);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    TRegWrite(TReg_Addr, TReg_Data);
    unsigned int TReg_ReadData[100];
    DUT_LOOP_START
    Print("Read_Treg_Adress[%d][%02x]Data[%02x]", dut, TReg_Addr, TReg_ReadData[dut-1]);
    if (TReg_ReadData[dut-1] != TReg_Data)
    {
    (*item)->SetValue(1);
    TB_Write_TReg_1380[dut - 1] = 1;
    }
    else
    {
    (*item)->SetValue(0);
    TB_Write_TReg_1380[dut - 1] = 0;
    }
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Write_TReg -- end");
    }

/**
* Constructor
*/
TB_Write_TReg::TB_Write_TReg(TestItemExecuteContext * aContext) : TestItem("TB_Write_TReg", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Write_TReg::~TB_Write_TReg() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Write_TReg::Initialize(TestItemExecuteContext * aContext) {
	if(!this->UserInitialize(aContext))
	{
	 	return false;		
	}
	//add code here.

	return true;
}

/**
* Exit test
*/
void TB_Write_TReg::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Write_TReg::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Write_TReg::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Write_TReg::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Write_TReg::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Write_TReg, TestItemExecuteContext *)

