#pragma once

enum Color {
	Void = 0,
	Black,
	White
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

class Nard {
private:
	Hole table[2][10];

public:
	Nard() {
		table[0][0] = Hole(15, Color::White);
		table[1][0] = Hole(15, Color::Black);
	}

	void move(int i, int j, int to) {
		Hole *current = &table[i][j];
		if(j + to > 9) {
			i = i == 0 ? 1 : 0;
			j = j + to - 10;
			std::cout << j << std::endl;
		} else {
			j += to;
		}
		Hole *to_hole = &table[i][j];

		current->amount--;
		to_hole->amount++;
		to_hole->color = current->color;
	}

	Hole *get_hole(int i, int j) {
		return &table[i][j];
	}

	void draw() {
		std::cout << "┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓\n";

		for(int i = 0; i < 2; i++) {
			std::cout << "┃";
			if(i == 0) {
				for(int j = 9; j >= 0; j--) {
					draw_current(i, j);
				}
			} else {
				for(int j = 0; j < 10; j++) {
					draw_current(i, j);
				}
			}

			std::cout << '\n';

			if(i == 0) {
				for(int k = 0; k < 7; k++) {
					std::cout << "┃                   ┃                   ┃\n";
				}
			}
		}

		std::cout << "┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛\n";
	}

	void draw_current(int i, int j) {
		Hole current = table[i][j];
		if(current.amount == 0) {
			std::cout << "   ";
		} else {
			if(current.amount < 10)
				std::cout << ' ';
			std::cout << current.amount << (current.color == Color::Black ? "ч" : "б");
		}
		std::cout << "┃";
	}

};

