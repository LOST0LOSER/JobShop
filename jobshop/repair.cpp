#include<stdio.h>//Ӧ���� 2017211387 
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
	int repeat[SIZE];//����������
	int step[SIZE];//����������
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
	}//��ȡorigin 
	tempPtr=(*tempChromosome).message;//��ͷ��ʼ��
	i=0;
	while(*tempPtr!=-1){
		repeat[*tempPtr]++;//ÿ��һ��������Ӧ����λ�õĲ�����++����Ӧinput����0��ʼ�� 
		tempInput=inputArray[*tempPtr][repeat[*tempPtr]];//Ŀ��input����temp,������� 
		step[tempInput.machine]++;//����Ҫ��������Ӧ���������ĸ����� 
		tempInput.process=step[tempInput.machine]; 
		inputArray[*tempPtr][repeat[*tempPtr]].process=step[tempInput.machine];//�����������ĸ�������ʱ�浽input�ж�Ӧ��processλ�ã������������
		if(step[tempInput.machine]!=0)//����ʼʱ�䣨������ͬһ������ 
		workMachine[tempInput.machine][tempInput.process].begintime=workMachine[tempInput.machine][tempInput.process-1/*ͬ������ǰһ����*/].endtime;
		else
		workMachine[tempInput.machine][tempInput.process].begintime=0;
		if(tempInput.step!=0){//��ͬһ��������ʱ��Ƚ� 
			if(workMachine[inputArray[tempInput.item][tempInput.step-1].machine/*ͬһ������ǰһ�����Ǻλ���*/][inputArray[tempInput.item][tempInput.step-1].process/*��ǰһ���������Ӧ�Ļ����ĵڼ�������*/].endtime>workMachine[tempInput.machine][step[tempInput.machine]].begintime){
				workMachine[tempInput.machine][tempInput.process].begintime=workMachine[inputArray[tempInput.item][tempInput.step-1].machine][inputArray[tempInput.item][tempInput.step-1].process].endtime;
			}
		}//��ʼʱ��Ϊ���Լ�ͬһ��������ͬһ������ǰ����Ľ���ʱ�����ֵ
		workMachine[tempInput.machine][tempInput.process].endtime=workMachine[tempInput.machine][tempInput.process].begintime+tempInput.time;
		//����ʱ��Ϊ��ʼʱ��ӹ���ʱ��
		workMachine[tempInput.machine][tempInput.process].item=tempInput.item;
		workMachine[tempInput.machine][tempInput.process].number=tempInput.machine;
		workMachine[tempInput.machine][tempInput.process].process=repeat[*tempPtr];//�洢��Ҫ��Ϣ 
		if(workMachine[tempInput.machine][tempInput.process].begintime>repairBegin){
			tempChromosome2.message[i]=workMachine[tempInput.machine][tempInput.process].item;
			i++;
		}//δ��ʼ����Ŀ˳�򱣴����� 
		else{
			originRepeat[*tempPtr]=repeat[*tempPtr];
			originStep[tempInput.machine]=step[tempInput.machine];
			originWorkMachine[tempInput.machine][tempInput.process]=workMachine[tempInput.machine][tempInput.process];
		}//�ѿ�ʼ�Ĳ��ִ���origin 
		tempPtr++;//��ȡ��һ��Ƭ��
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
		//����ά��
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

