/*
 ============================================================================
 Name        : padding.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct student {  //student ����ü Ÿ�� ����
	char lastName[13];  //�������� 1ĭ�� 1����Ʈ�� ���� 13bytes
	int studentId;       //int ���� ũ��� 4bytes
	short grade;         //short���� ũ��� 2bytes
};

int main(void) {

	printf("����Ʈ�����а� 2018068005 ������\n");
	struct student pst;  //student����ü Ÿ�� ���� pst����

	/*
	 * CPU���� �޸� ���ټ��� ���̱� ���� ����ü�� ������ ũ��� ������ �ϴµ� ��������� ���� ū �ڷ����� ũ���� ����� �����Ͽ� ���� ������ ä��� ���� �е��̶�� �Ѵ�.
	 * ���⼭ ��� ������ ���� ū �ڷ����� ũ��� int�̹Ƿ� 4�� ����� �����Ѵ�.
	 */
	printf("size of student = %ld\n",sizeof(struct student));  //struct�� typedef�� �����ϱ� ������ ����־߾��Ѵ�.
	/* ���� 19����Ʈ��� ������ �� ������ �е������ ����ϱ� ������
	 * lastName[13] �� ũ��� 13bytes ��� �� ���� 3bytes�� ä���־� 16byte
	 * studentId�� 4bytes�״��
	 * grade�� 2bytes ��� �� ���� 2bytes�� ä���־� 4bytes��
	 * ����ü�� �� ũ��� 24�� �ȴ�.
	 * */
	printf("size of int - %ld\n",sizeof(int));  //int���� ������ Ÿ���� ũ��� 4bytes
	printf("size of short = %ld\n",sizeof(short));  //short���� ������ Ÿ���� ũ��� 2bytes

	return 0;
}
