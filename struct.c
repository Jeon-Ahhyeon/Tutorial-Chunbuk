/*
 ============================================================================
 Name        : struct.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct student1{   //student1 ����ü Ÿ��  >>main�Լ����� Ÿ���� �ݵ�� �������־�� �Ѵ�.
	char lastName;
	int studentId;
	char grade;
};

typedef struct{  //typedef ���� ������ student ����ü   >>typedef�� ������ �־����Ƿ� main�Լ����� Ÿ���� ���� �������� �ʾƵ� �ȴ�.
	char lastName;
	int studentId;
	char grade;
} student2;

int main(void) {
	struct student1 st1 = {'A',100,'A'};   //student1����ü ���� st1���� �� �ʱ�ȭ >>typedef�� �Ǿ����� �ʾ� struct�� �������� �ڷ����� �������� �ʾҴٴ� ���� �߻�

	printf("����Ʈ�����а� 2018068005 ������\n");

	printf("st1.lastName = %c\n",st1.lastName);  //st1 ����ü Ÿ���� ������ ���� ���
	printf("st1.studentId = %d\n",st1.studentId);
	printf("st1.grade = %c\n",st1.grade);

	student2 st2 = {'B',200,'B'};  //typedef�� �Ǿ��־� struct�� ��� ���� �߻����� ����

	printf("\nst2.lastName = %c\n",st2.lastName);
	printf("st2.studentId = %d\n",st2.studentId);
	printf("st2.grade = %c\n",st2.grade);

	student2 st3;

	st3=st2;  //����ġȯ�� ���ֱ� ����  �������� �Ұ��������� ������ ����

	printf("\nst3.lastName = %c\n",st3.lastName);  //st2�� ����
	printf("st3.studentId = %d\n",st3.studentId);
	printf("st3.grade = %c\n",st3.grade);

	/*equalty test*/   //��ü ������ ��� �˻�

	/* if(st3==st2)  //ġȯ�� �����ϳ� �ѹ��� �񱳴� �Ұ����ؼ� ���� �߻�
	 printf("equal\n");
	 else
	 printf("not equal\n");
	 */

	return 0;
}
