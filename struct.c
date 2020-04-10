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

struct student1{   //student1 구조체 타입  >>main함수에서 타입을 반드시 지정해주어야 한다.
	char lastName;
	int studentId;
	char grade;
};

typedef struct{  //typedef 으로 정의한 student 구조체   >>typedef로 정의해 주었으므로 main함수에서 타입을 따로 지정하지 않아도 된다.
	char lastName;
	int studentId;
	char grade;
} student2;

int main(void) {
	struct student1 st1 = {'A',100,'A'};   //student1구조체 변수 st1선언 및 초기화 >>typedef이 되어있지 않아 struct를 빼버리면 자료형이 정해지지 않았다는 오류 발생

	printf("소프트웨어학과 2018068005 전아현\n");

	printf("st1.lastName = %c\n",st1.lastName);  //st1 구조체 타입의 내용을 각각 출력
	printf("st1.studentId = %d\n",st1.studentId);
	printf("st1.grade = %c\n",st1.grade);

	student2 st2 = {'B',200,'B'};  //typedef이 되어있어 struct가 없어도 오류 발생하지 않음

	printf("\nst2.lastName = %c\n",st2.lastName);
	printf("st2.studentId = %d\n",st2.studentId);
	printf("st2.grade = %c\n",st2.grade);

	student2 st3;

	st3=st2;  //구조치환을 해주기 위함  예전에는 불가능했으나 요즘은 가능

	printf("\nst3.lastName = %c\n",st3.lastName);  //st2과 동일
	printf("st3.studentId = %d\n",st3.studentId);
	printf("st3.grade = %c\n",st3.grade);

	/*equalty test*/   //전체 구조의 동등성 검사

	/* if(st3==st2)  //치환은 가능하나 한번에 비교는 불가능해서 오류 발생
	 printf("equal\n");
	 else
	 printf("not equal\n");
	 */

	return 0;
}
