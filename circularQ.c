/*
 ============================================================================
 Name        : circularQ.c
 ============================================================================
 */

/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  //큐의 최대 사이즈는 4

typedef char element;  //문자열 자료형을 정의해준다.
typedef struct {
	element queue[MAX_QUEUE_SIZE];  //element 자료형이고 크기가 MAX_QUEUE_SIZE인 공백 큐  배열 생성
	int front, rear;  //큐의 front와 rear 변수 선언
}QueueType;  //구조체 타입 이름을 미리 정의


QueueType* createQueue();  //원형 큐를 생성하여 주소를 반환하는 함수
int isEmpty(QueueType* cQ);  //해당 큐가 비어있는지 확인 하는 함수
int isFull(QueueType* cQ);  //해당 큐가 가득 찼는지 확인하는 함수
void enQueue(QueueType* cQ, element item);  //큐에 원소를 삽입해주는 함수(rear를 이동)
void deQueue(QueueType* cQ, element* item);  //큐의 원소를 삭제하는 함수(front를 이동)
void printQ(QueueType* cQ);  //큐를 출력해주는 함수
void debugQ(QueueType* cQ);  //큐의 전체적인 내용을 확인해주는 함수
int freeQueue(QueueType* cQ); //동적메모리를 해제해주는 함수

element getElement();  //큐의 원소를 입력받아 반환해주는 함수


int main(void)
{
	QueueType* cQ = createQueue();  //공백 큐인 cQ를 선언하고 createQueue를 호출하여 바로 동적으로 메모리 할당해준다.
	element data;  //입력받은 원소를 넘겨받는 변수

	printf("전아현 2018068005\n");
	char command;  //선택할 메뉴

	do {
		printf("\n-----------------------------------------------------\n");  //안내문 출력
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");  //i = 큐삽입, d = 큐 원소 삭제, p = 큐 리스트 출력
		printf("------------------------------------------------------\n");  //b = 큐의 front, rear의 위치, 큐 원소들들의 위치를 출력

		printf("Command = ");  //안내문
		fflush(stdout);  //입력받을 때 버퍼를 비워둔다.
		scanf(" %c", &command);  //메뉴를 입력받는다.

		switch (command) {  //스위치 문을 이용하여
		case 'i': case 'I':  //Insert를 선택하면
			data = getElement();  //getElement 함수를 호출하여 데이터를 입력받은 뒤 data변수에 저장한다.
			enQueue(cQ, data);  //enQueue함수를 호출해 현재 큐가 가득찼는지 확인 한 후 결과에 따라 삽입하거나 안내문을 출력한다.
			break;  //스위치 문을 빠져나간다.
		case 'd': case 'D':  //Delete를 선택하면
			deQueue(cQ, &data);  //deQueue를 호출하여 현재 큐가 공백인지 확인 한 후 결과에 따라 front를 이동하거나 안내문을 출력한다.
			break;//스위치 문을 빠져나간다.
		case 'p': case 'P':  //Print를 선택하면
			printQ(cQ);  //printQ함수를 호출하여 큐에 들어있는 원소를 순서대로 출력한다.
			break;  //스위치 문을 빠져나간다.
		case 'b': case 'B':  //Dubug를 선택하면
			debugQ(cQ);  //debugQ 함수를 호출하여 큐의 front,rear의 위치, 큐 원소의 위치를 출력
			break;  //스위치 문을 빠져나간다.
		case 'q': case 'Q'://Quit를 선택하면
			if(freeQueue(cQ)==1);  //freeQueue 함수를 호출하여 동적으로 할당받은 메모리를 해제해준다. 해제를 성공하면
				printf("메모리 해제 성공\n"); //안내문 출력
			break;  //스위치 문을 빠져나간다.
		default:  //잘못 선택하였따면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //안내문 출력후
			break;  //스위치문을 빠져나간다.
		}

	} while (command != 'q' && command != 'Q');  //Quit를 선택하면 반복 종료
	printf("프로그램을 종료합니다.\n");  //안내문 출력후
	return 1;  //프로그램 종료

}


QueueType* createQueue()//동적으로 메모리를 생성해주는 함수 생성한 메모리의 주소를 반환
{
	QueueType* cQ;  //동적으로 할당받을 QueueType 구조체 타입 포인터 변수 선언
	cQ = (QueueType*)malloc(sizeof(QueueType));  //구조체 타입 포인터 변수에 QueueType인 동적메모리를 할당한다.
	cQ->front = 0;  //cQ구조제 멤버 변수 front를 0으로 초기화
	cQ->rear = 0;//cQ구조제 멤버 변수 rear를 0으로 초기화
	return cQ;  //cQ의 주소값을 리턴한다.
}

element getElement()  //큐의 원소를 입력받는 원소
{
	element item;  //입력받을 변수 선언
	printf("Input element = ");  //안내문 출력후
	fflush(stdout);  //버퍼를 비운 뒤
	scanf(" %c", &item);  //변수 입력
	return item;  //입력받은 원소를 반환해준다.
}


/* 원형 큐가 공백 상태인지 확인하는 함수
 * 비어있다면 안내문을 출력하고 0을 반환
 * 아니라면 1을 반환다.
 * */
