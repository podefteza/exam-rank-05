#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 4)
		return 0;

	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int iter = atoi(argv[3]);

	int board[h][w];
	int next[h][w];

	for (int r = 0; r < h; r++)
		for (int c = 0; c < w; c++)
			board[r][c] = 0;

	int pen_r = 0, pen_c = 0, pen = 0;
	char car;
	while (read(0, &car, 1) > 0)
	{
		if (car == 'w' && pen_r > 0)
			pen_r--;
		else if (car == 's' && pen_r < h - 1)
			pen_r++;
		else if (car == 'a' && pen_c > 0)
			pen_c--;
		else if (car == 'd' && pen_c < w - 1)
			pen_c++;
		else if (car == 'x')
			pen = !pen;

		if (pen)
			board[pen_r][pen_c] = 1;
	}

	while (iter-- > 0)
	{
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < w; c++)
			{
				int n = 0;
				for (int dr = -1; dr <= 1; dr++)
				{
					for (int dc = -1; dc <= 1; dc++)
					{
						if (dc == 0 && dr == 0)
							continue;

						int nr = r + dr;
						int nc = c + dc;
						if (nc >= 0 && nc < w && nr >= 0 && nr < h)
							n += board[nr][nc];
					}
				}
				if (board[r][c] == 1)
				{
					if (n == 2 || n == 3)
						next[r][c] = 1;
					else
						next[r][c] = 0;
				}
				else
				{
					if (n == 3)
						next[r][c] = 1;
					else
						next[r][c] = 0;
				}
			}
		}
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < w; c++)
			{
				board[r][c] = next[r][c];
			}
		}
	}

	for (int r = 0; r < h; r++)
	{
		for (int c = 0; c < w; c++)
		{
			if (board[r][c] == 1)
				putchar('0');
			else
				putchar(' ');
		}
		putchar('\n');
	}

	return (0);
}
