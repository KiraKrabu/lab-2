#include <iostream>
#include <string>
 
class record;
class book;
 
 
struct date {
	int day_;
	int month_;
	int year_;
	date() :day_(1), month_(1), year_(1) {}
	date(int d, int m, int y) :day_(d), month_(m), year_(y) {}
	date(const date& oth) :day_(oth.day_), month_(oth.month_), year_(oth.year_) {}
	date(std::string s):day_(0), month_(0), year_(0) {
 
		for (int i = 0; s[i]!='.'; i++)
		{
			day_ *= 10;
			day_ += s[i] - '0';
		}
 
		for (int i = s.find('.')+1; i<s.rfind('.'); i++)
		{
			month_ *= 10;
			month_ += s[i] - '0';
		}
 
		for (int i = s.rfind('.')+1; i<s.length(); i++)
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
 
	 void print() {
		std::cout << day_ << "." << month_ << "." << year_;
	}
 
	friend std::ostream& operator <<(std::ostream& out, const date& d) {
		out << d.day_ << "." << d.month_ << "." << d.year_;
		return out;
	}
 
 
 
	friend bool operator ==(const date& lhs, const date& rhs) {
		if (lhs.day_ == rhs.day_ && lhs.month_ == rhs.month_ && lhs.year_ == rhs.year_) {
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
 
	void print()const {
		std::cout << "date:      " << date_ << "\n";
		std::cout << "category:  " << category_ << "\n";
		std::cout << "text:      " << text_ << "\n";
	}
 
};
 
class book {
	record* records_;
	int count_;
 
public:
 
	book() :count_(0), records_(nullptr) {}
	~book() { clear(); }
 
	void clear() {
		delete[] records_;
		count_ = 0;
	}
 
	void push_back(const record& r) {
		record* temp = new record[count_ + 1];
		std::copy(records_, records_ + count_, temp);
		temp[count_] = r;
		++count_;
		delete[]records_;
		records_ = temp;
	}
 
	void show_all() {
		for (size_t i = 0; i < count_; i++) {
			std::cout << i + 1 << ")\n";
			std::cout << records_[i] << "\n";
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
 
	void filt_category(std::string cat) const {
		for (size_t i = 0; i < count_; i++)
		{
			if (records_[i].category_ == cat) {
				std::cout << records_[i] << "\n";
			}
		}
	}
 
 
	void filt_date(const date& d) const {
		for (size_t i = 0; i < count_; i++)
		{
			if (records_[i].date_ == d) {
				std::cout << records_[i] << "\n";
			}
		}
	}
 
};
 
 
 
void menu(book &b) {
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
 
	std::cin >> num;
	if (num == 2) {
		b.show_all();
	}
	if (num == 8) {
		std::cout << "Введите текст\n";
		std::string text;
		std::getline(std::cin, text);
		std::getline(std::cin, text);
		std::cout << "Введите категорию\n";
		std::string cat;
		std::getline(std::cin, cat);
		std::cout << "Введите дату в формате XX.XX.XXX\n";
		std::string d;
		std::getline(std::cin, d);
		b.push_back(record(text, cat, date(d)));
		system("cls");
		menu(b);
	}
 
}
 
 
int main() {
 
 
	SetConsoleCP(1251); // Ввод согласно регистру системы. 
	SetConsoleOutputCP(1251); // Вывод согласно регистру системы.
 
 
	book b;
 
	b.push_back(record("hello", "kak", date(12, 8, 2002)));
 
	b.push_back(record("poka", "not", date(29, 7, 1995)));
 
 
	menu(b);
}
