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

 /* �ʿ��� ������� �߰� */

typedef struct Node {  // ���Ḯ��Ʈ�� �����ϴ� ����ü
    int key;  //���Ḯ��Ʈ�� ��
    struct Node* link;  //���Ḯ��Ʈ�� ������ ����Ŵ  //�������� ���� Ÿ���̾ �տ� struct�� �ٿ��ش�.
} listNode;

typedef struct Head {  //���Ḯ��Ʈ�� ó���� �����ϴ� ����ü
    struct Node* first;  //ó�� ��带 ����Ŵ //�������� ���� Ÿ���̾ �տ� struct�� �ٿ��ش�.
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h); //�ʱ�ȭ�����ִ� �Լ�
int freeList(headNode* h);  //�������� �Ҵ���� ����Ʈ �޸𸮸� ���������ִ� �Լ�

int insertFirst(headNode* h, int key);  //ù��° ��忡 Ű�� �������ִ� �Լ�
int insertNode(headNode* h, int key);  //�Է¹��� Ű�� �� ��ġ�� Ž���Ͽ� �����ϴ� �Լ�
int insertLast(headNode* h, int key);  //�Է¹��� Ű�� ������ ��忡 �����ϴ� �Լ�

int deleteFirst(headNode* h);  // ù��° ��带 �����ϴ� �Լ�
int deleteNode(headNode* h, int key);  //�Է¹��� Ű�� ã�� ������ �����ϰ� ������ �ȳ����� ����ϴ� �Լ�
int deleteLast(headNode* h);  //������ ��带 �����ϴ� �Լ�
int invertList(headNode* h);  //����Ʈ�� ������ �ٲ��ִ� �Լ�

void printList(headNode* h);  //����Ʈ�� ������ִ� �Լ�

int main()
{
    char command;  //�޴��� �Է¹��� ����
    int key;  //Ű�� �Է¹��� ����
    headNode* headnode = NULL;  //���Ḯ��Ʈ

    printf("������ 2018068005\n");

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
        scanf(" %c", &command);  //�޴� �Է¹ޱ�

        switch (command) {  //����ġ ���� ����Ͽ�
        case 'z': case 'Z':  //�ʱ�ȭ�޴� ���ý�
            headnode = initialize(headnode);  //�ʱ�ȭ �Լ� ȣ��
            break;  //����ġ�� Ż��
        case 'p': case 'P':  //����Ʈ�� ����ϱ� ���ϸ�
            printList(headnode);  // ����Ʈ ����ϴ� �Լ� ȣ��
            break;  //����ġ�� Ż��
        case 'i': case 'I':  //������ ���ϸ�
            printf("Your Key = ");  // �ȳ��� �����
            fflush(stdout);
            scanf("%d", &key);  //Ű�� �Է¹ް�
            insertNode(headnode, key);  //Ű�� �����ϴ� �Լ� ȣ��
            break;  //����ġ �� Ż��
        case 'd': case 'D':  //Ű�� �����ϱ� ���Ѵٸ�
            printf("Your Key = ");  //Ű�� �Է¹ް�
            fflush(stdout);
            scanf("%d", &key);
            deleteNode(headnode, key);  //Ű�� �����ϴ� �Լ� ȣ��
            break;  //����ġ�� Ż��
        case 'n': case 'N':  //�������� ��带 �����ϱ� ���ϸ�
            printf("Your Key = ");  //Ű�� �Է¹ް�
            fflush(stdout);
            scanf("%d", &key);
            insertLast(headnode, key);  //�Լ��� ȣ���ϰ�
            break;  //����ġ �� Ż��
        case 'e': case 'E':  // ������ ��带 �����ϱ� ���ϸ�
            deleteLast(headnode);  //�Լ� ȣ���ϰ�
            break;  //����ġ�� Ż��
        case 'f': case 'F':  // ù��°�� ��带 �����ϱ� ���ϸ�
            printf("Your Key = ");
            fflush(stdout);
            scanf("%d", &key);  //Ű�� �Է¹��� ��
            insertFirst(headnode, key);  //�Լ��� ȣ���ϰ�
            break;  //����ġ���� Ż���Ѵ�.
        case 't': case 'T':  //ù��° ��带 �����ϱ� ���Ѵٸ�
            deleteFirst(headnode);  //�Լ��� ȣ���ϰ�
            break; //����ġ�� Ż��
        case 'r': case 'R':  //����Ʈ�� ������ ���������� �ٲٰ� �ʹٸ�
            invertList(headnode);  // �Լ� ȣ���ϰ�
            break;  //����ġ�� Ż��
        case 'q': case 'Q':  //����Ʈ�� �����ϱ� ���Ѵٸ�
            freeList(headnode);  // ����Ʈ�� �޸𸮸� �������� ��
            break; //����ġ�� Ż��
        default:  //�߸� �Է��ߴٸ�
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //�ȳ��� ���
            break;
        }

    } while (command != 'q' && command != 'Q');  //�����ϱ� ���Ѵٸ� �ݺ��� Ż��

    printf("���α׷��� ����Ǿ����ϴ�\n");
    return 1;
}

