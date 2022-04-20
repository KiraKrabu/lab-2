#include <iostream>
#include <string>    //std::string, std::getline
// #include <Windows.h> //SetConsoleCP(1251); SetConsoleOutputCP(1251); !для русского языка в вижуалке(считать с консоли русский текст)!
#include <algorithm> //std::sort

class record;
class book;

struct date { //код для даты
	int day_;
	int month_;
	int year_;
	date() :day_(1), month_(1), year_(1) {}
	date(int d, int m, int y) :day_(d), month_(m), year_(y) {}
	date(const date& oth) :day_(oth.day_), month_(oth.month_), year_(oth.year_) {}
	date(std::string s) :day_(0), month_(0), year_(0) {

		for (int i = 0; s[i] != '.'; i++)
		{
			day_ *= 10;
			day_ += s[i] - '0';
		}

		for (int i = s.find('.') + 1; i < s.rfind('.'); i++)
		{
			month_ *= 10;
			month_ += s[i] - '0';
		}

		for (int i = s.rfind('.') + 1; i < s.length(); i++)
		{
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

	friend std::ostream& operator <<(std::ostream& out, const date& d) { 
		//out.width(2);
        if (d.day_ < 10)
            out << "0" << d.day_ << ".";
        else
            out << d.day_ << ".";
		//out.width(2);
        if (d.month_ < 10)
		    out << "0" << d.month_ << ".";
        else
            out << d.month_ << ".";
		//out.width(4);
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
private:
	friend class book; 
	std::string text_;
	date date_;
	std::string category_;

public:
	record() {}
	record(const std::string& t, const std::string& cat, const date& d) :text_(t), date_(d), category_(cat) {}
	record(const record& r) :text_(r.text_), category_(r.category_), date_(r.date_) {}

	record& operator = (const record& r) {
		if (this != &r) {
			text_ = r.text_;
			category_ = r.category_;
			date_ = r.date_;
		}
		return *this;
	}

	friend std::ostream& operator <<(std::ostream& out, const record& r) {
		out << "date:      " << r.date_ << "\n";
		out << "category:  " << r.category_ << "\n";
		out << "text:      " << r.text_ << "\n";
		return out;
	}


	void print(int max_length_cat, int max_length_text) {
		std::cout << "| " << date_ << " | ";
		std::cout.width(max_length_cat);
		std::cout << category_ << " | ";
		std::cout.width(max_length_text);
		std::cout << text_ << " | ";
	}

	friend bool operator <(const record& lhs, const record& rhs) {
		if (lhs.date_ < rhs.date_) {  
			return true;
		}
		return false;
	}

	friend int menu(book& b); 
};


class book {
	record* records_;
	int count_;
public:

	book() :count_(0), records_(nullptr) {}
	~book() { clear(); }

	void clear() {
		delete[] records_;
		records_ = nullptr;
		count_ = 0;
	}

	void push_back(const record& r) {
		record* temp = new record[count_ + 1];
		std::copy(records_, records_ + count_, temp); 
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
			std::cout << "\n";
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

	int filt_category(std::string cat) const {
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
				std::cout << "\n";
				++count_found;
			}
		}
		return count_found;
	}

	friend int menu(book& b);

};

int menu(book& b) { 
	int num;
	std::cout << "1 - Перезаписать массив даннных\n";
	std::cout << "2 - Посмотреть все записи\n";
	std::cout << "3 - Отсортировать массив по датам\n";
	std::cout << "4 - Посмотртеть под номером N\n";
	std::cout << "5 - Изменить под номером N\n";
	std::cout << "6 - Фильтр\n";
	std::cout << "7 - Посчитать\n";
	std::cout << "8 - Добавить запись\n";
	std::cout << "9 - Выйти\n";
	std::cout << '\n';
	std::cin >> num;
	if (num == 1) {
		system("cls");
		b.clear();
		std::cout << "Введите количество элементов\n";
		int count;
		std::cin >> count;
		for (size_t i = 0; i < count; i++)
		{
			std::cout << "\n\nВведите текст\n";
			std::string text;
			std::cin.ignore();	
			std::getline(std::cin, text);
			std::cout << "Введите категорию\n";
			std::string cat;
			std::cin.ignore();
			std::getline(std::cin, cat);
			std::cout << "Введите дату в формате XX.XX.XXXX\n";
			std::string d;
			std::cin.ignore();
			std::getline(std::cin, d);
			b.push_back(record(text, cat, date(d)));
		}
		system("cls");

		return 0;
	}
	if (num == 2) { 
		system("cls");
		b.show_all();
		std::cout << "Введите 0, чтобы вернуться в главное меню\n";
		std::cin >> num;
		system("cls");
		return 0;
	}

	if (num == 3) { 
		std::sort(b.records_, b.records_ + b.count_);	
		system("cls");
		std::cout << "\nКнига отсортирована\n\n";

		return 0;
	}
	if (num == 4) { 
		system("cls");
		std::cout << "Введите номер записи не больше " << b.count_ << " (нумерация начинается с 1)\n";
		int index;
		std::cin >> index;
		std::cout << b.records_[index - 1];
		std::cout << "\nВведите 0, чтобы вернуться в главное меню\n";
		std::cin >> num;
		system("cls");
		return 0;
	}

	if (num == 5) { 
		system("cls");
		std::cout << "Введите номер записи не больше " << b.count_ << " (нумерация начинается с 1)\n";
		int index;
		std::cin >> index;
		--index;
		std::cout << "Что изменить?\n1 - изменить дату\n2 - изменить категорию\n3 - изменить текст\n\n";
		int task;
		std::cin >> task;

		if (task == 1) {
			std::cout << "Введите дату в формате XX.XX.XXXX\n";
			std::string d;
			std::cin.ignore();
			std::getline(std::cin, d);
			b[index].date_ = date(d);
			system("cls");
			std::cout << "\nИзменения сохранены успешно \n\n";
			return 0;
		}
		else if (task == 2) {
			std::cout << "Введите категорию\n";
			std::string cat;
			std::cin.ignore();
			std::getline(std::cin, cat);
			b[index].category_ = cat;
			system("cls");
			std::cout << "\nИзменения сохранены успешно \n\n";
			return 0;
		}
		else if (task == 3) {
			std::string text;
			std::cin.ignore();
			std::getline(std::cin, text);
			b[index].text_ = text;
			system("cls"); 
			std::cout << "\nИзменения сохранены успешно \n\n";
			return 0;
		}
		std::cout << "\nНеверный номер\n\n";
		return 0;
	}

	if (num == 6) { 
		system("cls");
		std::cout << "Введите категорию\n";
		std::string cat;
		std::cin.ignore();
		std::getline(std::cin, cat);

		int count_found = b.filt_category(cat);

		if (count_found == 0) {
			std::cout << "\nТакой категории нет\n\n";
		}

		std::cout << "\nВведите 0, чтобы вернуться в главное меню\n";
		std::cin >> num;
		system("cls");
		return 0;
	}

	if (num == 7) { 
		system("cls");
		int max_count = 0;
		date max_date;
		for (size_t i = 0; i < b.count_; i++) 
		{

			int temp_count = 0;
			for (size_t j = 0; j < b.count_; j++) 
			{
				if (b[i].date_ == b[j].date_) {
					++temp_count;
				}
			}
			if (temp_count > max_count) {
				max_count = temp_count;
				max_date = b[i].date_;
			}
		}
		std::cout << "\nМаксимальное число записей = " << max_count << "\nДата = " << max_date << "\n";
		std::cout << "\nВведите 0, чтобы вернуться в главное меню\n";
		std::cin >> num;
		system("cls");
		return 0;
	}


	if (num == 8) { 
		std::cout << "Введите текст\n";
		std::string text;
		std::cin.ignore();
		std::getline(std::cin, text);
		std::cout << "Введите категорию\n";
		std::string cat;
		std::cin.ignore();
		std::getline(std::cin, cat);
		std::cout << "Введите дату в формате XX.XX.XXXX\n";
		std::string d;
		std::cin.ignore();
		std::getline(std::cin, d);
		b.push_back(record(text, cat, date(d))); 
		system("cls");
		std::cout << "\nЗапись добавлена\n\n";

		return 0;
	}
	// if (num == 9) { 
		return -1;
	// }
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
