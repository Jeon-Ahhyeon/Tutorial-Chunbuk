/*
 ============================================================================
 Name        : circluar-linked-list.c
 ============================================================================
 */

/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;
 printf("������ 2018068005\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	printf("���α׷� ����");
	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));  //���������ͷ� ���� ��� ��忡 �޸� �Ҵ�
	(*h)->rlink = *h;  //������� ������ ��ũ�� ����带 ����Ű���� �� ��
	(*h)->llink = *h;  //������� ���� ��ũ�� ����带 ����Ű�� �Ѵ�.
	(*h)->key = -9999;  //������� ���� -9999�� �����Ѵ�.
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {
	listNode* p = h->rlink;  //������ ����� ���� ����� ������ ���� ���
	listNode* pre = NULL;  //������ �޸��� ������ ���� ���
	while (p!= h)  //���Ḯ��Ʈ�� ����������
	{
		pre = p;  //pre�� p�� ���� ��带 ����Ű���� �ϰ�
		p = p->rlink;  //p�� p�� ���� ��带 ����Ű���� �� �Ĥ�
		free(pre);  //pre ��带 �������ش�.
	}
	free(h);  //���������� ������� �޸𸮸� �������ش�.
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {  //����� �������� ��� �ϳ� ����
	listNode* node = (listNode*)malloc(sizeof(listNode));  //�Է¹��� Ű�� ������ ���� ��� ���� �� ���� �޸� �Ҵ�
	listNode* p;  //���� ���� ���Ḯ��Ʈ�� Ž���� ���� ���

	node->key = key;  //��忡 �Է¹��� Ű�� ������ �����Ѵ�.
	node->llink = NULL;  //node�� ��ũ�� NULL�� ����Ű���� �����Ѵ�.
	node->rlink = NULL;

	if (h->rlink == h) //���鸮��Ʈ���
	{
		node->llink = h;  //����� ���� ��ũ�� ����带 ����Ű���� �ϰ�
		h->rlink = node;  //������� ������ ��ũ�� ��带 ����Ű���� �ϰ�
		node->rlink = h;  //����� ������ ��ũ�� ����带 ����Ű���� �� ��
		h->llink = node;  //������� ���� ��ũ�� ��带 ����Ű���� �Ѵ�.
	}
	else  //������� ���� ����Ʈ���
	{
		p = h->rlink;  //p�� ù��° ��带 ����Ű���� �Ѵ�.
		while (p->rlink != h)  //���Ḯ��Ʈ�� ��������带 ����ų ������
			p = p->rlink;  //p�� ���� ��带 ����Ű���� �Ѵ�.
		node->llink = p;  //����� ���� ��ũ�� ���Ḯ��Ʈ�� ������ ��带 ����Ű���� �� ��
		p->rlink = node;  //������ ����� ������ ��ũ�� ��带 ����Ű���� �ϰ�
		node->rlink = h;  //����� ������ ��ũ�� ��� ��带 ����Ű���� �ϰ�
		h->llink = node;  //����� ���� ��ũ�� ��带 ����Ű���� �Ѵ�.
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {  //������ ��带 �����ϴ� �Լ�
	listNode* p;  //������ ��带 ����ų ����ü
	p = h->rlink;  //p�� ù��° ��带 ����Ű���� �Ѵ�.

	if (h->rlink == h)  //���鸮��Ʈ���
	{
		printf("����ִ� ���� ���� ����Ʈ�Դϴ�.\n");  //�ȳ����� ����� ��
		return 0;  //���α׷��� �����Ѵ�.
	}
	else  //���鸮��Ʈ�� �ƴ϶��
	{
		while (p->rlink != h)  //p�� ����Ʈ�� ������ ��带 ����ų �� ����
			p = p->rlink;  //p�� ���� ��带 ����Ű���� �Ѵ�.
		p->llink->rlink = h;  //������ ����� ���� ����� ������ ��ũ�� ����带 ����Ű���� �ϰ�
		h->llink = p->llink;  //����� ���� ��尡 ������ ����� ���� ��带 ����Ű���� �Ѵ�.
		free(p);  //�������� �޸𸮸� �����Ѵ�.
	}
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));  //�Է¹��� Ű�� ������ ������ ���
	node->key = key;  //��忡 �Է¹��� Ű�������� �����Ѵ�.
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h)//���鸮��Ʈ���
	{
		node->llink = h; //������ ����� ���� ��ũ�� ����带 ����Ű�����ϰ�
		h->rlink = node;  //����� ������ ��ũ�� ������ ��带 ����Ű���� �ϰ�
		node->rlink = h;  //������ ����� ������ ��ũ�� ����带 ����Ű���� �� ��
		h->llink = node;  //������� ���� ��ũ�� ������ ��带 ����Ű���� �Ѵ�.
		return 0;  //���α׷��� �����Ѵ�.
	}
	node->rlink = h->rlink;  //������ ����� ������ ��ũ�� ù��° ��带 ����Ű���� �ϰ�
	h->rlink->llink = node;  //ù��° ����� ���� ��ũ�� ������ ��带 ����Ű���� �ϰ�
	node->llink = h; //������ ����� ���� ��ũ�� ��� ��带 ����Ű���� �� ��
	h->rlink = node;  //ù��° ��尡 ������ ��带 ����Ű���� �Ѵ�.

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	listNode* p;//������ ����� ������ ���� ���
	p = h->rlink;  //p�� ù��° ��带 ����Ű���� �Ѵ�.

	if (h->rlink == h)  //���鸮��Ʈ���
	{
		printf("����ִ� ���鸮��Ʈ �Դϴ�. \n");  //�ȳ��� ��� ��
		return 0;  //���α׷� ����
	}
	else  //�ƴ϶��
	{
		p->rlink->llink = h;  //ù��° ����� ���� ����� ���� ��ũ�� ��带 ����Ű���� �� ��
		h->rlink = p->rlink;  //����� ������ ��ũ�� ù��° ����� ������带 ����Ű���� �Ѵ�.
		free(p);  //p�� �޸𸮸� �������� �������ش�.
	}

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	listNode* p;  //����Ʈ�� �ѹ� ���� ���� �ʿ��� ���
	listNode* pre;  // ����Ʈ�� �������� ��ġ�ϱ� ���� �ʿ��� ���
	listNode* mid;

	if (h->rlink == h)  // ���鸮��Ʈ���
	{
		printf("����ִ� ����Ʈ �Դϴ�.\n");  //�ȳ����� ����� ��
		return 0;  //���α׷� ����
	}
	else if (h->rlink->rlink == h)  //��尡 �ϳ����
	{
		printf("��尡 �ϳ��ۿ� �����ϴ�.\n");  //�ȳ����� ����� ��
		return 0;  //���α׷��� �����Ѵ�.
	}
	p = h->rlink;  //p�� ����Ʈ�� ù��° ��带 ����Ű���� �Ѵ�.
	h->llink = p;  //����� ���� ��ũ�� ù��° ��带 ����Ű���� �Ѵ�.
	while (p != h)  //����Ʈ�� ����������
	{
		pre = p;  //pre�� p�� ����Ű���� �ϰ�
		mid = pre->rlink;  // mid�� pre�� ���� ��带 ����Ű���� �Ѵ�,
		pre->rlink = pre->llink;  //pre�� ������ ��ũ�� pre�� ���� ��ũ�� ����Ű���� �ϰ�
		pre->llink = mid;  //pre�� ���� ��ũ�� �ش� ����� ������ ����Ű���� �� ��
		p = mid;  //p�� ���� ��带 ����Ű���� �Ѵ�.
	}
	h->rlink = pre;  //������� ������ ��ũ�� ����Ʈ�� ������ ��带 ����Ű���� �ϰ�
	pre->llink = h;  // ù��° ��尡 �� ������ ����� ���� ��ũ�� ����带 ����Ű���� �Ѵ�.

	return 0;  //���α׷��� �����Ѵ�.
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));  //�Է��� Ű�� ������ ������ ���
	listNode* p;  //����Ʈ Ž���� ���� ���
	listNode* pre;  //����Ʈ�� �������� �ٲ��ֱ� ���� ���

	node->key = key;  //��忡 �Է¹��� Ű�� ������ �����Ѵ�.
	node->llink = NULL;
	node->rlink = NULL;

	if (h->rlink == h)//���鸮��Ʈ���
	{
		node->llink = h;  //������ ����� ���� ��尡 ����带 ����Ű���� �ϰ�
		h->rlink = node;  //��� ����� ������ ��ũ�� ������ ��带 ����Ű���� �ϰ�
		node->rlink = h;  // ������ ����� ������ ��尡 ��� ��带 ����Ű���� �� ��
		h->llink = node;  //��� ����� ���� ��尡 ������ ��带 ����Ű���� �Ѵ�.
		return 0;  //���α׷��� �����Ѵ�.
	}
	p = h->rlink;  //p�� ����Ʈ�� ù��° ��带 ����Ű���� �Ѵ�.
	while (p != h)  //p�� ����Ʈ�� ������ ��带 ����ų �� ����
	{
		if (p->key >= key)  //�Է¹��� Ű�� �� ��ġ�� ã�Ҵٸ�
		{
			if (p == h->rlink)  //�ش� ��ġ�� ����Ʈ�� ó���̶��
			{
				node->rlink = h->rlink;//������ ����� ������ ��ũ�� ù��° ��带 ����Ű���� �ϰ�
				h->rlink->llink = node; //ù��° ����� ���� ��尡 ������ ��带 ����Ű���� �ϰ�
				node->llink = h;  // ������ ����� ���� ��ũ�� ����带 ����Ű���� �� ��
				h->rlink = node;  //������� ������ ��ũ�� ������ ��带 ����Ű���� �Ѵ�.
			}
			else  //�ƴ϶��
			{
				node->rlink = p; //������ ����� ������ ��ũ�� p�� ����Ű���� �ϰ�
				p->llink->rlink = node;  // ������ ��ġ�� ���� ����� ������ ��ũ�� ������ ��带 ����Ű���� �ϰ�
				node->llink = p->llink;  //������ ����� ���� ��ũ�� ������ ��ġ�� ���� ��带 ����Ű���� �� ��
				p->llink = node;  //������ ��ġ�� ���� ����� ���� ��ũ�� ������ ��带 ����Ű���� �Ѵ�.
			}
			return 0;  //���α׷��� �����Ѵ�.
		}
		pre = p;  //pre�� ���� ��ġ�� �����ϰ�
		p = p->rlink;  //p�� ���� ��ġ�� �����Ѵ�.
	}
	node->llink = pre;  //������ ����� ���� ��ũ�� ������ ��带 ����Ű���� �ϰ�
	pre->rlink = node;  //������ ����� ������ ��ũ�� ������ ��带 ����Ű���� �ϰ�
	node->rlink = h;  //������ ����� ������ ��ũ�� ��� ��带 ����Ű���� �ϰ�
	h->llink = node;  //������� ���� ��ũ�� ������ ��带 ����Ű���� �Ѵ�.

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	listNode* p;  //������ ��带 Ž���ϱ� ���� �ʿ��� ���

	if (h->rlink == h)  //���鸮��Ʈ���
	{
		printf("����ִ� ���鸮��Ʈ �Դϴ�. \n");//�ȳ����� ����� ��
		return 0;  //���α׷��� �����Ѵ�.
	}
	p = h->rlink;  //p�� ù��° ����Ʈ�� ����Ű���� �Ѵ�.
	while (p != h)  //����Ʈ�� ����������
	{
		if (p->key == key)  //������ ��带 ã��
		{
			if (p == h->rlink)  //�ش� ��尡 ù��° �����
			{
				p->rlink->llink = h;  //������ ����� ���� ����� ���� ��ũ�� ����带 ����Ű���� �ϰ�
				h->rlink = p->rlink;  //ù��° ��尡 ������ ����� ���� ��带 ����Ű���� ����
				free(p);  //�ش� ����� �޸𸮸� �����Ѵ�.
			}
			else  //�ƴ϶��
			{
				p->llink->rlink = p->rlink;  //������ ����� ���� ����� ������ ��ũ�� ������ ����� ���� ��带 ����Ű���� �ϰ�
				p->rlink->llink = p->llink;  // ������ ����� ���� ����� ���� ��ũ�� ������ ����� ���� ��带 ����Ű���� �� ��
				free(p);  //�ش� ����� �޸𸮸� �����Ѵ�.
			}
			return 0;  //���α׷��� �����Ѵ�.
		}
		p = p->rlink;  //p�� p�� ������带 ����Ű���� �Ѵ�.
	}//���ٸ�

	printf("%d �� ����Ʈ�� �������� �ʽ��ϴ�.\n", key);  //�ȳ����� ����� ��

	return 0;  //���α׷��� �����Ѵ�.

}