headNode* initialize(headNode* h) {

    /* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
    if (h != NULL)
        freeList(h);

    /* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode* h) {
    /* h�� ����� listNode �޸� ����
     * headNode�� �����Ǿ�� ��.
     */
    listNode* p = h->first;  //����Ʈ�� ����Ű�� ���� ����

    listNode* prev = NULL;  //������ ����Ʈ�� ����ų ����
    while (p != NULL) {  //����Ʈ�� ������ �ƴϸ�
        prev = p;  //prev�� ���� ��带 ����Ű�� �ϰ�
        p = p->link;  //p�� �� ���� ��带 ����Ű�� �� ��
        free(prev);  //prev�� ���� �޸� ���� ���ش�.
    }
    free(h);  //�� �������� ù��° ���� �޸� �������� ��
    return 0;  // �Լ��� �����Ѵ�.
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));  //�Ѱܹ��� ���� ����ų ���
    node->key = key;  //����� ���� ����

    node->link = h->first;  // ����� ��尡 ����Ű�� ���� ��尡 ����Ű���� �ϰ�
    h->first = node;  //����� ��尡 node�� ����Ű���� �Ѵ�.

    return 0; //���α׷��� �����Ѵ�.
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //����Ʈ�� head�� ����Ű�� ���� �޾� ����Ʈ�� Ž���ϱ� ���� ����Ʈ
    listNode* NEW= (listNode*)malloc(sizeof(listNode));  //Ű ���� ������ ����Ʈ
    listNode* Pre = (listNode*)malloc(sizeof(listNode));  //����Ʈ�� ������ �� ���� ����Ʈ���� �����ϴ� ����Ʈ
    NEW->key = key;  //NEW ����Ʈ�� Ű���� �����Ѵ�.
    NEW->link = NULL;
    node = h->first;  //
    Pre =h->first;

    if (h->first==NULL)  //����Ʈ�� ���鸮��Ʈ���
    {
        h->first = NEW;  //����Ʈ�� ó���� NEW�� ����Ű���� �Ѵ�.
        return 0;  //���α׷� ����
    }
    while (node!=NULL)  //���鸮��Ʈ�� �ƴϰ�
    {
        if (NEW->key <= node->key)  //�Է¹��� Ű�� �뵵�� ������ �ִ� ������ ������
        {
            if (node = h->first)//���� ������ ��ġ�� ù��� �����̶��
            {
                h->first = NEW;  //����Ʈ�� ó���� NEW�� ����Ű���� �� ��
                NEW->link = node;  //������ ����Ʈ�� node�� ����Ű���� ���ش�.
            }
            else//������ ��ġ�� �߰� ���̶��
            {
                NEW->link = node->link;//������ Ű ���� �� ��ġ�� ���� ��带 ����Ű���� �ϰ�
                Pre->link = NEW;  //������ ��ġ�� �� ��尡 NEW�� ����Ű���� �Ѵ�.
            }
            return 0;  //�Լ��� �����Ѵ�.
        }  //�ƴ϶��
        Pre = node;  //Pre�� node�� ����Ű���� �ϰ�
        node = node->link;  //node�� ���� ���� ����Ű���� �Ѵ�.
    }// Ű ���� ������ ��忡 ���ԵǾ�� �Ѵٸ�
    Pre->link = NEW;  //Pre�� ��ũ�� ���ο� ��带 ����Ű���� �Ѵ�.
    return 0;  //�Լ��� �����Ѵ�.
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
    listNode* node = h->first;//����Ʈ�� head�� ����Ű�� ���� �޾� ����Ʈ�� Ž���ϱ� ���� ����Ʈ ���� �� ���� �Ҵ�
    listNode* NEW=(listNode*)malloc(sizeof(listNode));  //���ο� Ű ���� �Է¹��� ����Ʈ ���� �� ���� �Ҵ�

    NEW->key = key;  //Ű ���� ����Ʈ�� �����Ѵ�.
    NEW->link = NULL;


    if (h->first==NULL)  //���鸮��Ʈ ���
    {
        h->first = NEW;  //����Ʈ�� ó���� NEW�� ����Ű���� �ϰ�
        return 0; //���α׷��� �����Ѵ�.
    }
    else  //������ �ƴ϶��
    {
        while (node->link != NULL)  //list�� �������� ã�� ������
            node = node->link;  //node�� �ּҸ� �̵����ְ�
        node -> link = NEW;  //�������� ã�Ҵٸ� ������ ��ũ�� NEW�� ����Ű���� ���ش�.
    }

    return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
    listNode* node = h->first; //����Ʈ�� head�� ����Ű�� ���� �޾� ����Ʈ�� Ž���ϱ� ���� ����Ʈ ���� �� ���� �Ҵ�

    if (h->first==NULL)  //���鸮��Ʈ���
    {
        printf("���� ����Ʈ �Դϴ�.\n");//�ȳ����� ����ϰ�
        return 0;  //�Լ��� �����Ѵ�.
    }  //���鸮��Ʈ�� �ƴ϶��
    h->first = node->link;  // ����Ʈ�� ó���� ����Ű�� �ּҸ� ù��° ����� ���� ��带 ����Ű���� ���ְ�
    free(node);  //������ ����� �����޸𸮸� �����Ѵ�.

    return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
    listNode* node = h->first;//����Ʈ�� head�� ����Ű�� ���� �޾� ����Ʈ�� Ž���ϱ� ���� ����Ʈ ���� �� ���� �Ҵ�
    listNode* Pre;  //������ ����Ʈ�� ���� ����Ʈ���� �����ϴ� ����Ʈ
    Pre = h->first;

    if (h->first==NULL)  //���鸮��Ʈ���
    {
        printf("���� ����Ʈ �Դϴ�.\n");//�ȳ����� ����ϰ�
        return 0;  //�Լ��� �����Ѵ�.
    }  //���鸮��Ʈ�� �ƴ϶��

    while (node != NULL)  //���鸮��Ʈ�� �ƴ϶�� �ݺ�
    {
        if (node->key == key)  //����� Ű���� ���� Ű���� ������
        {
            if (node == h->first)//���� ������ ��ġ�� ù�����
            {
                h->first = node->link;  //����Ʈ�� ó���� node�� ������ ����Ű���� �� ��
                free(node);  //������ ����� �����޸𸮸� �����Ѵ�.
                return 0;  //�Լ��� �����Ѵ�.
            }
            else if (node->link == NULL) //������ ��尡 ������ �����
            {
                Pre->link = NULL;  //������ ��带 ����Ű�� Pre�� NULL�� ����Ű���� �ϰ�
                free(node);  //������ ��带 �޸� ���� ��Ų��.
                return 0;// ���α׷��� �����Ѵ�.
            }
            else //������ ����� ��ġ�� �߰� ���̶��
            {
                Pre->link = node->link;  //Pre�� ����Ű�� ���� node�� �������� �ٲ��ְ�
                free(node);  //node���� �޸𸮸� ������Ų ��
                return 0;  //�Լ��� �����Ѵ�.
            }
        }  //�ƴ϶��

        Pre = node;  //Pre�� ������ node�� �� ��带 ����Ű���� �ϰ�
        node = node->link;  //��尡 �� ���� ���� ����Ű���� �Ѵ�.
    }

    printf("%d �� ����Ʈ�� �������� �ʽ��ϴ�.\n",key);

    return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
    listNode* node = h->first;//����Ʈ�� head�� ����Ű�� ���� �޾� ����Ʈ�� Ž���ϱ� ���� ����Ʈ ���� �� ���� �Ҵ�
    listNode* Pre;  //������ ����Ʈ�� ���� ����Ʈ���� �����ϴ� ����Ʈ


    if (h->first ==NULL)// ���鸮��Ʈ���
    {
        printf("���� ����Ʈ �Դϴ�.\n");//�ȳ����� ����ϰ�
        return 0;  //�Լ��� �����Ѵ�.
    }
    else if (node->link == NULL)  //����Ʈ�� ��尡 �ϳ��� �����Ѵٸ�
    {
        h->first = NULL;  //����Ʈ�� ó���� ����Ű�� ���� ����ְ�
        free(node);  //�ش� ����� �޸𸮸� ���������ش�.
    }// �ƴ϶��
    while (node->link!=NULL)//node�� �������϶�����  �ݺ�
    {
        Pre= node;//�����ϱ� ������ ���� ����Ű���� �ϰ�
        node = node->link; //��尡 ���� ��带 ����Ű���� �Ѵ�.
    }
    Pre->link = NULL;  //������ ����� ���� ����Ʈ�� ��ũ�� NULL�� ����Ű���� �ϰ�
    free(node);  //������ ����� �޸𸮸� ���������ش�.

    return 0;  //���α׷��� �����Ѵ�.
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
    listNode* node ;//����Ʈ�� ù��° ���
    listNode* Pre;  //����Ʈ�� �ٲ��� ���
    listNode* mid; //�ٲ� ����Ʈ�� �߰��� ������ �ִ� ���

    node = h->first; //��尡 ����Ʈ�� ù��°�� ����Ű���� �Ѵ�.
    Pre = NULL;
    mid = NULL;

    while (node != NULL)  //����Ʈ�� ������ ��尡 �ƴҶ� ����
    {
        Pre = mid;  //Pre�� Mid�� �������ְ�
        mid = node;  //mid�� node�� ����Ű�� �Ѵ�.
        node = node->link;// ��尡 ���� ��带 ����Ű�� ���� ��
        mid->link = Pre;  //mid�� ����Ű�� ���� Pre�� �������ش�.
    }
    h->first = mid;  //�������� ��ġ�� �Ϸ�Ǿ��ٸ� ����Ʈ�� ó���� ����Ʈ�� ���������� �������ش�.


    return 0;  //�Լ��� �����Ѵ�.
}


void printList(headNode* h) {  //����Ʈ�� ������ִ� �Լ�
    int i = 0;
    listNode* p; //����� ����Ʈ�� ����ų ����

    printf("\n---PRINT\n");

    if (h == NULL) {  //���鸮��Ʈ���
        return;//�Լ��� �����Ѵ�.
    }

    p = h->first;  //���鸮��Ʈ�� �ƴ϶�� p�� ����Ʈ�� ����Ű���� �ϰ�

    while (p != NULL) {  //p�� ������ ��尡 �ƴ϶��

        printf("[ [%d]=%d ] ", i, p->key);  // Ű ���� ����Ѵ�.
        p = p->link;  //p�� ���� Ű�� ����Ű���� �� ��
        i++;
    }

    printf("  items = %d\n", i);//Ű�� �� �� ���
}
