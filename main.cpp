// #include <windows.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
using namespace std::chrono;

struct date {
    int d;  // day
    int m;  // month
    int y;  // year
    bool valid; // valid datetime
    date(const date& date) {    // date a(b); // copy
        d = date.d;
        m = date.m;
        y = date.y;
        valid = date.valid; //valid - check date
    }
    date(string s) {
        valid = isValid(s);
    }
    date& operator=(const date& other) {    // date a = b;
        // Guard no self assignment
        if (this != &other) {
            d = other.d;
            m = other.m;
            y = other.y;
            valid = other.valid;
        }
        return *this;
	}
    // check valid datetime format xx.xx.xxxx
    bool isValid(string s)
    {
        if (s.length() != 10 && s[2] != '.' && s[5] != '.')
            return false;
        
        d = ( s[0] - '0' ) * 10 + ( s[1] - '0' );   // '12' -> ('1'-'0')*10 + ('2' - '0') = 1 * 10 + 2 = 12
        m = ( s[3] - '0' ) * 10 + ( s[4] - '0' );   // 'a2' -> 'a' - '0' = 31 -> 312
        y = ( s[6] - '0');
        for (int i = 7; i <= 9; i++)
            y = y * 10 + ( s[i] - '0' );
        
        if (y >= 1000 && y <= 2022)
        {
            // check leap year
            if ( (m == 2) && (d == 29) && 
               ( ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0) ))
                return true;
            if (( (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && (1 <= d && d <= 31) ) || 
                ( (m == 4 || m == 6 || m == 9 || m == 11) && (1 <= d && d <= 30) ) || 
                ( (m == 2) && (1 <= d && d <= 28) ))
                return true;
        }
        return false;
    }
    bool operator<(const date& other) const {
        return  ( y < other.y ) || 
                ( y == other.y && m < other.m ) || 
                ( y == other.y && m == other.m && d < other.d );
    }
    bool operator>(const date& other) const {
        return  ( y > other.y ) || 
                ( y == other.y && m > other.m ) || 
                ( y == other.y && m == other.m && d > other.d );
    }
    bool operator==(const date& other) const {
        return ( y == other.y ) && ( m == other.m ) && ( d == other.d );
    }
    // date to string
    string str() {
        string fmt = (d < 10)? "0" : "";
        fmt += to_string(d);
        fmt += (m < 10)? ".0" : ".";
        fmt += to_string(m) + "." + to_string(y);
        return fmt; // xx.xx.xxxx
    }
};

struct notebook {
    string content;
    string category;
    date datetime;

    notebook(string _content, string _category, date _datetime): // create a new notebook
        content(_content), category(_category), datetime(_datetime) {}
    notebook(const notebook &other): // notebook a(b)   -> copy other notebook
        content(other.content), category(other.category), datetime(other.datetime) {}
    notebook& operator=(const notebook &other) {    // notebook a = b
        if (this != &other) {
            content = other.content;
            category = other.category;
            datetime = other.datetime;
        }
        return *this;
    }
    // priority: datetime
    bool less(const notebook &other) {
        return datetime < other.datetime;
    }
    bool equal(const notebook &other) {
        return datetime == other.datetime;
    }
};

