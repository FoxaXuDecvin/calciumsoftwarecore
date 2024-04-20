// Set Var in here

#include"../SourceHeader/include.h"

using namespace std;;


//Set Var

int aaa = 1;

//const

const string ver_bd = "Build";
const string ver_beta = "Beta";
const string ver_rl = "Release";
const string ver_sd = "Stable";
const string ver_sdlts = "Stable (LTS)";

//int 1 = const string ver_bd = "Build";
//int 2 = const string ver_beta = "Beta";
//int 3 = const string ver_rl = "Release";
//int 4 = const string ver_sd = "Stable";
//int 5 = const string ver_sdlts = "Stable (LTS)";
//int 5+ = Modify";
int VerSignID = 0;

//set over 0-5 to return Modify
string getversign() {
	if (VerSignID == 0)return "( VSID not set on Code/example.h . Please contact developer to fill this int VerSignID )";
	if (VerSignID == 1)return ver_bd;
	if (VerSignID == 2)return ver_beta;
	if (VerSignID == 3)return ver_rl;
	if (VerSignID == 4)return ver_sd;
	if (VerSignID == 5)return ver_sdlts;

	return "Modify";
}

//build

string rlib_c;
string rc_name, rc_auther;
string rc_sysrun;
string rc_args;

string rc_run;

int rc_result_exit;

string sfid_ver;

string rtlist_prf;

string rtlist_rtp;

string dlbuffer;

string $quomark = "\"";
string $sqmark = "\'";

string araBuffer;

string defserver;

string upd_cache;