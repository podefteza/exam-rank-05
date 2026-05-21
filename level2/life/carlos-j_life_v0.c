#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void init_board(int height, int width, int board[height][width])
{
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			board[row][col] = 0;
}

static void draw_board(int height, int width, int board[height][width])
{
	int penrow = 0;
	int pencol = 0;
	int pen = 0;
	char c;

	while (read(0, &c, 1) > 0)
	{
		if (c == 'w' && penrow > 0)
			penrow--;
		else if (c == 's' && penrow < height - 1)
			penrow++;
		else if (c == 'a' && pencol > 0)
			pencol--;
		else if (c == 'd' && pencol < width - 1)
			pencol++;
		else if (c == 'x')
			pen = !pen;

		if (pen)
			board[penrow][pencol] = 1;
	}
}

static int count_neighbors(int height, int width, int board[height][width], int row, int col)
{
	int n = 0;

	for (int drow = -1; drow <= 1; drow++)
	{
		for (int dcol = -1; dcol <= 1; dcol++)
		{
			int nrow;
			int ncol;

			if (dcol == 0 && drow == 0)
				continue;
			nrow = row + drow;
			ncol = col + dcol;
			if (ncol >= 0 && ncol < width && nrow >= 0 && nrow < height)
				n += board[nrow][ncol];
		}
	}
	return n;
}

static void compute_next_state(int height, int width, int board[height][width], int next[height][width])
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int n = count_neighbors(height, width, board, row, col);

			if (board[row][col] == 1)
			{
				if (n == 2 || n == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
			else
			{
				if (n == 3)
					next[row][col] = 1;
				else
					next[row][col] = 0;
			}
		}
	}
}

static void copy_board(int height, int width, int source[height][width], int destination[height][width])
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
			destination[row][col] = source[row][col];
	}
}

static void print_board(int height, int width, int board[height][width])
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
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
		return (0);

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iter = atoi(argv[3]);

	int board[height][width];
	int next[height][width];

	init_board(height, width, board);
	draw_board(height, width, board);
	while (iter-- > 0) {
		compute_next_state(height, width, board, next);
		copy_board(height, width, next, board);
	}

	print_board(height, width, board);

	return (0);
}
