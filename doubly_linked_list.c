/*
 ============================================================================
 Name        : doubly_linked_list.c
 ============================================================================
 */

/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;



typedef struct Head {
    struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
    char command;
    int key;
    headNode* headnode = NULL;
    printf("2018068005 전아현 \n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Doubly Linked  List                        \n");
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

    return 1;
}


int initialize(headNode** h) {

    if ((*h) != NULL)    //만약 해당 연결리스트가 비어있지 않다면
        freeList(*h);  // 해당 연결리스트를 비워준다.
    (*h) = (headNode*)malloc(sizeof(headNode));  //이중포인터로 리스트의 처음을 받았으니 *를 이용하여 리스트를 동적으로 메모리 할당을 해준 후
    (*h)->first = NULL;  //연결리스트의 처음이 가리키는 값을 NULL로 만들어준다.

    return 1;  //프로그램을 종료한다.
}

int freeList(headNode* h) {
    listNode* p = h->first;  //리스트의 처음을 가리키는 포인터 구조체 생성
    listNode* pre = NULL;  //메모리 해제를 할 노드
    while (p != NULL)  //연결리스트가 끝날때까지
    {
        pre = p;  //pre에 이전 값을 넣고
        p = p->rlink;  // p가 다음 노드를 가리키도록 한 후
        free(pre);  //이전 노드의 메모리를 해제해준다.
    }
    free(h);  // 노드들의 메모리 해제가 끝났다면 연결리스트의 처음의 메모리를 해제한 후
    return 0;  //프로그램을 종료한다.
}


