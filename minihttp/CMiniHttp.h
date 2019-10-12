// ---------------------------------------------
// project：	minihttp
// author：		anhkgg
// time：		2016-08-01
// site：		http://anhkgg.github.io
// github:		https://github.com/anhkgg
// ---------------------------------------------

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
#pragma comment(lib, "../liburl/Win32/vs2017/libcurls.lib")
#else
#pragma comment(lib, "../liburl/Win32/vs2017/libcurlds.lib")
#endif

/*
1. 基本http访问功能，支持get，post，ajax
2. 可能不支持数据中有\0
3. 不支持添加HEADER
*/

class CMiniHttp
{
public:
	CMiniHttp();
	~CMiniHttp();

	typedef struct _WRITE_CALLBACK_DATA {
		string data;
		size_t size;
	}WRITE_CALLBACK_DATA, *PWRITE_CALLBACK_DATA;

	/*
	url: www.baidu.com:8000/upload.asp?id=11
	*/
	size_t get(string url, string& res);
	/*
	url: www.baidu.com:8000/upload.asp
	data: id=1&name=123
	*/
	size_t post(string url, string data, string& res, bool ajax = false);
	size_t ajax(string url, string data, string& res);
	/*
	url:only host
	port:
	para:action url and param, for /upload.asp?id=1
	*/
	size_t get(string url, int port, string param, string& res);
	/*
	url:only host
	port:
	action:action url and param, for /upload.asp
	data: id=1&name=123
	*/
	size_t post(string url, int port, string action, string data, string& res);
	size_t ajax(string url, int port, string action, string data, string& res);

	/*
	cookies: ASP.NET_SessionId=0q4fx3o24ebaglm0rf3o3l2l; bank=bankLogonToken=25i8J4oF;
	*/
	void set_cookies(string cookies);
	void set_header(string header);

	/*有些时候会限制位数*/
	static string time(size_t len = 10);

private:

	void curl_init(CURL **curl, PWRITE_CALLBACK_DATA data);
	void curl_clean(CURL *curl);

	string packet_url(string url, int port, string action);

	static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

private:
	string m_cookies;
	struct curl_slist *m_headers;
};

