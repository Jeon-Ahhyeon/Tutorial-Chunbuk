/*
 ============================================================================
 Name        : Sorting&Hashing.c
 ============================================================================
 */

/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE            13    /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

 /* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int** a);
int freeArray(int* a);
void printArray(int* a);

int selectionSort(int* a);
int insertionSort(int* a);
int bubbleSort(int* a);
int shellSort(int* a);
/* recursive function���� ���� */
int quickSort(int* a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int* a, int** ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int* ht, int key);


int main()
{
    char command;  //������ �޴�
    int* array = NULL;  //�迭 ������ ���� NULL�� �ʱ�ȭ
    int* hashtable = NULL;  //�ؽ� ���̺� �ʱ�ȭ
    int key = -1;
    int index = -1;

    srand(time(NULL));

    do {
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        fflush(stdout);
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':  //�ʱ�ȭ
            initialize(&array);  //initialize �Լ���
            break;
        case 'q': case 'Q':  //����
            freeArray(array);
            break;
        case 's': case 'S':  //��������
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);  //��������
            break;
        case 'b': case 'B':
            bubbleSort(array);  //��������
            break;
        case 'l': case 'L':
            shellSort(array);  //������
            break;
        case 'k': case 'K':  //������
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);  //���� �� �迭 ���
            quickSort(array, MAX_ARRAY_SIZE);  // ������ �Լ� ȣ��
            printf("----------------------------------------------------------------\n");
            printArray(array);  // ���� �� �迭 ���

            break;

        case 'h': case 'H': //�ؽ�
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);  //�迭 ���
            hashing(array, &hashtable);  //��Ī �Լ� ȣ��
            printArray(hashtable);  //�ؽ����̺� ���
            break;

        case 'e': case 'E':  //�ؽ����̺� �˻�
            printf("Your Key = ");
            fflush(stdout);
            scanf("%d", &key);  //Ű�� �Է¹޾�
            printArray(hashtable);  //�ؽ� ���̺� ��� ��
            index = search(hashtable, key);  // ã���� �ϴ� Ű�� �ε��� ��ȯ�޾�
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);  //�ش� �� ���
            break;

        case 'p': case 'P':
            printArray(array);  // �迭 ����Ʈ
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initialize(int** a)
{
    int* temp = NULL;

    /* array�� NULL�� ��� �޸� �Ҵ� */
    if (*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
    }
    else
        temp = *a;

    /* �������� �迭�� ������ ���� */
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int* a)
{
    if (a != NULL)  //�迭�� ������� ���� ���
        free(a);  //�޸𸮸� �������� ��
    return 0;  //�Լ��� �����Ѵ�.
}

void printArray(int* a)
{
    if (a == NULL) {  //�Ѱܹ��� �迭 �����Ͱ� ����ִ� ���
        printf("nothing to print.\n");  // �ȳ��� ��� ��
        return;  //�Լ� ����
    }
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //�迭�� ũ�⸸ŭ
        printf("a[%02d] ", i);  //�迭�� �ε��� ���
    printf("\n");
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)  // �迭�� ũ�⸸ŭ
        printf("%5d ", a[i]);  //�迭�� ���� ���
    printf("\n");
}


