#pragma once

enum Color {
	Void,
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
		table[0][9] = Hole(15, Color::White);
		table[1][0] = Hole(15, Color::Black);
	}

	void move(int i, int j) {
		table[i][j].amount--;
		table[i][j - 1].amount++;
		table[i][j - 1].color = table[i][j].color;
	}

	void draw() {
		std::cout << "┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓\n";

		for(int i = 0; i < 2; i++) {
			std::cout << "┃";
			for(int j = 0; j < 10; j++) {
				Hole current = table[i][j];
				if(current.color == Color::Void) {
					std::cout << "   ";
				} else {
					if(current.amount < 10)
						std::cout << ' ';
					std::cout << current.amount << (current.color == Color::Black ? "ч" : "б");
				}
				std::cout << "┃";
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

};

