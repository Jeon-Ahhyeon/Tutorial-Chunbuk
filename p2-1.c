/*
 ============================================================================
 Name        : p2-1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

#define MAX_SIZE 100//��ũ�� ����

float sum(float [],int);  //
float input[MAX_SIZE],answer;  //float�� �迭�� ������ �������� ��������
int i;  //��������

void main() {

	printf("����Ʈ�����а� 2018068005 ������\n");

	for(i=0;i<MAX_SIZE;i++)   //MAX_SIZE�� ����
		input[i]=i;  //input[i]�� ���� i��ŭ�� ���� ��Ų��.
	//for checking call by reference
	 printf("address of input = %p\n",input);   //input�迭�� �ּ� ��� >>


	answer=sum(input,MAX_SIZE);
	printf("The sum is : %f\n",answer);

}

float sum(float list[],int n)  //�迭 ��ü�� �ƴ� �ּҰ��� �Ѿ
{

	 printf("value of list = %p\n",list);  //input�� �ּ�
	 printf("address of list = %p\n\n",&list);//


	int i;
	float tempsum =0;
	for(i=0;i<n;i++)
		tempsum += list[i];
	return tempsum;
}
