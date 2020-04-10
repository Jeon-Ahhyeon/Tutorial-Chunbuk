#include <stdio.h>

#define MAX_SIZE 100//매크로 정의

float sum(float [],int);  //input배열에 있는 모든 수를 더해주는 함수 선언
float input[MAX_SIZE],answer;  //float형 배열과 변수를 전역으로 선언해줌
int i;  //전역변수

void main() {

	printf("소프트웨어학과 2018068005 전아현\n");

	for(i=0;i<MAX_SIZE;i++)   //MAX_SIZE번 동안
		input[i]=i;  //input[i]의 값을 i만큼을 증가 시킨다.
	//for checking call by reference
	 printf("address of input = %p\n",input);   //input배열의 주소 출력 >>004070A0


	answer=sum(input,MAX_SIZE); //전연변수인 answer에 함수 sum을 호출하여 sum의 리턴값 대입
	printf("The sum is : %f\n",answer);  //총 합계를 출력 >> 4950.000000

}

float sum(float list[],int n)  //input 배열의 모든 수를 더해주는 함수 구현  (배열 전체가 아닌 주소값만 넘어감) input의 주소값을 list가 받음 ,n을 반복 횟수
{

	 printf("value of list = %p\n",list);  //list가 가지고 있는 값은 list의 시작주소 값이 아니라 넘겨받은 input의 주소값이다. >>004070A0
	 printf("address of list = %p\n\n",&list);//  //list의 시작주소값 출력 >>0061FF00


	int i;  //변수 선언
	float tempsum =0;  //list의 값을 다 더해주기 위해 변수를 선언하고 초기화해줌
	for(i=0;i<n;i++)  //n번만큼 반복해서
		tempsum += list[i];  //tempsum에 list[i]의 값을 더해준다.
	return tempsum;  //tempsum (list를 다 더한값)을 리턴해준다.
} 
