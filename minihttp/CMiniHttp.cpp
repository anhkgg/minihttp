// ---------------------------------------------
// project：	minihttp
// author：		anhkgg
// time：		2016-08-01
// site：		http://anhkgg.github.io
// github:		https://github.com/anhkgg
// ---------------------------------------------

#include "CMiniHttp.h"

#pragma comment(lib, "legacy_stdio_definitions.lib")
extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

CMiniHttp::CMiniHttp()
{
	curl_global_init(CURL_GLOBAL_ALL);

	m_cookies = "";

	m_headers = NULL;
	m_headers = curl_slist_append(m_headers, "User-Agent:Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.122 Safari/537.36 SE 2.X MetaSr 1.0");
}


CMiniHttp::~CMiniHttp()
{
	if (m_headers) 
		curl_slist_free_all(m_headers);

	curl_global_cleanup();
}

void CMiniHttp::curl_init(CURL **curl, PWRITE_CALLBACK_DATA data)
{
	*curl = curl_easy_init();

	data->data = "";
	data->size = 0;

    // https://blog.csdn.net/ypbsyy/article/details/83784670
    curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYPEER, false);//这个是重点。

    // https请求 不验证证书和hosts
    // 不能设置这个，否则连接失败
    //curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYHOST, false);//

    /*
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, true);
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, true);
    curl_setopt($curl,CURLOPT_CAINFO,dirname(__FILE__).'/cacert.pem');//这是根据http://curl.haxx.se/ca/cacert.pem 下载的证书，添加这句话之后就运行正常了
    */

	curl_easy_setopt(*curl, CURLOPT_WRITEDATA, data);
	curl_easy_setopt(*curl, CURLOPT_WRITEFUNCTION, write_callback);

	curl_easy_setopt(*curl, CURLOPT_HTTPHEADER, m_headers);

	curl_easy_setopt(*curl, CURLOPT_COOKIEJAR, "cookie.txt");        //把服务器发过来的cookie保存到cookie.txt
	curl_easy_setopt(*curl, CURLOPT_COOKIEFILE, "cookie.txt");        //读取本地存储的cookie
}

void CMiniHttp::curl_clean(CURL *curl)
{
	curl_easy_cleanup(curl);
}

size_t CMiniHttp::write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t all_size = size*nmemb;
	PWRITE_CALLBACK_DATA data = (PWRITE_CALLBACK_DATA)userdata;

	data->data.append(ptr);
	data->size += all_size;

	return all_size;
}


string CMiniHttp::packet_url(string url, int port, string action)
{
	string full_url;

	size_t pos = 0;
	pos = url.find_last_of("/\\");

	if ((pos + 1) == url.length()){
		url.erase(pos, 1);
	}

	ostringstream oss;
	oss << ":" << port;

	full_url.append(url);
	full_url.append(oss.str());

	pos = 0;
	pos = action.find_first_of("/\\");

	if (pos != 0){
		full_url.append("/");
	}
	full_url.append(action);

	return full_url;
}

void CMiniHttp::set_header(string header)
{
	m_headers = curl_slist_append(m_headers, header.c_str());
}

size_t CMiniHttp::get(string url, int port, string param, string& res)
{
	string full_url;

	full_url = packet_url(url, port, param);

	cout << full_url << endl;

	return get(full_url, res);
}

size_t CMiniHttp::get(string url, string& res)
{
	CURLcode ret;
	size_t ret_size = 0;

	CURL * curl = NULL;
	WRITE_CALLBACK_DATA data;

	curl_init(&curl, &data);

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	ret = curl_easy_perform(curl);
	/* Check for errors */
	if (ret != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
		ret_size = 0;
	}
	else {
		res = data.data;
		ret_size = data.size;
	}

	curl_clean(curl);

	return ret_size;
}

void CMiniHttp::set_cookies(string cookies)
{
	if (m_cookies.length() > 0)	m_cookies.append("; ");
	m_cookies.append(cookies);
}

size_t CMiniHttp::post(string url, string data, string& res, bool ajax )
{
	size_t ret_size = 0;
	CURL * curl = NULL;
	WRITE_CALLBACK_DATA rdata;

	curl_init(&curl, &rdata);

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	/* size of the POST data */
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());

	/* pass in a pointer to the data - libcurl will not copy */
	if (data.length() == 0) {
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);
	}
	else {
		curl_easy_setopt(curl, CURLOPT_POST, 0);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
	}

	CURLcode ret = curl_easy_perform(curl);
	/* Check for errors */
	if (ret != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
		ret_size = 0;
	}
	else {

		res = rdata.data;

		ret_size = rdata.size;
	}

	curl_clean(curl);

	return ret_size;
}


size_t CMiniHttp::post(string url, int port, string action, string data, string& res)
{
	string full_url = packet_url(url, port, action);

	return post(full_url, data, res);
}

size_t CMiniHttp::ajax(string url, int port, string action, string data, string& res)
{
	string full_url = packet_url(url, port, action);

	return ajax(full_url, data, res);
}

size_t CMiniHttp::ajax(string url, string data, string& res)
{
	set_header("X-Requested-With:XMLHttpRequest");
	set_header("Accept:application/json,text/javascript,*/*");
	set_header("Content-Type:application/json");
	
	return  post(url, data, res, true);
}

string CMiniHttp::time(size_t len)
{
	time_t rawtime;
	ostringstream oss;

	::time(&rawtime);
	oss << rawtime;

	string st = oss.str();

	for (int i = st.length(); i < len; i++){
		st.append("0");
	}

	if (st.length() > len) {
		st.erase(len, st.length() - len);
	}

	return st;
}