void printList(headNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while (p != NULL) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }

    printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //입력받은 키를 저장하기 위한 구조체 선언
    listNode* p;
    node->key = key;  // 키 값을 저장하고
    node->llink = NULL;  // 연결리스트의 양 옆에 가리키는 곳을 NULL로 만들어 준다.
    node->rlink = NULL;  //

    if (h->first == NULL) {  //만약 연결리스트가 공백이라면
        h->first = node;  // 연결리스트의 처음이 새로 저장한 키 값을 가리키도록 한다.
        return 0;
    }
    else  //리스트가 비어있지 않다면
    {
        p = h->first;  //p가 리스트의 처음을 가리키도록 한 후
        while (p->rlink != NULL)  //p가 연결리스트의 끝이 될 때까지
        {
            p = p->rlink;  //p가 다음 노드를 가리키도록 한다.
        }//p가 리스트의 마지막을 가리킨다면
        node->llink = p;  //새로 만들어진 키값의 왼쪽 링크가 연결리스트의 끝을 가리키도록 하고
        p->rlink = node;  //원래 연결리스트의 마지막 노드의 오른쪽 링크가 새로 만들어진 키값을 가리키도록 한다.

    }
    return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    listNode* p;  //리스트의 마지막을 가리킬 구조페 선언
    p = h->first; //p가 리스트의 처음을 가리키도록 한다.

    if (h->first == NULL) {  //만약 리스트가 공백리스트라면
        printf("비어있는 공백 연결리스트 입니다.\n");  //안내문을 출력한 후
        return 0; //프로그램을 종료한다.
    }
    else if (p->rlink == NULL)//공백리스트가 하나밖에 없다면
    {
        h->first = NULL;  // 연결리스트의 처음을 NULL로 만들어준 후
        free(p);  //처음 노드의 메모리를 해제한 후
        return 0;  //프로그램을 종료한다.
    }
    else { //공백리스트가 아니라면

        while (p->rlink != NULL) { //p가 연결리스트의 마지막을 가리킬 때까지
            p = p->rlink;  //p가 다음노드를 가리키게 한다.
        }// 마지막 노드를 찾았다면
        p->llink->rlink = NULL;// 마지막 노드의 이전에 있는 노드의 오른쪽 링크가 NULL을 가리키도록 한 후
        free(p);  //마지막 노드의 메모리를 삭제해준다.
    }

    return 0;  //프로그램을 종료한다.
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));  //입력받은 키의 정보를 저장할 변수
    node->key = key;  // 키 값을 저장하고
    node->llink = NULL;  // 연결리스트의 양 옆에 가리키는 곳을 NULL로 만들어 준다.
    node->rlink = NULL;

    if (h->first == NULL) {  //만약 연결리스트가 공백이라면
        h->first = node;  // 연결리스트의 처음이 새로 저장한 키 값을 가리키도록 한다.
        return 0;
    }

    node->rlink = h->first;  //키의 정보를 가지고 있는 노드의 오른쪽 링크가 리스트의 처음을 가리키도록 한 후
    node->rlink->llink = node; //원래 리스트의 처음에 있었던 노드의 왼쪽 노드가 키듸 정보를 가진 노드를 가리키게 한 후
    h->first = node;//리스트의 처음이 노드를 가리키도록 한다.
    return 0;  //프로그램을 종료한다.
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    listNode* p;  //리스트의 처음을 가리킬 변수
    p = h->first;  //p가 리스트의 처응을 가리키도록 한 후

    if (h->first == NULL) {  //만약 리스트가 공백리스트라면
        printf("비어있는 공백 연결리스트 입니다.\n");  //안내문을 출력한 후
        return 0; //프로그램을 종료한다.
    }
    else if (p->rlink == NULL)//공백리스트가 하나밖에 없다면
    {
        h->first = NULL;  // 연결리스트의 처음을 NULL로 만들어준 후
        free(p);  //처음 노드의 메모리를 해제한 후
        return 0;  //프로그램을 종료한다.
    }
    p->rlink->llink = NULL;  //삭제할 다음노드의 왼쪽 링크를 NULL로 만들어준 후
    h->first = p->rlink;  //리스트의 처음이 삭제할 노드의 다음 노드를 가리키게 하고
    p->rlink = NULL;  //삭제할 리스트의 링크를 비워준 후
    p->llink = NULL;
    free(p);  //삭제할 리스트의 메모리를 삭제한다.
    return 0;//프로그램을 종료한다.
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

    listNode* p; // 연결리스트의 처음을 가리킬 변수
    listNode* pre;  // 역전에 필요한 변수
    listNode* mid;
    if (h->first == NULL) {  //리스트가 공백리스트라면
        printf("nothing to invert...\n");  //안내문 출력 후
        return 0;//프로그램 종료
    }
    else if(h->first->rlink == NULL)  //만약 리스트가 하나밖에 없다면
    {
        return 0;  //프로그램 종료
    }
    p = h->first;  //리스트의 처음을 가리키도록 한후
    while (p != NULL)  //리스트가 마지막이 될때까지
    {
        pre = p;  //pre가 p를 가리키도록 하고
        mid = pre->rlink;  //mid가 그 다음 노드를 가리키도록 한다.
        pre->rlink = pre->llink;  //pre의 오른쪽 링크가 왼쪽링크를 가리키도록 한후
        pre->llink = mid;  // pre의 왼쪽 링크가  pre의 다음 노드를 가리키도록 하고
        p = mid;  //p가 다음 노드를 가리키도록 한다.
    }

    h->first = pre;  //마지막으로 연결리스트의 처음이 pre를 가리키도록 한 후



    return 0;  //프로그램을 종료한다.
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //입력받은 키 정보를 저장하는 변수
    listNode* p;  //리스트의 처음을 전달받을 변수
    listNode* pre;  //리스트의 처음을 전달받을 변수
    node->key = key;  //입력받은 키를 노드에 저장
    node->llink = NULL;  //노드의 왼쪽 오른쪽 링크를 NULL로 만들어줌
    node->rlink = NULL;

    if (h->first == NULL) {  //만약 연결리스트가 공백이라면
        h->first = node;  // 연결리스트의 처음이 새로 저장한 키 값을 가리키도록 한다.
        return 0;//프로그램 종료
    }
    p = h->first; //리스트의 처음을 가리키고

    while (p!=NULL) { //p의 마지막까지

       if(p->key>=key){  //p의 키가 입력받은 키보다 크거나 같을때

           if (p == h->first) {//삽입할 위치가 리스트 처음의 앞이라면
                node->rlink = h->first; //입력받은 키값의 노드의 오른쪽 링크가 연결리스트의 첫번째 노드를 가리키도록 하고
                node->rlink->llink = node;  //연결리스트의 첫번째 노드의 왼쪽 노드가 입력받은 노드를 가리키도록 한 후
                node->llink = NULL;  //입력받은 노드의 왼쪽 링크를 NULL로 만들어준 후
                h->first = node;  //연결리스트의 처음이 입력받은 노드를 가리키도록 한다.
            }
            else{  //아니라면
               node->rlink =p;  //입력받은 노드의 오른쪽 링크가 p를 가리키도록 하고
               p->llink->rlink = node;  //p의 이전 노드의 오른쪽 링크가 입력받은 노드를 가리키게 한 후
               node->llink = p->llink;  //입력받은 노드의 왼쪽 링크가 p의 이전 노드를 가리키도록 한다.
               p->llink = node;  //p의 왼쪽 링크가 입력받은 노드를 가리키도록 한다.
            }
           return 0;  //프로그램을 종료한다.
        }
       pre = p;  //pre가 p를 가리키도록 한 후
       p = p->rlink; //p가 다음 노드를 가리키게 한다.
    } //만약 마지막까지 삽입 위치를 못찾았다면
    node->llink = pre;  //노드의 왼쪽 링크가 마지막 노도를 가리키도록 하고
    pre->rlink = node;  //마지막 노드의 오른쪽 링크가 입력받은 노드를 가리키도록 한다.


    return 0;  //프로그램을 종료시킨다.
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    listNode* p;  //리스트의 처음을 전달받을 변수


    if (h->first == NULL)  //공백리스트라면
    {
        printf("공백 리스트 입니다.\n");//안내문을 출력하고
        return 0;  //함수를 종료한다.
    }  //공백리스트가 아니라면

    p = h->first; //리스트의 처음을 가리키고
    while (p != NULL)  //p가 마지막일때까지
    {
        if (p->key == key)  //노드의 키값이 받은 키값과 같을때
        {
            if (p == h->first)//만약 삭제할 위치가 처음이라면
            {
                h->first = p->rlink;  //리스트의 처음이 p의 오른쪽 링크를 가리키도록 하고
                p->rlink->llink =NULL;  //p의 다음 링크가 NULL이 되도록 하고
                free(p);  //p의 메모리를 해제해준다.
                return 0;  //프로그램을 종료한다.
            }
            else if (p->rlink == NULL)  //마지막 노드라면
            {
                p->llink->rlink = NULL;  //p의 이전 노드의 오른쪽 링크를 NULL로 만들어 준후
                free(p);  //메모리를 해제해주고
                return 0;  //프로그래을 종료한다.
            }
            else  //중간이라면
            {
                p->llink->rlink = p->rlink;  //p의 이전 노드의 오른쪽 링크가 다음 노드를 가리키도록 하고
                p->rlink->llink = p->llink;  //p의 다음 노드의 왼쪽 링크가 p의 왼쪽 노드를 가리키도록 한 후
                free(p);  //메모리를 해제해준다.
                return 0;
            }
        }
        p = p->rlink;  //p가 다음노드를 가리키도록 한다.
    }

    printf("%d 는 리스트에 존재하지 않습니다.\n", key);
    return 1;
}
