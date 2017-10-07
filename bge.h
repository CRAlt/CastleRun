#include	<stdio.h>
#include	<termios.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ncurses.h>
#include	<string.h>

unsigned char color;

char lastKey;

int kbhit(void){
	
	struct termios oldt, newt;
	int ch;
	int oldf;
	
	//Set things up
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO); //Non-canonical input, no echo
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); //Nonblock = operations not patient
	
	ch = getchar(); //Get our character
	
	//Wrap things up
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	
	if(ch != EOF){
		
		if(ch == 033){
			getchar();
			char ch2 = getchar();
			lastKey = ch2;
		}

		ungetc(ch, stdin); //Put character back in stream?
		return 1;
	}
	
	return 0; //If ch was EOF, then 0 would be returned.
}

void setup(void){
	initscr();
	start_color();
	lastKey = EOF;
}

void chclr(unsigned char c){
	attroff(COLOR_PAIR(1));	
	color = c;
}

void endpr(void){
	attroff(COLOR_PAIR(1));
	endwin();
}

char getLastKey(void){
	return lastKey;
}

void drwbx(int x, int y, int l, int h){
	int i, j;
	
	for(i = y; i < (y+h); i++){
		//printf("Debug :\t%i\r\n",l);
		char c[l+1];	//Contains horizontal slice of box.

		for(j = 0; j < l; j++){
			//printf("Debug:\t%i\r\n", j);
			if((j == 0) || (j == (l-1))){
				c[j] = (((i == y) || (i == (y+h-1))) ? '+' : '|');
			}else{
				c[j] = (((i == y) || (i == (y+h-1))) ? '-' : ' ');
			}
		}
		c[l] = '\0';

		//printf("Debug:\t%d\r\n\r\n", (int) strlen(c));
		mvprintw(i, x, c);
	}
}
