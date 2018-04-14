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
*Summary: ����
*Parameters:
* rep: ���ɵı��ʽ�ֿ�
* flag: �����ɵı��ʽ�±�
*return: false��ʾû���ظ��ı�ʾʽ true��֮
**/
bool recheck(Repertory* rep,int flag)
{
  for(int i = 0; i<flag; i++)//����flag��֮ǰ�ı��ʽ
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
* number: �������ʽ�ĸ���
* max: ������ȡֵ����
*operandNumber: �������ĸ���
*decimal: true ��ʾС�� false ��ʾ����
*negative: true ��ʾ���� false ��ʾ����
*bracket: true ��ʾ������ false ��ʾ������
*opreation: ��ʾ����������֮��
*   + ���ӷ���������8��ʾ
*   - ��������������4��ʾ
*   * ���˷���������2��ʾ
*   / ��������������1��ʾ
*output:0��ʾ���������̨��1��ʾ������ļ���2��ʾ�������ӡ��
**/
Repertory* expression(int number, int max, int operandNumber, bool decimal, bool negative,
				bool bracket, int opreation, int output)
{
	//���ʽ�ֿ⶯̬��ʼ��
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

		//�����ʾʽ�ظ������ʽ��ջָ���һ
		if(recheck(rep,i))
		{
			i--;
		}
		//��������������û��Զ���ķ�Χ�����ʽָ���һ
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
* rep: ���ɵı��ʽ�ֿ�
* output: 0��ʾ���������̨��1��ʾ������ļ���2��ʾ�������ӡ��
**/
void display(Repertory* rep,int output)
{
   //���������̨
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
* rep: ���ɵı��ʽ�ֿ�
* output: 0��ʾ���������̨��1��ʾ������ļ���2��ʾ�������ӡ��
* isResult: true��ʾ����������false��ʾ����������
* isBracket:ture��ʾ�����ţ�false��ʾû������
**/
void getResult(Repertory* rep, bool isResult, bool isBracket)
{
    int n = 0; //��¼��������
    bool turn = false; //��־������������������ʱΪtrue���������һ����������һ��������ס
    for(int i = 0;i<(rep->row);i++)
	{
	    char equation[100]={'0'};
	    string str="";
		for(int j = 0;j<(rep->col-1);j++)
		{
			if(j%2==0)
			{
			    if(j==0&&isBracket&&random(2))//��һλ�������Ƿ�����������
                {
                    str+="(";
                    cout << "(";
                    n++;
                }
				str+= to_string(rep->array[i][j]); //���������ŵ��ַ���str��

                if(j!=0&&isBracket&&random(2)&&n!=0&&!turn)//�Ƿ���Ҫ����������
                {
                    n--;
                    str+=")";
                    cout<<rep->array[i][j]<<")";
                }
                else
				{
				    turn = false;
				    cout<<rep->array[i][j];            //��ӡ����������
				}
			}
			else
			{
			    str+=configure[(int)rep->array[i][j]-1];//���������ŵ��ַ���str��
			    if(isBracket&&random(2)&&((rep->col-j)/2>n+1))    //�Ƿ���Ҫ����������
                {
                    turn = true;
                    n++;
                    str+="(";
                    cout<<configure[(int)(rep->array[i][j])-1]<<"(";
                }
                else
				{
				    cout<<configure[(int)(rep->array[i][j])-1];//��ӡ����������
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
		strcpy(equation, str.c_str()); //���ַ���strת��Ϊ�ַ�����equation
		if(isResult)
		{
		    calculate(equation);  //���㲢��ӡ�����
		}
		cout <<endl;
	}
}



