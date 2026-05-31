#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int H;
int W;
int ITER;

void init(int board[H][W]) {
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			board[i][j] = 0;
}

void print(int board[H][W]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == 1)
				putchar('0');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

void draw(int board[H][W]) {
	int row = 0;
	int pen = 0;
	int col = 0;
	char c;

	while(read(0, &c, 1) > 0) {
		if (c == 'w' && row > 0)
			row--;
		else if (c == 's' && row < H - 1)
			row++;
		else if (c == 'a' && col > 0)
			col--;
		else if (c == 'd' && col < W - 1)
			col++;
		else if (c == 'x')
			pen = !pen;

		if (pen)
			board[row][col] = 1;
	}
}

int count_nei(int board[H][W], int row, int col) {
	int nei = 0;

	for (int drow = -1; drow <= 1; drow++) {
		for (int dcol = -1; dcol <= 1; dcol++) {
			int nrow;
			int ncol;

			if (dcol == 0 && drow == 0)
				continue;

			nrow = row + drow;
			ncol = col + dcol;
			if (ncol >= 0 && ncol < W && nrow >= 0 && nrow < H && board[nrow][ncol] == 1)
				nei++;
		}
	}
	return nei;
}

void next_state(int board[H][W], int next[H][W]) {
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			int nei = count_nei(board, row, col);

			if (board[row][col] == 1) {
				if (nei == 2 || nei == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
			else {
				if (nei == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
		}
	}

}

void copy(int board[H][W], int next[H][W]) {
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			board[i][j] = next[i][j];
}

int main(int argc, char **argv) {
	if (argc != 4)
		return 1;

	W = atoi(argv[1]);
	H = atoi(argv[2]);
	ITER = atoi(argv[3]);

	int board[H][W];
	int next[H][W];

	init(board);

	draw(board);
	while (ITER-- > 0) {
		next_state(board, next);
		copy(board, next);
	}

	print(board);

	return 0;
}
