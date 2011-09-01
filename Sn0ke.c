															// Sn0ke by Ro0mquy

#include <stdio.h>											// Includes
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define NEW 7

void flush_buffer (void){									// define flush_buffer()
	while (_kbhit ()){
		 _getch ();
	}
} 


void sleepx (int milliseconds) {							// define sleepx()

	clock_t start;

	start = clock ();

	while (1) {
		
		if (clock () - start > milliseconds - 9){
			break;
		}
	}
}


int main ()
{
	struct position {										// Init values
		int x;
		int y;
	};
	srand (time (0));
	
	char input;
	char direction;
	int points;
	int i;

	struct position food;
	struct position head;
	struct position pos[NEW * 50]; 


	food.x = rand () % 80 + 1;								// reset values
	food.y = rand () % 19 + 7;
	
	head.x = 40;
	head.y = 13;

	for (i = 0; i < NEW * 50; ++i) {
		pos[i].x = 80;
		pos[i].y = 1;
	}

	for (i = 0; i < NEW; ++i) {
		pos[i].x = 39 - i;
		pos[i].y = 13;
		_gotoxy (pos[i].x,pos[i].y);
		printf ("Û");

		if (food.x == pos[i].x && food.y == pos[i].y) {
			food.x = rand () % 80 + 1;
			food.y = rand () % 19 + 7;
		}
	}

	points = 0;
	direction = 'd';

	_gotoxy (16,4);											//print UI
	printf ("Points:");
	_gotoxy (47,4);
	printf ("Length of Worm:\n________________________________________________________________________________"); 

	do {
		_gotoxy (food.x, food.y);							// print food, worm and points
		printf ("%c", 207);

		_gotoxy (head.x, head.y);
		printf ("%c",16);

		_gotoxy (24,4);
		printf ("%02i", points);
		_gotoxy (63,4);
		printf ("%03i", NEW * (points + 1) + 1);


		flush_buffer ();
		sleepx (100);										// wait and ask for input
		if (_kbhit ()) {
			input = _getch ();
		}


		_gotoxy (head.x, head.y);							// replace beginning and ending of worm
		printf ("Û");

		_gotoxy (pos[(NEW * (points + 1)) - 1].x,pos[(NEW * (points + 1)) - 1].y);
		printf (" ");

		for (i = NEW * (points + 1) - 1; i > 0; --i) {		// change coordinats of worm
			pos[i].x = pos[i - 1].x;
			pos[i].y = pos[i - 1].y;
		}
		pos[0].x = head.x;
		pos[0].y = head.y;

															// check if input is ok
		if ((input == 'w' && direction != 's') || (input == 'a' && direction != 'd') || (input == 's' && direction != 'w') || (input == 'd' && direction != 'a')) {
			direction = input;
		}

		if (direction == 'w') {								// change worm direction
			--head.y;
		}
		else if (direction == 'a') {
			--head.x;
		}
		else if (direction == 's') {
			++head.y;
		}
		else if (direction == 'd') {
			++head.x;
		}

		if (head.x == food.x && head.y == food.y) {			// worm eats food
			++points;
			init_rand:
			food.x = rand () % 80 + 1;
			food.y = rand () % 19 + 7;

			for (i = 0; i < NEW * (points +1); ++i)  {
				if ((pos[i].x == food.x && pos[i].y == food.y) || (head.x == food.x && head.y == food.y)) {
					goto init_rand;
				}
			}
		}
															// you lose
		for (i = 0; i < NEW * (points + 1); ++i) {
			if (head.x == 0 || head.x == 81 || head.y == 5 || head.y == 26 || pos[i].x == head.x & pos[i].y == head.y) {
				input ='\x1b';
				_gotoxy (29,12);
				printf ("                      ");
				_gotoxy (29,13);
				printf (" You lose! Try again! ");
				_gotoxy (29,14);
				printf ("                      ");
				_getch ();
			}
		}

	} while (input != '\x1b');								// quit with [Esc]

	return 0;
}
