#include<stdio.h>
#include<math.h>

void inc(int b[],int n)  //��b��ʾ�Ķ���������1
{
  int i;
  for(i=0;i<n;i++)   //��������b
  {   if(b[i])           //��Ԫ��1��Ϊ0
         b[i]=0;
       else              //��Ԫ��0��Ϊ1���˳�forѭ��
      {  b[i]=1;
          break;
      }
  }
}

void PSet(int a[],int b[],int n)  //���ݼ� 
{ int i,j;
  int pw=(int)pow(2,n);           //��2^n
  printf("1~%d���ݼ���\n",n);
  
  for(i=0;i<pw;i++)               //ִ��2^n�� 
  {
  	printf(" { ");
  	int k;
  	for(k=0;k<n;k++)          //ִ��n�� 
  	if(b[k])
  	printf("%d",a[k]);
  	printf(" } ");
  	inc(b,n);                     //b��ʾ�Ķ���������1 
  }
  printf("\n");
}

int main(){
	int n=3,i;
	int a[10],b[10];
	for(i=0;i<n;i++)
	{
		a[i]=i+1;
		b[i]=0;
	 } 
	 PSet(a,b,n);
} 

