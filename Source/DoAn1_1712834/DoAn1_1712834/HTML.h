#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _HTML_h_
#define _HTML_h_

#include<stdio.h>
#include<conio.h>
#include<wchar.h>
#include <fcntl.h> 
#include <io.h>
#include"SV.h"

void FindNReplace(wchar_t *&wcs, wchar_t *f, wchar_t *rw);
wchar_t* ToWCS(int a);
wchar_t* ToWlower(wchar_t* wcs);
wchar_t* ToWupper(wchar_t* wcs);
bool Choose();
void Option(int choose, CSDL& dssv);
bool CreateAPage(wchar_t *t_html, SV t_sv, SV sv);
bool Generate(wchar_t *t_html, CSDL dssv, SV t_sv);
wchar_t* GetLine();

#endif