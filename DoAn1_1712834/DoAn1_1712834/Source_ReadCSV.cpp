#include"SV.h"

wchar_t* ReadALine(FILE*& f) {
	wchar_t *str = (wchar_t*)malloc(sizeof(wchar_t));
	
	wchar_t c = fgetwc(f);
	int n = 1;
	while (1) {
		if (feof(f)) {
			free(str);
			str = NULL;
			break;
		}
		if (c == '\n') {
			str = (wchar_t*)realloc(str, (n - 1) * sizeof(wchar_t));
			str[n-1] = L'\0';
			break;
		}
		str = (wchar_t*)realloc(str, (n + 1) * sizeof(wchar_t));
		str[n - 1] = c;
		c = fgetwc(f);
		n++;
	}

	return str;
}

bool Check(bool flag, wchar_t p, wchar_t delim) {
	if (flag == true)
		return false;
	return p == delim;
}

// Viết lại hàm theo mẫu wcstok để ko cắt token tại dấu , giữa 2 dấu "
wchar_t* Token(wchar_t *in, wchar_t delim, wchar_t excpt) {
	static wchar_t* itr = NULL;
	if (in == NULL) {
		if (itr == NULL)
			return NULL;
		else
			in = itr;
	}
	wchar_t* p2 = in;
	bool flag = false;
	while (!Check(flag, *p2, delim)) {
		if (*p2 == NULL) {
			itr = NULL;
			return in;
		}
		if (*p2 == excpt) {
			flag = !flag;
			*p2 = ' ';
		}
		p2++;
	}
	*p2 = '\0';
	itr = p2+1;
	return in;
}

void FileToSV(CSDL& ds, wchar_t* filepath) {
	FILE *f = _wfopen(filepath, L"r,ccs=UTF-16LE");
	wchar_t* str = NULL;
	str = ReadALine(f);
	while (str) {
		SV sv;
		wchar_t* p = Token(str, L',', L'\"');
		sv.InsMSSV(p);

		p = Token(NULL, L',', L'\"');
		sv.InsName(p);
		
		p = Token(NULL, L',', L'\"');
		sv.InsFac(p);

		p = Token(NULL, L',', L'\"');
		sv.InsYear(p);

		p = Token(NULL, L',', L'\"');
		sv.InsMail(p);

		p = Token(NULL, L',', L'\"');
		sv.InsDob(p);

		p = Token(NULL, L',', L'\"');
		sv.InsImg(p);

		p = Token(NULL, L',', L'\"');
		sv.InsDes(p);

		p = Token(NULL, L',', L'\"');
		while (p) {
			if (wcslen(p)>0)
				sv.InsHobby(p);
			p = Token(NULL, L',', L'\"');
		}
		ds.Add(sv);

		str = (wchar_t*)realloc(str, 1);
		/*
		Sử dụng free lên str:
			- CT kêu tèn ten tại dòng free (lỗi) nhưng ko hiện bất cứ lỗi nào (CT dừng)
			- Thêm 1 dòng relloc đại ở trên: Chạy bt ?.?
		*/
		free(str);
		str = NULL;
		str = ReadALine(f);
	}
}