struct notebooks
{
    vector<notebook> lst;   // list of notebooks
    notebooks() { }
    int size() {
        return lst.size();  // number of notebooks
    }
    const notebook& operator[] (size_t index) const {
		return lst[index-1];
	}
    void _default() {   // read notebooks from file
        lst.erase(lst.begin(), lst.end());
        ifstream fin ( "notebooks.csv" );
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string content, category, tmp; 
            getline(ss, content, ','); 
            getline(ss, category, ','); 
            getline(ss, tmp, ','); // tmp = 18.03.1997
            date datetime(tmp);  // date(string s)
            if (datetime.valid) {
                notebook nb(content, category, datetime);
                lst.push_back(nb);
            }
        }
        fin.close();
    }
    void push(const notebook& nb) {     // add a notebook to list
        lst.push_back(nb);
    }
    void remove(size_t id) {    // remove a notebook by id
        auto it = lst.begin();  // pointer to beginning of list
        advance(it, id-1);      // increment pointer into id
        lst.erase(it);          // remove notebook
    }
    // quick sort implementation
    int partition(int start, int end) {
        int pivot = end;
        int j = start;
        for (int i = start; i < end; i++) {
            if (( lst[i].less(lst[pivot]) ) || 
                ( lst[i].equal(lst[pivot]) && lst[i].less(lst[pivot]) )) {
                swap(lst[i], lst[j]);
                j++;
            }
        }
        swap(lst[j], lst[pivot]);
        return j;
    }
    void quicksort(int start, int end) { // recursion
        if (start < end) {
            int mid = partition(start, end);
            quicksort(start, mid-1);
            quicksort(mid+1, end);
        }
    }
    void bubblesort() {
        for (int j = lst.size()-1; j > 0; j--) {
            for (int i = 0; i < j; i++) {
                if (( lst[i+1].less(lst[i])) || 
                    ( lst[i+1].equal(lst[i]) && lst[i+1].less(lst[i]) )) {
                    swap(lst[i], lst[i+1]);
                }
            }
        }
    }
    void sort(int tp) {
        if (tp == 1)
            quicksort(0, lst.size()-1);
        else 
            bubblesort();
    }
    void disp() {
        for (int i = 0; i < 80; i++) cout << "-";
        for (int i = 0; i < lst.size(); i++) {
            cout << endl <<  "| " << setw(2) << i+1 << " | ";
            cout << setw(30) << lst[i].content << " | ";
            cout << setw(30) << lst[i].category << " | ";
            cout << lst[i].datetime.str() << " | ";
        }
        cout << endl;
        for (int i = 0; i < 80; i++) cout << "-";
        cout << endl;
    }
    void disp_N(int n) {
        for (int i = 0; i < 80; i++) cout << "-";
        cout << endl <<  "| " << setw(2) << n+1 << " | ";
        cout << setw(30) << lst[n].content << " | ";
        cout << setw(30) << lst[n].category << " | ";
        cout << lst[n].datetime.str() << " | ";
        cout << endl;
        for (int i = 0; i < 80; i++) cout << "-";
        cout << endl;
    }
};

void menu() {
    cout << endl << "***** Menu *****" << endl;
    cout << "1. Добавить запись" << endl;
    cout << "2. Изменить запись" << endl;
    cout << "3. Удалить запись" << endl;
    cout << "4. Фильтр" << endl;
    cout << "5. Отсортировать массив" << endl;
    cout << "6. Посмотреть все записи" << endl;
    cout << "7. Читать данные из файла" << endl;
    cout << "8. Посчитать по датам" << endl;
    cout << "9. Посмотреть под номером" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите опцию -> ";
}

void add_job(notebooks &nbs) {
    string _content, _author, _category, tmp;
    cout << "Вводить запись:" << endl;
    cout << "Текст: "; cin >> _content;  // getline(cin, _content);
    cout << "Категория: "; cin >> _category;  //getline(cin, _category);
    cout << "Дата (в формате XX.XX.XXXX): "; cin >> tmp;  //getline(cin, tmp);
    date _date(tmp);
    if (_date.valid) {
        notebook nb(_content, _category, _date);
        nbs.push(nb);
        cout << "Запись успешно добавлена." << endl;
    } else {
        cout << "Ошибка: неверно введена дата" << endl;
    }
}

void update_job(notebooks& nbs) {
    cout << "Какую запись Вы хотите изменить? [1-" << nbs.size() << "]? ";
    int id; cin >> id;
    if (id >= 1 && id <= nbs.size()) {
        cout << "Что изменить (1 - текст, 2 - категорию, 3 - дату, 0 - выход)? ";
        int n; cin >> n;
        string tmp;
        while (1 <= n && n <= 3) {
            switch (n)
            {
            case 1:
                cout << "Введите текст: ";
                cin >> tmp;
                nbs.lst[id-1].content = tmp;
                break;
            case 2:
                cout << "Введите категорию: ";
                cin >> tmp;
                nbs.lst[id-1].category = tmp;
                break;
            default:
                cout << "Введите дату: ";
                cin >> tmp;
                date _date(tmp);
                if (_date.valid) {
                    nbs.lst[id-1].datetime = _date;
                } else {
                    cout << "Ошибка: неверно введена дата" << endl;
                }
                break;
            }
            cout << "Что изменить (1 - текст, 2 - категорию, 3 - дату, 0 - выход)? ";
            cin >> n;
        }
    } else {
        cout << "Ошибка: запись с таким номером не существует." << endl;
    }
}

