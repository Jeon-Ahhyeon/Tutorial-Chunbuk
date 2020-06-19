/*
 ============================================================================
 Name        : Term-Project.c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20// 최대 크기를 20으로 잡았다 밑에 코드에서는 0~20까지 구현을 위해 MAX_VERTEX+1 이라고 작성하였다.

typedef struct Vertex {  //정점들의 edge나타냄
	int num;  // 정점번호
	struct Vertex* link;  //정점이 다음에 가리키는 정점
}Vertex;

typedef struct VertexHead {  //정점
	Vertex* head;  //정점들의 간선을 나타냄
}VertexHead;

typedef struct Graph {  //전체 그래프
	VertexHead* vlist;  //헤드들을 가리킨다.
}Graph;

int visited[MAX_VERTEX + 1] = { 0 };  //탐색할 때 방문여부를 나타내는 전역배열  처음에는 0으로 초기화한다.

void visitedreset()   // 탐색함수에서 전역배열을 초기화한 후 사용하기 위해 작성
{
	for (int i = 0; i < MAX_VERTEX + 1; i++)  //전역배열을 초기화해준다.
		visited[i] = 0;
}

//typedef int element;

typedef struct QNode {  //breadthFS()함수에서 큐를 이용하기 위해 작성
	int data;  //Q의 값
	struct QNode* link;  //Q가 가질 다음 값
}QNode;

typedef struct {  //Q의 front와 rear를 나타냄
	QNode* front,*rear;
}LQueueType;

LQueueType* createLinkedQueue() {  //Q를 생성한 후 초기화 해주는 함수
	LQueueType* LQ = (LQueueType*)malloc(sizeof(LQueueType));  //만들어둔 자료형으로 LQ를 동적할당한 후
	LQ->front = NULL;  //front와 rear를 NULL로 초기화해준다.
	LQ->rear = NULL;
	return LQ;  //만든 Q를 반환한다.
}

int isEmpty(LQueueType *LQ)  //Q가 비었는지 확인해주는 함수
{
	if (LQ->front == NULL)  //front가 NULL이라면 Q가 비어있다는 뜻
	{
		printf("비어있는 큐입니다.\n");  //안내문 출력 후
		return 1;  //1반환
	}
	else
		return 0;  //비어있지 않다면 0반환
}

void enQueue(LQueueType* LQ, int item)  //Q에 data를 추가해주는 함수
{
	QNode* q = (QNode*)malloc(sizeof(QNode));  //q를 동적으로 할당해준다.
	q->data = item;  //할당받은 q의 data에 저장할 값을 입력하고
	q->link = NULL;  //q가 가리키는 다음 값을 NULL로 초기화한다.
	if (LQ->front == NULL)  //큐가 비어있었다면
	{
		LQ->front = q;  //Q의 front와 rear가 q를 가리키도록 한다.
		LQ->rear = q;
	}
	else {  //아니라면
		LQ->rear->link = q;  //rear의 값과 가리키는 값이 q를 가리키도록 한다.
		LQ->rear = q;
	}
}

int deQueue(LQueueType* LQ)  //Q에서 하나를 빼주는 함수
{
	QNode* old = LQ->front;  //Q의 front값을 저장한다.
	int item;  //뺄 값을 저장할 변수
	if (isEmpty(LQ)) return 0;  //Q가 비어있다면 함수 종료
	else {  //비어있지 않다면
		item = old->data;  //Q의 첫번째 값을 item에 저장
		LQ->front = LQ->front->link;  //첫번째 링크가 두번째 링크를 가리키도록 한 다.
		if (LQ->front == NULL)  //만약 첫번째 자리가 NULL이라면
			LQ->rear = NULL;  //rear도 NULL로 초기화해준다.
		free(old);  //동적으로 할당받은 old의 메모리를 해제한다.
		return item;  //아까 빼준 값을 반환한다.
	}
}
int empty[MAX_VERTEX+1];  //정점이 생겼는지 안생겼는지 확인하는 전역배열

/*추가 구현한 함수*/
int insertsearch(VertexHead* h, int v);   //insert를 요구하는 insertEdge함수에서 사용 -> 값을 오름차순으로 저장하기 위해 사용
int deletesearch(VertexHead* h, Vertex* ver, Vertex* pre);  //delete함수에서 원하는 정점을 찾은 후 삭제하기 위해 구현

