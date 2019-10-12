#include "stdafx.h"
#include "CMiniHttp.h"

int main()
{
	CMiniHttp http;

	string res_;

	size_t size = http.get("https://www.baidu.com", res_);
    cout << "size = " << size << endl;
    cout << res_ << endl;

	//size_t size = http.get("http://www.baidu.com/", 80, "/index.html", res_);

	/*
	username:111
	userpass:11
	saveLogin:0
	*/
	//size_t size = http.post("http://www.xiaoshuo520.com/services/Member/chkLogin/?jsoncallback=jQuery17206062402683310211_1470489169755&0.05604361440055072", "username=111&userpass=11&saveLogin=0", res_);
	size = http.post("http://www.xiaoshuo520.com/", 80, "services/Member/chkLogin/?jsoncallback=jQuery17206062402683310211_1470489169755&0.05604361440055072", "username=111&userpass=11&saveLogin=0", res_);

	cout << "size = " << size << endl;
	cout << res_ << endl;

	//size = http.get("http://www.baidu.com/", 80, "/index.html", res_);
	size = http.ajax("http://www.xiaoshuo520.com/", 80, "services/Member/chkLogin/?jsoncallback=jQuery17206062402683310211_1470489169755&0.05604361440055072", "username=admin11&userpass=admin11&saveLogin=0", res_);

	cout << "size = " << size << endl;
	cout << res_ << endl;

	//size = http.get("http://so.xiaoshuo520.com/kw/%E6%B1%9F%E5%B1%B1", res_);
	size = http.get("http://so.xiaoshuo520.com/", 80, "kw/½­É½", res_);

	return 0;
}