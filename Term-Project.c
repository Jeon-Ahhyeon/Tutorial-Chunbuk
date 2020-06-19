/*
 ============================================================================
 Name        : Term-Project.c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20// �ִ� ũ�⸦ 20���� ��Ҵ� �ؿ� �ڵ忡���� 0~20���� ������ ���� MAX_VERTEX+1 �̶�� �ۼ��Ͽ���.

typedef struct Vertex {  //�������� edge��Ÿ��
	int num;  // ������ȣ
	struct Vertex* link;  //������ ������ ����Ű�� ����
}Vertex;

typedef struct VertexHead {  //����
	Vertex* head;  //�������� ������ ��Ÿ��
}VertexHead;

typedef struct Graph {  //��ü �׷���
	VertexHead* vlist;  //������ ����Ų��.
}Graph;

int visited[MAX_VERTEX + 1] = { 0 };  //Ž���� �� �湮���θ� ��Ÿ���� �����迭  ó������ 0���� �ʱ�ȭ�Ѵ�.

void visitedreset()   // Ž���Լ����� �����迭�� �ʱ�ȭ�� �� ����ϱ� ���� �ۼ�
{
	for (int i = 0; i < MAX_VERTEX + 1; i++)  //�����迭�� �ʱ�ȭ���ش�.
		visited[i] = 0;
}

//typedef int element;

typedef struct QNode {  //breadthFS()�Լ����� ť�� �̿��ϱ� ���� �ۼ�
	int data;  //Q�� ��
	struct QNode* link;  //Q�� ���� ���� ��
}QNode;

typedef struct {  //Q�� front�� rear�� ��Ÿ��
	QNode* front,*rear;
}LQueueType;

LQueueType* createLinkedQueue() {  //Q�� ������ �� �ʱ�ȭ ���ִ� �Լ�
	LQueueType* LQ = (LQueueType*)malloc(sizeof(LQueueType));  //������ �ڷ������� LQ�� �����Ҵ��� ��
	LQ->front = NULL;  //front�� rear�� NULL�� �ʱ�ȭ���ش�.
	LQ->rear = NULL;
	return LQ;  //���� Q�� ��ȯ�Ѵ�.
}

int isEmpty(LQueueType *LQ)  //Q�� ������� Ȯ�����ִ� �Լ�
{
	if (LQ->front == NULL)  //front�� NULL�̶�� Q�� ����ִٴ� ��
	{
		printf("����ִ� ť�Դϴ�.\n");  //�ȳ��� ��� ��
		return 1;  //1��ȯ
	}
	else
		return 0;  //������� �ʴٸ� 0��ȯ
}

void enQueue(LQueueType* LQ, int item)  //Q�� data�� �߰����ִ� �Լ�
{
	QNode* q = (QNode*)malloc(sizeof(QNode));  //q�� �������� �Ҵ����ش�.
	q->data = item;  //�Ҵ���� q�� data�� ������ ���� �Է��ϰ�
	q->link = NULL;  //q�� ����Ű�� ���� ���� NULL�� �ʱ�ȭ�Ѵ�.
	if (LQ->front == NULL)  //ť�� ����־��ٸ�
	{
		LQ->front = q;  //Q�� front�� rear�� q�� ����Ű���� �Ѵ�.
		LQ->rear = q;
	}
	else {  //�ƴ϶��
		LQ->rear->link = q;  //rear�� ���� ����Ű�� ���� q�� ����Ű���� �Ѵ�.
		LQ->rear = q;
	}
}

int deQueue(LQueueType* LQ)  //Q���� �ϳ��� ���ִ� �Լ�
{
	QNode* old = LQ->front;  //Q�� front���� �����Ѵ�.
	int item;  //�� ���� ������ ����
	if (isEmpty(LQ)) return 0;  //Q�� ����ִٸ� �Լ� ����
	else {  //������� �ʴٸ�
		item = old->data;  //Q�� ù��° ���� item�� ����
		LQ->front = LQ->front->link;  //ù��° ��ũ�� �ι�° ��ũ�� ����Ű���� �� ��.
		if (LQ->front == NULL)  //���� ù��° �ڸ��� NULL�̶��
			LQ->rear = NULL;  //rear�� NULL�� �ʱ�ȭ���ش�.
		free(old);  //�������� �Ҵ���� old�� �޸𸮸� �����Ѵ�.
		return item;  //�Ʊ� ���� ���� ��ȯ�Ѵ�.
	}
}
int empty[MAX_VERTEX+1];  //������ ������� �Ȼ������ Ȯ���ϴ� �����迭

/*�߰� ������ �Լ�*/
int insertsearch(VertexHead* h, int v);   //insert�� �䱸�ϴ� insertEdge�Լ����� ��� -> ���� ������������ �����ϱ� ���� ���
int deletesearch(VertexHead* h, Vertex* ver, Vertex* pre);  //delete�Լ����� ���ϴ� ������ ã�� �� �����ϱ� ���� ����

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
	char command;//�Է¹޴� �޴�
	int key;  //�Է¹޴� Ű
	int u, v;  //  �Է¹޴� ����
	Graph* graph = NULL;//�׷��� ����

	printf("������ 2018068005\n");  //���� �̸� ���

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     ������ Graph Function       \n");   //�޴� ���
		printf("----------------------------------------------------------------\n");
		printf(" Create          = c         Print Graph      = p \n");
		printf(" Insert Vertex   = v         Delete Vertex    = d \n");
		printf(" Insert Edge     = e         Delete Edge      = l\n");
		printf(" DepthFS         = f         BreadthFS        = b\n");
		printf(" Quit            = q                \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);  //�޴� �Է¹ޱ�

		switch (command) {  //����ġ ���� ����Ͽ�
		case 'c': case 'C':  //�ʱ�ȭ�޴� ���ý�
			graph = createGraph(graph);   //�ʱ�ȭ �Լ� ȣ��
			break;
		case 'p': case 'P':    //���� ����Ʈ ����ϴ� �Լ� ȣ��
			printGraph(graph);
			break;
		case 'v': case 'V':    //���� �����ϴ� �Լ� ȣ��
			printf("Insert Vertex NUM = ");
			fflush(stdout);
			scanf("%d", &key);   // ������ Ű �Է�
			insertVertex(graph, key);
			break;
		case 'd': case 'D':    //������ �����ϴ� �Լ� ȣ��
			printf("Delete Vertex NUM = ");
			fflush(stdout);
			scanf("%d", &key);  //������ Ű �Է�
			deleteVertex(graph, key);
			break;
		case 'e': case 'E':    //������ ������ �Լ� ȣ��
			printf("-----(u,v)------\n");
			printf("Insert Edge u = ");      //���� �ΰ� �Է�
			fflush(stdout);
			scanf("%d", &u);
			printf("Insert Edge v = ");
			fflush(stdout);
			scanf("%d", &v);
			insertEdge(graph, u, v);
			break;
		case 'l': case 'L':   //������ �����ϴ� �Լ� ȣ��
			printf("-----(u,v)------\n");  //���� �ΰ� �Է�
			printf("Insert Edge u = ");
			fflush(stdout);
			scanf("%d", &u);
			printf("Insert Edge v = ");
			fflush(stdout);
			scanf("%d", &v);
			deleteEdge(graph, u, v);
			break;
		case 'f': case 'F':   //�׷��� ���� �켱 Ž�� �Լ� ȣ��
			visitedreset();  //ȣ�� �� �湮 ��� �ʱ�ȭ
			printf("SELECT VERTEX NUM = ");  //������ ������ �����Ѵ�.
			fflush(stdout);
			scanf("%d", &key);
			depthFS(graph,key);  // �Լ� ȣ��
			printf("\n");
			break;
		case 'b': case 'B':
			printf("SELECT VERTEX NUM = ");  //�ʺ�켱 Ž���Լ� ȣ��
			fflush(stdout);
			scanf("%d", &key);  //������ ���� ����
			breadthFS(graph,key);
			printf("\n");
			break;
		case 'q': case 'Q':   // �׷��� ���α׷� ����
			destroyGraph(graph);  //�������� �Ҵ���� �׷����� �� ���Ҹ� �����ϴ� �Լ�
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//�޴��� �߸� �Է¹��� ��� �ٽ� �Է¹ޱ�
			break;
		}
	} while (command != 'q' && command != 'Q');  //q�� �Է����� �ʾҴٸ� �޴� ��� ����


}