Graph* createGraph(Graph*g); /* empty graph creation */
int destroyGraph(Graph * g); /* deallocating all allocated memory */
int insertVertex(Graph* g,int v); /* vertex insertion */
int deleteVertex(Graph* g, int v); /* vertex deletion */
int insertEdge(Graph* g, int u, int v); /* new edge creation between two vertices */
int deleteEdge(Graph* g,int u,int v); /* edge removal */
int depthFS(Graph* g,int v); /* depth firt search using stack */
int breadthFS(Graph* g, int v); /* breadth first search using queue */
int printGraph(Graph* g); /* printing graph with vertices and edges */



void main()
{
	char command;//입력받는 메뉴
	int key;  //입력받는 키
	int u, v;  //  입력받는 정점
	Graph* graph = NULL;//그래프 형성

	printf("전아현 2018068005\n");  //학점 이름 출력

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     무방향 Graph Function       \n");   //메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf(" Create          = c         Print Graph      = p \n");
		printf(" Insert Vertex   = v         Delete Vertex    = d \n");
		printf(" Insert Edge     = e         Delete Edge      = l\n");
		printf(" DepthFS         = f         BreadthFS        = b\n");
		printf(" Quit            = q                \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);  //메뉴 입력받기

		switch (command) {  //스위치 문을 사용하여
		case 'c': case 'C':  //초기화메뉴 선택시
			graph = createGraph(graph);   //초기화 함수 호출
			break;
		case 'p': case 'P':    //인접 리스트 출력하는 함수 호출
			printGraph(graph);
			break;
		case 'v': case 'V':    //정점 삽입하는 함수 호출
			printf("Insert Vertex NUM = ");
			fflush(stdout);
			scanf("%d", &key);   // 삽입할 키 입력
			insertVertex(graph, key);
			break;
		case 'd': case 'D':    //정점을 삭제하는 함수 호출
			printf("Delete Vertex NUM = ");
			fflush(stdout);
			scanf("%d", &key);  //삭제할 키 입력
			deleteVertex(graph, key);
			break;
		case 'e': case 'E':    //엣지를 삽입할 함수 호출
			printf("-----(u,v)------\n");
			printf("Insert Edge u = ");      //정점 두개 입력
			fflush(stdout);
			scanf("%d", &u);
			printf("Insert Edge v = ");
			fflush(stdout);
			scanf("%d", &v);
			insertEdge(graph, u, v);
			break;
		case 'l': case 'L':   //엣지를 삭제하는 함수 호출
			printf("-----(u,v)------\n");  //정점 두개 입력
			printf("Insert Edge u = ");
			fflush(stdout);
			scanf("%d", &u);
			printf("Insert Edge v = ");
			fflush(stdout);
			scanf("%d", &v);
			deleteEdge(graph, u, v);
			break;
		case 'f': case 'F':   //그래프 깊이 우선 탐색 함수 호출
			visitedreset();  //호출 전 방문 기록 초기화
			printf("SELECT VERTEX NUM = ");  //시작할 정점을 선택한다.
			fflush(stdout);
			scanf("%d", &key);
			depthFS(graph,key);  // 함수 호출
			printf("\n");
			break;
		case 'b': case 'B':
			printf("SELECT VERTEX NUM = ");  //너비우선 탐색함수 호출
			fflush(stdout);
			scanf("%d", &key);  //시작할 정점 선택
			breadthFS(graph,key);
			printf("\n");
			break;
		case 'q': case 'Q':   // 그래프 프로그램 종료
			destroyGraph(graph);  //동적으로 할당받은 그래프의 각 원소를 해제하는 함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//메뉴를 잘못 입력받을 경우 다시 입력받기
			break;
		}
	} while (command != 'q' && command != 'Q');  //q를 입력하지 않았다면 메뉴 계속 실행


}


