#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "model.h"
using namespace std;
int random(int range)
{
    //srand(time(0));
	return rand()%range;
}
/**
*Summary:
*Parameters:
* max: ������ȡֵ����
* decimal: true ��ʾС�� false ��ʾ����
* negative: true ��ʾ���� false ��ʾ����
*return: ���������
**/
float getOperand(int max, bool decimal, bool negative)
{
	if(!decimal && !negative)
	{
		return random(max);
	}
	else if(!decimal && negative)
	{
		return -1*random(max);
	}
    else if(decimal && !negative)
	{
		return random(max)/100.0+random(99);
	}
	else
	{
		return -1*(random(max)/100.0+random(99));
	}
}
/**
*Summary:
*Parameters:
* opreation: ��ʾ����������֮��
*	+ ���ӷ���������8��ʾ
*   - ��������������4��ʾ
*   * ���˷���������2��ʾ
*   / ��������������1��ʾ
*return: ����������
**/
int getOperation(int opreation)
{
	int count = 0;
	int i = 0;
	int temp = opreation;
	for(;i<4;i++)
	{
		count+=(temp&1);
		temp = temp>>1;
	}
	count =  random(count);
	for(i = 1;i<=8;i=i*2)
	{
		if((opreation&i) != 0)
		{
			if(count==0)
			{
				return i;
			}
			else
			{
				count--;
			}
		}
	}
}
/**
*Summary:
*Parameters:
* max: ��ʾ������ max+1��ʾ������
* left_bracket: δƥ��������Ÿ���
*return: ���Ŵ���
**/
int getBracket(int max, int &left_bracket)
{
	if(left_bracket == 0)
	{
		return max;
	}
	else
	{
		return max+random(2);
	}
}

