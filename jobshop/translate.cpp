#include<stdio.h>//Ӧ���� 2017211387 
#include<string.h>
#include <time.h>
#include"jobshop.h"
extern int repairBegin;
extern void translate(int machineNumber,struct chromosome *tempChromosome)
{
	int* tempPtr=NULL;
	int repeat[SIZE];//����������
	int step[SIZE];//����������
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
	tempPtr=(*tempChromosome).message;//��ͷ��ʼ��
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
			if(workMachine[tempInput.machine][tempInput.process].begintime<repairBegin){
				workMachine[tempInput.machine][tempInput.process].begintime=repairBegin;
			}
		}//��ʼʱ��Ϊ���Լ�ͬһ��������ͬһ������ǰ����Ľ���ʱ�����ֵ
		workMachine[tempInput.machine][tempInput.process].endtime=workMachine[tempInput.machine][tempInput.process].begintime+tempInput.time;
		//����ʱ��Ϊ��ʼʱ��ӹ���ʱ��
		workMachine[tempInput.machine][tempInput.process].item=tempInput.item;
		workMachine[tempInput.machine][tempInput.process].number=tempInput.machine;
		workMachine[tempInput.machine][tempInput.process].process=repeat[*tempPtr];//�洢��Ҫ��Ϣ 
		if(temptime<workMachine[tempInput.machine][tempInput.process].endtime)//��¼���ʱ�� 
		temptime=workMachine[tempInput.machine][tempInput.process].endtime;
		tempPtr++;//��ȡ��һ��Ƭ��
	}
	(*tempChromosome).time=temptime;
	return;
}

