#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define STACKELEMENT 100 //�����ջ�п���ջԪ�ظ���
#define BUFFERSIZE 100  //������ʱ��������С
 
typedef int Status; //���巵��״̬
typedef struct  //�����ջ����ջ��ֻ����ջ��С��ÿ����ջԪ�ش�С��ջ��һ��ʹ�ÿ�ָ����в����������������Լ������ջ�������˺����������޹��ԡ�����ʵ����ջ��ͨ�á�
{
  void *base; //ָ��ջ��
  void *top;  //ָ��ջ��
  int stackSize; //ջ�Ŀռ���������С
  int typeSize; //��ջʱ������Ԫ��ռ�ÿռ��С
} sqStack;
 
Status InitStack(sqStack *s,unsigned stackSize,unsigned typeSize); //��ʼ��ջ
Status Push(sqStack *s,void *e); //��ջ
Status Pop(sqStack *s,void *e); //��ջ
Status ClearStack(sqStack *s); //���ջ������Ԫ��
Status DestroyStack(sqStack *s); //����ջ
int GetLen(sqStack *s); //��ȡ����ջԪ�ظ���
 
Status Calculate(char *arr,void *result); //������ʽ���������һ��arrΪʹ�ÿո�ָ��Ĳ��ú�׺���ʽ��ʾ��Ҫ������ַ���,����arr={"3 5 + "}����������result��ż�������
Status InfixToPostfix(char *infix,char *postfix); //����׺���ʽת��Ϊ��׺���ʽ������infix={"3+5\n"} ,ת����postfix={"3 5 + "};
 
void my_err(char *str); //�Զ����������
 
int main(int argc,char *argv[])
{
  printf("Please input the nifix expression.\n"); //������׺���ʽ��
  char src[BUFFERSIZE]={'\0'}; //�����׺���ʽ����ʱ������
  char *infix=src; 
  char postfix[BUFFERSIZE]={'\0'}; //��ź�׺���ʽ����ʱ������
  fgets(infix,BUFFERSIZE,stdin); //�ӱ�׼�������ж�ȡҪ���������������ʽ
  printf("Infix expression:%s",infix);
  InfixToPostfix(infix,postfix); //����׺ת��Ϊ��׺���ʽ
  printf("Postfix expression:%s\n",postfix);
  double result;
  Calculate(postfix,&result); //�����׺���ʽ�Ľ��
  printf("result:%f\n",result);
  exit(0);
}
 
/*
����׺���ʽת��Ϊ��׺���ʽ
����:infix ָ����׺���ʽ���Իس�����\n��β��
postfix ָ���׺���ʽ��ʱ���������������ת����Ľ����
��ת�����򣺴����ұ�����׺���ʽ��ÿ�����ֺͷ��ţ�����������ֱ�ӱ�����postfix�����У����Ƿ��ţ����ж�����ջ�����ŵ����ȼ����������Ż������ȼ�������ջ�����ţ���ջ��Ԫ�����γ�ջ�������ֱ�����������Ż���ջ��ʱ���Ž��ղŵ��Ǹ�������ջ��
*/
Status InfixToPostfix(char *infix,char *postfix)
{
  sqStack s;
  if(InitStack(&s,STACKELEMENT*sizeof(char),sizeof(char))==ERROR)
		my_err("InfixToPostfix init stack error��");
  char c,e;
  int j=0,i=0;
  c=*(infix+i); //ȡ����׺���ʽ�еĵ�һ���ַ�
  i++;
  while('\n'!=c) //�������з�����ʾת������
    {
       while(c>='0'&&c<='9'|| c=='.') //���ж�һ��ȡ�����ַ��Ƿ������֣���������ֵĻ�����ֱ�Ӵ���postfix����
		{ 
		  postfix[j++]=c;
		  c=*(infix+i);
		  i++;
		  if((c<'0'||c>'9')&&(c!='.')) //����������֣����ں�����ӿո��Ա����ָ�������
			{
			postfix[j++]=' ';
			}
		}
//		while(isdigit(c) || c=='.')//���ڹ�������,���û�����
//        {
//            postfix[j++]=c;
//            postfix[j]='\0';
//            if(j>=10)
//            {
////                 cout<<"�������ݹ���\n";
//                printf("�������ݹ���\n");
//                return -1;
//            }
////            cin>>c;
//            //scanf("%c",&c);
//
//            if(c == ' ')
//            {
//                d = atof(str);//���ַ���ת��Ϊ����
////                cout<<d;
//                Push(&s, d);
//                i = 0;
//                break;
//            }
//             if(c<'0'||c>'9') //����������֣����ں�����ӿո��Ա����ָ�������
//			{
//			postfix[j++]=' ';
//			}
//        }
      if(')'==c) //�������֣����ж��Ƿ�Ϊ�����š�[���ŵ����ȼ���ߣ����ԣ�����������ŵĻ����͵��Ƚ���������ĸ�������]
		{
		  Pop(&s,(void*)&e);
		  while('('!=e) //ֱ������������Ϊֹ
			{
			  postfix[j++]=e;
			  postfix[j++]=' ';
			  Pop(&s,(void*)&e);
			}
		}
      else if('+'==c||'-'==c) //����ǼӼ���,��Ϊ���������ȼ�����ˣ����Դ�ʱ�Ƚ�ջ������з��ų�ջ��(��������������)���ٰѴ˷�����ջ
		{
		  if(!GetLen(&s)) //����ǿ�ջ����ֱ�ӽ��Ӽ�����ջ
			{
			  Push(&s,(void*)&c);
			}
		  else 
			{
			  do
				{
				  Pop(&s,(void*)&e);
				  if('('==e)   
					{
					  Push(&s,(void*)&e);
					}
				  else 
					{
					  postfix[j++]=e;
					  postfix[j++]=' ';
					}
				}while(GetLen(&s)&&'('!=e);  //��ջ������з��ų�ջ(��������������)
			  Push(&s,(void*)&c); //��������ļӼ�������ջ
			}
		}
      else if('*'==c||'/'==c||'('==c) //����ǳ˳��Ż������ţ���Ϊ���ǵ����ȼ��ߣ�����ֱ����ջ��
		{
		  Push(&s,(void*)&c);
		}
      else if('\n'==c) //�ж�һ�£����з����Ƿ���ת�����
		{
		  break;
		}
      else //���ߵ����else�ģ������Ҳ���ʶ�ķ�����
		{
		  // printf("\nError:input error,the character %d cann't recognize!\n",c);
		  return -1;
		}
      c=*(infix+i); //ȡ����һ���ַ�����ת��
      i++;
    }
  while(GetLen(&s)) //ת����ɺ�ջ����ܻ���û��ջ���������
    {
      Pop(&s,(void*)&e);
      postfix[j++]=e;
      postfix[j++]=' ';
    }
  DestroyStack(&s);
  return TRUE;
}
 
