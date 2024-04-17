// Http/Https Download Toolkit
// Base System API
// Copyright FoxaXu 2024

#include "../SourceHeader/include.h"


bool _$BufferCache;

//URLDown

//return True/False  =   result
bool _urldown_api(string url, string savepath) {
	//Disabled Cache
	_$BufferCache = URLDown(url, savepath);

	//Decide
	if (check_file_existenceA(savepath)) {
		return true;
	}
	else {
		return false;
	}

	//No Code
}

bool _urldown_api_nocache(string url, string savepath) {
	url = url + "?voidcache=" + _get_random_s(1, 10000);
	//Disabled Cache
	_$BufferCache = URLDown(url, savepath);

	//Decide
	if (check_file_existenceA(savepath)) {
		return true;
	}
	else {
		_sh_throw_error("OpenHttp.Error :  Failed to Get URL :   " + url);
		return false;
	}

	//No Code
}

//END