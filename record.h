#include <iostream>
#include <string>
#include "date.h"
using namespace std;

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
