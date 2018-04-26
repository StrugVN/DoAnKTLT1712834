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
	if (a == 0) {
		wchar_t *kq = (wchar_t*)malloc(sizeof(wchar_t)*2);
		kq[0] = L'0';
		kq[1] = L'\0';
		return kq;
	}
	int n = (int)log10((double)a) + 1;
	wchar_t *kq = (wchar_t*)malloc(sizeof(wchar_t)*(n + 1));

	swprintf(kq, n + 1, L"%d", a);

	return kq;
}

wchar_t* ToWupper(wchar_t* wcs) {
	wchar_t* temp = (wchar_t *)malloc((wcslen(wcs) + 1) * sizeof(wchar_t));
	for (unsigned int i = 0; i < wcslen(wcs); i++) {
		if (wcs[i] >= 256 && wcs[i] % 2 != 0)
			temp[i] = wcs[i] - 1;
		else if ((wcs[i] >= 192 && wcs[i]<=222)  || wcs[i] == 32 || (wcs[i] >= 256 && wcs[i] % 2 == 0) || (wcs[i] >= 65 && wcs[i] <= 90))
			temp[i] = wcs[i];
		else
			temp[i] = wcs[i] - 32;
	}
	temp[wcslen(wcs)] = L'\0';
	return temp;
}

wchar_t* ToWlower(wchar_t* wcs) {
	wchar_t* temp = (wchar_t *)malloc((wcslen(wcs) + 1) * sizeof(wchar_t));
	for (unsigned int i = 0; i < wcslen(wcs); i++) {
		if (wcs[i] >= 256 && wcs[i] % 2 == 0)
			temp[i] = wcs[i] + 1;
		else if ((wcs[i]>=224 && wcs[i]<=254) || wcs[i] == 32 || (wcs[i] >= 256 && wcs[i] % 2 != 0) || (wcs[i] >= 97 && wcs[i] <= 122))
			temp[i] = wcs[i];
		else
			temp[i] = wcs[i] + 32;
	}
	temp[wcslen(wcs)] = L'\0';
	return temp;
}

bool Choose() {
	wchar_t c;
	do {
		wprintf(L"Hãy nhập Y để chọn đồng ý hoặc N để chọn không đồng ý: ");
		wscanf(L"%c%*c", &c);
		if (c != L'N' && c != L'n' && c != L'Y' && c != 'y')
			wprintf(L"Hãy nhập đúng yêu cầu!\n");
	} while (c != L'N' && c != L'n' && c != L'Y' && c != 'y');
	return (c == L'Y' || c == L'y');
}

