#include <iostream>
#include "Nard.h"
#include <unistd.h>
#include <cstdlib>
#include <tuple>

using namespace std;

tuple<int, int> generate_cubes();

int main() {

	srand(time(NULL));

	Nard nard = Nard();

	Color current_turn = Color::Black;

	while(true) {

		int i, j, turn_length;
		nard.draw();

		tuple<int, int> cubes = generate_cubes();
		int cube1 = get<0>(cubes), cube2 = get<1>(cubes);
		cout << "Вам выпало: " << cube1 << " и " << cube2 << endl;
		if(cube1 == cube2) {
			cout << "Вам доступен дополнительный ход!" << endl;
		}

BAD_ANSWER:
		cout << "Выберите строку и колонну шашки, которую хотите переместить: ";
		cin >> i >> j;
		Hole *choosed = nard.get_hole(i - 1, j - 1);
		if(choosed->color != current_turn) {
			cout << "ВЫ ВЫБРАЛИ НЕ ВАШУ КЛЕТКУ ЛИБО ПУСТУЮ КЛЕТКУ!" << endl;
			goto BAD_ANSWER;
		}
		cout << "ВЫберите длину хода(1 или 2 куб): ";
		cin >> turn_length;

		nard.move(i - 1, j - 1, turn_length == 1 ? cube1 : cube2);

		current_turn = current_turn == Color::Black ? Color::White : Color::Black;

//		system("clear");
	}
}

tuple<int, int> generate_cubes() {
	return make_tuple(rand() % 6 + 1, rand() % 6 + 1);
}
