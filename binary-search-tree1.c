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
void postorderfree(Node* ptr);  // 트리의 메모리를 해제하는 함수 선언

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("전아현 2018068005\n");
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

	printf("프로그램 종료 \n");
	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)  //헤드노드가 비어있지 않다면
		freeBST(*h);   //해당 해드노드를 비워준 후 다음 동작을 실행한다.

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  // 헤드 노드에 동적으로 메모리를 할당한 후
	(*h)->left = NULL;	/* root */  //왼쪽 노드를 널로 만들어주고
	(*h)->right = *h;  //오른쪽 링크가 헤드노드를 가리키도록 한다.
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)  // 왼쪽 노드 -> 부모노드 -> 오른쪽 노드 순으로 탐색
{
	if (ptr)  { //노드가 비어있지 않다면
		inorderTraversal(ptr->left);  //노드의 왼쪽 노드로 재귀함수 호출
		printf("%5d", ptr->key);  // 해당 노드의 값 출력
		inorderTraversal(ptr->right);   //노드의 오른쪽 노드로 재귀함수 호출
	}
}

void preorderTraversal(Node* ptr)  //부모노드 -> 왼쪽 노드 -> 오른쪽 노드 순으로 탐색
{
	if (ptr) {   //노드가 비어있지 않다면
		printf("%5d", ptr->key);  //해당 노드의 값을 출력
		preorderTraversal(ptr->left);  //노드의 왼쪽 노드로 재귀함수 호출
		preorderTraversal(ptr->right);  //노드의 오른쪽 노드로 재귀함수 호출
	}
}

void postorderTraversal(Node* ptr)  //왼쪽 노드-> 오른쪽 노드 -> 부모 노드 순으로 탐색
{
	if (ptr)  //노드가 비어있지 않다면
	{
		postorderTraversal(ptr->left);  //왼쪽 노드로 재귀함수 호출
		postorderTraversal(ptr->right);  //오른쪽 노드로 재귀함수 호출
		printf("%5d", ptr->key);  // 해당 노드의 값을 출력
	}
}


int insert(Node* head, int key)   // 입력받은 키를 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));  //입력받은 키를 저장할 변수
	Node* p;  //트리를 탐색하는데 필요한 변수
	newNode->key = key;  //입력받은 키를 저장한다.
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL)  //만약 트리가 비어있다면
	{
		head->left = newNode;  //헤드노드의 왼쪽 링크가 입력받은 노드를 가리키도록 한다.
		return 1;  //1을 반환해준다.
	}
	p = head->left;  //p가 루프노드를 가리키도록 한다.
	while (1)// 조건을 만족할 때까지 반복한다.
	{
		if (p->key > key)  //만약 입력받은 키가 해당 노드의 값보다 작고
		{
			if (p->left == NULL)  // 해당 노드의 왼쪽이 비어있다면
			{
				p->left = newNode;  //노드의 왼쪽에 입력받은 키를 삽입하고
				return 1;  //함수 종료
			}
			else  //비어있지 않다면
			{
				p = p->left;  //p가 노드의 왼쪽 노드를 가리키도록 함
			}
		}
		else if (p->key < key)  //입력받은 키가 해당 노드의 값보다 크고
		{
			if (p->right == NULL)  //해당 노드의 오른쪽이 비어있다면
			{
				p->right = newNode;  //노드의 오른쪽에 입력받은 키를 삽입하고
				return 1;  //함수 종료
			}
			else  //비어있지 않다면
			{
				p = p->right;  //p가 노드의 오른쪽을 가리키도록 함
			}
		}
		else if(p->key == key)  //만약 입력받은 키가 같다면
		{
			printf("같은 키가 존재합니다.\n");  //안내문 출력한 후
			return 1;  //함수 종료
		}
	}

}

int deleteLeafNode(Node* head, int key) //입력받은 단말노드를 삭제하는 함수
{
	Node* p;  //삭제할 노드
	Node* pre;  //삭제할 노드의 부모 노드

	if (head->left == NULL)  //만약 비어있는 트리라면
	{
		printf("해당 트리는 비어있습니다.\n");  //안내문 출력 후
		return 0; //함수 종료
	}
	p = head->left;  //p가 루트노드를 가리키도록 한 후
	if (p->key == key && p->left == NULL && p->right == NULL) //트리의 첫번째 노드가 삭제할 노드이고 단말노드라면
	{
		free(p);  //p를 메모리를 해제하고
		head->left = NULL;  // 헤드노드의 왼쪽 링크를 비워준 후
		return 0; //함수를 종료한다.
	}

	while ((p != NULL)&&(p->key!=key)) //p가 비어있지 않고 해당 노드의 값이 입력받은 키와 같지 않다면
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
		if (pre->left == p)  // 부모노드의 왼쪽 노드이면
			pre->left = NULL;  //부모 노드의 왼쪽 링크를 비워주고
		else  //오른쪽 노드라면
			pre->right = NULL;  //부모노드의 오른쪽 링크를 비워준 후
		free(p);  //p를 메모리를 해제하고
		return 0;  //함수를 종료한다.
	}

	printf("%d 는 leafnode가 아닙니다.", p->key);  //만약 단말노드가 아니라면 안내문을 출력 한 후
	return 0;  //함수 종료

}

Node* searchRecursive(Node* ptr, int key)  // reculsive 방식으로 탐색
{
	if (!ptr)  //만약 트리가 비어있다면
		return NULL;  //NULL반환
	if (ptr->key == key)  //입력받은 키를 찾았다면
		return ptr;  //그 키의 주소 반환
	else if(ptr->key > key)  // 입력받은 키가 해당 노드의 값보다 작다면
		return searchRecursive(ptr->left, key);  // 노드의 왼쪽노드로 재귀함수 호출
	return searchRecursive(ptr->right, key);  // 크다면 노드의 오른쪽 노드로 재귀함수 호출
}

Node* searchIterative(Node* head, int key)  //Iterative 방식으로 탐색
{
	Node* p;  //탐색할 노드
	p = head->left;  //노드가 루트노드를 가리키도록 함

	while (p)  //트리가 마지막이 될때까지
	{
		if (p->key == key)  //탐색할 노드를 찾았다면
			return p;  //해당 노드의 주소 반환
		else if (p->key > key)  // 찾는 노드가 해당 노드의 값보다 작으면
			p = p->left;  //p가 왼쪽 노드를 가리키도록 하고
		else  //크다면
			p = p->right;  //p가 오른쪽 노드를 가리키도록 함
	}

	return NULL;  //만약 해당 키가 없다면 NULL을 반환
}
int freeBST(Node* head)  //메모리를 해제하는 함수
{
	Node* p;  //삭제할 노드

	p = head->left;  // 노드가 루트노드를 가리키도록 함

	postorderfree(p);  // postorder방식으로 트리의 메모리를 해제하는 함수 호출
	free(head);  //트리가 다 비었다면 마지막으로 해드 노드의 메모리 해제
}
void postorderfree(Node* ptr)  //postorder방식으로 메모리를 해제하는 함수
{
	if (ptr)  //트리가 비어있지 않다면
	{
		postorderfree(ptr->left);  //노드의 왼쪽 노드로 재귀함수 호출
		postorderfree(ptr->right);//노드의 오른쪽 노드로 재귀함수 호출
		free(ptr);  // 해당 노드의 메모리 해제
	}
}

