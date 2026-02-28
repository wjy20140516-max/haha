//#include "Common.h"
//#include "interface/ONESCommon.h"
//#include "interface/ONESInterfaceHeader.h"
//#include "interface/TestItem.h"
//#include "interface/TestDomainExecuteContext.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <iostream>
//#include "unistd.h"
//#include <math.h>
//#include <fstream>
//#include <string>
//#include <vector>


#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <stdio.h>
#include <time.h>
#include <dlfcn.h>
using namespace std;

map<string, string> pinchannel;
std::vector<std::string> ctrlPins;
std::vector<std::string> ioPins;
std::vector<std::string> powerPins;


int Data_conversion[DUT_NUM][1000000] = { 0 };
int test_mode_debug_power = 0;
char local_time_s[100] = { 0 };
//========driver

CDriver TheDevice2;
DynamicTrimM5 OlnTrim2;
DynamicUniCode UniCusCOde2;



//**********log print global variable start******************
std::string test_num = "1350";
std::string cp_ver = "Taiji1p8_CP_ProductionFlow_V1p1";
std::string lotnum = "B550064";
std::string wafernum = "B550064-14";
int Die_X = 0;
int Die_Y = 0;
std::string testname;






string start_time_s;
string end_time_s;
int TD = 0;
int g_die_X[16] = { 0 };
int g_die_Y[16] = { 0 };
ResultMap RsltVSS_OS_global;
ResultMap Rslt_VAA_global;
ResultMap Rslt_VHH_global;
bool TB_Power_On_Uninitialized_1010[16] = { false };//0 pass 1/fail
bool TB_Read_Cregs_TestMode_1020[16] = { false };
bool TB_Read_Version_ID_1030[16] = { false };
double TB_IAA_Stanby_1040[16] = { 0 };
bool TB_Load_CRegs_from_File_1050[16] = { false };
double TB_IAA_Stanby_1060[16] = { 0 };
bool TB_VHH_Trim_Source_1070[16] = { false };
bool TB_Mem_Main_Read_vsFFh_DDW_1080[16] = { false };
bool TB_Force_VHH_1090[16] = { false };
bool TB_Mbist_Write_00h_DDW_1100[16] = { false };
bool TB_Mem_Ext_Write_FFh_DDW_1110[16] = { false };
bool TB_Mem_Main_Read_vs00h_DDW_1120[16] = { false };
bool TB_Mbist_Write_FFh_DDW_1130[16] = { false };
bool TB_Mem_Ext_Write_00h_DDW_1140[16] = { false };
bool TB_Mem_Main_Read_vs00h_DDW_1150[16] = { false };
bool TB_Mem_Ext_Write_FF00h_DDW_1160[16] = { false };
bool TB_Mem_Main_Read_vsFFh_DDW_1170[16] = { false };
bool TB_Mbist_Write_FF00h_Cycles_DDW_1180[16] = { false };
bool TB_Mem_Main_Read_vs00h_DDW_1190[16] = { false };
bool TB_Mem_Ext_Write_00FFh_DDW_1200[16] = { false };
bool TB_Mem_Main_Read_vs00h_DDW_1210[16] = { false };
bool TB_Mbist_Write_CKB_DDW_1220[16] = { false };
bool TB_Mem_Main_Read_vsCKB_DDW_1230[16] = { false };
bool TB_Mem_Main_Read_vs00h_DDW_1240[16] = { false };
double  TB_Float_VHH_1250[16] = { 0 };
bool TB_Mbist_Write_InvCKB_DDW_1260[16] = { false };
bool TB_Mem_Main_Read_vsInvCKB_DDW_1270[16] = { false };
bool TB_Mbist_Write_InvCKB_DDW_1280[16] = { false };
bool TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS_1290[16] = { false };
bool TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1300[16] = { false };
bool TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1310[16] = { false };
bool TB_Load_CRegs_from_File_1320[16] = { false };
double TB_Chip_Erase_1330[16] = { 0 };
bool TB_Mem_Ext_Populate_Data_1340[16] = { false };
bool TB_Mem_Ext_Populate_vhhtrim_1350[16] = { false };
bool TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim_1360[16] = { false };
bool TB_Mem_Main_Read_vs00h_DDW_1370[16] = { false };
bool TB_Write_TReg_1380[16] = { false };
bool TB_Mem_Ext_Populate_CustomizedUniCode_1390[16] = { false };
double  TB_Float_VHH_1400[16] = { 0 };
bool TB_Power_Down_1410[16] = { false };
bool TB_Power_On_Initialized_1420[16] = { false };
bool TB_Read_StatusReg1_1430[16] = { false };
bool TB_Read_StatusReg2_1440[16] = { false };
bool TB_Read_SFDP_1450[16] = { false };
bool TB_Read_SecurityRegisters_1460[16] = { false };
bool TB_Read_SecurityRegisters_1470[16] = { false };
bool TB_Read_SecurityRegisters_1480[16] = { false };
bool TB_Read_Manufacturer_ID_1490[16] = { false };
bool TB_Read_Unique_ID_1500[16] = { false };
bool TB_Read_Jedec_ID_1510[16] = { false };
bool TB_Mem_Populate_Data_1520[16] = { false };
double TB_IAA_Stanby_1530[16] = { 0 };

bool TB_Read_Cregs_TestMode_1540[16] = { false };
bool TB_Power_Down_1550[16] = { false };

//**********log print global variable end******************








//TheDevice.init();
//UniCusCOde.init();
//OlnTrim.init();



//CDriver TheDevice;
//unsigned int curr_crs[128] = {
//
//	0x00,0X00,0X00,0X00,  0X00,0x00,0X00,0X00,  0X00,0X00,0X00,0X00,  0x00,0X00,0X00,0X00,
//	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00
//
//};
//
//CDriver::CDriver()
//{
//	char soFilePath[PATH_MAX];
//	//SiteContext* context;
//	std::string soRelatedPath = "CommRes/data/libTaijiRdDynTrimV0.so";
//	//std::string soRelatedPath = "CommRes/build/libNCATest.so";
//	getcwd(soFilePath, sizeof(soFilePath));
//	//std::string soFilePath = context->GetDataFile(soRelatedPath);
//	//cSoFileName = soFilePath;
//	std::string new_path = std::string(soFilePath).substr(0, std::string(soFilePath).find_last_of('/'));
//	cSoFileName = std::string(new_path) +"/" + soRelatedPath;
//	Print("SO PATH : %s", cSoFileName.c_str());
//
//
//	//SiteContext* context;
//	//std::string soRelatedPath = "so/libTaijiRdDynTrimV0.so";
//	//std::string soFilePath = context->GetDataFile(soRelatedPath);
//	//cSoFileName = soFilePath;
//
//
//}
//CDriver::~CDriver()
//{
//	dlclose(hSoInstance);
//
//}
//void CDriver::init()
//{
//	Print("*****************7xxxxxxx*************7");
//	Print("SO PATH : %s", cSoFileName.c_str());
//	hSoInstance = dlopen(cSoFileName.c_str(), RTLD_LAZY);
//	if (hSoInstance == NULL) {
//		const char* err = dlerror();
//		if (err) {
//			std::cerr << "dlopen失败：" << err << std::endl;
//		}
//		else {
//			std::cerr << "dlopen失败，无具体错误信息" << std::endl;
//		}
//		Print("So Open Failed :%s", dlerror());
//	}
//	else {
//		Drv_FetUpdCRs = (DRV_FET)(dlsym(hSoInstance, "TF_GetTaggedCRs"));
//		Drv_FetUpdMemCode = (DRV_FET_DIRC)(dlsym(hSoInstance, "TF_GetTaggedInitCode"));
//		Drv_FetCrsRead = (DRV_FET_RDCRS)(dlsym(hSoInstance, "TF_GetArchUpdCRsArray"));
//		Drv_FetMultiTrim = (DRV_FET_MULTRIM)(dlsym(hSoInstance, "TF_GetArchUpdCRsOrCode"));
//		Print("So Open pass");
//	}
//}
//
//void CDriver::ChangeSO(std::string  cName)
//{
//	cSoFileName = cName;
//
//	dlclose(hSoInstance);
//}
//void CDriver::SetSO(std::string cName)
//{
//	cSoFileName = cName;
//}
//std::string CDriver::GetSO()
//{
//	return cSoFileName;
//}
////==========================================================//

////=====================onlinetrim==============//
//DynamicTrimM5 OlnTrim;
//DynamicUniCode UniCusCOde;
//TF_MRTRIMBUFF  MulSiteArch[MAX_DUTS];
//
//
//DynamicTrimM5::DynamicTrimM5()
//{
//	//SiteContext* context;
//	//std::string soRelatedPath = "so/libTaijiRdDynTrimV0.so";
//	//std::string soFilePath = context->GetDataFile(soRelatedPath);
//	//cDllFileName = soFilePath;
//	char soFilePath[PATH_MAX];
//	string soRelatedPath = "CommRes/data/libCusnUID_V1p2c.so";
//	getcwd(soFilePath, sizeof(soFilePath));
//	string new_path = std::string(soFilePath).substr(0, std::string(soFilePath).find_last_of('/'));
//	cDllFileName = std::string(new_path) + "/" + soRelatedPath;
//}
//
//DynamicTrimM5::~DynamicTrimM5()
//{
//	dlclose(hDllInstance);
//}
//
//void DynamicTrimM5::init()
//{
//	hDllInstance = dlopen(cDllFileName.c_str(), RTLD_LAZY);
//	Print("SO PATH : %s", cDllFileName.c_str());
//
//	Print("*****************8xxxxxxx*************8");
//	// output("<COLOR=Blue>\n ==> open dll hnd : %x  %s  path:\"%s\"</COLOR>", hDllInstance, (hDllInstance)?" ":vFormat("%d", GetLastError()), dll_path.c_str());
//	// if (hDllInstance == NULL) fatal("!!! cannot open DLL file %s!!! ", dll_path.c_str()); ///// M2 logging func
//	if (hDllInstance == NULL)
//	{
//		Print("!!! cannot open DLL file :%s !!!", dlerror());
//	}
//	else
//	{
//		Drv_FetUpdCRs = (DRV_FET)(dlsym(hDllInstance, "TF_GetTaggedCRs"));
//	}
//
//	if (Drv_FetUpdCRs == NULL)
//	{
//		Print("!!! cannot open DLL function of TF_GetTaggedCRs");
//	}
//	else
//	{
//		Drv_FetCrsRead = (DRV_FET_RDCRS)(dlsym(hDllInstance, "TF_GetArchUpdCRsArray"));
//	}
//
//	if (Drv_FetCrsRead == NULL)
//	{
//		Print("!!! cannot open DLL function of TF_GetArchUpdCRsArray");
//	}
//	else
//	{
//		Drv_FetMultiTrim = (DRV_FET_MULTRIM_DBL)(dlsym(hDllInstance, "TF_GetArchUpdCRsOrCode"));
//	}
//	if (Drv_FetMultiTrim == NULL)
//	{
//		Print("!!! cannot open DLL function of TF_GetArchUpdCRsOrCode");
//	}
//}
//
//void DynamicTrimM5::ChangeDLL(std::string  cName)
//{
//	cDllFileName = cName;
//
//	dlclose(hDllInstance);
//}
//void DynamicTrimM5::SetDLL(std::string cName)
//{
//	cDllFileName = cName;
//}
//std::string DynamicTrimM5::GetDLL()
//{
//	return cDllFileName;
//}
//
//
//DynamicUniCode::DynamicUniCode()
//{
//	//SiteContext* context;
//	//std::string soRelatedPath = "so/libCusnUID_V1p2c.so";
//	//std::string soFilePath = context->GetDataFile(soRelatedPath);
//	//cDllFileName = soFilePath;
//	char soFilePath[PATH_MAX];
//	string soRelatedPath = "CommRes/data/libCusnUID_V1p2c.so";
//	getcwd(soFilePath, sizeof(soFilePath));
//	string new_path = std::string(soFilePath).substr(0, std::string(soFilePath).find_last_of('/'));
//	cDllFileName = std::string(new_path) +"/" + soRelatedPath;
//
//
//}
//
//DynamicUniCode::~DynamicUniCode()
//{
//	dlclose(hDllInstance);
//}
//
//void DynamicUniCode::init()
//{
//	// ETLog::Info("path {}", cDllFileName);
//	hDllInstance = dlopen(cDllFileName.c_str(), RTLD_LAZY);
//	// output("<COLOR=Blue>\n ==> open dll hnd : %x  %s  path:\"%s\"</COLOR>", hDllInstance, (hDllInstance) ? " " : vFormat("%d", GetLastError()), dll_path.c_str());
//	if (hDllInstance == NULL)
//	{
//		Print("!!! cannot open DLL file :%s !!!", dlerror());
//	}
//	else
//	{
//		Gen_GetCusUniCode = (UNI_GET_CUSUNICODE)(dlsym(hDllInstance, "RmGetUniCode"));
//	}
//	if (Gen_GetCusUniCode == NULL)
//	{
//		Print("!!! cannot open DLL function of RmGetUniCode");
//	}
//	// else
//	// {
//	// 	ETLog::Info("Gen_GetCusUniCode adress: {}",reinterpret_cast<void*>(Gen_GetCusUniCode));
//	// }
//}
//
//void DynamicUniCode::ChangeDLL(std::string  cName)
//{
//	cDllFileName = cName;
//
//	dlclose(hDllInstance);
//}
//void DynamicUniCode::SetDLL(std::string cName)
//{
//	cDllFileName = cName;
//}
//std::string DynamicUniCode::GetDLL()
//{
//	return cDllFileName;
//}
//
////===========================================================//


//=================================================  DEFINE ==================================================================//

//int Red_cnt_global[10][2] ;
//int Red_addr_global[10][2][16];
//int DUT_LIST_global[10];
int LocalID = 0;
int SysID = 0;
int Fail_data_1[DUT_NUM][1000000] = { 0 };
int Fail_addr_1[DUT_NUM][1000000] = { 0 };
string TestName = "";
string TestNumber = "";
string TestFlow = "";






unsigned int ubm_data[DUT_NUM][96] = { \
0x13, 0x00, 0x00, 0xFF, 0x0F, 0x14, 0x0E, 0x1E, 0x58, 0x7F, 0x10, 0x2F, 0x86, 0x77, 0x18, 0x41,\
0xD0, 0x00, 0x10, 0x09, 0x09, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F,\
0x11, 0x10, 0x12, 0x15, 0x18, 0x19, 0x1A, 0x1B, 0x0C, 0x02, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,\
0xFD, 0x00, 0x47, 0x73, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C,\
0x15, 0x15, 0x15, 0x17, 0x17, 0x17, 0x19, 0x1B, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x07, 0x07,\
0xFF, 0x00, 0x47, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
};

string DeviceName;
string LotNumber;
string WaferId;
string ProberId;
string WaferSlotNumber;

double temp_value[DUT_NUM][10];
MultiTrim MulDUTArch[MAX_DUTS];

int dutx[1000];
int duty[1000];
int device_num[1000];
int bin_num[1000];
int sort_num[1000];

int red_cnt[10][2];
int red_addr[10][2][16];
int rcam_exp_data[64];

int DUT_LIST[11];
//double vdd_value;
//double vdd;
//double vdd_min;
int fail_flag=0;

//string Pin_names[];
int dlog;
int DUTA_MASK = 0xAAAA; //1->mask die, 0->don't know
int DUTB_MASK = 0x5555;
int dutpf[1000000];
int dutpfa[1000000];
string str_pf[1000000];
int CUR_DUT_COUNT = 3;
int CUR_FAIL_MASK = 0x0000;
int CUR_DUT_MASK = 0x0000;
int DUT_MASK = 0x0000;
string PinList = "DO";
char str_results[1024];
char str_results1[1024];
char rdata_temp[12];
int logflag = 3;
int Para_Item = 0;
int flg_jump = 0;
int flg_break = 0;
int FLG_PF[DUT_NUM] = { 0 };
int itfail = 0;
int Fail_data[1000000] = { 0 };
int Fail_data_H[1000000] = { 0 };
int Fail_data_L[1000000] = { 0 };
int Fail_addr[1000000] = { 0 };
char buf[200000];
char cmd[200000];
double  TARGET_V2_MV = DEF_TARGET_V2_MV;



rep_info fail_gbl_info[11][2][16];
//               dut bank container
int fail_gbl_cnt[11][2][2];
double tx_current[11][7];  // dut tx

