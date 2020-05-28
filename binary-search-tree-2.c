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

	printf("2018068005 ������\n");
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
	if (!node) {  //����ִ� Ʈ���̸�
		printf("����Ʈ�� �Դϴ�.\n");  //�ȳ��� ��� �� ���α׷� ����
		return;
	}
	for (;;)
	{
		for (; node; node = node->left)  //Ʈ���� ��Ʈ���� �� ������ ������ �ִ� �����ڽĳ�带 �������
			push(node);  //���ÿ� �����Ѵ�.
		node = pop();  // ���������� ������ ��带 ��ȯ �� ���ÿ��� �����Ѵ�.
		if (!node) break;  //�ش� ��尡 NULL�̶�� �ݺ����� �����Ѵ�.
		printf(" [%d] ", node->key);  //�ƴϸ� �ش� ��带 ����ϰ�
		node = node->right;  // ��尡 ����� ������ �ڽ��� ����Ű���� �Ѵ�.
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	enQueue(ptr);  // �ش� ��带 ť�� �����Ѵ�.
	for (;;)
	{
		ptr = deQueue();  //������ ��带 ���� ��
		if (ptr)  //�� ��尡 ������� �ʴٸ�
		{
			printf(" [%d] ", ptr->key);  //�ش� ����� Ű ���� ����� ��
			if (ptr->left)  //���� �ڽ��� �����ϸ�
				enQueue(ptr->left);  //���� �ڽ��� �־��ְ�
			if (ptr->right)  //������ �ڽ��� �����ϸ�
				enQueue(ptr->right);  //������ �ڽ��� ť�� �־��ش�
		}
		else break;  // ����ִٸ� �ݺ����� �������´�.
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

	if (head->left == NULL)  //�ش� Ʈ���� ����ִٸ�
	{
		printf("�ش� Ʈ���� ������ϴ�.\n");  //�ȳ��� ��� ��
		return 0;  //�Լ� ����
	}
	p = head->left;


	while ((p != NULL) && (p->key != key)) //p�� ������� �ʰ� �ش� ����� ���� �Է¹��� Ű�� ���� �ʴٸ�
	{
		pre = p;  //�θ��尡 p�� ����Ű���� �ϰ�
		if (key < p->key) p = p->left;  //�Է¹��� Ű�� ������ p�� p�� ���� ��带
		else p = p->right;  //�Է¹��� Ű�� ũ�� p�� p�� ������ ��带 ����Ű���� �Ѵ�.
	}

	if (p == NULL)  //���� �Է¹��� Ű�� �������� �ʴ´ٸ�
	{
		printf("%d �� �������� �ʽ��ϴ�.\n", key);  //�ȳ����� ����� ��
		return 0;  //�Լ� ����
	}

	if (p->left == NULL && p->right == NULL)  // ������ ��尡 �ܸ������
	{
		if (pre != NULL)  //�θ��尡 ����尡 �ƴϸ�
		{
			if (pre->left == p)  // �θ����� ���� ����̸�
				pre->left = NULL;  //�θ� ����� ���� ��ũ�� ����ְ�
			else  //������ �����
				pre->right = NULL;  //�θ����� ������ ��ũ�� ����ش�.
		}
		else //�θ��尡 ������ϰ��
			head->left = NULL;  //������� ������ NULL�� ������ش�.
	}

	else if (p->left == NULL || p->right == NULL)  //������ ��尡 �ڽ� ��带 �ϳ��� ���� ���
	{
		if (p->left != NULL)  //������ ����� ���� �ڽ��� �ִٸ�
			child = p->left;   //�ڽĳ�尡 p�� ������ ����Ű���� �ϰ�
		else  //�ݴ���
			child = p->right;   // �ڽĳ�尡 p�� �������� ����Ű���� �Ѵ�.

		if (pre != NULL)  //�θ��尡 ����尡 �ƴ϶��
		{
			if (pre->left == p)  //�θ����� ���� ��尡 ������ ��忴�ٸ�
				pre->left = child;  //�θ����� ���� ��尡 �ڽĳ�带 ����Ű���� �ϰ�
			else  //�ƴ϶��
				pre->right = child;  //������ ��尡 �ڽĳ�带 ����Ű���� �Ѵ�.
		}
		else//�θ��尡 �������
			head->left = child;
	}

	else  //������ ��尡 �ڽ� ��� �ΰ��� ���� ��� ( ���� ��� �� �� ���� ū ��� ����)
	{
		pre = p;  //�θ��尡 ������ ��带 ����Ű���� �Ѵ�.
		child = p->left;  //�ڽ� ��尡 ������ ����� ���� �ڽ��� �����ϵ��� �Ѵ�.
		while (child->right != NULL)  //���� ū ��带 �����ؾ� �ϹǷ� �ڽ� ����� ������ �ڽ��� ����������
		{
			pre = child;  // �θ��尡 �ڽĳ�带 ����Ű��
			child = child->right;  //�ڽĳ�尡 �ڽ��� ������ ��带 ����Ű���� �Ѵ�.
		}

		if (pre->left == child)  // ���� �θ��� ���� ��尡 �ڽĳ���� (������ ����� ���� �ڽ��� ���� ū ����� ���)
			pre->left = child->left;  //�θ����� ���� ��尡 �ڽĳ����  ���� �ڽ��� ����Ű���� �ϰ�
		else
			pre->right = child->left;  //�θ��� ������ ��尡 �ڽĳ���� �θ��� ������ ��尡 �ڽĳ���� ���� �ڽ��� ����Ű�����ϰ�
		p->key = child->key;  //������ ����� Ű�� �ڽĳ���� Ű�� �ٲ��� ��
		p = child;  //������ ��带 �ڽĳ��� �������ش�.
	}
	free(p);  //�ش� ��带 �����Ѵ�.

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
	if (top == -1)  //������ ����ٸ�
		return NULL;  //�Լ� ����

	return stack[top--]; //�ƴ϶�� ���� top�� ���Ҹ� �ϳ� ��ȯ�� �� top�� ����
}

void push(Node* aNode)
{
	if (top == MAX_STACK_SIZE - 1)  //������ ���� á�ٸ�
		return;   //�Լ� ����

	stack[++top]=aNode;  //�ƴ϶�� ���� top�� ������Ų �� �ش� ��带 �־��ش�.
}

int isEmpty()
{
	if (top == -1) return 1;  // ���� ������ ����ٸ�
	else return 0; //�ƴ϶�� 0��ȯ
}


Node* deQueue()
{
	if (rear == front)  //���� ����ִ� ť���
		return NULL;  //���α׷� ����

	front = (front + 1) % MAX_QUEUE_SIZE;  //�ƴ϶��  front �� �� ������ ����Ű���� �ϰ�
	return queue[front];  //front�� ����Ű�� ���� ��ȯ�� �� �����Ѵ�.
}

void enQueue(Node* aNode)
{
	if (((rear + 1) % MAX_QUEUE_SIZE) == front)  //���� ����ť�� ��ȭ���¶��
		return;  //���α׷� ����

	rear = ((rear + 1) % MAX_QUEUE_SIZE);  //�ƴ϶�� rear�� 1 ������ ��
	queue[rear] = aNode;  // �ش� ��忡 Ʈ�� ����
}



