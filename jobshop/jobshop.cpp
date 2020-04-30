#include<stdio.h>//应冲书 2017211387
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#include"graphics.h"
#include"jobshop.h"
struct input inputArray[SIZE][SIZE];//输入的所有数据，行表示机器号，列表示工序
struct machine workMachine[SIZE][SIZE];//所有机器
struct machine originWorkMachine[SIZE][SIZE];//初始状态 
int originRepeat[SIZE];//初始工件步骤 
int originStep[SIZE];//初始机器步骤  
double start,finish,programmetime;
extern int itemamount;
extern int machineamount;
struct chromosome minChromosome;
int repairBegin;//维修开始时间
int main(int argc, char *argv[]) {
	struct chromosome tempChromosome;
	memset(originRepeat,-1,sizeof(originRepeat));//清空
	memset(originStep,-1,sizeof(originStep));
	memset(originWorkMachine,-1,sizeof(originWorkMachine));
	repairBegin=0; 
	int i;
	input();
	start=clock();
	srand(time(NULL));
	FILE *fptr;
	fptr=fopen("jobshop_output1.txt","w");//清空指定输出文件的内容 
	fptr=fopen("jobshop_output2.txt","w");
	fclose(fptr); 
	initchro(&tempChromosome);
	superAnneal(&tempChromosome); 
	minChromosome=tempChromosome;
	for(i=0;i<=300;i++){
		initchro(&tempChromosome);
		superAnneal(&tempChromosome); 
		if(minChromosome.time>tempChromosome.time){
			minChromosome=tempChromosome;
			printf("\n"); 
		}
	}
	finish=clock();
	programmetime=(finish-start)/1000;
	output1(&minChromosome);
	draw_graphics(&minChromosome.time,&programmetime);//!!!!!
	printf("\n");
	return 0;
}
