#include 	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<time.h>
#include	"bge.h"
#define		WIDTH	99
#define 	HEIGHT	5
#define		DIGITS	"0123456789ABCDEF"

const int size = WIDTH * HEIGHT;

char* hexInt(unsigned int n){
	char* c = (char*) malloc(9);
	int i;
	for(i = 0; i < 8; i++){
		*(c+i) = DIGITS[((n >> (4 * i)) % 16)];
	}
	*(c+9) = '\0';
	putchar('\n');
	return c;
}

int main(int argc, const char * argv[])
{
    FILE *logfile;  //Logfile
    logfile=fopen("/tmp/cr.log","a");
    srand(time(NULL));	//Seed
    unsigned int sid = rand();	//Session ID
    char* sids = hexInt(sid);
    printf("%s\n", sids);
    fprintf(logfile, "\n\n[%s]:\tStarting Program\n", sids);
    fclose(logfile);
    logfile=fopen("/tmp/cr.log","a");

    printf("Unfinished!\n");

    printf("Enter level name:");
    char fnm[100];
    scanf("%s",fnm);
    putchar(10);
    FILE *lvl;
    lvl=fopen(fnm,"r");
    fprintf(logfile,"[%s]:\tFile Opened\n",sids);
    if(lvl==NULL){
	fprintf(logfile,"[%s]:\tFile Opening Failed.\n",sids);
        fclose(logfile);
        exit(EXIT_FAILURE);
    }
        //Opened file sucessfully
    fprintf(logfile,"[%s]:\tFile Opening Successful.\n",sids);
    char* level = (char *)malloc(size * sizeof(char));
    fprintf(logfile,"[%s]:\tMalloc successful.\n",sids);
    if (level == NULL) return -1;
    int oi=0;
    char ox;
    fprintf(logfile,"[%s]:\tDeclaring variables, ready to dump file data into level.\n",sids);
    while(((ox=fgetc(lvl))!=0)&&(oi<size)){
        *(level+oi) = ox;
        oi++;
    }

    fprintf(logfile,"[%s]:\tReady to run game\n",sids);
    char c;
    char* game = malloc(size * sizeof(char)); //Game
    int i, j, k, l; //For for loops
    //Initial Coordinates
    int x=2;
    int y=2;
    int s,t;
    int panx=0;
    int pany=0;
    int coins=0;
    setup();
    chclr(0x0f);
    goto menu;
menu:
    fprintf(logfile,"[%s]:\tReady to print menu.\n",sids);
    clear();
    
    //Draw frame
    fprintf(logfile,"[%s]:\tScreen cleared\n",sids);
    drwbx(0,0,64,32);
    drwbx(0,16,64,16);

    //Draw logo
    int lx = 0, ly = 0;
    FILE *logo;
    logo = fopen("logo.txt","r");
    for(i = 0; ((c = fgetc(logo)) != EOF); i++){
	if(c == '\n'){
		ly += 1;
		lx = 0;
	}else{
		mvaddch(ly+4,lx+5,c);
		lx += 1;
	}
    }

    //Text
    mvprintw(17,30,"Menu");

    mvprintw(19,2,"Play");
    mvprintw(20,2,"Help");
    mvprintw(21,2,"Exit");
    
    //Version
    mvprintw(30,1,"Alpha v0.0.2");
    
    //Set up menu
    unsigned char item = 0x00;
    unsigned char previtem = 0x00;

    fprintf(logfile, "[%s]:\tItem is %i\n", sids, item);

    refresh();
    /*
     *	0 = resume
     *	1 = instructions
     *	2 = exit
     */
    while(1){
        if(kbhit()){
	    c = getchar();
	    switch(c){
		case '\033':
		    switch(getLastKey()){
			case 'A':
			    item = ((item > 0) ? (item - 1) : item);
			    fprintf(logfile, "[%s]:\tItem changed to %i\n", sids, item);
			    break;
			case 'B':
			    item = ((item < 2) ? (item + 1) : item);
			    fprintf(logfile, "[%s]:\tItem changed to %i\n", sids, item);
			    break;
			default:
			    break;
		    }
		    break;
		case '\r':
		    switch(item){
			case 0:
    			    fclose(logfile);
    			    logfile=fopen("/tmp/cr.log","a");
			    goto resume;
			    break;
			case 1:
			    goto instructions;
			    break;
			case 2:
			    goto exit;
			    break;
		   }
		   break;
		case 'x':
		   goto exit;
		   break;
	    }
	}
	mvaddch(19+item, 1, '*');
	refresh();
	mvaddch(19+previtem, 1, ' ');
	previtem = item;
    }
    goto resume;
instructions:
    clear();
    
    drwbx(0,0,64,32);
    drwbx(0,16,64,16);
    
    mvprintw(17,28,"Controls");

    mvprintw(19,2,"Moving Around");
    mvprintw(19,53,"Arrow Keys");
    
    mvprintw(20,2,"Pausing");
    mvprintw(21,62,"p");
        
    mvprintw(21,2,"Exiting");
    mvprintw(23,62,"x");
    
    mvprintw(30,1,"Press m to go back.");

    refresh();
    while(1){
        //Oh, please don't delete me!
        c=getchar();
        if(c=='m'){
            goto menu;
        }
    }
resume:
   clear();
    
    //Draw the frame
    drwbx(0,0,64,32);
    drwbx(0,0,64,3);
    drwbx(0,2,49,21);
    drwbx(48,2,16,21);
    
    //fprintf(logfile, "[%s]:\tReady to enter game loop\n",sids);

    while(1){
	
	//fprintf(logfile,"[%s]:Starting loop(%i,%i)\n",sids,panx,pany);
        fclose(logfile);
        logfile=fopen("/tmp/cr.log","a");
        for(i=0;i<HEIGHT;i++){
            for(j=0;j<WIDTH;j++){
                game[i*WIDTH+j]=level[i*WIDTH+j];
            }
        }
        s=x;
        t=y;
        if(kbhit()){
            c=getchar();
            switch (c){
                case 'a':
                    x--; //Move up
                    break;
                case 'w':
                    y--; //Move left
                    break;
                case 's':
                    y++; //Move down
                    break;
                case 'd':
                    x++; //Move right
                    break;
                case 'x':
                    goto exit;
                    break;
                case 'p':
                    goto pause;
                    break;
                case 'i':
                    if(pany>0){
                        pany--;
                    }
                    break;
                case 'j':
                    if (panx>0){
                        panx--;
                    }
                    break;
                case 'k':
                    if((pany+19)<HEIGHT){
                        pany++;
                    }
                    break;
                case 'l':
                    if ((panx+47)<WIDTH){
                        panx++;
                    }
                    break;
                default:
                    break;
            }
        }
	//fprintf(logfile,"[%s]:Finished handling controls\n",sids);
        if(x>WIDTH||x<0){
            x=s;
        }
        if(y>HEIGHT||y<0){
            y=t;
        }
        switch(game[y*WIDTH+x]){
            case 'W':
                x=s;
                y=t;
                break;
            case 'c':
                coins++;
                level[y*WIDTH+x]=' ';
                break;
            case 'x':
                x = 4;
                y = 4;
                goto die;
                break;
        }
        game[y*WIDTH+x]='j'; //Add player to location
	for(k=pany;k<(pany+19);k++){
            for(l=panx;l<(panx+47);l++){
                if((k<HEIGHT)&&(l<WIDTH)){
	    		mvaddch(k+3-pany,l+1-panx,game[k*WIDTH+l]);//Print the character at the array
		}
            }
        }
        mvprintw(1, 54, "Coins: %i", (coins % 10));
        refresh();
    }
    goto exit;
die:
    drwbx(26,15,12,5);

    mvprintw(16, 28, "You died");
    mvprintw(18, 27, "Exit");
    mvprintw(18, 36, "x");

    refresh();
    
    while(1){
        coins=0;
	

        c=getchar();
        switch(c){
            case 'x':
                goto exit;
                break;
            default:
                break;
        }
    }
pause:
    fprintf(logfile, "[%s]:Pause Menu initialized.\n", sids);
    drwbx(27,12,10,8);
    drwbx(27,14,10,6);

    mvprintw(13,29,"Paused");
    mvprintw(15,29,"Resume");
    mvprintw(16,30,"Main");
    mvprintw(17,30,"Exit");

    item = 0;

    int arrayOfLeftAsterisks[3] = {28, 29, 29};
    int arrayOfRightAsterisks[3] = {35, 34, 34};
   
    refresh();
    while(1){
	previtem = item;
        c=getchar();
        switch(c){
		case '\033':
			getchar();
			switch(getchar()){
				case 'A':
					if(item > 0){
						item--;
					}
					break;
				case 'B':
					if(item < 2){
						item++;
					}
					break;
				default:
					break;
			}
			break;
		case '\r':
			switch(item){
				case 0:
					goto resume;
				case 1:
					goto menu;
				case 2:
					goto exit;
			}
		default:
			break;
        }

	mvaddch(15+previtem,arrayOfLeftAsterisks[previtem],' ');
	mvaddch(15+previtem,arrayOfRightAsterisks[previtem],' ');
	mvaddch(15+item,arrayOfLeftAsterisks[item],'*');
	mvaddch(15+item,arrayOfRightAsterisks[item],'*');

	fprintf(logfile,"[%s]:\tRefresh called.",sids);
	refresh();
    }
exit:
    fclose(logfile);
    endpr();
    return 0;
}
