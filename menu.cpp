#include "menu.h"

bool is_valid(string s) {
	int d = 0, m = 0, y = 0;
	for (int i = 0; s[i] != '.'; i++) {
		d *= 10;
		d += s[i] - '0';
	}
	for (int i = s.find('.') + 1; i < s.rfind('.'); i++) {
		m *= 10;
		m += s[i] - '0';
	}
	for (int i = s.rfind('.') + 1; i < s.length(); i++) {
		y *= 10;
		y += s[i] - '0';
	}

	if (1000 < y && y < 2023)
	{
		switch (m) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (0 < d && d < 32) return true;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if (0 < d && d < 31) return true;
				break;
			case 2: // only 28 day required
				if (0 < d && d < 29) return true;
				break;
		}
	}
	return false;
}

int menu(book& b) {
	int num;
	cout << "1 - Перезаписать массив даннных\n";
	cout << "2 - Посмотреть все записи\n";
	cout << "3 - Отсортировать массив по датам\n";
	cout << "4 - Посмотртеть под номером N\n";
	cout << "5 - Изменить под номером N\n";
	cout << "6 - Фильтр\n";
	cout << "7 - Посчитать\n";
	cout << "8 - Добавить запись\n";
	cout << "9 - Выйти\n";
	cout << '\n';
	cin >> num;
	if (num == 1) {
		system("cls");
		b.clear();
		cout << "Введите количество элементов\n";
		int count;
		cin >> count;
		for (size_t i = 0; i < count; i++)
		{
			cout << "\n\nВведите текст\n";
			string text;
			cin.ignore();
			getline(cin, text);
			cout << "Введите категорию\n";
			string cat;
			cin.ignore();
			getline(cin, cat);
			cout << "Введите дату в формате XX.XX.XXXX\n";
			string d;
			cin.ignore();
			getline(cin, d);
			if (is_valid(d)) {
				b.push_back(record(text, cat, date(d)));
			} else {
				cout << "Ошибка: Дата введена неверно\n\n";
			}
		}
		system("cls");

		return 0;
	}
	if (num == 2) {
		system("cls");
		b.show_all();
		cout << "Введите 0, чтобы вернуться в главное меню\n";
		cin >> num;
		system("cls");
		return 0;
	}

	if (num == 3) {
		book copy(b);
		sort(copy.get_records_(), copy.get_records_() + copy.get_count_());
		system("cls");
		cout << "\nКнига отсортирована\n\n";
		copy.show_all();
		cout << "Введите 0, чтобы вернуться в главное меню\n";
		cin >> num;
		return 0;
	}
	
	if (num == 4) { 
		system("cls");
		cout << "Введите номер записи не больше " << b.get_count_() << " (нумерация начинается с 1)\n";
		int index;
		cin >> index;
		cout << b.get_records_()[index - 1];
		cout << "\nВведите 0, чтобы вернуться в главное меню\n";
		cin >> num;
		system("cls");
		return 0;
	}

	if (num == 5) { 
		system("cls");
		cout << "Введите номер записи не больше " << b.get_count_() << " (нумерация начинается с 1)\n";
		int index;
		cin >> index;
		--index;
		cout << "Что изменить?\n1 - изменить дату\n2 - изменить категорию\n3 - изменить текст\n\n";
		int task;
		cin >> task;

		if (task == 1) {
			cout << "Введите дату в формате XX.XX.XXXX\n";
			string d;
			cin.ignore();
			getline(cin, d);
			if (is_valid(d)) {
				b[index].set_date_(date(d));
				cout << "\nИзменения сохранены успешно\n\n";
			}
			else
				cout << "Ошибка: Дата введена неверно\n\n";
			system("cls");
			return 0;
		}
		else if (task == 2) {
			cout << "Введите категорию\n";
			string cat;
			cin.ignore();
			getline(cin, cat);
			b[index].set_category_(cat);
			system("cls");
			cout << "\nИзменения сохранены успешно\n\n";
			return 0;
		}
		else if (task == 3) {
			string text;
			cin.ignore();
			getline(cin, text);
			b[index].set_text_(text);
			system("cls");
			cout << "\nИзменения сохранены успешно\n\n";
			return 0;
		}
		cout << "\nНеверный номер\n\n";
		return 0;
	}

	if (num == 6) {
		system("cls");
		cout << "Введите категорию\n";
		string cat;
		cin.ignore();
		getline(cin, cat);

		int count_found = b.filt_category(cat);

		if (count_found == 0) {
			cout << "\nТакой категории нет\n\n";
		}

		cout << "\nВведите 0, чтобы вернуться в главное меню\n";
		cin >> num;
		system("cls");
		return 0;
	}

	if (num == 7) { 
		system("cls");
		int max_count = 0;
		date max_date;
		for (size_t i = 0; i < b.get_count_(); i++)
		{

			int temp_count = 0;
			for (size_t j = 0; j < b.get_count_(); j++) 
			{
				if (b[i].get_date_() == b[j].get_date_()) {
					++temp_count;
				}
			}
			if (temp_count > max_count) {
				max_count = temp_count;
				max_date = b[i].get_date_();
			}
		}
		cout << "\nМаксимальное число записей = " << max_count << "\nДата = " << max_date << "\n";
		cout << "\nВведите 0, чтобы вернуться в главное меню\n";
		cin >> num;
		system("cls");
		return 0;
	}

	if (num == 8) { 
		cout << "Введите текст\n";
		string text;
		cin.ignore();
		getline(cin, text);
		cout << "Введите категорию\n";
		string cat;
		cin.ignore();
		getline(cin, cat);
		cout << "Введите дату в формате XX.XX.XXXX\n";
		string d;
		cin.ignore();
		getline(cin, d);
		if (is_valid(d)) {
			b.push_back(record(text, cat, date(d)));
			cout << "\nИзменения сохранены успешно\n\n";
		}
		else
			cout << "Ошибка: Дата введена неверно\n\n";
		system("cls");
		cout << "\nЗапись добавлена\n\n";
		return 0;
	}

	//выход в меню
	return -1;
}
