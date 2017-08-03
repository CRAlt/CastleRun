#include	<stdio.h>
#include	<termios.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ncurses.h>

char scrn[64][64];
unsigned char color;

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
		ungetc(ch, stdin); //Put character back in stream?
		return 1;
	}
	
	return 0; //If ch was EOF, then 0 would be returned.
}

void setup(void){
	initscr();
	start_color();
	int i, j;
	for(i=0; i<64; i++){
		for(j=0; j<64; j++){
			scrn[i][j] = ' ';
		}
	}
}

void update(void){
	init_pair(1, (color % 16), ((color - (color % 16)) / 16));
	attron(COLOR_PAIR(1));
	int i,j;
	for(i=0; i<64; i++){
		for(j=0; j<64; j++){
			char c = scrn[i][j];
			mvaddch(i, j, c);
		}
	}
	refresh();
}

void wrtch(char c, int i, int j){
	scrn[i][j] = c;
}

void wrtst(const char *s, int i, int j){
	int k;
	for(k = 0; s[k]; k++){
		if((j + k) < 64){
			wrtch(s[k], i, (j + k));
		}
	}
}

void clscr(void){
	int i, j;
	for(i = 0; i < 64; i++){
		for(j = 0; j < 64; j++){
			wrtch(' ', i, j);
		}
	}
}

void chclr(unsigned char c){
	attroff(COLOR_PAIR(1));	
	color = c;
}

void endpr(void){
	attroff(COLOR_PAIR(1));
	endwin();
}
