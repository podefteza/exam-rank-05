#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void init_board(int h, int w, int board[h][w]) {
	for (int i = 0; i < h; i++)
		for (int k = 0; k < w; k++)
			board[i][k] = 0;
}

void print_board(int h, int w, int board[h][w]) {
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			if (board[i][k] == 1)
				putchar('0');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

void draw_board(int h, int w, int board[h][w]) {
	int row = 0;
	int col = 0;
	int pen = 0;
	char c;

	while (read(0, &c, 1) > 0) {
		if (c == 'w' && row > 0)
			row--;
		else if (c == 's' && row < h - 1)
			row++;
		else if (c == 'a' && col > 0)
			col--;
		else if (c == 'd' && col < w - 1)
			col++;
		else if (c== 'x')
			pen = !pen;

		if (pen)
			board[row][col] = 1;
	}
}

int count_neighbors(int h, int w, int board[h][w], int row, int col) {
	int n = 0;

	for (int drow = -1; drow <= 1; drow++) {
		for (int dcol = -1; dcol <= 1; dcol++) {
			int nrow;
			int ncol;

			if (dcol == 0 && drow == 0)
				continue ;
			nrow = row + drow;
			ncol = col + dcol;
			if (ncol >= 0 && ncol < w && nrow >= 0 && nrow < h)
				n += board[nrow][ncol];
		}
	}
	return n;
}

void next_state(int h, int w, int board[h][w], int next[h][w]) {
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int n = count_neighbors(h, w, board, row, col);

			if (board[row][col] == 1) {
				if (n == 2 || n == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
			else {
				if (n == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
		}
	}
}

void copy_board(int h, int w, int board[h][w], int next[h][w]) {
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			board[i][j] = next[i][j];
}

int main(int argc, char **argv) {
	if (argc != 4)
		return 1;

	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int iter = atoi(argv[3]);

	int board[h][w];
	int next[h][w];

	init_board(h, w, board);
	draw_board(h, w, board);

	while (iter-- > 0) {
		next_state(h, w, board, next);
		copy_board(h, w, board, next);
	}

	print_board(h, w, board);


	return 0;
}
