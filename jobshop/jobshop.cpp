#include<stdio.h>//Ӧ���� 2017211387
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#include"graphics.h"
#include"jobshop.h"
struct input inputArray[SIZE][SIZE];//������������ݣ��б�ʾ�����ţ��б�ʾ����
struct machine workMachine[SIZE][SIZE];//���л���
struct machine originWorkMachine[SIZE][SIZE];//��ʼ״̬ 
int originRepeat[SIZE];//��ʼ�������� 
int originStep[SIZE];//��ʼ��������  
double start,finish,programmetime;
extern int itemamount;
extern int machineamount;
struct chromosome minChromosome;
int repairBegin;//ά�޿�ʼʱ��
int main(int argc, char *argv[]) {
	struct chromosome tempChromosome;
	memset(originRepeat,-1,sizeof(originRepeat));//���
	memset(originStep,-1,sizeof(originStep));
	memset(originWorkMachine,-1,sizeof(originWorkMachine));
	repairBegin=0; 
	int i;
	input();
	start=clock();
	srand(time(NULL));
	FILE *fptr;
	fptr=fopen("jobshop_output1.txt","w");//���ָ������ļ������� 
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
