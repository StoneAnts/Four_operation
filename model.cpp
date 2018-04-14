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
* max: 操作数取值上限
* decimal: true 表示小数 false 表示整数
* negative: true 表示负数 false 表示正数
*return: 随机操作数
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
* opreation: 表示操作符代号之和
*	+ ：加法，用数字8表示
*   - ：减法，用数字4表示
*   * ：乘法，用数字2表示
*   / ：除法，用数字1表示
*return: 操作符代号
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
* max: 表示左括号 max+1表示右括号
* left_bracket: 未匹配的左括号个数
*return: 括号代号
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

