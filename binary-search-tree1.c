/*
 ============================================================================
 Name        : binary-search-tree1.c
 ============================================================================
 */

/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void postorderfree(Node* ptr);  // Ʈ���� �޸𸮸� �����ϴ� �Լ� ����

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("������ 2018068005\n");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	printf("���α׷� ���� \n");
	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)  //����尡 ������� �ʴٸ�
		freeBST(*h);   //�ش� �ص��带 ����� �� ���� ������ �����Ѵ�.

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  // ��� ��忡 �������� �޸𸮸� �Ҵ��� ��
	(*h)->left = NULL;	/* root */  //���� ��带 �η� ������ְ�
	(*h)->right = *h;  //������ ��ũ�� ����带 ����Ű���� �Ѵ�.
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)  // ���� ��� -> �θ��� -> ������ ��� ������ Ž��
{
	if (ptr)  { //��尡 ������� �ʴٸ�
		inorderTraversal(ptr->left);  //����� ���� ���� ����Լ� ȣ��
		printf("%5d", ptr->key);  // �ش� ����� �� ���
		inorderTraversal(ptr->right);   //����� ������ ���� ����Լ� ȣ��
	}
}

void preorderTraversal(Node* ptr)  //�θ��� -> ���� ��� -> ������ ��� ������ Ž��
{
	if (ptr) {   //��尡 ������� �ʴٸ�
		printf("%5d", ptr->key);  //�ش� ����� ���� ���
		preorderTraversal(ptr->left);  //����� ���� ���� ����Լ� ȣ��
		preorderTraversal(ptr->right);  //����� ������ ���� ����Լ� ȣ��
	}
}

void postorderTraversal(Node* ptr)  //���� ���-> ������ ��� -> �θ� ��� ������ Ž��
{
	if (ptr)  //��尡 ������� �ʴٸ�
	{
		postorderTraversal(ptr->left);  //���� ���� ����Լ� ȣ��
		postorderTraversal(ptr->right);  //������ ���� ����Լ� ȣ��
		printf("%5d", ptr->key);  // �ش� ����� ���� ���
	}
}


int insert(Node* head, int key)   // �Է¹��� Ű�� �����ϴ� �Լ�
{
	Node* newNode = (Node*)malloc(sizeof(Node));  //�Է¹��� Ű�� ������ ����
	Node* p;  //Ʈ���� Ž���ϴµ� �ʿ��� ����
	newNode->key = key;  //�Է¹��� Ű�� �����Ѵ�.
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL)  //���� Ʈ���� ����ִٸ�
	{
		head->left = newNode;  //������� ���� ��ũ�� �Է¹��� ��带 ����Ű���� �Ѵ�.
		return 1;  //1�� ��ȯ���ش�.
	}
	p = head->left;  //p�� ������带 ����Ű���� �Ѵ�.
	while (1)// ������ ������ ������ �ݺ��Ѵ�.
	{
		if (p->key > key)  //���� �Է¹��� Ű�� �ش� ����� ������ �۰�
		{
			if (p->left == NULL)  // �ش� ����� ������ ����ִٸ�
			{
				p->left = newNode;  //����� ���ʿ� �Է¹��� Ű�� �����ϰ�
				return 1;  //�Լ� ����
			}
			else  //������� �ʴٸ�
			{
				p = p->left;  //p�� ����� ���� ��带 ����Ű���� ��
			}
		}
		else if (p->key < key)  //�Է¹��� Ű�� �ش� ����� ������ ũ��
		{
			if (p->right == NULL)  //�ش� ����� �������� ����ִٸ�
			{
				p->right = newNode;  //����� �����ʿ� �Է¹��� Ű�� �����ϰ�
				return 1;  //�Լ� ����
			}
			else  //������� �ʴٸ�
			{
				p = p->right;  //p�� ����� �������� ����Ű���� ��
			}
		}
		else if(p->key == key)  //���� �Է¹��� Ű�� ���ٸ�
		{
			printf("���� Ű�� �����մϴ�.\n");  //�ȳ��� ����� ��
			return 1;  //�Լ� ����
		}
	}

}

