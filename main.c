#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bge.h"

int main(int argc, const char * argv[])
{
    printf("Enter level name:");
    char fnm[100];
    scanf("%s",fnm);
    putchar(10);
    FILE *lvl;
    lvl=fopen(fnm,"r");
    printf("Debug:\tFile Opened\n");
    char level[10][10];
    if(lvl==NULL){
        exit(EXIT_FAILURE);
    }else{
        //Opened file sucessfully
	printf("Debug:\tFile Opening Successful\n");
        int i=0;
        char x;
        while(((x=fgetc(lvl))!=0)&&(i<100)){
            int j = (int) floor(i/10);
	    level[j][i%10]=x;
            i++;
        }
    }
    char c;
    char game[9][10]; //Game
    int i, j, k, l; //For for loops
    //Initial Coordinates
    int x=4;
    int y=4;
    int s,t;
    int panx=0;
    int pany=0;
    int coins=0;
    setup();
    chclr(0x0f);
    goto menu;
menu:
    clscr();
    wrtst("+--------------+",0,0);
    wrtst("|  Castle Run  |",1,0);
    wrtst("|  Alpha v0.0  |",2,0);
    wrtst("+--------------+",3,0);
    wrtst("|Action     Key|",4,0);
    wrtst("|Play         p|",5,0);
    wrtst("|Instructions i|",6,0);
    wrtst("|Exit         x|",7,0);
    wrtst("+--------------+",8,0);
    update();
    while(1){
        c=getchar();
        switch(c){
                case 'p':
                goto resume;
                break;
                case 'i':
                goto instructions;
                break;
                case 'x':
                goto exit;
                break;
            default:
                break;
        }
	update();
    }
    goto resume;
instructions:
    clscr();
    wrtst("+--------------+",0,0);
    wrtst("|  Castle Run  |",1,0);
    wrtst("| Instructions |",2,0);
    wrtst("+--------------+",3,0);
    wrtst("|Action    Keys|",4,0);
    wrtst("|Move        w |",5,0);
    wrtst("|           a d|",6,0);
    wrtst("|            s |",7,0);
    wrtst("|              |",8,0);
    wrtst("|Pan         i |",9,0);
    wrtst("|           j l|",10,0);
    wrtst("|            k |",11,0);
    wrtst("|              |",12,0);
    wrtst("|Pause        p|",13,0);
    wrtst("|Exit         x|",14,0);
    wrtst("+--------------+",15,0);
    wrtst("|Back         m|",16,0);
    wrtst("+--------------+",17,0);
    update();
    while(1){
        //Oh, please don't delete me!
        c=getchar();
        if(c=='m'){
            goto menu;
        }
    }
resume:
    clscr();
    //Draw the frame
    wrtst("+--------+",0,0);
    for(i=1;i<9;i++){
        wrtst("|        |",i,0);
    }
    wrtst("+--------+",10,0);
    wrtst("|Coins:  |",11,0);
    wrtst("+--------+",12,0);
    while(1){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                game[i][j]=level[i][j];
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
                    if((pany+8)<9){
                        pany++;
                    }
                    break;
                case 'l':
                    if ((panx+8)<10){
                        panx++;
                    }
                    break;
                default:
                    break;
            }
        }
        if(x>8||x<0){
            x=s;
        }
        if(y>8||y<0){
            y=t;
        }
        switch(game[y][x]){
            case 'W':
                x=s;
                y=t;
                break;
            case 'c':
                coins++;
                level[y][x]=' ';
                break;
            case 'x':
                x = 4;
                y = 4;
                goto die;
                break;
        }
        game[y][x]='^'; //Add player to location
        for(k=pany;k<(pany+8);k++){
            for(l=panx;l<(panx+8);l++){
                wrtch(game[k][l],k+1-pany,l+1-panx);//Print the character at the array
            }
        }
        wrtch((coins % 10) + '0', 11, 8);
        update();
    }
    goto exit;
die:
    clscr();
    wrtst("+-------------------+",0,0);
    wrtst("|     Game over     |",1,0);
    wrtst("+-------------------+",2,0);
    wrtst("|Action          Key|",3,0);
    wrtst("|Main Menu         m|",4,0);
    wrtst("|Exit              x|",5,0);
    wrtst("+-------------------+",6,0);
    update();
    
    while(1){
        coins=0;
        c=getchar();
        switch(c){
            case 'r':
                clscr();
                goto resume;
                break;
            case 'm':
                goto menu;
                break;
            case 'x':
                goto exit;
                break;
            default:
                break;
        }
    }
pause:
    clscr();
    wrtst("+-------------------+",0,0);
    wrtst("|    Game Paused    |",1,0);
    wrtst("+-------------------+",2,0);
    wrtst("|Action          Key|",3,0);
    wrtst("|Resume            r|",4,0);
    wrtst("|Main Menu         m|",5,0);
    wrtst("|Exit              x|",6,0);
    wrtst("+-------------------+",7,0);
    update();
    
    while(1){
        c=getchar();
        switch(c){
                case 'm':
                goto menu;
                break;
                case 'x':
                goto exit;
                break;
            default:
                break;
        }
    }
exit:
    endpr();
    return 0;
}
