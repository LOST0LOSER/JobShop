#include<stdio.h>//周耀东 2017211378 
#include<string.h>
#include "jobshop.h"
int itemamount,machineamount;
extern void input()
{
    memset(inputArray,-1,sizeof(inputArray));
    int i=0,j;
    char s;
    FILE *fptr;
    if((fptr=fopen("TheInput.txt","r"))==NULL)//读取文件+判断文件能否读取
    {
        printf("can't not read the file\n");
    }
    else
    {

        fscanf(fptr,"%d",&itemamount);//输入工件与机器数量
        fscanf(fptr,"%d",&machineamount);
        while(i<itemamount)//当文件未读到末尾时读取数据
        {
            j=0;
            while(s!='\n')//换行符ascii码为10
            {
                fscanf(fptr,"%d",&inputArray[i][j].machine);
                fscanf(fptr,"%d",&inputArray[i][j].time);
                s=fgetc(fptr);
                inputArray[i][j].item=i;
                inputArray[i][j].step=j;
                j++;
            }
            s='0';
            i++;
        }
    }
    fclose(fptr);//关闭文件指针
}