Graph* createGraph(Graph* g) /* empty graph creation */
{
	if (g != NULL) //�׷����� ������� �ʴٸ�
		destroyGraph(g);  //�׷����� ������ �� �� ���� �ڵ� ����

	Graph* graph = (VertexHead*)malloc(sizeof(VertexHead)*(MAX_VERTEX+1)); //  �׷����� ���� �迭�� MAX_VERTEX+1ũ�� ��ŭ �Ҵ����ش� 0~20�� �� �Է� ����

	for (int i = 0; i < MAX_VERTEX+1; i++)  //���� �迭�� ũ�⸸ŭ
	{
		graph[i].vlist = NULL;  //�׷����� vlist�� NULL�� �ʱ�ȭ ���ְ�
		empty[i] = 0;  //vlist�� ���� ����� �ʱ�ȭ���ش�.
	}
	return graph;  //������ �׷�������Ʈ�� ��ȯ�Ѵ�.
}
int destroyGraph(Graph* g) /* deallocating all allocated memory */
{
	VertexHead* h;  //��� ������
	Vertex* v;  //����������
	Vertex* vprev = NULL;  //������ ������

	for (int i = 0; i < MAX_VERTEX + 1; i++)  //�迭�� ũ�⸸ŭ
	{
		if (empty[i] == 1)  //���� ������ �����Ǿ� �ִٸ�
		{
			h = g[i].vlist;  //��������Ϳ� ������ �����ϰ�
			v = h->head;  // ������ �������� �����Ѵ�.
			while (v != NULL) //������ ������ ������ ������
			{
				vprev = v;
				v = v->link;
				free(vprev); //������ �������ش�.
			}
			free(h);  //��������͵� �������ش�.
		}
	}
	free(g);  //�� �����ٸ� ���������� graph�� �޸𸮸� �������ش�.


}
int printGraph(Graph* g) /* printing graph with vertices and edges */
{
	Vertex* p;//����� ����

	for (int i = 0; i <( MAX_VERTEX + 1); i++)//������� �迭�� ũ�⸸ŭ
	{
		if (empty[i] != 0)  //������ �������θ� Ȯ���Ͽ� �����Ǿ��ٸ�
		{
			p = g[i].vlist->head;  //p�� ������ ������ �����͸� �Ѱ��� ��
			printf("\t[%d]�� ��������Ʈ : ",i);  // ������ ���
			while (p != NULL)  //����� ������ ����������
			{
				printf("  ->  [%d]", p->num);  //p�� �� ���
				p = p->link;  //p�� ���� ���� ����Ű���� ��
			}
			printf("\n");  //���๮�� �����
		}
	}
}
int insertVertex(Graph *g,int v)  //������ �����ϴ� �Լ�
{
	VertexHead* head = (VertexHead*)malloc(sizeof(VertexHead));  //������ ��������� �����Ҵ�
	head->head = NULL;  //����� ���� NULL�� �ʱ�ȭ


	if (empty[v] != 0)  //�ش� ������ ��������� ���ٸ�
	{
		printf("%d�� �̹� ������� �����Դϴ�.\n", v);//�ȳ��� ��� �� �Լ� ����
		return 0;
	}
	else if (v > MAX_VERTEX+1)  // ���� ������ ���� ������ �ʰ��Ͽ��ٸ� �ȳ��� ��� ��
	{
		printf("������ ������ �ʰ��Ͽ����ϴ�.\n");
		return 0;
	}
	else if (v < 0)
	{
		printf("�Է¹��� ���� ������ ������ϴ�.\n");
		return 0;  //�Լ� ����
	}

	empty[v] = 1;  //������� ������ ���� ����� 1�� �ٲ���
	g[v].vlist = head;  //�ش� �׷����� ������� ���� �����͸� ����Ű���� �� ��
	return 1;  //�Լ� ����

}