Graph* createGraph(Graph* g) /* empty graph creation */
{
	if (g != NULL) //그래프가 비어있지 않다면
		destroyGraph(g);  //그래프를 해제해 준 후 다음 코드 실행

	Graph* graph = (VertexHead*)malloc(sizeof(VertexHead)*(MAX_VERTEX+1)); //  그래프를 동적 배열로 MAX_VERTEX+1크기 만큼 할당해준다 0~20의 수 입력 가능

	for (int i = 0; i < MAX_VERTEX+1; i++)  //만든 배열의 크기만큼
	{
		graph[i].vlist = NULL;  //그래프의 vlist를 NULL로 초기화 해주고
		empty[i] = 0;  //vlist의 생성 기록을 초기화해준다.
	}
	return graph;  //생성한 그래프리스트를 반환한다.
}
int destroyGraph(Graph* g) /* deallocating all allocated memory */
{
	VertexHead* h;  //헤드 포인터
	Vertex* v;  //정접포인터
	Vertex* vprev = NULL;  //삭제할 포인터

	for (int i = 0; i < MAX_VERTEX + 1; i++)  //배열의 크기만큼
	{
		if (empty[i] == 1)  //만약 정점이 생성되어 있다면
		{
			h = g[i].vlist;  //헤드포인터에 정점을 연결하고
			v = h->head;  // 정점의 간전들을 연결한다.
			while (v != NULL) //정점의 간선이 없어질 때까지
			{
				vprev = v;
				v = v->link;
				free(vprev); //정점을 해제해준다.
			}
			free(h);  //헤드포인터도 해제해준다.
		}
	}
	free(g);  //다 끝났다면 마지막으로 graph의 메모리를 해제해준다.


}
int printGraph(Graph* g) /* printing graph with vertices and edges */
{
	Vertex* p;//출력할 정점

	for (int i = 0; i <( MAX_VERTEX + 1); i++)//만들어진 배열의 크기만큼
	{
		if (empty[i] != 0)  //정점의 생성여부를 확인하여 생성되었다면
		{
			p = g[i].vlist->head;  //p에 생성된 정점의 포인터를 넘겨준 후
			printf("\t[%d]의 인접리스트 : ",i);  // 데이터 출력
			while (p != NULL)  //연결된 간선이 없을때까지
			{
				printf("  ->  [%d]", p->num);  //p의 값 출력
				p = p->link;  //p가 다음 값을 가리키도록 함
			}
			printf("\n");  //개행문자 ㅈ출력
		}
	}
}
int insertVertex(Graph *g,int v)  //정점을 삽입하는 함수
{
	VertexHead* head = (VertexHead*)malloc(sizeof(VertexHead));  //정점의 헤드포인터 동적할당
	head->head = NULL;  //헤드의 값을 NULL로 초기화


	if (empty[v] != 0)  //해당 정점의 생성기록이 없다면
	{
		printf("%d는 이미 만들어진 정점입니다.\n", v);//안내문 출력 후 함수 종료
		return 0;
	}
	else if (v > MAX_VERTEX+1)  // 만약 정점의 개수 범위를 초과하였다면 안내문 출력 후
	{
		printf("정점의 개수를 초과하였습니다.\n");
		return 0;
	}
	else if (v < 0)
	{
		printf("입력받은 수가 범위를 벗어났습니다.\n");
		return 0;  //함수 종료
	}

	empty[v] = 1;  //만들어진 정점의 생성 기록을 1로 바꿔줌
	g[v].vlist = head;  //해당 그래프가 만들어진 정점 포인터를 가리키도록 한 후
	return 1;  //함수 종료

}

