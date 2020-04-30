#include<stdio.h>//应冲书 2017211387
#include <stdlib.h>
#include<windows.h>
#include"graphics.h"
#include"ege.h"
#include"jobshop.h"
extern int machineamount;;
extern int repairBegin;
extern struct chromosome minChromosome;
void repair(int machineNumber,struct chromosome *tempChromosome,int repairBegin,int repairMessage[]);
extern void repairOutput(){
	int times=100;
	int interval=times*2;
	int timeLine=0;
	int i;
	int endflag=0;
	char timeLineC[4];
	char iC[2];
	char itemC[2];
	char processC[2];
	char starttime[4];
	char endtime[4];
	int repairMessage[SIZE];
	struct machine* workingMachine[SIZE];
	for(i=0;i<machineamount;i++){
		workingMachine[i]=&workMachine[i][0];
	}
	while(endflag!=machineamount){
		endflag=0;
		setfillcolor(WHITE);
		bar(5,355,450,715);//左下 
		setcolor(BLACK); 
		outtextxy(60,420-(200/machineamount),"当前|");
		outtextxy(100,420-(200/machineamount),"机器|");
		outtextxy(140,420-(200/machineamount),"状态|");
		outtextxy(180,420-(200/machineamount),"工件|");
		outtextxy(220,420-(200/machineamount),"步骤|");
		outtextxy(260,420-(200/machineamount),"已开始|");
		outtextxy(320,420-(200/machineamount),"将结束|");//title 
		for(i=0;i<machineamount;i++){
			if((*(workingMachine[i]+1)).item==-1&&timeLine>(*workingMachine[i]).endtime)
			endflag++;
			while((*(workingMachine[i]+1)).item!=-1&&timeLine>=(*(workingMachine[i]+1)).begintime){
				workingMachine[i]++;
			}
			itoa(timeLine,timeLineC,10);
			itoa(i,iC,10);
			outtextxy(60,420+i*(200/machineamount),timeLineC);//当前时间 
			outtextxy(100,420+i*(200/machineamount),iC);//机器号 
			if(timeLine>=(*workingMachine[i]).endtime){
				outtextxy(140,420+i*(200/machineamount),"空闲");
			}
			else{
				if((*workingMachine[i]).item!=-2){
					if((*workingMachine[i]).begintime<=timeLine&&timeLine<(*workingMachine[i]).endtime){
						outtextxy(140,420+i*(200/machineamount),"加工");
					}
					else{
						outtextxy(140,420+i*(200/machineamount),"空闲");
					}
				}
				else{
					if((*workingMachine[i]).begintime<=timeLine&&timeLine<(*workingMachine[i]).endtime){
						outtextxy(140,420+i*(200/machineamount),"检修");
					}
					else{
						outtextxy(140,420+i*(200/machineamount),"空闲");
					}
				} 
			} //状态 
			if((*workingMachine[i]).item!=-2&&(*workingMachine[i]).begintime<=timeLine&&timeLine<(*workingMachine[i]).endtime){
				itoa((*workingMachine[i]).item,itemC,10);
				outtextxy(180,420+i*(200/machineamount),itemC);//工件号 
				outtextxy(200,420+i*(200/machineamount),"-");
				itoa((*workingMachine[i]).process,processC,10);//工件步骤 
				outtextxy(220,420+i*(200/machineamount),processC);
			}
			if(timeLine>=(*workingMachine[i]).begintime)
			itoa(timeLine-(*workingMachine[i]).begintime,starttime,10);
			else
			itoa(timeLine,starttime,10);
			outtextxy(260,420+i*(200/machineamount),starttime);//已开始时间 
			if(timeLine<(*(workingMachine[i]+1)).begintime||(timeLine<(*workingMachine[i]).endtime&&(*(workingMachine[i]+1)).item==-1)){
				if(timeLine<(*workingMachine[i]).endtime) 
				itoa((*workingMachine[i]).endtime-timeLine,endtime,10);
				else
				itoa((*(workingMachine[i]+1)).begintime-timeLine,endtime,10);//该状态持续时间 
				outtextxy(320,420+i*(200/machineamount),endtime);
			} 
			else{
				outtextxy(320,420+i*(200/machineamount),"结束");
			}
		}
		Sleep(2000); 
		while(kbhit()){
			repairBegin=timeLine; 
			setfillcolor(WHITE);
			bar(645,355,1275,715);//右下
			memset(repairMessage,-1,sizeof(repairMessage));
			char s[10];
			int place=0;
    		inputbox_getline("对话框","请输入机器号，退出请输入-1",s,10);
    		place=atoi(s);
    		int where=400;
    		while(place!=-1){
    			outtextxy(700,where,s);
    			inputbox_getline("对话框","请输入维修时间",s,10);
    			outtextxy(730,where, s);
    			where=where+30;
    			repairMessage[place]=atoi(s);
    			inputbox_getline("对话框","请输入机器号，退出请输入-1",s,10);
    			place=atoi(s);
    		}
    		repair(machineamount,&minChromosome,timeLine,repairMessage);
    		superAnneal(&minChromosome);
    		for(i=0;i<machineamount;i++){
				workingMachine[i]=&workMachine[i][0];
			}	
		}//维修 
		timeLine=timeLine+2*times;
	}
	output2(&minChromosome);
}
