#include<stdio.h>//应冲书 2017211387 
#include<string.h>
#include <time.h>
#include"jobshop.h"
extern void repair(int machineNumber,struct chromosome *tempChromosome,int repairBegin,int repairMessage[])
{
	int i,j;
	i=0;
	j=0;
	struct chromosome tempChromosome2;
	memset(tempChromosome2.message,-1,sizeof(tempChromosome2.message));
	int* tempPtr=NULL;
	int repeat[SIZE];//工件步骤数
	int step[SIZE];//机器步骤数
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
	}//读取origin 
	tempPtr=(*tempChromosome).message;//从头开始读
	i=0;
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
		}//起始时间为和自己同一工件或者同一机器的前步骤的结束时间最大值
		workMachine[tempInput.machine][tempInput.process].endtime=workMachine[tempInput.machine][tempInput.process].begintime+tempInput.time;
		//结束时间为起始时间加工作时间
		workMachine[tempInput.machine][tempInput.process].item=tempInput.item;
		workMachine[tempInput.machine][tempInput.process].number=tempInput.machine;
		workMachine[tempInput.machine][tempInput.process].process=repeat[*tempPtr];//存储必要信息 
		if(workMachine[tempInput.machine][tempInput.process].begintime>repairBegin){
			tempChromosome2.message[i]=workMachine[tempInput.machine][tempInput.process].item;
			i++;
		}//未开始的项目顺序保存下来 
		else{
			originRepeat[*tempPtr]=repeat[*tempPtr];
			originStep[tempInput.machine]=step[tempInput.machine];
			originWorkMachine[tempInput.machine][tempInput.process]=workMachine[tempInput.machine][tempInput.process];
		}//已开始的部分存入origin 
		tempPtr++;//读取下一个片段
	}
	for(j=0;j<machineNumber;j++){
		if(repairMessage[j]!=-1){
			if(originWorkMachine[j][originStep[j]].endtime>=repairBegin){
				originWorkMachine[j][originStep[j]+1].begintime=originWorkMachine[j][originStep[j]].endtime;
				originWorkMachine[j][originStep[j]+1].endtime=originWorkMachine[j][originStep[j]].endtime+repairMessage[j];
			}
			else{
				originWorkMachine[j][originStep[j]+1].begintime=repairBegin;
				originWorkMachine[j][originStep[j]+1].endtime=repairBegin+repairMessage[j];
			}
			originWorkMachine[j][originStep[j]+1].item=-2;
			originWorkMachine[j][originStep[j]+1].number=j;
			originStep[j]++;
		//增加维修
		}
	}
	memset((*tempChromosome).message,-1,sizeof((*tempChromosome).message));
	i=0;
	while(tempChromosome2.message[i]!=-1){
		(*tempChromosome).message[i]=tempChromosome2.message[i];
		i++;
	}
	return;
}

