/*
 ============================================================================
 Name        : p2-1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

#define MAX_SIZE 100//매크로 정의

float sum(float [],int);  //
float input[MAX_SIZE],answer;  //float형 배열과 변수를 전역으로 선언해줌
int i;  //전역변수

void main() {

	printf("소프트웨어학과 2018068005 전아현\n");

	for(i=0;i<MAX_SIZE;i++)   //MAX_SIZE번 동안
		input[i]=i;  //input[i]의 값을 i만큼을 증가 시킨다.
	//for checking call by reference
	 printf("address of input = %p\n",input);   //input배열의 주소 출력 >>


	answer=sum(input,MAX_SIZE);
	printf("The sum is : %f\n",answer);

}

float sum(float list[],int n)  //배열 전체가 아닌 주소값만 넘어감
{

	 printf("value of list = %p\n",list);  //input의 주소
	 printf("address of list = %p\n\n",&list);//


	int i;
	float tempsum =0;
	for(i=0;i<n;i++)
		tempsum += list[i];
	return tempsum;
}
