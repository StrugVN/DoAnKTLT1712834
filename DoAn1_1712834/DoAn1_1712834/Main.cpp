#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<conio.h>
#include<wchar.h>
#include <fcntl.h> 
#include <io.h>
#include"SV.h"
#include"HTML.h"

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);

	// ========================== Phần thay đổi khi template thay đổi ============================
	SV t_sv;
	t_sv.InsMSSV(L"1212123");
	t_sv.InsName(L"Nguyễn Văn A");
	t_sv.InsFac(L"Công nghệ thông tin");
	t_sv.InsYear(L"2017");
	t_sv.InsMail(L"nva@gmail.com");
	t_sv.InsDob(L"20/01/1994");
	t_sv.InsImg(L"Images/HinhCaNhan.jpg");
	t_sv.InsDes(L"Tôi là một người rất thân thiện.");
	t_sv.InsHobby(L"Âm nhạc: POP, Balad");
	t_sv.InsHobby(L"Ẩm thực: bún riêu, bún thịt nướng");

	wchar_t **extra = (wchar_t**)malloc(sizeof(wchar_t*) * 2);
	extra[0] = L"NGUYỄN VĂN A";
	extra[1] = L"CÔNG NGHỆ THÔNG TIN";
	// ================= Tùy theo extra mà Source_HTML.cpp thay đổi (1 dòng/1 extra) ========================
	
	CSDL dssv;
	FileToSV(dssv, L"dl1.csv");

	Generate(L"mau.htm", dssv, t_sv, extra);
	
	FreeCSDL(dssv);
	FreeSV(t_sv);
	free(extra);

	return 0;
}