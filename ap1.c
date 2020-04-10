#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int list[5];     //요소가 5개인 배열
	int *plist[5] = {NULL,};  //  int형 포인터를 담고 있는 배열로 null로 초기화

	plist[0] = (int*)malloc(sizeof(int)); //plist[0]에 int형의 사이즈 메모리를 동적으로 할당해 주소를 넘겨줌

	list[0]=1;   //list[0]에 1대입
	list[1]=100; //list[1]에 100 대입

	*plist[0]=200;  //plist[0]이 갖고 있는 주소에 200을 대입

	printf("소프트웨어학과 2018068005 전아현\n");

	printf("value of list[0] = %d\n",list[0]);  //list[0]의 값을 출력  >>1
	printf("address of list[0]       = %p\n",&list[0]);  //list[0]의 주소 출력 >>0061FF0C
	printf("value of list            = %p\n",list);  //list배열의 이름이 가지고 있는 값은 배열의 주소 이다. >>0061FF0C
	printf("address of list (&list)  = %p\n",&list);  //list 배열의 주소를 출력한다. >>0061FF0C
	/*&list[0], list, &list가 가지고 있는 값은 전부 list배열의 주소로 동일하다.*/

	printf("-------------------------------------\n\n");   //list[1]의 값과 주소
	printf("value of list[1]   = %d\n",list[1]);  //list[1]의 값 출력 >>100
	printf("address of list[1] = %p\n",&list[1]);  //list[1]의 주소 출력 (list[0]의 주소값에 int형 데이터이므로 4를 더한 값이다.) >>0061FF10
	printf("value of *(list+1) = %d\n",*(list +1));  //(list+1)에 대한 값을 출력한다. (list의 시작 주소에 4를 더한 값이 가리키는 값이다..) >100
	printf("address of list +1 = %p\n",list +1);  // list +1 의 주소값을 출력한다 (list의 시작주소에 4를 더한 주소값이다.)>>0061FF10
	//list[1]은 (list+1)이 가키리는 값이다. int형 배열이기 때문에 첫번째 주소에 4바이트 만큼 이동한 주소값을 list +1과 &list[1]이 가지고 있다.

	printf("-------------------------------------\n\n");  //*plist의 값과 주소 알아보기
	printf("value of *plist[0] = %d\n",*plist[0]); //plist[0]이 가리키는 값 >>200
	printf("&plist[0]          = %p\n",&plist[0]);  //plist[0]의 주소 >> 0061FEF8
	printf("&plist             = %p\n",&plist);    //plist의 시작주소 >> 0061FEF8
	printf("plist              = %p\n",plist);  //plist의 이름이 가지고 있는 값은 포인터 배열의 주소 이다. >>0061FEF8
	/*plist,&plist,&plist[0]은 전부 포인터 배열의 시작주소를 가리킨다.
	 * plist는 포인터 배열이므로 값을 가지고 있는 것이 아니라 값을 가지고 있는 곳의 주소를 가지고 있는 배열이다.
	 * 그래서 plist[0] 과 plist의 값은 같지 않다.*/
	printf("plist[0]           = %p\n",plist[0]);  //plist[0]이 가지고 있는 주소 (int형 포인터 배열이기 때문에 이 주소는 int형 자료가 들어있는 곳의 주소를 가리킨다.) >>007B1FA0
	printf("plist[1]           = %p\n",plist[1]);  //plist[1]이 가지고 있는 주소는 위에서 null로 초기화 하였기 때문에 밑에도 쭉 00000000값만 출력된다.
	printf("plist[2]           = %p\n",plist[2]);
	printf("plist[3]           = %p\n",plist[3]);
	printf("plist[4]           = %p\n",plist[4]);

	free(plist[0]);  //동적으로 할당해주어던 배열은 꼭 해제를 해 주어야지 메모리 낭비를 줄일 수 있다.


}
