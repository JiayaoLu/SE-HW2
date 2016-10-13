// 找素数1.cpp : Defines the entry point for the console application.
//

//***由于个人电脑比较挫，所以开数组只能开到10亿个bool，所以只做到了第1亿个素数

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

typedef struct
{
	//num==0表示素数，1表示合数
	bool num_neg = 0;//表示6N-1
	bool num_pos = 0;//表示6N+1
}IsNotPrime;

const long LENGTH = 339679124;
				  //2038074743 = 339679124 * 6 - 1;
const long SQUART_LENGTH = 7525;
				  //sqrt(2038074743) = 45146 < 7525*6 - 1;
int main()
{
	IsNotPrime *p, *head, *tail;
	IsNotPrime *p_current;//指向当前循环正在筛的数
	long i, count = 100000001;//count用于计数，记录第几个素数，因为是倒着数的（目标是大数，所以倒着数更快），所以从100000001开始算
	long order;//读数进来

	scanf_s("%ld", &order);
	if (order > 100000000 || order <= 0)
	{
		printf("error input!\n");
		return 1;
	}

	if (order <= 2) //因为2和3已经被筛掉了，所以要单独处理一下
	{
		printf("%d\n", order==2?3:2);
		return 0;
	}

	p = (IsNotPrime*)malloc(sizeof(IsNotPrime)*LENGTH);//数组中第n个结构体包含6N-1和6N+1两个数
	if (p == 0)
	{
		printf("no enough memory!\n");
		return 1;
	}
	//printf("success\n");//测试用
	//printf("p=%d\n", p);//测试用

	head = p;
	tail = head + LENGTH;//tail指向最后一个结点的下一个位置
	//printf("%d %d\n",head->num_neg,head->num_pos);//测试用
	//for (i = 0; i < LENGTH; i++) *(p++) = 0;//置零
	
	p_current = head;
	for (i = 0; i<SQUART_LENGTH; i++)
	{
		p = p_current;
		if (p->num_neg == 0)
		{
			long pace = 6 * i + 5;//pace表示每次p跳过的结构体数,pace = (i + 1) * 6 - 1
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

	//printf("finish!!!\n");//测试用

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