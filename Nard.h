#pragma once
#include <tuple>

enum Color {
	Black = 0,
	White,
	Void
};

class Hole {
public:
	int amount;
	Color color;

	Hole() {
		amount = 0;
		color = Color::Void;
	}

	Hole(int a, Color c) {
		amount = a;
		color = c;
	}
};


using namespace std;
class Nard {

public:
	Nard() {
		table[0][0] = Hole(15, Color::White);
		table[1][0] = Hole(15, Color::Black);
	}

	/*
	 * Передвигаем шашку с позиции (i, j) на to позиций
	 */
	bool move(int i, int j, int to) {
		Hole *current = &table[i][j]; // Получает текущую лунку
		Hole *to_hole;

		j += to;
		if(j > 9) {
			if(is_winner_zone(current->color)) { // Проверка на зону победителя
				amount_winners_checker[current->color]++;//Добавляем шашку в победный счет
				goto END;//Переход на метку конца функции
			}
			if(current->color == i) {
				return false;
			}
			i = !i;
			j = j - 10;
		}

		to_hole = &table[i][j];

		if(current->color != to_hole->color && to_hole->amount != 0) //Проверка на позицию, в которую хочет встать шашка
				return false;

		to_hole->amount++;
		to_hole->color = current->color;
END:
		current->amount--;
		return true;
	}

	/*
	 * Получаем победитя игры.
	 * Если победителя нет - возвращаем VOID.
	 */
	Color get_winner() {
		if(amount_winners_checker[0] < 15 && amount_winners_checker[1] < 15) {
			return Color::Void;
		}
		return amount_winners_checker[0] > amount_winners_checker[1] ? Color::Black : Color::White;

	}

	/*
	 * Получаем лунку по позиции (i, j)
	 */
	Hole *get_hole(int i, int j) {
		return &table[i][j];
	}

	/*
	 * Отрисовываем поле нардов
	 */
	void draw() {
		for(int i = 10; i > 0; i--) cout << " " << i << "  "; cout << endl;
		cout << "┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓\n";

		for(int i = 0; i < 2; i++) {
			cout << "┃";
			if(i == 0) {
				for(int j = 9; j >= 0; j--) {
					draw_current(i, j);
				}
			} else {
				for(int j = 0; j < 10; j++) {
					draw_current(i, j);
				}
			}

			cout << " Выведенных: " << amount_winners_checker[i] << endl;

			if(i == 0) {
				for(int k = 0; k < 7; k++) {
					cout << "┃                   ┃                   ┃\n";
				}
			}
		}

		cout << "┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛\n";
		for(int i = 1; i <= 10; i++) cout << "  " << i << " "; cout << endl;
	}

private:
	Hole table[2][10];
	int amount_winners_checker[2] = {0, 0};

	/*
	 * Проверка на "победную зону"
	 */
	bool is_winner_zone(Color checker_color) {
		int winning_row = checker_color == Color::Black ? 0 : 1;
		int sum = amount_winners_checker[checker_color];//Добавляем к сумме, выведенные шашки.
		for(int i = 5; i < 10; i++) {
			if(checker_color == table[winning_row][i].color) {
				sum += table[winning_row][i].amount;
			}
		}
		return sum == 15;
	}

	void draw_current(int i, int j) {
		Hole current = table[i][j];
		if(current.amount == 0) {
			cout << "   ";
		} else {
			if(current.amount < 10)
				cout << ' ';
			cout << current.amount << (current.color == Color::Black ? "ч" : "б");
		}
		cout << "┃";
	}
};
