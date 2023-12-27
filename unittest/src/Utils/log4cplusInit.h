
#include <iostream>
#include <string>
#include <codecvt>
#include <direct.h>

#include "log4cplus/initializer.h"
#include "log4cplus/logger.h"
#include "log4cplus/configurator.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/stringhelper.h"
#include "log4cplus/loggingmacros.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

inline std::wstring to_wide_string(const std::string& input) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(input);
}

log4cplus::tstring getBinPath(string strPath) {
    size_t pos = strPath.find_last_of("\\");
    string newpath = strPath.substr(0, pos+1);
    log4cplus::tstring tPath = to_wide_string( newpath + "log4cplus.properties" );
    wcout << "current config -> " << tPath <<endl;
    return tPath;
}

bool InitLog4cplus(string path){
    _mkdir("log");
    cout << "get cur exe path:" << path << endl;
    PropertyConfigurator::doConfigure(getBinPath(path));
    return true;
}
