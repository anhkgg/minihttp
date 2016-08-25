#pragma once

#include <assert.h>

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#define CURL_STATICLIB

#include "../liburl/include/curl/curl.h"

#ifndef _DEBUG
#pragma comment(lib, "../liburl/Win32/VC12/LIB Release/libcurl.lib")
#else
#pragma comment(lib, "../liburl/Win32/VC12/LIB Debug/libcurld.lib")
#endif