int deleteLeafNode(Node* head, int key) //�Է¹��� �ܸ���带 �����ϴ� �Լ�
{
	Node* p;  //������ ���
	Node* pre;  //������ ����� �θ� ���

	if (head->left == NULL)  //���� ����ִ� Ʈ�����
	{
		printf("�ش� Ʈ���� ����ֽ��ϴ�.\n");  //�ȳ��� ��� ��
		return 0; //�Լ� ����
	}
	p = head->left;  //p�� ��Ʈ��带 ����Ű���� �� ��
	if (p->key == key && p->left == NULL && p->right == NULL) //Ʈ���� ù��° ��尡 ������ ����̰� �ܸ������
	{
		free(p);  //p�� �޸𸮸� �����ϰ�
		head->left = NULL;  // ������� ���� ��ũ�� ����� ��
		return 0; //�Լ��� �����Ѵ�.
	}

	while ((p != NULL)&&(p->key!=key)) //p�� ������� �ʰ� �ش� ����� ���� �Է¹��� Ű�� ���� �ʴٸ�
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
		if (pre->left == p)  // �θ����� ���� ����̸�
			pre->left = NULL;  //�θ� ����� ���� ��ũ�� ����ְ�
		else  //������ �����
			pre->right = NULL;  //�θ����� ������ ��ũ�� ����� ��
		free(p);  //p�� �޸𸮸� �����ϰ�
		return 0;  //�Լ��� �����Ѵ�.
	}

	printf("%d �� leafnode�� �ƴմϴ�.", p->key);  //���� �ܸ���尡 �ƴ϶�� �ȳ����� ��� �� ��
	return 0;  //�Լ� ����

}

Node* searchRecursive(Node* ptr, int key)  // reculsive ������� Ž��
{
	if (!ptr)  //���� Ʈ���� ����ִٸ�
		return NULL;  //NULL��ȯ
	if (ptr->key == key)  //�Է¹��� Ű�� ã�Ҵٸ�
		return ptr;  //�� Ű�� �ּ� ��ȯ
	else if(ptr->key > key)  // �Է¹��� Ű�� �ش� ����� ������ �۴ٸ�
		return searchRecursive(ptr->left, key);  // ����� ���ʳ��� ����Լ� ȣ��
	return searchRecursive(ptr->right, key);  // ũ�ٸ� ����� ������ ���� ����Լ� ȣ��
}

Node* searchIterative(Node* head, int key)  //Iterative ������� Ž��
{
	Node* p;  //Ž���� ���
	p = head->left;  //��尡 ��Ʈ��带 ����Ű���� ��

	while (p)  //Ʈ���� �������� �ɶ�����
	{
		if (p->key == key)  //Ž���� ��带 ã�Ҵٸ�
			return p;  //�ش� ����� �ּ� ��ȯ
		else if (p->key > key)  // ã�� ��尡 �ش� ����� ������ ������
			p = p->left;  //p�� ���� ��带 ����Ű���� �ϰ�
		else  //ũ�ٸ�
			p = p->right;  //p�� ������ ��带 ����Ű���� ��
	}

	return NULL;  //���� �ش� Ű�� ���ٸ� NULL�� ��ȯ
}
int freeBST(Node* head)  //�޸𸮸� �����ϴ� �Լ�
{
	Node* p;  //������ ���

	p = head->left;  // ��尡 ��Ʈ��带 ����Ű���� ��

	postorderfree(p);  // postorder������� Ʈ���� �޸𸮸� �����ϴ� �Լ� ȣ��
	free(head);  //Ʈ���� �� ����ٸ� ���������� �ص� ����� �޸� ����
}
void postorderfree(Node* ptr)  //postorder������� �޸𸮸� �����ϴ� �Լ�
{
	if (ptr)  //Ʈ���� ������� �ʴٸ�
	{
		postorderfree(ptr->left);  //����� ���� ���� ����Լ� ȣ��
		postorderfree(ptr->right);//����� ������ ���� ����Լ� ȣ��
		free(ptr);  // �ش� ����� �޸� ����
	}
}

