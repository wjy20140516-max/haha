//// Driver.cpp: CDriver 
#include <dlfcn.h>
#include "../include/Driver.h"

CDriver TheDevice;

unsigned int curr_crs[128] = {

	0x00,0X00,0X00,0X00,  0X00,0x00,0X00,0X00,  0X00,0X00,0X00,0X00,  0x00,0X00,0X00,0X00,
	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00,  0x00,0x00,0x00,0x00

};

CDriver::CDriver()
{
	char soFilePath[PATH_MAX];
	//SiteContext* context;
	std::string soRelatedPath = "CommRes/data/libTaijiRdDynTrimV0.so";
	          //std::string soRelatedPath = "so/libTaijiRdDynTrimV0.so";
	//std::string soRelatedPath = "CommRes/build/libNCATest.so";
	getcwd(soFilePath, sizeof(soFilePath));
	Print("soFilePath : %s", soFilePath);

	//std::string soFilePath = context->GetDataFile(soRelatedPath);
	//cSoFileName = soFilePath;
	std::string new_path = std::string(soFilePath).substr(0, std::string(soFilePath).find_last_of('/'));

	cSoFileName = std::string(new_path) + "/" + soRelatedPath;
	//Print("SO PATH : %s", cSoFileName.c_str());


	//SiteContext* context;
	//std::string soRelatedPath = "so/libTaijiRdDynTrimV0.so";
	//std::string soFilePath = context->GetDataFile(soRelatedPath);
	//cSoFileName = soFilePath;


}
CDriver::~CDriver()
{
	dlclose(hSoInstance);

}
void CDriver::init()
{

    // 1. 查找并移除 "/build/lib" 子串
    size_t buildLibPos = cSoFileName.find("build/lib/CommRes/");
    if (buildLibPos != std::string::npos) {  // 确认找到该子串
    cSoFileName.erase(buildLibPos, strlen("build/lib/CommRes/"));  // 从找到的位置开始，删除子串（长度为~~）
     }
    Print("SO PATH : %s", cSoFileName.c_str());
	//Print("*****************7xxxxxxx*************7");
	hSoInstance = dlopen(cSoFileName.c_str(), RTLD_LAZY);
	if (hSoInstance == NULL) {
		const char* err = dlerror();
		if (err) {
			std::cerr << "dlopen失败：" << err << std::endl;
		}
		else {
			std::cerr << "dlopen失败，无具体错误信息" << std::endl;
		}
		Print("So Open Failed :%s", dlerror());
	}
	else {
		Drv_FetUpdCRs = (DRV_FET)(dlsym(hSoInstance, "TF_GetTaggedCRs"));
		Drv_FetUpdMemCode = (DRV_FET_DIRC)(dlsym(hSoInstance, "TF_GetTaggedInitCode"));
		Drv_FetCrsRead = (DRV_FET_RDCRS)(dlsym(hSoInstance, "TF_GetArchUpdCRsArray"));
		Drv_FetMultiTrim = (DRV_FET_MULTRIM)(dlsym(hSoInstance, "TF_GetArchUpdCRsOrCode"));
		Print("*************cd driver So Open pass**********************8");
	}
}

void CDriver::ChangeSO(std::string  cName)
{
	cSoFileName = cName;

	dlclose(hSoInstance);
}
void CDriver::SetSO(std::string cName)
{
	cSoFileName = cName;
}
std::string CDriver::GetSO()
{
	return cSoFileName;
}
//==========================================================//
