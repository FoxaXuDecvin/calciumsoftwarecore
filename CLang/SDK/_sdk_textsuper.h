//Based on Old Project CalciumRunPlatfom
//SDK  TextSuper

#pragma once
#include"../shload.h"

using namespace std;
//TEXT READ

string readbufferA, readbufferB, readbufferC, readbufferD;
int numbuffer;

//COPYRIGHT FOXAXU SOFTWARE TEAM
// Text command Process
// Cpp Includer


//Only Support Read 1 Char Size,Read Size A"B$C "+$ = B
bool check_file_existence(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        return true;
    } else {
        return false;
    }
}

//Read Env NEW
string PartRead(string Info, string StartMark, string EndMark) {
	int MaxInfoSize = Info.size();
	int startmarkadd, endmarkadd,readptr;
	string readbufferPR;
	readptr = 0;

	if (StartMark == "$FROMSTART$") {
		startmarkadd = 0;
		goto SKIPGETMARKSTART;
	}

	//GetStart
	for (; readbufferPR != StartMark; readptr++) {
		if (readptr > MaxInfoSize) {
			//cout << "Message :  " << Info << endl;
			return "notfoundstart :  " + Info;
		}
		readbufferPR = Info[readptr];
	}
	
	startmarkadd = readptr;

	SKIPGETMARKSTART:
	readbufferPR = "";
	//GetEnd
	if (EndMark == "$FROMEND$") {
		endmarkadd = MaxInfoSize;
		goto skipENDGET;
	}
	for (; readbufferPR != EndMark; readptr++) {
		if (readptr > MaxInfoSize) {
			return "notfoundEnd :  " + Info;
		}
		readbufferPR = Info[readptr];
	}

	endmarkadd = readptr;
	endmarkadd--;

	skipENDGET:
	//cout << "Start :  " << startmarkadd << "  End :  " << endmarkadd << endl;

	//Start Process CMD

	//ReadPTR
	readbufferPR = "";
	for (readptr = startmarkadd; readptr != endmarkadd; readptr++) {
		readbufferPR = readbufferPR + Info[readptr];
	}

	return readbufferPR;
}

int PartSizeA;
//Read Env NEW PART
//Use StartMark
string PartReadA(string Info, string StartMark, string EndMark,int RPartSizeA) {
	//Anti Search All
	if (RPartSizeA == 1) {
		return PartRead(Info, StartMark, EndMark);
	}

	int MAXSIZEA = Info.size();
	int readptr = 0;
	PartSizeA = RPartSizeA;
	int cbuffer = 0;

	int getStart, getEnd , getcurrent = 0;

	//FindStart
	if (StartMark == EndMark) {
		PartSizeA = PartSizeA * 2;
		PartSizeA--;
		PartSizeA--;
	}

	while (PartSizeA != getcurrent) {
		for (; readbufferC != StartMark; readptr++) {
			readbufferC = Info[readptr];
			if (readbufferC == StartMark) {
				getcurrent++;
			}
			//cout << "Read :  " << readptr << "Data :  " << readbufferC << endl;
			if (readptr > MAXSIZEA)return "pra.failed mark";
		}
		
		//cout << "A :  " << readbufferC << "  B :  " << getcurrent << endl;
		readbufferC = "";
	}
	//cout << "Start :  " << readptr << "  PartSA :  " << PartSizeA << endl;

	//GetStart
	for (; readbufferD != StartMark; readptr++) {
		if (readptr > MAXSIZEA) {
			return "sizeoutStart";
		}
		readbufferD = Info[readptr];
	}

	getStart = readptr;
	//cout << "Start Mark : " << getStart << endl;

SKIPGETMARKSTART:
	readbufferD = "";
	//GetEnd
	for (; readbufferD != EndMark; readptr++) {
		if (readptr > MAXSIZEA) {
			return "sizeoutEnd";
		}
		readbufferD = Info[readptr];
	}

	getEnd = readptr;

	//cout << "Start :  " << getStart<< "  End :  " << getEnd << endl;

	//Start Process CMD

	//ReadPTR
	readbufferD = "";
	getEnd--;
	for (readptr = getStart; readptr != getEnd; readptr++) {
		readbufferD = readbufferD + Info[readptr];
	}

	return readbufferD;

}


