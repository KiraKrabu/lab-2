// #include <Windows.h>	// for Windows only
#include "menu.h"

int main() {
	// SetConsoleCP(1251); // Ввод согласно регистру системы. 
	// SetConsoleOutputCP(1251); // Вывод согласно регистру системы.

	book b;
	b.push_back(record("Погулять с собакой", "Домашние обязанности", date(12, 07, 2002)));
	b.push_back(record("Покататься на машине", "Отдых", date(31, 07, 1995)));
	b.push_back(record("Постирать вещи", "Домашние обязанности", date(29, 07, 1995)));
	b.push_back(record("Погулять с Машей", "Отдых", date(30, 07, 1995)));
	b.push_back(record("Помочь брату сделать уроки", "Домашние обязанности", date(29, 07, 1995)));
	b.push_back(record("Приготовить кушать", "Домашние обязанности", date(29, 07, 1995)));
	b.push_back(record("Сходить в магазин", "Домашние обязанности", date(31, 07, 1995)));

	int a = menu(b);
	while (a != -1) {
		a = menu(b);
	}
}