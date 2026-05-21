#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	/*
	 * Program entry and argument parsing
	 * Expected: ./life width height iterations
	 */
	if (argc != 4)
		return (0);

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iter = atoi(argv[3]);

	/*
	 * Boards: `board` holds the current state, `next` is used to compute the
	 * following state for each iteration. These are variable-length arrays
	 * allocated on the stack using the provided width/height.
	 */
	int board[height][width];
	int next[height][width];

	/*
	 * Initialize the board to all-dead (0). This sets the starting state
	 * before any drawing commands from stdin are processed.
	 */
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			board[row][col] = 0;

	/*
	 * Read drawing commands from standard input one byte at a time. A pen
	 * starts at the top-left corner (x=0,y=0) and is initially not drawing.
	 * Commands:
	 *  - 'w','a','s','d' : move pen up,left,down,right (clamped to board)
	 *  - 'x'            : toggle pen (lift/lower)
	 * After each command the program marks the current cell as alive (1)
	 * if the pen is down.
	 */
	int pen_row = 0, pen_col = 0, pen = 0;
	char c;
	while (read(0, &c, 1) > 0) {
		if (c == 'w' && pen_row > 0)
			pen_row--;
		else if (c == 's' && pen_row < height - 1)
			pen_row++;
		else if (c == 'a' && pen_col > 0)
			pen_col--;
		else if (c == 'd' && pen_col < width - 1)
			pen_col++;
		else if (c == 'x')
			pen = !pen;

		if (pen)
			board[pen_row][pen_col] = 1;
	}

	/*
	 * Main simulation loop: run `iter` iterations of Conway's Game of Life.
	 * For each cell we count the number of alive neighbors (8-neighborhood)
	 * and write the result into the `next` board according to the rules:
	 *  - Alive cell with 2 or 3 neighbors survives.
	 *  - Dead cell with exactly 3 neighbors becomes alive.
	 *  - Otherwise, the cell is dead.
	 */
	while (iter-- > 0) {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {

				/* Count alive neighbors around (row,col). Skip the center cell. */
				int n = 0;
				for (int drow = -1; drow <= 1; drow++) {
					for (int dcol = -1; dcol <= 1; dcol++) {
						if (dcol == 0 && drow == 0)
							continue; /* Skip the cell itself */

						int nrow = row + drow;
						int ncol = col + dcol;

						/* Only count neighbors that are inside the board. */
						if (ncol >= 0 && ncol < width && nrow >= 0 && nrow < height)
							n += board[nrow][ncol];
					}
				}

				/* Apply Game of Life rules and store result in `next`. */
				if (board[row][col] == 1) {
					if (n == 2 || n == 3)
						next[row][col] = 1; /* survives */
					else
						next[row][col] = 0; /* dies */
				} else {
					if (n == 3)
						next[row][col] = 1; /* born */
					else
						next[row][col] = 0; /* stays dead */
				}
			}
		}

		/*
		 * Copy the computed `next` state back into `board` so the next
		 * iteration (if any) uses the updated state. This is a plain
		 * element-wise copy.
		 */
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				board[row][col] = next[row][col];
			}
		}
	}

	/*
	 * After all iterations, print the final board to stdout. Alive cells are
	 * represented by the character 'O', dead cells by a space. Each row is
	 * terminated by a newline.
	 */
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (board[row][col] == 1)
				putchar('0');
			else
				putchar(' ');
		}
		putchar('\n');
	}

	return (0);
}
