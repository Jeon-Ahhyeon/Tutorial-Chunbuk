/*
 ============================================================================
 Name        : ap1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : ap1.c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int list[5];     //��Ұ� 5���� �迭
	int *plist[5] = {NULL,};  //  int�� �����͸� ��� �ִ� �迭�� null�� �ʱ�ȭ

	plist[0] = (int*)malloc(sizeof(int)); //plist[0]�� int���� ������ �޸𸮸� �������� �Ҵ��� �ּҸ� �Ѱ���

	list[0]=1;   //list[0]�� 1����
	list[1]=100; //list[1]�� 100 ����

	*plist[0]=200;  //plist[0]�� ���� �ִ� �ּҿ� 200�� ����

	printf("����Ʈ�����а� 2018068005 ������\n");

	printf("value of list[0] = %d\n",list[0]);  //list[0]�� ���� ���  >>1
	printf("address of list[0]       = %p\n",&list[0]);  //list[0]�� �ּ� ��� >>0061FF0C
	printf("value of list            = %p\n",list);  //list�迭�� �̸��� ������ �ִ� ���� �迭�� �ּ� �̴�. >>0061FF0C
	printf("address of list (&list)  = %p\n",&list);  //list �迭�� �ּҸ� ����Ѵ�. >>0061FF0C
	/*&list[0], list, &list�� ������ �ִ� ���� ���� list�迭�� �ּҷ� �����ϴ�.*/

	printf("-------------------------------------\n\n");   //list[1]�� ���� �ּ�
	printf("value of list[1]   = %d\n",list[1]);  //list[1]�� �� ��� >>100
	printf("address of list[1] = %p\n",&list[1]);  //list[1]�� �ּ� ��� (list[0]�� �ּҰ��� int�� �������̹Ƿ� 4�� ���� ���̴�.) >>0061FF10
	printf("value of *(list+1) = %d\n",*(list +1));  //(list+1)�� ���� ���� ����Ѵ�. (list�� ���� �ּҿ� 4�� ���� ���� ����Ű�� ���̴�..) >100
	printf("address of list +1 = %p\n",list +1);  // list +1 �� �ּҰ��� ����Ѵ� (list�� �����ּҿ� 4�� ���� �ּҰ��̴�.)>>0061FF10
	//list[1]�� (list+1)�� ��Ű���� ���̴�. int�� �迭�̱� ������ ù��° �ּҿ� 4����Ʈ ��ŭ �̵��� �ּҰ��� list +1�� &list[1]�� ������ �ִ�.

	printf("-------------------------------------\n\n");  //*plist�� ���� �ּ� �˾ƺ���
	printf("value of *plist[0] = %d\n",*plist[0]); //plist[0]�� ����Ű�� �� >>200
	printf("&plist[0]          = %p\n",&plist[0]);  //plist[0]�� �ּ� >> 0061FEF8
	printf("&plist             = %p\n",&plist);    //plist�� �����ּ� >> 0061FEF8
	printf("plist              = %p\n",plist);  //plist�� �̸��� ������ �ִ� ���� ������ �迭�� �ּ� �̴�. >>0061FEF8
	/*plist,&plist,&plist[0]�� ���� ������ �迭�� �����ּҸ� ����Ų��.
	 * plist�� ������ �迭�̹Ƿ� ���� ������ �ִ� ���� �ƴ϶� ���� ������ �ִ� ���� �ּҸ� ������ �ִ� �迭�̴�.
	 * �׷��� plist[0] �� plist�� ���� ���� �ʴ�.*/
	printf("plist[0]           = %p\n",plist[0]);  //plist[0]�� ������ �ִ� �ּ� (int�� ������ �迭�̱� ������ �� �ּҴ� int�� �ڷᰡ ����ִ� ���� �ּҸ� ����Ų��.) >>007B1FA0
	printf("plist[1]           = %p\n",plist[1]);  //plist[1]�� ������ �ִ� �ּҴ� ������ null�� �ʱ�ȭ �Ͽ��� ������ �ؿ��� �� 00000000���� ��µȴ�.
	printf("plist[2]           = %p\n",plist[2]);
	printf("plist[3]           = %p\n",plist[3]);
	printf("plist[4]           = %p\n",plist[4]);

	free(plist[0]);  //�������� �Ҵ����־�� �迭�� �� ������ �� �־���� �޸� ���� ���� �� �ִ�.


}
