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
	int **x;  //int형 이중 포인터 선언

	printf("소프트웨어학과 2018068005 전아현\n");

	printf("sizeof(x)  = %lu\n",sizeof(x));  //x의 크기  =>주소 저장 4바이트 (이클립스 다운받을 때  32비트용으로 다운받아서 주소는 4비트이다)
	printf("sizeof(*x) = %lu\n",sizeof(*x));  //포인터 x의 크기  => 주소저장 4바이트
	printf("sizeof(**x)= %lu\n",sizeof(**x)); //이중 포인터 x의 크기 => 두번 참조해서 실제 데이터 값 저장 int형 크기 4
}
