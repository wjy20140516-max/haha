////////////////////////////////////////////////////////////////////////
#include <dlfcn.h>
#include "../include/OnlineTrim.h"

//=====================onlinetrim==============//
DynamicTrimM5 OlnTrim;
DynamicUniCode UniCusCOde;
TF_MRTRIMBUFF  MulSiteArch[MAX_DUTS];


DynamicTrimM5::DynamicTrimM5()
{
	//SiteContext* context;
	//std::string soRelatedPath = "so/libTaijiRdDynTrimV0.so";
	//std::string soFilePath = context->GetDataFile(soRelatedPath);
	//cDllFileName = soFilePath;
	char soFilePath[PATH_MAX];
	//string soRelatedPath = "CommRes/data/libCusnUID_V1p2c.so";
	//string soRelatedPath = "CommRes/data/libCusUIDV1p2d.so";
	string soRelatedPath = "CommRes/data/libTaijiRdDynTrimV0.so";


	getcwd(soFilePath, sizeof(soFilePath));
	Print("soFilePath : %s", soFilePath);

	string new_path = std::string(soFilePath).substr(0, std::string(soFilePath).find_last_of('/'));
	cDllFileName = std::string(new_path) + "/" + soRelatedPath;
}

DynamicTrimM5::~DynamicTrimM5()
{
	dlclose(hDllInstance);
}

void DynamicTrimM5::init()
{
	// 1. 查找并移除 "/build/lib" 子串
	size_t buildLibPos = cDllFileName.find("build/lib/CommRes/");
	if (buildLibPos != std::string::npos) {  // 确认找到该子串
		cDllFileName.erase(buildLibPos, strlen("build/lib/CommRes/"));  // 从找到的位置开始，删除子串（长度为~~）
	}
	Print("SO PATH : %s", cDllFileName.c_str());
	hDllInstance = dlopen(cDllFileName.c_str(), RTLD_LAZY);
	Print("*****************8xxxxxxx*************8");
	// output("<COLOR=Blue>\n ==> open dll hnd : %x  %s  path:\"%s\"</COLOR>", hDllInstance, (hDllInstance)?" ":vFormat("%d", GetLastError()), dll_path.c_str());
	// if (hDllInstance == NULL) fatal("!!! cannot open DLL file %s!!! ", dll_path.c_str()); ///// M2 logging func
	if (hDllInstance == NULL)
	{
		Print("!!! cannot open DLL file :%s !!!", dlerror());
	}
	else
	{
		Drv_FetUpdCRs = (DRV_FET)(dlsym(hDllInstance, "TF_GetTaggedCRs"));
	}

	if (Drv_FetUpdCRs == NULL)
	{
		Print("!!! cannot open DLL function of TF_GetTaggedCRs");
	}
	else
	{
		Drv_FetCrsRead = (DRV_FET_RDCRS)(dlsym(hDllInstance, "TF_GetArchUpdCRsArray"));
	}

	if (Drv_FetCrsRead == NULL)
	{
		Print("!!! cannot open DLL function of TF_GetArchUpdCRsArray");
	}
	else
	{
		Drv_FetMultiTrim = (DRV_FET_MULTRIM_DBL)(dlsym(hDllInstance, "TF_GetArchUpdCRsOrCode"));
	}
	if (Drv_FetMultiTrim == NULL)
	{
		Print("!!! cannot open DLL function of TF_GetArchUpdCRsOrCode");

	}
	Print("**************OnlineTrim DynamicTrimM5  So Open pass******************");
}

void DynamicTrimM5::ChangeDLL(std::string  cName)
{
	cDllFileName = cName;

	dlclose(hDllInstance);
}
void DynamicTrimM5::SetDLL(std::string cName)
{
	cDllFileName = cName;
}
std::string DynamicTrimM5::GetDLL()
{
	return cDllFileName;
}


DynamicUniCode::DynamicUniCode()
{
	//SiteContext* context;
	//std::string soRelatedPath = "so/libCusnUID_V1p2c.so";
	//std::string soFilePath = context->GetDataFile(soRelatedPath);
	//cDllFileName = soFilePath;
	char soFilePath[PATH_MAX];
	string soRelatedPath = "CommRes/data/libCusUIDV1p2d.so";
	getcwd(soFilePath, sizeof(soFilePath));

	Print("soFilePath : %s", soFilePath);


	string new_path = std::string(soFilePath).substr(0, std::string(soFilePath).find_last_of('/'));
	cDllFileName = std::string(new_path) + "/" + soRelatedPath;

}

DynamicUniCode::~DynamicUniCode()
{
	dlclose(hDllInstance);
}

void DynamicUniCode::init()
{
	// ETLog::Info("path {}", cDllFileName);

		// 1. 查找并移除 "/build/lib" 子串
	size_t buildLibPos = cDllFileName.find("build/lib/CommRes/");
	if (buildLibPos != std::string::npos) {  // 确认找到该子串
		cDllFileName.erase(buildLibPos, strlen("build/lib/CommRes/"));  // 从找到的位置开始，删除子串（长度为~~）
	}
	Print("SO PATH : %s", cDllFileName.c_str());


	hDllInstance = dlopen(cDllFileName.c_str(), RTLD_LAZY);

	Print("*****************9xxxxxxx*************9");
	// output("<COLOR=Blue>\n ==> open dll hnd : %x  %s  path:\"%s\"</COLOR>", hDllInstance, (hDllInstance) ? " " : vFormat("%d", GetLastError()), dll_path.c_str());
	if (hDllInstance == NULL)
	{
		Print("!!! cannot open DLL file :%s !!!", dlerror());
	}
	else
	{
		Gen_GetCusUniCode = (UNI_GET_CUSUNICODE)(dlsym(hDllInstance, "RmGetUniCode"));
	}
	if (Gen_GetCusUniCode == NULL)
	{
		Print("!!! cannot open DLL function of RmGetUniCode");
	}
	// else
	// {
	// 	ETLog::Info("Gen_GetCusUniCode adress: {}",reinterpret_cast<void*>(Gen_GetCusUniCode));
	// }
	Print("**************OnlineTrim DynamicUniCode So Open pass******************");
}

void DynamicUniCode::ChangeDLL(std::string  cName)
{
	cDllFileName = cName;

	dlclose(hDllInstance);
}
void DynamicUniCode::SetDLL(std::string cName)
{
	cDllFileName = cName;
}
std::string DynamicUniCode::GetDLL()
{
	return cDllFileName;
}

