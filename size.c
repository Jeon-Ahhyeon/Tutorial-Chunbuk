/*
 ============================================================================
 Name        : size.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void main() {
	int **x;  //int�� ���� ������ ����

	printf("����Ʈ�����а� 2018068005 ������\n");

	printf("sizeof(x)  = %lu\n",sizeof(x));  //x�� ũ��  =>�ּ� ���� 4����Ʈ (��Ŭ���� �ٿ���� ��  32��Ʈ������ �ٿ�޾Ƽ� �ּҴ� 4��Ʈ�̴�)
	printf("sizeof(*x) = %lu\n",sizeof(*x));  //������ x�� ũ��  => �ּ����� 4����Ʈ
	printf("sizeof(**x)= %lu\n",sizeof(**x)); //���� ������ x�� ũ�� => �ι� �����ؼ� ���� ������ �� ���� int�� ũ�� 4
}
