#include<stdio.h>//应冲书 2017211387 
#include<string.h>
#include <time.h>
#include"jobshop.h"
extern int repairBegin;
extern void translate(int machineNumber,struct chromosome *tempChromosome)
{
	int* tempPtr=NULL;
	int repeat[SIZE];//工件步骤数
	int step[SIZE];//机器步骤数
	int temptime=0; 
	int i,j;
	double start,finish;
	struct input tempInput;
	for(i=0;i<SIZE;i++){
		repeat[i]=originRepeat[i];
	}
	for(i=0;i<SIZE;i++){
		step[i]=originStep[i];
	}
	for(j=0;j<=machineNumber;j++){
		for(i=0;i<SIZE;i++){
			workMachine[j][i]=originWorkMachine[j][i];
		}
	}
	tempPtr=(*tempChromosome).message;//从头开始读
	while(*tempPtr!=-1){
		repeat[*tempPtr]++;//每读一个数，对应该数位置的步骤数++（对应input，从0开始） 
		tempInput=inputArray[*tempPtr][repeat[*tempPtr]];//目标input存入temp,方便操作 
		step[tempInput.machine]++;//记下要处理工件对应机器做到哪个步骤 
		tempInput.process=step[tempInput.machine]; 
		inputArray[*tempPtr][repeat[*tempPtr]].process=step[tempInput.machine];//将机器做到哪个步骤临时存到input中对应的process位置，方便后续查找
		if(step[tempInput.machine]!=0)//处理开始时间（仅考虑同一机器） 
		workMachine[tempInput.machine][tempInput.process].begintime=workMachine[tempInput.machine][tempInput.process-1/*同机器，前一步骤*/].endtime;
		else
		workMachine[tempInput.machine][tempInput.process].begintime=0;
		if(tempInput.step!=0){//和同一工件结束时间比较 
			if(workMachine[inputArray[tempInput.item][tempInput.step-1].machine/*同一工件的前一步骤是何机器*/][inputArray[tempInput.item][tempInput.step-1].process/*该前一工件步骤对应的机器的第几个步骤*/].endtime>workMachine[tempInput.machine][step[tempInput.machine]].begintime){
				workMachine[tempInput.machine][tempInput.process].begintime=workMachine[inputArray[tempInput.item][tempInput.step-1].machine][inputArray[tempInput.item][tempInput.step-1].process].endtime;
			}
			if(workMachine[tempInput.machine][tempInput.process].begintime<repairBegin){
				workMachine[tempInput.machine][tempInput.process].begintime=repairBegin;
			}
		}//起始时间为和自己同一工件或者同一机器的前步骤的结束时间最大值
		workMachine[tempInput.machine][tempInput.process].endtime=workMachine[tempInput.machine][tempInput.process].begintime+tempInput.time;
		//结束时间为起始时间加工作时间
		workMachine[tempInput.machine][tempInput.process].item=tempInput.item;
		workMachine[tempInput.machine][tempInput.process].number=tempInput.machine;
		workMachine[tempInput.machine][tempInput.process].process=repeat[*tempPtr];//存储必要信息 
		if(temptime<workMachine[tempInput.machine][tempInput.process].endtime)//记录最短时间 
		temptime=workMachine[tempInput.machine][tempInput.process].endtime;
		tempPtr++;//读取下一个片段
	}
	(*tempChromosome).time=temptime;
	return;
}

