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

void print1 (int *ptr,int rows);   //배열의 주소와 요소를 출력해주는 함수 선언

int main(void) {

	printf("소프트웨어학과 2018068005 전아현\n");
	int one[] = {0,1,2,3,4};  //one배열 선언 및 초기화

	printf("one    = %p\n",one);  //one 배열의 이름은 시작주소 이다. >>0061FF0C
	printf("&one   = %p\n",&one);  //one 배열의 주소 >>0061FF0C
	printf("&one[0]= %p\n",&one[0]);  //one[0]의 주소는 배열의 시작주소와 동일하다. >>0061FF0C
	//위의 세가지는 모두 배열의 시작주소를 나타낸다.

	print1(&one[0],5);  //함수 호출 (배열의 주소와 반복횟수를 넘겨준다.)

	return 0;
}
void print1 (int *ptr, int rows) // 출력 함수 구현 (배열을 포인터 형태로 하여 주소를 넘겨받음 , rows는 반복횟수)
{ //배열의 포인터 형태로 넘겨받았기 때문에 사용할때도 포인터처럼 사용해 준다.
	/*print out a one-dimensional array using a pointer*/

	int i;  //변수 선언
	printf("Address \t Contents\n");  //안내문 출력
	for (i=0;i<rows;i++)  //반복횟수만큼
		printf("%p \t %5d\n",ptr+i,*(ptr+i));  //ptr+i(배열의 주소)와 *(ptr+1)(배열의 값)을 출력한다.
	printf("\n");
}
