#pragma once

#include"../shload.h"

//Args API
//format
//         [cl] <run/install> <softwareid> </no_launchscreen> </loadmode>

int argslonger = 0;
int runmode = -1;
string rtpath = "runtools/";
string runlib = "runlib/";
string rtemp = "temp/";
string netlib = "netlib/";
string rtappdata = "rtappdata/";

string lbtemp = "def";

bool displayLaunchScreen = true;

string sfid = "def";

void outcmdHelp() {
	_prtoutmsg("	        [cl] <run/install/uninstall/update> <softwareid> </no_launchscreen> </loadmode>");
}

void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	if (args$api == "run") {
		argslonger++;
		runmode = 1001;
		return;
	}

	if (args$api == "install") {
		argslonger++;
		runmode = 1002;
		return;
	}

	if (args$api == "uninstall") {
		argslonger++;
		runmode = 1003;
		return;
	}

	if (args$api == "update") {
		argslonger++;
		runmode = 1004;
		return;
	}

	if (args$api == "test_nullint") {
		argslonger++;
		runmode = 666;
		return;
	}

	if (args$api == "no_launchscreen") {
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
	if (_dapi_ExistFolder_check(netlib)) {
		_dapi_mkdir(netlib);
		if (!_urldown_api_nocache("https://calcium.foxaxu.com/cw_tsc/rt.txt", rtlist_local)) {
			_prtendl();
			_prtendl();
			_prtoutmsg("Failed to get software list");
			_prtoutmsg("Software :  " + sfid);
			_prtoutmsg("	        Check your internet and try again");
			return 4004;
		}
	}

	_prtoutmsg("Searching ...");
	rtlist_prf = _load_sipcfg(rtlist_local, sfid);

	rtlist_rtp = runlib + "/" + sfid + ".txt";
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
		dlbuffer = "./BatchDownloadScript \"local\" \"" + rtlist_rtp + "\" \"" + rtpath + "\"";
		system(dlbuffer.c_str());
	}

	return 0;
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
	rtlist_local = netlib + "/" + "rtlist.txt";
	if (!_dapi_ExistFolder_check("temp")) {
		_prtoutmsg("Press Enter to Setup Calcium ");

		_pause();

		_dapi_mkdir(rtpath);
		_dapi_mkdir(runlib);
		_dapi_mkdir(rtemp);
		_dapi_mkdir(netlib);
		_dapi_mkdir(rtappdata);

		_urldown_api("https://calcium.foxaxu.com/appcore/BatchDownloadScript.exe", "BatchDownloadScript.exe");
	}
	if (runmode == -1) {
		_prtoutmsg("Calcium Software Core ");
		_prtoutmsg("format ");
		outcmdHelp();
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
		
		rtlist_prf = _load_sipcfg(rtlist_local, sfid);

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

	_prtoutmsg("null \"int runmode =  " + to_string(runmode) + "\" to running this app. Please report for developer");
	return 0;
}