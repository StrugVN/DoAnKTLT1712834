#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include"HTML.h"

void FindNReplace(wchar_t *&wcs, wchar_t *f, wchar_t *rw) {
	if (wcscmp(f, rw) == 0)
		return;
	wchar_t *p = wcsstr(wcs, f);

	while (p) {
 		wchar_t *temp = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(wcs) + wcslen(rw) - wcslen(f) + 1));
		wcsncpy(temp, wcs, (p - wcs));
		wcsncpy(temp + (p - wcs), rw, wcslen(rw));
		wcscpy(temp + (p - wcs) + wcslen(rw), wcs + (p - wcs + wcslen(f)));
		
		wcs = (wchar_t*)realloc(wcs, 1);
		free(wcs);
		wcs = temp;
		p = wcsstr(wcs, f);
	}
}

void FindNReplace(wchar_t *&wcs, wchar_t *f, wchar_t *rw, bool& flag) {
	if (wcscmp(f, rw) == 0)
		return;
	wchar_t *p = wcsstr(wcs, f);

	while (p) {
		wchar_t *temp = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(wcs) + wcslen(rw) - wcslen(f) + 1));
		wcsncpy(temp, wcs, (p - wcs));
		wcsncpy(temp + (p - wcs), rw, wcslen(rw));
		wcscpy(temp + (p - wcs) + wcslen(rw), wcs + (p - wcs + wcslen(f)));

		wcs = (wchar_t*)realloc(wcs, 1);
		free(wcs);
		wcs = temp;
		p = wcsstr(wcs, f);
		flag = true;
	}
}

wchar_t* ToWCS(int a) {
	int n = (int)log10(a) + 1;
	wchar_t *kq=(wchar_t*)malloc(sizeof(wchar_t)*(n+1));
	
	swprintf(kq,n+1,L"%d",a);

	return kq;
}

void CreateAPage(wchar_t *t_html, SV t_sv, SV sv, wchar_t **extra) {
	FILE *f = _wfopen(t_html, L"r,ccs=UTF-16LE");
	wchar_t* des = GenerateName(sv);
	FILE *out = _wfopen(des, L"w,ccs=UTF-16LE");

	bool flag = false;
	while (!feof(f)) {
		if (!flag) {
			wchar_t *temp = ReadALine(f);
			if (temp == NULL)
				break;
						
			if (wcsstr(temp, t_sv.mssv))
				FindNReplace(temp, t_sv.mssv, sv.mssv);

			if (wcsstr(temp, t_sv.name))
				FindNReplace(temp, t_sv.name, sv.name);
			if (wcsstr(temp, extra[0]))
				FindNReplace(temp, extra[0], sv.name);

			if (wcsstr(temp, t_sv.fac))
				FindNReplace(temp, t_sv.fac, sv.fac);
			if (wcsstr(temp, extra[1]))
				FindNReplace(temp, extra[1], sv.fac);
			

			wchar_t *year = ToWCS(sv.year);
			wchar_t *t_year = ToWCS(t_sv.year);
			if (wcsstr(temp, year))
			FindNReplace(temp, year, t_year);
			free(year);	free(t_year);

			if (wcsstr(temp, t_sv.mail))
				FindNReplace(temp, t_sv.mail, sv.mail);
			if (wcsstr(temp, t_sv.dob))
				FindNReplace(temp, t_sv.dob, sv.dob);
			if (wcsstr(temp, t_sv.image))
				FindNReplace(temp, t_sv.image, sv.image);
			if (wcsstr(temp, t_sv.des))
				FindNReplace(temp, t_sv.des, sv.des);
				
			if (wcsstr(temp, t_sv.hobby[0]))
				FindNReplace(temp, t_sv.hobby[0], sv.hobby[0], flag);
			fwprintf(out, L"%ls\n", temp);
			
			temp = (wchar_t*)realloc(temp, 1);	// ? Tương tự bên SV cần dòng này ko thì free lỗi
			free(temp);
			
		}
		else {	// Tách riêng xử lí sở thích
			wchar_t *temp = NULL;
			unsigned int n = t_sv.hobby_count > sv.hobby_count ? t_sv.hobby_count : sv.hobby_count;
			for (unsigned int i = 1; i < n; i++) {
				if (i < t_sv.hobby_count) {	// Mẫu có >= số sở thích
					temp = ReadALine(f);
					
					if (i < sv.hobby_count) {
						FindNReplace(temp, t_sv.hobby[i], sv.hobby[i]);
						fwprintf(out, L"%ls\n", temp);	// Đọc đổi in
						
					}	// Hết sở thích thì đọc để đẩy con trỏ lên
					if (i + 1 < t_sv.hobby_count) {
						temp = (wchar_t*)realloc(temp, 1);
						free(temp);
						temp = NULL;
					}
				}
				else {	// Mẫu có < số sở thích thì lấy sở thích trước đó làm mẫu
					FindNReplace(temp, sv.hobby[i-1], sv.hobby[i]);
					fwprintf(out, L"%ls\n", temp);
					;
				}
			}
			if (temp) {
				temp = (wchar_t*)realloc(temp, 1);
				free(temp);
			}
			flag = false;
		}
		
	}
	free(des);
}

wchar_t* GenerateName(SV sv) {
	wchar_t* wcs = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(sv.mssv) + 1 + wcslen(L".htm")));
	wcscpy(wcs, sv.mssv);
	wcscat(wcs, L".htm");
	return wcs;
}

void Generate(wchar_t *t_html, CSDL dssv, SV t_sv, wchar_t **extra) {
	for (unsigned int i = 0; i < dssv.sl; i++)
		CreateAPage(t_html, t_sv, dssv.ds[i], extra);
}