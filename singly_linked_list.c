/*
 ============================================================================
 Name        : singly_linked_list.c
 ============================================================================
 */

/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {  // 연결리스트를 정의하는 구조체
    int key;  //연결리스트의 값
    struct Node* link;  //연결리스트의 다음을 가리킴  //존재하지 않은 타입이어서 앞에 struct를 붙여준다.
} listNode;

typedef struct Head {  //연결리스트의 처음을 정의하는 구조체
    struct Node* first;  //처음 노드를 가리킴 //존재하지 않은 타입이어서 앞에 struct를 붙여준다.
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //초기화시켜주는 함수
int freeList(headNode* h);  //동적으로 할당받은 리스트 메모리를 해제시켜주는 함수

int insertFirst(headNode* h, int key);  //첫번째 노드에 키를 삽입해주는 함수
int insertNode(headNode* h, int key);  //입력받은 키가 들어갈 위치를 탐색하여 삽입하는 함수
int insertLast(headNode* h, int key);  //입력받은 키를 마지막 노드에 삽입하는 함수

int deleteFirst(headNode* h);  // 첫번째 노드를 삭제하는 함수
int deleteNode(headNode* h, int key);  //입력받은 키를 찾아 있으면 삭제하고 없으면 안내문을 출력하는 함수
int deleteLast(headNode* h);  //마지막 노드를 삭제하는 함수
int invertList(headNode* h);  //리스트를 역으로 바꿔주는 함수

void printList(headNode* h);  //리스트를 출력해주는 함수

int main()
{
    char command;  //메뉴를 입력받을 변수
    int key;  //키를 입력받을 변수
    headNode* headnode = NULL;  //연결리스트

    printf("전아현 2018068005\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        fflush(stdout);
        scanf(" %c", &command);  //메뉴 입력받기

        switch (command) {  //스위치 문을 사용하여
        case 'z': case 'Z':  //초기화메뉴 선택시
            headnode = initialize(headnode);  //초기화 함수 호출
            break;  //스위치문 탈출
        case 'p': case 'P':  //리스트를 출력하길 원하면
            printList(headnode);  // 리스트 출력하는 함수 호출
            break;  //스위치문 탈출
        case 'i': case 'I':  //삽입을 원하면
            printf("Your Key = ");  // 안내문 출력후
            fflush(stdout);
            scanf("%d", &key);  //키를 입력받고
            insertNode(headnode, key);  //키를 삽입하는 함수 호출
            break;  //스위치 문 탈출
        case 'd': case 'D':  //키를 삭제하길 원한다면
            printf("Your Key = ");  //키를 입력받고
            fflush(stdout);
            scanf("%d", &key);
            deleteNode(headnode, key);  //키를 삭제하는 함수 호출
            break;  //스위치문 탈출
        case 'n': case 'N':  //마지막에 노드를 삽입하길 원하면
            printf("Your Key = ");  //키를 입력받고
            fflush(stdout);
            scanf("%d", &key);
            insertLast(headnode, key);  //함수를 호출하고
            break;  //스위치 문 탈출
        case 'e': case 'E':  // 마지막 노드를 삭제하길 원하면
            deleteLast(headnode);  //함수 호출하고
            break;  //스위치문 탈출
        case 'f': case 'F':  // 첫번째에 노드를 삽입하길 원하면
            printf("Your Key = ");
            fflush(stdout);
            scanf("%d", &key);  //키를 입력받은 뒤
            insertFirst(headnode, key);  //함수를 호출하고
            break;  //스위치문을 탈출한다.
        case 't': case 'T':  //첫번째 노드를 삭제하길 원한다면
            deleteFirst(headnode);  //함수를 호출하고
            break; //스위치문 탈출
        case 'r': case 'R':  //리스트의 순서를 역방향으로 바꾸고 싶다면
            invertList(headnode);  // 함수 호출하고
            break;  //스위치문 탈출
        case 'q': case 'Q':  //리스트를 종료하길 원한다면
            freeList(headnode);  // 리스트의 메모리를 해제해준 뒤
            break; //스위치문 탈출
        default:  //잘못 입력했다면
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //안내문 출력
            break;
        }

    } while (command != 'q' && command != 'Q');  //종료하길 원한다면 반복문 탈출

    printf("프로그램이 종료되었습니다\n");
    return 1;
}

headNode* initialize(headNode* h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (h != NULL)
        freeList(h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode* h) {
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제되어야 함.
     */
    listNode* p = h->first;  //리스트를 가리키는 변수 선언

    listNode* prev = NULL;  //삭제할 리스트를 가리킬 변수
    while (p != NULL) {  //리스트가 공백이 아니면
        prev = p;  //prev가 이전 노드를 가리키게 하고
        p = p->link;  //p가 그 다음 노드를 가리키게 한 후
        free(prev);  //prev를 동적 메모리 해제 해준다.
    }
    free(h);  //다 끝났으면 첫번째 노드로 메모리 해제해준 후
    return 0;  // 함수를 종료한다.
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));  //넘겨받은 값을 가리킬 노드
    node->key = key;  //노드의 값을 변경

    node->link = h->first;  // 노드의 헤드가 가리키는 값을 노드가 가리키도록 하고
    h->first = node;  //노드의 헤드가 node를 가리키도록 한다.

    return 0; //프로그램을 종료한다.
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트의 head가 가리키는 값을 받아 리스트를 탐색하기 위한 리스트
    listNode* NEW= (listNode*)malloc(sizeof(listNode));  //키 값을 저장할 리스트
    listNode* Pre = (listNode*)malloc(sizeof(listNode));  //리스트를 삽입할 때 이전 리스트값을 저장하는 리스트
    NEW->key = key;  //NEW 리스트에 키값을 저장한다.
    NEW->link = NULL;
    node = h->first;  //
    Pre =h->first;

    if (h->first==NULL)  //리스트가 공백리스트라면
    {
        h->first = NEW;  //리스트의 처음이 NEW를 가리키도록 한다.
        return 0;  //프로그램 종료
    }
    while (node!=NULL)  //공백리스트가 아니고
    {
        if (NEW->key <= node->key)  //입력받은 키가 노도가 가지고 있는 값보다 작을때
        {
            if (node = h->first)//만약 삽입할 위치가 첫노드 앞쪽이라면
            {
                h->first = NEW;  //리스트의 처음이 NEW를 가리키도록 한 후
                NEW->link = node;  //삽입한 리스트가 node를 가리키도록 해준다.
            }
            else//삽입할 위치가 중간 쯤이라면
            {
                NEW->link = node->link;//삽입할 키 값이 그 위치의 다음 노드를 가리키도록 하고
                Pre->link = NEW;  //삽입할 위치의 앞 노드가 NEW를 가리키도록 한다.
            }
            return 0;  //함수를 종료한다.
        }  //아니라면
        Pre = node;  //Pre가 node를 가리키도록 하고
        node = node->link;  //node가 다음 값을 가리키도록 한다.
    }// 키 값이 마지막 노드에 삽입되어야 한다면
    Pre->link = NEW;  //Pre의 링크가 새로운 노드를 가리키도록 한다.
    return 0;  //함수를 종료한다.
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    listNode* node = h->first;//리스트의 head가 가리키는 값을 받아 리스트를 탐색하기 위한 리스트 선언 및 동적 할당
    listNode* NEW=(listNode*)malloc(sizeof(listNode));  //새로운 키 값을 입력받을 리스트 선언 및 동적 할당

    NEW->key = key;  //키 값을 리스트에 저장한다.
    NEW->link = NULL;


    if (h->first==NULL)  //공백리스트 라면
    {
        h->first = NEW;  //리스트의 처음이 NEW를 가리키도록 하고
        return 0; //프로그램을 종료한다.
    }
    else  //공백이 아니라면
    {
        while (node->link != NULL)  //list의 마지막을 찾을 때까지
            node = node->link;  //node의 주소를 이동해주고
        node -> link = NEW;  //마지막을 찾았다면 마지막 링크가 NEW를 가리키도록 해준다.
    }

    return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    listNode* node = h->first; //리스트의 head가 가리키는 값을 받아 리스트를 탐색하기 위한 리스트 선언 및 동적 할당

    if (h->first==NULL)  //공백리스트라면
    {
        printf("공백 리스트 입니다.\n");//안내문을 출력하고
        return 0;  //함수를 종료한다.
    }  //공백리스트가 아니라면
    h->first = node->link;  // 리스트의 처음이 가리키는 주소를 첫번째 노드의 다음 노드를 가리키도록 해주고
    free(node);  //삭제할 노드의 동적메모리를 해제한다.

    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    listNode* node = h->first;//리스트의 head가 가리키는 값을 받아 리스트를 탐색하기 위한 리스트 선언 및 동적 할당
    listNode* Pre;  //삭제할 리스트의 이전 리스트값을 저장하는 리스트
    Pre = h->first;

    if (h->first==NULL)  //공백리스트라면
    {
        printf("공백 리스트 입니다.\n");//안내문을 출력하고
        return 0;  //함수를 종료한다.
    }  //공백리스트가 아니라면

    while (node != NULL)  //공백리스트가 아니라면 반복
    {
        if (node->key == key)  //노드의 키값이 받은 키값과 같을때
        {
            if (node == h->first)//만약 삭제할 위치가 첫노드라면
            {
                h->first = node->link;  //리스트의 처음이 node의 다음을 가리키도록 한 후
                free(node);  //삭제할 노드의 동적메모리를 해제한다.
                return 0;  //함수를 종료한다.
            }
            else if (node->link == NULL) //삭제할 노드가 마지막 노드라면
            {
                Pre->link = NULL;  //삭제할 노드를 가리키는 Pre를 NULL을 가리키도록 하고
                free(node);  //삭제할 노드를 메모리 해제 시킨다.
                return 0;// 프로그램을 종료한다.
            }
            else //삭제할 노드의 위치가 중간 쯤이라면
            {
                Pre->link = node->link;  //Pre가 가리키는 값을 node의 다음으로 바꿔주고
                free(node);  //node값의 메모리를 해제시킨 후
                return 0;  //함수를 종료한다.
            }
        }  //아니라면

        Pre = node;  //Pre가 기존의 node의 앞 노드를 가리키도록 하고
        node = node->link;  //노드가 그 다음 값을 가리키도록 한다.
    }

    printf("%d 는 리스트에 존재하지 않습니다.\n",key);

    return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    listNode* node = h->first;//리스트의 head가 가리키는 값을 받아 리스트를 탐색하기 위한 리스트 선언 및 동적 할당
    listNode* Pre;  //삭제할 리스트의 이전 리스트값을 저장하는 리스트


    if (h->first ==NULL)// 공백리스트라면
    {
        printf("공백 리스트 입니다.\n");//안내문을 출력하고
        return 0;  //함수를 종료한다.
    }
    else if (node->link == NULL)  //리스트에 노드가 하나만 존재한다면
    {
        h->first = NULL;  //리스트의 처음이 가리키는 곳을 비워주고
        free(node);  //해당 노드의 메모리를 해제시켜준다.
    }// 아니라면
    while (node->link!=NULL)//node가 마지막일때까지  반복
    {
        Pre= node;//삭제하기 이전의 값을 가리키도록 하고
        node = node->link; //노드가 다음 노드를 가리키도록 한다.
    }
    Pre->link = NULL;  //삭제할 노드의 이전 리스트의 링크가 NULL을 가리키도록 하고
    free(node);  //삭제할 노드의 메모리를 해제시켜준다.

    return 0;  //프로그램을 종료한다.
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* node ;//리스트의 첫번째 노드
    listNode* Pre;  //리스트를 바꿔줄 노드
    listNode* mid; //바꿀 리스트의 중간을 가지고 있는 노드

    node = h->first; //노드가 리스트의 첫번째를 가리키도록 한다.
    Pre = NULL;
    mid = NULL;

    while (node != NULL)  //리스트의 마지막 노드가 아닐때 까지
    {
        Pre = mid;  //Pre를 Mid로 변경해주고
        mid = node;  //mid가 node를 가리키게 한다.
        node = node->link;// 노드가 다음 노드를 가리키게 만든 후
        mid->link = Pre;  //mid가 가리키는 곳을 Pre로 변경해준다.
    }
    h->first = mid;  //역순으로 배치가 완료되었다면 리스트의 처음을 리스트의 마지막으로 변경해준다.


    return 0;  //함수를 종료한다.
}


void printList(headNode* h) {  //리스트를 출력해주는 함수
    int i = 0;
    listNode* p; //출력할 리스트를 가리킬 변ㅅ

    printf("\n---PRINT\n");

    if (h == NULL) {  //공백리스트라면
        return;//함수를 종료한다.
    }

    p = h->first;  //공백리스트가 아니라면 p가 리스트를 가리키도록 하고

    while (p != NULL) {  //p가 마지막 노드가 아니라면

        printf("[ [%d]=%d ] ", i, p->key);  // 키 값을 출력한다.
        p = p->link;  //p가 다음 키를 가리키도록 한 후
        i++;
    }

    printf("  items = %d\n", i);//키의 총 수 출력
}
