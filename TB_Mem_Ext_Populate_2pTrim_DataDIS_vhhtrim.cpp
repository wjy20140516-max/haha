#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    std::string Cfg_Filename;
    std::string Populate_Data_File;
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
    //Print("Cycle_Number =%d", Cycle_Number);
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
    //Print("Wait_Dummy =%d", WaitDummy);
    }
    if (theParameters->TryGetParameter("Register_Address", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("Register_Address s= %s", pa.c_str());
    Register_Address = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Register_Address = %d(dec) 0x%04x(hex)   ", Register_Address, Register_Address);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("Solid_Data s= %s", pa.c_str());
    Solid_Data = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = %d(dec) 0x%04x(hex)   ", Solid_Data, Solid_Data);
    }
    Cfg_Filename = "TJ_CFG_DEMO.txt";
    Populate_Data_File = "TJ_CFG_DEMO.txt";
    // AutoMation
    #ifdef RRAM_B2_AUTOMATION
    std::string logName = log_name_setting(aContext, lotnum, wafernum, Die_X, Die_Y, testname);
    #else
    std::string logName =log_name_setting(aContext, TestName);
    #endif
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    // Step1 Load CFG And Compare
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    // Step1 Load CFG And Compare
    //RRAM_TJ::LoadConfigFile(context, Cfg_Filename, testlog, false);
    // Step2 Write T-reg
    TRegWrite(Register_Address, Solid_Data);
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
    if (TReg_ReadData[dut-1] != Solid_Data)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dut-1]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dut]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    // Step3 Write T-Reg
    TRegWrite(0x03, OP_DDW_OFF);
    // Read T-Reg
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dut-1] != OP_DDW_OFF)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut-1]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    //// call DLL Function
    //int size = Page_Length * MBIST_READ_USER_PAGE;
    //std::vector<std::vector<int>> UniqueTrimArray(MAX_DUTS, std::vector<int>(size, 0));
    //std::vector<unsigned int> page_array(size, 0);
    //std::vector<unsigned int> page_array_cpy(size, 0);  // add a copy
    //FileRead(aContext, Populate_Data_File, page_array.data(), size);
    //std::vector<UBMCacheData> buffer{};
    //UBMCacheData UBM_Buffer{};
    //UBM_Buffer.Value.resize(CFG_FILE_LENGTH);
    //UBM_Buffer.Size = CFG_FILE_LENGTH;
    //DUT_LOOP_START
    //int dutid = dutz;
    //string Die_X = (*item)->GetX();
    //string Die_Y = (*item)->GetY();
    //int DieX = std::stoi(Die_X);
    //int DieY = std::stoi(Die_Y);
    ////Print("DUT[%d] Location(%d,%d)", (*item)->GetSysID(), DieX, DieY);
    ////Print("DUT[%d] ArchMnsTFC is %d  ArchPlsTFC is %d", (*item)->GetSysID(), MulDUTArch[dutid].ArchMnsTFC, MulDUTArch[dutid].ArchPlsTFC);
    //page_array_cpy = page_array;
    //TheDevice.Drv_FetMultiTrim(
    //    MulDUTArch[dutid].ArchMnsTFC,
    //    MulDUTArch[dutid].ArchPlsTFC,
    //    DieX,
    //    DieY,
    //    page_array_cpy.data(),
    //    0,
    //    true,
    //    true
    //    );
    //std::vector<unsigned char> page_array_cpy1;
    //page_array_cpy1.reserve(size);
    //for (auto val : page_array_cpy) {
    //    page_array_cpy1.push_back(static_cast<unsigned char>(val & 0xFF));
    //}
    ////Print("[111111]page_array_cpy1:%d %d", page_array_cpy1[11], page_array_cpy1[12]);
    //UserRegs.get_trim_val_update(dutid, 0, page_array_cpy1);
    //UserRegs.set_xreg_target(page_array_cpy1);
    ////Print("[111111]page_array_cpy1:%d %d", page_array_cpy1[11], page_array_cpy1[12]);
    //std::unique_ptr<unsigned char[]> arrayUBM(new unsigned char[size]());
    //for (int i = 0; i < size; i++) {
    //    arrayUBM[i] = static_cast<unsigned char>(page_array_cpy1[i] & 0xFF);
    //    UniqueTrimArray[dutid][i] = static_cast<int>(page_array_cpy1[i]);
    //}
    //UBM_Buffer.DataType = ENUM_D_TYPE;
    //for (int i = 0; i < CFG_FILE_LENGTH; i++) {
    //    if (i < UBM_Buffer.Value.size()) {
    //        UBM_Buffer.Value[i] = arrayUBM[i];
    //    }
    //    else {
    //        Print("Warning: CFG_FILE_LENGTH > UBM_Buffer.Value.size()! i=%d", i);
    //        break;
    //    }
    //}
    //buffer.push_back(UBM_Buffer);
    //UBM_Buffer.Value.clear();
    //DUT_LOOP_END
    //Print("- imported %d bytes memory data from file %s", Page_Length * 128, logName.c_str());
    // call DLL Function
    int size = Page_Length * MBIST_READ_USER_PAGE;
    std::vector<std::vector<int>> UniqueTrimArray(MAX_DUTS, std::vector<int>(size, 0));
    std::vector<unsigned int> page_array(size, 0);
    std::vector<unsigned int> page_array_cpy(size, 0);  // add a copy
    FileRead(aContext, Populate_Data_File, page_array.data(), size);
    //std::vector<UBMBuffer> buffer{};
    //UBMBuffer UBM_Buffer{};
    std::vector<UBMCacheData> buffer{};
    UBMCacheData UBM_Buffer{};
    unsigned int UbmSize = size;
    unsigned int UbmData[16][128] = { 0 };
    Digital.UBM.Config("DI");
    DUT_LOOP_START
    // int dutid = itDUT->GetLocalID();
    // int SYS_DUT = itDUT->GetSysID();
    // #ifdef RRAM_B2_AUTOMATION
    // int DUT_X = itDUT->GetX();
    // int DUT_Y = itDUT->GetY();
    // #else
    // int DUT_X = Die_X  + DUT_Location_X[SYS_DUT];
    // int DUT_Y = Die_Y  + DUT_Location_Y[SYS_DUT%4];
    // #endif
    page_array_cpy = page_array;
    //int dutid = (*item)->GetID();
    int dutid = dutz;
    string Die_X = (*item)->GetX();
    string Die_Y = (*item)->GetY();
    int DieX = std::stoi(Die_X);
    int DieY = std::stoi(Die_Y);
    //Print("DUT[%d] Location(%d,%d)", (*item)->GetSysID(), DieX, DieY);
    //Print("DUT[%d] ArchMnsTFC is %d  ArchPlsTFC is %d", (*item)->GetSysID(), MulDUTArch[dutid].ArchMnsTFC, MulDUTArch[dutid].ArchPlsTFC);
    TheDevice.Drv_FetMultiTrim(
    MulDUTArch[dutid].ArchMnsTFC, /* read_tfbc */
    MulDUTArch[dutid].ArchPlsTFC, /* read_tfbc */
    // DUT_X, /* dut x coordinate */
    // DUT_Y, /* dut y coordinate */
    DieX, /* dut x coordinate */
    DieY, /* dut y coordinate */
    page_array_cpy.data(), /* cfg byte array or ext code array */
    0, /* use DEFAULT value */
    true, /* true: array point to ext_code; false: array point to cfg */
    true /* true: enable location based trim; false: disable location based trim */
    );
    std::vector<unsigned char> page_array_cpy1;
    for (auto val : page_array_cpy)
    page_array_cpy1.push_back(static_cast<unsigned char>(val & 0xFF));
    //Print("[111111]page_array_cpy1:%d %d", page_array_cpy1[11], page_array_cpy1[12]);
    UserRegs.get_trim_val_update(dutid, 0, page_array_cpy1);
    UserRegs.set_xreg_target(page_array_cpy1);
    //Print("[111111]page_array_cpy1:%d %d", page_array_cpy1[11], page_array_cpy1[12]);
    // Write to UBM
    //!!! unsigned char arrayUBM[size];
    for (int i = 0; i < size; i++)
    {
    //arrayUBM[i] = static_cast<unsigned char>(page_array_cpy1[i] & 0xFF);
    UbmData[dut-1][i] = static_cast<int>(page_array_cpy1[i]);
    }
    //UBM_Buffer.data = new unsigned char[size];
    ////memcpy(UBM_Buffer.data, arrayUBM, size);
    //UBM_Buffer.size = size;
    //UBM_Buffer.dutId = dutid;
    //buffer.push_back(UBM_Buffer);
    Digital.UBM.Write(dut, ENUM_D_TYPE, 0, UbmData[dut - 1], UbmSize);
    DUT_LOOP_END
    Print("- imported %d bytes memory data from file %s", Page_Length * 128, logName.c_str());
    //testlog.Info("- imported {} bytes memory data from file {}", Page_Length * 128, logName);
    //!!!!UBM::Write("DI", &buffer);
    // Step4 Ext Write
    Array_result_t error_flag;
    for (int cycle = 0; cycle < Cycle_Number; cycle++)
    {
    for (int page_num = 0; page_num < Page_Length; page_num++)
    {
    MemExtWriteUniqeTrim(Mem_Ext_Write_Page + page_num * 0x80, page_num);
    #ifdef POLLING_DELAY
    usleep(5 * 1000);
    #endif
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
    MemExtReadPopulateData(Mem_Ext_Write_Page, Page_Length * 0x80);
    int Read_Bytes = Page_Length * 128;
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
    All_DUTs_Date[dut-1][j] = Data[j];
    }
    DUT_LOOP_END
    // Data Check and Print
    Data_Compare_Ext_array_XOR_array(true_data_fmt, Read_Bytes, All_DUTs_Date, UniqueTrimArray, error_bfr, &error_flag, TFB_Limit, DFB_Limit, aContext);
    Data_Compare_Ext_print(true_data_fmt, Read_Bytes, All_DUTs_Date, Mem_Ext_Write_Page, &error_flag, aContext);
    }
    }
    // Delete Memory
    //!!!!  for (auto Buf_Release : buffer)
    //!!!!  {
    //!!!!      delete[] Buf_Release.data;
    //!!!!      Buf_Release.data = nullptr;
    //!!!!  }
    //!!!!  std::vector<UBMBuffer>().swap(buffer);
    if (EXT_WRITE_READ)
    {
    DUT_LOOP_START
    if (error_flag.error_flags[dut-1][1] != 1)
    {
    (*item)->SetValue(1);
    TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim_1360[dut-1] = 1;
    }
    DUT_LOOP_END
    }
    //this->Info("[Test Item] TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim -- end");
    }

/**
* Constructor
*/
TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::~TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim, TestItemExecuteContext *)

