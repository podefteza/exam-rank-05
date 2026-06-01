#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int HEIGHT;
int WIDTH;
int ITER;

void init(int board[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			board[i][j] = 0;
}

void print(int board[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] == 1)
				putchar('0');
			else
				putchar(' ');
		}
		putchar('\n');
	}
	//printf("_____________\n");
}

void draw(int board[HEIGHT][WIDTH]) {
	int col = 0;
	int row = 0;
	int pen = 0;
	char c;

	while (read(0, &c, 1) > 0) {
		if(c == 'w' && row > 0)
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

int count(int board[HEIGHT][WIDTH], int row, int col) {
	int nei = 0;

	for (int drow = -1; drow <= 1; drow++) {
		for (int dcol = -1; dcol <= 1; dcol++) {
			int nrow = 0;
			int ncol = 0;
			nrow = row + drow;
			ncol = col + dcol;



			if (board[nrow][ncol] == 1)
				nei++;
		}
	}
	return nei;
}

void change(int board[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
	// 1 && 2/3 > 1
	// 0 && 3 > 1

	for (int row = 0; row < HEIGHT; row++) {
		for (int col = 0; col < WIDTH; col++) {
			int nei = 0;
			nei = count(board, row, col);
			//printf("nei of cell %d %d: %d\n", row, col, nei);
			if ((board[row][col] == 1 && nei >= 2 && nei <= 3) || (nei == 3))
				next[row][col] = 1;
			else
				next[row][col] = 0;
		}
	}
}

void copy(int board[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			board[i][j] = next[i][j];
}

int main(int argc, char **argv) {
	if (argc != 4)
		return 1;

	WIDTH = atoi(argv[1]);
	HEIGHT = atoi(argv[2]);
	ITER = atoi(argv[3]);

	int board[HEIGHT][WIDTH];
	int next[HEIGHT][WIDTH];

	init(board);
	draw(board);

	//print(board);

	while (ITER-- > 0) {
		change(board, next);
		copy(board, next);
	}

	print(board);

	return 0;
}
