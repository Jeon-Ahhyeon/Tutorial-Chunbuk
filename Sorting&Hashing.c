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

 /* 필요에 따라 함수 추가 가능 */
int initialize(int** a);
int freeArray(int* a);
void printArray(int* a);

int selectionSort(int* a);
int insertionSort(int* a);
int bubbleSort(int* a);
int shellSort(int* a);
/* recursive function으로 구현 */
int quickSort(int* a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int* a, int** ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int* ht, int key);


int main()
{
    char command;  //선택할 메뉴
    int* array = NULL;  //배열 포인터 생성 NULL로 초기화
    int* hashtable = NULL;  //해시 테이블 초기화
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
        case 'z': case 'Z':  //초기화
            initialize(&array);  //initialize 함수에
            break;
        case 'q': case 'Q':  //종료
            freeArray(array);
            break;
        case 's': case 'S':  //선택정렬
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);  //삽입정렬
            break;
        case 'b': case 'B':
            bubbleSort(array);  //버블정렬
            break;
        case 'l': case 'L':
            shellSort(array);  //셸정렬
            break;
        case 'k': case 'K':  //퀵정렬
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);  //정렬 전 배열 출력
            quickSort(array, MAX_ARRAY_SIZE);  // 퀵정렬 함수 호출
            printf("----------------------------------------------------------------\n");
            printArray(array);  // 정렬 후 배열 출력

            break;

        case 'h': case 'H': //해싱
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);  //배열 출력
            hashing(array, &hashtable);  //해칭 함수 호출
            printArray(hashtable);  //해싱테이블 출력
            break;

        case 'e': case 'E':  //해시테이블 검색
            printf("Your Key = ");
            fflush(stdout);
            scanf("%d", &key);  //키를 입력받아
            printArray(hashtable);  //해시 테이블 출력 후
            index = search(hashtable, key);  // 찾고자 하는 키의 인덱스 반환받아
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);  //해당 값 출력
            break;

        case 'p': case 'P':
            printArray(array);  // 배열 프린트
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

    /* array가 NULL인 경우 메모리 할당 */
    if (*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    }
    else
        temp = *a;

    /* 랜덤값을 배열의 값으로 저장 */
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int* a)
{
    if (a != NULL)  //배열이 비어있지 않은 경우
        free(a);  //메모리를 해제해준 후
    return 0;  //함수를 종료한다.
}

void printArray(int* a)
{
    if (a == NULL) {  //넘겨받은 배열 포인터가 비어있는 경우
        printf("nothing to print.\n");  // 안내문 출력 후
        return;  //함수 종료
    }
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //배열의 크기만큼
        printf("a[%02d] ", i);  //배열의 인덱스 출력
    printf("\n");
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)  // 배열의 크기만큼
        printf("%5d ", a[i]);  //배열의 원소 출력
    printf("\n");
}


