#include <iostream>
#include <string>    //std::string, std::getline
// #include <Windows.h> //SetConsoleCP(1251); SetConsoleOutputCP(1251); !для русского языка в вижуалке(считать с консоли русский текст)!
#include <algorithm> //std::sort
using namespace std;

struct date {
	int day_;
	int month_;
	int year_;
	
    date(): day_(0), month_(0), year_(0) {}
	date(int d, int m, int y): day_(d), month_(m), year_(y) {}
	date(const date& oth): day_(oth.day_), month_(oth.month_), year_(oth.year_) {}
	date(string s): day_(0), month_(0), year_(0) {
        int d = 0, m = 0, y = 0;
		for (int i = 0; s[i] != '.'; i++) {
			day_ *= 10;
			day_ += s[i] - '0';
		}
		for (int i = s.find('.') + 1; i < s.rfind('.'); i++) {
			month_ *= 10;
			month_ += s[i] - '0';
		}
		for (int i = s.rfind('.') + 1; i < s.length(); i++) {
			year_ *= 10;
			year_ += s[i] - '0';
		}
	}

	date& operator =(const date& d) {
		if (this != &d) {
			day_ = d.day_;
			month_ = d.month_;
			year_ = d.year_;
		}
		return *this;
	}

	friend ostream& operator <<(ostream& out, const date& d) { 
        if (d.day_ < 10)
            out << "0" << d.day_ << ".";
        else
            out << d.day_ << ".";
        if (d.month_ < 10)
		    out << "0" << d.month_ << ".";
        else
            out << d.month_ << ".";
		out << d.year_;
		return out;
	}

	friend bool operator ==(const date& lhs, const date& rhs) {
		if (lhs.day_ == rhs.day_ && lhs.month_ == rhs.month_ && lhs.year_ == rhs.year_) {
			return true;
		}
		return false;
	}

	friend bool operator <(const date& lhs, const date& rhs) {
		int left = lhs.day_ + lhs.month_ * 30 + lhs.year_ * 365;
		int right = rhs.day_ + rhs.month_ * 30 + rhs.year_ * 365;
		if (left < right) {
			return true;
		}
		return false;
	}
};
class record {
public:
	record() {}
	record(const string& t, const string& cat, const date& d) :text_(t), date_(d), category_(cat) {}
	record(const record& r) :text_(r.text_), category_(r.category_), date_(r.date_) {}

    date get_date_() {
        return date_;
    }
    
    void set_date_(date d) {
        date_ = d;
    }
    
    string get_text_() {
        return text_;
    }
    
    void set_text_(string t) {
        text_ = t;
    }
    
    string get_category_() {
        return category_;
    }
    
    void set_category_(string c) {
        category_ = c;
    }

	record& operator = (const record& r) {
		if (this != &r) {
			text_ = r.text_;
			category_ = r.category_;
			date_ = r.date_;
		}
		return *this;
	}

	friend ostream& operator <<(ostream& out, const record& r) {
		out << "date:      " << r.date_ << "\n";
		out << "category:  " << r.category_ << "\n";
		out << "text:      " << r.text_ << "\n";
		return out;
	}

	void print(int max_length_cat, int max_length_text) {
		cout << "| " << date_ << " | ";
		cout.width(max_length_cat);
		cout << category_ << " | ";
		cout.width(max_length_text);
		cout << text_ << " | ";
	}

	friend bool operator <(const record& lhs, const record& rhs) {
		if (lhs.date_ < rhs.date_) {  //для сравнения категорий используем перегруженный оператор сравнения дат
			return true;
		}
		return false;
    }

private:
	friend class book;
	string text_;
	date date_;
	string category_;
};

class book {
	public:
	book() :count_(0), records_(nullptr) {}
    book(const book& b) {
        count_ = b.count_;
        records_ = new record[count_];
        copy(b.records_, b.records_ + count_, records_);
    }
	~book() { clear(); }

	void clear() {
		delete[] records_;
		records_ = nullptr;
		count_ = 0;
	}

    record* get_records_() {
        return records_;
    }

    int get_count_() {
        return count_;
    }

	void push_back(const record& r) {
		record* temp = new record[count_ + 1];
		copy(records_, records_ + count_, temp);
		temp[count_] = r;

		if (records_ != nullptr) {
			delete[]records_;
		}

		++count_;
		records_ = temp;
	}

	void show_all() {
		int max_length_cat = 0;
		int max_length_text = 0;

		for (size_t i = 0; i < count_; i++)
		{
			if (max_length_cat < records_[i].category_.length()) {
				max_length_cat = records_[i].category_.length();
			}
			if (max_length_text < records_[i].text_.length()) {
				max_length_text = records_[i].text_.length();
			}
		}

		for (size_t i = 0; i < count_; i++) {
			records_[i].print(max_length_cat, max_length_text);
			cout << "\n";
		}
	}

	const record& operator [] (size_t index) const {
		return records_[index];
	}

	record& operator [] (size_t index) {
		return records_[index];
	}

	void edit(const int& index, const record& r) { 
		records_[index] = r;
	}

	int filt_category(string cat) const {
		int max_length_cat = 0;
		int max_length_text = 0;
		int count_found = 0;
		for (size_t i = 0; i < count_; i++)
		{
			if (max_length_cat < records_[i].category_.length()) {
				max_length_cat = records_[i].category_.length();
			}
			if (max_length_text < records_[i].text_.length()) {
				max_length_text = records_[i].text_.length();
			}
		}

		for (size_t i = 0; i < count_; i++) {
			if (records_[i].category_ == cat) {
				records_[i].print(max_length_cat, max_length_text);
				cout << "\n";
				++count_found;
			}
		}
		return count_found;
	}

private:
	record* records_;
	int count_;
};

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

int main() {

	// SetConsoleCP(1251); // Ввод согласно регистру системы. 
	// SetConsoleOutputCP(1251); // Вывод согласно регистру системы.


	book b;

	b.push_back(record("Погулять с собакой", "Домашние обязанности", date(12, 07, 2002)));

	b.push_back(record("Постирать вещи", "Домашние обязанности", date(29, 07, 1995)));

	b.push_back(record("Помочь брату сделать уроки", "Домашние обязанности", date(29, 07, 1995)));

	b.push_back(record("Приготовить кушать", "Домашние обязанности", date(29, 07, 1995)));

	b.push_back(record("Погулять с Машей", "Отдых", date(30, 07, 1995)));

	b.push_back(record("Покататься на машине", "Отдых", date(31, 07, 1995)));

	b.push_back(record("Сходить в магазин", "Домашние обязанности", date(31, 07, 1995)));

	int a = menu(b);
	while (a != -1) {
		a = menu(b);
	}
}
