/*
 ============================================================================
 Name        : p2-2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>

void print1 (int *ptr,int rows);   //�迭�� �ּҿ� ��Ҹ� ������ִ� �Լ� ����

int main(void) {

	printf("����Ʈ�����а� 2018068005 ������\n");
	int one[] = {0,1,2,3,4};  //one�迭 ���� �� �ʱ�ȭ

	printf("one    = %p\n",one);  //one �迭�� �̸��� �����ּ� �̴�. >>0061FF0C
	printf("&one   = %p\n",&one);  //one �迭�� �ּ� >>0061FF0C
	printf("&one[0]= %p\n",&one[0]);  //one[0]�� �ּҴ� �迭�� �����ּҿ� �����ϴ�. >>0061FF0C
	//���� �������� ��� �迭�� �����ּҸ� ��Ÿ����.

	print1(&one[0],5);  //�Լ� ȣ�� (�迭�� �ּҿ� �ݺ�Ƚ���� �Ѱ��ش�.)

	return 0;
}
void print1 (int *ptr, int rows) // ��� �Լ� ���� (�迭�� ������ ���·� �Ͽ� �ּҸ� �Ѱܹ��� , rows�� �ݺ�Ƚ��)
{ //�迭�� ������ ���·� �Ѱܹ޾ұ� ������ ����Ҷ��� ������ó�� ����� �ش�.
	/*print out a one-dimensional array using a pointer*/

	int i;  //���� ����
	printf("Address \t Contents\n");  //�ȳ��� ���
	for (i=0;i<rows;i++)  //�ݺ�Ƚ����ŭ
		printf("%p \t %5d\n",ptr+i,*(ptr+i));  //ptr+i(�迭�� �ּ�)�� *(ptr+1)(�迭�� ��)�� ����Ѵ�.
	printf("\n");
}
