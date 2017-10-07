#include	<stdio.h>
#include	"bge.h"

int main(){
	FILE *logo;
	logo = fopen("logo.txt", "r");
	int i;
	char c;
	int x = 0, y = 0;
	
	setup();
	chclr(0x0f);
	for(i = 0; (c = fgetc(logo)) != EOF; i++){
		if(c == '\n'){
			x = 0;
			y += 1;
		}else{
			wrtch(c,y,x);
			x += 1;
		}
	}
	update();
	while(1){
		if(kbhit()){
			printf("Broken\n");
			break;
		}
	}
	endpr();
	return 0;
}
