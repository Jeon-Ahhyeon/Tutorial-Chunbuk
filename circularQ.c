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

#define MAX_QUEUE_SIZE 4  //ť�� �ִ� ������� 4

typedef char element;  //���ڿ� �ڷ����� �������ش�.
typedef struct {
	element queue[MAX_QUEUE_SIZE];  //element �ڷ����̰� ũ�Ⱑ MAX_QUEUE_SIZE�� ���� ť  �迭 ����
	int front, rear;  //ť�� front�� rear ���� ����
}QueueType;  //����ü Ÿ�� �̸��� �̸� ����


QueueType* createQueue();  //���� ť�� �����Ͽ� �ּҸ� ��ȯ�ϴ� �Լ�
int isEmpty(QueueType* cQ);  //�ش� ť�� ����ִ��� Ȯ�� �ϴ� �Լ�
int isFull(QueueType* cQ);  //�ش� ť�� ���� á���� Ȯ���ϴ� �Լ�
void enQueue(QueueType* cQ, element item);  //ť�� ���Ҹ� �������ִ� �Լ�(rear�� �̵�)
void deQueue(QueueType* cQ, element* item);  //ť�� ���Ҹ� �����ϴ� �Լ�(front�� �̵�)
void printQ(QueueType* cQ);  //ť�� ������ִ� �Լ�
void debugQ(QueueType* cQ);  //ť�� ��ü���� ������ Ȯ�����ִ� �Լ�
int freeQueue(QueueType* cQ); //�����޸𸮸� �������ִ� �Լ�

element getElement();  //ť�� ���Ҹ� �Է¹޾� ��ȯ���ִ� �Լ�


int main(void)
{
	QueueType* cQ = createQueue();  //���� ť�� cQ�� �����ϰ� createQueue�� ȣ���Ͽ� �ٷ� �������� �޸� �Ҵ����ش�.
	element data;  //�Է¹��� ���Ҹ� �Ѱܹ޴� ����

	char command;  //������ �޴�

	do {
		printf("\n-----------------------------------------------------\n");  //�ȳ��� ���
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");  //i = ť����, d = ť ���� ����, p = ť ����Ʈ ���
		printf("------------------------------------------------------\n");  //b = ť�� front, rear�� ��ġ, ť ���ҵ���� ��ġ�� ���

		printf("Command = ");  //�ȳ���
		fflush(stdout);  //�Է¹��� �� ���۸� ����д�.
		scanf(" %c", &command);  //�޴��� �Է¹޴´�.

		switch (command) {  //����ġ ���� �̿��Ͽ�
		case 'i': case 'I':  //Insert�� �����ϸ�
			data = getElement();  //getElement �Լ��� ȣ���Ͽ� �����͸� �Է¹��� �� data������ �����Ѵ�.
			enQueue(cQ, data);  //enQueue�Լ��� ȣ���� ���� ť�� ����á���� Ȯ�� �� �� ����� ���� �����ϰų� �ȳ����� ����Ѵ�.
			break;  //����ġ ���� ����������.
		case 'd': case 'D':  //Delete�� �����ϸ�
			deQueue(cQ, &data);  //deQueue�� ȣ���Ͽ� ���� ť�� �������� Ȯ�� �� �� ����� ���� front�� �̵��ϰų� �ȳ����� ����Ѵ�.
			break;//����ġ ���� ����������.
		case 'p': case 'P':  //Print�� �����ϸ�
			printQ(cQ);  //printQ�Լ��� ȣ���Ͽ� ť�� ����ִ� ���Ҹ� ������� ����Ѵ�.
			break;  //����ġ ���� ����������.
		case 'b': case 'B':  //Dubug�� �����ϸ�
			debugQ(cQ);  //debugQ �Լ��� ȣ���Ͽ� ť�� front,rear�� ��ġ, ť ������ ��ġ�� ���
			break;  //����ġ ���� ����������.
		case 'q': case 'Q'://Quit�� �����ϸ�
			if(freeQueue(cQ)==1);  //freeQueue �Լ��� ȣ���Ͽ� �������� �Ҵ���� �޸𸮸� �������ش�. ������ �����ϸ�
				printf("�޸� ���� ����\n"); //�ȳ��� ���
			break;  //����ġ ���� ����������.
		default:  //�߸� �����Ͽ�����
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //�ȳ��� �����
			break;  //����ġ���� ����������.
		}

	} while (command != 'q' && command != 'Q');  //Quit�� �����ϸ� �ݺ� ����
	printf("���α׷��� �����մϴ�.\n");  //�ȳ��� �����
	return 1;  //���α׷� ����

}


