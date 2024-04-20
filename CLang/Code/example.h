// WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
// HELLO WORLD
//Copyright FoxaXu
//Calcium Core Service

//FoxaXuDecvin
// 2024.4.18

//Follow Me
// BiliBili:   https://space.bilibili.com/1426318422
// Github: https://github.com/FoxaXuDecvin
// site:      https://www.foxaxu.com   &&   https://www.foxaxu.top
// ....

#pragma once

#include"../shload.h"

//String Version
int ccversion = 1002;

//Args API
//format
//         goto outcmdHelp

int argslonger = 0;
int runmode = -1;

string ccversion_str = to_string(ccversion);

string cfg_load = "calcium_config.cfg";
string rtpath = "runtools/";
string runlib = "runlib/";
string rtemp = "temp/";
string rtappdata = "rtappdata/";

string lbtemp = "def";

bool displayLaunchScreen = true;

string sfid = "def";

void outcmdHelp() {
	_prtoutmsg("	        [cl] -<run/install/uninstall/update/coreupdate> <softwareid> </no_launchscreen> </loadmode>");
}

void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	if (args$api == "-run") {
		argslonger++;
		runmode = 1001;
		return;
	}

	if (args$api == "-install") {
		argslonger++;
		runmode = 1002;
		return;
	}

	if (args$api == "-uninstall") {
		argslonger++;
		runmode = 1003;
		return;
	}

	if (args$api == "-update") {
		argslonger++;
		runmode = 1004;
		return;
	}

	if (args$api == "-coreupdate") {
		argslonger++;
		runmode = 10041;
		return;
	}

	if (args$api == "-test_nullint") {
		argslonger++;
		runmode = 666;
		return;
	}

	if (args$api == "-no_launchscreen") {
		argslonger++;
		displayLaunchScreen = false;
		return;
	}

	argslonger++;
	if (sfid == "def") {
		sfid = args$api;
	}
	else {
		if (lbtemp == "def") {
			lbtemp = args$api;
		}
	}

	return;
}

string get_os_runfile() {
	if (_Run_SysKernel == "Win32") {
		return _load_sipcfg(rlib_c, "launch_w");
	}
	if (_Run_SysKernel == "Linux") {
		return _load_sipcfg(rlib_c, "launch_n");
	}

	return "unkOS";
}

bool cp_true = false;
bool RemoveSFAPI(string fileaddress) {
	string tempdata, outdata;

	if (checkChar(fileaddress, "/")) cp_true = true;
	if (checkChar(fileaddress, "\\")) cp_true = true;

	if (cp_true == false) {
		return true;
	}

	fileaddress = ReplaceChar(fileaddress, "\\", "/");

	int numbuffer = fileaddress.size();
	int baseNum = -1;

	while (true) {
		tempdata = fileaddress[numbuffer];
		if (tempdata == "/") break;
		numbuffer--;
	}
	numbuffer--;
	while (baseNum != numbuffer) {
		baseNum++;
		outdata = outdata + fileaddress[baseNum];
	};

	if (checkChar(outdata, "/")) RemoveSFAPI(outdata);
	if (outdata == "runtools") {
		return true;
	}
	_dapi_rmdir(outdata);
	return true;

}

bool removeSoftwareAPi(string sfid_m) {
	rlib_c = runlib + "/" + sfid_m + ".txt";
	dlbuffer = get_os_runfile();
	if (dlbuffer == "unkOS") {
		_prtoutmsg("Error Failed to uninstall " + sfid_m + ". we did not found profile to uninstall");
		return false;
	}
	RemoveSFAPI("runtools/" + dlbuffer);
	_fileapi_del(rlib_c);

	return true;
}

int InstallSoftwareAPI() {
	rtlist_prf = defserver  + sfid + ".txt";

	rtlist_rtp = runlib + "/" + sfid + ".txt";
	_prtoutmsg("Get SFID Profile from £º  " + rtlist_prf);

	if (!_urldown_api_nocache(rtlist_prf, rtlist_rtp)) {
		_prtendl();
		_prtendl();
		_prtoutmsg("Failed to get sfid      -software id");
		_prtoutmsg("Software :  " + sfid);
		_prtoutmsg("	        Check your internet and try again");
		return 4004;
	}

	_prtoutmsg("Start Download ....   ");

	if (_Run_SysKernel == "Win32") {
		dlbuffer = "BatchDownloadScript.exe \"local\" \"" + rtlist_rtp + "\" \"" + rtpath + "\"";
		system(dlbuffer.c_str());
	}
	if (_Run_SysKernel == "Linux") {
		dlbuffer = "./BatchDownloadScript.lux \"local\" \"" + rtlist_rtp + "\" \"" + rtpath + "\"";
		system(dlbuffer.c_str());
	}

	return 0;
}

