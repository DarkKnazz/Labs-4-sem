#include "ArchiveUser.h"

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "������������ ������ 1" << endl;
	cout << "����������� ������ �������� � �������� �������" << endl;
	cout << "���������� ������ �� ������� ������ �� �����" << endl;
	cout << "��� ������������ ������ ��� ������ �� ������ ��������� ������" << endl;
	_getch();
	system("cls");
	int kol = 0;

	string password;
	unsigned int line;
	while (1){
		ArchiveUser user(L"\\\\.\\pipe\\$MyPipe$", L"..\\..\\Child_1\\Debug\\Child_1.exe");
		cout << "������� ������ ��� �������� ������: " << endl;
		getline(cin, password);
		cout << "������� ����� ������, ������� ����� ��������� �� �����: " << endl;
		cin >> line;

		user.formQuery(password, line);
		user.sendQuery();
		user.print();
		_getch();

		cout << "���� ������ ����������, ������� 1: " << endl;
		cin >> kol;
		cin.ignore(1, '\n');
		if (kol != 1)
			break;
	}
	return 0;
}