/*
�����׺���ʽ�Ľ��
������arrʹ�ÿո�ָ��ĺ�׺���ʽ�ַ���������arr="31 5 + "
result ���������Ϻ�Ľ��
ע���������ջ�������׺���ʽ�Ľ��������ȡ����׺���ʽ�еķ��Ž��бȽϣ���������֣���ֱ����ջ������Ƿ��ţ����ջ���Σ���������Ҫ��������������м��㣬֮���ٽ���������ջ��֪����׺���ʽ�����з��Ŷ��ѱȽ���ϡ�
*/
Status Calculate(char *arr,void *result)
{
  // printf("%s\n",arr);
  double d,e,f; //d,e �������������f���d,e�����Ľ��.
  sqStack s; 
  char *op; //��ź�׺���ʽ�е�ÿ�������������
  char *buf=arr; //����bufhe saveptr������������strtok_r��������Ҫ��
  char *saveptr=NULL;
  if(InitStack(&s,STACKELEMENT*sizeof(double),sizeof(double))==ERROR)
		my_err("Calculate init stack error!");
  while((op=strtok_r(buf," ",&saveptr))!=NULL) //����strtok_r�����ָ��ַ���
    {
      buf=NULL;
      switch(op[0])
		{
		case '+':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=d+e;
		  Push(&s,&f);
		  break;
		case '-':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=e-d;
		  Push(&s,&f);
		  break;
		case '*':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=d*e;
		  Push(&s,&f);
		  break;
		case '/':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=e/d;
		  Push(&s,&f);
		  break;
		default:
		  d=atof(op); //������������Ϳ϶��������ˡ����ԣ���atof���������ַ���ת��Ϊdouble����
		  Push(&s,&d);
		  break;
		}      
    }
  Pop(&s,result);
  DestroyStack(&s);
  return TRUE;
}
 
/*
��ʼ��ջ
������stackSize:ջ����������С
typeSize:�Ժ�Ҫ��ջ�ĵ���Ԫ�صĴ�С
*/
Status InitStack(sqStack *s,unsigned stackSize,unsigned typeSize)
{
  s->base=malloc(stackSize);
  if(!s->base)
    return ERROR;
  s->top=s->base;
  s->stackSize=stackSize;
  s->typeSize=typeSize;
  return TRUE;
}
 
/*
ѹջ
*/
Status Push(sqStack *s,void *e)
{
  if((int)s->top-(int)s->base+s->typeSize>s->stackSize)
    return FALSE;
  memcpy(s->top,e,s->typeSize);
  s->top=(void*)((int)s->top+s->typeSize);
  return TRUE;
}
 
/*
��ջ
*/
Status Pop(sqStack *s,void *e)
{
  if(s->top==s->base)
    return FALSE;
  s->top=(void*)((int)s->top-(int)s->typeSize);
  memcpy(e,s->top,s->typeSize);
  return TRUE;
}
 
/*
��ջ
*/
Status ClearStack(sqStack *s)
{
  s->top=s->base;
  return TRUE;
}
 
/*
��ջ
*/
Status DestroyStack(sqStack *s)
{
  free(s->base);
  s->top=s->base=NULL;
  s->stackSize=s->typeSize=0;
  return TRUE;
}
 
/*
��ȡ����ջԪ�ظ���
*/
int GetLen(sqStack *s)
{
  return ((int)s->top-(int)s->base)/s->typeSize;
}
 
/*
�Զ����������
*/
void my_err(char *str)
{
  perror(str);
  exit(1);
}
