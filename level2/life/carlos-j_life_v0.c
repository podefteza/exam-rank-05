#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int HEIGHT;
int WIDTH;
int ITER;

static void init_board(int board[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++)
		for (int col = 0; col < WIDTH; col++)
			board[row][col] = 0;
}

static void draw_board(int board[HEIGHT][WIDTH]) {
	int penrow = 0;
	int pencol = 0;
	int pen = 0;
	char c;

	while (read(0, &c, 1) > 0) {
		if (c == 'w' && penrow > 0)
			penrow--;
		else if (c == 's' && penrow < HEIGHT - 1)
			penrow++;
		else if (c == 'a' && pencol > 0)
			pencol--;
		else if (c == 'd' && pencol < WIDTH - 1)
			pencol++;
		else if (c == 'x')
			pen = !pen;

		if (pen)
			board[penrow][pencol] = 1;
	}
}

static int count_neighbors(int board[HEIGHT][WIDTH], int row, int col) {
	int neighbors = 0;

	for (int drow = -1; drow <= 1; drow++) {
		for (int dcol = -1; dcol <= 1; dcol++) {
			int nrow;
			int ncol;

			if (dcol == 0 && drow == 0)
				continue;
			nrow = row + drow;
			ncol = col + dcol;
			if (ncol >= 0 && ncol < WIDTH && nrow >= 0 && nrow < HEIGHT)
				neighbors += board[nrow][ncol];
		}
	}
	return neighbors;
}

static void compute_next_state(int board[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++) {
		for (int col = 0; col < WIDTH; col++) {
			int neighbors = count_neighbors(board, row, col);

			if (board[row][col] == 1) {
				if (neighbors == 2 || neighbors == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
			else {
				if (neighbors == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
		}
	}
}

static void copy_board(int board[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++)
		for (int col = 0; col < WIDTH; col++)
			board[row][col] = next[row][col];
}

static void print_board(int board[HEIGHT][WIDTH]) {
	for (int row = 0; row < HEIGHT; row++) {
		for (int col = 0; col < WIDTH; col++) {
			if (board[row][col] == 1)
				putchar('O');
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
