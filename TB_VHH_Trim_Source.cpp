#include "interface/ONESInterfaceHeader.h"
#include "TB_VHH_Trim_Source.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_VHH_Trim_Source::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_VHH_Trim_Source -- started");
    double VLimit_High;
    double VLimit_Low;
    double ForceHighVoltage;
    int Register_Address;
    int Solid_Data;
    int Mbist_Start_Page;
    int Mbist_Pages;
    TABLE_VAR tv_parameters;
    // int Mbist_Page_Bytes        = MBIST_READ_DDW_PAGE;
    // int Read_Bytes              = Mbist_Pages * Mbist_Page_Bytes;
    int Read_Bytes = 0x80;
    int ip_inx = 0;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Register_Address", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("Solid_Data s= %s", pa.c_str());
    Register_Address = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = %d(dec) 0x%04x(hex)   ", Register_Address, Register_Address);
    }
    if (theParameters->TryGetParameter("VHH", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("VHH = %2f", ForceHighVoltage);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("Solid_Data s= %s", pa.c_str());
    Solid_Data = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = %d(dec) 0x%04x(hex)   ", Solid_Data, Solid_Data);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    std::string outBfr;
    // Reset trim flag
    DUT_LOOP_START
    UserRegs.set_trim_flag(dutz, false);
    DUT_LOOP_END
    unsigned int trim_pass_mask = 0;  //// initial val = 0. switch to 1 if dut failed
    // Step0 Load CFG and Compare
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    // Step1 Treg setup Command=0Bh
    // 1) Write Treg
    #if (USE_BLUEFIN_INSTRUCTION_SET == 1)
    TRegWrite(Register_Address, Solid_Data);
    #endif
    // 2) Read T-Reg
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, Register_Address, TReg_ReadData);
    //DUTȡ
    DUT_LOOP_START
    //Print("[[Read T-Reg] DUT[%] %02Xh = %02Xh (Hex)",dut, Register_Address, TReg_ReadData[dut-1]);
    Print("[Read T-Reg] %02Xh = %02Xh (Hex)", Register_Address, TReg_ReadData[dut-1]);
    DUT_LOOP_END
    // Step3 measure VHH voltage regardless of criteria
    // 1) Read Config-Register Data
    ReadConfigFileTrim;
    // 2) initial val = 1, switch to 0 if passed the trim criteria
    int DutPassMask = 0x0;
    DUT_LOOP_START
    DutPassMask |= (1ULL << dut);
    DUT_LOOP_END
    // ETLog::Info("DutPassMask is 0x{:2X}",DutPassMask);
    trim_pass_mask /*OR*/ |= iterate_ip_voltage_trim(aContext, DutPassMask, 0, ip_inx, ForceHighVoltage/* target voltage for vhh trim */, UserRegs);
    // ETLog::Info("trim_pass_mask is {}",trim_pass_mask);
    // Step4 restore Tregs
    TRegWrite(0xFF, 0x00);  // register-addr=0xFF
    // Read T-Reg Addr
    TReg_ReadData[MAX_DUTS] = { 0 };
    TRegsRead(aContext, Register_Address, TReg_ReadData);
    //DUTȡ
    DUT_LOOP_START
    //Print("[TRegs_Read] DUT %d Read T-Reg = %02X %02X %02X %02X (Hex)", dut, TReg_ReadData[0], TReg_ReadData[1], TReg_ReadData[2], TReg_ReadData[3]);
    Print("[Read T-Reg] = %02X %02X %02X %02X (Hex)", TReg_ReadData[0], TReg_ReadData[1], TReg_ReadData[2], TReg_ReadData[3]);
    DUT_LOOP_END
    ///// +-----------------------------
    ///// + Step5 update dut trim flag & log
    ///// +-----------------------------
    DUT_LOOP_START
    if (!(trim_pass_mask & (1ULL << dutz)))//// find 0: pass dut
    UserRegs.set_trim_flag(dutz, true);
    Print("[Update Trim Flag] DUT[%d], dut_trim_mask = 0x%2Xh,trimflag:0x%02Xh", dut, trim_pass_mask, UserRegs.get_trim_flag(dutz));
    if (UserRegs.get_trim_flag(dutz) == 1)
    {
    (*item)->SetValue(0);
    Print("[VOLTAGE TRIM]: V1= %d, V2= %d", (UserRegs.get_v1_trim_val(dutz, 0)), (UserRegs.get_v2_trim_val(dutz, 0)));
    //testlog.Info("[VOLTAGE TRIM]: V1= {}, V2= {}", (UserRegs.get_v1_trim_val(dut, 0)), (UserRegs.get_v2_trim_val(dut, 0)));
    }
    else
    {
    (*item)->SetValue(0);
    Print("[VOLTAGE TRIM]: V1= %d, V2= %d", (UserRegs.get_v1_trim_val(dutz, 0)), (UserRegs.get_v2_trim_val(dutz, 0)));
    //testlog.Info("[VOLTAGE TRIM]: V1= {}, V2= {}", (UserRegs.get_v1_trim_val(dut, 0)), (UserRegs.get_v2_trim_val(dut, 0)));
    }
    DUT_LOOP_END
    //this->Info("[Test Item] TB_VHH_Trim_Source -- end");
    }

/**
* Constructor
*/
TB_VHH_Trim_Source::TB_VHH_Trim_Source(TestItemExecuteContext * aContext) : TestItem("TB_VHH_Trim_Source", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_VHH_Trim_Source::~TB_VHH_Trim_Source() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_VHH_Trim_Source::Initialize(TestItemExecuteContext * aContext) {
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
void TB_VHH_Trim_Source::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_VHH_Trim_Source::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_VHH_Trim_Source::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_VHH_Trim_Source::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_VHH_Trim_Source::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_VHH_Trim_Source, TestItemExecuteContext *)