int isEmpty(QueueType* cQ)
{
	if (cQ->front == cQ->rear)  //구조체의 멤버변수 front와 rear가 같다면 원형큐는 비어있다는 것을 의미한다.
	{
		printf("This queue is empty.\n");  //비어있다는 안내문 출력후
		return 0;  //함수를 종료한다.
	}
	return 1;  //아니면 1을 반환해준다.
}

/* 원형 큐가 가득찬 상태인지 확인하는 함수 */
int isFull(QueueType* cQ)
{
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
	/*원형 큐에서는 일반 큐와 달리  front가 가리키는 부분을 항상 비어있는 공간이다.
	 * 위의 식은 modulo연산으로 이렇게 하면 rear가 0- MAX_QUEUE_SIZE -1 을 가리킬 수 있다.
	 * rear가 현재 rear가 가리키는 곳의 다음 곳을 가리키도록 한 후*/
	if (cQ->front == cQ->rear)  //만약 front와 rear가 같다면 이는 현재 큐가 가득 찼다는 것이다.
	{
		printf("cQ is full.\n");  //큐가 가득 찼다는 안내문을 출력한 후
		if (cQ->rear == 0)  //만약 cQ가 가리키는 위치가 0이라면
			cQ->rear = MAX_QUEUE_SIZE - 1;  //rear가 원래 가리키는 곳을 가리키도록 하기 위해 배열의 제일 마지막 인덱스를 가리키도록 하고
		else  //아니라면
			cQ->rear -= 1; //지금 가리키는 곳보다 전의 rear를 가리키도록 한후
		return 0;  //함수를 종료한다.
	}
	return 1;  //가득 차지 않았다면 1을 반환한다.
}


/* 큐에 원소를 삽입해주는 함수 */
void enQueue(QueueType* cQ, element item)
{
	if (isFull(cQ) == 1)  //isFull 함수를 출력하여 해당 큐가 가득찼는지 확인 한 후 가득차지 않았다면
		/*isFull함수에서 큐가 가득차지 않았다면 cQ->rear는 그 다음 비어있는 공간을 가리키게 된다.*/
		cQ->queue[cQ->rear] = item;  //현재 구조체 멤버변수 rear가 가리키는 공간(isFull함수에서 변경해줌)에 이력받은 원소를 삽입해준다.
}

/* 큐에 원소를 삭제해주는 함수
 * 정확히 삭제라기 보다는 front가 가리키는 배열을 이동시켜준다. */
void deQueue(QueueType* cQ, element* item)  //큐는 먼저 들어온 것이 먼저 나가는 구조이다.
{
	if (isEmpty(cQ) == 1)  //ifEmpty함수를 이용하여 큐가 공백인지 확인한 후 공백이 아니라면
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //cQ->front가 가리키는 곳을 현재 위치에서 다음 위치로 변경해준다.
}


void printQ(QueueType* cQ)  //큐의 원소를 순서대로 출력해주는 함수
{
	int i, first, last;  //변수 선언

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;  //front는 아무 것도 없는 공간을 가리키므로 그 다음 원소를 가리키게 한다.
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;  //마지막은 rear의 다음 원소를 가리키도록 한다.

	printf("Circular Queue : [");  //안내문 출력

	i = first;  //i를 first로 입력해주고
	while (i != last) {  //i가 last와 같지 않으면 반복  // rear가 가리키는 곳 의 전까지 큐의 원소가 들어있다.
		printf("%3c", cQ->queue[i]);  //cQ->queue[i]는 큐의 첫번째 원소부터 큐의 마지막 원소까지 이다.//원소를 출력하고
		i = (i + 1) % MAX_QUEUE_SIZE;  //cQ->queue[i] 가 다음 원소를 가리킬 수 있도록 i를 변경해준다.

	}
	printf(" ]\n");  //안내문 출력후 종료
}


void debugQ(QueueType* cQ)  //큐의 front,rear의 위치, 큐 원소의 위치를 출력해주는 함수
{

	printf("\n---DEBUG\n");  //안내문 출력
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)  //MAX_QUEUE_SIZE동안 반복
	{
		if (i == cQ->front) {  //만약 i가 cQ->front와동일하다면 (front가 가리키는 공간은 빈 공간)
			printf("  [%d] = front\n", i);  //front 임을 알리고
			continue;  //반복문의 처음으로 돌아간다.
		}//아니라면
		printf("  [%d] = %c\n", i, cQ->queue[i]);  //Queue의 원소를 출력한다.
		//deQueue는 원소를 삭제하는 것이 아니라 front의 위치만 변경해주는 것이기 때문에 입력후 삭제한 원소들이 그대로 남이 있는다.

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  //front와 rear의 위치를 출력한다.
}

int freeQueue(QueueType* cQ)  //동적으로 할당받은 메모리를 해제해준다.
{
	if (cQ == NULL) {  //동적메모리를 할당받지 않았다면
		printf("동적으로 메모리를 할당받지 않음\n");  //안내문 출력 후
		return 0;//프로그램 종료
	}
	free(cQ);  //아니라면 동적메모리를 해제해 준 후
	return 1;  //1을 반환해준다.
}
