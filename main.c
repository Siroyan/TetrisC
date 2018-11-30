#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "field.h"
#include "blocks.h"
#include "key.h"
#define EMPT 0
#define WALL 1
#define BLOC 2
#define STAC 4

/* FIELD DATA */
static int tgtBlock[4][4];
static int stackBlocks[25][15];
static int outputData[25][15];
int blcX = 1, blcY = 3;	/* location of block at first */
/* PROTOTYPE */
int checkDest(int,int,char);
void cpBlock(void);
void keyInput(void);
void moveBlock(char);
void showDisplayData(void);
void integrateData(void);
void recordBlocks(void);
void rotateBlock(char);

int main(void){
	while(1){
		int cnt = 0;
		blcX = 1, blcY = 3;
		cpBlock();
		while(checkDest(blcX, blcY, 's')){
			while(cnt == 150){
				moveBlock('s');
				cnt = 0;
			}
			keyInput();
			system("clear");
			integrateData();
			showDisplayData();
			//TODO Clear proccess
			usleep(10000);	//10ms
			cnt++;
		}
		recordBlocks();
	}
	return 0;
}

void cpBlock(){
	float x;
	x = (float)rand()/(RAND_MAX+1.0);
	if(0.0 <= x && x < 0.14)	memcpy(tgtBlock, block1, sizeof(int)*4*4);
	if(0.1 <= x && x < 0.28)	memcpy(tgtBlock, block2, sizeof(int)*4*4);
	if(0.2 <= x && x < 0.42)	memcpy(tgtBlock, block3, sizeof(int)*4*4);
	if(0.3 <= x && x < 0.56)	memcpy(tgtBlock, block4, sizeof(int)*4*4);
	if(0.4 <= x && x < 0.60)	memcpy(tgtBlock, block5, sizeof(int)*4*4);
	if(0.5 <= x && x < 0.74)	memcpy(tgtBlock, block6, sizeof(int)*4*4);
	if(0.6 <= x && x < 1.00)	memcpy(tgtBlock, block7, sizeof(int)*4*4);
}

void moveBlock(char dir){
	if(dir == 'a') if(checkDest(blcX, blcY, 'a')) blcY--;
	if(dir == 's') if(checkDest(blcX, blcY, 's')) blcX++;
	if(dir == 'd') if(checkDest(blcX, blcY, 'd')) blcY++;
}
int checkDest(int x, int y, char dir){
	int a = 0, b = 0;
	if(dir == 'a') b = -1;
	if(dir == 's') a =  1;
	if(dir == 'd') b =  1;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(outputData[x+i+a][y+j+b]+tgtBlock[i][j] == WALL + BLOC) return 0;
			if(outputData[x+i+a][y+j+b]+tgtBlock[i][j] == STAC + BLOC) return 0;
		}
	}
	return 1;
}

void rotateBlock(char dir){
	int temp[4][4];
	int check = 1;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(dir == 'l') temp[j][3-i] = tgtBlock[i][j];
			if(dir == 'r') temp[3-j][i] = tgtBlock[i][j];
		}
	}
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(outputData[blcX+i][blcY+j]+temp[i][j] == WALL + BLOC) check = 0;
			if(outputData[blcX+i][blcY+j]+temp[i][j] == STAC + BLOC) check = 0;
		}
	}
	if(check == 1) memcpy(tgtBlock, temp, sizeof(int)*4*4);
}

void recordBlocks(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(tgtBlock[i][j]==2) stackBlocks[blcX+i][blcY+j] = STAC;
		}
	}
}

void integrateData(){
	/* Copy field */
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 15; j++){
			outputData[i][j] = field[i][j];
			if(stackBlocks[i][j] == STAC) outputData[i][j] = STAC;
		}
	}
	/* Copy block */
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(tgtBlock[i][j] == BLOC) outputData[blcX+i][blcY+j] = BLOC;
		}
	}
}

void showDisplayData(){
	for(int i = 0; i < 23; i++){
		for(int j = 2; j < 13; j++){
			if(outputData[i][j] == EMPT) printf("  ");
			if(outputData[i][j] == WALL) printf("■ ");	
			if(outputData[i][j] == BLOC) printf("□ ");
			if(outputData[i][j] == STAC) printf("□ ");
		}
		printf("\n");
	}
}
void keyInput(){
	char buf;
	buf = kbhit();
	if(buf == 'a') moveBlock('a');			/* move left */
	if(buf == 's') moveBlock('s');			/* move under */
	if(buf == 'd') moveBlock('d');			/* move right */
	if(buf == 'q') rotateBlock('l');		/* rotate left */
	if(buf == 'e') rotateBlock('r');	/* rotate right */
}

/*
void showDisplayData(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			printf("%d",outputData[i][j]);
		}
		printf("\n");
	}
}
*/
