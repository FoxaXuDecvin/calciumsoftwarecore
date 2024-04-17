//Switch Tools
#pragma once
#include "../SourceHeader/include.h"
using namespace std;

//Message
string $_pause = "Press Enter...   ";

string _swt_buffer;

//Main
void _pause() {
	printf($_pause.c_str());
	getchar();
	return;
}

string _getline_type(void) {
	getline(cin, _swt_buffer);
	return _swt_buffer;
}