int insertEdge(Graph* g, int u, int v) /* new edge creation between two vertices */
{
	if (empty[u] == 0 || empty[v] == 0) //�Է��� ������ ��������� ���ٸ�
	{
		printf("�׷����� �ش� ������ �������� �ʽ��ϴ�.\n");  //�ȳ��� ��� �� �Լ� ����
		return 0;
	}
	else if (v > MAX_VERTEX || u > MAX_VERTEX || v < 0 || u < 0 )  //�Է¹����� �ʰ��Ͽ��ٸ�
	{
		printf("������ �߸��Է��Ͽ����ϴ�.\n");  //�ȳ��� ��� ��
		return 0;  //�Լ� ����
	}

	insertsearch(g[u].vlist, v);  //���� u�� ���ؼ� v������ �Է��ϴ� �Լ� ȣ��
	insertsearch(g[v].vlist, u);  //���� v�� ���ؼ� u������ �Է��ϴ� �Լ� ȣ��

	return 0;
}
int insertsearch(VertexHead* h, int v)  //������ ã�� �Է����ִ� �Լ�
{
	Vertex* ver = (Vertex*)malloc(sizeof(Vertex));  //�Է��� ���� ���� �Ҵ�
	ver->num = v;  // �Է¹��� ������ �Է�
	ver->link = NULL;  // link���� �ʱ�ȭ �Ѵ�.
	Vertex* pre;  //ver�� �� �ڸ��� ���� ��
	Vertex* p;  //ver�� �� �ڸ��� ���� ��

	if (h->head == NULL)  //��� ������ ������ ��������� �ʾҴٸ�
	{
		h->head = ver;  //��������Ͱ� ver�� ����Ű���� �� ��
		return 0;  //�Լ��� �����Ѵ�.
	}
	p = h->head;  //������ Ž���ϱ� ���� p�� pre�� ���� ��������Ͱ� ����Ű�� �� �Է�
	pre = h->head;
	while (p != NULL)  //������ ��� Ž���Ҷ�����
	{
		if (p->num > v) {  //p�� ����Ű�� ���� �Է¹��� �������� ũ��
			if (p == h->head)  //�� �ڸ��� ó���̶��
			{
				h->head = ver;  //��������Ͱ� ver�� ����Ű���� �ϰ�
				ver->link = p;  //ver�� ���� ��������Ͱ� ����Ų ù��° ���� ����Ű���� �Ѵ�.
			}
			else  //ù��° �ڸ��� �ƴ϶��
			{
				ver->link = pre->link;  //ver�� �� �ڸ��� �����ڸ��� ���� ��ũ�� ����Ű���� �ϰ�
				pre->link = ver;  //pre�� ���� ��ũ�� ver�� ����Ű���� �Ѵ�.
			}
			return 0;  //�Լ��� �����Ѵ�.
		}
		else if (p->num == v)  //���� �Է��� ������ �����Ѵٸ�
			return 0;  //�ƹ��͵� ���� �ʰ� �Լ��� �����Ѵ�.
		pre = p;  //pre�� p��
		p = p->link; //p�� �� ���� ��ũ�� ����Ű���� �Ѵ�.
	}
	pre->link = ver;  //�� �ڸ��� �� ������ ��ũ��� pre��ũ�� ver�� ����Ű���� �Ѵ�.
	return 0;  //���α׷��� �����Ѵ�.
}

