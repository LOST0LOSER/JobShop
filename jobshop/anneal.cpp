#include<stdio.h>//���Դ 2017211390 
#include<string.h>
#include"jobshop.h"
void translate(int,struct chromosome*);
extern int machineamount;
extern void anneal(struct chromosome *tempChromosome,struct chromosome *minChromosome)
{
	int i,j,k;
	int tmp;
	int change=0;
	i=0;
	j=0;
	k=0;
	memset((*minChromosome).message,-1,sizeof((*minChromosome).message));//��� 
	while((*tempChromosome).message[k]!=-1){
		(*minChromosome).message[k]=(*tempChromosome).message[k];
		k++;
	}//��ʼ����min��temp��ͬ 
	translate(machineamount,tempChromosome);//���� 
	(*minChromosome).time=(*tempChromosome).time;
	i=0;
	while((*tempChromosome).message[i+1]!=-1){  //ÿ�����ֺ��������������ֽ��������ʱ�������� 
		j=i;
		while((*tempChromosome).message[j]!=-1){
			if((*tempChromosome).message[i]!=(*tempChromosome).message[j]){//����ͬ������½���temp 
				change=(*tempChromosome).message[i];
				(*tempChromosome).message[i]=(*tempChromosome).message[j];
				(*tempChromosome).message[j]=change;
				translate(machineamount,tempChromosome);//���ʱ�� 
				if((*minChromosome).time>=(*tempChromosome).time){//ʱ�����ˣ��ͽ���min 
					change=(*minChromosome).message[i];
					(*minChromosome).message[i]=(*minChromosome).message[j];
					(*minChromosome).message[j]=change;
					(*minChromosome).time=(*tempChromosome).time;
				}
				else{//���򣬼Ȳ�����min������֮ǰ��temp�н����Ľ������������ƽ����������� 
					change=(*tempChromosome).message[i];
					(*tempChromosome).message[i]=(*tempChromosome).message[j];
					(*tempChromosome).message[j]=change;
				}
			}
			j++;
		}
		i++;
	}
	return;
}