bool UpdateCore() {
	if (VerSignID == 1) {
		_prtoutmsg("Warning you are using Build Version.");
		_prtoutmsg("This version is for compilation testing and is not a release version");
		_prtoutmsg("If you're not a tester, you shouldn't get this release");
		_prtoutmsg("We can only help you update to the release version");
		_prtendl();
	}

	upd_cache = _load_sipcfg(cfg_load, "coreurl");

	if (!_urldown_api_nocache(_load_sipcfg(cfg_load, "coreupd"), "coreupd.tmp")) {
		_prtoutmsg("Failed to connect server.");
		_prtoutmsg("Server URL :  " + _load_sipcfg(cfg_load, "coreupd"));
		_prtendl();
		return false;
	}

	if (ccversion_str == _fileapi_textread("coreupd.tmp", 1)) {
		_prtoutmsg("Calcium Software Core is latest version");
		return true;
	}

	_prtoutmsg("Please wait a moment We are updating Calcium Software Core");

	rename("Calcium.exe", "Calcium-old.exe");
	rename("Calcium.lux", "Calcium-old.lux");
	_fileapi_del("coreupd.tmp");

	if (!_urldown_api_nocache(_load_sipcfg(cfg_load, "coreurl") + "Calcium.exe.txt", "Calcium.exe")) {
		_prtoutmsg("Failed to connect server.");
		_prtoutmsg("Server URL :  " + _load_sipcfg(cfg_load, "coreupd"));
		_prtendl();
		return false;
	}
	if (!_urldown_api_nocache(_load_sipcfg(cfg_load, "coreurl") + "Calcium.lux.txt", "Calcium.lux")) {
		_prtoutmsg("Failed to connect server.");
		_prtoutmsg("Server URL :  " + _load_sipcfg(cfg_load, "coreupd"));
		_prtendl();
		return false;
	}

	return true;
}

int AppRunAuto(string file, string arguments) {
	if (_Run_SysKernel == "Win32") {
		file = ReplaceChar(file, "/", "\\");
		araBuffer = $quomark + file + $quomark + " " + arguments;
		return system(araBuffer.c_str());
	}
	if (_Run_SysKernel == "Linux") {
		file = ReplaceChar(file, "\\", "/");
		araBuffer = $sqmark + file + $sqmark + " " + arguments;
		return system(araBuffer.c_str());
	}

	return 999;
}

