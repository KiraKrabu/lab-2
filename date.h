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