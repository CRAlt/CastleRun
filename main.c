#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <conio.h>

int main(int argc, const char * argv[])
{
    FILE *lvl;
    lvl=fopen("D:/PRs/PR14/level.txt","r");
    char level[10][10];
    if(lvl==NULL){
        exit(EXIT_FAILURE);
    }else{
        //Opened file sucessfully
        int f=0;
        int i=0;
        char x;
        while(((x=fgetc(lvl))!=0)&&(i<100)){
            level[(int)floor(i/10)][i%10]=x;
            i++;
        }
        if(f<100){
            printf("File too short\n");
            printf("%s",argv[0]);
            getchar();
            exit(EXIT_FAILURE);
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
    goto menu;
    init_keyboard();
menu:
    while(1){
        system("cls");
        printf("+--------------+\n");
        printf("|  Castle Run  |\n");
        printf("|Prerelease 13 |\n");
        printf("+--------------+\n");
        printf("|Action     Key|\n");
        printf("|Play         p|\n");
        printf("|Instructions i|\n");
        printf("|Exit         x|\n");
        printf("+--------------+\n");
        c=getchar();
        switch(c){
                case 'p':
                system("cls");
                goto resume;
                break;
                case 'i':
                system("cls");
                goto instructions;
                break;
                case 'x':
                goto exit;
                break;
            default:
                break;
        }
    }
    goto resume;
instructions:
    while(1){
        printf("+--------------+\n");
        printf("|  Castle Run  |\n");
        printf("| Instructions |\n");
        printf("+--------------+\n");
        printf("|Action    Keys|\n");
        printf("|Move        w |\n");
        printf("|           a d|\n");
        printf("|            s |\n");
        printf("|              |\n");
        printf("|Pan         i |\n");
        printf("|           j l|\n");
        printf("|            k |\n");
        printf("|              |\n");
        printf("|Pause        p|\n");
        printf("|Exit         x|\n");
        printf("+--------------+\n");
        printf("|Back         m|\n");
        printf("+--------------+\n");
        c=getchar();
        if(c=='m'){
            goto menu;
        }
        system("cls");
    }
resume:
    while(1){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                game[i][j]=level[i][j];
            }
        }
        s=x;
        t=y;
        if(kbhit()){
            c=getch();
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
                goto die;
                break;
        }
        game[y][x]='^'; //Add player to location
        printf("+--------+\n");
        for(k=pany;k<(pany+8);k++){
            putchar('|');
            for(l=panx;l<(panx+8);l++){
                putchar(game[k][l]);//Print the character at the array
            }
            putchar('|');
            putchar(10);//Print next line
        }
        printf("+--------+\n");
        printf("|Coins:%i|\n", coins);
        printf("+--------+\n");
        sleep(0x1);//Wait one second
        system("cls");//Clear the screen
    }
    goto exit;
die:
    system("cls");
    while(1){
        coins=0;
        printf("+-------------------+\n");
        printf("|     Game over     |\n");
        printf("+-------------------+\n");
        printf("|Action          Key|\n");
        printf("|Main Menu         m|\n");
        printf("|Exit              x|\n");
        printf("+-------------------+\n");
        c=getchar();
        switch(c){
            case 'r':
                system("cls");
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
        system("cls");
    }
pause:
    system("cls");
    while(1){
        printf("+-------------------+\n");
        printf("|    Game Paused    |\n");
        printf("+-------------------+\n");
        printf("|Action          Key|\n");
        printf("|Resume            r|\n");
        printf("|Main Menu         m|\n");
        printf("|Exit              x|\n");
        printf("+-------------------+\n");
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
        system("cls");
    }
exit:
    return 0;
}