//void TRegWrite(int CReg_Addr, int CReg_Data)
//{
//	//this->Info(""[CR_WRT] Write C - Reg add{ :02X }h = { :02X }h \r\n", CReg_Addr, CReg_Data");
//	Digital.Pattern.SetRegister(ONES_REG_X1, CReg_Addr);
//	Digital.Pattern.SetRegister(ONES_REG_D1, CReg_Data);
//	Digital.Pattern.RunRegister("pWriteCTrimRegister", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
//	Digital.Pattern.RunModule("pWriteCTrimRegister", "fWriteCTrimRegister", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
//
//}
void TRegWrite(int TReg_Addr, int TReg_Data)
{
	//Print("[TR_WRT] Write T-Reg Addr %02Xh = %02Xh\r\n", TReg_Addr, TReg_Data);
	string PatternName = "pWriteTRegister";
	string FuncName = "fWriteTRegister";
	//double TimeOutValue = 5 MS;
	//bool Include_RegisterInit = true;
	Digital.Pattern.SetRegister(ONES_REG_X1, TReg_Addr); // Register addr
	Digital.Pattern.SetRegister(ONES_REG_D1, TReg_Data); // data
	Digital.Pattern.RunRegister(PatternName, ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule(PatternName, FuncName, ENUM_PATTERNSTOP_INTERRUPT, 5 S);
}

void AFM_READ_Non_cross_VP(int afm_size_num, int addr_start, int DATA, TestItemExecuteContext* aContext)
{
	int k = 0;
	int flag_degbug = 1;
	unsigned int afm_size = afm_size_num;
	//unsigned int afm_size = (afm_size_num * 1024 * 1024) / 32 * 4;
	unsigned int* AFMData = new unsigned int[afm_size]; // 数组索引最大 0xFFFFF
	DUT_LOOP_START
		Digital.AFM.Read(dut, addr_start, AFMData, afm_size);
	int failcounter[DUT_NUM] = { 0 };

	for (int i = 0; i < afm_size; i++)
	{

		//Print("@@@@@ i %d AFM_data=0x%02X",i, AFMData[i]);
		Data_conversion[dut - 1][i] = AFMData[i];
		if (TURN_ON_TR_BIN)
		{
			if (AFMData[i] != DATA)
			{
				failcounter[dut - 1]++;
				Fail_data_1[dut - 1][k] = AFMData[i];
				Fail_addr_1[dut - 1][k] = i;
				FLG_PF[dut - 1] = 1;

			}
		}
		//===============================================================================================================================
		if (1)
		{
			if (i == 0)
			{
				DataLog.Info("");
				Print("---------------------------");
				Print2buff("      ");
				for (int j = 0; j < 16; j++)
				{
					Print2buff("data %-2d   ", j);
				}
				DataLog.Info("");

			}

			if (i % 16 == 0)
			{
				if (flag_degbug)
				{
					Print2buff(" ROW[ %-6d]:", i / 16);
				}
			}
			if (flag_degbug)Print2buff(" 0x%02X", AFMData[i]);//打印wl

			if ((i > 0) && ((i % 16) == 15))
			{
				Print("\n");
				//DataLog.Info("");
			}
		}

	}
	Print("\n");
	if (failcounter[dut - 1] == 0)
	{
		Print("dut[%d]   :    >>>>PASS>>>>> \n", dut);
	}
	else
	{
		if (TURN_ON_TR_BIN)
		{
			Print("dut[%d]   :    >>>>***FAIL**>>>>> F_count[%d]\n", dut, failcounter[dut - 1]);
			for (int n = 0; n < failcounter[dut - 1]; n++)
			{
				if (n < 10)
				{
					//Print("F_Addr[0X%06X]-> F_Data[0X%04X]\n", ((Fail_addr[n])), Fail_data[n]);
					Print("[TR_RD_ERROR] Read T - Reg Add{ :02X }h = { :02X }", 0x03, Fail_data_1[dut - 1][n]);
				}
			}
		}
	}
	delete[]AFMData;
	DUT_LOOP_END

}

void TryGetParameter_AsDouble(string Name, TestExecuteContext* aContext)
{

	TestExecuteParameterCollection* theParameters = aContext->GetParameters();
	TestExecuteParameter* theParameter = nullptr;
	if (theParameters->TryGetParameter(Name, theParameter))
	{
		double Name_value = theParameter->GetValueAsDouble();
		Print(" %s %.2f uA", Name.data(), Name_value);
	}
}

void TRegRead(TestItemExecuteContext* aContext, int TReg_Addr, int* TReg_ReadData)
{

	Digital.Pattern.SetRegister(ONES_REG_D1, 0X00);
	Digital.Pattern.SetRegister(ONES_REG_Z1, TReg_Addr);
	Digital.Pattern.RunRegister("pReadTReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pReadTReg", "fReadTReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);



	//Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);	
	//Digital.AFM.SetResultMode(ENUM_OVERWRITE);
	//Digital.AFM.ResetData(0x01);
	//Digital.Pattern.SetRegister(ONES_REG_Z1, TReg_Addr);
	//Digital.Pattern.RunRegister("pReadTReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	//Digital.Pattern.RunModule("pReadTReg", "fReadTReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);

	int size = 1;
	DUT_LOOP_START
	
	uint Data_TReg[1] = { 0 };
	Digital.AFM.Read(dut, 0, Data_TReg, 1);
	TReg_ReadData[dut-1] = Data_TReg[0];
	//Print("[TR_RD] Read T-Reg Add %02Xh = %02X", TReg_Addr, TReg_ReadData[dut - 1]);
	DUT_LOOP_END
}
void MemMainReadDDW(int Mbist_Read_StartPage, int Mbist_Read_Pages)
{

	string PatternName = "pMemMainRead";
	string FuncName = "fMemMainRead";
	double TimeOutValue = 30 MS;
	//bool Include_RegisterInit = true;
	//0Bh-->read Set data
	Digital.Pattern.SetRegister(ONES_REG_Z1, Mbist_Read_StartPage);
	Digital.Pattern.SetRegister(ONES_REG_LI1, Mbist_Read_Pages);
	Digital.Pattern.RunModule(PatternName, FuncName, ENUM_PATTERNSTOP_INTERRUPT, 100 S);

}

void MemMainReadDDW_All(int comparedata, int Mbist_Read_StartPage, int loop1, int loop2)
{

	
	if (loop1 == 1)
	{
		string PatternName = "pMemMainRead_1PAGE";
		string FuncName = "pMemMainRead_1PAGE";
		Digital.Pattern.SetRegister(ONES_REG_D2, comparedata);
		Digital.Pattern.SetRegister(ONES_REG_ZK, Mbist_Read_StartPage);
		Digital.Pattern.SetRegister(ONES_REG_LI1, loop2-2);//0xC0 192  //Mbist_Page_Bytes    192*2-2
		//Digital.Pattern.SetRegister(ONES_REG_LI2, 0x17E);//384
		Digital.Pattern.RunRegister(PatternName, ENUM_PATTERNSTOP_INTERRUPT, 100 S);
		Digital.Pattern.RunModule(PatternName, FuncName, ENUM_PATTERNSTOP_INTERRUPT, 100 S);
	}
	else
	{
		string PatternName = "pMemMainRead";
		string FuncName = "fMemMainRead";
		Digital.Pattern.SetRegister(ONES_REG_D2, comparedata);
		Digital.Pattern.SetRegister(ONES_REG_ZK, Mbist_Read_StartPage);
		Digital.Pattern.SetRegister(ONES_REG_LI1, (loop1 / 2)-2);//4096    //Mbist_Pages  8192/2  -2
		Digital.Pattern.SetRegister(ONES_REG_LI2, (loop2 * 2)-2);//384     //Mbist_Page_Bytes    192*2-2
		Digital.Pattern.RunRegister(PatternName, ENUM_PATTERNSTOP_INTERRUPT, 1 S);
		Digital.Pattern.RunModule(PatternName, FuncName, ENUM_PATTERNSTOP_INTERRUPT, 100 S);
	}
}


void MemExtWrite(int PageAddr, int Mem_Ext_Write_Data)
{
	Digital.Pattern.SetRegister(ONES_REG_ZK, PageAddr);
	Digital.Pattern.SetRegister(ONES_REG_DK, Mem_Ext_Write_Data);
	Digital.Pattern.RunRegister("pExtWrite_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pExtWrite_NoPolling", "fExtWrite_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 60 S);


}


void EnterTestModeTJ()
{
	Digital.Pattern.RunRegister("pEnterTestModeTJ", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pEnterTestModeTJ", "fEnterTestModeTJ", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Time.Delay(5 MS);
}
int TRegsRead(TestItemExecuteContext* aContext, int TReg_Addr, int* TReg_ReadData)
{
	Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
	Digital.AFM.SetResultMode(ENUM_OVERWRITE);
	Digital.AFM.ResetData(0x11);
	Digital.Pattern.SetRegister(ONES_REG_Z1, TReg_Addr);
	Digital.Pattern.RunRegister("pReadTRegs", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pReadTRegs", "fReadTRegs", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Time.Delay(5 MS);
	uint size = 1;
	//遍历DUT读取数据
	DUT_LOOP_START

		uint Data_TReg[1] = { 0 };
		Digital.AFM.Read(dut, 0, Data_TReg, size);
		TReg_ReadData[dut] = Data_TReg[size - 1];

	DUT_LOOP_END
	return 1;
}

void LoadConfigFile(TestItemExecuteContext* aContext, bool Judge,string ConfigFileName)
{
	DUTList* theDUTArray = aContext->GetDUTs();
	int size = CFG_FILE_LENGTH;
	std::vector <unsigned int> value(size, 0);

	//VI.SetMeasureParameter();

	string theDBMDataFileName = ConfigFileName;//
	//string theDBMDataFileName = "TJ_CFG_DEMO";

	Digital.DBM.Write(0, theDBMDataFileName);

	Digital.DBM.Read(0, value.data(), size);

	std::vector<unsigned char> temp_bytes_container;

	for (auto val : value)
		temp_bytes_container.push_back(static_cast<unsigned char>(val & 0xFF));

	
	std::vector<UBMCacheData> buffer{};

	UBMCacheData UBM_Buffer{};
	Digital.UBM.Config("DI");
		DUT_LOOP_START
		

		unsigned int UbmSize = CFG_FILE_LENGTH;
		unsigned int UbmData[16][96];
		UBM_Buffer.DUTID = dutz;
		UBM_Buffer.Size = UbmSize;

		std::vector<unsigned char> dut_bytes = temp_bytes_container;

		UserRegs.get_trim_val_update(dutz, 0, dut_bytes);
		UserRegs.set_xreg_target(dutz, 0, dut_bytes);/// per dut 
	
		for (int i = 0; i < CFG_FILE_LENGTH; i++)
		{
			UbmData[dut-1][i] = static_cast<unsigned char> (dut_bytes[i]);

			//Print("DBM data 0x%02x", dut_bytes[i]);
		}
		//int x = 0;
		
		//UBM_Buffer.Value = new unsigned int[UbmSize];
	/*	for (int i = 0; i < UbmSize; i++) {
			UBM_Buffer.Value[i] = UbmData[dut - 1][i];
		}
		
		buffer.push_back(UBM_Buffer);*/
		Digital.UBM.Write(dut, ENUM_D_TYPE, 0, UbmData[dut - 1], size);
		DUT_LOOP_END
		
	

		Digital.Pattern.RunRegister("pWriteCfgRegUbm", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
		Digital.Pattern.RunModule("pWriteCfgRegUbm", "fWriteCfgRegUbm", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
		Time.Delay(1 MS);

		//UBM_Buffer.Value.clear;
		
		Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
		Digital.AFM.SetResultMode(ENUM_OVERWRITE);
		Digital.AFM.ResetData(0x11);
		Digital.Pattern.RunRegister("pReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
		Digital.Pattern.RunModule("pReadCfgReg", "fReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
		Time.Delay(1 MS);

		unsigned int Data[96];

		DUT_LOOP_START

			bool result = true;
			Digital.AFM.Read(dut, 0, Data, size);
			int r = 0;
			update_local_time();
			Print("Start_Addr=000000h,Byte Num=96\r\n");
			Print("[CR_RD] \t\t   Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
		
		for (int j = 0; j < 6; j++)
		{
			Print("[CR_RD]Dut %d %06XH-%06XH:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
				dut, r, r + 15, Data[r], Data[r + 1], Data[r + 2], Data[r + 3], Data[r + 4], Data[r + 5], Data[r + 6], Data[r + 7],
				Data[r + 8], Data[r + 9], Data[r + 10], Data[r + 11], Data[r + 12], Data[r + 13], Data[r + 14], Data[r + 15]);

			r = r + 16;
		}
		
		Print(" ");
	
		// compare
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (UserRegs.xreg_target[dut-1][0].byte[i] != (unsigned char)Data[i]) {
				// pirnt fail location
				// ETLog::Info("{:<20d}{:<20d}0x{:<18x}0x{:<18x}", itDUT->GetSysID(), i, value[i], Data[i]);
				// testlog.Info("{:<20d}{:<20d}0x{:<18x}0x{:<18x}", itDUT->GetSysID(), i, value[i], Data[i]);
				result = false;
				count++;
				// break;
			}
		}
		// ETLog::Info("error counts is {}",count);
		//Print("Load register value and read compare:", result);

		if (Judge)
		{
			if (result) {
				(*item)->SetValue(0);
			}
			else {
				(*item)->SetValue(0);
			}
		}
		DUT_LOOP_END

}



//int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, int* get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, UserLog& testlog, UnitContext* context, bool IsEccOut)
//int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, int* get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* context, bool IsEccOut)
//{
//	int ddw_dwfb_cnt = 0;                   // DDW中错误数量
//	int byte_err_cnt = 0;                   // 错误位数量
//	int last_byte = byte_limt;              // 总字节数
//	char buf[500];							// ERR Log
//	std::string output, outBuf;
//	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
//	errflag->err_flags[TFB_LMT_FLAG] = 0;
//	errflag->err_flags[DFB_LMT_FLAG] = 0;
//	DUTList* theDUTs = context->GetActiveDUTs();
//	// Print Info Head 
//#ifdef RRAM_B2_ERR_LOG
//// ETLog::Info("Start_Addr={:04X}00h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
//	testlog.Info("Start_Addr={:06X}h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
//#endif
//	for (auto itDUT : *theDUTs) {
//		int dut = itDUT->GetLocalID();
//		int SysDut = itDUT->GetSysID();
//		int print_error_cnt = 0;
//		int start_page_count = start_page >> 7;
//		errflag->error_cnt[dut] = 0;
//		errflag->max_ddw_dwfb[dut] = 0;
//		ddw_dwfb_cnt = 0;
//		errflag->error_flags[dut][TFB_LMT_FLAG] = 0;
//		errflag->error_flags[dut][DFB_LMT_FLAG] = 0;
//		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
//		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
//		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
//
//#ifdef RRAM_B2_ERR_LOG
//		outBuf = "";		// 按DUT进行打印
//		sprintf(buf, "[MEM_RD][DUT#%d] \t\t  Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17", SysDut);
//		output = buf;
//		outBuf += output;
//#endif
//
//		for (int bytei = 0; bytei < last_byte; ++bytei)
//		{
//			get_error_bit[bytei] = output_array[dut][bytei] ^ target_byte_patt;		//异或运算
//			//位或运算,兼容0F的情况
//			if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
//			{/// e.g. FF FF FF FF FF 0F 
//				get_error_bit[bytei] = (output_array[dut][bytei] ^ target_byte_patt) & 0x0F /*mask of the last byte*/;
//			}
//			byte_err_cnt = 0;
//			for (int biti = 0; biti < 8; ++biti)
//			{
//				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
//			}
//			if (bytei % 6 == 0)
//			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
//				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }  //2025.2.7
//				ddw_dwfb_cnt = 0;
//			}
//
//			// Print ERR Data
//#ifdef RRAM_B2_ERR_LOG
//			print_error_cnt += byte_err_cnt;
//			if (bytei % 24 == 23) {
//				if (print_error_cnt > 0)
//				{
//					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
//						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
//						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
//						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
//					output = buf;
//					outBuf += output;
//
//					if ((bytei % 192 == 191) && (bytei != last_byte - 1))
//					{
//						outBuf += "\n";
//					}
//				}
//				else if ((print_error_cnt == 0) && (bytei == last_byte - 1))
//				{
//					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
//						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
//						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
//						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
//					output = buf;
//					outBuf += output;
//				}
//				print_error_cnt = 0;
//			}
//
//
//			// Print RAW Data
//			// if(bytei % 24 == 23)
//			// {
//			// 	sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", 
//			// 					SysDut, start_page_count,(bytei-23)%192,start_page_count,bytei%192, get_error_bit[bytei-23],get_error_bit[bytei-22],get_error_bit[bytei-21],get_error_bit[bytei-20],get_error_bit[bytei-19],get_error_bit[bytei-18],get_error_bit[bytei-17],get_error_bit[bytei-16],
//			// 					get_error_bit[bytei-15],get_error_bit[bytei-14],get_error_bit[bytei-13],get_error_bit[bytei-12],get_error_bit[bytei-11],get_error_bit[bytei-10],get_error_bit[bytei-9],get_error_bit[bytei-8],get_error_bit[bytei-7],get_error_bit[bytei-6],
//			// 					get_error_bit[bytei-5],get_error_bit[bytei-4],get_error_bit[bytei-3],get_error_bit[bytei-2],get_error_bit[bytei-1],get_error_bit[bytei]);
//			// 	output = buf;
//			// 	outBuf += output;
//			// 	if ((bytei % 192 == 191) && (bytei != last_byte -1))
//			// 	{	
//			// 		outBuf += "\n";
//			// 	}
//			// 	print_error_cnt = 0;	
//			// }
//
//			if ((bytei % 192 == 191) && (bytei > 0))
//			{
//				start_page_count++;
//			}
//#endif
//
//			errflag->error_cnt[dut] += byte_err_cnt;
//			ddw_dwfb_cnt += byte_err_cnt;
//
//			// Do MaxVal Compare after counter increment  2025.2.7
//			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }
//		}
//		if (errflag->error_cnt[dut] > TFB_Limit)
//		{
//			errflag->error_flags[dut][TFB_LMT_FLAG] = -1;
//			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
//		}
//
//		else
//		{
//			errflag->error_flags[dut][TFB_LMT_FLAG] = 1;
//		}
//
//		if (errflag->max_ddw_dwfb[dut] > DFB_Limit)
//		{
//			errflag->error_flags[dut][DFB_LMT_FLAG] = -1;
//			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
//		}
//
//		else
//		{
//			errflag->error_flags[dut][DFB_LMT_FLAG] = 1;
//		}
//		errflag->error_flags[dut][2] = errflag->error_cnt[dut];
//		// Log Print
//#ifdef RRAM_B2_ERR_LOG
//// ETLog::Info(outBuf);
//		testlog.Info(outBuf);
//#endif
//		if (IsEccOut)
//		{
//			ETLog::Info(">>> dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dut], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
//			testlog.Info(">>> dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dut], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
//		}
//	}
//	return 1;
//}
//
//
//
//
//
//
//

//int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, UserLog& testlog, UnitContext* context, bool IsEccOut)
int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数
	char buf[500];							// ERR Log
	std::string output, outBuf;
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;
	//DUTList* theDUTs = context->GetActiveDUTs();
	DUTList* theDUTArray = aContext->GetDUTs();
	// Print Info Head 
#ifdef RRAM_B2_ERR_LOG
    // Print("Start_Addr=%04X00h, Byte Num=%d, >>> Log Errors Only <<<", start_page, byte_limt);
	Print("Start_Addr=%06Xh, Byte Num=%d, >>> Log Errors Only <<<", start_page, byte_limt);
#endif
	//for (auto itDUT : *theDUTs) {

	//	int dut = itDUT->GetLocalID();
	DUT_LOOP_START
		//int SysDut = itDUT->GetSysID();
	  int SysDut = (*item)->GetSysID();


		int print_error_cnt = 0;
		int start_page_count = start_page >> 7;
		errflag->error_cnt[dutz] = 0;
		errflag->max_ddw_dwfb[dutz] = 0;
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dutz][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dutz][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));

#ifdef RRAM_B2_ERR_LOG
		outBuf = "";		// 按DUT进行打印
		sprintf(buf, "[MEM_RD][DUT#%d] \t\t  Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17", SysDut);
		output = buf;
		outBuf += output;
#endif

		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			get_error_bit[bytei] = output_array[dutz][bytei] ^ target_byte_patt;		//异或运算
			//位或运算,兼容0F的情况
			if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
			{/// e.g. FF FF FF FF FF 0F 
				get_error_bit[bytei] = (output_array[dutz][bytei] ^ target_byte_patt) & 0x0F /*mask of the last byte*/;
			}
			byte_err_cnt = 0;
			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}
			if (bytei % 6 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			// Print ERR Data
#ifdef RRAM_B2_ERR_LOG
			print_error_cnt += byte_err_cnt;
			if (bytei % 24 == 23) {
				if (print_error_cnt > 0)
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;

					if ((bytei % 192 == 191) && (bytei != last_byte - 1))
					{
						outBuf += "\n";
					}
				}
				else if ((print_error_cnt == 0) && (bytei == last_byte - 1))
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;
				}
				print_error_cnt = 0;
			}


			// Print RAW Data
			// if(bytei % 24 == 23)
			// {
			// 	sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", 
			// 					SysDut, start_page_count,(bytei-23)%192,start_page_count,bytei%192, get_error_bit[bytei-23],get_error_bit[bytei-22],get_error_bit[bytei-21],get_error_bit[bytei-20],get_error_bit[bytei-19],get_error_bit[bytei-18],get_error_bit[bytei-17],get_error_bit[bytei-16],
			// 					get_error_bit[bytei-15],get_error_bit[bytei-14],get_error_bit[bytei-13],get_error_bit[bytei-12],get_error_bit[bytei-11],get_error_bit[bytei-10],get_error_bit[bytei-9],get_error_bit[bytei-8],get_error_bit[bytei-7],get_error_bit[bytei-6],
			// 					get_error_bit[bytei-5],get_error_bit[bytei-4],get_error_bit[bytei-3],get_error_bit[bytei-2],get_error_bit[bytei-1],get_error_bit[bytei]);
			// 	output = buf;
			// 	outBuf += output;
			// 	if ((bytei % 192 == 191) && (bytei != last_byte -1))
			// 	{	
			// 		outBuf += "\n";
			// 	}
			// 	print_error_cnt = 0;	
			// }

			if ((bytei % 192 == 191) && (bytei > 0))
			{
				start_page_count++;
			}
#endif

			errflag->error_cnt[dutz] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dutz] > TFB_Limit)
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dutz] > DFB_Limit)
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dutz][2] = errflag->error_cnt[dutz];
		// Log Print
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info(outBuf);
		aContext->Info(outBuf);
#endif
		if (IsEccOut)
		{
			Print(">>> dut# %d memory read error count >>> %d >>> TBF: 0x%02x, DBF: 0X%02X", SysDut, errflag->error_cnt[dutz], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			//testlog.Info(">>> dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dutz], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
		}
	DUT_LOOP_END
	return 1;
}


//int Data_Compare_Mbist_array_print_bak(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, UserLog& testlog, UnitContext* context, bool IsEccOut)
int Data_Compare_Mbist_array_print_bak(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数
	char buf[500];							// ERR Log
	std::string output, outBuf;
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;
	//DUTList* theDUTs = context->GetActiveDUTs();
	DUTList* theDUTArray = aContext->GetDUTs();
	// Print Info Head 
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info("Start_Addr={:04X}00h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
	Print("Start_Addr=%06Xh, Byte Num=%d, >>> Log Errors Only <<<", start_page, byte_limt);
#endif
	//for (auto itDUT : *theDUTs) {
		//int dut = itDUT->GetLocalID();
	DUT_LOOP_START
		//int SysDut = itDUT->GetSysID();
	   int SysDut = (*item)->GetSysID();

		int print_error_cnt = 0;
		int start_page_count = start_page >> 7;
		errflag->error_cnt[dut] = 0;
		errflag->max_ddw_dwfb[dut] = 0;
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dut][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dut][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));

#ifdef RRAM_B2_ERR_LOG
		outBuf = "";		// 按DUT进行打印
		sprintf(buf, "[MEM_RD][DUT#%d] \t\t  Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F", SysDut);
		output = buf;
		outBuf += output;
#endif

		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			get_error_bit[bytei] = output_array[dut][bytei] ^ target_byte_patt;		//异或运算
			//位或运算,兼容0F的情况
			if (dataFmt == raw_data_fmt)
			{/// e.g. FF FF FF FF FF 0F 
				get_error_bit[bytei] = (output_array[dut][bytei] ^ target_byte_patt) /*mask of the last byte*/;
			}
			byte_err_cnt = 0;
			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}
			if (bytei % 4 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			// Print ERR Data
#ifdef RRAM_B2_ERR_LOG
			print_error_cnt += byte_err_cnt;
			if (bytei % 16 == 15) {
				if (print_error_cnt > 0)
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
						SysDut, start_page_count, (bytei - 15) % 128, start_page_count, bytei % 128, get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12],
						get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6], get_error_bit[bytei - 5],
						get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;

					if ((bytei % 128 == 127) && (bytei != last_byte - 1))
					{
						outBuf += "\n";
					}
				}
				else if ((print_error_cnt == 0) && (bytei == last_byte - 1))
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
						SysDut, start_page_count, (bytei - 15) % 1128, start_page_count, bytei % 128, get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12],
						get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6], get_error_bit[bytei - 5],
						get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;
				}
				print_error_cnt = 0;
			}


			// Print RAW Data
			// if(bytei % 24 == 23)
			// {
			// 	sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", 
			// 					SysDut, start_page_count,(bytei-23)%192,start_page_count,bytei%192, get_error_bit[bytei-23],get_error_bit[bytei-22],get_error_bit[bytei-21],get_error_bit[bytei-20],get_error_bit[bytei-19],get_error_bit[bytei-18],get_error_bit[bytei-17],get_error_bit[bytei-16],
			// 					get_error_bit[bytei-15],get_error_bit[bytei-14],get_error_bit[bytei-13],get_error_bit[bytei-12],get_error_bit[bytei-11],get_error_bit[bytei-10],get_error_bit[bytei-9],get_error_bit[bytei-8],get_error_bit[bytei-7],get_error_bit[bytei-6],
			// 					get_error_bit[bytei-5],get_error_bit[bytei-4],get_error_bit[bytei-3],get_error_bit[bytei-2],get_error_bit[bytei-1],get_error_bit[bytei]);
			// 	output = buf;
			// 	outBuf += output;
			// 	if ((bytei % 192 == 191) && (bytei != last_byte -1))
			// 	{	
			// 		outBuf += "\n";
			// 	}
			// 	print_error_cnt = 0;	
			// }

			if ((bytei % 128 == 127) && (bytei > 0))
			{
				start_page_count++;
			}
#endif

			errflag->error_cnt[dut] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dut] > TFB_Limit)
		{
			errflag->error_flags[dut][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dut] > DFB_Limit)
		{
			errflag->error_flags[dut][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dut][2] = errflag->error_cnt[dut];
		// Log Print
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info(outBuf);
		aContext->Info(outBuf);
#endif
		if (IsEccOut)
		{
			Print(">>> dut# %d memory read error count >>> %d >>> TBF: 0x%02x, DBF: 0X%02X", SysDut, errflag->error_cnt[dut], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			//testlog.Info(">>> dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dut], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
		}
 DUT_LOOP_END
	return 1;
}



int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, int* get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut)
//int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数
	char buf[500];							// ERR Log
	std::string output, outBuf;
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;
	//DUTList* theDUTs = aContext->GetActiveDUTs();
	DUTList* theDUTArray = aContext->GetDUTs();
	// Print Info Head 
#ifdef RRAM_B2_ERR_LOG
	Print("Start_Addr={:04X}00h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
	//testlog.Info("Start_Addr={:06X}h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
#endif
	//for (auto itDUT : *theDUTs) {
	//	int dut = itDUT->GetLocalID();
	
		DUT_LOOP_START
		//int SysDut = itDUTs->GetSysID();
		//DUT* GetDUTBySysID(int SysDut);
		int SysDut = (*item)->GetSysID();

		int print_error_cnt = 0;
		int start_page_count = start_page >> 7;
		errflag->error_cnt[dut] = 0;
		errflag->max_ddw_dwfb[dut] = 0;
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dut][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dut][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));

#ifdef RRAM_B2_ERR_LOG
		outBuf = "";		// 按DUT进行打印
		sprintf(buf, "[MEM_RD][DUT#%d] \t\t  Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17", SysDut);
		output = buf;
		outBuf += output;
#endif

		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			get_error_bit[bytei] = output_array[dut][bytei] ^ target_byte_patt;		//异或运算
			//位或运算,兼容0F的情况
			if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
			{/// e.g. FF FF FF FF FF 0F 
				get_error_bit[bytei] = (output_array[dut][bytei] ^ target_byte_patt) & 0x0F /*mask of the last byte*/;
			}
			byte_err_cnt = 0;
			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}
			if (bytei % 6 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			// Print ERR Data
#ifdef RRAM_B2_ERR_LOG
			print_error_cnt += byte_err_cnt;
			if (bytei % 24 == 23) {
				if (print_error_cnt > 0)
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;

					if ((bytei % 192 == 191) && (bytei != last_byte - 1))
					{
						outBuf += "\n";
					}
				}
				else if ((print_error_cnt == 0) && (bytei == last_byte - 1))
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;
				}
				print_error_cnt = 0;
			}


			// Print RAW Data
			// if(bytei % 24 == 23)
			// {
			// 	sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", 
			// 					SysDut, start_page_count,(bytei-23)%192,start_page_count,bytei%192, get_error_bit[bytei-23],get_error_bit[bytei-22],get_error_bit[bytei-21],get_error_bit[bytei-20],get_error_bit[bytei-19],get_error_bit[bytei-18],get_error_bit[bytei-17],get_error_bit[bytei-16],
			// 					get_error_bit[bytei-15],get_error_bit[bytei-14],get_error_bit[bytei-13],get_error_bit[bytei-12],get_error_bit[bytei-11],get_error_bit[bytei-10],get_error_bit[bytei-9],get_error_bit[bytei-8],get_error_bit[bytei-7],get_error_bit[bytei-6],
			// 					get_error_bit[bytei-5],get_error_bit[bytei-4],get_error_bit[bytei-3],get_error_bit[bytei-2],get_error_bit[bytei-1],get_error_bit[bytei]);
			// 	output = buf;
			// 	outBuf += output;
			// 	if ((bytei % 192 == 191) && (bytei != last_byte -1))
			// 	{	
			// 		outBuf += "\n";
			// 	}
			// 	print_error_cnt = 0;	
			// }

			if ((bytei % 192 == 191) && (bytei > 0))
			{
				start_page_count++;
			}
#endif

			errflag->error_cnt[dut] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dut] > TFB_Limit)
		{
			errflag->error_flags[dut][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dut] > DFB_Limit)
		{
			errflag->error_flags[dut][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dut][2] = errflag->error_cnt[dut];
		// Log Print
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info(outBuf);
		//testlog.Info(outBuf);
		//Print("%s", outBuf.c_str());
		aContext->Info(outBuf);
#endif
		if (IsEccOut)
		{
			Print(">>> dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dut], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			//testlog.Info(">>> dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dut], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
		}
	DUT_LOOP_END
	return 1;
}

int Data_Compare_CKB_DDW_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量 
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数 
	char buf[500];							// ERR Log
	std::string output, outBuf;
	int opposite = 0xFF;					// CKB Opposite
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;

	//DUTList* theDUTs = context->GetActiveDUTs();
	DUTList* theDUTArray = aContext->GetDUTs();
	// Print Log Head
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info("Start_Addr={:04X}00h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
	Print("Start_Addr=%06Xh, Byte Num=%d, >>> Log Errors Only <<<", start_page, byte_limt);
#endif

	DUT_LOOP_START
		//int SysDut = itDUT->GetSysID();
		int SysDut = (*item)->GetSysID();

		int print_error_cnt = 0;
		int start_page_count = start_page >> 7;
		errflag->error_cnt[dutz] = 0;
		errflag->max_ddw_dwfb[dutz] = 0;                   // DDW中错误数量最大值
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dutz][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dutz][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));

#ifdef RRAM_B2_ERR_LOG
		outBuf = "";		// 按DUT进行打印
		sprintf(buf, "[MEM_RD][DUT#%d] \t\t  Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17", SysDut);
		output = buf;
		outBuf += output;
#endif

		//if (byte_limt > 0x340000) last_byte = 0x340000;  //peddy.ji
		if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;

		// if(target_byte_patt == 0x55 || target_byte_patt == 0xAA)
		// {
		// 	opposite = target_byte_patt ^ 0xFF;
		// }
		// if (target_byte_patt == 0x00)
		// {
		// 	opposite = 0xFF;
		// }
		// else
		// {
		// 	opposite = 0x00;
		// }
		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			// if (bytei % 384 < 192) {
			// 	if (bytei % 12 < 6 ){
			if (bytei % 6 == 5)
			{/// e.g. FF FF FF FF FF 0F 
				get_error_bit[bytei] = (output_array[dutz][bytei] ^ target_byte_patt) & 0x0F /*mask of the last byte*/;
			}
			else
			{
				get_error_bit[bytei] = output_array[dutz][bytei] ^ target_byte_patt;		//异或运算
			}

			// 	}
			// 	else
			// 	{
			// 		if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
			// 		{/// e.g. FF FF FF FF FF 0F 
			// 			get_error_bit[bytei] = (output_array[dutz][bytei] ^ opposite) & 0x0F /*mask of the last byte*/;
			// 		}
			// 		else
			// 		{
			// 			get_error_bit[bytei] = output_array[dutz][bytei] ^ opposite;				//异或运算
			// 		}
			// 	}
			// }
			// else{
			// 	if (bytei % 12 < 6 ){
			// 		if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
			// 		{/// e.g. FF FF FF FF FF 0F 
			// 			get_error_bit[bytei] = (output_array[dutz][bytei] ^ opposite) & 0x0F /*mask of the last byte*/;
			// 		}
			// 		else
			// 		{
			// 			get_error_bit[bytei] = output_array[dutz][bytei] ^ opposite;				//异或运算
			// 		}
			// 	}
			// 	else
			// 	{	
			// 		if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
			// 		{/// e.g. FF FF FF FF FF 0F 
			// 			get_error_bit[bytei] = (output_array[dutz][bytei] ^ target_byte_patt) & 0x0F /*mask of the last byte*/;
			// 		}
			// 		else
			// 		{
			// 			get_error_bit[bytei] = output_array[dutz][bytei] ^ target_byte_patt;		//异或运算
			// 		}
			// 	}
			// }
			byte_err_cnt = 0;
			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}

			if (bytei % 6 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			// Print ERR Data
#ifdef RRAM_B2_ERR_LOG
			print_error_cnt += byte_err_cnt;
			if (bytei % 24 == 23) {
				if (print_error_cnt > 0)
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;

					if ((bytei % 192 == 191) && (bytei != last_byte - 1))
					{
						outBuf += "\n";
					}
				}
				else if ((print_error_cnt == 0) && (bytei == last_byte - 1))
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;
				}
				print_error_cnt = 0;
			}

			// Print RAW Data
			// if(bytei % 24 == 23)
			// {
			// 	sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", 
			// 					SysDut, start_page_count,(bytei-23)%192,start_page_count,bytei%192, get_error_bit[bytei-23],get_error_bit[bytei-22],get_error_bit[bytei-21],get_error_bit[bytei-20],get_error_bit[bytei-19],get_error_bit[bytei-18],get_error_bit[bytei-17],get_error_bit[bytei-16],
			// 					get_error_bit[bytei-15],get_error_bit[bytei-14],get_error_bit[bytei-13],get_error_bit[bytei-12],get_error_bit[bytei-11],get_error_bit[bytei-10],get_error_bit[bytei-9],get_error_bit[bytei-8],get_error_bit[bytei-7],get_error_bit[bytei-6],
			// 					get_error_bit[bytei-5],get_error_bit[bytei-4],get_error_bit[bytei-3],get_error_bit[bytei-2],get_error_bit[bytei-1],get_error_bit[bytei]);
			// 	output = buf;
			// 	outBuf += output;
			// 	if ((bytei % 192 == 191) && (bytei != last_byte -1))
			// 	{
			// 		outBuf += "\n";
			// 	}
			// 	print_error_cnt = 0;	
			// }

			if ((bytei % 192 == 191) && (bytei > 0))
			{
				start_page_count++;
			}
#endif

			errflag->error_cnt[dutz] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dutz] > TFB_Limit)
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dutz] > DFB_Limit)
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dutz][2] = errflag->error_cnt[dutz];
		// Log Print
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info(outBuf);
		//testlog.Info(outBuf);
		//Print("%s", outBuf.c_str());
		aContext->Info(outBuf);
#endif
		if (IsEccOut)
		{
			//ETLog::Info(">>> {} dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", context->GetSiteContext()->GetCurrentUnit()->GetNumber(), SysDut, errflag->error_cnt[dutz], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			// ETLog::Info(">>> dut# {} memory read error count >>> {} @ {:02x}h >>> TBF: 0x{:02x}, DBF: 0X{:02X}",SysDut, errflag->error_cnt[dutz], DAC, errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			Print(">>> dut# %d memory read error count >>> %d >>> TBF: 0x%02x, DBF: 0X%02X", SysDut, errflag->error_cnt[dutz], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
		}
	DUT_LOOP_END
	return 1;
}



