#include "stdio.h"
#define MAX_Vertices 20
#define MAX_Lenght 20

//QUEUE
typedef struct{
	int data[MAX_Lenght];
	int front;
	int rear;
} Queue;

void make_null_Queue(Queue *Q) {
	Q->front = 0;
	Q->rear = -1;
}

void push_Queue(Queue *Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}

int empty_Queue(Queue *Q) {
	return (Q->front>Q->rear);
}

void pop(Queue *Q) {
	Q->front++;
}

int top(Queue *Q) {
	return Q->data[Q->front];
}

//LIST
typedef struct {
	int data[MAX_Lenght];
	int size;
} List;

void make_null(List *L) {
	L->size = 0;
}

void push_List(List *L, int x) {
	L->data[L->size] = x;
	L->size++;
}

int retrieve(List *L, int i) {
	return L->data[i-1];
}


typedef struct {
	 int A[MAX_Vertices][MAX_Vertices];
	 int n;
}Graph;

void init_Graph(Graph *G, int n) {
	int i, j;
	G->n = n;
	for(i=1; i<=G->n; i++) {
		for(j=1; j<=n; j++) {
			G->A[i][j] = 0;
		}
	}
}

void add_Edge(Graph *G, int a, int b) {
	G->A[a][b] = 1;
	G->A[b][a] = 1;
}

int adjacent(Graph *G, int a, int b) {
	return G->A[a][b] != 0;
}

int degree(Graph *G, int n) {
	int i;
	int deg = 0;
	for(i=1; i<=G->n; i++) {
		if(G->A[i][n] == 1) deg++;
	}
	return deg;
}

List neightbots(Graph *G, int n) {
	int i;
	List L;
	make_null(&L);
	for(i=1; i<=G->n; i++) {
		if(adjacent(G, i, n)) 
			push_List(&L, i);
	}
	return L;
}

void print_Graph(Graph *G) {
	int i, j;
	for(i=1; i<=G->n; i++) {
		for(j=1; j<=G->n; j++) {
			printf("%d ", G->A[i][j]);
		}
		printf("\n");
	}
}

List BFS(Graph *G, int n, int parent[]) {
	Queue Q;make_null_Queue(&Q);
	int mark[MAX_Lenght];
	int i, u, v;
	for(i=1; i<=G->n; i++) {
		mark[i] = 0;
	}
	List L, save;
	make_null(&save);
	make_null(&L);
	push_Queue(&Q, n);
	parent[n] = 0;
	while(!empty_Queue(&Q)) {
		u = top(&Q);
		pop(&Q);
		if(mark[u] == 1) 
			continue;
		push_List(&save, u);
		mark[u] = 1;
		L = neightbots(G, u);
		for(i=1; i<=L.size; i++) {
			v = retrieve(&L, i);
			if(mark[v] == 0) {
				push_Queue(&Q, v);
				if(parent[v] == -1)
					parent[v] = u;
			}
		}
	} 
	return save;
}

int main() {
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int u, v, i, j;
	for(i=1; i<=m; i++) {
		scanf("%d%d", &u, &v);
		add_Edge(&G, u, v);
	}
	print_Graph(&G);
	printf("\n\n\n");
	int c;
	int mark[MAX_Lenght];
	int parent[MAX_Lenght];		
	for(i=1; i<=G.n; i++) {
		mark[i] = 0;
		parent[i] = -1;
	}
		

	for(i=1; i<=G.n; i++) {
		if(mark[i] == 0) {
			List L = BFS(&G, i, parent);
			for(j=1; j<=L.size; j++) {
				c = retrieve(&L, j);
				printf("%d", c);
				mark[c] = 1;
			}
			printf("\n");
		}
	}
	
	
	for(i=1; i<=G.n; i++) {
		printf("parent[%d] = %d\n", i, parent[i]);
	}
	return 0;
}
