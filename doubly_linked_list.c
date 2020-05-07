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
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;



typedef struct Head {
    struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
    printf("2018068005 ������ \n");

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

    if ((*h) != NULL)    //���� �ش� ���Ḯ��Ʈ�� ������� �ʴٸ�
        freeList(*h);  // �ش� ���Ḯ��Ʈ�� ����ش�.
    (*h) = (headNode*)malloc(sizeof(headNode));  //���������ͷ� ����Ʈ�� ó���� �޾����� *�� �̿��Ͽ� ����Ʈ�� �������� �޸� �Ҵ��� ���� ��
    (*h)->first = NULL;  //���Ḯ��Ʈ�� ó���� ����Ű�� ���� NULL�� ������ش�.

    return 1;  //���α׷��� �����Ѵ�.
}

int freeList(headNode* h) {
    listNode* p = h->first;  //����Ʈ�� ó���� ����Ű�� ������ ����ü ����
    listNode* pre = NULL;  //�޸� ������ �� ���
    while (p != NULL)  //���Ḯ��Ʈ�� ����������
    {
        pre = p;  //pre�� ���� ���� �ְ�
        p = p->rlink;  // p�� ���� ��带 ����Ű���� �� ��
        free(pre);  //���� ����� �޸𸮸� �������ش�.
    }
    free(h);  // ������ �޸� ������ �����ٸ� ���Ḯ��Ʈ�� ó���� �޸𸮸� ������ ��
    return 0;  //���α׷��� �����Ѵ�.
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //�Է¹��� Ű�� �����ϱ� ���� ����ü ����
    listNode* p;
    node->key = key;  // Ű ���� �����ϰ�
    node->llink = NULL;  // ���Ḯ��Ʈ�� �� ���� ����Ű�� ���� NULL�� ����� �ش�.
    node->rlink = NULL;  //

    if (h->first == NULL) {  //���� ���Ḯ��Ʈ�� �����̶��
        h->first = node;  // ���Ḯ��Ʈ�� ó���� ���� ������ Ű ���� ����Ű���� �Ѵ�.
        return 0;
    }
    else  //����Ʈ�� ������� �ʴٸ�
    {
        p = h->first;  //p�� ����Ʈ�� ó���� ����Ű���� �� ��
        while (p->rlink != NULL)  //p�� ���Ḯ��Ʈ�� ���� �� ������
        {
            p = p->rlink;  //p�� ���� ��带 ����Ű���� �Ѵ�.
        }//p�� ����Ʈ�� �������� ����Ų�ٸ�
        node->llink = p;  //���� ������� Ű���� ���� ��ũ�� ���Ḯ��Ʈ�� ���� ����Ű���� �ϰ�
        p->rlink = node;  //���� ���Ḯ��Ʈ�� ������ ����� ������ ��ũ�� ���� ������� Ű���� ����Ű���� �Ѵ�.

    }
    return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
    listNode* p;  //����Ʈ�� �������� ����ų ������ ����
    p = h->first; //p�� ����Ʈ�� ó���� ����Ű���� �Ѵ�.

    if (h->first == NULL) {  //���� ����Ʈ�� ���鸮��Ʈ���
        printf("����ִ� ���� ���Ḯ��Ʈ �Դϴ�.\n");  //�ȳ����� ����� ��
        return 0; //���α׷��� �����Ѵ�.
    }
    else if (p->rlink == NULL)//���鸮��Ʈ�� �ϳ��ۿ� ���ٸ�
    {
        h->first = NULL;  // ���Ḯ��Ʈ�� ó���� NULL�� ������� ��
        free(p);  //ó�� ����� �޸𸮸� ������ ��
        return 0;  //���α׷��� �����Ѵ�.
    }
    else { //���鸮��Ʈ�� �ƴ϶��

        while (p->rlink != NULL) { //p�� ���Ḯ��Ʈ�� �������� ����ų ������
            p = p->rlink;  //p�� ������带 ����Ű�� �Ѵ�.
        }// ������ ��带 ã�Ҵٸ�
        p->llink->rlink = NULL;// ������ ����� ������ �ִ� ����� ������ ��ũ�� NULL�� ����Ű���� �� ��
        free(p);  //������ ����� �޸𸮸� �������ش�.
    }

    return 0;  //���α׷��� �����Ѵ�.
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));  //�Է¹��� Ű�� ������ ������ ����
    node->key = key;  // Ű ���� �����ϰ�
    node->llink = NULL;  // ���Ḯ��Ʈ�� �� ���� ����Ű�� ���� NULL�� ����� �ش�.
    node->rlink = NULL;

    if (h->first == NULL) {  //���� ���Ḯ��Ʈ�� �����̶��
        h->first = node;  // ���Ḯ��Ʈ�� ó���� ���� ������ Ű ���� ����Ű���� �Ѵ�.
        return 0;
    }

    node->rlink = h->first;  //Ű�� ������ ������ �ִ� ����� ������ ��ũ�� ����Ʈ�� ó���� ����Ű���� �� ��
    node->rlink->llink = node; //���� ����Ʈ�� ó���� �־��� ����� ���� ��尡 Ű�� ������ ���� ��带 ����Ű�� �� ��
    h->first = node;//����Ʈ�� ó���� ��带 ����Ű���� �Ѵ�.
    return 0;  //���α׷��� �����Ѵ�.
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
    listNode* p;  //����Ʈ�� ó���� ����ų ����
    p = h->first;  //p�� ����Ʈ�� ó���� ����Ű���� �� ��

    if (h->first == NULL) {  //���� ����Ʈ�� ���鸮��Ʈ���
        printf("����ִ� ���� ���Ḯ��Ʈ �Դϴ�.\n");  //�ȳ����� ����� ��
        return 0; //���α׷��� �����Ѵ�.
    }
    else if (p->rlink == NULL)//���鸮��Ʈ�� �ϳ��ۿ� ���ٸ�
    {
        h->first = NULL;  // ���Ḯ��Ʈ�� ó���� NULL�� ������� ��
        free(p);  //ó�� ����� �޸𸮸� ������ ��
        return 0;  //���α׷��� �����Ѵ�.
    }
    p->rlink->llink = NULL;  //������ ��������� ���� ��ũ�� NULL�� ������� ��
    h->first = p->rlink;  //����Ʈ�� ó���� ������ ����� ���� ��带 ����Ű�� �ϰ�
    p->rlink = NULL;  //������ ����Ʈ�� ��ũ�� ����� ��
    p->llink = NULL;
    free(p);  //������ ����Ʈ�� �޸𸮸� �����Ѵ�.
    return 0;//���α׷��� �����Ѵ�.
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

    listNode* p; // ���Ḯ��Ʈ�� ó���� ����ų ����
    listNode* pre;  // ������ �ʿ��� ����
    listNode* mid;
    if (h->first == NULL) {  //����Ʈ�� ���鸮��Ʈ���
        printf("nothing to invert...\n");  //�ȳ��� ��� ��
        return 0;//���α׷� ����
    }
    else if(h->first->rlink == NULL)  //���� ����Ʈ�� �ϳ��ۿ� ���ٸ�
    {
        return 0;  //���α׷� ����
    }
    p = h->first;  //����Ʈ�� ó���� ����Ű���� ����
    while (p != NULL)  //����Ʈ�� �������� �ɶ�����
    {
        pre = p;  //pre�� p�� ����Ű���� �ϰ�
        mid = pre->rlink;  //mid�� �� ���� ��带 ����Ű���� �Ѵ�.
        pre->rlink = pre->llink;  //pre�� ������ ��ũ�� ���ʸ�ũ�� ����Ű���� ����
        pre->llink = mid;  // pre�� ���� ��ũ��  pre�� ���� ��带 ����Ű���� �ϰ�
        p = mid;  //p�� ���� ��带 ����Ű���� �Ѵ�.
    }

    h->first = pre;  //���������� ���Ḯ��Ʈ�� ó���� pre�� ����Ű���� �� ��



    return 0;  //���α׷��� �����Ѵ�.
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //�Է¹��� Ű ������ �����ϴ� ����
    listNode* p;  //����Ʈ�� ó���� ���޹��� ����
    listNode* pre;  //����Ʈ�� ó���� ���޹��� ����
    node->key = key;  //�Է¹��� Ű�� ��忡 ����
    node->llink = NULL;  //����� ���� ������ ��ũ�� NULL�� �������
    node->rlink = NULL;

    if (h->first == NULL) {  //���� ���Ḯ��Ʈ�� �����̶��
        h->first = node;  // ���Ḯ��Ʈ�� ó���� ���� ������ Ű ���� ����Ű���� �Ѵ�.
        return 0;//���α׷� ����
    }
    p = h->first; //����Ʈ�� ó���� ����Ű��

    while (p!=NULL) { //p�� ����������

       if(p->key>=key){  //p�� Ű�� �Է¹��� Ű���� ũ�ų� ������

           if (p == h->first) {//������ ��ġ�� ����Ʈ ó���� ���̶��
                node->rlink = h->first; //�Է¹��� Ű���� ����� ������ ��ũ�� ���Ḯ��Ʈ�� ù��° ��带 ����Ű���� �ϰ�
                node->rlink->llink = node;  //���Ḯ��Ʈ�� ù��° ����� ���� ��尡 �Է¹��� ��带 ����Ű���� �� ��
                node->llink = NULL;  //�Է¹��� ����� ���� ��ũ�� NULL�� ������� ��
                h->first = node;  //���Ḯ��Ʈ�� ó���� �Է¹��� ��带 ����Ű���� �Ѵ�.
            }
            else{  //�ƴ϶��
               node->rlink =p;  //�Է¹��� ����� ������ ��ũ�� p�� ����Ű���� �ϰ�
               p->llink->rlink = node;  //p�� ���� ����� ������ ��ũ�� �Է¹��� ��带 ����Ű�� �� ��
               node->llink = p->llink;  //�Է¹��� ����� ���� ��ũ�� p�� ���� ��带 ����Ű���� �Ѵ�.
               p->llink = node;  //p�� ���� ��ũ�� �Է¹��� ��带 ����Ű���� �Ѵ�.
            }
           return 0;  //���α׷��� �����Ѵ�.
        }
       pre = p;  //pre�� p�� ����Ű���� �� ��
       p = p->rlink; //p�� ���� ��带 ����Ű�� �Ѵ�.
    } //���� ���������� ���� ��ġ�� ��ã�Ҵٸ�
    node->llink = pre;  //����� ���� ��ũ�� ������ �뵵�� ����Ű���� �ϰ�
    pre->rlink = node;  //������ ����� ������ ��ũ�� �Է¹��� ��带 ����Ű���� �Ѵ�.


    return 0;  //���α׷��� �����Ų��.
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
    listNode* p;  //����Ʈ�� ó���� ���޹��� ����


    if (h->first == NULL)  //���鸮��Ʈ���
    {
        printf("���� ����Ʈ �Դϴ�.\n");//�ȳ����� ����ϰ�
        return 0;  //�Լ��� �����Ѵ�.
    }  //���鸮��Ʈ�� �ƴ϶��

    p = h->first; //����Ʈ�� ó���� ����Ű��
    while (p != NULL)  //p�� �������϶�����
    {
        if (p->key == key)  //����� Ű���� ���� Ű���� ������
        {
            if (p == h->first)//���� ������ ��ġ�� ó���̶��
            {
                h->first = p->rlink;  //����Ʈ�� ó���� p�� ������ ��ũ�� ����Ű���� �ϰ�
                p->rlink->llink =NULL;  //p�� ���� ��ũ�� NULL�� �ǵ��� �ϰ�
                free(p);  //p�� �޸𸮸� �������ش�.
                return 0;  //���α׷��� �����Ѵ�.
            }
            else if (p->rlink == NULL)  //������ �����
            {
                p->llink->rlink = NULL;  //p�� ���� ����� ������ ��ũ�� NULL�� ����� ����
                free(p);  //�޸𸮸� �������ְ�
                return 0;  //���α׷��� �����Ѵ�.
            }
            else  //�߰��̶��
            {
                p->llink->rlink = p->rlink;  //p�� ���� ����� ������ ��ũ�� ���� ��带 ����Ű���� �ϰ�
                p->rlink->llink = p->llink;  //p�� ���� ����� ���� ��ũ�� p�� ���� ��带 ����Ű���� �� ��
                free(p);  //�޸𸮸� �������ش�.
                return 0;
            }
        }
        p = p->rlink;  //p�� ������带 ����Ű���� �Ѵ�.
    }

    printf("%d �� ����Ʈ�� �������� �ʽ��ϴ�.\n", key);
    return 1;
}