//Put Code Here
//RunMode
// -1 Not Set
// 1001 Run
// 1002 Install
// 1003 Uninstall
// 1004 Update
int _HeadMainLoad() {

	VerSignID = 1;

	if (!check_file_existence(cfg_load)) {
		_prtoutmsg("Press Enter to Setup Calcium ");

		_pause();

		_dapi_mkdir(rtpath);
		_dapi_mkdir(runlib);
		_dapi_mkdir(rtemp);
		_dapi_mkdir(rtappdata);

		_fileapi_createmark(cfg_load, "//Calcium Config Profile");
		_write_sipcfg(cfg_load, "CurrentVersion", ccversion_str);
		_write_sipcfg(cfg_load, "geturl", "https://calciumservices.foxaxu.com/CCore/cc_list/");
		_write_sipcfg(cfg_load, "coreupd", "https://calciumservices.foxaxu.com/CCore/core_version.txt");
		_write_sipcfg(cfg_load, "coreurl", "https://calciumservices.foxaxu.com/CCore/core/");
		_prtoutmsg("Downloading..   BatchDownloadScript");
		_urldown_api("https://dl.foxaxu.com/chfs/shared/calcium/appcore/BatchDownloadScript.exe?v=1", "BatchDownloadScript.exe");
		_urldown_api("https://dl.foxaxu.com/chfs/shared/calcium/appcore/BatchDownloadScript.lux?v=1", "BatchDownloadScript.lux");

		_prtoutmsg("Create New Config ... ");
	}

	if (check_file_existence("Calcium-old.exe")) {
		_fileapi_del("Calcium-old.exe");
	}
	if (check_file_existence("Calcium-old.lux")) {
		_fileapi_del("Calcium-old.lux");
	}
	//Load Config
	_prtendl();
	_prtendl();

	defserver = _load_sipcfg(cfg_load, "geturl");

	if (_load_sipcfg(cfg_load, "CurrentVersion") != ccversion_str) {
		_prtoutmsg("This Profile is used for old calcium version");
		_prtoutmsg("If the program appears error. Please delete " + ccversion_str);
		_pause();

		cleanConsole();
	}

	if (runmode == -1) {
		_prtoutmsg("Calcium Software Core ");
		_prtoutmsg("Based on OpenCLT ");
		_prtoutmsg("Version :  " + ccversion_str + "  " + getversign() + " (" + to_string(VerSignID) + ") .");
		_prtoutmsg("Github :  https://github.com/FoxaXuDecvin/calciumsoftwarecore");
		_prtoutmsg(" command format :  ");
		outcmdHelp();
		_prtendl();
		return 4004;
	}
	if (runmode == 1001) {

		rlib_c = runlib + "/" + sfid + ".txt";

		if (!check_file_existence(rlib_c)) {
			_prtoutmsg("No runid on runlib ");
			_prtoutmsg("File :  " + rlib_c);
			_prtoutmsg("format ");
			outcmdHelp();
			return 4004;
		}

		rc_name = _load_sipcfg(rlib_c, "TaskName");
		rc_auther = _load_sipcfg(rlib_c, "auther");
		rc_args = _load_sipcfg(rlib_c, lbtemp);
		sfid_ver = _load_sipcfg(rlib_c, "sfid_ver");
		
		rc_sysrun = get_os_runfile();

		if (rc_sysrun == "unkOS") {
			_prtendl();
			_prtendl();
			_prtoutmsg("No Support your system ");
			_prtoutmsg("Software :  " + rc_name + " (" + rc_auther + ")");
			_prtoutmsg("Calcium Version :   " + _Run_SysKernel);
			_prtoutmsg("	        Try to install other version");
			outcmdHelp();
			return 4004;
		}

		rc_sysrun = rtpath + rc_sysrun;

		if (!check_file_existence(rc_sysrun)) {
			_prtendl();
			_prtendl();
			_prtoutmsg("This software is corrupted");
			_prtoutmsg("Missing File :  " + rc_sysrun);
			_prtoutmsg("Software :  " + rc_name + " (" + rc_auther + ")");
			_prtoutmsg(" Run install command and try again");
			outcmdHelp();
			return 4004;
		}

		rc_run = rc_sysrun + " " + rc_args;
		if (displayLaunchScreen == true) {
			cleanConsole();
			_prtoutmsg(" Launching ... ");
			_prtendl();
			_prtendl();
			_prtoutmsg("     " + rc_name + "   " + sfid_ver);
			_prtendl();
			_prtoutmsg("console:  " + rc_run);
			_prtoutmsg("     _" + rc_auther + "_");
			sleepapi(2);
		}

		rc_result_exit = AppRunAuto(rc_sysrun, rc_args);

		if (rc_result_exit == 0) {
			return 0;
		}
		else {
			_prtendl();
			_prtendl();
			_prtendl();
			_prtoutmsg("The software has stopped working ... ");
			_prtoutmsg("But there is a suspected collapse ... ");
			_prtoutmsg("Error Code :     " + to_string(rc_result_exit));
			_prtendl();
			_prtoutmsg("Software: " + rc_name);
			_prtoutmsg("Version: " + sfid_ver);
			_prtoutmsg("console:   " + rc_run);
			_prtoutmsg("Calcium Tools    ... Please report it to _" + rc_auther + "_");
			_pause();
		}

		return 0;
	}
	if (runmode == 1002) {
		
		InstallSoftwareAPI();

		_prtoutmsg(" Complete...");
		_prtoutmsg(" Use               [Calcium] run " + sfid + " </no_launchscreen>");
		_prtoutmsg(" Press any key to exit");

		_pause();

		return 0;
	}
	if (runmode == 1003) {
		if (removeSoftwareAPi(sfid)) {
			_prtoutmsg("Software: " + sfid + "  is successfully to remove from your calcium");
		}
		else {
			_prtoutmsg("Software: " + sfid + "  is failed to remove from your calcium");
		}
		return 0;
	}
	if (runmode == 1004) {
		rlib_c = runlib + "/" + sfid + ".txt";

		if (!check_file_existence(rlib_c)) {
			_prtoutmsg("No runid on runlib ");
			_prtoutmsg("File :  " + rlib_c);
			_prtoutmsg("format ");
			outcmdHelp();
			return 4004;
		}

		rc_name = _load_sipcfg(rlib_c, "TaskName");
		rc_auther = _load_sipcfg(rlib_c, "auther");
		rc_args = _load_sipcfg(rlib_c, lbtemp);
		sfid_ver = _load_sipcfg(rlib_c, "sfid_ver");

		_fileapi_CpFile(rlib_c, rlib_c + "-old");
		_fileapi_del(rlib_c);

		rtlist_prf = defserver + sfid + ".txt";

		if (!_urldown_api_nocache(rtlist_prf, rlib_c)) {
			_fileapi_CpFile(rlib_c + "-old", rlib_c);
			_prtendl();
			_prtendl();
			_prtoutmsg("Failed to get sfid      -from server");
			_prtoutmsg("Software :  " + sfid);
			_prtoutmsg("Update Failed");
			return 4004;
		}
		_fileapi_del(rlib_c + "-old");


		if (_load_sipcfg(rlib_c, "sfid_ver") == sfid_ver) {
			_prtoutmsg("This software is latest version ");
			_prtoutmsg("complete ");
			return 1004;
		}

		_prtoutmsg("Update " + rc_name + "  .---   " + sfid_ver + "  to  " + _load_sipcfg(rlib_c, "sfid_ver"));
		_prtoutmsg("Remove old file");


		removeSoftwareAPi(sfid);
		InstallSoftwareAPI();
		sfid_ver = _load_sipcfg(rlib_c, "sfid_ver");
		_prtendl();
		_prtoutmsg("Now ..This software is latest version ---  " + sfid_ver);
		_prtoutmsg("Update Complete");
		return 0;
	}
	if (runmode == 10041) {
		if (UpdateCore()) {
			_prtoutmsg("Update Complete");
			return 0;
		}
		else {
			_prtoutmsg("Update Failed");
			return 0;
		}
	}
	
	_prtoutmsg("null \"int runmode =  " + to_string(runmode) + "\" to running this app. Please report for developer");
	return 0;
}