int deleteVertex(Graph* g, int v) /* edge removal */
{
	VertexHead* head;  //Ž���� ������ �������Ʈ
	Vertex* ver,*pre;  //������ ���� ���� ���
	if (empty[v] == 0)  //���� �ش� ������ ��������� �������� �ʴ´ٸ�
	{
		printf("%d������ �������� �ʽ��ϴ�.\n");  //�ȳ��� ��� �� �Լ� ����
		return 0;
	}
	else if(v<0 || v>MAX_VERTEX+1)  //���� ������ ������ ������ ����ٸ�
	{
		printf("�Է��� ������ ������ �ʰ��Ͽ����ϴ�.\n");  //�ȳ��� ��� ��
		return 0; //�Լ� ����
	}

	for (int i = 0; i < (MAX_VERTEX + 1); i++)  //������� �迭�� ũ�⸸ŭ
	{
		if (empty[i] != 0) {  //������ ��������� �����Ѵٸ�
			head = g[i].vlist;  //��������Ͱ� ������ ����Ű���� �ϰ�
			if (head->head != NULL)  //������ ������ ������ ���
			{
				ver = head->head;  //ver�� pre�� ��������� ������ ó���� ����Ű���� �� ��
				pre = head->head;
				while (ver != NULL)  //������ ��� Ž���� ������
				{
					if (ver->num == v)  //����� ������ ������ �Է¹��� ���� ���Ƹ�
					{
						deletesearch(g[i].vlist, ver, pre);  //�ش� ������ �������ִ� �Լ��� ȣ��
						break;  //�ݺ����� �����Ѵ�.
					}
					pre = ver;//pre�� ver��
					ver = ver->link; //ver�� pre�� ����Ű���� �Ѵ�.
				}
			}
		}
	}


	empty[v] = 0;  //�ش� ������ ���� ����� 0���� �ʱ�ȭ �Ѵ�.
	return 0;
}
int deletesearch(VertexHead * h,Vertex* ver,Vertex*pre)  //������ �������ִ� �Լ�
{
	if (ver == h->head)  //������ ������ ù��°���
	{
		h->head = ver->link;  //��������Ͱ� ver�� ������ ����Ű���� �� ��
		free(ver);  //ver����
		return 0;//���α׷� ����
	}
	else  //�ƴ϶��
	{
		pre->link = ver->link;  //pre�� ����Ű�� ���� ver�� ���� ������ �ٲ� ��
		free(ver);  //ver�� ����������
		return 0;  //�Լ� ����

	}
	return 0;
}
int deleteEdge(Graph* g, int u, int v) /* edge removal */
{
	Vertex* ver,*pre;  //������ ������ ���� ���� ����
	if (empty[v] == 0 || empty[u] == 0)  //�Է¹��� ������ ��������� �������� �ʴ´ٸ�
	{
		printf("�Է��Ͻ� ������ �������� �ʽ��ϴ�.\n");  //�ȳ��� ��� ��
		return 0; //�Լ� ����
	}
	else if (v<0 || v>(MAX_VERTEX+1))  //���� �Է��� ������ ������ �߸��Ǿ��ٸ�
	{
		printf("�Է��� ������ ������ �ʰ��Ͽ����ϴ�.\n");  //�ȳ��� ��� ��
		return 0;  //�Լ� ����
	}

	ver = g[u].vlist->head;  //ver�� pre�� ������ u������ ��������Ͱ� ����Ű�� ���� ����Ű���� �ϰ�
	pre = g[u].vlist->head;
	while (ver != NULL)  //���� Ž���� ����������
	{
		if (ver->num == v)  //v������ ���� �Է��� ���� ������
		{
			deletesearch(g[u].vlist, ver, pre);  //�Լ� ȣ���Ͽ� �ش� ���� ����
			break;  //�ݺ��� �����Ѵ�.
		}
		pre = ver;  //�ƴϸ� pre�� ver�� ver�� ver���� ���� ����Ű���� �Ѵ�.
		ver = ver->link;
	}
	ver = g[v].vlist->head;//ver�� pre�� ������ v������ ��������Ͱ� ����Ű�� ���� ����Ű���� �ϰ�
	pre = g[v].vlist->head;
	while (ver != NULL)  //���� Ž���� ����������
	{
		if (ver->num == u) //u������ ���� �Է��� ���� ������
		{
			deletesearch(g[v].vlist, ver, pre);  //�Լ� ȣ���Ͽ� �ش� ���� ����
			break;  //�ݺ� ����
		}
		pre = ver; //�ƴϸ� pre�� ver�� ver�� ver���� ���� ����Ű���� �Ѵ�.
		ver = ver->link;
	}

	return 0;
}
int depthFS(Graph* g,int v) /* depth fisrt search using stack */
{
	if (empty[v] == 0)  //�ش� ������ ��������� �������� �ʴ´ٸ�
	{
		printf("�������� ���� �����Դϴ�.\n");  //�ȳ��� ��� ��
		return 0;  //�Լ� ����
	}
	VertexHead* h =g[v].vlist;  //Ž���� ������ ��������͸� ����Ű���� �Ѵ�.
	Vertex* ver = h->head;  //����������� ������ ù��° ����� ����Ű���� �Ѵ�.

	visited[v] = 1;  //�ش� ������ �湮����� ������ش�.
	printf("%5d", v);  //�ش� ������ ����Ѵ�.
	for (h = g[v].vlist; ver; ver=ver->link)  //�� ������ Ž���� ����������
		if (!visited[ver->num])  //�ش� ������ �湮����� ���ٸ�
			depthFS(g,ver->num);  //�ش� ������ Ž�� �������� �Ͽ� �Լ� ������ ȣ���Ѵ�.
	return 0;

}
int breadthFS(Graph *g,int v) /* breadth first search using queue */
{
	if (empty[v] == 0)  //�ش� ������ ��������� �������� �ʴ´ٸ�
	{
		printf("�������� ���� �����Դϴ�.\n");  //�ȳ��� ��� ��
		return 0;  //�Լ� ����
	}

	visitedreset();         //�湮����� �ʱ�ȭ���ش�.
	VertexHead* h = g[v].vlist;  //��������Ͱ� Ž���� ������ ������ ��������͸� ����Ű���� �Ѵ�.

	Vertex* ver = h->head;  //Ž���� ������ ó�� ������ ������ ����Ű���� �Ѵ�.
	LQueueType* q;  //�̿��� ť�� ������ �� ��
	q = createLinkedQueue();  //ť�� �ʱ�ȭ���ش�.
	visited[v] = 1;  //�ش� ������ �湮����� 1�� ������־� ������ ���� ���� �湮���� �ʵ��� �Ѵ�.
	printf("%5d", v);  //�ش� ������ ������ش�.
	enQueue(q, v);  // �ش� ������ ���� ť�� �����Ѵ�.
	while (q->front)  //ť�� ������� ��������
	{
		v = deQueue(q);  //v�� �Է��� ������ �ٽ� �־��� ��
		h = g[v].vlist;  //��������Ϳ� �� ������ ���� ������ �����Ѵ�.
		ver = h->head;  //ver�� �� ������ ���� ������ ���� ������ �����Ѵ�.
 		for(;ver;ver=ver->link)  //�ش� ������ ���� ������ Ž���� ����������
			if (!visited[ver->num])  // �ش� ������ �湮�� �������� ������
			{
				visited[ver->num] = 1;  // �湮����� 1�� ������ְ�
				printf("%5d", ver->num);  //������ ����� ��
				enQueue(q, ver->num);  //�� ������ ť�� �����Ͽ� �ش�.
			}
	}

}
