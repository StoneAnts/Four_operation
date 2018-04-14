#include<iostream>
#include<malloc.h>
#include"model.h"
#include "controller.h"
#include "evaluateExpression.h"
#include<string.h>

using namespace std;
char configure[] = {'+','-',' ','*',' ',' ',' ','/'};

Repertory* rep;
/**
*Summary: 查重
*Parameters:
* rep: 生成的表达式仓库
* flag: 新生成的表达式下标
*return: false表示没有重复的表示式 true反之
**/
bool recheck(Repertory* rep,int flag)
{
  for(int i = 0; i<flag; i++)//遍历flag行之前的表达式
  {
      bool target = true;
	  for(int j = 0; j<(rep->col-1); j++)
	  {
		  if((rep->array[i][j]!=rep->array[flag][j]))
		  {
			  target = false;
		  }
	  }
	  if(target)
	  {
		  return true;
	  }
  }
  return false;
}

/**
*Summary:
*Parameters:
* number: 算数表达式的个数
* max: 操作数取值上限
*operandNumber: 操作数的个数
*decimal: true 表示小数 false 表示整数
*negative: true 表示负数 false 表示正数
*bracket: true 表示有括号 false 表示无括号
*opreation: 表示操作符代号之和
*   + ：加法，用数字8表示
*   - ：减法，用数字4表示
*   * ：乘法，用数字2表示
*   / ：除法，用数字1表示
*output:0表示输出到控制台，1表示输出到文件，2表示输出到打印机
**/
Repertory* expression(int number, int max, int operandNumber, bool decimal, bool negative,
				bool bracket, int opreation, int output)
{
	//表达式仓库动态初始化
	int i = 0;
	rep = (Repertory*)malloc(sizeof(Repertory));
	rep->row = number;
	rep->col = 2*operandNumber;
    rep->array=(float**)malloc(sizeof(float*)*rep->row);
    for(i = 0; i < number; i++)
	{
        rep->array[i] = (float*)malloc(sizeof(float)*rep->col);
	}

	for(i = 0; i < number; i++)
	{
		int j = 0;
		for(j = 0; j < operandNumber; j++)
		{
			rep->array[i][j*2] = getOperand(max, decimal, negative);
			if(j < operandNumber-1)
			{
				rep->array[i][j*2+1] = getOperation(opreation);
			}
		}

		//如果表示式重复，表达式堆栈指针减一
		if(recheck(rep,i))
		{
			i--;
		}
		//如果计算结果超出用户自定义的范围，表达式指针减一
		if(recheck(rep,i))
		{
			i--;
		}
	}
	return rep;
}
/**
*Summary:
*Parameters:
* rep: 生成的表达式仓库
* output: 0表示输出到控制台，1表示输出到文件，2表示输出到打印机
**/
void display(Repertory* rep,int output)
{
   //输出到控制台
	for(int i = 0;i<(rep->row);i++)
	{
		for(int j = 0;j<(rep->col-1);j++)
		{
			if(j%2==0)
			{
				cout<<rep->array[i][j];
			}
			else
			{
				cout<<configure[(int)(rep->array[i][j])-1];
			}

		}
		cout<<"="<<endl;
	}
}
/**
*Summary:
*Parameters:
* rep: 生成的表达式仓库
* output: 0表示输出到控制台，1表示输出到文件，2表示输出到打印机
* isResult: true表示计算出结果，false表示不计算出结果
* isBracket:ture表示有括号，false表示没有括号
**/
void getResult(Repertory* rep, bool isResult, bool isBracket)
{
    int n = 0; //记录左括号数
    bool turn = false; //标志，当操作符后有括号时为true，避免出现一个操作数被一对括号套住
    for(int i = 0;i<(rep->row);i++)
	{
	    char equation[100]={'0'};
	    string str="";
		for(int j = 0;j<(rep->col-1);j++)
		{
			if(j%2==0)
			{
			    if(j==0&&isBracket&&random(2))//第一位操作数是否生成左括号
                {
                    str+="(";
                    cout << "(";
                    n++;
                }
				str+= to_string(rep->array[i][j]); //将操作数放到字符串str中

                if(j!=0&&isBracket&&random(2)&&n!=0&&!turn)//是否需要生成右括号
                {
                    n--;
                    str+=")";
                    cout<<rep->array[i][j]<<")";
                }
                else
				{
				    turn = false;
				    cout<<rep->array[i][j];            //打印单个操作数
				}
			}
			else
			{
			    str+=configure[(int)rep->array[i][j]-1];//将操作符放到字符串str中
			    if(isBracket&&random(2)&&((rep->col-j)/2>n+1))    //是否需要生成左括号
                {
                    turn = true;
                    n++;
                    str+="(";
                    cout<<configure[(int)(rep->array[i][j])-1]<<"(";
                }
                else
				{
				    cout<<configure[(int)(rep->array[i][j])-1];//打印单个操作符
				}
			}
		}
		while(n!=0)
        {
            str+=")";
            cout << ")";
            n--;
        }
		cout << "=";
		strcpy(equation, str.c_str()); //将字符串str转换为字符数组equation
		if(isResult)
		{
		    calculate(equation);  //计算并打印出结果
		}
		cout <<endl;
	}
}