int selectionSort(int* a)  //전체 원소 중 기준 위치에 맞는 원소 선택 후 자리 교환하는 선택정렬
{
    int min;  //최소값
    int minindex;  //최소값이 들어있는 배열의 인덱스
    int i, j; //반복문 조건

    printf("Selection Sort: \n");  //안내문 출력
    printf("----------------------------------------------------------------\n");

    printArray(a);  // 현재 배열의 원소를 출력하는 함수 호출

    for (i = 0; i < MAX_ARRAY_SIZE; i++)  //배열의 크기만큼 반복
    {
        minindex = i;   //기준인덱스를 i로 정한 후
        min = a[i];  // 찾는 값에 기준인덱스 배열의 원소를 저장한다.
        for (j = i + 1; j < MAX_ARRAY_SIZE; j++)  // 배열의 크기만큼 반복
        {
            if (min > a[j])  // min의 값이 비교하는 값보다 크다면
            {
                min = a[j];  //min에 해당 값을 넣어준 후
                minindex = j;  //최소값의 인덱스도 바꿔준다.
            }
        }
        //찾은 가장 작은 원소와 기준위치에 들어있던 값을 교환해준다.
        a[minindex] = a[i];  // 최소값이 들어있던 위치의 값을 기준위치의 값으로 바꿔준다.
        a[i] = min;  // 기준 위치에 찾은 최소값을 넣어준다.
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  // 정렬 후의 배열을 출력해준다.
    return 0;
}

int insertionSort(int* a)  //정렬되어 있는 부분 집합에 정렬할 새로운 원소의 위치를 찾아 삽입하는 정렬
{
    int i, j, t;

    printf("Insertion Sort: \n");  //안내문 출력
    printf("----------------------------------------------------------------\n");

    printArray(a);  //정렬 전의 배열을 출력해준다.

    for (i = 1; i < MAX_ARRAY_SIZE; i++) //배열의 크기만큼
    {
        t = a[i];  //아직 정렬되지 않은 부분의 첫번째 원소를 저장  ,비교대상
        j = i;  //정렬 대상의 인덱스를 j에 넣어준다.
        while (a[j - 1] > t&& j > 0)  // 정렬된 부분의 마지막원소부터 비교대상인 t와 비교하여 t가 들어갈 위치를 찾는다.
        {
            a[j] = a[j - 1];  //정렬된 부분의 원소가 비교대상보다 크다면 j의 위치에 큰 원소를 넣어준다,
            j--;  //j의 인덱스를 1 감소 시킨다.
        }
        a[j] = t;  //a[j]부분에 정렬전의 첫번째 원소를 저장해준다.
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  //선택정렬 후의 배열을 출력한다.

    return 0;
}

int bubbleSort(int* a)  //인접한 두개의 원소를 비교하여 자리를 교환하는 버블정렬
{
    int i, j, t;

    printf("Bubble Sort: \n");  //안내문 출력
    printf("----------------------------------------------------------------\n");

    printArray(a);  //정렬 전 배열 출력

    for (i = MAX_ARRAY_SIZE-1; i>0; i--)  //배열의 크기 만큼
    {
        for (j =0; j<i; j++) //j가 0보다 클때까지
        {
            if (a[j + 1] < a[j])  //인접한 두개의 원소를 비교하여 크기가 이전것이 크면
            {
                /*두개의 원소를 서로 교환한다.*/
                t = a[j ];  //이전의 값을 t에 저장하고
                a[j] = a[j+1];  // 이전 자리에 더 작은 원소를 넣어준 후
                a[j+1] = t;   //다음 자리에 큰 원소를 넣어준다.
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  //정렬 후의 원소를 출력한다.

    return 0;
}

int shellSort(int* a) //일정한 간격으로 떨어져 있는 자료들끼리 부분집합을 구성하고, 각 부분집합에 있는 원소에 대해 삽입정렬을 수행하는 작업을 반복하여 전체 원소를 정력
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");  //안내문 출력
    printf("----------------------------------------------------------------\n");

    printArray(a);  //정렬 전의 배열을 출력한다.

    for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)  //h가 1이 될때까지 반복 배열의 크기의 1/2로 범위 설정
    {
        for (i = 0; i < h; i++)
        {
            for (j = i + h; j < MAX_ARRAY_SIZE; j += h)  //생성된 부분집합의 수 만큼
            {
                v = a[j];  //부분집합중 가장 큰 인덱스를 가진 원소 저장
                k = j;  //인덱스를 저장한다.
                while (k > h - 1 && a[k - h] > v)  // 부분집합의 첫번째 원소보다 v가 크고 k가 h-1보다 크다면
                {
                    a[k] = a[k - h];  //a의 원소를 교환하고
                    k -= h;  // k=에서 h를 뺀다.
                }
                a[k] = v; //바뀐 공간에 가장 큰 인덱스를 가진 원소를 저장한다.
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);  //정렬 후 배열 출력

    return 0;
}
/*정렬한 전체 원소에 대해 정렬을 수행하지 않고기준값을 중심으로
왼쪽 부분집합과 오른쪽 부분 집합으로 분할 후 정렬*/
int quickSort(int* a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)  // n이 1보다 크다면 실행
    {
        v = a[n - 1];  //피봇 가장 오른쪽 원소로 설정
        i = -1;    //분할부분의 가장 왼쪽 원소의 인덱스
        j = n - 1;  //분할부분의 가장 오른쪽 원소의 인덱스

        while (1)  //i가 오른쪽부분의 인덱스 j보다 작을때까지 실행
        {
            while (a[++i] < v);  //a의 왼쪽 원소가 피봇보다 작을때까지 i증가
            /*왼쪽 정렬 중 피봇보다 큰 수를 찾는다.*/
            while (a[--j] > v);  //a의 원소가 피봇보다 클때까지 j증가
            /*오른쪽 정렬 중 피봇보다 작은 수를 찾는다*/

            if (i >= j) break; //만약 i가 피봇원소를 가리키거나 오른쪽 j를 만났다면 반복문 종료
            t = a[i];  //t 왼쪽 정렬에서 찾은 피봇보다 큰 수 저장
            a[i] = a[j]; //왼쪽 정렬에서 찾은 수와 오른쪽 정렬에서 찾은 수를 교환한다.
            a[j] = t;  //오른쪽 정렬에서 찾은 수에 왼쪽 정렬의 수 넣어줌
        }
        t = a[i]; //t에 피봇 원소 넣어줌
        a[i] = a[n - 1];   //오른쪽 원소 a[n-1]과 피봇원소 교환
        a[n - 1] = t;

        quickSort(a, i); //왼쪽 정렬 다시 퀵정렬 호출
        quickSort(a + i + 1, n - i - 1);  //오른쪽 정렬 다시 퀵 정렬 호출
    }


    return 0;
}

int hashCode(int key) {
    return key % MAX_HASH_TABLE_SIZE;  //홈 버킷
}

int hashing(int* a, int** ht) //키가 있는 위치를 계산하여 바로 찾아가는 계산 검색 방식
{
    int* hashtable = NULL;

    /* hash table이 NULL인 경우 메모리 할당 */
    if (*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    }
    else {
        hashtable = *ht;    /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
    }

    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;  //초기화

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */

    int key = -1;  //key값 홈 버킷값 인덱스 설정
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //배열의 크기 만큼 반복
    {
        key = a[i];  //a의 i번째 원소를 key에 저장
        hashcode = hashCode(key);  //홈버킷 계산
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1)  //해시 테이블의 홈 버킷이 -1이면
        {
            hashtable[hashcode] = key;  // 아까 저장해둔 key값을 해시테이블에 저장
        }
        else {

            index = hashcode;  //아니면 인덱스에 홈버킷값 저장 후

            while (hashtable[index] != -1)  //해시테이블의 원소가 -1이 아닐때까지
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;
                // 인덱스 키를 MAX_HASH_TABLE_SIZE로 나눈 나머지를 index에 저장
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key;  // 그 후 키 값을 넣어준다.
        }
    }

    return 0;
}

int search(int* ht, int key)  //해시테이블과 키값을 받아 검색하는 함수
{
    int index = hashCode(key);  //인덱스에 key의 홈버킷을 저장하고

    if (ht[index] == key)  //key값이 지정한 인덱스의 해시테이블의 값과 같다면
        return index; //해당 인덱스 반환

    while (ht[++index] != key)  //아니라면
    {
        index = index % MAX_HASH_TABLE_SIZE;  // index의 값을 MAX_HASH_TABLE_SIZE로 나눈 나머지로 수정 후
    }
    return index;  //인덱스 반환
}
