#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define INIT_STACK_SIZE 20
#define INCREMENT_SIZE 10
typedef int Status;
typedef struct Stack_OPND{      //操作数栈 
	float *base;
	float *top;
	int stacksize;
}Stack_OPND;
typedef struct Stack_OPTR{		//操作符栈 
	char *base;
	char *top;
	int stacksize;
}Stack_OPTR;
Status InitStack_OPND(Stack_OPND &S)
{
	S.base=(float*)malloc(sizeof(float)*INIT_STACK_SIZE);
	if(!S.base)
	{
		exit(OVERFLOW);
	}
	S.top=S.base;
	S.stacksize=INIT_STACK_SIZE;
	return OK;
}
float GetTop_OPND(Stack_OPND &S)
{
	float f;
	if(S.base==S.top)
		return ERROR;
	f=*(S.top-1);
	return f;
}
Status Push_OPND(Stack_OPND &S,float f)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(float*)realloc(S.base,sizeof(float)*(S.stacksize+INCREMENT_SIZE));
		if(!S.base)
		{
			exit(OVERFLOW);
		}
		S.top=S.base+S.stacksize;
		S.stacksize+=INCREMENT_SIZE;
	}
	*(S.top)=f;
	S.top++;
	return OK; 
}
Status Pop_OPND(Stack_OPND &S,float &f)
{
	if(S.top==S.base)
	{
		return ERROR;
	}
	f=*(--S.top);
	return OK; 
}
Status EmptyStack_OPND(Stack_OPND S)
{
	if(S.base==S.top)
		return OK;
	else
		return ERROR;
}
Status InitStack_OPTR(Stack_OPTR &S)
{
	S.base=(char*)malloc(sizeof(char)*INIT_STACK_SIZE);
	if(!S.base)
	{
		exit(OVERFLOW);
	}
	S.top=S.base;
	S.stacksize=INIT_STACK_SIZE;
	return OK;
}
char GetTop_OPTR(Stack_OPTR &S)
{
	char c;
	if(S.base==S.top)
		return ERROR;
	c=*(S.top-1);
	return c;
}
Status EmptyStack_OPTR(Stack_OPTR S)
{
	if(S.base==S.top)
		return OK;
	else
		return ERROR;
}
Status Push_OPTR(Stack_OPTR &S,char c)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(char*)realloc(S.base,sizeof(char)*(S.stacksize+INCREMENT_SIZE));
		if(!S.base)
		{
			exit(OVERFLOW);
		}
		S.top=S.base+S.stacksize;
		S.stacksize+=INCREMENT_SIZE;
	}
	*(S.top)=c;
	S.top++;
	return OK; 
}
Status Pop_OPTR(Stack_OPTR &S,char &c)
{
	if(S.top==S.base)
	{
		return ERROR;
	}
	c=*(--S.top);
	return OK; 
}
void PrintStack_OPND(Stack_OPND S)
{
	printf("OPND栈:\n");
	for(float *p=S.base;p<S.top;p++)
	{
		printf("%g ",*p);
	}
	printf("\n");
}
void PrintStack_OPTR(Stack_OPTR S)
{
	printf("OPTR栈:\n");
	for(char *p=S.base;p<S.top;p++)
	{
		printf("%c ",*p);
	}
	printf("\n");
}
float StrToFloat(char *s)
{
	int n,i;
	float temp=0;
	for(i=0;i<strlen(s);i++)
	{
		if(s[i]=='.')
			break;
	}
	for(int j=0;j<strlen(s);j++)
	{
		if(j<i)
			temp+=(float)(s[j]-'0')*pow(10,i-j-1);
		else if(j==i)
			continue;
		else
			temp+=(s[j]-'0')*pow(10,i-j);
	}
	return temp;
}
char OPSET[7]={'+','-','*','/','(',')','#'};
unsigned char Prior[7][7] =
{ // 运算符优先级表
    // 	   '+' '-' '*' '/' '(' ')' '#' 
    /*'+'*/'>','>','<','<','<','>','>',
    /*'-'*/'>','>','<','<','<','>','>',
    /*'*'*/'>','>','>','>','<','>','>',
    /*'/'*/'>','>','>','>','<','>','>',
    /*'('*/'<','<','<','<','<','=','>', 
    /*')'*/'>','>','>','>','=','>',' ', 
    /*'#'*/'<','<','<','<','<',' ','='
};
Status In(char Test)//检测该字符是否为操作符号 
{
    int Find=false;
    for (int i=0; i< 7; i++)
    {
        if(Test == OPSET[i])
            Find= true;
    }
    return Find;
}
Status In_num(char c)
{
	if((c<='9'&&c>='0')||c=='.')
		return OK;
	return ERROR;
}
float Operate(float a,unsigned char optr, float b)//计算 
{
    switch(optr)
    {
    case '+': return a+b;
    case '-': return a-b;
    case '*': return a*b;
    case '/': return a/b;
    default : return 0;
    }
}
Status ReturnOpOrd(char op)//找到操作符号的位置以比较优先级
{
    for(int i=0; i< 7; i++)
    {
        if (op == OPSET[i])
            return i; 
    }
}
Status Locate(char *s,char c)
{
	for(int i=0;i<strlen(s);i++)
	{
		if(s[i]==c)
			return OK;
	}
	return ERROR;
}
char precede(char A, char B)//比较两个操作符的优先级
{
    return Prior[ReturnOpOrd(A)][ReturnOpOrd(B)];
}
float EvaluateExpression(char* Expression,float &result)
{
    // 算术表达式求值的算符优先算法
    // 设OPTR和OPND分别为运算符栈和运算数栈
    Stack_OPTR OPTR;       // 运算符栈，字符元素
    Stack_OPND OPND;       // 运算数栈，实数元素
    InitStack_OPTR(OPTR);
    InitStack_OPND(OPND); 
    char TempData[20],temp;//用来表示实数
    float Data,a,b;
    char optr,*c,Dr[]={'#','\0'};
    Push_OPTR(OPTR,'#');
    printf("输入:#\n");
    PrintStack_OPND(OPND);
    PrintStack_OPTR(OPTR);
    printf("\n");
	c=strcat(Expression,Dr);//不改变原表达式
    strcpy(TempData,"\0");
    while (*c!= '#'||GetTop_OPTR(OPTR)!='#')
    {
    	printf("输入:%c\n",*c);
    	if(EmptyStack_OPND(OPND)&&(In(*c)&&*c!='('))//如果操作数栈是空的读入的第一个字符除了'('以外其他操作符均非法. 
    	{
    		printf("表达式错误,非法运算符\n\n");
			return ERROR;
		}
        if (In_num(*c))
        {
            Dr[0]=*c;
            if(Locate(TempData,*c))
			{
				printf("表达式错误,非法数值\n\n");
				return ERROR;
			} 
            strcat(TempData,Dr);
            c++;
            if (In(*c))
            {
                Data=StrToFloat(TempData);
                Push_OPND(OPND, Data);
                strcpy(TempData,"\0");
            }
    	}
        else if(In(*c))//运算符 
        {
            switch (precede(GetTop_OPTR(OPTR),*c))
            {
            case '<': // 栈顶元素优先级低
            	if(GetTop_OPTR(OPTR)=='#'&&!EmptyStack_OPND(OPND)&&*c=='(')//判断“23(45)...”情况的发生 
            	{
            		printf("表达式错误,非法运算符\n\n");
					return ERROR;
				}
                Push_OPTR(OPTR, *c);
                c++;
                break;
            case '=': // 脱括号并接收下一字符
                Pop_OPTR(OPTR,temp);
                c++;
                break;
            case '>': // 退栈并将运算结果入栈
				Pop_OPTR(OPTR,optr);
				if(!Pop_OPND(OPND,b)||!Pop_OPND(OPND,a)||optr=='#')//输入多个运算符不符合运算规则 
				{
					printf("表达式错误,非法运算符\n\n");
					return ERROR;
				}
                Push_OPND(OPND,Operate(a,optr,b));
            	break;
            default://‘)’没有(与之配对 
            	printf("表达式错误,非法运算符\n\n");
            	return ERROR;
            }
        }
        else
        {
        	printf("表达式错误,非法字符\n\n");
			return ERROR;
		}
        PrintStack_OPND(OPND);
    	PrintStack_OPTR(OPTR);
    	printf("\n");
    }
	Pop_OPND(OPND,result);
	if(!EmptyStack_OPND(OPND))
	{
		printf("表达式错误,非法运算符\n\n");
		return ERROR;
	}
    return OK;
}