int Data_Compare_CKB_DDW_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, int* get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量 
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数 
	char buf[500];							// ERR Log
	std::string output, outBuf;
	int opposite = 0xFF;					// CKB Opposite
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;
	//DUTList* theDUTs = context->GetActiveDUTs();
	DUTList* theDUTArray = aContext->GetDUTs();
	// Print Log Head
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info("Start_Addr={:04X}00h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
	Print("Start_Addr=%06Xh, Byte Num=%d, >>> Log Errors Only <<<", start_page, byte_limt);
#endif

	DUT_LOOP_START
		//int SysDut = itDUT->GetSysID();
		int SysDut = (*item)->GetSysID();
		int print_error_cnt = 0;
		int start_page_count = start_page >> 7;
		errflag->error_cnt[dutz] = 0;
		errflag->max_ddw_dwfb[dutz] = 0;                   // DDW中错误数量最大值
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dutz][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dutz][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));

#ifdef RRAM_B2_ERR_LOG
		outBuf = "";		// 按DUT进行打印
		sprintf(buf, "[MEM_RD][DUT#%d] \t\t  Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17", SysDut);
		output = buf;
		outBuf += output;
#endif

		//if (byte_limt > 0x340000) last_byte = 0x340000;//peddy.ji
		if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			// if (bytei % 384 < 192) {
			// 	if (bytei % 12 < 6 ){
			if (bytei % 6 == 5)
			{/// e.g. FF FF FF FF FF 0F 
				get_error_bit[bytei] = (output_array[dutz][bytei] ^ target_byte_patt) & 0x0F /*mask of the last byte*/;
			}
			else
			{
				get_error_bit[bytei] = output_array[dutz][bytei] ^ target_byte_patt;		//异或运算
			}


			byte_err_cnt = 0;
			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}

			if (bytei % 6 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			// Print ERR Data
#ifdef RRAM_B2_ERR_LOG
			print_error_cnt += byte_err_cnt;
			if (bytei % 24 == 23) {
				if (print_error_cnt > 0)
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;

					if ((bytei % 192 == 191) && (bytei != last_byte - 1))
					{
						outBuf += "\n";
					}
				}
				else if ((print_error_cnt == 0) && (bytei == last_byte - 1))
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, start_page_count, (bytei - 23) % 192, start_page_count, bytei % 192, get_error_bit[bytei - 23], get_error_bit[bytei - 22], get_error_bit[bytei - 21], get_error_bit[bytei - 20], get_error_bit[bytei - 19], get_error_bit[bytei - 18], get_error_bit[bytei - 17], get_error_bit[bytei - 16],
						get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12], get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;
				}
				print_error_cnt = 0;
			}


			if ((bytei % 192 == 191) && (bytei > 0))
			{
				start_page_count++;
			}
#endif

			errflag->error_cnt[dutz] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dutz] > TFB_Limit)
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dutz] > DFB_Limit)
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dutz][2] = errflag->error_cnt[dutz];
		// Log Print
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info(outBuf);
		//testlog.Info(outBuf);
		//Print("%s",outBuf.c_str());
		aContext->Info(outBuf);
#endif
		if (IsEccOut)
		{
			//----getd什么number
			Print(">>> %d dut# %d memory read error count >>> %d >>> TBF: 0x%02x, DBF: 0X%02X", dut, SysDut, errflag->error_cnt[dutz], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			// ETLog::Info(">>> dut# {} memory read error count >>> {} @ {:02x}h >>> TBF: 0x{:02x}, DBF: 0X{:02X}",SysDut, errflag->error_cnt[dutz], DAC, errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			//testlog.Info(">>> dut# {} memory read error count >>> {} >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dutz], errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
		}
	
	DUT_LOOP_END

	return 1;
}


void ReadConfigFileTrim(TestItemExecuteContext* aContext)
{
	DUTList* theDUTArray = aContext->GetDUTs();

	int size = CFG_FILE_LENGTH;

	// // ETLog::Info("Trigger");
	// // sleep(10);

	// read cfg reg
	Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
	Digital.AFM.SetResultMode(ENUM_OVERWRITE);
	Digital.AFM.ResetData(0x11);
	Digital.Pattern.RunRegister("pReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pReadCfgReg", "fReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);


	//Date Read
	uint Data[96] = { 0 };                     //从栈申请空间 数组大小与size一致
	uint offset = 0;                           //需要被读取的数据相对地址
	DUT_LOOP_START
		// Print Each Dut Time
		update_local_time();
		int ip = 0;

		Digital.AFM.Read(dut, offset, Data, size);

		// update to UserRegs.xreg_errmask
		std::vector<unsigned char> fetch_bytes;

		for (int i = 0; i < size; ++i)
		{
			fetch_bytes.push_back(Data[i]);
		}

		UserRegs.get_trim_val_update(dutz, ip, fetch_bytes);
		for (size_t j = 0; j < fetch_bytes.size() && j < XREG_COUNT; ++j)
		{
			UserRegs.xreg_errmask[dutz][ip].byte[j] = fetch_bytes[j];
		}

		// print read data
		int r = 0;
		Print("Start_Addr=000000h,Byte Num=96\r\n");
		Print("[CR_RD] \t\t   Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
		//testlog.Info("Start_Addr=000000h,Byte Num=96\r\n");
		//testlog.Info("[CR_RD] \t\t   Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
		for (int j = 0; j < 6; j++)
		{
			Print("[CR_RD]Dut %d %06XH-%06XH:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",dut, r, r + 15, Data[r], Data[r + 1], Data[r + 2], Data[r + 3], Data[r + 4], Data[r + 5], Data[r + 6], Data[r + 7],Data[r + 8], Data[r + 9], Data[r + 10], Data[r + 11], Data[r + 12], Data[r + 13], Data[r + 14], Data[r + 15]);

			//testlog.Info("[CR_RD]Dut {} {:06X}H-{:06X}H:{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}",itDUT->GetSysID(), r, r + 15, Data[r], Data[r + 1], Data[r + 2], Data[r + 3], Data[r + 4], Data[r + 5], Data[r + 6], Data[r + 7],Data[r + 8], Data[r + 9], Data[r + 10], Data[r + 11], Data[r + 12], Data[r + 13], Data[r + 14], Data[r + 15]);

			r = r + 16;
		}
		//ETLog::Info("");
		Print("");

	DUT_LOOP_END
}

void update_local_time()
{
	// 获取当前系统时间
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// 将当前时间转化为本地时间
	std::tm* localTime = std::localtime(&currentTime);

	// 获取年、月、日、时、分、秒
	int year = localTime->tm_year + 1900;
	int month = localTime->tm_mon + 1;
	int day = localTime->tm_mday;
	int hour = localTime->tm_hour;
	int min = localTime->tm_min;
	int sec = localTime->tm_sec;

	// 输出时间信息
	Print("LOCAL TIME: %d/%d/%d   %02d:%02d:%02d ", year, month, day, hour, min, sec);
	//testlog.Info("LOCAL TIME: {}/{}/{}   {:02}:{:02}:{:02} ", year, month, day, hour, min, sec);

}

void Polling_Soft(TestItemExecuteContext* aContext, const std::string pins, int polling_gap, int WaitDummy)
{

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> tm = end - start;
	int Device_Status_Data[MAX_DUTS] = { 0 };
	std::vector<double> dut_polling_time(MAX_DUTS, 0); // 记录每个DUT的时间
	int dut_polling_count[MAX_DUTS] = { 0 }; // 每个DUT的 polling次数初始化为0
	int polling_time = 0;
	PST.Reset();
	int time_out_cnt;
	while (tm.count() < WaitDummy)
	{
		// Start Polling
		std::string PatternName = "pPolling_Soft";
		std::string FuncName = "fPolling_Soft";
	
		//Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
		//Digital.AFM.SetResultMode(ENUM_OVERWRITE);
		//Digital.AFM.ResetData(0x11);
		Digital.FMM.Clear();
		Digital.FMM.Config(pins, time_out_cnt + 1);

		Digital.Pattern.RunRegister("pPolling_Soft", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
		Digital.Pattern.RunModule("pPolling_Soft", "fPolling_Soft", ENUM_PATTERNSTOP_INTERRUPT, 60 S);
		//Time.Delay(1 MS);
		if (polling_gap > 1.5)  usleep((polling_gap - 1.5) * 1000);
		polling_time++;

		// Read Data
		int Device_Status = 0;
		DUT_LOOP_START
			int size = 1;
			uint Data[1] = { 0 };
			Digital.AFM.Read(dut, 0, Data, size);
			// ETLog::Info("DUT {} Status Register {:02X}", itDUT->GetSysID(),Data[0]);
			Device_Status += Data[0];
			Device_Status_Data[dutz] = Data[0];


			end = std::chrono::high_resolution_clock::now();
			tm = end - start;

			// 更新polling次数
			if (Data[0] == 0)
			{
				if (dut_polling_time[dutz] <= 0)
				{
					dut_polling_time[dutz] = tm.count();
					PST.Polling_Count[dutz] = tm.count(); //记录每个dut的时间
				}
			}
			else
			{
				dut_polling_count[dutz]++;
			}

		DUT_LOOP_END


		if (Device_Status == 0)
		{
			//Print("Total Polling Times is %d", polling_time);
			break;
		}
	}


	if (tm.count() >= WaitDummy)
	{
		DUT_LOOP_START
			if (Device_Status_Data[dutz] != 0)
			{
				//Print("DUT %d Polling Time Out", dut);
				(*item)->SetValue(1);
				dut_polling_time[dutz] = tm.count(); //记录每个dut的时间
				PST.Polling_Count[dutz] = tm.count(); //记录每个dut的时间
			}
		DUT_LOOP_END
	}

	// 打印所有dut的时间点
	DUT_LOOP_START
		//Print("DUT %d Polling Elapsed Time(sec) %.6f", dut, dut_polling_time[dutz] / 1000);
		// testlog.Info("[DUT{}]Polling Elapsed Time (sec){:.6f}", i, dut_polling_time[i]/1000);
	DUT_LOOP_END
}

void Polling_Soft_RND(TestItemExecuteContext* aContext, std::string pins, int polling_gap, int WaitDummy)
{
	
	int resultList[MAX_DUTS] = { 1 };
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> tm = end - start;
	int Device_Status_Data[MAX_DUTS] = { 0 };
	std::vector<double> dut_polling_time(MAX_DUTS, 0); // 记录每个DUT的时间
	int dut_polling_count[MAX_DUTS] = { 0 }; // 每个DUT的 polling次数初始化为0
	int polling_time = 0;
	PST.Reset();
	// DUTRNDFlag.Reset();

	while (tm.count() < WaitDummy)
	{
		// ETLog::Info("TM.COUNT:{}", tm.count()); 
		// Start Polling

		//Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
		//Digital.AFM.SetResultMode(ENUM_OVERWRITE);
		//Digital.AFM.ResetData(0x11);

		Digital.FMM.Clear();
		Digital.FMM.Config(pins);

		Digital.Pattern.RunRegister("pPolling_Soft", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
		Digital.Pattern.RunModule("pPolling_Soft", "fPolling_Soft", ENUM_PATTERNSTOP_INTERRUPT, 7 S);
		
		if (polling_gap > 1.5)  Time.Delay((polling_gap - 1.5) * 1000 MS);
		polling_time++;

		// Read Data
		int Device_Status = 0;
		DUT_LOOP_START
			int size = 1;
			 uint Data[1] = {0};

			//std::vector<uint32_t> Data(size, 0);
			// std::vector<int> error_bfr(Read_Bytes,0);
		

			if (DUTRNDFlag.Flag[dutz])
			{
				Digital.AFM.Read(dut, 0, Data, 1);
				// ETLog::Info("DUT {} Status Register {:02X}", itDUT->GetSysID(),Data[0]);
				Device_Status += Data[0];
				Device_Status_Data[dutz] = Data[0];
				end = std::chrono::high_resolution_clock::now();
				tm = end - start;
			}

			// 更新polling次数
			if (Data[0] == 0)
			{
				if (dut_polling_time[dutz] <= 0)
				{
					dut_polling_time[dutz] = tm.count();
					PST.Polling_Count[dutz] = tm.count(); //记录每个dut的时间
				}
			}
			else
			{
				dut_polling_count[dutz]++;
			}
		DUT_LOOP_END



		if (Device_Status == 0)
		{
			//Print("Total Polling Times is %d", polling_time);
			break;
		}
	}

	if (tm.count() >= WaitDummy)
	{
		DUT_LOOP_START
			
			// if(Device_Status_Data[dutid] != 0)
			// {	
			// 	ETLog::Info("DUT {} Polling Time Out",dutid);
			if (Device_Status_Data[dutz] != 0)
			{
				//Print("DUT %d Polling Time Out", dut);
				(*item)->SetValue(1);
				DUTRNDFlag.Invalidut(dut);
				// RNDFlag.rndFlag =1;
				dut_polling_time[dutz] = tm.count(); //记录每个dut的时间
				PST.Polling_Count[dutz] = tm.count(); //记录每个dut的时间
			}
		DUT_LOOP_END
	}

	// 打印所有dut的时间点
	DUT_LOOP_START
		//Print("DUT %d Polling Elapsed Time(sec) %.6f", dut, dut_polling_time[dutz] / 1000);
		// testlog.Info("[DUT{}]Polling Elapsed Time (sec){:.6f}", i, dut_polling_time[i]/1000);
	DUT_LOOP_END
}

void LoadConfigFileBySo(TestItemExecuteContext* aContext, const std::string fileName, int maxByte, unsigned int* cfgReg, int arch_pt, bool read_oper)
{

	int size = maxByte;
	// Get Data From File
	FileRead(aContext, fileName, cfgReg, size);
	std::vector <unsigned int> cfgRegOriginal(size, 0);
	for (int i = 0; i < size; i++)
	{
		cfgRegOriginal[i] = cfgReg[i];
	}

	// Change cfg By So Fuction
	TheDevice.Drv_FetCrsRead(
		arch_pt, /* user given arch pt: auto table column 21# */
		cfgReg, /* cfg byte array */
		read_oper /* true, DEFAULT value for the first call, for ArchMnsTFC */
		);

	//Print("read :", cfgReg);
	// Write cfg to DBM
	Digital.DBM.Write(0, cfgReg, size);

	// write cfg reg
	//std::string PatternName = "pWriteCfgReg";            //Pattern Name
	//std::string FuncName = "fWriteCfgReg";               //Pattern Fun Name
	//double TimeOutValue = 5 S;                           //Pattern超时终止时间5s
	//bool Include_RegisterInit = true;                    //是否包含寄存器初始化区域的运行 true
	Digital.Pattern.RunModule("pWriteCfgReg", "fWriteCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);

	//// Debug Print
	//DUT_LOOP_START
	//	// // print write data
	//	int w = 0;
	//	//Print("Start_Addr=00h,Bytes Num=96\r\n");
	//	//ETLog::Info("[CFG_From_File]\t\tHex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
	//	for (int j = 0; j < 6; j++)
	//	{
	//		Print("[CFG_From_File] DUT %d %04X-%04X:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
	//			(*item)->GetSysID(), w, w + 15, cfgRegOriginal[w], cfgRegOriginal[w + 1], cfgRegOriginal[w + 2], cfgRegOriginal[w + 3], cfgRegOriginal[w + 4], cfgRegOriginal[w + 5], cfgRegOriginal[w + 6], cfgRegOriginal[w + 7],
	//			cfgRegOriginal[w + 8], cfgRegOriginal[w + 9], cfgRegOriginal[w + 10], cfgRegOriginal[w + 11], cfgRegOriginal[w + 12], cfgRegOriginal[w + 13], cfgRegOriginal[w + 14], cfgRegOriginal[w + 15]);
	//		w = w + 16;
	//	}
	//	//Print("");

	//	// print read data
	//	int r = 0;
	//	//Print("Start_Addr=000000h,Byte Num=96\r\n");
	//	//Print("[CFG_After_So] \t\tHex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
	//	for (int j = 0; j < 6; j++)
	//	{
	//		Print("[CFG_After_So]Dut %d %06XH-%06XH:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
	//			(*item)->GetSysID(), r, r + 15, cfgReg[r], cfgReg[r + 1], cfgReg[r + 2], cfgReg[r + 3], cfgReg[r + 4], cfgReg[r + 5], cfgReg[r + 6], cfgReg[r + 7],
	//			cfgReg[r + 8], cfgReg[r + 9], cfgReg[r + 10], cfgReg[r + 11], cfgReg[r + 12], cfgReg[r + 13], cfgReg[r + 14], cfgReg[r + 15]);
	//		r = r + 16;
	//	}
	//	//Print("");

	//	// // compare
	//	// bool result = true;
	//	// int count = 0;
	//	// for (int i = 0; i < size; i++)
	//	// {   
	//	//     if(cfgRegOriginal[i] != cfgReg[i]){
	//	//         // pirnt fail location
	//	//         // ETLog::Info("{:<20d}{:<20d}0x{:<18x}0x{:<18x}", itDUT->GetSysID(), i, cfgRegOriginal[i], cfgReg[i]);
	//	// 		// testlog.Info("{:<20d}{:<20d}0x{:<18x}0x{:<18x}", itDUT->GetSysID(), i, cfgRegOriginal[i], cfgReg[i]);
	//	// 		result = false; 
	//	//         count ++;
	//	//     }
	//	// }
	//	// // ETLog::Info("error counts is {}",count);
	//	// ETLog::Info(50, "Load register value compare with File and So:", result);
	//DUT_LOOP_END
}

void ReadConfigFile(TestItemExecuteContext* aContext)
{
	

	int size = CFG_FILE_LENGTH;

	// read cfg reg
	//std::string PatternName = "pReadCfgReg";
	//std::string FuncName = "fReadCfgReg";
	//double TimeOutValue = 5 S;
	//bool Include_RegisterInit = true;
	//Pattern::Run(PatternName, FuncName, Include_RegisterInit, InterruptType::INT_ANY, TimeOutValue * 1000 * 1000);
	Digital.Pattern.RunModule("pReadCfgReg", "fReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);


	//Date Read
	uint Data[96] = { 0 };                     //从栈申请空间 数组大小与size一致
	uint offset = 0;                           //需要被读取的数据相对地址
	DUT_LOOP_START
		// Print Each Dut Time
		update_local_time();

		Digital.AFM.Read(dut, offset, Data, size);

		// print read data
		int r = 0;
		Print("Start_Addr=000000h,Byte Num=96\r\n");
		Print("[CR_RD] \t\t   Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
		//testlog.Info("Start_Addr=000000h,Byte Num=96\r\n");
		//testlog.Info("[CR_RD] \t\t   Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
		for (int j = 0; j < 6; j++)
		{
			Print("[CR_RD]Dut %d %06XH-%06XH:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
				(*item)->GetSysID(), r, r + 15, Data[r], Data[r + 1], Data[r + 2], Data[r + 3], Data[r + 4], Data[r + 5], Data[r + 6], Data[r + 7],
				Data[r + 8], Data[r + 9], Data[r + 10], Data[r + 11], Data[r + 12], Data[r + 13], Data[r + 14], Data[r + 15]);

			//testlog.Info("[CR_RD]Dut {} {:06X}H-{:06X}H:{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}",
			//	itDUT->GetSysID(), r, r + 15, Data[r], Data[r + 1], Data[r + 2], Data[r + 3], Data[r + 4], Data[r + 5], Data[r + 6], Data[r + 7],
			//	Data[r + 8], Data[r + 9], Data[r + 10], Data[r + 11], Data[r + 12], Data[r + 13], Data[r + 14], Data[r + 15]);

			r = r + 16;
		}
		Print("");
		//testlog.Info("");

	DUT_LOOP_END
}

void FileRead(TestItemExecuteContext* aContext, const std::string& fileName, unsigned int* value, unsigned long size)

{
	 
	char current_path[PATH_MAX];
	
	std::string filepath = "CommRes/data/"+ fileName;
	//Print("***********8FilePath %s******************", filepath.c_str());
	getcwd(current_path, sizeof(current_path));
	std::string new_path = std::string(current_path).substr(0, std::string(current_path).find_last_of('/'));
	string FilePath = std::string(new_path) +"/" + filepath;
	//Print("***********8FilePath %s******************", FilePath.c_str());


	//char soFilePath[PATH_MAX];
	//string soRelatedPath = "CommRes/data/libCusUIDV1p2d.so";
	//getcwd(soFilePath, sizeof(soFilePath));
	//string new_path = std::string(soFilePath).substr(0, std::string(soFilePath).find_last_of('/'));
	//cDllFileName = std::string(new_path) + "/" + soRelatedPath;




	  std::ifstream inFile(FilePath, std::ios_base::in);
	  if (!inFile.is_open()) {
	  	Print("Error opening %s!", fileName.c_str());
	  	throw "Error opening file!";
	  }
	  else {
	  	std::string line;
	  	unsigned long index = 0;
	  	while (std::getline(inFile, line) && index < size) {
	  		std::istringstream iss(line);
	  		std::string token;
	  		while (iss >> token) {
	  			value[index] = std::stoul(token, nullptr, 16);
	  			index++;
	  		}
	  	}
	  }
	  inFile.close();
	
	  //std::string FilePath = context->GetSiteContext()->GetDataFile(fileName);
	  //std::ifstream inFile(FilePath, std::ios_base::in);
	  //if (!inFile.is_open()) {
		 // ETLog::Error("Error opening {}!", fileName);
		 // throw "Error opening file!";
	  //}
	  //else {
		 // std::string line;
		 // unsigned long index = 0;
		 // while (std::getline(inFile, line) && index < size) {
			//  std::istringstream iss(line);
			//  std::string token;
			//  while (iss >> token) {
			//	  value[index] = std::stoul(token, nullptr, 16);
			//	  index++;
			//  }
		 // }
	  //}
	  //inFile.close();



	//string theDBMDataFileName = "TJ_CFG_DEMO";
	//
	//Digital.DBM.Write(0, theDBMDataFileName);
	//
	//Digital.DBM.Read(0, value, size);
}

int Data_Compare_Ext_array_XOR_array(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, std::vector<unsigned int>& target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;
	//DUTList* theDUTs = context->GetActiveDUTs();
	DUT_LOOP_START
		int print_error_cnt = 0;
		errflag->error_cnt[dut] = 0;
		errflag->max_ddw_dwfb[dut] = 0;
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dut][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dut][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));


		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			get_error_bit[bytei] = output_array[dut][bytei] ^ target_byte_patt[bytei];		//异或运算
			//位或运算,兼容0F的情况
			if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
			{/// e.g. FF FF FF FF FF 0F 
				get_error_bit[bytei] = (output_array[dut][bytei] ^ target_byte_patt[bytei]) & 0x0F /*mask of the last byte*/;
			}
			byte_err_cnt = 0;

			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}
			if (bytei % 6 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			errflag->error_cnt[dut] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut]) { errflag->max_ddw_dwfb[dut] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dut] > TFB_Limit)
		{
			errflag->error_flags[dut][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dut] > DFB_Limit)
		{
			errflag->error_flags[dut][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dut][2] = errflag->error_cnt[dut];
	DUT_LOOP_END
	return 1;
}

int Data_Compare_Ext_array_XOR_array(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, std::vector<std::vector<int>>& UniqueCharArray, std::vector<int>& get_error_bit, Array_result_t* errflag, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;
	//DUTList* theDUTs = context->GetActiveDUTs();
	DUT_LOOP_START
		int print_error_cnt = 0;
		errflag->error_cnt[dutz] = 0;
		errflag->max_ddw_dwfb[dutz] = 0;
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dutz][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dutz][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));


		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			get_error_bit[bytei] = output_array[dutz][bytei] ^ UniqueCharArray[dutz][bytei];		//异或运算
			//位或运算,兼容0F的情况
			if ((dataFmt == raw_data_fmt) && (bytei % 6 == 5))
			{/// e.g. FF FF FF FF FF 0F 
				get_error_bit[bytei] = (output_array[dutz][bytei] ^ UniqueCharArray[dutz][bytei]) & 0x0F /*mask of the last byte*/;
			}
			byte_err_cnt = 0;

			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}
			if (bytei % 6 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			errflag->error_cnt[dutz] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dutz]) { errflag->max_ddw_dwfb[dutz] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dutz] > TFB_Limit)
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dutz] > DFB_Limit)
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dutz][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dutz][2] = errflag->error_cnt[dutz];
	DUT_LOOP_END
	return 1;
}