int selectionSort(int* a)  //��ü ���� �� ���� ��ġ�� �´� ���� ���� �� �ڸ� ��ȯ�ϴ� ��������
{
    int min;  //�ּҰ�
    int minindex;  //�ּҰ��� ����ִ� �迭�� �ε���
    int i, j; //�ݺ��� ����

    printf("Selection Sort: \n");  //�ȳ��� ���
    printf("----------------------------------------------------------------\n");

    printArray(a);  // ���� �迭�� ���Ҹ� ����ϴ� �Լ� ȣ��

    for (i = 0; i < MAX_ARRAY_SIZE; i++)  //�迭�� ũ�⸸ŭ �ݺ�
    {
        minindex = i;   //�����ε����� i�� ���� ��
        min = a[i];  // ã�� ���� �����ε��� �迭�� ���Ҹ� �����Ѵ�.
        for (j = i + 1; j < MAX_ARRAY_SIZE; j++)  // �迭�� ũ�⸸ŭ �ݺ�
        {
            if (min > a[j])  // min�� ���� ���ϴ� ������ ũ�ٸ�
            {
                min = a[j];  //min�� �ش� ���� �־��� ��
                minindex = j;  //�ּҰ��� �ε����� �ٲ��ش�.
            }
        }
        //ã�� ���� ���� ���ҿ� ������ġ�� ����ִ� ���� ��ȯ���ش�.
        a[minindex] = a[i];  // �ּҰ��� ����ִ� ��ġ�� ���� ������ġ�� ������ �ٲ��ش�.
        a[i] = min;  // ���� ��ġ�� ã�� �ּҰ��� �־��ش�.
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  // ���� ���� �迭�� ������ش�.
    return 0;
}

int insertionSort(int* a)  //���ĵǾ� �ִ� �κ� ���տ� ������ ���ο� ������ ��ġ�� ã�� �����ϴ� ����
{
    int i, j, t;

    printf("Insertion Sort: \n");  //�ȳ��� ���
    printf("----------------------------------------------------------------\n");

    printArray(a);  //���� ���� �迭�� ������ش�.

    for (i = 1; i < MAX_ARRAY_SIZE; i++) //�迭�� ũ�⸸ŭ
    {
        t = a[i];  //���� ���ĵ��� ���� �κ��� ù��° ���Ҹ� ����  ,�񱳴��
        j = i;  //���� ����� �ε����� j�� �־��ش�.
        while (a[j - 1] > t&& j > 0)  // ���ĵ� �κ��� ���������Һ��� �񱳴���� t�� ���Ͽ� t�� �� ��ġ�� ã�´�.
        {
            a[j] = a[j - 1];  //���ĵ� �κ��� ���Ұ� �񱳴�󺸴� ũ�ٸ� j�� ��ġ�� ū ���Ҹ� �־��ش�,
            j--;  //j�� �ε����� 1 ���� ��Ų��.
        }
        a[j] = t;  //a[j]�κп� �������� ù��° ���Ҹ� �������ش�.
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  //�������� ���� �迭�� ����Ѵ�.

    return 0;
}

int bubbleSort(int* a)  //������ �ΰ��� ���Ҹ� ���Ͽ� �ڸ��� ��ȯ�ϴ� ��������
{
    int i, j, t;

    printf("Bubble Sort: \n");  //�ȳ��� ���
    printf("----------------------------------------------------------------\n");

    printArray(a);  //���� �� �迭 ���

    for (i = MAX_ARRAY_SIZE-1; i>0; i--)  //�迭�� ũ�� ��ŭ
    {
        for (j =0; j<i; j++) //j�� 0���� Ŭ������
        {
            if (a[j + 1] < a[j])  //������ �ΰ��� ���Ҹ� ���Ͽ� ũ�Ⱑ �������� ũ��
            {
                /*�ΰ��� ���Ҹ� ���� ��ȯ�Ѵ�.*/
                t = a[j ];  //������ ���� t�� �����ϰ�
                a[j] = a[j+1];  // ���� �ڸ��� �� ���� ���Ҹ� �־��� ��
                a[j+1] = t;   //���� �ڸ��� ū ���Ҹ� �־��ش�.
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  //���� ���� ���Ҹ� ����Ѵ�.

    return 0;
}

int shellSort(int* a) //������ �������� ������ �ִ� �ڷ�鳢�� �κ������� �����ϰ�, �� �κ����տ� �ִ� ���ҿ� ���� ���������� �����ϴ� �۾��� �ݺ��Ͽ� ��ü ���Ҹ� ����
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");  //�ȳ��� ���
    printf("----------------------------------------------------------------\n");

    printArray(a);  //���� ���� �迭�� ����Ѵ�.

    for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)  //h�� 1�� �ɶ����� �ݺ� �迭�� ũ���� 1/2�� ���� ����
    {
        for (i = 0; i < h; i++)
        {
            for (j = i + h; j < MAX_ARRAY_SIZE; j += h)  //������ �κ������� �� ��ŭ
            {
                v = a[j];  //�κ������� ���� ū �ε����� ���� ���� ����
                k = j;  //�ε����� �����Ѵ�.
                while (k > h - 1 && a[k - h] > v)  // �κ������� ù��° ���Һ��� v�� ũ�� k�� h-1���� ũ�ٸ�
                {
                    a[k] = a[k - h];  //a�� ���Ҹ� ��ȯ�ϰ�
                    k -= h;  // k=���� h�� ����.
                }
                a[k] = v; //�ٲ� ������ ���� ū �ε����� ���� ���Ҹ� �����Ѵ�.
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);  //���� �� �迭 ���

    return 0;
}
/*������ ��ü ���ҿ� ���� ������ �������� �ʰ���ذ��� �߽�����
���� �κ����հ� ������ �κ� �������� ���� �� ����*/
int quickSort(int* a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)  // n�� 1���� ũ�ٸ� ����
    {
        v = a[n - 1];  //�Ǻ� ���� ������ ���ҷ� ����
        i = -1;    //���Һκ��� ���� ���� ������ �ε���
        j = n - 1;  //���Һκ��� ���� ������ ������ �ε���

        while (1)  //i�� �����ʺκ��� �ε��� j���� ���������� ����
        {
            while (a[++i] < v);  //a�� ���� ���Ұ� �Ǻ����� ���������� i����
            /*���� ���� �� �Ǻ����� ū ���� ã�´�.*/
            while (a[--j] > v);  //a�� ���Ұ� �Ǻ����� Ŭ������ j����
            /*������ ���� �� �Ǻ����� ���� ���� ã�´�*/

            if (i >= j) break; //���� i�� �Ǻ����Ҹ� ����Ű�ų� ������ j�� �����ٸ� �ݺ��� ����
            t = a[i];  //t ���� ���Ŀ��� ã�� �Ǻ����� ū �� ����
            a[i] = a[j]; //���� ���Ŀ��� ã�� ���� ������ ���Ŀ��� ã�� ���� ��ȯ�Ѵ�.
            a[j] = t;  //������ ���Ŀ��� ã�� ���� ���� ������ �� �־���
        }
        t = a[i]; //t�� �Ǻ� ���� �־���
        a[i] = a[n - 1];   //������ ���� a[n-1]�� �Ǻ����� ��ȯ
        a[n - 1] = t;

        quickSort(a, i); //���� ���� �ٽ� ������ ȣ��
        quickSort(a + i + 1, n - i - 1);  //������ ���� �ٽ� �� ���� ȣ��
    }


    return 0;
}

int hashCode(int key) {
    return key % MAX_HASH_TABLE_SIZE;  //Ȩ ��Ŷ
}

int hashing(int* a, int** ht) //Ű�� �ִ� ��ġ�� ����Ͽ� �ٷ� ã�ư��� ��� �˻� ���
{
    int* hashtable = NULL;

    /* hash table�� NULL�� ��� �޸� �Ҵ� */
    if (*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
    }
    else {
        hashtable = *ht;    /* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
    }

    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;  //�ʱ�ȭ

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */

    int key = -1;  //key�� Ȩ ��Ŷ�� �ε��� ����
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //�迭�� ũ�� ��ŭ �ݺ�
    {
        key = a[i];  //a�� i��° ���Ҹ� key�� ����
        hashcode = hashCode(key);  //Ȩ��Ŷ ���
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1)  //�ؽ� ���̺��� Ȩ ��Ŷ�� -1�̸�
        {
            hashtable[hashcode] = key;  // �Ʊ� �����ص� key���� �ؽ����̺� ����
        }
        else {

            index = hashcode;  //�ƴϸ� �ε����� Ȩ��Ŷ�� ���� ��

            while (hashtable[index] != -1)  //�ؽ����̺��� ���Ұ� -1�� �ƴҶ�����
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;
                // �ε��� Ű�� MAX_HASH_TABLE_SIZE�� ���� �������� index�� ����
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key;  // �� �� Ű ���� �־��ش�.
        }
    }

    return 0;
}

int search(int* ht, int key)  //�ؽ����̺�� Ű���� �޾� �˻��ϴ� �Լ�
{
    int index = hashCode(key);  //�ε����� key�� Ȩ��Ŷ�� �����ϰ�

    if (ht[index] == key)  //key���� ������ �ε����� �ؽ����̺��� ���� ���ٸ�
        return index; //�ش� �ε��� ��ȯ

    while (ht[++index] != key)  //�ƴ϶��
    {
        index = index % MAX_HASH_TABLE_SIZE;  // index�� ���� MAX_HASH_TABLE_SIZE�� ���� �������� ���� ��
    }
    return index;  //�ε��� ��ȯ
}
