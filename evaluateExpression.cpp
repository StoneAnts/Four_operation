#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
#define OPSETSIZE 8
bool flag;									// �ж������Ƿ�Ϸ���־

unsigned char Prior[8][8] =
{
	// ��������ȼ���
	//	    '+' '-' '*' '/' '%' '(' ')' '#'
	/*'+'*/ '>','>','<','<','<','<','>','>',
	/*'-'*/ '>','>','<','<','<','<','>','>',
	/*'*'*/ '>','>','>','>','>','<','>','>',
	/*'/'*/ '>','>','>','>','>','<','>','>',
	/*'%'*/ '>','>','>','>','>','<','>','>',
	/*'('*/ '<','<','<','<','<','<','=',' ',
	/*')'*/ '>','>','>','>','>',' ','>','>',
	/*'#'*/ '<','<','<','<','<','<',' ','=',
};

typedef struct StackChar
{
	char c;
	struct StackChar *next;
}SC;       //StackChar���͵Ľ��SC

typedef struct StackFloat
{
	float f;
	struct StackFloat *next;
}SF;       //StackFloat���͵Ľ��SF

SC *Push(SC *s,char c)          //SC���͵�ָ��Push������p
{
	SC *p=(SC*)malloc(sizeof(SC));
	p->c=c;
	p->next=s;
	return p;
}

SF *Push(SF *s,float f)        //SF���͵�ָ��Push������p
{
	SF *p=(SF*)malloc(sizeof(SF));
	p->f=f;
	p->next=s;
	return p;
}

SC *Pop(SC *s)    //SC���͵�ָ��Pop
{
	SC *q=s;
	s=s->next;
	free(q);
	return s;
}

SF *Pop(SF *s)      //SF���͵�ָ��Pop
{
	SF *q=s;
	s=s->next;
	free(q);
	return s;
}

float Operate(float a,unsigned char theta, float b)      //���㺯��Operate
{
	switch(theta)
	{
	case '+': return a+b;
	case '-': return a-b;
	case '*': return a*b;
	case '/':
		if(b == 0) {flag = false;return 0;}				// �жϳ����Ƿ�Ϊ0
		return a/b;
	case '%':
		{
			if(b == 0) {flag = false;return 0;}			// �жϳ����Ƿ�Ϊ0
			int c = (int)a%(int)b;
			return c;
		}
	default : return 0;
	}
}

char OPSET[OPSETSIZE]={'+','-','*','/','%','(',')','#'};

bool In(char Test,char *TestOp)
{
	for (int i=0; i< OPSETSIZE; i++)
	{
		if(Test == TestOp[i])
			return true;
	}
	return false;
}

int ReturnOpOrd(char op,char *TestOp)
{
	for(int i=0; i< OPSETSIZE; i++)
	{
		if (op == TestOp[i])
			return i;
	}
	return 0;
}

char precede(char Aop, char Bop)
{
	return Prior[ReturnOpOrd(Aop,OPSET)][ReturnOpOrd(Bop,OPSET)];
}

float EvaluateExpression(char* MyExpression)
{
	// �������ʽ��ֵ����������㷨
	// ��OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��OPΪ���������
	SC *OPTR=NULL;									 // �����ջ���ַ�Ԫ��
	SF *OPND=NULL;									 // ������ջ��ʵ��Ԫ��
	char TempData[20];								 // �����洢��ת��������
	float Data, a, b;
	char theta, *c, Dr[] = {'#', '\0'};				 // Dr[]��'#'����ʹ���������ַ���βΪ'#','\0'���ַ��������ı�־�������䳤��
	OPTR = Push(OPTR, '#');
	c = strcat(MyExpression, Dr);
	strcpy(TempData, "\0");							//�ַ�����������,��TempData[0]Ϊ"\0"
	while (*c != '#' || OPTR->c != '#')
	{
		if (!In(*c, OPSET))
		{
			Dr[0] = *c;
			strcat(TempData, Dr);				//�ַ������Ӻ���
			c++;
			if(In(*c, OPSET))
			{
				Data = atof(TempData);			//�ַ���ת������(double)
				OPND = Push(OPND, Data);
				strcpy(TempData,"\0");
			}
		}
		else if(In(*c, OPSET))					// ���ǲ��������ջ
		{
			switch(precede(OPTR->c, *c))
			{
			case '<': // ջ��Ԫ�����ȼ���
				OPTR = Push(OPTR, *c);
				c++;
				break;
			case '=': // �����Ų�������һ�ַ�
				OPTR = Pop(OPTR);
				c++;
				break;
			case '>': // ��ջ������������ջ
				if(OPTR->c == '#'){cout << "�������!"; break;}
				theta= OPTR->c;
				OPTR = Pop(OPTR);

				if(OPND==NULL) {flag = false; return 0;}
				b = OPND->f;
				OPND = Pop(OPND);

				if(OPND==NULL) {flag = false; return 0;}
				a = OPND->f;
				OPND = Pop(OPND);

				float p = Operate(a, theta, b);				//p������¼�����Ľ��
				if(!flag) return 0;							//�����㲻�Ϸ���������
				OPND = Push(OPND, p);
				break;
			} //switch
		}
	} //while
	return OPND->f;
} //EvaluateExpression

void calculate(char* a)
{
    flag = true;
    if(!flag)cout << "\n\a���ʽ�������!\n\n";
			else{
				//cout << "\n�ñ��ʽ��ֵΪ:";
				printf("%g",EvaluateExpression(a));
			}

}
