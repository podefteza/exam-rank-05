#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int HEIGHT;
int WIDTH;
int ITER;

void init_board(int board[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++)
		for (int col = 0; col < WIDTH; col++)
			board[row][col] = 0;
}

void draw_board(int board[HEIGHT][WIDTH]) {
	int row = 0;
	int col = 0;
	int pen = 0;
	char c;

	while (read(0, &c, 1) > 0) {
		if (c == 'w' && row > 0)
			row--;
		else if (c == 's' && row < HEIGHT - 1)
			row++;
		else if (c == 'a' && col > 0)
			col--;
		else if (c == 'd' && col < WIDTH - 1)
			col++;
		else if (c == 'x')
			pen = !pen;

		if (pen)
			board[row][col] = 1;
	}
}

int count_neighbors(int board[HEIGHT][WIDTH], int row, int col) {
	int neighbors = 0;

	for (int drow = -1; drow <= 1; drow++) {
		for (int dcol = -1; dcol <= 1; dcol++) {
			int nrow = row + drow;
			int ncol = col + dcol;

			if (nrow < 0 || nrow >= HEIGHT || ncol < 0 || ncol >= WIDTH || (drow == 0 && dcol == 0))
				continue;

			if (board[nrow][ncol] == 1)
				neighbors++;
		}
	}
	return neighbors;
}

void compute_next_state(int board[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++) {
		for (int col = 0; col < WIDTH; col++) {
			int neighbors = count_neighbors(board, row, col);

			if (board[row][col] == 1)
				next[row][col] = (neighbors == 2 || neighbors == 3);
			else
				next[row][col] = (neighbors == 3);
		}
	}
}

void copy_board(int board[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++)
		for (int col = 0; col < WIDTH; col++)
			board[row][col] = next[row][col];
}

void print_board(int board[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++) {
		for (int col = 0; col < WIDTH; col++) {
			if (board[row][col] == 1)
				putchar('0');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

int main(int argc, char **argv) {
	if (argc != 4)
		return (1);

	WIDTH = atoi(argv[1]);
	HEIGHT = atoi(argv[2]);
	ITER = atoi(argv[3]);

	int board[HEIGHT][WIDTH];
	int next[HEIGHT][WIDTH];

	init_board(board);
	draw_board(board);
	while (ITER-- > 0) {
		compute_next_state(board, next);
		copy_board(board, next);
	}

	print_board(board);

	return (0);
}
