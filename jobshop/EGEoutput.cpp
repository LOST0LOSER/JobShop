#include<stdio.h>//��ҫ�� 2017211378
#include<stdlib.h>
#include"graphics.h"
#include"jobshop.h"
extern int itemamount,machineamount;
void repairOutput();
void menu(int *endtime,double *programme_endtime)//�����굥 
{
	void show_time(int*,double*,int,int);
	FILE *fptr;
	char s[3000];
	if((fptr=fopen("TheInput.txt","r"))==NULL){
		printf("can't read the file");
	}
	else{
    for(int i=0;!feof(fptr);i++)
    {
    	fscanf(fptr,"%c",&s[i]);
	}
	fclose(fptr);
 	}
 	setbkmode(TRANSPARENT);
	setcolor(BLACK);
	setfont(13,0,"����");
	outtextrect(660,20,1275,350,s);//��ӡ������ 
	setfont(15,0,"��Բ");
	show_time(endtime,programme_endtime,1080,20);//��ʾ����ʱ�� 
 	 
}
void show_time(int *endtime,double *programme_endtime,int x,int y)//��ʾʱ�� 
{
	if(y<360){ 
		outtextxy(x,y,"����ǰ����ʱ��:");
		char exchange[20];
		itoa(*endtime,exchange,10);//����ת�ַ� 
		outtextxy(x+40,y+20,exchange);
		outtextxy(x,y+40,"��������ʱ��(��λS):");
		gcvt((*programme_endtime),5,exchange);//����ת�ַ� 
		outtextxy(x+40,y+60,exchange);
	} 
	else{
		outtextxy(x,y,"���޺�����ʱ��:");
		char exchange[20];
		itoa(*endtime,exchange,10);//ת�ַ���� 
		outtextxy(x+40,y+20,exchange);
	}
}
void draw_granter(int *endtime,int x,int y)//������ͼ 
{
	void color(int);
	setcolor(BLACK);
	line(x+30,y+30,x+30,y+320);
	line(x+30,y+320,x+620,y+320);
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	double endtime0=*endtime;//ת������������������ͼ�񳤶� 
	double machineamount0=machineamount;
	char M[2];
	setbkmode(TRANSPARENT);
	for(int i=0;i<machineamount;i++)
	{
		itoa(i,M,10);
		outtextxy(x+8,y+30+i*(300/machineamount0),"M");
		outtextxy(x+20,y+30+i*(300/machineamount0),M);
		for(int j=0;workMachine[i][j].item!=-1;j++)
		{
			color(workMachine[i][j].item);//���ݹ���ѡ��ɫ 
			bar(x+31+workMachine[i][j].begintime/((endtime0)/500),y+30+i*(300/machineamount0),x+31+workMachine[i][j].endtime/((endtime0)/500),y+30+200/machineamount0+i*(300/machineamount0));
			char str[20];
			sprintf(str,"%d",workMachine[i][j].process);
			setfont(15,0,"��Բ");
			outtextxy(x+31+workMachine[i][j].begintime/((endtime0)/500),y+30+i*(300/machineamount0),str);
			setfont(15,0,"��Բ");
			line(x+31+workMachine[i][j].begintime/((endtime0)/500),y+30+i*(300/machineamount0),x+31+workMachine[i][j].begintime/((endtime0)/500),y+30+200/machineamount0+i*(300/machineamount0));
			line(x+31+workMachine[i][j].endtime/((endtime0)/500),y+30+i*(300/machineamount0),x+31+workMachine[i][j].endtime/((endtime0)/500),y+30+200/machineamount0+i*(300/machineamount0));
			//�� 
			line(x+31+workMachine[i][j].begintime/((endtime0)/500),y+30+i*(300/machineamount0),x+31+workMachine[i][j].endtime/((endtime0)/500),y+30+i*(300/machineamount));
			line(x+31+workMachine[i][j].begintime/((endtime0)/500),y+30+200/machineamount0+i*(300/machineamount0),x+31+workMachine[i][j].endtime/((endtime0)/500),y+30+200/machineamount0+i*(300/machineamount0));
			//�� 
			//������� 
		}//��ͼʱ������� 
	}
}
void iteam_color()//������ɫ�� 
{
	char s[10];
	void color(int);
	setfont(12,0,"��Բ");
	outtextxy(570,380,"������ɫ"); 
	outtextxy(520,380,"������"); 
	setfont(15,0,"��Բ");
	for(int i=0;i<itemamount;i++)
	{
		color(i);
		bar(580,400+i*15,620,410+i*15);
		sprintf(s,"%d",i);
		outtextxy(530,395+i*15,s);
	}
	outtextxy(530,395+itemamount*15,"����");
	color(-2); 
	bar(580,400+itemamount*15,620,410+itemamount*15);
}

void color(int i)//ѡɫ 
{
	switch(i)
	{
		case 0:setfillcolor(EGERGB(0,255,127));break;
		case 1:setfillcolor(EGERGB(255 ,215 ,0));break;
		case 2:setfillcolor(EGERGB(205 ,92 ,92));break;
		case 3:setfillcolor(EGERGB(139, 137 ,137));break;
		case 4:setfillcolor(EGERGB(238 ,213 ,183));break;
		case 5:setfillcolor(EGERGB(	139 ,119, 101));break;
		case 6:setfillcolor(EGERGB(131 ,111, 255));break;
		case 7:setfillcolor(EGERGB(67, 110 ,238));break;
		case 8:setfillcolor(EGERGB(	30 ,144 ,255));break;
		case 9:setfillcolor(EGERGB(155, 48 ,255));break;
		case 10:setfillcolor(EGERGB(205, 0 ,0));break;
		case 11:setfillcolor(EGERGB(255, 99 ,71));break;
		case 12:setfillcolor(EGERGB(238, 118 ,0));break;
		case 13:setfillcolor(EGERGB(255 ,193 ,193));break;
		case 14:setfillcolor(EGERGB(205 ,205, 0));break;
		case 15:setfillcolor(EGERGB(	110, 139, 61));break;
		case 16:setfillcolor(EGERGB(118 ,238, 198));break;
		case 17:setfillcolor(EGERGB(	0, 238 ,238));break;
		case 18:setfillcolor(EGERGB(193, 255 ,193));break;
		case 19:setfillcolor(EGERGB(	192 ,255,62));break;
		case 20:setfillcolor(EGERGB(255,236,139));break;
		case -2:setfillcolor(BLACK);break;
	}
}
void draw_graphics(int *endtime,double *programme_endtime)//����ȫ��ͼ�� 
{
    initgraph(1280,720);
    setbkcolor(BLACK);
    setfillcolor(WHITE);
	bar(5, 5, 640, 350);//���ϰ�ɫ���� 
	bar(645,5,1275,350);//����
	bar(5,355,640,715);//����
	bar(645,355,1275,715);//����
	menu(endtime,programme_endtime);
	draw_granter(endtime,5,5);//ԭ�ȸ���ͼ 
	iteam_color();
	repairOutput();
	bar(645,355,1275,715);//������� 
	draw_granter(endtime,645,355);//���޺����ͼ 
	show_time(endtime,programme_endtime,500,650);//���޺�ʱ�� 
	getch();
	closegraph();
}

