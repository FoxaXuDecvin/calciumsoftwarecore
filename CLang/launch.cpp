//Launch
// Main Cpp

//NET Loader

#include"Code/example.h"

//EDIT ON ANY_H



//Other Main
#include"Code/launchscreen.h"

using namespace std;

void printmsgoclt() {
    _prtendl();
    _prtoutmsg("Build By OpenCLT");
    _prtoutmsg($version_title + "   " + to_string($version_code));
    _prtoutmsg("OpenCLT " + $version_msg);
    _prtoutmsg("Code Name :   " + $codename);
    _prtoutmsg("    Copyright FoxaXu " + $year_message);
    _prtoutmsg(" Github :  " + $github_website);
    _pause();
    return;

}

int main(int argc, char* argv[]) {
    
    if (__settings_displaylaunchscreen) {
        _LaunchScreen();
        sleepapi(__settings_displaylaunchscreen_time);
        cleanConsole();
    }
    else {

    }


    for (int readargc = 1, fileswitch = 0; readargc != argc; readargc++) {
        readbuffer = argv[readargc];
        if (readbuffer == "--oclt-version") {
            printmsgoclt();
            return 0;
        }

        argsApi(readbuffer);
    }

    if (argsSetExit == true) {
        return 0;
    }

    int return_code = _HeadMainLoad();

    return return_code;
}
