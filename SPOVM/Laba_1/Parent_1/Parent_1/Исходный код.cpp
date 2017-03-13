#include "ArchiveUser.h"

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа 1" << endl;
	cout << "Организация работы человека и архивной системы" << endl;
	cout << "Передается запрос на возврат строки из файла" << endl;
	cout << "При несовпадении строки или пароля от архива возвратит ошибку" << endl;
	_getch();
	system("cls");
	int kol = 0;

	string password;
	unsigned int line;
	while (1){
		ArchiveUser user(L"\\\\.\\pipe\\$MyPipe$", L"..\\..\\Child_1\\Debug\\Child_1.exe");
		cout << "Введите пароль для открытия архива: " << endl;
		getline(cin, password);
		cout << "Введите номер строки, которую нужно прочитать из файла: " << endl;
		cin >> line;

		user.formQuery(password, line);
		user.sendQuery();
		user.print();
		_getch();

		cout << "Если хотите продолжить, нажмите 1: " << endl;
		cin >> kol;
		cin.ignore(1, '\n');
		if (kol != 1)
			break;
	}
	return 0;
}