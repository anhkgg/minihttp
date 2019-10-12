# minihttp

`minihttp` is a simple https/http request library based on libcurl and openssl.

support:

1. [x] https / http
2. [x] GET
3. [x] POST
4. [x] Ajax
5. [x] Cookies

# Usage

build by vs2017.

```
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
	//size_t size = http.post("http://www.xiaoshuo520.com/services/Member/chkLogin/?", "username=111&userpass=11&saveLogin=0", res_);
	size = http.post("http://www.xiaoshuo520.com/", 80, "services/Member/chkLogin/?", "username=111&userpass=11&saveLogin=0", res_);

	cout << "size = " << size << endl;
	cout << res_ << endl;

	//size = http.get("http://www.baidu.com/", 80, "/index.html", res_);
	size = http.ajax("http://www.xiaoshuo520.com/", 80, "services/Member/chkLogin/?", "username=admin11&userpass=admin11&saveLogin=0", res_);

	cout << "size = " << size << endl;
	cout << res_ << endl;

	//size = http.get("http://so.xiaoshuo520.com/kw/%E6%B1%9F%E5%B1%B1", res_);
	size = http.get("http://so.xiaoshuo520.com/", 80, "kw/江山", res_);

	return 0;
}
```

You can see more informaiton [here](http://anhkgg.github.io/liburl-use-minihttp/).

Contact me if there are some bugs in `minihttp`.

- 公众号：[汉客儿](https://mp.weixin.qq.com/s/-h4A6MXOdPLBEIzFXY-SiA)
- homepage:  [anhkgg.com](anhkgg.com)
- weibo: [weibo.com/anhkgg](weibo.com/anhkgg)
