#include "record.h"

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