int insertEdge(Graph* g, int u, int v) /* new edge creation between two vertices */
{
	if (empty[u] == 0 || empty[v] == 0) //입력할 정점의 생성기록이 없다면
	{
		printf("그래프에 해당 정점이 존재하지 않습니다.\n");  //안내문 출력 후 함수 종료
		return 0;
	}
	else if (v > MAX_VERTEX || u > MAX_VERTEX || v < 0 || u < 0 )  //입력범위를 초과하였다면
	{
		printf("정점을 잘못입력하였습니다.\n");  //안내문 출력 후
		return 0;  //함수 종료
	}

	insertsearch(g[u].vlist, v);  //정점 u에 대해서 v간선을 입력하는 함수 호출
	insertsearch(g[v].vlist, u);  //정점 v에 대해서 u간선을 입력하는 함수 호출

	return 0;
}
int insertsearch(VertexHead* h, int v)  //간선을 찾아 입력해주는 함수
{
	Vertex* ver = (Vertex*)malloc(sizeof(Vertex));  //입력할 정점 동적 할당
	ver->num = v;  // 입력받은 정점을 입력
	ver->link = NULL;  // link값을 초기화 한다.
	Vertex* pre;  //ver이 들어갈 자리의 이전 값
	Vertex* p;  //ver이 들어갈 자리의 다음 값

	if (h->head == NULL)  //헤당 정점에 간선이 만들어지지 않았다면
	{
		h->head = ver;  //헤드포인터가 ver을 가리키도록 한 후
		return 0;  //함수를 종료한다.
	}
	p = h->head;  //간선을 탐색하기 위해 p와 pre에 정점 헤드포인터가 가리키는 값 입력
	pre = h->head;
	while (p != NULL)  //간선을 모두 탐색할때까지
	{
		if (p->num > v) {  //p가 가리키는 값이 입력받은 정점보다 크고
			if (p == h->head)  //들어갈 자리가 처음이라면
			{
				h->head = ver;  //헤드포인터가 ver을 가리키도록 하고
				ver->link = p;  //ver이 원래 헤드포인터가 가리킨 첫번째 값을 가리키도록 한다.
			}
			else  //첫번째 자리가 아니라면
			{
				ver->link = pre->link;  //ver이 들어갈 자리의 이전자리의 다음 링크를 가리키도록 하고
				pre->link = ver;  //pre의 다음 링크가 ver을 가리키도록 한다.
			}
			return 0;  //함수를 종료한다.
		}
		else if (p->num == v)  //만약 입력한 간선이 존재한다면
			return 0;  //아무것도 하지 않고 함수를 종료한다.
		pre = p;  //pre가 p를
		p = p->link; //p가 그 다음 링크를 가리키도록 한다.
	}
	pre->link = ver;  //들어갈 자리가 맨 마지막 링크라면 pre링크가 ver을 가리키도록 한다.
	return 0;  //프로그램을 종료한다.
}

