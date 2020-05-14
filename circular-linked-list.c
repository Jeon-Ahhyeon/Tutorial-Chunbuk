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
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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
 printf("전아현 2018068005\n");

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

	printf("프로그램 종료");
	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));  //이중포인터로 받은 헤드 노드에 메모리 할당
	(*h)->rlink = *h;  //헤드노드의 오른쪽 링크가 헤드노드를 가리키도록 한 후
	(*h)->llink = *h;  //헤드노드의 왼쪽 링크가 헤드노드를 가리키게 한다.
	(*h)->key = -9999;  //헤드노드의 값은 -9999로 설정한다.
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	listNode* p = h->rlink;  //해제할 노드의 다음 노드의 정보를 담은 노드
	listNode* pre = NULL;  //해제할 메모리의 정보를 담은 노드
	while (p!= h)  //연결리스트의 마지막까지
	{
		pre = p;  //pre가 p의 이전 노드를 가리키도록 하고
		p = p->rlink;  //p가 p의 다음 노드를 가리키도록 한 후ㅜ
		free(pre);  //pre 노드를 해제해준다.
	}
	free(h);  //마지막으로 헤드노드의 메모리를 해제해준다.
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {  //노드의 마지막에 노드 하나 삽입
	listNode* node = (listNode*)malloc(sizeof(listNode));  //입력받은 키의 정보를 담을 노드 선언 및 동적 메모리 할당
	listNode* p;  //원형 이중 연결리스트의 탐색을 위한 노드

	node->key = key;  //노드에 입력받은 키의 정보를 저장한다.
	node->llink = NULL;  //node의 링크가 NULL을 가리키도록 저장한다.
	node->rlink = NULL;

	if (h->rlink == h) //공백리스트라면
	{
		node->llink = h;  //노드의 왼쪽 링크가 헤드노드를 가리키도록 하고
		h->rlink = node;  //헤드노드의 오른쪽 링크가 노드를 가리키도록 하고
		node->rlink = h;  //노드의 오른쪽 링크가 헤드노드를 가리키도록 한 후
		h->llink = node;  //헤드노드의 왼쪽 링크가 노드를 가리키도록 한다.
	}
	else  //비어있지 않은 리스트라면
	{
		p = h->rlink;  //p가 첫번째 노드를 가리키도록 한다.
		while (p->rlink != h)  //연결리스트의 마지막노드를 가리킬 때까지
			p = p->rlink;  //p가 다음 노드를 가리키도록 한다.
		node->llink = p;  //노드의 왼쪽 링크가 연결리스트의 마지막 노드를 가리키도록 한 후
		p->rlink = node;  //마지막 노드의 오른쪽 링크가 노드를 가리키도록 하고
		node->rlink = h;  //노드의 오른쪽 링크가 헤드 노드를 가리키도록 하고
		h->llink = node;  //헤드의 왼쪽 링크가 노드를 가리키도록 한다.
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {  //마지막 노드를 삭제하는 함수
	listNode* p;  //삭제할 노드를 가리킬 구조체
	p = h->rlink;  //p가 첫번째 노드를 가리키도록 한다.

	if (h->rlink == h)  //공백리스트라면
	{
		printf("비어있는 공백 연결 리스트입니다.\n");  //안내문을 출력한 후
		return 0;  //프로그램을 종료한다.
	}
	else  //공백리스트가 아니라면
	{
		while (p->rlink != h)  //p가 리스트의 마지막 노드를 가리킬 때 까지
			p = p->rlink;  //p가 다음 노드를 가리키도록 한다.
		p->llink->rlink = h;  //삭제할 노드의 이전 노드의 오른쪽 링크가 헤드노드를 가리키도록 하고
		h->llink = p->llink;  //헤드의 왼쪽 노드가 삭제할 노드의 왼쪽 노드를 가리키도록 한다.
		free(p);  //동적으로 메모리를 해제한다.
	}
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));  //입력받은 키의 정보를 저장할 노드
	node->key = key;  //노드에 입력받은 키의정보를 저장한다.
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h)//공백리스트라면
	{
		node->llink = h; //삽입할 노드의 왼쪽 링크가 헤드노드를 가리키도록하고
		h->rlink = node;  //헤드의 오른쪽 링크가 삽입할 노드를 가리키도록 하고
		node->rlink = h;  //삽입할 노드의 오른쪽 링크가 헤드노드를 가리키도록 한 후
		h->llink = node;  //헤드노드의 왼쪽 링크가 삽입할 노드를 가리키도록 한다.
		return 0;  //프로그램을 종료한다.
	}
	node->rlink = h->rlink;  //삽입할 노드의 오른쪽 링크가 첫번째 노드를 가리키도록 하고
	h->rlink->llink = node;  //첫번째 노드의 왼쪽 링크가 삽입할 노드를 가리키도록 하고
	node->llink = h; //삽입할 노드의 왼쪽 링크가 헤드 노드를 가리키도록 한 후
	h->rlink = node;  //첫번째 노드가 삽입할 노드를 가리키도록 한다.

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* p;//삭제할 노드의 정보를 담을 노드
	p = h->rlink;  //p가 첫번째 노드를 가리키도록 한다.

	if (h->rlink == h)  //공백리스트라면
	{
		printf("비어있는 공백리스트 입니다. \n");  //안내문 출력 후
		return 0;  //프로그램 종료
	}
	else  //아니라면
	{
		p->rlink->llink = h;  //첫번째 노드의 다음 노드의 왼쪽 링크가 헤드를 가리키도록 한 후
		h->rlink = p->rlink;  //헤드의 오른쪽 링크가 첫번째 노드의 다음노드를 가리키도록 한다.
		free(p);  //p의 메모리를 동적으로 해제해준다.
	}

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* p;  //리스트를 한번 보기 위해 필요한 노드
	listNode* pre;  // 리스트를 역순으로 배치하기 위해 필요한 노드
	listNode* mid;

	if (h->rlink == h)  // 공백리스트라면
	{
		printf("비어있는 리스트 입니다.\n");  //안내문을 출력한 후
		return 0;  //프로그램 종료
	}
	else if (h->rlink->rlink == h)  //노드가 하나라면
	{
		printf("노드가 하나밖에 없습니다.\n");  //안내문을 출력한 후
		return 0;  //프로그램을 종료한다.
	}
	p = h->rlink;  //p가 리스트의 첫번째 노드를 가리키도록 한다.
	h->llink = p;  //헤드의 왼쪽 링크가 첫번째 노드를 가리키도록 한다.
	while (p != h)  //리스트의 마지막까지
	{
		pre = p;  //pre가 p를 가리키도록 하고
		mid = pre->rlink;  // mid가 pre의 다음 노드를 가리키도록 한다,
		pre->rlink = pre->llink;  //pre의 오른쪽 링크가 pre의 왼쪽 링크를 가리키도록 하고
		pre->llink = mid;  //pre의 왼쪽 링크가 해당 노드의 다음을 가리키도록 한 후
		p = mid;  //p가 다음 노드를 가리키도록 한다.
	}
	h->rlink = pre;  //헤드노드의 오른쪽 링크가 리스트의 마지막 노드를 가리키도록 하고
	pre->llink = h;  // 첫번째 노드가 된 마지막 노드의 왼쪽 링크가 헤드노드를 가리키도록 한다.

	return 0;  //프로그램을 종료한다.
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));  //입력한 키의 정보를 저장할 노드
	listNode* p;  //리스트 탐색을 위한 노드
	listNode* pre;  //리스트를 역순으로 바꿔주기 위한 노드

	node->key = key;  //노드에 입력받은 키의 정보를 저장한다.
	node->llink = NULL;
	node->rlink = NULL;

	if (h->rlink == h)//공백리스트라면
	{
		node->llink = h;  //삽입할 노드의 왼쪽 노드가 헤드노드를 가리키도록 하고
		h->rlink = node;  //헤드 노드의 오른쪽 링크가 삽입할 노드를 가리키도록 하고
		node->rlink = h;  // 삽입할 노드의 오른쪽 노드가 헤드 노드를 가리키도록 한 후
		h->llink = node;  //헤드 노드의 왼쪽 노드가 삽입할 노드를 가리키도록 한다.
		return 0;  //프로그램을 종료한다.
	}
	p = h->rlink;  //p가 리스트의 첫번째 노드를 가리키도록 한다.
	while (p != h)  //p가 리스트의 마지막 노드를 가리킬 때 까지
	{
		if (p->key >= key)  //입력받은 키가 들어갈 위치를 찾았다면
		{
			if (p == h->rlink)  //해당 위치가 리스트의 처음이라면
			{
				node->rlink = h->rlink;//삽입할 노드의 오른쪽 링크가 첫번째 노드를 가리키도록 하고
				h->rlink->llink = node; //첫번째 노드의 왼쪽 노드가 삽입할 노드를 가리키도록 하고
				node->llink = h;  // 삽입할 노드의 왼쪽 링크가 헤드노드를 가리키도록 한 후
				h->rlink = node;  //헤드노드의 오른쪽 링크가 삽입할 노드를 가리키도록 한다.
			}
			else  //아니라면
			{
				node->rlink = p; //삽입할 노드의 오른쪽 링크가 p를 가리키도록 하고
				p->llink->rlink = node;  // 삽입할 위치의 이전 노드의 오른쪽 링크가 삽입할 노드를 가리키도록 하고
				node->llink = p->llink;  //삽입할 노드의 왼쪽 링크가 삽입할 위치의 이전 노드를 가리키도록 한 후
				p->llink = node;  //삽입할 위치의 다음 노드의 왼쪽 링크가 삽입할 노드를 가리키도록 한다.
			}
			return 0;  //프로그램을 종료한다.
		}
		pre = p;  //pre에 현재 위치를 저장하고
		p = p->rlink;  //p에 다음 위치를 저장한다.
	}
	node->llink = pre;  //삽입할 노드의 왼쪽 링크가 마지막 노드를 가리키도록 하고
	pre->rlink = node;  //마지막 노드이 오른쪽 링크가 삽입할 노드를 가리키도록 하고
	node->rlink = h;  //삽입할 노드의 오른쪽 링크가 헤드 노드를 가리키도록 하고
	h->llink = node;  //헤드노드의 왼쪽 링크가 삽입한 노드를 가리키도록 한다.

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* p;  //삭제할 노드를 탐색하기 위해 필요한 노드

	if (h->rlink == h)  //공백리스트라면
	{
		printf("비어있는 공백리스트 입니다. \n");//안내문을 출력한 후
		return 0;  //프로그램을 종료한다.
	}
	p = h->rlink;  //p가 첫번째 리스트를 가리키도록 한다.
	while (p != h)  //리스트의 마지막까지
	{
		if (p->key == key)  //삭제할 노드를 찾고
		{
			if (p == h->rlink)  //해당 노드가 첫번째 노드라면
			{
				p->rlink->llink = h;  //삭제할 노드의 다음 노드의 왼쪽 링크가 헤드노드를 가리키도록 하고
				h->rlink = p->rlink;  //첫번째 노드가 삭제할 노드의 다음 노드를 가리키도록 한후
				free(p);  //해당 노드의 메모리를 해제한다.
			}
			else  //아니라면
			{
				p->llink->rlink = p->rlink;  //삭제할 노드의 이전 노드의 오른쪽 링크가 삭제할 노드의 다음 노드를 가리키도록 하고
				p->rlink->llink = p->llink;  // 삭제할 노드의 다음 노드의 왼쪽 링크가 삭제할 노드의 이전 노드를 가리키도록 한 후
				free(p);  //해당 노드의 메모리를 해제한다.
			}
			return 0;  //프로그램을 종료한다.
		}
		p = p->rlink;  //p가 p의 다음노드를 가리키도록 한다.
	}//없다면

	printf("%d 는 리스트에 존재하지 않습니다.\n", key);  //안내문을 출력한 후

	return 0;  //프로그램을 종료한다.

}


