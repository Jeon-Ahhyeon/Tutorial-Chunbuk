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

struct student {  //student 구조체 타입 지정
	char lastName[13];  //문자형은 1칸당 1바이트를 차지 13bytes
	int studentId;       //int 형의 크기는 4bytes
	short grade;         //short형의 크기는 2bytes
};

int main(void) {

	printf("소프트웨어학과 2018068005 전아현\n");
	struct student pst;  //student구조체 타입 변수 pst선언

	/*
	 * CPU에서 메모리 접근성을 높이기 위해 구조체를 일정한 크기로 정렬을 하는데 멤버변수중 가장 큰 자료형의 크기의 배수로 정렬하여 남을 공간을 채우는 것을 패딩이라고 한다.
	 * 여기서 멤버 변수중 가장 큰 자료형의 크기는 int이므로 4의 배수로 정렬한다.
	 */
	printf("size of student = %ld\n",sizeof(struct student));  //struct은 typedef이 없으니까 무조건 찍어주야아한다.
	/* 원래 19바이트라고 생각할 수 있으나 패딩기능을 사용하기 때문에
	 * lastName[13] 의 크기는 13bytes 사용 후 남은 3bytes를 채워주어 16byte
	 * studentId는 4bytes그대로
	 * grade는 2bytes 사용 후 남은 2bytes를 채워주어 4bytes로
	 * 구조체의 총 크기는 24가 된다.
	 * */
	printf("size of int - %ld\n",sizeof(int));  //int형의 데이터 타입의 크기는 4bytes
	printf("size of short = %ld\n",sizeof(short));  //short형의 데이터 타입의 크기는 2bytes

	return 0;
}