//ReadSize
// FoxaXu good work 3 = Fox
string SizeRead(string Info, int Size) {
	if (Size > Info.size()) {
		return "SizeRead.OverSize";
	}

	string TempInfo;
	for (int ReadCharSize = 0; ReadCharSize != Size; ReadCharSize++) {
		TempInfo = TempInfo + Info[ReadCharSize];
	}

	return TempInfo;
}

//Read Size from End
// This is FoxaXu 4=xaXu
string EndSizeRead(string Info, int LateSize) {
	int InfoSize = Info.size();
	int EndAddress = InfoSize - LateSize;
	if (EndAddress < 0) {
		return "EndSizeRead.LateSizeOverSmall";
	}
	string TempInfo,ReadChar;

	for (int LateRead = InfoSize; LateRead != EndAddress; LateRead--) {
		ReadChar = Info[LateRead];
		TempInfo = TempInfo + ReadChar;
	}

	return TempInfo;
}

//Get Char Address int
// ABC$DEFG$
int TextGetSizeAddress(string Info, string MarkSize, int NumBit) {
	int MaxSizeInfo = Info.size();
	int CurrentNumBit = 0;
	int StartRead = 0;
	string TempInfo, charRead;

	while (CurrentNumBit != NumBit) {
		for (int EndRead; charRead != MarkSize; StartRead++) {
			charRead = Info[StartRead];
		}
		CurrentNumBit++;
	}

	return StartRead;
}

//Char Size Read
//Example ABCDEFG S=C E=F DE
string PartReadSize(string Info, int StartSize, int EndSize) {
	StartSize--; EndSize--;
	int MaxInfoSize = Info.size();
	if (StartSize > EndSize) {
		return "PartReadSize.StartOverThanEnd";
	}
	if (StartSize == EndSize) {
		return "";
	}
	if (EndSize > MaxInfoSize) {
		return "PartReadSize.EndSizeOverMaxinfo";
	}
	int CurrentSize = StartSize;

	string TempInfo, charRead;
	while (CurrentSize <= EndSize) {
		charRead = Info[CurrentSize];
		TempInfo = TempInfo + charRead;
		CurrentSize++;
	}

	return TempInfo;
}


