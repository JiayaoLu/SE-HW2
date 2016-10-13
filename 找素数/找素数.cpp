// ������1.cpp : Defines the entry point for the console application.
//

//***���ڸ��˵��ԱȽϴ죬���Կ�����ֻ�ܿ���10�ڸ�bool������ֻ�����˵�1�ڸ�����

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

typedef struct
{
	//num==0��ʾ������1��ʾ����
	bool num_neg = 0;//��ʾ6N-1
	bool num_pos = 0;//��ʾ6N+1
}IsNotPrime;

const long LENGTH = 339679124;
				  //2038074743 = 339679124 * 6 - 1;
const long SQUART_LENGTH = 7525;
				  //sqrt(2038074743) = 45146 < 7525*6 - 1;
int main()
{
	IsNotPrime *p, *head, *tail;
	IsNotPrime *p_current;//ָ��ǰѭ������ɸ����
	long i, count = 100000001;//count���ڼ�������¼�ڼ�����������Ϊ�ǵ������ģ�Ŀ���Ǵ��������Ե��������죩�����Դ�100000001��ʼ��
	long order;//��������

	scanf_s("%ld", &order);
	if (order > 100000000 || order <= 0)
	{
		printf("error input!\n");
		return 1;
	}

	if (order <= 2) //��Ϊ2��3�Ѿ���ɸ���ˣ�����Ҫ��������һ��
	{
		printf("%d\n", order==2?3:2);
		return 0;
	}

	p = (IsNotPrime*)malloc(sizeof(IsNotPrime)*LENGTH);//�����е�n���ṹ�����6N-1��6N+1������
	if (p == 0)
	{
		printf("no enough memory!\n");
		return 1;
	}
	//printf("success\n");//������
	//printf("p=%d\n", p);//������

	head = p;
	tail = head + LENGTH;//tailָ�����һ��������һ��λ��
	//printf("%d %d\n",head->num_neg,head->num_pos);//������
	//for (i = 0; i < LENGTH; i++) *(p++) = 0;//����
	
	p_current = head;
	for (i = 0; i<SQUART_LENGTH; i++)
	{
		p = p_current;
		if (p->num_neg == 0)
		{
			long pace = 6 * i + 5;//pace��ʾÿ��p�����Ľṹ����,pace = (i + 1) * 6 - 1
			p += pace;
			while (p < tail)
			{
				p->num_neg = 1;
				p += pace;
			}
			p = p_current + 4 * i + 3;//p = p_current + pace - 2*(i+1);
			while (p < tail)
			{
				p->num_pos = 1;
				p += pace;
			}
		}
		p = p_current;
		if (p->num_pos == 0)
		{
			long pace = 6 * i + 7;//pace = (i + 1) * 6 + 1;
			p += pace;
			while (p < tail)
			{
				p->num_pos = 1;
				p += pace;
			}
			p = p_current + 4 * i + 5;//p = p_current + pace - 2 * (i + 1);
			while (p < tail)
			{
				p->num_neg = 1;
				p += pace;
			}
		}
		p_current++;
	}

	//printf("finish!!!\n");//������

	p = tail - 1;
	for (i=LENGTH; i>0; i--)
	{
		if (p->num_pos == 0)
		{
			count--;
			if (count == order)
			{
				printf("%d\n", 6*i+1);
				break;
			}
		}
		if (p->num_neg == 0)
		{
			count--;
			if (count == order)
			{
				printf("%d\n", 6 * i - 1);
				break;
			}
		}
		p--;
	}

	free(head);
	return 0;
}