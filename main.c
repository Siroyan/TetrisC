#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "field.h"
#include "blocks.h"
#include "key.h"
#define EMPT 0
#define WALL 1
#define BLOC 2

/* FIELD DATA */
extern int field[10][10];
extern int block1[5][5];
int outputData[10][10];
int blcX = 1, blcY = 1;	/* location of block at first */
/* PREAMBLE */
int checkDestW(int,int);
int checkDestA(int,int);
int checkDestS(int,int);
int checkDestD(int,int);
void keyInput(void);
void move(char);
void moveElement(char,char);
void showDisplayData(void);
void integrateData(void);
extern char getch(void);

int main(void){
	int cnt = 0;
	while(1){
		while(cnt == 50){
			system("clear");
			integrateData();
			showDisplayData();
			//TODO Clear proccess
			cnt = 0;
		}
		keyInput();
		usleep(1000);	//1ms
		cnt++;
	}
	return 0;
}

void move(char dir){
	if(dir == 'w') if(checkDestW(blcX, blcY) == 1) blcX--;
	if(dir == 'a') if(checkDestA(blcX, blcY) == 1) blcY--;
	if(dir == 's') if(checkDestS(blcX, blcY) == 1) blcX++;
	if(dir == 'd') if(checkDestD(blcX, blcY) == 1) blcY++;
}

int checkDestW(int x, int y){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(outputData[i+x-1][j+y]+block1[i][j] == 3) return 0;
		}
	}
	return 1;
}
int checkDestA(int x, int y){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(outputData[i+x][j+y-1]+block1[i][j] == 3) return 0;
		}
	}
	return 1;
}
int checkDestS(int x, int y){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(outputData[i+x+1][j+y]+block1[i][j] == 3) return 0;
		}
	}
	return 1;
}
int checkDestD(int x, int y){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(outputData[i+x][j+y+1]+block1[i][j] == 3) return 0;
		}
	}
	return 1;
}

void integrateData(){
	/* Copy field */
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			outputData[i][j] = field[i][j];
		}
	}
	/* Copy block */
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(block1[i][j] == 2) outputData[blcX+i][blcY+j] = block1[i][j];
		}
	}
}

void showDisplayData(){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(outputData[i][j] == EMPT) printf("  ");
			if(outputData[i][j] == WALL) printf("■ ");	
			if(outputData[i][j] == BLOC) printf("□ ");
		}
		printf("\n");
	}
}

void keyInput(){
	char buf;
	buf = kbhit();
	if(buf == 'w') move('w');	/* move top */
	if(buf == 'a') move('a');	/* move left */
	if(buf == 's') move('s');	/* move under */
	if(buf == 'd') move('d');	/* move right */
}