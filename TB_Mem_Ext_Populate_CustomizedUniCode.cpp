#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Ext_Populate_CustomizedUniCode.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Ext_Populate_CustomizedUniCode::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    // AC Param
    std::string Cfg_Filename;
    std::string Populate_Data_Filename;
    int Mem_Ext_Write_Page;
    int Page_Length;
    int Cycle_Number;
    int TFB_Limit;
    int DFB_Limit;
    int WaitDummy;
    int Register_Address;
    int Solid_Data;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Page_Length = theParameter->GetValueAsInt();
    //Print("Page_Length =%d", Page_Length);
    }
    if (theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("1st_Page_Addressain s= %s", pa.c_str());
    Mem_Ext_Write_Page = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mem_Ext_Write_Page, Mem_Ext_Write_Page);
    }
    if (theParameters->TryGetParameter("Cycle_Number", theParameter))
    {
    Cycle_Number = theParameter->GetValueAsInt();
    //Print("Cycle_Number = %d ", Cycle_Number);
    }
    if (theParameters->TryGetParameter("TFB_Limit", theParameter))
    {
    TFB_Limit = theParameter->GetValueAsInt();
    //Print("TFB_Limit =%d", TFB_Limit);
    }
    else
    {
    TFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters->TryGetParameter("DFB_Limit", theParameter))
    {
    DFB_Limit = theParameter->GetValueAsInt();
    //Print("DFB_Limit =%d", DFB_Limit);
    }
    else
    {
    TFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters->TryGetParameter("Wait_Dummy", theParameter))
    {
    WaitDummy = theParameter->GetValueAsInt();
    //Print("Wait_Dummy = %d", WaitDummy);
    }
    if (theParameters->TryGetParameter("Register_Address", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    Register_Address = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Register_Address = 0x%04x", Register_Address);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    Solid_Data = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = 0x%04x", Solid_Data);
    }
    Cfg_Filename = "TJ_CFG_DEMO.txt";
    Populate_Data_Filename = "TJ_CFG_DEMO.txt";
    // Step1 import 4-byte code from file
    // AutoMation
    #ifdef RRAM_B2_AUTOMATION
    std::string logName = log_name_setting(aContext, lotnum, wafernum, Die_X, Die_Y, testname);
    #else
    std::string logName = log_name_setting(aContext, TestName);
    #endif
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    int size = 128;
    // std::vector <unsigned int> value(size, 0);
    std::vector<unsigned int> custm4bytes(size, 0);
    // cfg txt to DBM
    string theDBMDataFileName = "TJ_CFG_DEMO.bin";
    Digital.DBM.Write(0, theDBMDataFileName);
    //  DBM to array for compare
    Digital.DBM.Read(0, custm4bytes.data(), size);
    //DUTȡ
    DUT_LOOP_START
    Print("[TRegs_Read] DUT %d Read T-Reg = %02X %02X %02X %02X (Hex)", (*item)->GetSysID(), custm4bytes[0], custm4bytes[1], custm4bytes[2], custm4bytes[3]);
    //testlog.Info("[Read T-Reg] = %02X %02X %02X %02X (Hex)", custm4bytes[0], custm4bytes[1], custm4bytes[2], custm4bytes[3]);
    DUT_LOOP_END
    UINT64 customized_4byte =
    (static_cast<UINT64>(custm4bytes[0] & 0xFF) << 24) |
    (static_cast<UINT64>(custm4bytes[1] & 0xFF) << 16) |
    (static_cast<UINT64>(custm4bytes[2] & 0xFF) << 8) |
    (static_cast<UINT64>(custm4bytes[3] & 0xFF));
    Print("Combined customized_4byte = 0x%08X", customized_4byte);
    // Step2 Load CFG And Compare
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    // Step3 Write T-reg
    TRegWrite(Register_Address, Solid_Data);
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, Register_Address, TReg_ReadData);
    DUT_LOOP_START
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dutz]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dutz]);
    DUT_LOOP_END
    // if (OP_TR_DELAY)
    // {
    //     usleep(100000);
    // }
    // Read T-Reg
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, Register_Address, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dutz] != Solid_Data)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dutz]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dutz]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    unsigned char CpFdsMask;
    int user_fail_bin;
    // Step4 Ext Write
    Array_result_t error_flag;
    for (int cycle = 0; cycle < Cycle_Number; cycle++)
    {
    int writebyte = 0;
    // int UniqueCharArray[MAX_DUTS][512];
    std::vector<std::vector<int>> UniqueCharArray(MAX_DUTS, std::vector<int>(512, 0));
    for (int page_num = 0; page_num < Page_Length; page_num++)
    {
    auto start = std::chrono::high_resolution_clock::now();
    // ETLog::Info("Trigger");
    // sleep(20);
    writebyte = CustomizedUniCode(aContext, lotnum, wafernum, Die_X, Die_Y,customized_4byte, UniqueCharArray, Mem_Ext_Write_Page + page_num * 0x80, page_num);
    DUT_LOOP_START
    if (writebyte == 0)// <RM 2025/07/18: fatal !!!!>
    {
    (*item)->SetValue(1);  // Judge then go to fail bin
    return;
    }
    DUT_LOOP_END
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    Print("Mbist Elapsed Time (sec)%.4f", tm.count() / 1000);
    // Polling Judge
    #ifdef POLLING_BY_JMATCH
    RRAM_TJ::Polling_Judge(theDUTs, POLLING_ONE_TIME_MEMEXT, Polling_Max);
    #else
    //Polling_Soft(aContext, "DO", POLLING_ONE_TIME_MEMEXT, WaitDummy);
    Polling_By_Mloop(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    #endif
    }
    if (EXT_WRITE_READ)
    {
    // Step5 Read Data
    //0Bh-->read data
    // ETLog::Info("Trigger debug2");
    // sleep(15);
    MemExtReadPopulateData(Mem_Ext_Write_Page, Page_Length * 0x40);
    int Read_Bytes = Page_Length * 64;
    // uint Data[Read_Bytes]       = { 0 };
    // int error_bfr[Read_Bytes]   = { 0 };
    std::vector<uint32_t> Data(Read_Bytes, 0);
    std::vector<int> error_bfr(Read_Bytes, 0);
    std::vector<std::vector<int>> All_DUTs_Date(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    // AFM Read
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data.data(), Read_Bytes);
    for (int j = 0; j < Read_Bytes; j++)
    {
    All_DUTs_Date[dutz][j] = Data[j];
    }
    // ETLog::Info("data:{},{},{},{}",All_DUTs_Date[dutz][0],All_DUTs_Date[dutz][1],All_DUTs_Date[dutz][2],All_DUTs_Date[dutz][3]);
    DUT_LOOP_END
    // Data Check and Print
    Data_Compare_Ext_array_XOR_array(true_data_fmt, writebyte, All_DUTs_Date, UniqueCharArray, error_bfr, &error_flag, TFB_Limit, DFB_Limit, aContext);
    Data_Compare_Ext_print(true_data_fmt, Read_Bytes, All_DUTs_Date, Mem_Ext_Write_Page, &error_flag,  aContext);
    }
    }
    if (EXT_WRITE_READ)
    {
    DUT_LOOP_START
    if (error_flag.error_flags[dutz][1] != 1)
    {
    (*item)->SetValue(1);
    TB_Mem_Ext_Populate_CustomizedUniCode_1390[dut-1] = 1;
    }
    else
    {
    (*item)->SetValue(0);
    TB_Mem_Ext_Populate_CustomizedUniCode_1390[dut - 1] = 0;
    }
    DUT_LOOP_END
    }
    // Step4 Write Tregs
    TRegWrite(0xFF, 0x00);
    //this->Info("[Test Item] TB_Mem_Ext_Populate_CustomizedUniCode -- end");
    }

/**
* Constructor
*/
TB_Mem_Ext_Populate_CustomizedUniCode::TB_Mem_Ext_Populate_CustomizedUniCode(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Ext_Populate_CustomizedUniCode", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Ext_Populate_CustomizedUniCode::~TB_Mem_Ext_Populate_CustomizedUniCode() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Ext_Populate_CustomizedUniCode::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Ext_Populate_CustomizedUniCode::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Ext_Populate_CustomizedUniCode::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Ext_Populate_CustomizedUniCode::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Ext_Populate_CustomizedUniCode::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Ext_Populate_CustomizedUniCode::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Ext_Populate_CustomizedUniCode, TestItemExecuteContext *)

