#include<stdio.h>//��ҫ�� 2017211378 
#include<string.h>
#include "jobshop.h"
int itemamount,machineamount;
extern void input()
{
    memset(inputArray,-1,sizeof(inputArray));
    int i=0,j;
    char s;
    FILE *fptr;
    if((fptr=fopen("TheInput.txt","r"))==NULL)//��ȡ�ļ�+�ж��ļ��ܷ��ȡ
    {
        printf("can't not read the file\n");
    }
    else
    {

        fscanf(fptr,"%d",&itemamount);//���빤�����������
        fscanf(fptr,"%d",&machineamount);
        while(i<itemamount)//���ļ�δ����ĩβʱ��ȡ����
        {
            j=0;
            while(s!='\n')//���з�ascii��Ϊ10
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
    fclose(fptr);//�ر��ļ�ָ��
}
