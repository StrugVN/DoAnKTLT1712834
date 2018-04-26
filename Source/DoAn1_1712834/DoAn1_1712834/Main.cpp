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

	wprintf(L"============== Đồ án KTLT - 1712834 - 2018 =============\n\n");


	// ===== Phần dự kiến sẽ bị thay đổi ======
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
	// ============================================

	CSDL dssv;
	wchar_t *f = NULL; int t = 0;
	wchar_t *html = NULL; int u = 0;

	wprintf(L"Profile page sẽ được tạo từ Page mẫu \"mau.htm\", bạn có muốn thay đổi không?\n");

	if (Choose()) {
		wprintf(L"Hãy nhập đường dẫn file cần làm mẫu\n");
		html = GetLine();
		u = 1;
	}
	else
		html = L"mau.htm";

	wprintf(L"Dữ liệu các SV sẽ được đọc từ file mẫu \"dl1.csv\", bạn có muốn thay đổi không?\n");

	if (Choose()) {
		wprintf(L"Hãy nhập đường dẫn file cần đọc\n");
		f = GetLine();
		t = 1;
	}
	else
		f = L"dl1.csv";
	
	if (FileToSV(dssv, f)) {

		wprintf(L"\nĐã đọc được dữ liệu của %d sinh viên\n", dssv.sl);
		wprintf(L"Hãy chọn tùy chọn xuất profile page:\n");
		wprintf(L"Hãy nhập:\n");
		wprintf(L"\t 0. Để xuất tất cả thông tin của các sinh viên\n");
		wprintf(L"\t 1. Để tùy chọn xuất thông tin cho tất cả sinh viên\n");
		wprintf(L"\t 2. Để tùy chọn xuất thông tin cho từng sinh viên\n");
		int choose;
		do {
			wscanf(L"%d%*c", &choose);
			if (choose != 0 && choose != 1 && choose != 2)
				wprintf(L"Hãy nhập đúng yêu cầu!\n");
		} while (choose != 0 && choose != 1 && choose != 2);

		system("cls");
		wprintf(L"============== Đồ án KTLT - 1712834 - 2018 =============\n\n");

		wprintf(L"Bạn đã chọn: %d\n", choose);

		Option(choose, dssv);

		if (Generate(html, dssv, t_sv))
			wprintf(L"Đã tạo xong các Profile Page, hãy thoát CT trước khi mở các page.\nẤn bất kì nút nào để thoát.");
		else
			wprintf(L"Đã có lỗi trong quá trình tạo cái Profile Page, Hãy kiểm tra và thử lại.\nCT kết thúc.");
		FreeCSDL(dssv);
	}
	else
		wprintf(L"Đã có lỗi khi đọc file .csv, hãy kiểm tra và thử lại.\nCT kết thúc.\n");
	FreeSV(t_sv);
	if (t == 1)
		free(f);
	if (u == 1)
		free(html);
	_getche();
	return 0;
}