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

void main() {  //ap1.c와 유사  list의 주소를 자세히 보는 코드
	int list[5];   //list[5]배열 선언
	int *plist[5];  //*plist[5] 포인터 배열 선언

	list[0]=10;  //list[0]에 10을 대입
	list[1]=11;   //list [1]에 11 대입

	plist[0] = (int*)malloc(sizeof(int));   //포인터 배열 plist[0]에 int형 사이즈의 메모리를 동적으로 할당해준다.

	printf("소프트웨어학과 2018068005 전아현\n");

	printf("list[0] \t=%d\n\n",list[0]);   //list[0]의 값을 출력  >>10
	printf("address of list \t = %p\n",list);  //list배열의 이름은 배열을 시작주소를 가지고 있다. >>0061FF0C
	printf("address of list[0] \t = %p\n",&list[0]);  //list[0]의 주소는 배열의 시작주소와 동일하다 >>0061FF0C
	printf("address of list + 0 \t = %p\n",list+0);    //list +0의 주소를 출력  int형 사이즈 포인터 배열이므로 4씩 증가하지만 0을 더했으므로 배열의 주소값과 동일 >>0061FF0C
	printf("address of list + 1 \t = %p\n",list+1);  //list +1 은 배열의 시작주소에  int 형 사이즈 4를 한번 더해준 값으로 list[1]의 주소값과 동일하다.>>0061FF10
	printf("address of list + 2 \t = %p\n",list+2);  //list +2 은 배열의 시작주소에  int 형 사이즈 4를 두번 더해준 값으로 list[2]의 주소값과 동일하다.>>0061FF14
	printf("address of list + 3 \t = %p\n",list+3);//list +3 은 배열의 시작주소에  int 형 사이즈 4를 세번 더해준 값으로 list[3]의 주소값과 동일하다.>>0061FF18
	printf("address of list + 4 \t = %p\n",list+4);//list +4 은 배열의 시작주소에  int 형 사이즈 4를 네번 더해준 값으로 list[4]의 주소값과 동일하다.>>0061FF1C
	printf("address of list[4] \t = %p\n",&list[4]);  //list[4]의 데이터가 들어있는 곳의 주소 출력 >>0061FF1C   /*위의 list + 4와 동일하다.


	free(plist[0]);//동적으로 할당해준 메모리를 해제해누어 메모리의 효율성을 높인다.
}
