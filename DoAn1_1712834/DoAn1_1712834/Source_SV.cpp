﻿#include"SV.h"

void In(SV sv) {
	wprintf(L"Tên: %ls\n", sv.name);
	wprintf(L"MSSV: %s\n", sv.mssv);
	wprintf(L"Khoa: %ls\n", sv.fac);
	wprintf(L"Khóa: %d\n", sv.year);
	wprintf(L"Mail: %ls\n", sv.mail);
	wprintf(L"Ngày sinh: %ls\n", sv.dob);
	wprintf(L"File ảnh: %ls\n", sv.image);
	wprintf(L"Mô tả: %ls\n", sv.des);
	wprintf(L"Sở thích: \n");
	for(unsigned int i=0; i<sv.hobby_count; i++)
		wprintf(L"%d: %ls\n",i, sv.hobby[i]);
}

void FreeSV(SV &sv) {
	free(sv.name);
	free(sv.mssv);
	free(sv.fac);
	free(sv.mail);
	free(sv.dob);
	free(sv.image);
	free(sv.des);
	for (unsigned int i = 0; i < sv.hobby_count; i++)
		free(sv.hobby[i]);
	free(sv.hobby);
}