void remove_job(notebooks& nbs) {
    cout << "Какую запись Вы хотите удалить [1-" << nbs.size() << "]? ";
    int id; cin >> id;
    if (id >= 1 && id <= nbs.size()) {
        nbs.remove(id);
    } else {
        cout << "Ошибка: запись с таким номером не существует." << endl;
    }
}

void search_job(notebooks& nbs) {   // allow filter by category, datetime interval
    cout << "Введите фильтр (1 - категория, 2 - дата): ";
    int filter; cin >> filter;
    if (filter != 2 && filter != 1) {
        cout << "Ошибка: фильтрация невозможна!" << endl;
    } else {
        if (filter == 2) {
            string start_filter, end_filter;
            cout << "Введите начальную дату (в формате XX.XX.XXXX): "; cin >> start_filter;  // getline(cin, start_filter);
            cout << "Введите конечную дату (в формате XX.XX.XXXX): "; cin >> end_filter;  // getline(cin, end_filter);
            date start(start_filter), end(end_filter);
            if (start.valid && end.valid) {
                for (int id = 1; id <= nbs.size(); ) {
                    if (end < nbs[id].datetime || nbs[id].datetime < start)
                        nbs.remove(id);
                    else
                        id++;
                }
            } else {
                cout << "Ошибка: неверно введена дата" << endl;
            }
        } else {    // 1
            cout << "Введите категорию: "; 
            string category_filter; cin >> category_filter;  // getline(cin, category_filter);
            for (int id = 1; id <= nbs.size(); ) {
                if (nbs[id].category.compare(category_filter) != 0) // nbs.list[id-1]
                    nbs.remove(id);
                else
                    id++;
            }
        }
        if (nbs.size() == 0) {
            cout << "Результат: не найдено." << endl;
            nbs._default();     // restore to default  
        } else {
            if (nbs.size() == 1)
                cout << "Результат: " << nbs.size() << " запись найдена." << endl;
            else
                cout << "Результат: " << nbs.size() << " записи найдено." << endl;
            nbs.disp();
        }
    }
}

void sort_job(notebooks& nbs) {
    cout << "Выберите алгоритм (1 - Быстрая сортировка, 2 - Сортировка пузырьком): ";
    int tp; cin >> tp;
    if (tp == 1 || tp == 2) {
        auto start = high_resolution_clock::now();
        nbs.sort(tp);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Результат: записи отсортированы (" << duration.count() << " микросекунд)"<< endl;
        nbs.disp();
    } else {
        cout << "Ошибка: неверно введен номер." << endl;
    }
}

void max_data_count(notebooks& nbs) {
    int n = 1;
    date maxDate = nbs[1].datetime;
    for (int i = 2; i <= nbs.size(); i++) {
        if (maxDate < nbs[i].datetime) {
            maxDate = nbs[i].datetime;
            n = 1;
        } else if (maxDate == nbs[i].datetime) {
            n++;
        }
    }
    cout << "Дата с наибольшим числом записей: " << maxDate.str() << endl;
    cout << "Количество найденных записей: " << n << endl;
}

void disp_N(notebooks& nbs) {
    cout << "Введите номер записи [1-" << nbs.size() << "]: ";
    int id; cin >> id;
    if (id >= 1 && id <= nbs.size()) {
        nbs.disp_N(id-1);
    } else {
        cout << "Ошибка: запись с таким номером не существует." << endl;
    }
}

bool process(notebooks &nbs) {
    menu();    
    int choice; cin >> choice;
    switch (choice) {
    case 1: 
        add_job(nbs); break;
    case 2:
        update_job(nbs); break;
    case 3:
        remove_job(nbs); break;
    case 4: 
        search_job(nbs); break;
    case 5:
        sort_job(nbs); break;
    case 6:
        nbs.disp(); break;
    case 7:
        nbs._default();
        cout << "Резуьтат: записи введены." << endl;
        break;
    case 8:
        max_data_count(nbs); break;
    case 9:
        disp_N(nbs); break;
    }
    return 1 <= choice && choice <= 9;
}

int main() {
    // SetConsoleOutputCP(1251);
    // SetConsoleCP(1251);
    notebooks tmp;
    tmp._default();
    tmp.disp();
    while (process(tmp));
    return 0;
}