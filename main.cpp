#include <iostream>
#include "Nard.h"
#include <unistd.h>
#include <tuple>

using namespace std;

tuple<int, int> generate_cubes();

int main() {

	srand(time(NULL));

	system("clear");

	Nard nard = Nard();

	tuple<int, int> generated_numbers = generate_cubes();// Генерация два кубика для определния стороны, которая будет ходить первой
	int black_c = get<0>(generated_numbers), white_c = get<1>(generated_numbers);

	cout << "Через жеребьевку будет определ тот, кто будет ходить первым." << endl;
	cout << "Черному вылало выпало " << black_c << "\nБелому выпало " << white_c << endl;

	Color current_turn = black_c >= white_c ? Color::Black : Color::White;

	while(true) {
		int i, j, turn_length;
		bool is_second = false, additional_turn = false;

		tuple<int, int> cubes = generate_cubes();
		int cube1 = get<0>(cubes), cube2 = get<1>(cubes);

		if(cube1 == cube2)
			additional_turn = true;

BAD_ANSWER:
		nard.draw();
		cout << "Сейчас ход: " << (current_turn == Color::Black ? "черный" : "белый") << endl;

		cout << "Вам выпало: " << cube1 << " и " << cube2 << endl;
		if(additional_turn) {
			cout << "Вам доступен дополнительный ход!" << endl;
		}

		cout << "Выберите строку и колонну шашки, которую хотите переместить: ";
		cin >> i >> j;
		Hole *hole = nard.get_hole(i - 1, j - 1);
		if(hole->color != current_turn || hole->amount == 0) { //Если это не наша клетка, либо на клетке никого
			system("clear");
			cout << "ВЫ ВЫБРАЛИ НЕ ВАШУ КЛЕТКУ ЛИБО ПУСТУЮ КЛЕТКУ!" << endl;
			goto BAD_ANSWER;
		}
		if(!is_second) {
			cout << "Выберите длину хода(1 или 2 куб): ";
			cin >> turn_length;
		} else {
			turn_length = turn_length == 1 ? 2 : 1;
		}

		if(!nard.move(i - 1, j - 1, turn_length == 1 ? cube1 : cube2)) {
			system("clear");
			cout << "Вы не можете сделать шаг на данную клетку." << endl;
			goto BAD_ANSWER;
		}

		Color winner = nard.get_winner();
		if(winner != Color::Void) {
			cout << "Победил " << (winner == Color::Black ? "черный" : "белый") << "! Поздравляем!!!" << endl;
			break;
		}

		if(!is_second) { //Второй куб
			is_second = true;
			system("clear");
			goto BAD_ANSWER;
		}

		if(additional_turn) { //Проверка на дополнительный ход.
			is_second = false;
			additional_turn = false;
			system("clear");
			goto BAD_ANSWER;
		}

		current_turn = current_turn == Color::Black ? Color::White : Color::Black; //Смена стороны

		system("clear");

	}
}

tuple<int, int> generate_cubes() {
	return make_tuple(rand() % 6 + 1, rand() % 6 + 1);
}