//Read LineSize
//Like : 
//
//      #Calcium
//      BEFORE
//      FOXAXU
//      After
//
//Read  :
//
//      LineReader(ExampleFile,3) return FOXAXU
string LineReader(string File, int line_number) {
	if (check_file_existence(File)) {}else {
		return "FileNotExist";
	}
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(File.c_str());
	lines = CountLines(File);

	if (line_number <= 0)
	{
		cout << "File :  " << File << endl;
		cout << "LineError :  " << line_number << endl;
		return "LineError";
	}
	if (file.fail())
	{
		return "ReadFailed";
	}
	if (line_number > lines)
	{
		return "overline";
	}
	while (getline(file, temp) && i < line_number - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

//NoError
string LineReader_noerror(string File, int line_number) {
	if (check_file_existence(File)) {}
	else {
		return "FileNotExist";
	}
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(File.c_str());
	lines = CountLines(File);

	if (line_number <= 0)
	{
		return "LineError";
	}
	if (file.fail())
	{
		return "ReadFailed";
	}
	if (line_number > lines)
	{
		return "overline";
	}
	while (getline(file, temp) && i < line_number - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

string cutlineblockA(string lines, string cutmark, int line) {
	string backapi;

	if (checkChar(lines, cutmark) == 0) {
		return "NUL";
	}

	char* readcut = NULL;

	char Texts[65535] = "a";
	char CUMark[65535] = "a";

	strcpy(Texts, lines.c_str());
	strcpy(CUMark, cutmark.c_str());

	int cutrecord = 1;
	char* token = strtok(Texts, CUMark);
	if (token == NULL) {
		backapi = "";
		return backapi;
	}

	if (cutrecord == line) {

		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}

NextRollCR:
	if (cutrecord == line) {
		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}
	if (token == NULL) {
		backapi = "";
		return backapi;
	}
	cutrecord++;
	token = strtok(NULL, CUMark);
	goto NextRollCR;
}

string HeadSpaceClean(string Info) {
	int maxCSize = Info.size();
	if (maxCSize == -1) {
		return "";
	}
	string readMCS, tempInfo;
	int currentFit;

	//cout << "Max C Size :  _" << maxCSize << endl;
	for (currentFit = 0; currentFit < maxCSize; currentFit++) {
		readMCS = Info[currentFit];
		//cout << "Read MCS :  _" << readMCS << endl;
		if (readMCS == " ") {}
		else {
			while (currentFit < maxCSize) {
				//cout << "Trans Add : _" << Info[currentFit] << endl;
				tempInfo = tempInfo + Info[currentFit];
				currentFit++;
			}
		}
	}
	return tempInfo;
}

string HeadSpaceCleanA(string Info) {
	int maxCSize = Info.size();
	string readMCS, tempInfo;
	int currentFit;

	//cout << "Max C Size :  _" << maxCSize << endl;
	for (currentFit = 0; currentFit < maxCSize; currentFit++) {
		readMCS = Info[currentFit];
		//cout << "Read MCS :  _" << readMCS << endl;
		if (readMCS == " ") {}
		else {
			while (currentFit < maxCSize) {
				//cout << "Trans Add : _" << Info[currentFit] << endl;
				tempInfo = tempInfo + Info[currentFit];
				if (tempInfo == " ") {
					return tempInfo;
				}
				currentFit++;
			}
		}
	}
	return tempInfo;
}

int charTotal(string info,string markchar){
	int charsize = info.size();
	int totalget = 0;
	for(int readsize = 0;charsize != readsize;readsize++){
		readbuffer = info[readsize];
		if (readbuffer == markchar){
			totalget ++;
			continue;
		}
		else {
			continue;
		}
	}
	return totalget;
}

int SpawnRandomNum(int min, int max) {

	string minb, maxb;
	minb = to_string(min);
	maxb = to_string(max);

	//string chars = "Min :  " + minb + "   Max :   " + maxb + "  Bug Report";
	//MessageBox(0, chars.c_str(), "MXBug Report", MB_OK);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max); // Missing
	int outdata = dis(gen);
	
	//string dis_str = to_string(dis(gen));
	//MessageBox(0,dis_str.c_str(),"Bug check",MB_OK);
	
	return dis(gen);
}

// -4 == Not Found
int FindCharLine(int startline,string file, string charData) {
	//cout << "GoRoll. in " << startline << endl;
	while (true) {
		//cout << "A" << endl;
		readbufferA = LineReader(file, startline);
		//cout << "B" << endl;
		readbufferA = HeadSpaceCleanA(readbufferA);
		//cout << "Roll :  " << startline << "  INFO :  " << readbufferA << endl;
		if (readbufferA == "overline") {
			return -4;
		}
		if (readbufferA == "LineError") {
			return -4;
		}
		if (readbufferA == "FileNotExist") {
			//cout << "File NULL" << endl;
			return -4;
		}

		if (checkChar(readbufferA, charData) == 1) {
			//cout << "EndRoll :  " << startline << endl;
			return startline;
		}
		startline++;
	}
}

string readbufferCMDVAR;

string GetURLCode(string URL) {
	//SpawnRandNum
	string tempcreatefile = "geturlcode~" + to_string(SpawnRandomNum(1, 10000)) + ".tmp";
	bool tmp = URLDown(URL, tempcreatefile);
	readbufferCMDVAR = LineReader(tempcreatefile, 1);
	//cout << "Remove :  " << tempcreatefile << endl;
	remove(tempcreatefile.c_str());

	if (tmp) {
		return readbufferCMDVAR;
	}
	else {
		cout << "GetURLCode Error :  URL -> " << URL << endl;
		cout << "TempFile :  ->  " << readbufferCMDVAR << endl;
		return "URLError.FailedGet";
	}
}

string getendchar(string infos) {
	numbuffer = infos.size();
	readbuffer = infos[numbuffer];
	return readbuffer;
}

string cutendchar(string infos) {
	numbuffer = infos.size();
	if (numbuffer == 0) {
		return "FAILED";
	}
	numbuffer--;
	readbuffer = "";
	for (int rptr = 0; rptr != numbuffer; rptr++) {
		readbuffer = readbuffer + infos[rptr];
	}
	return readbuffer;
}

bool createmark(string File, string info) {
	ofstream CMark;
	CMark.open(File);
	CMark << info << endl;
	CMark.close();

	if (check_file_existence(File)) {
		return true;
	}
	else {
		return false;
	}
}

void autopause(void) {
	cout << "Press Enter key to Next ...  ";
	getchar();
	return;
}