QueueType* createQueue()//�������� �޸𸮸� �������ִ� �Լ� ������ �޸��� �ּҸ� ��ȯ
{
	QueueType* cQ;  //�������� �Ҵ���� QueueType ����ü Ÿ�� ������ ���� ����
	cQ = (QueueType*)malloc(sizeof(QueueType));  //����ü Ÿ�� ������ ������ QueueType�� �����޸𸮸� �Ҵ��Ѵ�.
	cQ->front = 0;  //cQ������ ��� ���� front�� 0���� �ʱ�ȭ
	cQ->rear = 0;//cQ������ ��� ���� rear�� 0���� �ʱ�ȭ
	return cQ;  //cQ�� �ּҰ��� �����Ѵ�.
}

element getElement()  //ť�� ���Ҹ� �Է¹޴� ����
{
	element item;  //�Է¹��� ���� ����
	printf("Input element = ");  //�ȳ��� �����
	fflush(stdout);  //���۸� ��� ��
	scanf(" %c", &item);  //���� �Է�
	return item;  //�Է¹��� ���Ҹ� ��ȯ���ش�.
}


/* ���� ť�� ���� �������� Ȯ���ϴ� �Լ�
 * ����ִٸ� �ȳ����� ����ϰ� 0�� ��ȯ
 * �ƴ϶�� 1�� ��ȯ��.
 * */
int isEmpty(QueueType* cQ)
{
	if (cQ->front == cQ->rear)  //����ü�� ������� front�� rear�� ���ٸ� ����ť�� ����ִٴ� ���� �ǹ��Ѵ�.
	{
		printf("This queue is empty.\n");  //����ִٴ� �ȳ��� �����
		return 0;  //�Լ��� �����Ѵ�.
	}
	return 1;  //�ƴϸ� 1�� ��ȯ���ش�.
}

/* ���� ť�� ������ �������� Ȯ���ϴ� �Լ� */
int isFull(QueueType* cQ)
{
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
	/*���� ť������ �Ϲ� ť�� �޸�  front�� ����Ű�� �κ��� �׻� ����ִ� �����̴�.
	 * ���� ���� modulo�������� �̷��� �ϸ� rear�� 0- MAX_QUEUE_SIZE -1 �� ����ų �� �ִ�.
	 * rear�� ���� rear�� ����Ű�� ���� ���� ���� ����Ű���� �� ��*/
	if (cQ->front == cQ->rear)  //���� front�� rear�� ���ٸ� �̴� ���� ť�� ���� á�ٴ� ���̴�.
	{
		printf("cQ is full.\n");  //ť�� ���� á�ٴ� �ȳ����� ����� ��
		if (cQ->rear == 0)  //���� cQ�� ����Ű�� ��ġ�� 0�̶��
			cQ->rear = MAX_QUEUE_SIZE - 1;  //rear�� ���� ����Ű�� ���� ����Ű���� �ϱ� ���� �迭�� ���� ������ �ε����� ����Ű���� �ϰ�
		else  //�ƴ϶��
			cQ->rear -= 1; //���� ����Ű�� ������ ���� rear�� ����Ű���� ����
		return 0;  //�Լ��� �����Ѵ�.
	}
	return 1;  //���� ���� �ʾҴٸ� 1�� ��ȯ�Ѵ�.
}


