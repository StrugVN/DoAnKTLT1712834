#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _SV_h_
#define _SV_h_

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <fcntl.h>
#include <io.h>

struct SV {
	wchar_t *mssv;
	wchar_t *name;
	wchar_t *fac;
	int year;
	wchar_t *mail;
	wchar_t *dob;
	wchar_t *image;
	wchar_t *des;
	unsigned int hobby_count;
	wchar_t **hobby;
	wchar_t *pageName;

	SV() {
		name = NULL;
		mssv = NULL;
		fac = NULL;
		year = 0;
		mail = NULL;
		dob = NULL;
		image = NULL;
		des = NULL;
		hobby_count = 0;
		hobby = NULL;
		pageName = NULL;
	}

	void InsName(wchar_t* _name) {
		name = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_name) + 1));
		wcscpy(name, _name);
	}
	void InsMSSV(wchar_t* _mssv) {
		mssv = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_mssv) + 1));
		wcscpy(mssv, _mssv);
	}
	void InsPageName(wchar_t* _mssv) {
		pageName = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_mssv) + 1 + wcslen(L".htm")));
		wcscpy(pageName, _mssv);
		wcscat(pageName, L".htm");
	}
	void InsFac(wchar_t* _fac) {
		fac = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_fac) + 1));
		wcscpy(fac, _fac);
	}
	void InsYear(wchar_t* _year) {
		wchar_t *p = _year;
		while (*p) {
			year *= 10;
			year += *p - L'0';
			p++;
		}
	}
	void InsMail(wchar_t* _mail) {
		mail = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_mail) + 1));
		wcscpy(mail, _mail);
	}
	void InsDob(wchar_t* _dob) {
		dob = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_dob) + 1));
		wcscpy(dob, _dob);
	}
	void InsImg(wchar_t* _Img) {
		image = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_Img) + 1));
		wcscpy(image, _Img);
	}
	void InsDes(wchar_t* _des) {
		des = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_des) + 1));
		wcscpy(des, _des);
	}
	void InsHobby(wchar_t* _hobby) {
		hobby = (wchar_t**)realloc(hobby, sizeof(wchar_t*)*(hobby_count + 1));
		hobby[hobby_count] = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_hobby) + 1));
		wcscpy(hobby[hobby_count], _hobby);
		hobby_count++;
	}
};

struct CSDL {
	SV *ds;
	unsigned int sl;
	CSDL() {
		ds = NULL;
		sl = 0;
	}

	void Add(SV sv) {
		ds = (SV*)realloc(ds, sizeof(SV)*(sl + 1));
		ds[sl] = sv;
		sl++;
	}
};

wchar_t* ReadALine(FILE*& f);
bool Check(bool flag, wchar_t p, wchar_t delim);
wchar_t* Token(wchar_t *in, wchar_t delim, wchar_t excpt);
bool FileToSV(CSDL& ds, wchar_t* filepath);
void In(SV sv);
void FreeSV(SV &sv);
void InDL(CSDL &ds);
void FreeCSDL(CSDL &ds);

#endif