int Data_Compare_Ext_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int start_page, Array_result_t* errflag, TestItemExecuteContext* aContext)
{
	//DUTList* theDUTs = context->GetActiveDUTs();
	char buf[500];							// ERR Log
	std::string output, outBuf;

	outBuf = "";

	// Print Info Head 
	update_local_time();
	sprintf(buf, "Start_Addr=%06xh,Byte Num=%d", start_page, byte_limt);
	output = buf;
	outBuf += output;
	outBuf += "\n";

	std::string page_ddw = "\n[MEM_RD]                               Hex 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17";
	std::string page_user = "\n[MEM_RD]                               Hex 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F";
	std::string page_maker = page_ddw;
	if (dataFmt == raw_data_fmt)
	{
		page_maker = page_ddw;
	}
	else
	{
		page_maker = page_user;
	}
	outBuf += page_maker;


	DUT_LOOP_START
		// int start_page_count = start_page >> 7;
		// int start_row_count = start_page & 0x7F;
		
		int SysDut = (*item)->GetSysID();
		if (dataFmt == raw_data_fmt)
		{
			for (int bytei = 0; bytei < byte_limt; bytei++)
			{
				int cur_addr = start_page + bytei;
				int start_page_count = cur_addr >> 7;
				int start_row_count = cur_addr & 0x7F;
				// Print RAW Data
				if (bytei % 24 == 23) {
					int row_start_addr = cur_addr - 15;
					int row_start_page = row_start_addr >> 7;
					int row_start_row = row_start_addr & 0x7F;
					sprintf(buf, "\n[MEM_RD][DUT#%d] %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, row_start_page, row_start_row, start_page_count, start_row_count, output_array[dutz][bytei - 23], output_array[dutz][bytei - 22], output_array[dutz][bytei - 21], output_array[dutz][bytei - 20],
						output_array[dutz][bytei - 19], output_array[dutz][bytei - 18], output_array[dutz][bytei - 17], output_array[dutz][bytei - 16], output_array[dutz][bytei - 15], output_array[dutz][bytei - 14],
						output_array[dutz][bytei - 13], output_array[dutz][bytei - 12], output_array[dutz][bytei - 11], output_array[dutz][bytei - 10], output_array[dutz][bytei - 9], output_array[dutz][bytei - 8],
						output_array[dutz][bytei - 7], output_array[dutz][bytei - 6], output_array[dutz][bytei - 5], output_array[dutz][bytei - 4], output_array[dutz][bytei - 3], output_array[dutz][bytei - 2],
						output_array[dutz][bytei - 1], output_array[dutz][bytei]);
					output = buf;
					outBuf += output;
					if ((bytei % 192 == 191) && (bytei != byte_limt - 1))
					{
						start_page_count++;
						outBuf += "\n";


						outBuf += page_maker;

					}

				}

			}
		}
		else
		{
			for (int bytei = 0; bytei < byte_limt; bytei++)
			{
				int cur_addr = start_page + bytei;
				int start_page_count = cur_addr >> 7;
				int start_row_count = cur_addr & 0x7F;
				// Print RAW Data
				if (bytei % 16 == 15) {
					int row_start_addr = cur_addr - 15;
					int row_start_page = row_start_addr >> 7;
					int row_start_row = row_start_addr & 0x7F;
					sprintf(buf, "\n[MEM_RD][DUT#%d] %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
						SysDut, row_start_page, row_start_row, start_page_count, start_row_count, output_array[dutz][bytei - 15], output_array[dutz][bytei - 14],
						output_array[dutz][bytei - 13], output_array[dutz][bytei - 12], output_array[dutz][bytei - 11], output_array[dutz][bytei - 10], output_array[dutz][bytei - 9], output_array[dutz][bytei - 8],
						output_array[dutz][bytei - 7], output_array[dutz][bytei - 6], output_array[dutz][bytei - 5], output_array[dutz][bytei - 4], output_array[dutz][bytei - 3], output_array[dutz][bytei - 2],
						output_array[dutz][bytei - 1], output_array[dutz][bytei]);

					output = buf;
					outBuf += output;
					if ((bytei % 128 == 127) && (bytei != byte_limt - 1))
					{
						start_page_count++;
						outBuf += "\n";


						outBuf += page_maker;

					}
				}

			}
		}

		sprintf(buf, "\n>>> dut# %d memory read error count >>> %d @ %02xh >>> TBF: 0x%02x, DBF: 0X%02X ", SysDut, errflag->error_cnt[dutz], 0, errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
		output = buf;
		outBuf += output;
	DUT_LOOP_END
	// Log Print
	//Print(outBuf);
	//Print("%s", outBuf.c_str());
	aContext->Info(outBuf);
	//testlog.Info(outBuf);
	
	return 1;
}

int CustomizedUniCode(TestItemExecuteContext* aContext, std::string& LotId, std::string& WaferId, int& Die_X, int& Die_Y,  UINT64 customized_4byte, std::vector<std::vector<int>>& UniqueCharArray, int Mem_Ext_Write_Page, int Page_Num)
{
#ifdef RRAM_B2_AUTOMATION
	LotId = context->GetLotId();
	WaferId = context->GetWaferId();
	Die_X = context->GetSiteContext()->GetTouchXCoordinate();
	Die_Y = context->GetSiteContext()->GetTouchYCoordinate();
#else
	LotId = "B550064";
	WaferId = "B550064-14";
	Die_X = 73;
	Die_Y = 304;
	int DUT_Location_X[128] = { 0,30,0,30,0,30,0,30,2,28,2,28,2,28,2,28,4,26,4,26,4,26,4,26,6,24,6,24,6,24,6,24,8,22,8,22,8,22,8,22,10,20,10,20,10,20,10,20,
								12,18,12,18,12,18,12,18,14,16,14,16,14,16,14,16,16,14,16,14,16,14,16,14,18,12,18,12,18,12,18,12,20,10,20,10,20,10,20,10,
								22,8,22,8,22,8,22,8,24,6,24,6,24,6,24,6,26,4,26,4,26,4,26,4,28,2,28,2,28,2,28,2,30,0,30,0,30,0,30,0 };
	int DUT_Location_Y[8] = { 0,-4,4,-8,8,-12,12,-16 };
	// int DUT_Location_X[192] = {0,31,0,31,0,31,1,30,1,30,1,30,2,29,2,29,2,29,3,28,3,28,3,28,4,27,4,27,4,27,5,26,5,26,5,26,6,25,6,25,6,25,7,24,7,24,7,24,8,23,8,23,8,23,9,22,9,22,9,22,
	// 						   10,21,10,21,10,21,11,20,11,20,11,20,12,19,12,19,12,19,13,18,13,18,13,18,14,17,14,17,14,17,15,16,15,16,15,16,16,15,16,15,16,15,17,14,17,14,17,14,
	// 						   18,13,18,13,18,13,19,12,19,12,19,12,20,11,20,11,20,11,21,10,21,10,21,10,22,9,22,9,22,9,23,8,23,8,23,8,24,7,24,7,24,7,25,6,25,6,25,6,26,5,26,5,26,5,
	// 						   27,4,27,4,27,4,28,3,28,3,28,3,29,2,29,2,29,2,30,1,30,1,30,1,31,0,31,0,31,0};
	// int DUT_Location_Y[6]  = {0,-3,3,-6,6,-9};
#endif


	//int theActiveDUTs = aContext->GetActiveDuts();

	// 获取当前系统时间
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// 将当前时间转化为本地时间
	std::tm* localTime = std::localtime(&currentTime);

	// 获取年、月、日、时、分、秒
	int year = localTime->tm_year + 1900;
	int month = localTime->tm_mon + 1;
	int day = localTime->tm_mday;
	int bytenum = 0;
	char buf[64];
	int retrieve_val = 0;
	bool debug_winlog = true;
	std::string window_log;
	UINT64 return_fail_dut_mask = PRESET_NO_DUT_FAIL;
	size_t mem_data_size = 0;

	std::vector <std::vector<int>> duts_target_bytes(MAX_DUTS);
	std::vector<UBMCacheData> buffer{};
	UBMCacheData UBM_Buffer{};
	std::string output, outbuf;
	std::string write_information[64];
	std::string write_information2[64];
	std::string readbuf = "";

	//std::vector <std::vector<int>> duts_target_bytes(MAX_DUTS);
	//std::vector<UBMBuffer> buffer{};
	//UBMBuffer UBM_Buffer{};
	//std::string output, outbuf;
	//std::string write_information[64];
	//std::string write_information2[64];
	//std::string readbuf = "";

	Digital.UBM.Config("DI");



	DUT_LOOP_START
		int SYS_DUT = (*item)->GetSysID();
#ifdef RRAM_B2_AUTOMATION
		int DUT_X = itDUT->GetX();
		int DUT_Y = itDUT->GetY();
#else
		int DUT_X = Die_X + DUT_Location_X[SYS_DUT];
		int DUT_Y = Die_Y + DUT_Location_Y[SYS_DUT % 6];
#endif
		int size = 64;
		std::vector <unsigned int> value(size, 0);

		duts_target_bytes[dutz].push_back( /*0: X_coordinate*/DUT_X); //dut x coordinate
		duts_target_bytes[dutz].push_back( /*1: Y_coordinate*/DUT_Y); //dut y coordinate
		duts_target_bytes[dutz].push_back( /*2: site# on probecard*/SYS_DUT); //dut y coordinate

		Print("waferID:%s,Sel_Taiji:%d,duts_target_bytes:%d %d %d,year:%d, month:%d,day:%d,customized_4byte:%08X,Sel_Magunm:%d",
			WaferId.c_str(), Sel_Taiji, duts_target_bytes[dutz][0], duts_target_bytes[dutz][1], duts_target_bytes[dutz][2], year, month, day, customized_4byte, Sel_Magunm);

		//Print("Gen_GetCusUniCode address: %p", reinterpret_cast<void*>(UniCusCOde.Gen_GetCusUniCode));
		Print("Gen_GetCusUniCode address: %p\n", reinterpret_cast<void*>(UniCusCOde.Gen_GetCusUniCode));
		if (UniCusCOde.Gen_GetCusUniCode == nullptr) {
			Print("ERROR: Gen_GetCusUniCode is nullptr! Dynamic library not loaded.\n");
			return -1; // 终止函数，避免卡死
		}
		// <RM 2025/07/18: change operator
		retrieve_val = UniCusCOde.Gen_GetCusUniCode(
			WaferId.c_str(),
			static_cast<char>(Sel_Taiji),    // <RM 2025/07/18: change operator> 
			duts_target_bytes,// 传指针而非引用
			year,
			month,
			day,
			customized_4byte,
			static_cast<char>(Sel_M5000));

		if (retrieve_val == 1 /*accomplished*/) {
			if (debug_winlog) {
				for (int dut = 0; dut < MAX_DUTS; ++dut) {
					// window_log += vFormat("\ndut[%d]mem_after_dll:", dut);
					// ETLog::Info("dut{} mem_after-dll",dut);
					std::ostringstream hex_stream;
					for (auto elem_code : duts_target_bytes[dutz]) {
						// window_log += vFormat("%02X,", elem_code);
						hex_stream << std::uppercase << std::setw(2) << std::setfill('0')
							<< std::hex << elem_code << ",";

					}
					// ETLog::Info(" hex:{}",hex_stream.str());

					std::ostringstream char_stream;
					for (auto elem_code : duts_target_bytes[dutz]) {
						char_stream << static_cast<char>(elem_code) << ",";
					}
					Print("dut%02d em_after-dll, hex:%s, char:%s", dut, hex_stream.str().c_str(), char_stream.str().c_str());
				}
			}
		}//// no error 
		else {// <RM 2025/07/18: fatal !!!>
			return_fail_dut_mask |= PRESET_ALL_DUT_FAIL;
			Print("OPERATION INTERRUPTED !!!! ERROR CODE: %d", retrieve_val);
			return 0;
		}////  error reported

		//// sync EBM & global buffer target 
		const size_t TARGET_BYTE_LENGTH = 64;
		std::vector<std::vector<unsigned char>> mem_data_container(MAX_DUTS);

		// for (auto itDUT : *theActiveDUTs)
		// {/// only active/enabled DUT will run:
		// 	int dut = itDUT->GetLocalID();;  ///dut per site range: 0~15
		for (auto _value : duts_target_bytes[dutz]) {
			mem_data_container[dutz].push_back(static_cast<unsigned char>(_value));
		}
		// if less than 64 byte，add 0xFF
		if (mem_data_container[dutz].size() < TARGET_BYTE_LENGTH) {
			mem_data_container[dutz].resize(TARGET_BYTE_LENGTH, 0xFF);
		}
		UserRegs.set_xreg_target(dut, 0, mem_data_container[dutz]);
		if (mem_data_container[dutz].size() > mem_data_size)
			mem_data_size = mem_data_container[dutz].size();

		if (debug_winlog) {
			int index = 0;
			std::ostringstream log_stream;
			for (auto dut_rec : mem_data_container)
			{
				// window_log += vFormat("\ndut%d:", index);

				log_stream << "dut" << index << ": ";
				for (auto byte : dut_rec)
				{
					// window_log += vFormat("%02x,", byte);
					log_stream << std::uppercase << std::setw(2) << std::setfill('0')
						<< std::hex << static_cast<int>(byte) << ",";
				}
				log_stream << "\n";
				index++;
			}

			Print("%s", log_stream.str().c_str());

		}


		unsigned int UbmSize = 64;
		unsigned int UbmData[16][64];
		UBM_Buffer.DUTID = dut;
		UBM_Buffer.Size = TARGET_BYTE_LENGTH;
		std::vector<unsigned char> dut_bytes = mem_data_container[dutz];

		for (int i = 0; i < TARGET_BYTE_LENGTH; i++)
		{
			UbmData[dut-1][i] = static_cast<unsigned char> (dut_bytes[i]);
		}
	

		////UBM_Buffer.Value = new unsigned int[UbmSize];
		//for (int i = 0; i < UbmSize; i++) {
		//	UBM_Buffer.Value[i] = UbmData[dut - 1][i];
		//}
		//buffer.push_back(UBM_Buffer);


		Digital.UBM.Write(dut, ENUM_D_TYPE, 0, UbmData[dut-1], UbmSize);


		//const auto& latestBuffer = buffer.back();

		//for (int j = 0; j < TARGET_BYTE_LENGTH; j++)
		//{
		//	UniqueCharArray[dutz][j] = static_cast<int>(latestBuffer.Value[j]);
		//}
		//Print("UniqueCharArray:%02X ", UniqueCharArray[dutz][0]);

	DUT_LOOP_END



	Digital.Pattern.SetRegister(ONES_REG_ZK, Mem_Ext_Write_Page);
	Digital.Pattern.SetRegister(ONES_REG_IB, 0);
	Digital.Pattern.RunRegister("pExtWriteUniqueChar_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pExtWriteUniqueChar_NoPolling", "fExtWriteUniqueChar_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 60 S);
	////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//for (auto Buf_Release : buffer)
	//{
	//	delete[] Buf_Release.data;
	//	Buf_Release.data = nullptr;
	//}
	//std::vector<UBMCacheData>().swap(buffer);

	// ETLog::Info(outbuf);
	// testlog.Info(outbuf);

	return static_cast<int>(mem_data_size);
}

int get_new_voltage_trim_bit(TestItemExecuteContext* aContext, int iteration_counter, unsigned char v2_trim, unsigned char v1_trim, double curr_vh_mv = 0, double curr_vr_mv = 0)
{
	// int want_v1_trim;
	// int want_v2_trim_delta;
	double ForceHighVoltage;

	
	TestExecuteParameterCollection* theParameters = aContext->GetParameters();
	TestExecuteParameter* theParameter = nullptr;

	if (theParameters->TryGetParameter("VHH", theParameter))
	{
		ForceHighVoltage = theParameter->GetValueAsDouble();
		Print("ForceLowVoltage = %.2f V", ForceHighVoltage);
	}
	// double TARGET_V2_MV = ForceHighVoltage;

	Print(" Vhh={:.2f} mV, Vref={:.2f} mV,  Vhh[0x{:02X}], Vref[0x{:02X}], {} ",
		curr_vh_mv, curr_vr_mv, v2_trim, v1_trim, iteration_counter); /// Vref=%.2f mV, curr_vr_mv, 
	if (iteration_counter > TRIM_TIMES)
		return false;

#if (USE_BLUEFIN_INSTRUCTION_SET == 1) 

	int want_v2_trim_delta = round((curr_vh_mv - TARGET_V2_MV * 1000) / INCREMENT_V2_MV);  ///// descending 
	Print("  {} = ({:.2f} - {:.2f}) / {:.3f}  ", want_v2_trim_delta, TARGET_V2_MV * 1000, curr_vh_mv, INCREMENT_V2_MV);

#endif  ////USE_BLUEFIN_INSTRUCTION_SET



	///// use macro instead here:
	if (want_v2_trim_delta + v2_trim > V2_TRIM_MAX)
		want_v2_trim_delta = V2_TRIM_MAX - v2_trim;
	if (want_v2_trim_delta + v2_trim < V2_TRIM_MIN)
		want_v2_trim_delta = V2_TRIM_MIN - v2_trim;


#if  (USE_BLUEFIN_INSTRUCTION_SET == 1)
	int want_v1_trim = round((TARGET_V2_MV * 1000 - curr_vh_mv + INCREMENT_V2_MV * want_v2_trim_delta) / INCREMENT_V1_MV + v1_trim);
	Print(" {} = ({:.2f} - ({:.2f} + {:.2f} * {})) / {:.3f} + {} >",
		want_v1_trim, TARGET_V2_MV * 1000, curr_vh_mv, INCREMENT_V2_MV, want_v2_trim_delta, INCREMENT_V1_MV, v1_trim);
#endif  ////USE_BLUEFIN_INSTRUCTION_SET




	///// use macro instead here:
	if (want_v1_trim > V1_TRIM_MAX)
		want_v1_trim = V1_TRIM_MAX;
	if (want_v1_trim < V1_TRIM_MIN)
		want_v1_trim = V1_TRIM_MIN;


	return (want_v1_trim << BYTE_WIDTH) + (want_v2_trim_delta + v2_trim);

}

unsigned int iterate_ip_voltage_trim(TestItemExecuteContext* aContext, unsigned int dut_pass_mask, int iterate_counter, int ip_inx, double TrimVtarget_mv, USER_REGBFR& reg_buffer)
{
	// Param Set
	double VLimit_High;
	double VLimit_Low;
	int precision = 10;               //ADC采样精度
	int interval = 150;
	int samples = 3;
	double ForceHighVoltage;
	double ForceHighVoltage1;
	double Dvalue = 0xFFFFFF;
	double Dvalue1 = 0x07;
	ResultMap ResultV;

	double POWERPIN[100];

	TestExecuteParameterCollection* theParameters = aContext->GetParameters();
	TestExecuteParameter* theParameter = nullptr;

	if (theParameters->TryGetParameter("VHH", theParameter))
	{
		ForceHighVoltage1 = theParameter->GetValueAsDouble();
		//Print("ForceHighVoltage1 = %.2f V", ForceHighVoltage1);
	}
	if (theParameters->TryGetParameter("VAA", theParameter))
	{
		ForceHighVoltage = theParameter->GetValueAsDouble();
		//Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
	}
	if (theParameters->TryGetParameter("DC_Test_high_limit", theParameter))
	{
		VLimit_High = theParameter->GetValueAsInt();
		//Print("VLimit_High = %d mV", VLimit_High);
	}
	if (theParameters->TryGetParameter("DC_Test_low_limit", theParameter))
	{
		VLimit_Low = theParameter->GetValueAsInt();
		//Print("VLimit_Low = %d mV", VLimit_Low);
	}

	VLimit_High = VLimit_High  MV;
	VLimit_Low = VLimit_Low   MV;

	//Print("[Debug] Force Voltage is: VAA=%.2f V, VHH=%.2f V", ForceHighVoltage, ForceHighVoltage1);

	// double TARGET_V2_MV = ForceHighVoltage1;


	std::vector<unsigned char> v2_trim_temp;
	std::vector<unsigned char> v1_trim_temp;
	std::vector<double> DcMeasVal(MAX_DUTS);
	// bool temp_active_duts[MAX_DUTS]= {0};

	// int get_new_trim_volt;

	// ETLog::Info("[iterate_counter]: {} Times  ", iterate_counter);

	// ETLog::Info("[TARGET_V2_MV]: {} MV  ", TARGET_V2_MV);

	if (iterate_counter == 0)
	{
		TARGET_V2_MV = TrimVtarget_mv;
	}


	//Print("[Volatage trim target]: {} MV  ", TrimVtarget_mv);

	///// ----------------------------
	///// measure volatge
	///// ----------------------------


	// DPS Share
//ifdef DPS_SHARE
//	DUTList* DPS_Share_Group_A = DUTList::Create();
//	DUTList* DPS_Share_Group_B = DUTList::Create();
//
//	for (auto itDUT : *theDUTs)
//	{
//		if (itDUT->GetLocalID() == 2 || itDUT->GetLocalID() == 3 || itDUT->GetLocalID() == 4 || itDUT->GetLocalID() == 5 ||
//			itDUT->GetLocalID() == 8 || itDUT->GetLocalID() == 9 || itDUT->GetLocalID() == 12 || itDUT->GetLocalID() == 13)  DPS_Share_Group_A->Emplace(itDUT);
//		else DPS_Share_Group_B->Emplace(itDUT);
//	}
//
//	// A group / B group measure  
//	if (DPS_Share_Group_A->Size() > 0) {
//		RRAM_TJ::VHH_Trim_Voltages(DPS_Share_Group_A, "VHH", DcMeasVal, VLimit_Low, VLimit_High, testlog);
//		usleep(5 * 1000);
//	}
//
//	if (DPS_Share_Group_B->Size() > 0) {
//		RRAM_TJ::VHH_Trim_Voltages(DPS_Share_Group_B, "VHH", DcMeasVal, VLimit_Low, VLimit_High, testlog);
//		usleep(5 * 1000);
//	}
//
//	site::OutputVoltageToLog(testlog, "VHH_Voltage", "VHH", precision);
//
//	// for(auto itDUT : *theDUTs)
//	// {   
//	//     int result = itDUT->GetResult();
//	//     if(result == 1)
//	//     {
//	//         ResultList[itDUT->GetLocalID()] = result;
//	//     }
//	// }
//
//#else
// VHH OS
	VI.SetPMUMode("VHH", PMU_MVM);
	VI.TurnOn("VHH");
	// Delay 200ms Info From RKW
	Time.Delay(100 MS);

	VI.GetMeasureValue("VHH", ResultV);

	DUT_LOOP_START
		POWERPIN[dut - 1] = ResultV[dutz]["VHH"]*1e3;
	//Print("VHH_Voltage %f ", POWERPIN[dut - 1]);
	if ((VLimit_Low < POWERPIN[dut - 1]) && (POWERPIN[dut - 1] < VLimit_High))
	{
		(*item)->SetValue(0);
	}
	else
	{
		(*item)->SetValue(1);
	}

	DUT_LOOP_END


	DPS_Off("VHH");
	Time.Delay(5 MS);



//#endif

	// delete DPS_Share_Group_A;
	// delete DPS_Share_Group_B;


	// if (iterate_counter >= TRIM_TIMES)
	// 	return dut_pass_mask;

	//Print("[iterate_counter] Start: Number {} Times ", iterate_counter);

	///// ----------------------------
	///// judge 
	///// ----------------------------
	DUT_LOOP_START

		if (abs((DcMeasVal[dutz]) - TARGET_V2_MV) * 1000
			< INCREMENT_V1_MV) {
			reg_buffer.set_v2_trim_val(
				dut,
				ip_inx,
				(reg_buffer.xreg_errmask[dutz][ip_inx].byte[V2_ADDR_INDEX] & (~V2_ADDR_MASK)) >> V2_ADDR_BITSHIFT);  //// regardless of other register within same byte

			reg_buffer.set_v1_trim_val(
				dut,
				ip_inx,
				(reg_buffer.xreg_errmask[dutz][ip_inx].byte[V1_ADDR_INDEX] & (~V1_ADDR_MASK)) >> V1_ADDR_BITSHIFT);  //// regardless of other register within same byte
			//Print("[Judge] DUT[{}], Delta = {} MV", dut, (abs((DcMeasVal[dutz]) - TARGET_V2_MV) * 1000));
			dut_pass_mask &= ~(1ULL << dut);
			//Print("[Judge] dut_pass_mask is {}", dut_pass_mask);

		}    ///// if pass the criteria 
	DUT_LOOP_END   // DUT loop

	///// break if all pass
	if (!dut_pass_mask)
		return dut_pass_mask;

	///// ----------------------------
	///// do trim if fail the criteria 
	///// ----------------------------

	std::vector<UBMCacheData> buffer{};
	UBMCacheData UBM_Buffer{};


	DUT_LOOP_START
		//Print("[BUFFER]: DUT[{}], IP={}, V2=0x{:02X}, V1=0x{:02X}", dut, ip_inx,
			//(reg_buffer.xreg_errmask[dutz][ip_inx].byte[V2_ADDR_INDEX]),
			//(reg_buffer.xreg_errmask[dutz][ip_inx].byte[V1_ADDR_INDEX]));

		int size = 2;
		std::vector<unsigned int> value(size, 0);
		unsigned int UbmSize = 2;
		// unsigned char UbmData[UbmSize];
		UBM_Buffer.DUTID = dut;
		UBM_Buffer.Size = UbmSize;

#if (USE_BLUEFIN_INSTRUCTION_SET == 1) 
		int get_new_trim_volt = get_new_voltage_trim_bit(
			aContext,
			iterate_counter,
			(reg_buffer.xreg_errmask[dutz][ip_inx].byte[V2_ADDR_INDEX] & (~V2_ADDR_MASK)) >> V2_ADDR_BITSHIFT, /// v2 trim
			(reg_buffer.xreg_errmask[dutz][ip_inx].byte[V1_ADDR_INDEX] & (~V1_ADDR_MASK)) >> V1_ADDR_BITSHIFT, /// v1 trim
			DcMeasVal[dutz] / (1 MV)  //// mv
			);

#endif  ////USE_BLUEFIN_INSTRUCTION_SET
		////////////////////
		if (get_new_trim_volt >= 0) {

			v2_trim_temp.clear();
			v1_trim_temp.clear();
			//Print("[New Trim1] : V1={:02X}h, V2={:02X}h  ", ((get_new_trim_volt >> BYTE_WIDTH) & 0xFF), (get_new_trim_volt & 0xFF));

			//// record the trim value of current dut
			v2_trim_temp.push_back(
			((unsigned char)(get_new_trim_volt & 0xFF) << V2_ADDR_BITSHIFT)
				+ (reg_buffer.xreg_errmask[dutz][ip_inx].byte[V2_ADDR_INDEX] & V2_ADDR_MASK));

			//// MUST UPDATE the V2 trim bits into buffer in case the V1 V2 have overlap
			reg_buffer.xreg_errmask[dutz][ip_inx].byte[V2_ADDR_INDEX] = v2_trim_temp[0];

			//// record the trim value of current dut
			v1_trim_temp.push_back(      // 同V2
			(((get_new_trim_volt >> BYTE_WIDTH) & 0xFF) << V1_ADDR_BITSHIFT)
				+ (reg_buffer.xreg_errmask[dutz][ip_inx].byte[V1_ADDR_INDEX] & V1_ADDR_MASK));

			// UserRegs.set_v2_trim_val(dutid,0,(get_new_trim_volt & 0xFF));
			// UserRegs.set_v1_trim_val(dutid,0,((get_new_trim_volt >> BYTE_WIDTH) & 0xFF));

			value.clear();
			value.push_back(v2_trim_temp[0]);
			value.push_back(v1_trim_temp[0]);

			// UbmData[0] = static_cast<unsigned char>(value[0]);
			// UbmData[1] = static_cast<unsigned char>(value[1]);

			//UBM_Buffer.Value = new unsigned char[UbmSize];

			UBM_Buffer.Value[0] = static_cast<unsigned char>(value[0]);
			UBM_Buffer.Value[1] = static_cast<unsigned char>(value[1]);

			// memcpy(UBM_Buffer.data,UbmData,UbmSize);

			//Print("[Trim_Data] UbmData[0]=0x{:2X}, UbmData[1]=0x{:2X}", UBM_Buffer.Value[0], UBM_Buffer.Value[1]);

			buffer.push_back(UBM_Buffer);

		}///// do if the trim value returned is valid

	DUT_LOOP_END

	//!!!!UBM::Write("DI", &buffer);

	

	CRegTrimWrite(V1_ADDR_INDEX, Dvalue1);

	//!!!for (auto Buf_Release : buffer)
	//!!!{
	//!!!	delete[] Buf_Release.data;
	//!!!	Buf_Release.data = nullptr;
	//!!!}
	//!!!std::vector<UBMBuffer>().swap(buffer);

	// Read Config-Register Data
	ReadConfigFileTrim;

	if (iterate_counter >= TRIM_TIMES)
		return dut_pass_mask;

	return iterate_ip_voltage_trim(aContext, dut_pass_mask, iterate_counter + 1, ip_inx, TrimVtarget_mv, reg_buffer);
}


int CRegTrimWrite(int CReg_Addr, int CReg_Data)
{
	//Print("[CR_WRT] Write C-Reg add %02Xh = %02Xh \r\n", CReg_Addr, CReg_Data);
	std::string PatternName = "pWriteCTrimRegister";
	std::string FuncName = "fWriteCTrimRegister";

	Digital.Pattern.SetRegister(ONES_REG_X1, CReg_Addr);
	Digital.Pattern.SetRegister(ONES_REG_D1, CReg_Data);
	Digital.Pattern.RunRegister("pWriteCTrimRegister", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pWriteCTrimRegister", "fWriteCTrimRegister", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	//!!!!!int resultCode = Pattern::Run(PatternName, FuncName, Include_RegisterInit, InterruptType::INT_ANY, TimeOutValue * 1000 * 1000);
	//!!!!!!!
	//return resultCode;
}

void MbistWriteDDW(int Mbist_Write_StartPage, int Mbist_Write_Date)
{
	string PatternName = "pMbistWrite_NoPolling";
	string FuncName = "fMbistWrite_NoPolling";
	Digital.Pattern.SetRegister(ONES_REG_Z1, Mbist_Write_StartPage);
	Digital.Pattern.SetRegister(ONES_REG_DK, Mbist_Write_Date);
	Digital.Pattern.RunRegister(PatternName, ENUM_PATTERNSTOP_INTERRUPT, 1 S);
	Digital.Pattern.RunModule(PatternName, FuncName, ENUM_PATTERNSTOP_INTERRUPT, 100 S);

}

void MbistReadDDW(int Mbist_Read_StartPage, int Mbist_Read_Pages)
{
	string PatternName = "pMbistRead";
	string FuncName = "fMbistRead";
	//0Bh-->read Set data
	Digital.Pattern.SetRegister(ONES_REG_X1, Mbist_Read_StartPage);
	Digital.Pattern.SetRegister(ONES_REG_LI2, Mbist_Read_Pages);
	Digital.Pattern.RunModule(PatternName, FuncName, ENUM_PATTERNSTOP_INTERRUPT, 100 S);
}

void MemExtWritePopulateData(int PageAddr, int Page_Num)
{

	//int PageAddr_l = PageAddr & 0xFF;
	//int	PageAddr_m = PageAddr >> 8 & 0xFF;
	//int	PageAddr_h = PageAddr >> 16 & 0xFF;
	//Digital.Pattern.SetRegister(ONES_REG_D5, PageAddr_l);
	//Digital.Pattern.SetRegister(ONES_REG_D6, PageAddr_m);
	//Digital.Pattern.SetRegister(ONES_REG_D7, PageAddr_l);
	//Digital.Pattern.SetRegister(ONES_REG_Z1, Page_Num * 128);
	//Digital.Pattern.RunRegister("pExtWritePopulate_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	//Digital.Pattern.RunModule("pExtWritePopulate_NoPolling", "fExtWritePopulate_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 60 S);

	Digital.Pattern.SetRegister(ONES_REG_ZK, PageAddr);
	Digital.Pattern.SetRegister(ONES_REG_IB, Page_Num * 128);
	Digital.Pattern.RunRegister("pExtWritePopulate_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pExtWritePopulate_NoPolling", "fExtWritePopulate_NoPolling", ENUM_PATTERNSTOP_INTERRUPT, 1 S);



}

void MemExtReadPopulateData(int PageAddr, int PageLength)
{

	//int PageAddr_l = PageAddr & 0xFF;
	//int	PageAddr_m = PageAddr >> 8 & 0xFF;
	//int	PageAddr_h = PageAddr >> 16 & 0xFF;
	//Digital.Pattern.SetRegister(ONES_REG_D5, PageAddr_l);
	//Digital.Pattern.SetRegister(ONES_REG_D6, PageAddr_m);
	//Digital.Pattern.SetRegister(ONES_REG_D7, PageAddr_l);
	//int LOOP_Cycle = PageLength - 2;
	//Digital.Pattern.SetRegister(ONES_REG_R1, LOOP_Cycle);
	//Digital.Pattern.RunRegister("pExtReadPopulate", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	//Digital.Pattern.RunModule("pExtReadPopulate", "fExtReadPopulate", ENUM_PATTERNSTOP_INTERRUPT, 60 S);

	Digital.Pattern.SetRegister(ONES_REG_ZK, PageAddr);
	Digital.Pattern.SetRegister(ONES_REG_LI1, PageLength-2);
	Digital.Pattern.RunRegister("pExtReadPopulate", ENUM_PATTERNSTOP_INTERRUPT, 1 S);
	Digital.Pattern.RunModule("pExtReadPopulate", "fExtReadPopulate", ENUM_PATTERNSTOP_INTERRUPT, 10 S);


}

void MemExtWriteUniqeTrim(int PageAddr, int Page_Num)
{	

	//int DValue = 0xFFFFFF;
	//if (Page_Num > 0)
	//{
	//	DValue = Page_Num * 128 * 8 - 1;
	//}
	////Pattern::WriteRegister(REG_Y1, PageAddr);
	////Pattern::WriteRegister(REG_D1, DValue);
	////Pattern::Run(PatternName, FuncName, Include_RegisterInit, InterruptType::INT_ANY, TimeOutValue * 1000 * 1000);
	//Digital.Pattern.SetRegister(ONES_REG_ZK, PageAddr);
	//Digital.Pattern.SetRegister(ONES_REG_D1, DValue);
	//Digital.Pattern.RunRegister("pExtWriteUniqueTrim", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	//Digital.Pattern.RunModule("pExtWriteUniqueTrim", "fExtWriteUniqueTrim", ENUM_PATTERNSTOP_INTERRUPT, 60 S);



	Digital.Pattern.SetRegister(ONES_REG_ZK, PageAddr);
	Digital.Pattern.SetRegister(ONES_REG_IB, Page_Num * 128);
	Digital.Pattern.RunRegister("pExtWriteUniqueTrim", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pExtWriteUniqueTrim", "fExtWriteUniqueTrim", ENUM_PATTERNSTOP_INTERRUPT, 60 S);





}





long str2int_convt(string input_str)
{
	char* str;
	if ((input_str.find("X") != input_str.npos) | (input_str.find("x") != input_str.npos)) // check if is HEX string
	{
		return strtol(input_str.c_str(), &str, 16);
	}
	else return strtol(input_str.c_str(), &str, 10);
}

void Print(const char* format, ...)
{
	int  vasprintf(char** result, char const* format, va_list args);
	va_list ap;
	va_start(ap, format);
	char* buf_ = NULL;
	vasprintf(&buf_, format, ap);
	//fprintf(stdout, "%s", buf_);
	//fflush(stdout);
	DataLog.Info(buf_);
	free(buf_);
	va_end(ap);
}


rndFlag RNDFlag;          
DUTListFlag DUTRNDFlag;
TABLE_VAR TableVar;
PollingTime_Count PST;
USER_REGBFR UserRegs;





//#include <stdio.h>
//#include <stdarg.h>
//#include <stdlib.h>

//void Print(const char* format, ...)
//{
//	va_list ap;
//	va_start(ap, format);
//
//	char* buf_ = NULL;
//	// 使用 vasprintf 格式化字符串
//	int len = vasprintf(&buf_, format, ap);
//
//	if (len == -1) {
//		// 如果 vasprintf 失败，返回，避免使用空指针
//		perror("vasprintf failed");
//		va_end(ap);
//		return;
//	}
//
//	// 打印到日志或其他处理逻辑
//	DataLog.Info(buf_);
//
//	// 释放内存
//	free(buf_);
//
//	va_end(ap);
//}

//void dc_print(string testname, string pinname, ResultMap doublem, double hlimit, double llimit, string unit, double multiple = 1, int flag = 1, TestItemExecuteContext* aContext)
void dc_print(string testname, string pinname, ResultMap doublem, double hlimit, double llimit, string unit,TestItemExecuteContext* aContext)
{
	string shlimit = "N/A", sllimit = "N/A", smeasV = "";
	string shlimit_unit = unit, sllimit_unit = unit, smeasV_unit = unit;
	if (1)
	{
		sprintf(buf, "%.3f", hlimit);
		shlimit = buf;
		sprintf(buf, "%.3f", llimit);
		sllimit = buf;
	}


	//string channel = "CHN";
	string pinlist[100];
	int len_pinlist = 0;
	len_pinlist = get_pin_list(pinname, pinlist);
	Print(" DUT    TestName		Pin Channel				Low			 Measured		 High      Unit     P/F");
	int flagpf = 0;
	DUT_LOOP_START
		if ((*item)->IsEnable())
		{
			for (int ipin = 0; ipin < len_pinlist; ipin++)
			{
				double measV = doublem[dut][pinlist[ipin]];
				string pinname = pinlist[ipin];
				string strpf = "P";
				//if (flag_hl)
				{
					if ((measV < hlimit) && (measV > llimit))
					{

					}
					else
					{
						strpf = "F";
						DUT_FAIL;
						flagpf = flagpf | 1;
						FLG_PF[dut - 1] = 1;
					}
				}
				sprintf(buf, "%.3f", measV );
				smeasV = buf;
				//Print("%2d     %-20s %15s %-10s      %16s %2s           %16s %2s       %16s %2s       %4s",  dut, testname.data(), pinname.data(), pinchannel[pinlist[ipin]].data(), sllimit.data(), sllimit_unit.data(), smeasV.data(), unit.data(), shlimit.data(), shlimit_unit.data(), strpf.data());
				Print("%2d     %-20s %15s %-10s     %16s            %16s        %16s      %2s   %4s",  dut, testname.data(), pinname.data(), pinchannel[pinlist[ipin]].data(), sllimit.data(),  smeasV.data(),  shlimit.data(), unit.data(), strpf.data());
			}
		}
	DUT_LOOP_END

}
int get_pin_list(string pinlists, string* pinlist)
{
	int pin_count = 0;
	PMUModeMap PMUModeMap;
	VI.GetPMUMode(pinlists, PMUModeMap);
	int i = 0;
	//Print("\nGET %s LIST:", pinlists.data());
	for (auto iter = PMUModeMap.begin(); iter != PMUModeMap.end(); iter++)
	{
		int dutid = iter->first;
		auto pinmode = iter->second;
		int pin_size = pinmode.size();
		//Print("[%2d]", pin_size);
		for (auto iter = pinmode.begin(); iter != pinmode.end(); iter++)
		{
			string pinname = iter->first;
			PMU_MODE_E pmumode = iter->second;
			//Print("%s ", pinname.data());
			pinlist[i] = pinname;
			pin_count++;
			i++;
		}
		break;
	}
	Print("");
	return pin_count;
}


void AFM_CONFIG_SET(string pins, int x, int y, TestItemExecuteContext* aContext)
{
	Digital.AFM.Clear();
	Digital.AFM.Config(x, y, pins, ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
	Digital.AFM.SetResultMode(ENUM_OVERWRITE);
	Digital.AFM.ResetData(0x99);
}
void AFM_CONFIG_SET_keep_default(string pins, int x, int y, TestItemExecuteContext* aContext)
{
	Digital.Pattern.Reset();
	unsigned int* theRegValue = new unsigned int[1];
	theRegValue[0] = 0xFFFF;
	Digital.Pattern.SetRegister(ONES_REG_DMAX, theRegValue, 1);
	Digital.Pattern.SetRegister(ONES_REG_SDMAX, theRegValue, 1);
	Digital.AFM.Clear();
	Digital.AFM.Config(x, y, pins, ENUM_DATA_WIDTH_BIT_SPAN_VP_16, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
	Digital.AFM.SetResultMode(ENUM_KEEPFAIL_DEFAULT); //ENUM_OVERWRITE | ENUM_KEEPFAIL_DEFAULT
	Digital.AFM.ResetDataSpanVP(0X0000);
}
void AFM_CONFIG_SET_OSCILLATOR(string pins, int x, int y, TestItemExecuteContext* aContext)
{
	Digital.AFM.Clear();
	Digital.AFM.Config(x, y, pins, ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
	Digital.AFM.SetResultMode(ENUM_OVERWRITE); //ENUM_OVERWRITE | ENUM_KEEPFAIL_DEFAULT
	Digital.AFM.ResetData(0X00);
}
void MARCH_WRITE_PATTERN( string pat_name, string module_name, int write_addr, int write_data, int blk_num, TestItemExecuteContext* aContext)
{
	//Print("pat_name=%s\n", pat_name.data());
	//Print("module_name=%s\n", module_name.data());
	//Print("write_addr=%d\n", write_addr);
	//Print("write_data=%d\n", write_data);
	Digital.Pattern.SetRegister(ONES_REG_X2, write_addr);// DATAIN
	Digital.Pattern.SetRegister(ONES_REG_YB, blk_num);// DATAIN
	Digital.Pattern.SetRegister(ONES_REG_DK, write_data);// DATAIN
	Digital.Pattern.RunModule(pat_name, module_name, ENUM_PATTERNSTOP_INTERRUPT, 20 S);
}
void MARCH_READ_PATTERN(string pat_name, string module_name, int read_addr, int read_data, int blk_num, TestItemExecuteContext* aContext)
{
	//Print("pat_name=%s\n", pat_name.data());
	//Print("module_name=%s\n", module_name.data());
	//Print("read_addr=%d\n", read_addr);
	//Print("read_data=%d\n", read_data);
	Digital.Pattern.SetRegister(ONES_REG_X1, read_addr);// DATAIN
	Digital.Pattern.SetRegister(ONES_REG_YB, blk_num);// DATAIN
	Digital.Pattern.SetRegister(ONES_REG_SDK, read_data);// DATAIN
	Digital.Pattern.RunModule(pat_name, module_name, ENUM_PATTERNSTOP_INTERRUPT, 20 S);
}

void power_up_level()
{

	PMU_DigitalSet("CtrlPins", 1.2 V, 0 V, 0.6 V, 0.6 V);

	DPS_FV("VDDC", 1.2 V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
	DPS_FV("VDDP1", 1.2 V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
	DPS_FV("VDDP3", 1.2 V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
	DPS_FV("VDDP4", 1.2 V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
}
void power_up_level_set(double val)
{
	Print(" Power_Voltage =	%.3f\n", val);
	PMU_DigitalSet("CtrlPins", val V, 0 V, val/2 V, val/2 V);

	DPS_FV("VDDC", val V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
	DPS_FV("VDDP1", val V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
	DPS_FV("VDDP3", val V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
	DPS_FV("VDDP4", val V, 50 MA, 50 MA, -10 MA, ENUM_SENSE_REMOTE);
	Time.Delay(5 MS);
}

void March_pgm(int block_num, char up_down, int data_W, TestItemExecuteContext* aContext)
{
	int block_byte = 8192;
	int data_R = 0x0000;
	switch (up_down)
	{
		case 'u':
			//blok地址从低到高pgm
			Digital.Pattern.SetRegister(ONES_REG_LI6, block_byte - 2);
			Digital.Pattern.SetRegister(ONES_REG_YC, block_num);
			Digital.Pattern.SetRegister(ONES_REG_XC, block_num<<13);
			Digital.Pattern.SetRegister(ONES_REG_DB, data_W);
			Digital.Pattern.SetRegister(ONES_REG_SDB, data_R);
			Digital.Pattern.RunModule("march_write", "march_write_up", ENUM_PATTERNSTOP_INTERRUPT, 20 S);
			break;
		case 'd':
			//block地址从高到低pgm
			Digital.Pattern.SetRegister(ONES_REG_LI6, block_byte - 2);
			Digital.Pattern.SetRegister(ONES_REG_YC, block_num);
			Digital.Pattern.SetRegister(ONES_REG_XC, block_num << 13);
			Digital.Pattern.SetRegister(ONES_REG_DB, data_W);
			Digital.Pattern.SetRegister(ONES_REG_SDB, data_R);
			Digital.Pattern.RunModule("march_write", "march_write_down", ENUM_PATTERNSTOP_INTERRUPT, 20 S);
			break;
		default:
			break;
	}


}
void March_read(int block_num, char up_down, int data_R, TestItemExecuteContext* aContext)
{
	int block_byte = 8192;
	int data_W = 0x0000;
	switch (up_down)
	{
		case 'u':
			//blok地址从低到高pgm
			Digital.Pattern.SetRegister(ONES_REG_LI6, block_byte - 2);
			Digital.Pattern.SetRegister(ONES_REG_YC, block_num);
			Digital.Pattern.SetRegister(ONES_REG_XC, block_num << 13);
			Digital.Pattern.SetRegister(ONES_REG_DB, data_W);
			Digital.Pattern.SetRegister(ONES_REG_SDB, data_R);
			Digital.Pattern.RunModule("march_read", "march_read_up", ENUM_PATTERNSTOP_INTERRUPT, 20 S);
			break;
		case 'd':
			//block地址从高到低pgm
			Digital.Pattern.SetRegister(ONES_REG_LI6, block_byte - 2);
			Digital.Pattern.SetRegister(ONES_REG_YC, block_num);
			Digital.Pattern.SetRegister(ONES_REG_XC, block_num << 13);
			Digital.Pattern.SetRegister(ONES_REG_DB, data_W);
			Digital.Pattern.SetRegister(ONES_REG_SDB, data_R);
			Digital.Pattern.RunModule("march_read", "march_read_down", ENUM_PATTERNSTOP_INTERRUPT, 20 S);
			break;
		default:
			break;
		}
}
void AFM_READ_CHECK(int block_num,int afm_size_num, int addr_start, TestItemExecuteContext* aContext)
{
	int k = 0;
	int flag_degbug = 1;
	unsigned int afm_size = afm_size_num * 4;
	//unsigned int afm_size = (afm_size_num * 1024 * 1024) / 32 * 4;
	unsigned int* AFMData = new unsigned int[afm_size]; // 数组索引最大 0xFFFFF
	DUT_LOOP_START
	Digital.AFM.Read(dut, addr_start, AFMData, afm_size);
	 int failcounter = 0;

	for (int i = 0; i < afm_size; i += 4)
	{

		//Print("i %d AFM_data=0x%02X",i, AFMData[i]);

		if (AFMData[i]!= 0x0000)
		{
			//Print(" i=%d 0x%04X", i,AFMData[i]);
			//Print(">>i= %3d 0x%04X", i, AFMData[i]);//打印wl

			Fail_data[k] = AFMData[i];
			Fail_addr[k] = i;
			failcounter++;
			//failcounter = failcounter + 1;
			FLG_PF[dut-1] = 1;
			flg_jump = 1;//debug vddmin test
			//vdd_value = vdd;
			fail_flag = 1;
	/*		if (failcounter <= 20)
			{
				Print("i %d F_[%d]\n",i, failcounter);

			}*/
			k++;

		}
		//===============================================================================================================================
		if (1)
		{
			if (i == 0)
			{
				DataLog.Info("");
				Print("---------------------------");
				Print2buff("      ");
				for (int j = 0; j < 16; j++)
				{
					Print2buff("data %-2d   ", j);
				}
				DataLog.Info("");

			}

			if (i % 64 == 0)
			{
				if (flag_degbug)
				{
					Print2buff(" ROW[ %-6d]:", i / 64);
				}
			}
			if(flag_degbug)Print2buff(" 0x%04X", AFMData[i]);//打印wl

			if ((i > 0) && ((i % 64) == 60))
			{
				Print("\n");
				//DataLog.Info("");
			}
		}

	}
	Print("\n");
	if (failcounter ==0)
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>PASS>>>>> \n", dut, block_num);
	}
	else
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>***FAIL**>>>>> F_count[%d]\n", dut, block_num, failcounter);
		for (int n = 0; n < failcounter; n++)
		{
			if (n < 10)
			{
				Print("F_Addr[0X%06X]-> F_Data[0X%04X]\n", ((Fail_addr[n]/4)), Fail_data[n]);
			
			}
		}
	}
	delete[]AFMData;
	DUT_LOOP_END

}
void AFM_READ_CHECK_addr_add(int step,string mark_flg, int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext)
{
	int k = 0;
	int flag_degbug =1;
	unsigned int afm_size = afm_size_num * 4;
	//unsigned int afm_size = (afm_size_num * 1024 * 1024) / 32 * 4;
	unsigned int* AFMData = new unsigned int[afm_size]; // 数组索引最大 0xFFFFF
	DUT_LOOP_START
		Digital.AFM.Read(dut, addr_start, AFMData, afm_size);
	int failcounter = 0;

	for (int i = 0; i < afm_size; i += 4)
	{

		//Print("i %d AFM_data=0x%02X",i, AFMData[i]);

		if (AFMData[i] != 0x0000)
		{
			//Print(" i=%d 0x%04X", i,AFMData[i]);
			//Print(">>i= %3d 0x%04X", i, AFMData[i]);//打印wl

			Fail_data[k] = AFMData[i];
			Fail_addr[k] = i;
			failcounter++;
			//failcounter = failcounter + 1;
			FLG_PF[dut - 1] = 1;
			flg_jump = 1;//debug vddmin test
	/*		if (failcounter <= 20)
			{
				Print("i %d F_[%d]\n",i, failcounter);

			}*/
			k++;

		}
		//===============================================================================================================================
		if (i == 0)
		{
			DataLog.Info("");
			//Print("MARCH_C_[%d] %s---------------------------", step, mark_flg.data());
			Print("========================= MARCH_C_[%d] %s=========================", step, mark_flg.data());


			Print2buff("      ");
		}
		if (0)
		{
			if (i == 0)
			{
				DataLog.Info("");
				Print("%s---------------------------", mark_flg.data());
				Print2buff("      ");
				for (int j = 0; j < 16; j++)
				{
					Print2buff("data %-2d   ", j);
				}
				DataLog.Info("");

			}

			if (i % 64 == 0)
			{
				if (flag_degbug)
				{
					Print2buff(" ROW[ %-6d]:", i / 64);
				}
			}
			if (flag_degbug)Print2buff(" 0x%04X", AFMData[i]);//打印wl

			if ((i > 0) && ((i % 64) == 60))
			{
				Print("\n");
				//DataLog.Info("");
			}
		}

	}
	Print("\n");
	if (failcounter == 0)
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>PASS>>>>> \n", dut, block_num);
	}
	else
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>***FAIL**>>>>> F_count[%d]\n", dut, block_num, failcounter);
		for (int n = 0; n < failcounter; n++)
		{
			//if (n < 10)
			{
				Print("F_Addr[0X%06X]-> F_Data[0X%04X]\n", ((Fail_addr[n] / 4)), Fail_data[n]);

			}
		}
	}
	delete[]AFMData;
	DUT_LOOP_END

}
void AFM_READ_CHECK_addr_sub(int step, string mark_flg, int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext)
{
	int k = 0;
	int flag_degbug = 1;
	unsigned int afm_size = afm_size_num * 4;
	//unsigned int afm_size = (afm_size_num * 1024 * 1024) / 32 * 4;
	unsigned int* AFMData = new unsigned int[afm_size]; // 数组索引最大 0xFFFFF
	DUT_LOOP_START
		Digital.AFM.Read(dut, addr_start, AFMData, afm_size);
	int failcounter = 0;

	for (int i = afm_size-4; i >=0; i -= 4)
	//for (int i = 0; i < afm_size; i += 4)
	{

		/*Print("i %d AFM_data=0x%02X",i, AFMData[i]);
		Print("i %d AFM_data=0x%02X", i, AFMData[i+1]);
		Print("i %d AFM_data=0x%02X", i, AFMData[i+2]);
		Print("i %d AFM_data=0x%02X", i, AFMData[i+3]);*/
		if (AFMData[i] != 0x0000)
		{
			//Print(" i=%d 0x%04X", i,AFMData[i]);
			//Print(">>i= %3d 0x%04X", i, AFMData[i]);//打印wl

			Fail_data[k] = AFMData[i];
			Fail_addr[k] = i;
			failcounter++;
			//failcounter = failcounter + 1;
			FLG_PF[dut - 1] = 1;
			flg_jump = 1;//debug vddmin test
	/*		if (failcounter <= 20)
			{
				Print("i %d F_[%d]\n",i, failcounter);

			}*/
			k++;

		}
		//===============================================================================================================================
		if (i == (afm_size - 4))
		{
			DataLog.Info("");
			//Print("MARCH_C_[%d] %s---------------------------", step, mark_flg.data());
			Print("========================= MARCH_C_[%d] %s=========================", step, mark_flg.data());

			Print2buff("      ");
		}
		if (0)
		{
			if (i == (afm_size - 4))
			{
				DataLog.Info("");
				Print("%s---------------------------", mark_flg.data());
				Print2buff("      ");
				for (int j = 0; j < 16; j++)
				{
					Print2buff("data %-2d   ", j);
				}
				DataLog.Info("");

			}

			if (i % 64 == 60)
			{
				if (flag_degbug)
				{
					Print2buff(" ROW[ %-6d]:", i / 64);
				}
			}
			if (flag_degbug)Print2buff(" 0x%04X", AFMData[i]);//打印wl

			//if ((i > 0) && ((i % 64) == 60))
			if ((i > 0) && ((i % 64) == 0))
			{
				Print("\n");
				//DataLog.Info("");
			}
		}

	}
	Print("\n");
	if (failcounter == 0)
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>PASS>>>>> \n", dut, block_num);
	}
	else
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>***FAIL**>>>>> F_count[%d]\n", dut, block_num, failcounter);
		for (int n = 0; n < failcounter; n++)
		{
			//if (n < 10)
			{
				Print("F_Addr[0X%06X]-> F_Data[0X%04X]\n", ((Fail_addr[n] / 4)), Fail_data[n]);

			}
		}
	}
	delete[]AFMData;
	DUT_LOOP_END

}
void AFM_READ_CHECK_BR(int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext)
{
	int k = 0;
	int flag_degbug = 1;
	unsigned int afm_size = afm_size_num * 4;
	//unsigned int afm_size = (afm_size_num * 1024 * 1024) / 32 * 4;
	unsigned int* AFMData = new unsigned int[afm_size]; // 数组索引最大 0xFFFFF
	DUT_LOOP_START
		Digital.AFM.Read(dut, addr_start, AFMData, afm_size);

	for (int i = 0; i < afm_size; i += 4)
	{
		if (1)
		{
			if (i == 0)
			{
				DataLog.Info("");
				//Print("---------------------------");
				Print2buff("      ");
				for (int j = 0; j < 16; j++)
				{
					Print2buff("data %-2d   ", j);
				}
				DataLog.Info("");

			}

			if (i % 64 == 0)
			{
				if (flag_degbug)
				{
					Print2buff(" ROW[ %-6d]:", i / 64);
				}
			}
			if (flag_degbug)Print2buff(" 0x%04X", AFMData[i]);

			if ((i > 0) && ((i % 64) == 60))
			{
				Print("\n");
			}
		}

	}
	delete[]AFMData;
	DUT_LOOP_END
}

void AFM_READ_CHECK_HL(int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext)
{
	int k = 0;
	int flag_degbug = 1;
	unsigned int afm_size = afm_size_num * 4;
	//unsigned int afm_size = (afm_size_num * 1024 * 1024) / 32 * 4;
	unsigned int* AFMData = new unsigned int[afm_size]; // 数组索引最大 0xFFFFF
	DUT_LOOP_START
		Digital.AFM.Read(dut, addr_start, AFMData, afm_size);
	int failcounter = 0;

	for (int i = 0; i < afm_size; i += 4)
	{

		//Print("i %d AFM_data=0x%02X",i, AFMData[i]);

		if (AFMData[i] != 0x00000000)
		{
			failcounter++;
			if ((AFMData[i]&&0xFFFF)!=0)
			{
				//Print(" i=%d 0x%04X", i,AFMData[i]);
				Fail_data_L[k] = AFMData[i] && 0xFFFF;
				Fail_addr[k] = i;
				//failcounter++;
				//failcounter = failcounter + 1;
				FLG_PF[dut - 1] = 1;
				flg_jump = 1;//debug vddmin test
				k++;

			}
			if (((AFMData[i] << 16) && 0xFFFF) != 0)
			{
				//Print(" i=%d 0x%04X", i,AFMData[i]);
				Fail_data_H[k] = (AFMData[i]<<16) && 0xFFFF;
				Fail_addr[k] = i;
				//failcounter++;
				//failcounter = failcounter + 1;
				FLG_PF[dut - 1] = 1;
				flg_jump = 1;//debug vddmin test
				k++;
			}
		}
		//===============================================================================================================================
		if (1)
		{
			if (i == 0)
			{
				DataLog.Info("");
				Print("---------------------------");
				Print2buff("      ");
				for (int j = 0; j < 16; j++)
				{
					Print2buff("data %-2d   ", j);
				}
				DataLog.Info("");

			}

			if (i % 64 == 0)
			{
				if (flag_degbug)
				{
					Print2buff(" ROW[ %-6d]:", i / 64);
				}
			}
			if (flag_degbug)Print2buff(" 0x%08X", AFMData[i]);

			if ((i > 0) && ((i % 64) == 60))
			{
				Print("\n");
				//DataLog.Info("");
			}
		}

	}
	//Print("\n");
	if (failcounter == 0)
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>PASS>>>>> \n", dut, block_num);
	}
	else
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>***FAIL**>>>>> F_count[%d]\n", dut, block_num, failcounter);
		for (int n = 0; n < failcounter; n++)
		{
			if (n <= 10)
			{
				Print("F_Addr[0X%06X] -> F_Data_[0X%08X] \n", ((Fail_addr[n] / 4)), (Fail_data_H[n]<<16)|(Fail_data_L[n]));

			}
		}
	}

	DUT_LOOP_END

}
void AFM_READ_CHECK_vdd(int block_num, int afm_size_num,double temp,int addr_start, TestItemExecuteContext* aContext)
{
	int k = 0;
	int flag_degbug = 1;
	unsigned int afm_size = afm_size_num * 4;
	//unsigned int afm_size = (afm_size_num * 1024 * 1024) / 32 * 4;
	unsigned int* AFMData = new unsigned int[afm_size]; // 数组索引最大 0xFFFFF
	DUT_LOOP_START
		Digital.AFM.Read(dut, addr_start, AFMData, afm_size);
	int failcounter = 0;

	for (int i = 0; i < afm_size; i += 4)
	{

		//Print("i %d AFM_data=0x%02X",i, AFMData[i]);

		if (AFMData[i] != 0x0000)
		{
			//Print(" i=%d 0x%04X", i,AFMData[i]);

			Fail_data[k] = AFMData[i];
			Fail_addr[k] = i;
			failcounter++;
			//failcounter = failcounter + 1;
			FLG_PF[dut - 1] = 1;
			flg_jump = 1;//debug vddmin test
			flg_break = 1;//debug vddmin test
			k++;
			

		}
		//===============================================================================================================================
		if (0)
		{
			if (i == 0)
			{
				DataLog.Info("");
				Print("---------------------------");
				Print2buff("      ");
				for (int j = 0; j < 16; j++)
				{
					Print2buff("data %-2d   ", j);
				}
				DataLog.Info("");

			}

			if (i % 64 == 0)
			{
				if (flag_degbug)
				{
					Print2buff(" ROW[ %-6d]:", i / 64);
				}
			}
			if (flag_degbug)Print2buff(" 0x%04X", AFMData[i]);

			if ((i > 0) && ((i % 64) == 60))
			{
				Print("\n");
				//DataLog.Info("");
			}
		}

	}
	//Print("\n");
	if (flg_jump == 1)
	{
		Print("fail >>>>>vdd_value=%.4f\n", temp);
	}
	else
	{
		Print("pass >>>>>vdd_value=%.4f\n", temp);
	}

	if (failcounter == 0)
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>PASS>>>>> \n", dut, block_num);
	}
	else
	{
		Print("dut[%d]  Blck_num[%d]:    >>>>***FAIL**>>>>> F_count[%d]\n", dut, block_num, failcounter);
		for (int n = 0; n < failcounter; n++)
		{
			if (n <= 10)
			{
				Print("F_Addr[0X%06X]-> F_Data[0X%04X]\n", ((Fail_addr[n] / 4) + block_num * 16384), Fail_data[n]);

			}
		}
	}

	DUT_LOOP_END


}



void init_rcam_exp_data()
{
	for (int i = 0; i < 64; i++)
	{
		rcam_exp_data[i] = 0;
	}
}
void init_gbl_info()
{
	for (int dut = 0; dut < 11; dut++)
	{
		for (int bank = 0; bank < 2; bank++)
		{
			fail_gbl_cnt[dut][bank][0] = 0;
			fail_gbl_cnt[dut][bank][1] = 0;

			for (int redgbl_num = 0; redgbl_num < 16; redgbl_num++)
			{
				fail_gbl_info[dut][bank][redgbl_num].gbl_addr = -1;
				fail_gbl_info[dut][bank][redgbl_num].container = -1;
				fail_gbl_info[dut][bank][redgbl_num].redgbl = -1;
			}
		}
	}
}

void append_fail_gbl(unsigned short dut, int bank, int gbl_addr, int container)
{
	int redgbl_num = fail_gbl_cnt[dut][bank][0] + fail_gbl_cnt[dut][bank][1];

	fail_gbl_info[dut][bank][redgbl_num].gbl_addr = gbl_addr;

	fail_gbl_info[dut][bank][redgbl_num].container = container; //default: select smaller one

	fail_gbl_info[dut][bank][redgbl_num].redgbl = fail_gbl_cnt[dut][bank][container];

	fail_gbl_cnt[dut][bank][container] += 1;
}
void print_rcam_exp_data(TestItemExecuteContext* aContext)
{
	// Print rcam_exp_data 
	char edata[4];
	string rcam_edata_str = "";
	for (int i = 0; i < 64; i++)
	{
		snprintf(edata, sizeof(edata), "%02X", rcam_exp_data[i]);
		rcam_edata_str += to_string(i) + "_0x" + (string)edata + " ";
	}
	aContext->Info("rcam_exp_data " + rcam_edata_str);
}

void print_gbl_info(TestItemExecuteContext* aContext)
{
	//aContext->Info("dut\tbank\tcontainer\tredgbls");
	//for(int dut = 0; dut < 11; dut++)
	//{
	//	for(int bank = 0; bank < 2; bank++)
	//	{
	//		for(int c = 0; c < 2; c++)
	//		{
	//			aContext->Info(to_string(dut) + "\t" + to_string(bank) + "\t" 
	//				+ to_string(c) + "\t" + to_string(fail_gbl_cnt[dut][bank][c]));
	//		}
	//	}
	//}

	aContext->Info("dut\tbank\tredgbl_num\tcontainer\tredgbl\tgbl_addr");

	for (int dut = 1; dut < 11; dut++)
	{
		for (int bank = 0; bank < 2; bank++)
		{
			int sum_redgbl_num = 16;
			for (int redgbl_num = 0; redgbl_num < sum_redgbl_num; redgbl_num++) // 16
			{
				aContext->Info(to_string(dut) + "\t" + to_string(bank) + "\t" + to_string(redgbl_num) + "\t"
					+ to_string(fail_gbl_info[dut][bank][redgbl_num].container) + "\t"
					+ to_string(fail_gbl_info[dut][bank][redgbl_num].redgbl) + "\t"
					+ to_string(fail_gbl_info[dut][bank][redgbl_num].gbl_addr) + "\t");
			}
		}
	}
}

//Info("DITID left_red_cnt left_red_addr\t\tright_red_cnt right_red_addr");
//DUT_LOOP_START
//string  red_info = to_string(dut) + "\t";
//int bank_fail_cnt;
//for (int bank = 0; bank < 2; bank++)
//{
//	bank_fail_cnt = fail_gbl_cnt[dut][bank][0] + fail_gbl_cnt[dut][bank][1];
//	red_info += to_string(bank_fail_cnt) + " ";
//	for (int redgbl_num = 0; redgbl_num < bank_fail_cnt; redgbl_num++)
//	{
//		red_info += to_string(fail_gbl_info[dut][bank][redgbl_num].gbl_addr) + "_";
//	}
//	red_info += (bank_fail_cnt == 0) ? "_\t\t" : "\t\t";
//}
//Info(red_info);
//DUT_LOOP_END

void print_gbl_info(int sum_redgbl_num, TestItemExecuteContext* aContext)
{
	//aContext->Info("dut\tbank\tcontainer\tredgbls");
	//for(int dut = 0; dut < 11; dut++)
	//{
	//	for(int bank = 0; bank < 2; bank++)
	//	{
	//		for(int c = 0; c < 2; c++)
	//		{
	//			aContext->Info(to_string(dut) + "\t" + to_string(bank) + "\t" 
	//				+ to_string(c) + "\t" + to_string(fail_gbl_cnt[dut][bank][c]));
	//		}
	//	}
	//}

	aContext->Info("dut\tbank\tredgbl_num\tcontainer\tredgbl\tgbl_addr");

	for (int dut = 1; dut < 11; dut++)
	{
		for (int bank = 0; bank < 2; bank++)
		{
			for (int redgbl_num = 0; redgbl_num < sum_redgbl_num; redgbl_num++) // 16
			{
				aContext->Info(to_string(dut) + "\t" + to_string(bank) + "\t" + to_string(redgbl_num) + "\t"
					+ to_string(fail_gbl_info[dut][bank][redgbl_num].container) + "\t"
					+ to_string(fail_gbl_info[dut][bank][redgbl_num].redgbl) + "\t"
					+ to_string(fail_gbl_info[dut][bank][redgbl_num].gbl_addr) + "\t");
			}
		}
	}
}
void print_gbl_info(int dut, int bank, TestItemExecuteContext* aContext)
{
	aContext->Info("dut " + to_string(dut) +  " bank " + to_string(bank) + " container0 "
		+ to_string(fail_gbl_cnt[dut][bank][0]) + " container1 " + to_string(fail_gbl_cnt[dut][bank][1]));

	aContext->Info("redgbl_num\tcontainer\tredgbl\tgbl_addr");

	int sum_redgbl_num = fail_gbl_cnt[dut][bank][0] + fail_gbl_cnt[dut][bank][1];
	for (int redgbl_num = 0; redgbl_num < sum_redgbl_num; redgbl_num++) // 16
	{
		aContext->Info(to_string(redgbl_num) + "\t"
			+ to_string(fail_gbl_info[dut][bank][redgbl_num].container) + "\t"
			+ to_string(fail_gbl_info[dut][bank][redgbl_num].redgbl) + "\t"
			+ to_string(fail_gbl_info[dut][bank][redgbl_num].gbl_addr) + "\t");
	}
}

// AFM 

// count err021/err120 + convert_512byte
void err_bit_comp(const unsigned int* exp_data, const unsigned int* data, const unsigned int len_data,
	unsigned int* err021, unsigned int* err120, unsigned int* sum_err, 
	Err_set* err_set, const unsigned int len_err_set, const unsigned int byte_offset, 
	unsigned int* compressed_data, TestItemExecuteContext* aContext)
{
	unsigned int edata;
	unsigned int rdata;
	unsigned int e_bit;
	unsigned int r_bit;
	unsigned int e0r1;
	unsigned int bank;
	
	unsigned int init_data[1] = { 0x00 };
	repeat(init_data, 1, compressed_data, 512);

	for (int byte = 0; byte < len_data; byte++)
	{
		edata = exp_data[byte];
		rdata = data[byte];
		e0r1 = 0;
		bank = ((byte >> 20) & 0x00000001);

		for (int bit = 0; bit < 8; bit++)
		{
			e_bit = (edata >> bit) & 0x00000001;
			r_bit = (rdata >> bit) & 0x00000001;
			if ((e_bit == 0) && (r_bit == 1))
			{
				(*err021) += 1;
				if ((*sum_err) < len_err_set)
				{
					err_set[(*sum_err)].bit = bit;
					err_set[(*sum_err)].byte = byte + byte_offset;
					err_set[(*sum_err)].err_type = 0;
				}
				(*sum_err) += 1;

				e0r1 = 1;   // record err_gbl_addr 
			}
			if ((e_bit == 1) && (r_bit == 0))
			{
				(*err120) += 1;
				//aContext->Info(" byte=" + to_string(byte) + " bit=" + to_string(bit) + " edata=" + to_string(edata) + " rdata=" + to_string(rdata) + " e_bit=" + to_string(e_bit) +  " r_bit=" + to_string(r_bit));
				if ((*sum_err) < len_err_set)
				{
					err_set[(*sum_err)].bit = bit;
					err_set[(*sum_err)].byte = byte + byte_offset;
					err_set[(*sum_err)].err_type = 1;
				}
				(*sum_err) += 1;
			}

		}
		// Save Err_Gbl "512 format"
		// sum_err_gbl  err_addr[dut], err_addr_cnt
		
		if (e0r1)
		{
			compressed_data[bank * 256 + (byte % 256)] = (compressed_data[bank * 256 + (byte % 256)] | rdata) & 0xFF; // ?
		}
	}
	//return compressed_data;
}

// count err021/err120
void err_bit_comp(const unsigned int* exp_data, const unsigned int* data, const unsigned int len_data,
	unsigned int* err021, unsigned int* err120, unsigned int* sum_err,
	Err_set* err_set, const unsigned int len_err_set, TestItemExecuteContext* aContext)
{
	unsigned int edata;
	unsigned int rdata;
	unsigned int e_bit;
	unsigned int r_bit;

	for (int byte = 0; byte < len_data; byte++)
	{
		edata = exp_data[byte];
		rdata = data[byte];

		for (int bit = 0; bit < 8; bit++)
		{
			e_bit = (edata >> bit) & 0x00000001;
			r_bit = (rdata >> bit) & 0x00000001;
			if ((e_bit == 0) && (r_bit == 1))
			{
				(*err021) += 1;
				if ((*sum_err) < len_err_set)
				{
					err_set[(*sum_err)].bit = bit;
					err_set[(*sum_err)].byte = byte;
					err_set[(*sum_err)].err_type = 0;
				}
				(*sum_err) += 1;

			}
			if ((e_bit == 1) && (r_bit == 0))
			{
				(*err120) += 1;
				if ((*sum_err) < len_err_set)
				{
					err_set[(*sum_err)].bit = bit;
					err_set[(*sum_err)].byte = byte;
					err_set[(*sum_err)].err_type = 1;
				}
				(*sum_err) += 1;
			}
		}
	}
}

// count 1 (err021)
void err_bit_comp(const unsigned int* data, const unsigned int len_data,
	unsigned int* sum_err, Err_set* err_set, const unsigned int len_err_set, 
	TestItemExecuteContext* aContext)
{
	unsigned int rdata;
	unsigned int r_bit;

	for (int byte = 0; byte < len_data; byte++)
	{
		rdata = data[byte];
		for (int bit = 0; bit < 8; bit++)
		{
			r_bit = (rdata >> bit) & 0x00000001;
			if (r_bit == 1)
			{
				if ((*sum_err) < len_err_set)
				{
					err_set[(*sum_err)].bit = bit;
					err_set[(*sum_err)].byte = byte;
					err_set[(*sum_err)].err_type = 0;
				}
				(*sum_err) += 1;
			}
		}
	}
}


void afm_err_count(const unsigned short dut, const unsigned int offset_addr, const unsigned int count_size,
	unsigned int* err021, unsigned int* err120, unsigned int* sum_err,
	Err_set* err_set, const unsigned int len_err_set, TestItemExecuteContext* aContext)
{
	unsigned int zero[1] = { 0x00 };
	unsigned int* exp_data = new unsigned int[count_size];
	repeat(zero, 1, exp_data, count_size);   // 周期扩展 
	unsigned int* AFMData = new unsigned int[count_size];
	Digital.AFM.Read(dut, offset_addr, AFMData, count_size);

	err_bit_comp(exp_data, AFMData, count_size, err021, err120,
		sum_err, err_set, len_err_set, aContext);

	delete[] exp_data;
	delete[] AFMData;
}

// need to Init compressed_data first
void convert_512(const unsigned int* data, const unsigned int len_data,
	unsigned int* compressed_data, TestItemExecuteContext* aContext)
{
	unsigned int rdata;
	unsigned int r_bit;
	unsigned int e0r1;
	unsigned int bank;

	for (int byte = 0; byte < len_data; byte++)
	{
		rdata = data[byte];
		e0r1 = 0;
		bank = ((byte >> 20) & 0x00000001);

		for (int bit = 0; bit < 8; bit++)
		{
			r_bit = ((rdata >> bit) & 0x00000001);
			if (r_bit == 1)
			{
				e0r1 = 1;   
			}
		}
		// Save Err_Gbl "512 format"
		if (e0r1)
		{
			compressed_data[bank * 256 + (byte % 256)] = (compressed_data[bank * 256 + (byte % 256)] | rdata) & 0xFF;    
		}
	}
}

void repeat(const unsigned int* data, const unsigned int len_data, unsigned int* repeat_data, const unsigned int len_repeat_data)
{
	for (int i = 0; i < len_repeat_data; i++)
	{
		repeat_data[i] = data[i % len_data];
	}
}

void Config_AFM(unsigned int XNum = 12, unsigned int YNum = 12, string PinList = "DO",
	DATA_WIDTH_MODE_E DataWidthMode = ENUM_DATA_WIDTH_BIT_8, ADDRESS_MODE_E AddressMode = ENUM_ADDRESS_MODE_1,
	AFM_RESULT_MODE_E ResultMode = ENUM_OVERWRITE, unsigned int ResetData = 0x00)
{
	Digital.AFM.Config(XNum, YNum, PinList, DataWidthMode, ENUM_ALPG_SDR, AddressMode);
	Digital.AFM.SetResultMode(ResultMode);
	Digital.AFM.ResetData(ResetData);
}

// QPI
void Enable_QPI(TestItemExecuteContext* aContext)
{
	//GET_DUT_LIST
	DUT_LOOP_START
	unsigned int SR2_Status;
	char rdata[8];
	Config_AFM(1, 1, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ADDRESS_MODE_1, ENUM_OVERWRITE, 0x00);
	Digital.Pattern.RunRegister("Pat_QPI_Enable", ENUM_PATTERNSTOP_INTERRUPT, 60 S);
	Digital.Pattern.RunModule("Pat_QPI_Enable", "Mod_QPI_Enable", ENUM_PATTERNSTOP_INTERRUPT, 360 S);
	Digital.AFM.Read(dut, 0, &SR2_Status, 1);
	if (SR2_Status != 0x02)  // ȡbit1:((SR2_Status>>1)&0x1)==0x1
	{
		snprintf(rdata, 8, "%02x", (char)SR2_Status);
		string theAFMDataInfo = "Error! Dut ID: " + to_string(dut) + " EnableQE Fail! SR2_Status: " + rdata + " Expected: 0x02";
		aContext->Info(theAFMDataInfo);
		(*item)->SetValue(2);
	}
	else
	{
		(*item)->SetValue(1);
	}
	DUT_LOOP_END
}

void Disable_QPI(TestItemExecuteContext* aContext)
{
	//GET_DUT_LIST
	DUT_LOOP_START
	unsigned int SR2_Status;
	char rdata[8];
	Config_AFM(1, 1, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ADDRESS_MODE_1, ENUM_OVERWRITE, 0x00);
	Digital.Pattern.RunRegister("Pat_QPI_Disable", ENUM_PATTERNSTOP_INTERRUPT, 60 S);
	Digital.Pattern.RunModule("Pat_QPI_Disable", "Mod_QPI_Disable", ENUM_PATTERNSTOP_INTERRUPT, 360 S);
	Digital.AFM.Read(dut, 0, &SR2_Status, 1);
	if (SR2_Status != 0x00)  // ȡbit1 ((SR2_Status>>1)&0x1)==0x1
	{
		snprintf(rdata, 8, "%02x", (char)SR2_Status);
		string theAFMDataInfo = "Error! Dut ID: " + to_string(dut) + " DisableQE Fail! SR2_Status: " + rdata + " Expected: 0x00";
		aContext->Info(theAFMDataInfo);
		(*item)->SetValue(2); 
	}
	else
	{
		(*item)->SetValue(1);
	}
	DUT_LOOP_END
}

//=====================================================PMU=======================================================================//
void PMU_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL)
{
	VI.Init(PinList);
	VI.SetIRange(PinList, IRangeValue);
	VI.SetPMUMode(PinList, PMU_VSIM);
	VI.SetIClamp(PinList, ICLAMPH, ICLAMPL);	
	VI.TurnOn(PinList);
	VI.ForceV(PinList, VoltageValue);
	Time.Delay(5 MS);
}

void PMU_FI(string PinList, double CurrentValue, double IRangeValue, double VCLAMPH, double VCLAMPL)
{
	VI.Init(PinList);
	VI.SetIRange(PinList, IRangeValue);
	VI.SetPMUMode(PinList, PMU_ISVM);
	VI.SetVClamp(PinList, VCLAMPH, VCLAMPL);
	VI.TurnOn(PinList);
	VI.ForceI(PinList, CurrentValue);
}

void PMU_MeasV(string PinList, ResultMap& ResultMap)
{
	VI.GetMeasureValue(PinList, ResultMap);
}

void PMU_MeasI(string PinList, ResultMap& ResultMap)
{
	VI.GetMeasureValue(PinList, ResultMap);
}

void PMU_Off(string PinList)
{
	VI.TurnOff(PinList);
	VI.Disconnect(PinList);
}

void PMU_DigitalSet(string PinList, double VIH, double VIL, double VOH, double VOL)
{
	VI.Init(PinList);
	VI.Connect(PinList);
	VI.SetPMUMode(PinList, PMU_FNMN);
	Digital.DCL.SetVIHVIL(PinList, VIH, VIL);
	Digital.DCL.SetVOHVOL(PinList, VOH, VOL);
	VI.TurnOn(PinList);
	Time.Delay(5 MS);
}

void Pin_LevelSet(string PinList, double VDD)
{
	VI.Init(PinList);
	VI.Connect(PinList);
	VI.SetPMUMode(PinList, PMU_FNMN);
	Digital.DCL.SetVIHVIL(PinList, VDD, 0);
	Digital.DCL.SetVOHVOL(PinList, (VDD / 2 + 0.1), (VDD / 2 - 0.1));
	VI.TurnOn(PinList);
}

void PMU_DtoMVSet(string PinList, double VIH, double VIL, double VOH, double VOL)
{
	VI.Init(PinList);
	VI.Connect(PinList);
	VI.SetPMUMode(PinList, PMU_MVM);
	Digital.DCL.SetVIHVIL(PinList, VIH, VIL);
	Digital.DCL.SetVOHVOL(PinList, VOH, VOL);
	VI.TurnOn(PinList);
}

void PMU_VrefSet(string PinList, double VRef, double IOH, double IOL)
{
	VI.Init(PinList);
	VI.Connect(PinList);
	VI.SetPMUMode(PinList, PMU_FNMN);           //DCL mode
	Digital.DCL.SetIOHIOL(PinList, IOH, IOL);
	Digital.DCL.SetVRef(PinList, VRef);
	VI.TurnOn(PinList);
}

//设置 DCL 的目的是实现不同 Level 的电流、电压值与 Pattern 中的 0、1bit 的转换。DCL 设置一般包括 6种设置：VIH、VIL、VOH、VOL、IOH、IOL。这 6 个参数的含义如下：
//数字通道支持高压模式，可以通过SDK接口打开数字通道的高压模式，数字通道则可以实现通道的三态模式（即 VIH、VIL、VTT）。
//VIH：如果 Pattern 输出 1，则对 DUT 输入 VIH 所对应的的电压值。
//VIL：如果 Pattern 输出 0，则对 DUT 输入 VIL 所对应的的电压值。
//VOH：如果 DUT 输出电压高于 VOH，则对 Pattern 输入 1。
//VOL：如果 DUT 输出电压低于 VOL，则对 Pattern 输入 0。
//IOH：如果 DUT 输出电流高于 IOH，则对 Pattern 输入 1。
//IOL：如果 DUT 输出电流低于 IOL，则对 Pattern 输入 0。
//设置 IOH 和 IOL 主要用于参考电压与拉电流、灌电流的配置，
//DCL 模式下，电流 CLAMP、电压 CLAMP、电流比较数值、电压比较数值的设置都是无意义的。

void PMU_MVMSet(string PinList)
{
	VI.Init(PinList);
	VI.Connect(PinList);
	VI.SetPMUMode(PinList, PMU_MVM);
	VI.TurnOn(PinList);  //temp close
}


//=========================================================DPS================================================================//
void DPS_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL, SENSE_MODE_E SenseMode)
{
	VI.Init(PinList);
	VI.SetIRange(PinList, IRangeValue);
	VI.SetPMUMode(PinList, PMU_VSIM);
	VI.SetIClamp(PinList, ICLAMPH, ICLAMPL);
	VI.SetSenseType(PinList, SenseMode);
	VI.Connect(PinList);
	VI.TurnOn(PinList);
	VI.ForceV(PinList, VoltageValue);
	Time.Delay(5 MS);
}
void DPS_FV_SLEW(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL, double SlewRate, SENSE_MODE_E SenseMode)
{
	VI.Init(PinList);
	VI.SetVSlewRate(PinList, SlewRate);
	VI.SetIRange(PinList, IRangeValue);
	VI.SetPMUMode(PinList, PMU_VSIM);
	VI.SetIClamp(PinList, ICLAMPH, ICLAMPL);
	VI.SetSenseType(PinList, SenseMode);
	VI.Connect(PinList);
	VI.ForceV(PinList, VoltageValue);
	VI.TurnOn(PinList);
}

void DPS_MI(string PinList, ResultMap& ResultMap)
{
	VI.GetMeasureValue(PinList, ResultMap);
}

void DPS_Off(string PinList)
{
	VI.TurnOff(PinList);
	VI.Disconnect(PinList);
}

void HV_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL, SENSE_MODE_E SenseMode)
{
	VI.Init(PinList);
	VI.SetPMUMode(PinList, PMU_VSIM);
	VI.SetIRange(PinList, IRangeValue);
	VI.SetIClamp(PinList, ICLAMPH, ICLAMPL);
	VI.SetSenseType(PinList, ENUM_SENSE_REMOTE);
	VI.Connect(PinList);
	VI.TurnOn(PinList);
	VI.ForceV(PinList, VoltageValue);
}

void HV_FV_SLOW(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL, SENSE_MODE_E SenseMode)
{
	VI.Init(PinList);
	VI.SetPMUMode(PinList, PMU_VSIM);
	VI.SetVSlewRate(PinList, 0);
	VI.SetIRange(PinList, IRangeValue);
	VI.SetIClamp(PinList, ICLAMPH, ICLAMPL);
	VI.SetSenseType(PinList, ENUM_SENSE_REMOTE);
	VI.Connect(PinList);
	VI.TurnOn(PinList);
	VI.ForceV(PinList, VoltageValue);
}

void HV_MI(string PinList, ResultMap& ResultMap)
{
	VI.GetMeasureValue(PinList, ResultMap);
}

void HV_Off(string PinList)
{
	VI.Disconnect(PinList);
	VI.TurnOff(PinList);
}

void HV_MV(string PinList, ResultMap& ResultMap)
{
	VI.Init(PinList);
	VI.SetPMUMode(PinList, PMU_MVM);
	VI.Connect(PinList);
	VI.GetMeasureValue(PinList, ResultMap);
}
void DPS_LOOP_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL)
{
	VI.SetIRange(PinList, IRangeValue);
	VI.SetPMUMode(PinList, PMU_VSIM);
	VI.SetIClamp(PinList, ICLAMPH, ICLAMPL);
	VI.ForceV(PinList, VoltageValue);
	VI.TurnOn(PinList);
}

void DPS_LOOP_MVM(string PinList)
{
	VI.SetPMUMode(PinList, PMU_MVM);
}

void DPS_LOOP_Connect(unsigned short dut, string PinList)
{
	VI.SetSenseType(dut, PinList, ENUM_SENSE_REMOTE);
	VI.Connect(dut, PinList);
}

void DPS_LOOP_Measure(unsigned short dut, string PinList, ResultMap& ResultMap)
{
	VI.GetMeasureValue(dut, PinList, ResultMap);
}

void DPS_LOOP_Disconnect(unsigned short dut, string PinList)
{
	VI.SetSenseType(dut, PinList, ENUM_SENSE_LOCAL);
	VI.Disconnect(dut, PinList);
}

void DPS_LOOP_OFF(string PinList)
{
	VI.TurnOff(PinList);
}
//void DPS_PatternTrigMISET(unsigned int dut,string PinList, unsigned int SampleCount, unsigned int SampleInterval;)
//{
//	MeasureParameter theMeasureParameter;
//	theMeasureParameter.interval = SampleInterval;
//	theMeasureParameter.sampleCount = SampleCount;
//	CPMU.Disconnect(dut, PinList);
//	CPMU.Connect(dut, PinList);
//	CPMU.SetMeasureParameter(dut, PinList, &theMeasureParameter);
//	CPMU.WaitForPatternTriggerStart(dut, PinList);
//}
//
//void DPS_ManualTrigMISET(unsigned int dut, string PinList, unsigned int SampleCount, unsigned int SampleInterval;)
//{
//	MeasureParameter theMeasureParameter;
//	theMeasureParameter.interval = SampleInterval;
//	theMeasureParameter.sampleCount = SampleCount;
//	CPMU.Disconnect(dut, PinList);
//	CPMU.Connect(dut, PinList);
//	CPMU.SetMeasureParameter(dut, PinList, &theMeasureParameter);
//	CPMU.StartMeasure(dut, PinList);
//}
//
//void DPS_GetTrigAverageMeasureValue(unsigned short dut, string PinList, double* aMeasureValue)
//{
//	CPMU.GetAverageMeasureValue(dut, PinList, double* aMeasureValue);
//}
//
//void DPS_TrigOff(unsigned short dut, string PinList)
//{
//	CPMU.Disconnect(dut, PinList);
//}


//=========================================================AFM================================================================//

void AFM_Refresh(unsigned int Data)
{
	Digital.AFM.ResetData(Data);
}
void AFM_Clear()
{
	Digital.AFM.Clear();
}

//=========================================================FMM================================================================//

void RestryCount_Set(string PinList, unsigned int RTC_MAX)
{
	Digital.FMM.Config(PinList, RTC_MAX);
}

void FMM_Set(string PinList, unsigned int RTC_MAX, unsigned int BBC_MAX)
{
	Digital.FMM.Config(PinList, RTC_MAX, BBC_MAX);
}

void FMM_FailCountAddress(unsigned int XStart, unsigned int YStart, unsigned int Xend, unsigned int Yend)
{
	Digital.FMM.FailCountAddress(XStart, YStart, Xend, Yend);
}





//=========================================================UBM================================================================//
void UBM_Write(string PinList,unsigned short dut, DATA_TYPE_E DataType, unsigned int Address, unsigned int* Value, unsigned int Size)
{
	Digital.UBM.Config(PinList);
	Digital.UBM.Write(dut, DataType, Address, Value, Size);
}

void UBM_Read(unsigned short dut, DATA_TYPE_E DataType, unsigned int Address, unsigned int* Value, unsigned int Size)
{
	Digital.UBM.Read(dut, DataType, Address,Value, Size);
}

//=========================================================DBM================================================================//
//void DBM_Set(unsigned int SegmentCount,unsigned int XAddressBitLength, unsigned int YAddressBitLength)
//{
//	Digital.DBM.Config(SegmentCount,XAddressBitLength,YAddressBitLength);
//}
//
//void DBM_Write(unsigned int SegmentID, unsigned long Address, unsigned int* Value, unsigned long Size)
//{
//	Digital.DBM.Write(SegmentID, Address, Value, Size);
//}
//
//void DBM_Read(unsigned int SegmentID, unsigned long Address, unsigned int* Value, unsigned long Size)
//{
//	Digital.DBM.Read(SegmentID, Address, Value, Size);
//}
//
//void DBM_Clear()
//{
//	Digital.DBM.Clear();
//}

//=========================================================ADD================================================================//
void Pattern_SetChannelHIGH(string PinList)
{
	string WaveSet = "WS62";
	string Period = "200ns";
	Digital.Timing.SetPinList(PinList);
	Digital.Timing.Waveformset->SetPeriod(WaveSet, Period);
	Digital.Timing.Waveformset->SetDriveFormat(WaveSet, FIX1, "0ns");
	Digital.Timing.Waveformset->SetDriveEnableFormat(WaveSet, FIX0, "10ns");
	Digital.Pattern.RunPresetPattern();
}

void Pattern_SetChannelLOW(string PinList)
{
	string WaveSet = "WS62";
	string Period = "200ns";
	Digital.Timing.SetPinList(PinList);
	Digital.Timing.Waveformset->SetPeriod(WaveSet, Period);
	Digital.Timing.Waveformset->SetDriveFormat(WaveSet, FIX0, "0ns");
	Digital.Timing.Waveformset->SetDriveEnableFormat(WaveSet, FIX0, "10ns");
	Digital.Pattern.RunPresetPattern();
}

void Generate_Random_Data(unsigned int* aRandomArray, int aSize, int aMaxData)
{
	srand(time(0));
	for (int i = 0; i < aSize; i++)
	{
		aRandomArray[i] = rand() % aMaxData;
		//aRandomArray[i] = 0xff;
	}
}

void ChangeMapValue(ResultMap& aResult, int aTime)
{
	unsigned int theValue = pow(10, aTime);
	for (ResultMap::iterator it = aResult.begin(); it != aResult.end(); it++)
	{
		unsigned int theDUTID = it->first;
		map<string, double> theDUTValue = it->second;
		for (map<string, double>::iterator it1 = theDUTValue.begin(); it1 != theDUTValue.end(); it1++)
		{
			aResult[theDUTID][it1->first] = it1->second * theValue;
		}
	}
}
double getMax(TestItemExecuteContext* aContext, double array[], int count)
{
	double max = array[0];
	for (int i = 0; i < count; i++)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	return max;
}

double getAvg(TestItemExecuteContext* aContext, double array[], int count, double spec)
{

	double sum = 0;
	int cnt = 0;
	for (int i = 0; i < count; i++)
	{
		if (array[i] > spec) {

			sum = sum + array[i];
			cnt++;
		}

	}
	return sum / cnt;
}
void POWERON(int flag, double VIH)
{
	if (flag) {
		PMU_DigitalSet("IO_PINS", VIH V, 0 V, VIH / 2 V, VIH / 2 V);
		Pattern_SetChannelHIGH("CS");
		DPS_FV("POWER", VIH V, 250 MA, 250 MA, -250 MA, ENUM_SENSE_REMOTE);
		Time.Delay(5 MS);
	}
}

void POWEROFF(int flag)
{
	if (flag) {
		VI.ForceV("POWER", 0 V);
		Time.Delay(2 MS);
		DPS_Off("POWER");
		PMU_Off("CtrlPins");
	}
}

void Get_Pin_Group()
{
	char thepath[256];
	string work_folder = getcwd(thepath, 256);
	std::string samplePath = work_folder + "/data/socketpin.txt";
	//*****************************
	std::ifstream inputFile(samplePath);

	std::vector<std::string> groupNames;
	std::vector<std::vector<std::string>> pinNames;


	std::string line;
	while (std::getline(inputFile, line)) {
		size_t groupStart = line.find("<Group");
		if (groupStart != std::string::npos) {
			size_t endPos = line.find("/>", groupStart);
			std::string groupData = line.substr(groupStart, endPos - groupStart);

			size_t nameStartPos = groupData.find("Name=\"") + 6;
			size_t nameEndPos = groupData.find("\"", nameStartPos);
			std::string groupName = groupData.substr(nameStartPos, nameEndPos - nameStartPos);

			size_t pinsStartPos = groupData.find("Pins=\"") + 6;
			size_t pinsEndPos = groupData.find("\"", pinsStartPos);
			std::string pinsData = groupData.substr(pinsStartPos, pinsEndPos - pinsStartPos);

			groupNames.push_back(groupName);

			std::vector<std::string> pins;
			size_t delimPos = pinsData.find("+");
			while (delimPos != std::string::npos) {
				std::string pin = pinsData.substr(0, delimPos);
				pins.push_back(pin);

				pinsData = pinsData.substr(delimPos + 1);
				delimPos = pinsData.find("+");
			}
			pins.push_back(pinsData);

			pinNames.push_back(pins);

			// 根据groupName将pin name分配到相应的数组中
			if (groupName == "CtrlPins") {
				ctrlPins = pins;
			}
			else if (groupName == "IO_PINS") {
				ioPins = pins;
			}
			else if (groupName == "POWER") {
				powerPins = pins;
			}
		}
	}

	inputFile.close();


	//for (size_t i = 0; i < ctrlPins.size(); ++i) {
	//	Print("CtrlPins %s:", ctrlPins[i].c_str());
	//}

	//for (size_t i = 0; i < ioPins.size(); ++i) {
	//	Print("IO_PINS %s:", ioPins[i].c_str());
	//}

	//for (size_t i = 0; i < powerPins.size(); ++i) {
	//	Print("POWER %s:", powerPins[i].c_str());
	//}

}

void run_module(string PatternName, string ModuleName, double TimeOut)
{
	Digital.Pattern.RunRegister(PatternName, ENUM_PATTERNSTOP_INTERRUPT, 1 S);
	Digital.Pattern.RunModule(PatternName, ModuleName, ENUM_PATTERNSTOP_INTERRUPT, TimeOut S);
}

double GetCycleAver(int dut, double rate, unsigned int size)
{
	unsigned int* CapData = new unsigned int[size];
	memset(CapData, 0, size * sizeof(unsigned int));
	Digital.AFM.Read(dut, 0, CapData, size);

	for (int k = 0; k < 512; k++)
	{
		if (k % 32 == 0)Print("\n");
		Print2buff("0x%02X\t", CapData[k]);
	}

	int first = -1;
	int last = -1;
	int risecount = -1;
	for (int i = 4; i < size; i = i + 4)
	{
		if (CapData[i - 4] < CapData[i] && ((CapData[i] / CapData[i + 4]) != 1))
		{
			risecount++;
			last = i;
			if (first < 0)first = i;
		}
	}
	delete[]CapData;
	return 1 / (rate * (last - first) / risecount);

}




int Get_Local_Time(char* local_time_buf, int buf_size) 
{
	if (local_time_buf == NULL || buf_size < 20) { // 20是"%Y-%m-%d %H:%M:%S"的最小长度（如2026-02-02 10:00:00共19个字符+'\0'）
		Print("Error: Invalid buffer or buffer size too small.\n");
		return 1;
	}
	time_t current_timestamp = time(NULL);
	if (current_timestamp == (time_t)-1) {
		Print("Error: Failed to get current timestamp.\n");
		return 1;
	}
	struct tm* local_time = localtime(&current_timestamp);
	if (local_time == NULL) {
		Print("Error: Failed to convert to local time.\n");
		return 1;
	}

	strftime(local_time_buf, buf_size, "%Y-%m-%d %H:%M:%S", local_time);

	// 4. 可选：内部打印验证
	//Print("LOCAL TIME:%s\n", local_time_buf);

	return 0;
}
int Get_Local_Time_1(char* local_time_buf, int buf_size)
{
	if (local_time_buf == NULL || buf_size < 20) { // 20是"%Y-%m-%d %H:%M:%S"的最小长度（如2026-02-02 10:00:00共19个字符+'\0'）
		Print("Error: Invalid buffer or buffer size too small.\n");
		return 1;
	}
	time_t current_timestamp = time(NULL);
	if (current_timestamp == (time_t)-1) {
		Print("Error: Failed to get current timestamp.\n");
		return 1;
	}
	struct tm* local_time = localtime(&current_timestamp);
	if (local_time == NULL) {
		Print("Error: Failed to convert to local time.\n");
		return 1;
	}

	strftime(local_time_buf, buf_size, "%Y/%m/%d %H:%M:%S", local_time);

	// 4. 可选：内部打印验证
	Print("\nLOCAL TIME:%s", local_time_buf);

	return 0;
}
void Print2buff(const char* format, ...)
{
	int  vasprintf(char** result, char const* format, va_list args);
	va_list ap;
	va_start(ap, format);
	char* buf_ = NULL;
	vasprintf(&buf_, format, ap);
	//fprintf(stdout, "%s", buf_);
	//fflush(stdout);
	DataLog.Info(buf_, false);
	free(buf_);
	va_end(ap);
}


int PrintLogall(TestDomainExecuteContext* aContext)
{
	int swbinno = 0;
	int hwbinno = 0;
	string theWaferInfo = aContext->GetWaferID(); //获取Wafer信息
	string thelotInfo = aContext->GetLotID(); //获取Wafer信息
	Print("");
	Print("*****K8000 Log Print Start*****"); 
	Print("[Header]       ");
	Print("Test_Program:\t%s\t", TestFlow.c_str());
    Print("Cust_LotId:\t%s\t", thelotInfo.c_str());
    Print("Customer_Id:	  ");
    Print("Device_ID:\t%s\t","TJ");
    Print("ProberCard_Id: ");
    Print("Tester_Id:\t%s\t","K8000");
    Print("Operator_Id:	  ");
    Print("Prober_Id:	  ");
    Print("temperature:	  ");
    Print("HSTS_LOT:	  ");
    Print("Flow_ID:\t%s\t", TestFlow.c_str());
    Print("Process:		  ");
    Print("Handle_Id:	  ");
    Print("LoadBoard_Id:  ");
	Print("WaferID:\t%s\t", theWaferInfo.c_str());
    Print("start_time:\t%s\t", start_time_s.c_str());
    Print("end_time:\t%s\t", end_time_s.c_str());
    Print("Tnumber:\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t", " ", " ", " ", " ", " ", "1", "1", "1", "1", "1", "1","2","3","4","5",
		"6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32",
		"33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56");
    Print("Uplimit:\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t"," "," "," "," "," ","-200", "-200", "-200", "-200", "-200", "-200");
    Print("Downlimit:\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t", " ", " ", " ", " ", " ", "-900", "-900", "-900", "-900", "-900", "-900");
    Print("unit:\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t", " ", " ", " ", " "," ", "mV", "mV", "mV", "mV", "mA", "mA");

	//Print2buff(">sysdut\tdut\tBIN\tX\tY\t");
	Print2buff("Serial#\tSite#\tProberX#\tProberY#\tHW Bin#\tSW Bin#\t");
	//Print2buff("WAFER\t");
	//DC parameters
	Print2buff("CS\tDO\tSCK\tDI\tVAA\tVHH\t");//1/TB_Continuity
	Print2buff("TB_Power_On_Uninitialized\t");
	Print2buff("TB_Read_Cregs_TestMode\t");
	Print2buff("TB_Read_Version_ID\t");
	Print2buff("TB_IAA_Stanby\t");
	Print2buff("TB_Load_CRegs_from_File\t");
	Print2buff("TB_IAA_Stanby\t");
	Print2buff("TB_VHH_Trim_Source\t");
	Print2buff("TB_Mem_Main_Read_vsFFh_DDW\t");
	Print2buff("TB_Force_VHH\t");
	Print2buff("TB_Mbist_Write_00h_DDW\t");
	Print2buff("TB_Mem_Ext_Write_FFh_DDW\t");
	Print2buff("TB_Mem_Main_Read_vs00h_DDW\t");
	Print2buff("TB_Mbist_Write_FFh_DDW\t");
	Print2buff("TB_Mem_Ext_Write_00h_DDW\t");
	Print2buff("TB_Mem_Main_Read_vs00h_DDW\t");
	Print2buff("TB_Mem_Ext_Write_FF00h_DDW\t");
	Print2buff("TB_Mem_Main_Read_vsFFh_DDW\t");
	Print2buff("TB_Mbist_Write_FF00h_Cycles_DDW\t");
	Print2buff("TB_Mem_Main_Read_vs00h_DDW\t");
	Print2buff("TB_Mem_Ext_Write_00FFh_DDW\t");
	Print2buff("TB_Mem_Main_Read_vs00h_DDW\t");
	Print2buff("TB_Mbist_Write_CKB_DDW\t");
	Print2buff("TB_Mem_Main_Read_vsCKB_DDW\t");
	Print2buff("TB_Mem_Main_Read_vs00h_DDW\t");
	Print2buff("TB_Float_VHH\t");
	Print2buff("TB_Mbist_Write_InvCKB_DDW\t");
	Print2buff("TB_Mem_Main_Read_vsInvCKB_DDW\t");
	Print2buff("TB_Mbist_Write_InvCKB_DDW\t");
	Print2buff("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS\t");
	Print2buff("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS\t");
	Print2buff("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS\t");
	Print2buff("TB_Load_CRegs_from_File\t");
	Print2buff("TB_Chip_Erase\t");
	Print2buff("TB_Mem_Ext_Populate_Data\t");
	Print2buff("TB_Mem_Ext_Populate_vhhtrim\t");
	Print2buff("TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim\t");
	Print2buff("TB_Mem_Main_Read_vs00h_DDW\t");
	Print2buff("TB_Write_TReg\t");
	Print2buff("TB_Mem_Ext_Populate_CustomizedUniCode\t");
	Print2buff("TB_Float_VHH\t");
	Print2buff("TB_Power_Down\t");
	Print2buff("TB_Power_On_Initialized\t");
	Print2buff("TB_Read_StatusReg1\t");
	Print2buff("TB_Read_StatusReg2\t");
	Print2buff("TB_Read_SFDP\t");
	Print2buff("TB_Read_SecurityRegisters\t");
	Print2buff("TB_Read_SecurityRegisters\t");
	Print2buff("TB_Read_SecurityRegisters\t");
	Print2buff("TB_Read_Manufacturer_ID\t");
	Print2buff("TB_Read_Unique_ID\t");
	Print2buff("TB_Read_Jedec_ID\t");
	Print2buff("TB_Mem_Populate_Data\t");
	Print2buff("TB_IAA_Stanby\t");
	Print2buff("TB_Read_Cregs_TestMode\t");
	Print2buff("TB_Power_Down\t");
	Print("");
	//"*********************************************"TestItem
	TD++;
		DUT_LOOP_START
		if ((*item)->IsEnable())
		{
			hwbinno = atoi((*item)->GetOwnerBin()->GetHardBinID().c_str());
			swbinno = atoi((*item)->GetOwnerBin()->GetSoftBinID().c_str());
			
			Print2buff("%d\t%d\t", TD,(*item)->GetSysID());
			Print2buff("%d\t%d\t", g_die_X[dut - 1], g_die_Y[dut - 1]);
			Print2buff("%d\t", hwbinno);
			Print2buff("%d\t", swbinno);
		
			
			//DC parameters
			Print2buff("%.7f\t%.7f\t%.7f\t%.7f\t%.7f\t%.7f\t", RsltVSS_OS_global[dut]["CS"], RsltVSS_OS_global[dut]["DO"], RsltVSS_OS_global[dut]["SCK"], RsltVSS_OS_global[dut]["DI"], Rslt_VAA_global[dut]["VAA"], Rslt_VHH_global[dut]["VHH"]);
			Print2buff("%s\t", TB_Power_On_Uninitialized_1010[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_Cregs_TestMode_1020[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_Version_ID_1030[dut - 1] ? "FAIL" : "PASS");
		    Print2buff("%.4f\t", TB_IAA_Stanby_1040[dut - 1]);
			Print2buff("%s\t", TB_Load_CRegs_from_File_1050[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%.4f\t", TB_IAA_Stanby_1060[dut - 1]);
			Print2buff("%s\t", TB_VHH_Trim_Source_1070[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vsFFh_DDW_1080[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Force_VHH_1090[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mbist_Write_00h_DDW_1100[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Ext_Write_FFh_DDW_1110[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vs00h_DDW_1120[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mbist_Write_FFh_DDW_1130[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Ext_Write_00h_DDW_1140[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vs00h_DDW_1150[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Ext_Write_FF00h_DDW_1160[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vsFFh_DDW_1170[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mbist_Write_FF00h_Cycles_DDW_1180[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vs00h_DDW_1190[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Ext_Write_00FFh_DDW_1200[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vs00h_DDW_1210[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mbist_Write_CKB_DDW_1220[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vsCKB_DDW_1230[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vs00h_DDW_1240[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%.4f\t", TB_Float_VHH_1250[dut - 1]);
			Print2buff("%s\t", TB_Mbist_Write_InvCKB_DDW_1260[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vsInvCKB_DDW_1270[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mbist_Write_InvCKB_DDW_1280[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS_1290[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1300[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1310[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Load_CRegs_from_File_1320[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%.4f\t", TB_Chip_Erase_1330[dut - 1]);
			Print2buff("%s\t", TB_Mem_Ext_Populate_Data_1340[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Ext_Populate_vhhtrim_1350[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim_1360[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Main_Read_vs00h_DDW_1370[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Write_TReg_1380[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Ext_Populate_CustomizedUniCode_1390[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%.4f\t", TB_Float_VHH_1400[dut - 1]);
			Print2buff("%s\t", TB_Power_Down_1410[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Power_On_Initialized_1420[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_StatusReg1_1430[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_StatusReg2_1440[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_SFDP_1450[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_SecurityRegisters_1460[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_SecurityRegisters_1470[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_SecurityRegisters_1480[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_Manufacturer_ID_1490[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_Unique_ID_1500[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_Jedec_ID_1510[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Mem_Populate_Data_1520[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_IAA_Stanby_1530[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Read_Cregs_TestMode_1540[dut - 1] ? "FAIL" : "PASS");
			Print2buff("%s\t", TB_Power_Down_1550[dut - 1] ? "FAIL" : "PASS");

			
				
			//2
			//Print2buff("%.2f\t0x%02X\t", osc_test_val[DUTID - 1], osc_test_dac[DUTID - 1]);//3
			//Print2buff("%.1f\t%d\t", novlcfgb_trim_time[DUTID - 1], novlcfgb_trim_fstatus[DUTID - 1]);//4
			//Print2buff("%d\t", check_novl_cfgb_fstatus[DUTID - 1]);//5
			//Print2buff("%.3f\t", vref_final_test_val[DUTID - 1]);//6
			//Print2buff("%.3f\t", iref_final_test_val[DUTID - 1]);//7
			//Print2buff("%.3f\t", osc_final_test_val[DUTID - 1]);//8
			//Print2buff("%.3f\t", isb_test_val[DUTID - 1]);//9
			//Print2buff("%.3f\t", idpd_test_val[DUTID - 1]);//10
			//Print2buff("%d\t", twrsr1_test_fstatus[DUTID - 1]);//11
			//Print2buff("%d\t", twrsr0_test_fstatus[DUTID - 1]);//12
			//Print2buff("0x%06X\t", rdsr00_val[DUTID - 1]);//13
			//Print2buff("0x%02X\t", rdsr_DRV10_val[DUTID - 1]);//14
			//Print2buff("%.1f\t", secuity_erase1_time[DUTID - 1]);//15
			//Print2buff("%d\t", secuity_chkff1_fstatus[DUTID - 1]);//16
			//Print2buff("%.1f\t", bist_erase_time[DUTID - 1]);//17
			//Print2buff("0x%04X\t", bistchk_FF_val[DUTID - 1]);//18
			//Print2buff("%.1f\t", bist_pgm_ckb_LV_time[DUTID - 1]);//19
			//Print2buff("0x%04X\t", bistchk_ckb_fix_HV_val[DUTID - 1]);//20
			//Print2buff("%.1f\t", bist_pgm_ickb_NV_time[DUTID - 1]);//21
			//Print2buff("0x%04X\t", bist_chk_00_all_1_val[DUTID - 1]);//22
			//Print2buff("%.1f\t", bist_erase_1_time[DUTID - 1]);//23
			//Print2buff("0x%04X\t", usermode_checkff_val[DUTID - 1]);//24
			//Print2buff("%.1f\t", bist_pgm_ickb_HV_1_time[DUTID - 1]);//25
			//Print2buff("0x%04X\t", bistchk_ickb_fix_LV_val[DUTID - 1]);//26
			//Print2buff("%.1f\t", bist_pgm_ckb_HV_time[DUTID - 1]);//27
			//Print2buff("0x%04X\t", bist_chk_00_all_val[DUTID - 1]);//28
			//Print2buff("%.1f\t%d\t", sdfp_erase_time[DUTID - 1], sdfp_erase_fstatus[DUTID - 1]);//29
			//Print2buff("0x%02X\t%.1f\t", secuity_erase2_val[DUTID - 1], secuity_erase2_time[DUTID - 1]);//30
			//Print2buff("%d\t", secuity_chkff2_fstatus[DUTID - 1]);//31
			//Print2buff("0x%04X\t0x%06X\t", ReadId_9F90_IDval[DUTID - 1], ReadId_9F90_Jedecval[DUTID - 1]);//32
			//Print2buff("0x%06X\t", write_cp1_flag_val[DUTID - 1]);//33
			//Print2buff("%d\t", check_novl_record_fstatus[DUTID - 1]);//34
		}
	Print("");
	DUT_LOOP_END
	Print("*****K8000 Log Print End*****");

}
void log_file_head_information(const std::string testNum, const std::string cp_ver, const std::string LotId, const std::string WaferId, const int Die_X, const int Die_Y)
{
	// 获取当前系统时间
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	// 将当前时间转化为本地时间
	std::tm* localTime = std::localtime(&currentTime);

	// 获取年、月、日、时、分、秒
	int year = localTime->tm_year + 1900;
	int month = localTime->tm_mon + 1;
	int day = localTime->tm_mday;
	int hour = localTime->tm_hour;
	int min = localTime->tm_min;
	int sec = localTime->tm_sec;

	// ET LOG Output
	//ETLog::Info("\n[TEST_NUM]=#{}", testNum);
	//ETLog::Info("\n[CP_VER]={}", cp_ver);
	//ETLog::Info("\nLotNum={},WaferNum={} Die_X={},Die_Y={} LOCAL TIME:{}-{}-{} {:02}:{:02}:{:02} \n", LotId, WaferId, Die_X, Die_Y, year, month, day, hour, min, sec);

	// User Log Output
	Print("\n[TEST_NUM]=#%s", testNum.c_str());
	Print("\n[CP_VER]=#%s", cp_ver.c_str());
	Print("\nLotNum=%s,WaferNum=%s Die_X=%d,Die_Y=%d LOCAL TIME:%d-%d-%d %02d:%02d:%02d \n", LotId.c_str(), WaferId.c_str(), Die_X, Die_Y, year, month, day, hour, min, sec);
}

//
//void Get_TestNumber(TestItemExecuteContext* aContext,string TestNumber)
//{
//
//	const char* original_str = (aContext->GetActiveTestName()).c_str();
//	const char* delimiter = "_TB";
//	char testnumber[100] = { 0 };
//	char* tb_pos = strstr(original_str, delimiter);
//
//	if (tb_pos == NULL) {
//		Print("Error: Delimiter not found in the original string! \"%s\"", delimiter);
//		return 1;
//	}
//
//	int number_len = tb_pos - original_str;
//
//	strncpy(testnumber, original_str, number_len);
//	testnumber[number_len] = '\0';
//	//strcpy(testname, tb_pos + 1);
//
//	Print("original_str:%s", original_str);
//	Print("testnumber:%s", testnumber);
//
//
//
//
//	TestNumber = testnumber;
//	return TestNumber;
//}
//void Get_TestName(TestItemExecuteContext* aContext,string TestName)
//{
//
//	const char* original_str = (aContext->GetActiveTestName()).c_str();
//	const char* delimiter = "_TB";
//	char testname[100] = { 0 };
//
//	char* tb_pos = strstr(original_str, delimiter);
//
//	if (tb_pos == NULL) {
//		Print("Error: Delimiter not found in the original string! \"%s\"", delimiter);
//		return 1;
//	}
//
//	int number_len = tb_pos - original_str;
//
//	strncpy(testnumber, original_str, number_len);
//	testnumber[number_len] = '\0';
//	strcpy(testname, tb_pos + 1);
//
//	Print("original_str:%s", original_str);
//	Print("testnumber:%s", testnumber);
//	Print("testname:%s", testname);
//
//     TestName = testname;
//	return TestNumber;
//}
//void RRAM_TJ::update_local_time(UserLog& testlog)
//{
//	// 获取当前系统时间
//	auto now = std::chrono::system_clock::now();
//	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
//
//	// 将当前时间转化为本地时间
//	std::tm* localTime = std::localtime(&currentTime);
//
//	// 获取年、月、日、时、分、秒
//	int year = localTime->tm_year + 1900;
//	int month = localTime->tm_mon + 1;
//	int day = localTime->tm_mday;
//	int hour = localTime->tm_hour;
//	int min = localTime->tm_min;
//	int sec = localTime->tm_sec;
//
//	// 输出时间信息
//	ETLog::Info("LOCAL TIME: {}/{}/{}   {:02}:{:02}:{:02} ", year, month, day, hour, min, sec);
//	testlog.Info("LOCAL TIME: {}/{}/{}   {:02}:{:02}:{:02} ", year, month, day, hour, min, sec);
//
//}
string log_name_setting(TestItemExecuteContext* aContext, std::string& LotId, std::string& WaferId, int& Die_X, int& Die_Y, const std::string testname)
{

	//LotID_WaferID_TouchdownX_TochdownY_LogNameInTable_Date

	LotId = aContext->GetLotID();
	WaferId = aContext->GetWaferID();

	//dutx[dutz] = atoi((*item)->GetX().c_str());
	//duty[dutz] = atoi((*item)->GetY().c_str());
	DUT_LOOP_START
	Die_X = atoi((*item)->GetX().c_str());
	Die_Y = atoi((*item)->GetX().c_str());
	DUT_LOOP_END
	char td_buf[500];
	std::string td = "";
	sprintf(td_buf, "%d_%d", Die_X, Die_Y);
	td = td_buf;
	std::string logName = LotId + "_" + WaferId + "_" + td + "_" + testname.substr(0, testname.find(".txt")) + "_" + aContext->GetSiteName() + ".txt";

	std::stringstream save_file_temp;

	// Get the current date and time
	time_t now = time(nullptr);
	tm* time_info = localtime(&now);

	// Format the date and time as strings
	save_file_temp << "_" << (time_info->tm_year + 1900) << "_" << (time_info->tm_mon + 1) << "_" << time_info->tm_mday << "_" << time_info->tm_hour << "_" << time_info->tm_min;

	// Check if the file name has an extension
	size_t dot_pos = logName.find_last_of('.');
	if (dot_pos == std::string::npos)
	{
		// Append the formatted date and time to the file name
		logName += save_file_temp.str();
		logName += ".txt";
	}
	else
	{
		// Insert the formatted date and time before the extension
		logName.insert(dot_pos, save_file_temp.str());
	}
	return logName;
}

string log_name_setting(TestItemExecuteContext* aContext, const std::string testname)
{
	// LogNameInTable_Date
	std::string logName = testname.substr(0, testname.find(".txt")) + "_" + aContext->GetSiteName() + ".txt";

	std::stringstream save_file_temp;

	// Get the current date and time
	time_t now = time(nullptr);
	tm* time_info = localtime(&now);

	// Format the date and time as strings
	save_file_temp << "_" << (time_info->tm_year + 1900) << "_" << (time_info->tm_mon + 1) << "_" << time_info->tm_mday << "_" << time_info->tm_hour << "_" << time_info->tm_min;

	// Check if the file name has an extension
	size_t dot_pos = logName.find_last_of('.');
	if (dot_pos == std::string::npos)
	{
		// Append the formatted date and time to the file name
		logName += save_file_temp.str();
		logName += ".txt";
	}
	else
	{
		// Insert the formatted date and time before the extension
		logName.insert(dot_pos, save_file_temp.str());
	}
	return logName;
}


//int CustomizedUniCode(TestItemExecuteContext* aContext, std::string& LotId, std::string& WaferId, int& Die_X, int& Die_Y,  UINT64 customized_4byte, std::vector<std::vector<int>>& UniqueCharArray, int Mem_Ext_Write_Page, int Page_Num)
//{
//#ifdef RRAM_B2_AUTOMATION
//	LotId = context->GetLotId();
//	WaferId = context->GetWaferId();
//	Die_X = context->GetSiteContext()->GetTouchXCoordinate();
//	Die_Y = context->GetSiteContext()->GetTouchYCoordinate();
//#else
//	LotId = "B550064";
//	WaferId = "B550064-14";
//	Die_X = 73;
//	Die_Y = 304;
//	int DUT_Location_X[128] = { 0,30,0,30,0,30,0,30,2,28,2,28,2,28,2,28,4,26,4,26,4,26,4,26,6,24,6,24,6,24,6,24,8,22,8,22,8,22,8,22,10,20,10,20,10,20,10,20,
//								12,18,12,18,12,18,12,18,14,16,14,16,14,16,14,16,16,14,16,14,16,14,16,14,18,12,18,12,18,12,18,12,20,10,20,10,20,10,20,10,
//								22,8,22,8,22,8,22,8,24,6,24,6,24,6,24,6,26,4,26,4,26,4,26,4,28,2,28,2,28,2,28,2,30,0,30,0,30,0,30,0 };
//	int DUT_Location_Y[8] = { 0,-4,4,-8,8,-12,12,-16 };
//	// int DUT_Location_X[192] = {0,31,0,31,0,31,1,30,1,30,1,30,2,29,2,29,2,29,3,28,3,28,3,28,4,27,4,27,4,27,5,26,5,26,5,26,6,25,6,25,6,25,7,24,7,24,7,24,8,23,8,23,8,23,9,22,9,22,9,22,
//	// 						   10,21,10,21,10,21,11,20,11,20,11,20,12,19,12,19,12,19,13,18,13,18,13,18,14,17,14,17,14,17,15,16,15,16,15,16,16,15,16,15,16,15,17,14,17,14,17,14,
//	// 						   18,13,18,13,18,13,19,12,19,12,19,12,20,11,20,11,20,11,21,10,21,10,21,10,22,9,22,9,22,9,23,8,23,8,23,8,24,7,24,7,24,7,25,6,25,6,25,6,26,5,26,5,26,5,
//	// 						   27,4,27,4,27,4,28,3,28,3,28,3,29,2,29,2,29,2,30,1,30,1,30,1,31,0,31,0,31,0};
//	// int DUT_Location_Y[6]  = {0,-3,3,-6,6,-9};
//#endif
//
//
//	//DUTList* theActiveDUTs = context->GetActiveDUTs();
//
//	// 获取当前系统时间
//	auto now = std::chrono::system_clock::now();
//	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
//
//	// 将当前时间转化为本地时间
//	std::tm* localTime = std::localtime(&currentTime);
//
//	// 获取年、月、日、时、分、秒
//	int year = localTime->tm_year + 1900;
//	int month = localTime->tm_mon + 1;
//	int day = localTime->tm_mday;
//	int bytenum = 0;
//	char buf[64];
//	int retrieve_val = 0;
//	bool debug_winlog = true;
//	std::string window_log;
//	UINT64 return_fail_dut_mask = PRESET_NO_DUT_FAIL;
//	size_t mem_data_size = 0;
//
//	std::vector <std::vector<int>> duts_target_bytes(MAX_DUTS);
//	//std::vector<UBMBuffer> buffer{};
//	//UBMBuffer UBM_Buffer{};
//
//
//	std::vector<UBMCacheData> buffer{};
//
//	UBMCacheData UBM_Buffer{};
//	UBM_Buffer.Value.resize(CFG_FILE_LENGTH);
//	UBM_Buffer.Size = CFG_FILE_LENGTH;
//
//	std::string output, outbuf;
//	std::string write_information[64];
//	std::string write_information2[64];
//	std::string readbuf = "";
//
//	//for (auto itDUT : *theActiveDUTs) {
//	DUT_LOOP_START
//		//int dut = itDUT->GetLocalID();
//		//int SYS_DUT = itDUT->GetSysID();
//	    int SYS_DUT = (*item)->GetSysID();
//#ifdef RRAM_B2_AUTOMATION
//		int DUT_X = itDUT->GetX();
//		int DUT_Y = itDUT->GetY();
//#else
//		int DUT_X = Die_X + DUT_Location_X[SYS_DUT];
//		int DUT_Y = Die_Y + DUT_Location_Y[SYS_DUT % 6];
//#endif
//		int size = 64;
//		std::vector <unsigned int> value(size, 0);
//
//		duts_target_bytes[dut].push_back( /*0: X_coordinate*/DUT_X); //dut x coordinate
//		duts_target_bytes[dut].push_back( /*1: Y_coordinate*/DUT_Y); //dut y coordinate
//		duts_target_bytes[dut].push_back( /*2: site# on probecard*/SYS_DUT); //dut y coordinate
//
//		Print("waferID:%s,Sel_Taiji:%d,duts_target_bytes:%d %d %d,year:%d, month:%d,day:%d,customized_4byte:%08X,Sel_Magunm:%d",
//			WaferId, Sel_Taiji, duts_target_bytes[dut][0], duts_target_bytes[dut][1], duts_target_bytes[dut][2], year, month, day, customized_4byte, Sel_Magunm);
//
//		Print("Gen_GetCusUniCode address: %d", reinterpret_cast<void*>(UniCusCOde.Gen_GetCusUniCode));
//
//		// <RM 2025/07/18: change operator
//		retrieve_val = UniCusCOde.Gen_GetCusUniCode(
//			WaferId.c_str(),
//			static_cast<char>(Sel_Taiji),    // <RM 2025/07/18: change operator> 
//			duts_target_bytes,
//			year,
//			month,
//			day,
//			customized_4byte,
//			static_cast<char>(Sel_M5000));
//
//		if (retrieve_val == 1 /*accomplished*/) {
//			if (debug_winlog) {
//				for (int dut = 0; dut < MAX_DUTS; ++dut) {
//					// window_log += vFormat("\ndut[%d]mem_after_dll:", dut);
//					// ETLog::Info("dut{} mem_after-dll",dut);
//					std::ostringstream hex_stream;
//					for (auto elem_code : duts_target_bytes[dut]) {
//						// window_log += vFormat("%02X,", elem_code);
//						hex_stream << std::uppercase << std::setw(2) << std::setfill('0')
//							<< std::hex << elem_code << ",";
//
//					}
//					// ETLog::Info(" hex:{}",hex_stream.str());
//
//					std::ostringstream char_stream;
//					for (auto elem_code : duts_target_bytes[dut]) {
//						char_stream << static_cast<char>(elem_code) << ",";
//					}
//					Print("dut%02d em_after-dll, hex:%s, char:%s", dut, hex_stream.str(), char_stream.str());
//				}
//			}
//		}//// no error 
//		else {// <RM 2025/07/18: fatal !!!>
//			return_fail_dut_mask |= PRESET_ALL_DUT_FAIL;
//			Print("OPERATION INTERRUPTED !!!! ERROR CODE: %d", retrieve_val);
//			return 0;
//		}////  error reported
//
//		//// sync EBM & global buffer target 
//		const size_t TARGET_BYTE_LENGTH = 64;
//		std::vector<std::vector<unsigned char>> mem_data_container(MAX_DUTS);
//
//		// for (auto itDUT : *theActiveDUTs)
//		// {/// only active/enabled DUT will run:
//		// 	int dut = itDUT->GetLocalID();;  ///dut per site range: 0~15
//		for (auto _value : duts_target_bytes[dut]) {
//			mem_data_container[dut].push_back(static_cast<unsigned char>(_value));
//		}
//		// if less than 64 byte，add 0xFF
//		if (mem_data_container[dut].size() < TARGET_BYTE_LENGTH) {
//			mem_data_container[dut].resize(TARGET_BYTE_LENGTH, 0xFF);
//		}
//		UserRegs.set_xreg_target(dut, 0, mem_data_container[dut]);
//		if (mem_data_container[dut].size() > mem_data_size)
//			mem_data_size = mem_data_container[dut].size();
//
//		if (debug_winlog) {
//			int index = 0;
//			std::ostringstream log_stream;
//			for (auto dut_rec : mem_data_container)
//			{
//				// window_log += vFormat("\ndut%d:", index);
//
//				log_stream << "dut" << index << ": ";
//				for (auto byte : dut_rec)
//				{
//					// window_log += vFormat("%02x,", byte);
//					log_stream << std::uppercase << std::setw(2) << std::setfill('0')
//						<< std::hex << static_cast<int>(byte) << ",";
//				}
//				log_stream << "\n";
//				index++;
//			}
//
//			Print("%s", log_stream.str());
//
//		}
//
//
//		//unsigned int UbmSize = 64;
//		unsigned char UbmData[64];
//		UBM_Buffer.DUTID = dut;
//		UBM_Buffer.Size = TARGET_BYTE_LENGTH;
//
//
//		//*@par Description
//		//	* 用于存放UBM缓存的数据
//		//	* /
//		//	typedef struct
//		//{
//		//	/**
//		//	* @par Description
//		//	* DUT的编号.
//		//	*/
//		//	unsigned short DUTID;
//		//	/**
//		//	* @par Description
//		//	* 缓存数据的类型, 跨VP模式下该参数无效.
//		//	*/
//		//	DATA_TYPE_E DataType;
//		//	/**
//		//	* @par Description
//		//	* 缓存数据的相对地址.
//		//	*/
//		//	unsigned int Address;
//		//	/**
//		//	* @par Description
//		//	* 缓存数据的值.
//		//	*/
//		//	vector<unsigned int> Value;
//		//	/**
//		//	* @par Description
//		//	* 缓存数据的数量.(跨VP模式下Size必须是4的整数倍).
//		//	*/
//		//	unsigned int Size;
//		//	/**
//		//	* @par Description
//		//	* 缓存数据的主题.
//		//	*/
//		//	std::string Topic;
//		//}UBMCacheData;
//
//
//
//		//// 分配内存，并拷贝 mem_data_container[dut] 数据
//		//UBM_Buffer.Value = new unsigned char[TARGET_BYTE_LENGTH];
//		//memcpy(UBM_Buffer.Value, mem_data_container[dut].data(), TARGET_BYTE_LENGTH);
//		//buffer.push_back(UBM_Buffer);
//
//		//const auto& latestBuffer = buffer.back();
//
//		//for (int j = 0; j < TARGET_BYTE_LENGTH; j++)
//		//{
//		//	UniqueCharArray[dut][j] = static_cast<int>(latestBuffer.data[j]);
//		//}
//
//		Print("UniqueCharArray:%02X ", UniqueCharArray[dut][0]);
//
//		// for(size_t i =0; i< TARGET_BYTE_LENGTH; i++)
//		// {
//		// 	ETLog::Info("UniqueCharArray[{}]:{:02X}",dut ,UniqueCharArray[dut][0]);
//		// }
//
//		// ETLog::Info("buffer:{}", buffer.data);
//
//
//
//		// for(int j = 0; j < size; j++)
//		// {   
//		// 	UniqueCharArray[dut][j] = static_cast<int>(ValueArray[j]);
//		// }
//	//}
//
//	DUT_LOOP_END
//
//
//	//UBM::Write("DI", &buffer);
//
//	//// ETLog::Info("Trigger debug1");
//	//// sleep(15);
//
//	//Pattern::WriteRegister(REG_Y1, Mem_Ext_Write_Page);
//	//// Pattern::WriteRegister(REG_D1,DValue);
//	//Pattern::Run("pExtWriteUniqueChar_NoPolling", "fExtWriteUniqueChar_NoPolling", true, InterruptType::INT_ANY, 60 * 1000 * 1000);
//
//
//
//
//
//
//
//	//for (auto Buf_Release : buffer)
//	//{
//	//	delete[] Buf_Release.data;
//	//	Buf_Release.data = nullptr;
//	//}
//	std::vector<UBMCacheData>().swap(buffer);
//
//	// ETLog::Info(outbuf);
//	// testlog.Info(outbuf);
//
//	return static_cast<int>(mem_data_size);
//}


void loadHexFile(const std::string& filepath, std::vector<uint8_t>& data)
{
	std::ifstream infile(filepath);
	if (!infile.is_open())
	{
		std::cerr << "Failed to open file" << filepath << std::endl;
		return;
	}

	std::string token;
	// 按空格或换行分割，每个token是 "FF" / "00" / "CC" 这样的字符串
	while (infile >> token) {
		// 把16进制字符串转成uint8_t
		uint8_t value = static_cast<uint8_t>(std::stoul(token, nullptr, 16));
		data.push_back(value);
	}
}

void Polling_By_Mloop(TestItemExecuteContext* aContext, const std::string pins, int polling_gap, int WaitDummy)
{

	std::vector<double> dut_polling_time(MAX_DUTS, 0); // 记录每个DUT的时间
	int dut_polling_count[MAX_DUTS] = { 0 }; // 每个DUT的 polling次数初始化为0
	int polling_time = 0;
	PST.Reset();
	int time_out_cnt;
	unsigned int RTCMAXC = 0;

	Digital.AFM.Config(12, 0, pins, ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
	Digital.AFM.SetResultMode(ENUM_OVERWRITE);
	Digital.AFM.ResetData(0x01);
	Digital.FMM.Clear();
	Digital.FMM.Config(pins, WaitDummy*50);

	Digital.Pattern.RunRegister("pPolling_Soft", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
	Digital.Pattern.RunModule("pPolling_Soft", "fPolling_Soft", ENUM_PATTERNSTOP_INTERRUPT, 60 S);

	DUT_LOOP_START
	Digital.FMM.GetRTC(dut, &RTCMAXC);
	//aContext->Info("Current Dut Retry Count:" + to_string(RTCMAXC));
	double oper_time;
	oper_time = RTCMAXC * 0.0301;//ms    200ns period: 30100ns;  

	if ((0 < RTCMAXC) && (RTCMAXC < WaitDummy*50))
	{
		(*item)->SetValue(0);// Pass
		//aContext->Info(to_string(dut) + "\t\t" + "pass\t\t" + to_string(oper_time) + "\t\tMS\t\t");
	}
	else
	{
		(*item)->SetValue(1);// Fail
		//aContext->Info(to_string(dut) + "\t\t" + "fail\t\t" + to_string(oper_time) + "\t\tMS\t\t");
	}
	PST.Polling_Count[dutz] = oper_time; //记录每个dut的时间
	DUT_LOOP_END
}


int Data_Compare_vsFF_User_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, int* get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, int DAC, bool IsEccOut)
{
	int ddw_dwfb_cnt = 0;                   // DDW中错误数量
	int byte_err_cnt = 0;                   // 错误位数量
	int last_byte = byte_limt;              // 总字节数
	char buf[500];							// ERR Log
	std::string output, outBuf;
	int opposite = 0xFF;					// CKB Opposite
	if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
	errflag->err_flags[TFB_LMT_FLAG] = 0;
	errflag->err_flags[DFB_LMT_FLAG] = 0;
	//DUTList* theDUTs = context->GetActiveDUTs();
	DUTList* theDUTArray = aContext->GetDUTs();
	// Print Log Head
#ifdef RRAM_B2_ERR_LOG
	//ETLog::Info("Start_Addr={:06X}h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
	//testlog.Info("Start_Addr={:06X}h, Byte Num={}, >>> Log Errors Only <<<", start_page, byte_limt);
     Print("Start_Addr=%06Xh, Byte Num=%d, >>> Log Errors Only <<<", start_page, byte_limt);
#endif


	 DUT_LOOP_START
	//for (auto itDUT : *theDUTs) {
		//int dut = itDUT->GetLocalID();
		//int SysDut = itDUT->GetSysID();
		int SysDut = (*item)->GetSysID();

		int print_error_cnt = 0;
		int start_page_count = start_page >> 7;
		errflag->error_cnt[dut-1] = 0;
		errflag->max_ddw_dwfb[dut-1] = 0;                   // DDW中错误数量最大值
		ddw_dwfb_cnt = 0;
		errflag->error_flags[dut-1][TFB_LMT_FLAG] = 0;
		errflag->error_flags[dut-1][DFB_LMT_FLAG] = 0;
		//	reset error flag to "0"(no error) of current dut	/*current dut mask*/	/*255 for 32-DUT*/
		errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));
		errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] & (((int)pow(2, MAX_DUTS) - 1) - (1 << (int)dut));

#ifdef RRAM_B2_ERR_LOG
		outBuf = "";		// 按DUT进行打印
		sprintf(buf, "[MEM_RD][DUT#%d] \t\t  Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F", SysDut);
		output = buf;
		outBuf += output;
#endif

		if (byte_limt > MAX_BYTE_NUM_FULL) last_byte = MAX_BYTE_NUM_FULL;
		/*if(target_byte_patt == 0x00){
			opposite = 0xFF;
		}
		else{
			opposite = 0x00;
		}*/
		for (int bytei = 0; bytei < last_byte; ++bytei)
		{
			/*if (bytei % 256 < 128) {
				if (bytei % 8 < 4 ){
					get_error_bit[bytei] = output_array[dut-1][bytei] ^ target_byte_patt;		//异或运算
				}
				else{
					get_error_bit[bytei] = output_array[dut-1][bytei] ^ opposite;				//异或运算
				}
			}
			else{
				if (bytei % 8 < 4 ){
					get_error_bit[bytei] = output_array[dut-1][bytei] ^ opposite;				//异或运算
				}
				else{
					get_error_bit[bytei] = output_array[dut-1][bytei] ^ target_byte_patt;		//异或运算
				}
			}*/

			get_error_bit[bytei] = output_array[dut-1][bytei] ^ target_byte_patt;		//异或运算
			byte_err_cnt = 0;
			for (int biti = 0; biti < 8; ++biti)
			{
				byte_err_cnt += (get_error_bit[bytei] >> biti) & 0x01;   //获取当前位的值
			}

			if (bytei % 6 == 0)
			{///// the 'ddw_dwfb_cnt' is effective in DDW only 
				// if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut-1]) { errflag->max_ddw_dwfb[dut-1] = ddw_dwfb_cnt; }  //2025.2.7
				ddw_dwfb_cnt = 0;
			}

			// Print ERR Data
#ifdef RRAM_B2_ERR_LOG
			print_error_cnt += byte_err_cnt;
			if (bytei % 16 == 15) {
				if (print_error_cnt > 0)
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
						SysDut, start_page_count, (bytei - 15) % 128, start_page_count, bytei % 128, get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12],
						get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;

					if ((bytei % 128 == 127) && (bytei != last_byte - 1))
					{
						outBuf += "\n";
					}
				}
				else if ((print_error_cnt == 0) && (bytei == last_byte - 1))
				{
					sprintf(buf, "\n[MEM_RD][DUT#%d] ERR  %04X%03X-%04X%03X: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
						SysDut, start_page_count, (bytei - 15) % 128, start_page_count, bytei % 128, get_error_bit[bytei - 15], get_error_bit[bytei - 14], get_error_bit[bytei - 13], get_error_bit[bytei - 12],
						get_error_bit[bytei - 11], get_error_bit[bytei - 10], get_error_bit[bytei - 9], get_error_bit[bytei - 8], get_error_bit[bytei - 7], get_error_bit[bytei - 6],
						get_error_bit[bytei - 5], get_error_bit[bytei - 4], get_error_bit[bytei - 3], get_error_bit[bytei - 2], get_error_bit[bytei - 1], get_error_bit[bytei]);
					output = buf;
					outBuf += output;
				}
				print_error_cnt = 0;
			}

			if ((bytei % 128 == 127) && (bytei > 0))
			{
				start_page_count++;
			}
#endif

			errflag->error_cnt[dut-1] += byte_err_cnt;
			ddw_dwfb_cnt += byte_err_cnt;

			// Do MaxVal Compare after counter increment  2025.2.7
			if (ddw_dwfb_cnt > errflag->max_ddw_dwfb[dut-1]) { errflag->max_ddw_dwfb[dut-1] = ddw_dwfb_cnt; }
		}
		if (errflag->error_cnt[dut-1] > TFB_Limit)
		{
			errflag->error_flags[dut-1][TFB_LMT_FLAG] = -1;
			errflag->err_flags[TFB_LMT_FLAG] = errflag->err_flags[TFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut-1][TFB_LMT_FLAG] = 1;
		}

		if (errflag->max_ddw_dwfb[dut-1] > DFB_Limit)
		{
			errflag->error_flags[dut-1][DFB_LMT_FLAG] = -1;
			errflag->err_flags[DFB_LMT_FLAG] = errflag->err_flags[DFB_LMT_FLAG] | (1 << (int)dut);
		}

		else
		{
			errflag->error_flags[dut-1][DFB_LMT_FLAG] = 1;
		}
		errflag->error_flags[dut-1][2] = errflag->error_cnt[dut-1];
		// Log Print
#ifdef RRAM_B2_ERR_LOG
// ETLog::Info(outBuf);
		//testlog.Info(outBuf);
		//Print(outBuf.c_str());
		aContext->Info(outBuf);
#endif
		if (IsEccOut)
		{
			//ETLog::Info(">>> dut# {} memory read error count >>> {} @ {:02x}h >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dut-1], DAC, errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			//testlog.Info(">>> dut# {} memory read error count >>> {} @ {:02x}h >>> TBF: 0x{:02x}, DBF: 0X{:02X}", SysDut, errflag->error_cnt[dut-1], DAC, errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
			Print(">>> dut# %d memory read error count >>> %d @ %02xh >>> TBF: 0x%02x, DBF: 0X%02X", SysDut, errflag->error_cnt[dut-1], DAC, errflag->err_flags[TFB_LMT_FLAG], errflag->err_flags[DFB_LMT_FLAG]);
		}
	DUT_LOOP_END
	return 1;
}
