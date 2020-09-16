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

	while(true) {

		int i, j;
		nard.draw();

		tuple<int, int> cubes = generate_cubes();
		int cube1 = get<0>(cubes), cube2 = get<1>(cubes);
		cout << "Вам выпало: " << cube1 << " и " << cube2 << endl;
		if(cube1 == cube2) {
			cout << "Вам доступен дополнительный ход!" << endl;
		}

		cout << "Выберите строку и колонну шашки, которую хотите переместить: ";
		cin >> i >> j;

		nard.move(i - 1, j - 1);

		system("clear");
	}
}

tuple<int, int> generate_cubes() {
	return make_tuple(rand() % 6 + 1, rand() % 6 + 1);
}