int deleteVertex(Graph* g, int v) /* edge removal */
{
	VertexHead* head;  //탐색할 정점의 헤드포인트
	Vertex* ver,*pre;  //삭제할 노드와 이전 노드
	if (empty[v] == 0)  //만약 해당 정점의 생성기록이 존재하지 않는다면
	{
		printf("%d정점이 존재하지 않습니다.\n");  //안내문 출력 후 함수 종료
		return 0;
	}
	else if(v<0 || v>MAX_VERTEX+1)  //만약 정점이 정점의 범위를 벗어난다면
	{
		printf("입력한 정점이 범위를 초과하였습니다.\n");  //안내문 출력 후
		return 0; //함수 종료
	}

	for (int i = 0; i < (MAX_VERTEX + 1); i++)  //만들어진 배열의 크기만큼
	{
		if (empty[i] != 0) {  //정점의 생성기록이 존재한다면
			head = g[i].vlist;  //헤드포인터가 정점을 가리키도록 하고
			if (head->head != NULL)  //정점에 간선이 존재할 경우
			{
				ver = head->head;  //ver과 pre가 헤드포인터 간선의 처음을 가리키도록 한 후
				pre = head->head;
				while (ver != NULL)  //간선을 모두 탐색할 때까지
				{
					if (ver->num == v)  //연결된 간선의 정점이 입력받은 값과 같아면
					{
						deletesearch(g[i].vlist, ver, pre);  //해당 간선을 삭제해주는 함수를 호출
						break;  //반복문을 종료한다.
					}
					pre = ver;//pre가 ver을
					ver = ver->link; //ver이 pre를 가리키도록 한다.
				}
			}
		}
	}


	empty[v] = 0;  //해당 정점의 생성 기록을 0으로 초기화 한다.
	return 0;
}
int deletesearch(VertexHead * h,Vertex* ver,Vertex*pre)  //정점을 삭제해주는 함수
{
	if (ver == h->head)  //삭제할 엣지가 첫번째라면
	{
		h->head = ver->link;  //헤드포인터가 ver의 다음을 가리키도록 한 후
		free(ver);  //ver삭제
		return 0;//프로그램 종료
	}
	else  //아니라면
	{
		pre->link = ver->link;  //pre가 가리키는 값을 ver의 다음 값으로 바꾼 후
		free(ver);  //ver을 해제해준후
		return 0;  //함수 종료

	}
	return 0;
}
int deleteEdge(Graph* g, int u, int v) /* edge removal */
{
	Vertex* ver,*pre;  //삭제할 정점과 이전 정점 선언
	if (empty[v] == 0 || empty[u] == 0)  //입력받은 정점의 생성기록이 존재하지 않는다면
	{
		printf("입력하신 정점이 존재하지 않습니다.\n");  //안내문 출력 후
		return 0; //함수 종료
	}
	else if (v<0 || v>(MAX_VERTEX+1))  //만약 입력한 정점의 범위가 잘못되었다면
	{
		printf("입력한 정점이 범위를 초과하였습니다.\n");  //안내문 출력 후
		return 0;  //함수 종료
	}

	ver = g[u].vlist->head;  //ver과 pre가 삭제할 u간선의 헤드포인터가 가리키는 곳을 가리키도록 하고
	pre = g[u].vlist->head;
	while (ver != NULL)  //간선 탐색이 끝날때까지
	{
		if (ver->num == v)  //v간선의 값과 입력한 값이 같으면
		{
			deletesearch(g[u].vlist, ver, pre);  //함수 호출하여 해당 간선 해제
			break;  //반복을 종료한다.
		}
		pre = ver;  //아니면 pre가 ver을 ver이 ver다음 값을 가리키도록 한다.
		ver = ver->link;
	}
	ver = g[v].vlist->head;//ver과 pre가 삭제할 v간선의 헤드포인터가 가리키는 곳을 가리키도록 하고
	pre = g[v].vlist->head;
	while (ver != NULL)  //간선 탐색이 끝날때까지
	{
		if (ver->num == u) //u간선의 값과 입력한 값이 같으면
		{
			deletesearch(g[v].vlist, ver, pre);  //함수 호출하여 해당 간선 해제
			break;  //반복 종료
		}
		pre = ver; //아니면 pre가 ver을 ver이 ver다음 값을 가리키도록 한다.
		ver = ver->link;
	}

	return 0;
}
int depthFS(Graph* g,int v) /* depth fisrt search using stack */
{
	if (empty[v] == 0)  //해당 정점의 생성기록이 존재하지 않는다면
	{
		printf("생성되지 않은 정점입니다.\n");  //안내문 출력 후
		return 0;  //함수 종료
	}
	VertexHead* h =g[v].vlist;  //탐색할 정점의 헤드포인터를 가리키도록 한다.
	Vertex* ver = h->head;  //헤드포인터의 간선의 첫번째 목록을 가리키도록 한다.

	visited[v] = 1;  //해당 정점의 방문기록을 만들어준다.
	printf("%5d", v);  //해당 정점을 출력한다.
	for (h = g[v].vlist; ver; ver=ver->link)  //각 간선의 탐색이 끝날때까지
		if (!visited[ver->num])  //해당 정점의 방문기록이 없다면
			depthFS(g,ver->num);  //해당 정점을 탐색 정점으로 하여 함수 본인을 호출한다.
	return 0;

}
int breadthFS(Graph *g,int v) /* breadth first search using queue */
{
	if (empty[v] == 0)  //해당 정점의 생성기록이 존재하지 않는다면
	{
		printf("생성되지 않은 정점입니다.\n");  //안내문 출력 후
		return 0;  //함수 종료
	}

	visitedreset();         //방문기록을 초기화해준다.
	VertexHead* h = g[v].vlist;  //헤드포인터가 탐색을 시작한 정점의 헤드포인터를 가리키도록 한다.

	Vertex* ver = h->head;  //탐색할 정점의 처음 인접한 정점을 가리키도록 한다.
	LQueueType* q;  //이용할 큐를 선언해 준 후
	q = createLinkedQueue();  //큐를 초기화해준다.
	visited[v] = 1;  //해당 정점의 방문기록을 1로 만들어주어 다음에 같은 곳을 방문하지 않도록 한다.
	printf("%5d", v);  //해당 정점을 출력해준다.
	enQueue(q, v);  // 해당 정점의 값을 큐에 삽입한다.
	while (q->front)  //큐가 비어있지 않을동안
	{
		v = deQueue(q);  //v에 입력한 정점을 다시 넣어준 후
		h = g[v].vlist;  //헤드포인터에 그 정점에 대한 정보를 저장한다.
		ver = h->head;  //ver에 그 정점의 인접 정점에 대한 정보를 저장한다.
 		for(;ver;ver=ver->link)  //해당 정점의 인접 정점의 탐색이 끝날때까지
			if (!visited[ver->num])  // 해당 정점의 방문이 존재하지 않으면
			{
				visited[ver->num] = 1;  // 방문기록을 1로 만들어주고
				printf("%5d", ver->num);  //정점을 출력한 뒤
				enQueue(q, ver->num);  //그 정점을 큐에 삽입하여 준다.
			}
	}

}
