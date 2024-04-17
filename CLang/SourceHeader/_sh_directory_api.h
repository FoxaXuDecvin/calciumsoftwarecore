//Directory API
// Copyright FoxaXu 2024

#include "../SourceHeader/include.h"

//DEF
bool _fileapi_createmark(string File, string info);
int _get_random(int min, int max);


//MAIN
bool _dapi_ExistFolder_check(string dir) {
	string tmpDoct = dir + pathsign + "test~" + to_string(_get_random(1, 999999)) + "~.mark";

	if (_fileapi_createmark(tmpDoct, "nWn")) {
		remove(tmpDoct.c_str());
		return true;
	}
	else {
		remove(tmpDoct.c_str());
		return false;
	}
}

bool _dapi_rmdir(string dir) {
	dir = ReplaceChar(dir, "\\", "/");

	removeDirectoryAPIX(dir.c_str());

	//cout << "Remove Directory :  " << dir << endl;

	if (_dapi_ExistFolder_check(dir)) {
		return false;
	}
	else {
		return true;
	}
}

bool _dapi_mkdir(string dir) {
	dir = ReplaceChar(dir, "\\", "/");

	foldercreateapi(dir.c_str());

	//cout << "Remove Directory :  " << dir << endl;

	if (_dapi_ExistFolder_check(dir)) {
		return true;
	}
	else {
		return false;
	}
}