/* ť�� ���Ҹ� �������ִ� �Լ� */
void enQueue(QueueType* cQ, element item)
{
	if (isFull(cQ) == 1)  //isFull �Լ��� ����Ͽ� �ش� ť�� ����á���� Ȯ�� �� �� �������� �ʾҴٸ�
		/*isFull�Լ����� ť�� �������� �ʾҴٸ� cQ->rear�� �� ���� ����ִ� ������ ����Ű�� �ȴ�.*/
		cQ->queue[cQ->rear] = item;  //���� ����ü ������� rear�� ����Ű�� ����(isFull�Լ����� ��������)�� �̷¹��� ���Ҹ� �������ش�.
}

/* ť�� ���Ҹ� �������ִ� �Լ�
 * ��Ȯ�� ������� ���ٴ� front�� ����Ű�� �迭�� �̵������ش�. */
void deQueue(QueueType* cQ, element* item)  //ť�� ���� ���� ���� ���� ������ �����̴�.
{
	if (isEmpty(cQ) == 1)  //ifEmpty�Լ��� �̿��Ͽ� ť�� �������� Ȯ���� �� ������ �ƴ϶��
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //cQ->front�� ����Ű�� ���� ���� ��ġ���� ���� ��ġ�� �������ش�.
}


void printQ(QueueType* cQ)  //ť�� ���Ҹ� ������� ������ִ� �Լ�
{
	int i, first, last;  //���� ����

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;  //front�� �ƹ� �͵� ���� ������ ����Ű�Ƿ� �� ���� ���Ҹ� ����Ű�� �Ѵ�.
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;  //�������� rear�� ���� ���Ҹ� ����Ű���� �Ѵ�.

	printf("Circular Queue : [");  //�ȳ��� ���

	i = first;  //i�� first�� �Է����ְ�
	while (i != last) {  //i�� last�� ���� ������ �ݺ�  // rear�� ����Ű�� �� �� ������ ť�� ���Ұ� ����ִ�.
		printf("%3c", cQ->queue[i]);  //cQ->queue[i]�� ť�� ù��° ���Һ��� ť�� ������ ���ұ��� �̴�.//���Ҹ� ����ϰ�
		i = (i + 1) % MAX_QUEUE_SIZE;  //cQ->queue[i] �� ���� ���Ҹ� ����ų �� �ֵ��� i�� �������ش�.

	}
	printf(" ]\n");  //�ȳ��� ����� ����
}


void debugQ(QueueType* cQ)  //ť�� front,rear�� ��ġ, ť ������ ��ġ�� ������ִ� �Լ�
{

	printf("\n---DEBUG\n");  //�ȳ��� ���
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)  //MAX_QUEUE_SIZE���� �ݺ�
	{
		if (i == cQ->front) {  //���� i�� cQ->front�͵����ϴٸ� (front�� ����Ű�� ������ �� ����)
			printf("  [%d] = front\n", i);  //front ���� �˸���
			continue;  //�ݺ����� ó������ ���ư���.
		}//�ƴ϶��
		printf("  [%d] = %c\n", i, cQ->queue[i]);  //Queue�� ���Ҹ� ����Ѵ�.
		//deQueue�� ���Ҹ� �����ϴ� ���� �ƴ϶� front�� ��ġ�� �������ִ� ���̱� ������ �Է��� ������ ���ҵ��� �״�� ���� �ִ´�.

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  //front�� rear�� ��ġ�� ����Ѵ�.
}

int freeQueue(QueueType* cQ)  //�������� �Ҵ���� �޸𸮸� �������ش�.
{
	if (cQ == NULL) {  //�����޸𸮸� �Ҵ���� �ʾҴٸ�
		printf("�������� �޸𸮸� �Ҵ���� ����\n");  //�ȳ��� ��� ��
		return 0;//���α׷� ����
	}
	free(cQ);  //�ƴ϶�� �����޸𸮸� ������ �� ��
	return 1;  //1�� ��ȯ���ش�.
}
