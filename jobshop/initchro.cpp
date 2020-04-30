#include<stdio.h> //刘昊源 2017211390 
#include<string.h>
#include<stdlib.h>
#include<time.h> 
#include"jobshop.h"
extern int itemamount;
int length;
extern void initchro(struct chromosome *tempChromosome)
{
	int row,col,count,change,place;
	row=0;
	col=0;
	count=0;
	change=0;
	memset((*tempChromosome).message,-1,sizeof((*tempChromosome).message));//初始化
	while(row<itemamount)//读取所有工件及其步骤数，按序存入initChromosome 
	{
		col=0;
		while(inputArray[row][col].machine!=-1){
			(*tempChromosome).message[count]=inputArray[row][col].item;
			col++;
			count++;
		}
		row++;
	}
	length=count;
	int i=0;
	for(i=0;i<count;i++){
		place=rand()%count;//遍历交换，交换位置随机 
		if((*tempChromosome).message[i]!=(*tempChromosome).message[place]){
			change=(*tempChromosome).message[i];
			(*tempChromosome).message[i]=(*tempChromosome).message[place];
			(*tempChromosome).message[place]=change;
		}
	}
	(*tempChromosome).time=0; 
	return;
}