void Option(int choose, CSDL& dssv) {
	switch (choose) {
	case 1:
		wprintf(L"MSSV của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"MSSV các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				free(dssv.ds[i].mssv);
				dssv.ds[i].mssv = NULL;
				dssv.ds[i].InsMSSV(L" ");
			}
		}

		wprintf(L"Tên của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Tên các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				free(dssv.ds[i].name);
				dssv.ds[i].name = NULL;
				dssv.ds[i].InsName(L" ");
			}
		}

		wprintf(L"Khoa của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Khoa các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				free(dssv.ds[i].fac);
				dssv.ds[i].fac = NULL;
				dssv.ds[i].InsFac(L" ");
			}
		}

		wprintf(L"Khóa của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Khóa các SV đã được đặt thành 0!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				dssv.ds[i].year = 0;
			}
		}

		wprintf(L"Mail của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Mail các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				free(dssv.ds[i].mail);
				dssv.ds[i].mail = NULL;
				dssv.ds[i].InsMail(L" ");
			}
		}

		wprintf(L"Ngày sinh của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Ngày sinh các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				free(dssv.ds[i].dob);
				dssv.ds[i].dob = NULL;
				dssv.ds[i].InsDob(L" ");
			}
		}

		wprintf(L"Hình ảnh của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Hình ảnh các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				free(dssv.ds[i].image);
				dssv.ds[i].image = NULL;
				dssv.ds[i].InsImg(L" ");
			}
		}

		wprintf(L"Mô tả của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Mô tả các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				free(dssv.ds[i].des);
				dssv.ds[i].des = NULL;
				dssv.ds[i].InsDes(L" ");
			}
		}

		wprintf(L"Các sở thích của các sinh viên có cần hiển thị?\n");
		if (!Choose()) {
			wprintf(L"Các sở thích các SV đã được xóa bỏ!\n");
			for (unsigned int i = 0; i < dssv.sl; i++) {
				for (unsigned int j = 0; j < dssv.ds[i].hobby_count; j++) {
					free(dssv.ds[i].hobby[j]);
					dssv.ds[i].hobby[j] = NULL;
				}
				dssv.ds[i].hobby_count = 0;
				dssv.ds[i].InsHobby(L" ");
			}
		}
		break;
	case 2:
		for (unsigned int i = 0; i < dssv.sl; i++) {
			wprintf(L"==== Sinh viên: %ls - MSSV %ls\n", dssv.ds[i].name, dssv.ds[i].mssv);
			wprintf(L"MSSV của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"MSSV của SV này đã được xóa bỏ!\n");
				free(dssv.ds[i].mssv);
				dssv.ds[i].mssv = NULL;
				dssv.ds[i].InsMSSV(L" ");
			}

			wprintf(L"Tên của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"Tên của SV này đã được xóa bỏ!\n");
				free(dssv.ds[i].name);
				dssv.ds[i].name = NULL;
				dssv.ds[i].InsName(L" ");
			}

			wprintf(L"Khoa của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"Khoa của SV này đã được xóa bỏ!\n");
				free(dssv.ds[i].fac);
				dssv.ds[i].fac = NULL;
				dssv.ds[i].InsFac(L" ");
			}

			wprintf(L"Khóa của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"Khóa của SV này đã được đặt thành 0!\n");
				dssv.ds[i].year = 0;
			}

			wprintf(L"Mail của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"Mail của SV này đã được xóa bỏ!\n");
				free(dssv.ds[i].mail);
				dssv.ds[i].mail = NULL;
				dssv.ds[i].InsMail(L" ");
			}

			wprintf(L"Mô tả của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"Mô tả của SV này đã được xóa bỏ!\n");
				free(dssv.ds[i].des);
				dssv.ds[i].des = NULL;
				dssv.ds[i].InsDes(L" ");
			}

			wprintf(L"Hình ảnh của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"Hình ảnh của SV này đã được xóa bỏ!\n");
				free(dssv.ds[i].image);
				dssv.ds[i].image = NULL;
				dssv.ds[i].InsImg(L" ");
			}

			wprintf(L"Các sở thích của sinh viên này có cần hiển thị?\n");
			if (!Choose()) {
				wprintf(L"Các sở thích của SV này đã được xóa bỏ!\n");

				for (unsigned int j = 0; j < dssv.ds[i].hobby_count; j++) {
					free(dssv.ds[i].hobby[j]);
					dssv.ds[i].hobby[j] = NULL;
				}
				dssv.ds[i].hobby_count = 0;
				dssv.ds[i].InsHobby(L" ");
			}
		}
		break;
	case 0:
		wprintf(L"Thông tin các SV sẽ được in đầy đủ\n");
		break;
	default:
		break;
	}
}

bool CreateAPage(wchar_t *t_html, SV t_sv, SV sv) {
	FILE *f = _wfopen(t_html, L"r,ccs=UTF-16LE");
	if (!f)
		return false;
	FILE *out = _wfopen(sv.pageName, L"w,ccs=UTF-16LE");
	if (!out)
		return false;

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
			wchar_t *t_Ncase = ToWupper(t_sv.name);
			wchar_t *Ncase = ToWupper(sv.name);
			if (wcsstr(temp, t_Ncase))
				FindNReplace(temp, t_Ncase, Ncase);
			free(t_Ncase);
			free(Ncase);

			t_Ncase = ToWlower(t_sv.name);
			Ncase = ToWlower(sv.name);
			if (wcsstr(temp, t_Ncase))
				FindNReplace(temp, t_Ncase, Ncase);
			free(t_Ncase);
			free(Ncase);

			if (wcsstr(temp, t_sv.fac))
				FindNReplace(temp, t_sv.fac, sv.fac);

			t_Ncase = ToWupper(t_sv.fac);
			Ncase = ToWupper(sv.fac);
			if (wcsstr(temp, t_Ncase))
				FindNReplace(temp, t_Ncase, Ncase);
			free(t_Ncase);
			free(Ncase);

			t_Ncase = ToWlower(t_sv.fac);
			Ncase = ToWlower(sv.fac);
			if (wcsstr(temp, t_Ncase))
				FindNReplace(temp, t_Ncase, Ncase);
			free(t_Ncase);
			free(Ncase);


			wchar_t *year = ToWCS(sv.year);
			wchar_t *t_year = ToWCS(t_sv.year);
			if (wcsstr(temp, t_year))
				FindNReplace(temp, t_year, year);
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
					FindNReplace(temp, sv.hobby[i - 1], sv.hobby[i]);
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
	return true;
}

bool Generate(wchar_t *t_html, CSDL dssv, SV t_sv) {
	for (unsigned int i = 0; i < dssv.sl; i++)
		if (!CreateAPage(t_html, t_sv, dssv.ds[i]))
			return false;
	return true;
}

wchar_t* GetLine() {
	wchar_t *str = (wchar_t*)malloc(sizeof(wchar_t));

	wchar_t c = getwchar();
	int n = 1;
	while (c!=L'\n') {
		str = (wchar_t*)realloc(str, (n + 1) * sizeof(wchar_t));
		str[n - 1] = c;
		c = getwchar();
		n++;
	}
	str[n-1] = L'\0';
	return str;
}