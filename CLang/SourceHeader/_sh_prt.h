//Print Advanced
#pragma once
#include "../SourceHeader/include.h"
using namespace std;

void _prtoutmsg(string message) {
	printf(message.c_str());
	printf("\n");
	return;
}

void _prts(string message) {
	printf(message.c_str());
	return;
}

void _prtendl(void) {
	printf("\n");
	return;
}

void _coutmsg(string message) {
	cout << message << endl;
	return;
}