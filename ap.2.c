/*
 ============================================================================
 Name        : ap2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void main() {  //ap1.c�� ����  list�� �ּҸ� �ڼ��� ���� �ڵ�
	int list[5];   //list[5]�迭 ����
	int *plist[5];  //*plist[5] ������ �迭 ����

	list[0]=10;  //list[0]�� 10�� ����
	list[1]=11;   //list [1]�� 11 ����

	plist[0] = (int*)malloc(sizeof(int));   //������ �迭 plist[0]�� int�� �������� �޸𸮸� �������� �Ҵ����ش�.

	printf("����Ʈ�����а� 2018068005 ������\n");

	printf("list[0] \t=%d\n\n",list[0]);   //list[0]�� ���� ���  >>10
	printf("address of list \t = %p\n",list);  //list�迭�� �̸��� �迭�� �����ּҸ� ������ �ִ�. >>0061FF0C
	printf("address of list[0] \t = %p\n",&list[0]);  //list[0]�� �ּҴ� �迭�� �����ּҿ� �����ϴ� >>0061FF0C
	printf("address of list + 0 \t = %p\n",list+0);    //list +0�� �ּҸ� ���  int�� ������ ������ �迭�̹Ƿ� 4�� ���������� 0�� �������Ƿ� �迭�� �ּҰ��� ���� >>0061FF0C
	printf("address of list + 1 \t = %p\n",list+1);  //list +1 �� �迭�� �����ּҿ�  int �� ������ 4�� �ѹ� ������ ������ list[1]�� �ּҰ��� �����ϴ�.>>0061FF10
	printf("address of list + 2 \t = %p\n",list+2);  //list +2 �� �迭�� �����ּҿ�  int �� ������ 4�� �ι� ������ ������ list[2]�� �ּҰ��� �����ϴ�.>>0061FF14
	printf("address of list + 3 \t = %p\n",list+3);//list +3 �� �迭�� �����ּҿ�  int �� ������ 4�� ���� ������ ������ list[3]�� �ּҰ��� �����ϴ�.>>0061FF18
	printf("address of list + 4 \t = %p\n",list+4);//list +4 �� �迭�� �����ּҿ�  int �� ������ 4�� �׹� ������ ������ list[4]�� �ּҰ��� �����ϴ�.>>0061FF1C
	printf("address of list[4] \t = %p\n",&list[4]);  //list[4]�� �����Ͱ� ����ִ� ���� �ּ� ��� >>0061FF1C   /*���� list + 4�� �����ϴ�.


	free(plist[0]);//�������� �Ҵ����� �޸𸮸� �����ش��� �޸��� ȿ������ ���δ�.
}
