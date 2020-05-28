/*
 ============================================================================
 Name        : binary-search-tree-2.c
 ============================================================================
 */

/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);
int isfull();
int isEmpty();

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);
int isFull(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */





int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("2018068005 전아현\n");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;


		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	if (!node) {  //비어있는 트리이면
		printf("공백트리 입니다.\n");  //안내문 출력 후 프로그램 종료
		return;
	}
	for (;;)
	{
		for (; node; node = node->left)  //트리의 루트부터 맨 마지막 레벨에 있는 왼쪽자식노드를 순서대로
			push(node);  //스택에 삽입한다.
		node = pop();  // 마지막으로 삽입한 노드를 반환 후 스택에서 삭제한다.
		if (!node) break;  //해당 노드가 NULL이라면 반복문을 종료한다.
		printf(" [%d] ", node->key);  //아니면 해당 노드를 출력하고
		node = node->right;  // 노드가 노드의 오른쪽 자식을 가리키도록 한다.
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	enQueue(ptr);  // 해당 노드를 큐에 삽입한다.
	for (;;)
	{
		ptr = deQueue();  //삽입한 노드를 빼낸 후
		if (ptr)  //그 노드가 비어있지 않다면
		{
			printf(" [%d] ", ptr->key);  //해당 노드의 키 값을 출력한 후
			if (ptr->left)  //왼쪽 자식이 존재하면
				enQueue(ptr->left);  //왼쪽 자식을 넣어주고
			if (ptr->right)  //오른쪽 자신이 존재하면
				enQueue(ptr->right);  //오른쪽 자식을 큐에 넣어준다
		}
		else break;  // 비어있다면 반복문을 빠져나온다.
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* p;
	Node* pre,*child;

	if (head->left == NULL)  //해당 트리가 비어있다면
	{
		printf("해당 트리는 비었습니다.\n");  //안내문 출력 후
		return 0;  //함수 종료
	}
	p = head->left;


	while ((p != NULL) && (p->key != key)) //p가 비어있지 않고 해당 노드의 값이 입력받은 키와 같지 않다면
	{
		pre = p;  //부모노드가 p를 가리키도록 하고
		if (key < p->key) p = p->left;  //입력받은 키가 작으면 p가 p의 왼쪽 노드를
		else p = p->right;  //입력받은 키가 크면 p가 p의 오른쪽 노드를 가리키도록 한다.
	}

	if (p == NULL)  //만약 입력받은 키가 존재하지 않는다면
	{
		printf("%d 는 존재하지 않습니다.\n", key);  //안내문을 출력한 뒤
		return 0;  //함수 종료
	}

	if (p->left == NULL && p->right == NULL)  // 삭제할 노드가 단말노드라면
	{
		if (pre != NULL)  //부모노드가 헤드노드가 아니면
		{
			if (pre->left == p)  // 부모노드의 왼쪽 노드이면
				pre->left = NULL;  //부모 노드의 왼쪽 링크를 비워주고
			else  //오른쪽 노드라면
				pre->right = NULL;  //부모노드의 오른쪽 링크를 비워준다.
		}
		else //부모노드가 헤드노드일경우
			head->left = NULL;  //헤드노드의 왼쪽을 NULL로 만들어준다.
	}

	else if (p->left == NULL || p->right == NULL)  //삭제할 노드가 자식 노드를 하나만 가진 경우
	{
		if (p->left != NULL)  //삭제할 노드의 왼쪽 자식이 있다면
			child = p->left;   //자식노드가 p의 왼쪽을 가리키도록 하고
		else  //반대라면
			child = p->right;   // 자식노드가 p의 오른쪽을 가리키도록 한다.

		if (pre != NULL)  //부모노드가 헤드노드가 아니라면
		{
			if (pre->left == p)  //부모노드의 왼쪽 노드가 삭제할 노드였다면
				pre->left = child;  //부모노드의 왼쪽 노드가 자식노드를 가리키도록 하고
			else  //아니라면
				pre->right = child;  //오른쪽 노드가 자식노드를 가리키도록 한다.
		}
		else//부모노드가 헤드노드라면
			head->left = child;
	}

	else  //삭제할 노드가 자식 노드 두개를 가진 경우 ( 왼쪽 노드 들 중 가장 큰 노드 선택)
	{
		pre = p;  //부모노드가 삭제할 노드를 가리키도록 한다.
		child = p->left;  //자식 노드가 삭제할 노드의 왼쪽 자식을 선택하도록 한다.
		while (child->right != NULL)  //가장 큰 노드를 선택해야 하므로 자식 노드의 오른쪽 자식이 없을때까지
		{
			pre = child;  // 부모노드가 자식노드를 가리키고
			child = child->right;  //자식노드가 자신의 오른쪽 노드를 가리키도록 한다.
		}

		if (pre->left == child)  // 만약 부모의 왼쪽 노드가 자식노드라면 (삭제할 노드의 왼쪽 자식이 가장 큰 노드일 경우)
			pre->left = child->left;  //부모노드의 왼쪽 노드가 자식노드의  왼쪽 자식을 가리키도록 하고
		else
			pre->right = child->left;  //부모의 오른쪽 노드가 자식노드라면 부모의 오른쪽 노드가 자식노드의 왼쪽 자식을 가리키도록하고
		p->key = child->key;  //삭제할 노드의 키를 자식노드의 키로 바꿔준 후
		p = child;  //삭제할 노드를 자식노드로 변경해준다.
	}
	free(p);  //해당 노드를 삭제한다.

}



void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top == -1)  //스택이 비었다면
		return NULL;  //함수 종료

	return stack[top--]; //아니라면 현재 top의 원소를 하나 반환한 후 top을 감소
}

void push(Node* aNode)
{
	if (top == MAX_STACK_SIZE - 1)  //스택이 가득 찼다면
		return;   //함수 종료

	stack[++top]=aNode;  //아니라면 현재 top을 증가시킨 후 해당 노드를 넣어준다.
}

int isEmpty()
{
	if (top == -1) return 1;  // 만약 스택이 비었다면
	else return 0; //아니라면 0반환
}


Node* deQueue()
{
	if (rear == front)  //만약 비어있는 큐라면
		return NULL;  //프로그램 종료

	front = (front + 1) % MAX_QUEUE_SIZE;  //아니라면  front 가 그 다음을 가리키도록 하고
	return queue[front];  //front가 가리키는 값을 반환한 후 삭제한다.
}

void enQueue(Node* aNode)
{
	if (((rear + 1) % MAX_QUEUE_SIZE) == front)  //만약 원형큐가 포화상태라면
		return;  //프로그램 종료

	rear = ((rear + 1) % MAX_QUEUE_SIZE);  //아니라면 rear를 1 증가한 뒤
	queue[rear] = aNode;  // 해당 노드에 트리 삽입
}



