class reply
{
public:
	TCHAR name[255];
	TCHAR ip[255];
	int message;
	bool con;

	reply(){
		message = 0;
		_tcscpy_s(this->name, (LPCTSTR)"no name");
		_tcscpy_s(this->ip, (LPCTSTR)"127.0.0.1");
		con = false;
	}

	void SetMessage(CString name, CString ip, int message=0, bool con = false){
		_tcscpy_s(this->name, (LPCTSTR)name);
		_tcscpy_s(this->ip, (LPCTSTR)ip);
		this->message = message;
		this->con = con;
	}
};