#include <iostream>
using namespace std;

//�ݹ�ʵ����һ�����ϵ�ȫ���Ӽ�
//˼·�����ַ����е������ַ���״̬����0��1.
//template <class T>
void subset(int *p,int n,int len){

    //�������
    if (n==0){

        int j = 0;
        cout<<"{";
        for (int i = 0; i < len; ++i) {//��len������ȫ������ַ�
            if (j!=0&&p[i]!=0){
                cout<<",";//���ƣ������
            }
            if (p[i]!=0){
                cout<<p[i];
                j++;
            }
        }

        cout<<"}"<<endl;
        return;
    }

    for (int j = 0; j <=1; ++j) {//ÿ��Ԫ�ض���0��1����״̬

        int *ch = new int[len];

        for (int i = 0; i < len; ++i) {
            ch[i] = p[i];//������ʱ����������p������ֵ,ȷ���������Ԫ�صĳ�ʼֵ
        }

        if (j==0){
            ch[n-1] = 0;//0��ʾԪ�ز��ڸ��Ӽ���
        }

        subset(ch,n-1,len);//�ж�ʣ�µ�n-1���ַ��Ƿ����Ӽ���

    }
    

}

