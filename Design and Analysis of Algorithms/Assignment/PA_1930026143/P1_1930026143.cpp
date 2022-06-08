// The taks I select are 1, 2, 3
/* Reference: 1. http://c.biancheng.net/cpp/html/175.html
              2. https://blog.csdn.net/weixin_30855761/article/details/97604505
*/ 
// programmer: Jack    1930026143


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    // The values (data) in the stack is more tahn one at a floor.
    int **values;
	int top;
	int maxTop;
} Stack;

// The edge structure
typedef struct Edge
{
    int start_point;
    int end_point;
    int weight;
} Edge;

// The graph structure
typedef struct {
    // weight and adj can be viewed as a two-dimensional array
    int root_state;
    int **weight;
    int *discovery_time;
    int *depth;
    // adjacent matrix
    int **adj;
    char *color;
    int numOfVertice;
    int numOfEdge;
    int *pred;
} Graph;


// detemine if the stack is empty
bool IsEmpty(Stack* stack){
	if(stack == NULL){
		printf("The stack is NULL");
		return true;;
	}
	if(stack->top == -1)
		return true;
	else
		return false;
}

// detemine if the stack is full
bool IsFull(Stack* stack){
	if(stack == NULL){
		printf("The stack is NULL");
		return false;
	}
	if(stack->top == stack->maxTop)
		return true;
	else
		return false;
}


bool CreateStack(Stack *stack, int size){
    // Detemine the maxTop if is larger than zero
	if(size <= 0)
		return false;

    // Allocate memory space 
    stack->values = (int**)malloc(sizeof(int*)*size);
    for (int i = 0; i < size; i++){
        stack->values[i] = (int*)malloc(sizeof(int)*size);
    }

    // The initialization default value is -1 and the stack is empty
	stack -> top = -1;
	stack -> maxTop = size -1;
	return true;
}

bool Push(Stack *stack, int *x){
    // If the stack is full, we cannot push something
	if(IsFull(stack)){
        printf("full");
		return false;
    }
    // printf("%d__%d  ", x[0], x[1]);
	stack->values[++stack->top][0] = x[0];
	stack->values[stack->top][1] = x[1];
	return true;
}

bool Pop(Stack *stack, int *x){
    // If the stack is full, we cannot push something
	if(IsEmpty(stack) == true)
		return false;

    // x is a pointer to top_value
	x[0] = stack->values[stack->top][0];
	x[1] = stack->values[stack->top][1];
    // Or stack->values[stack->top--] = NULL;
	stack->values[stack->top][0] = NULL;
    stack->values[stack->top][1] = NULL;
	stack->top--;
	return true;
}

void DisplayStack(Stack* stack){
    // Detemined if the stack is empty
	if(stack == NULL || IsEmpty(stack) == true){
		printf("\nThe stack is NULL or not existing");
		return;
	}
    
    printf("\nThe stack has these number: ");
    // Start at zero and stop at top
	for(int i=stack->top; i>=0; i--){
        // Keep two decimals
		printf("%d--%d ", stack->values[i][0], stack->values[i][1]);
	}
}

void DestroyStack(Stack **pstack){
    // clear the stack
	free((*pstack) -> values);
	(*pstack)->top = -1;
	(*pstack)->maxTop = 0;
	free(*pstack);
	*pstack = NULL;
    printf("\nDestroy the stack successfully!");
}

bool Top(Stack* stack, int* x){
	if(stack == NULL){
		printf("The stack is NULL");
		return false;
	}
    if(IsEmpty(stack) == true){
        return false;
    }
    // x pointee to the top value
    x[0] = stack->values[stack->top][0];
	x[1] = stack->values[stack->top][1];
	return true;
}

// Initalize the graph struct
// After an operation, some of values in the structure will be changed
// It must be set to the initial value then we can do the next operation
int Initialize (Graph *graph){
    for (int i = 0; i < graph->numOfVertice; i++) {
        graph->color[i] = 'W';
    }
    for (int i = 0; i < graph->numOfVertice; i++){
        graph->discovery_time[i] = 0;
    }
    for (int i = 0; i < graph->numOfVertice; i++){
        graph->depth[i] = 0;
    }
    for (int i = 0; i < graph->numOfVertice; i++){
        graph->pred[i] = -1;
    }
    for (int i = 0; i < graph->numOfVertice; i++){
        graph->root_state = 0;
    }
    return 0;
}

// Operation 1:
// Find the all while vertice after recursion
int DFSVisit(Graph graph, int i){
    graph.color[i] = 'G';
    for (int j = 0; j < graph.numOfVertice; j++){
        // It don't have to judge for itself
        if(i != j && graph.adj[i][j] != 0){
            // printf("%d", graph.startPoint[i]);
            // Find the next white vertex
            if(graph.color[j] == 'W'){
                printf("%d--%d ", i, j);
                graph.pred[j] = i;
                // Recursion by the adj vertex
                DFSVisit(graph, j);
            }
        }
    }
    graph.color[i] = 'B';
    return 0;
}

// Begin of the finding
int DFS(Graph *graph){
    for (int i = 0; i < graph->numOfVertice; i++){
        if(graph->color[i] == 'W')
            DFSVisit(*graph, i);
    }
    return 0;
}

// Find all of articulation point bt dfs visit
int ArtPt(Graph *graph, int i, int *time, int *ArticulationPoint){
    graph->color[i] = 'G';
    graph->depth[i] = graph->discovery_time[i] = ++(*time);
    // printf("dicovertime[%d]: %d\n", i, graph->discovery_time[i]);
    // printf("dicovertime[%d]: %d\n", i, graph->depth[i]);
    int cnt = 1;
    for (int j = 0; j < graph->numOfVertice; j++){
        if(i != j && graph->adj[i][j] != 0){
            // printf("i=%d, j=%d", i, j);
            if(graph->color[j] == 'W'){
                graph->pred[j] = i;
                ArtPt(graph, j, time, ArticulationPoint);
                if (graph->pred[i] == -1){
                    // The cnt is used to count the recursion
                    // If the root recurse more than one time, then it has more than two point
                    // Which means it is an articulation point
                    if (cnt >=  2){
                        // printf("\nVertex %d", i);
                        ArticulationPoint[i] = 1;
                    }
                }
                else if (graph->depth[j] >= graph->discovery_time[i]){
                    // Its child can reach the higer than it this vertex.
                    ArticulationPoint[i] = 1;
                }
                // update the depth/low of the vertex
                graph->depth[i] = ((graph->depth[i]<graph->depth[j]) ?  graph->depth[i] : graph->depth[j]);
            }
            else if (j != graph->pred[i]){
                // update the depth/low of the vertex
                graph->depth[i] = ((graph->depth[i]<graph->discovery_time[j]) ?  graph->depth[i] : graph->discovery_time[j]);
            }
            cnt++;
        }
    }
    // The vertex finish, the color bof it become black
    graph->color[i] = 'B';
    return 0;
}

int ReArtPt(Graph *graph, int i, int *time, Stack **stack){
    graph->color[i] = 'G';
    graph->depth[i] = graph->discovery_time[i] = ++(*time);
    // printf("dicovertime[%d]: %d\n", i, graph->discovery_time[i]);
    // printf("dicovertime[%d]: %d\n", i, graph->depth[i]);
    int cnt = 1;
    for (int j = 0; j < graph->numOfVertice; j++){
        if(i != j && graph->adj[i][j] != 0){
            // It don't have to judge for itself
            if(graph->color[j] == 'W'){
                int a[2];
                a[0] = i, a[1]= j;
                // Push the dicovered vertices to thestack
                Push(*stack, a);
                // DisplayStack(*stack);
                graph->pred[j] = i;
                ReArtPt(graph, j, time, stack);
                if (graph->pred[i] == -1){
                    // The cnt is used to count the recursion
                    // If the root recurse more than one time, then it has more than two point
                    // Which means it is an articulation point
                    if (cnt >=  2){
                        // printf("\nVertex %d", i);
                        int lst[2];
                        lst[0] = lst[1] = -1;
                        while (1)
                        {   
                            // If it not meet the articulation point
                            if(lst[0] != i){
                                Pop(*stack, lst);
                                printf("%d--%d ", lst[0], lst[1]);
                            }
                            else{
                                break;
                            }
                        }
                        // specification format
                        printf("    ");
                    }
                }
                else if (graph->depth[j] >= graph->discovery_time[i]){
                    // DisplayStack(&stack);
                    // printf("Vertex: %d ", i);
                    int lst[2];
                    lst[0] = lst[1] = -1;
                    while (1) {   
                        // If it not meet the articulation point
                        if(lst[0] != i) {
                            // 
                            Pop(*stack, lst);
                            printf("%d--%d ", lst[0], lst[1]);
                        }
                        else
                            break;
                    }
                    printf("    ");
                }
                // update the low of the vertex
                graph->depth[i] = ((graph->depth[i]<graph->depth[j]) ?  graph->depth[i] : graph->depth[j]);
            }
            else if (j != graph->pred[i]){
                int a[2];
                a[0] = i, a[1]= j;
                // update the low of the vertex
                graph->depth[i] = ((graph->depth[i]<graph->discovery_time[j]) ?  graph->depth[i] : graph->discovery_time[j]);
                if(graph->discovery_time[j] < graph->discovery_time[i])
                    // push the back edge to the stack 
                    Push(*stack, a);
                // DisplayStack(*stack);
            }
            cnt++;
        }
    }
    // Finish and turns the color to the black
    graph->color[i] = 'B';
    return 0;
}

// Find the biconnected graph
int FindBiconnected(Graph *graph){
    int time = 0;
    // Create and initialize a stack
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    // Dynamically allocate a block of memory
    CreateStack(stack, 2*(graph->numOfEdge));
    for (int i = 0; i < graph->numOfVertice; i++){
        if(graph->color[i] == 'W')
            ReArtPt(graph, i, &time, &stack);
    }
    int lst[2];
    // If there some elements still exists in the stack, pop it out 
    while (!IsEmpty(stack)) {
        Pop(stack, lst);
        printf("%d--%d ", lst[0], lst[1]);
    }
    return 0;
}

// Find the articulation point
int FindArticulation(Graph *graph){
    int time = 0; // Pay attention to the time, it is an important parameter.
    int *ArticulationPoint = (int*)malloc(sizeof(int)*graph->numOfVertice);

    // Initialize the articulation point which is a list
    for(int i = 0; i < graph->numOfVertice; i++) {
        ArticulationPoint[i] = 0;
    }
    for (int i = 0; i < graph->numOfVertice; i++){
        if(graph->color[i] == 'W')
            ArtPt(graph, i, &time, ArticulationPoint);
    }
    // show the ArticulationPoint
    for(int i = 0; i < graph->numOfVertice; i++) {
        if (ArticulationPoint[i] == 1){
            printf("Vertex %d    ", i);
        // printf("%d ", ArticulationPoint[i]);
        }
    }
    return 0;
}

int MST_Kruskals(Edge **edge, int numOfEdge, int numOfVertice) {
    int *sort_lst = (int*)malloc(numOfEdge*sizeof(int));
	// Initialize a sort list
	for (int i=0; i<numOfVertice; i++){
		// It just a list to distinguish between each other
		sort_lst[i] = i;
	}
    // QuickSort(edge, 0, numOfEdge-1);
    Edge *temp = (Edge*)malloc(sizeof(Edge));

    // Bubble sort by the weight of edges
    for (int i = 0; i < numOfEdge; i++) {
        for(int j = 0; j < numOfEdge-1; j++) {
            if(edge[i]->weight < edge[j]->weight){
                temp = edge[i];
                edge[i] = edge[j];
                edge[j] = temp;
            }
        }
    }
	int k = 1;
    // The index of each edge
	int idx = 0;
    // If we need to calculate the weight, we need a variable to store the weight
	int weight = 0;

    // Start form 1 and end end with numOfVertice
    while(k < numOfVertice){
        // you can image a list from 1 to n, and n is the numOfVertice
        // left is the start_point and right is the end_point
		int left = edge[idx]->start_point;
		int right = edge[idx]->end_point;
		int cluster = sort_lst[left];
		int cluster_temp = sort_lst[right];

        // If the edge is not is the two cluster
        // Which means that it does not create a circle
		if(cluster != cluster_temp){
			printf("%d--%d    ", left, right);
			weight += edge[idx]->weight;
            // Add the vertex until all the edge are connected
			k++;
			for(int i = 0; i < numOfVertice; i++){
				if(sort_lst[i]==cluster_temp)
					sort_lst[i]=cluster;
			}
		}
        // The idx update each time
		idx++;
	}
    // printf("\ntotol_weight: %d", weight);
    return 0;
}

int main(){
    char fileName[50];    
    while(1){
        printf("\n***************\n");
        printf("Input the file name: \n");

        if(scanf("%s", fileName) != EOF){        
            FILE *fp;
            int numOfVertice = 0;
            int numOfEdge = 0;
            // 
            fp = fopen(fileName, "r");   //open .txt file to read
            if(fp == NULL){
                printf("The file The file does not exists!");
                continue;
            }
            // Get the number of vertices and edges
            fscanf(fp, "%d\n", &numOfVertice);
            fscanf(fp, "%d\n", &numOfEdge);

            int adj[numOfVertice];
            char color[numOfVertice];
            int weight[numOfVertice][numOfVertice];
            char verticeWeigth[20];

            // Create a dynamic space for structure Graph and Edge
            Graph *graph = (Graph*)malloc(sizeof(Graph));

            // Edge is a struct array: pointer of pointer
            Edge **edge = (Edge**)malloc(sizeof(Edge*)*numOfEdge);
            // Then create space to pointer
            for (int i = 0; i < numOfEdge; i++) {
                edge[i] = (Edge*)malloc(sizeof(Edge));
            }
            graph->color = (char*)malloc(sizeof(char)*numOfVertice);
            graph->pred = (int*)malloc(sizeof(int)*numOfVertice);
            graph->depth = (int*)malloc(sizeof(int)*numOfVertice); 
            graph->adj = (int**)malloc(sizeof(int*)*numOfVertice);
            for (int i = 0; i < numOfVertice; i++) {
                graph->adj[i] = (int*)malloc(sizeof(int)*numOfVertice);
            }
            graph->discovery_time = (int*)malloc(sizeof(int)*numOfVertice);
            graph->weight = (int**)malloc(sizeof(int*)*numOfVertice);
            for (int i = 0; i < numOfVertice; i++){
                graph->weight[i] = (int*)malloc(sizeof(int)*numOfVertice);
            }

            // Initialize the values
            for (int i = 0; i < numOfVertice; i++) {
                for (int j = 0; j < numOfVertice; j++)
                    graph->weight[i][j] = 0;
            }

            for (int i = 0; i < numOfVertice; i++) {
                for (int j = 0; j < numOfVertice; j++)
                    graph->adj[i][j] = 0;
            }

            int cnt = 0;
            char* result;
            int a[3], i = 0;
            // Then scan th file line by line and store in the struct edge and graph
            while(fscanf(fp,"%d, %d, %d", &a[0], &a[1], &a[2]) != EOF) {
                // printf("%d, %d, %d\n", a[0], a[1], a[2]);
                int vertex_1 = 0, vertex_2 = 0;
                // result = strtok(verticeWeigth, ",");
                // while(result != NULL) {  
                //     a[i] = atoi(result);
                //     i++;
                //     result = strtok(NULL, ",");  
                // }
                // Remember that edge is a struct array
                // The index of edges is the cnt
                edge[cnt]->start_point = a[0];
                edge[cnt]->end_point = a[1];
                edge[cnt]->weight = a[2];
                graph->adj[a[0]][a[1]] = 1;
                graph->adj[a[1]][a[0]] = 1;
                graph->color[a[0]]=graph->color[a[1]]='W';
                graph->numOfEdge = numOfEdge;
                graph->numOfVertice = numOfVertice; 
                graph->weight[a[0]][a[1]] = a[2];
                cnt++;
            }
            
            // Answer for 1, 2, 3 tasks
            // Between each task, it should be initialized again
            printf("1.The following are the edges in the constructed DFS Tree: \n");
            DFS(graph);
            printf("\n2.The articulation points found in the given graph is/are: \n");
            Initialize(graph);
            FindArticulation(graph); 
            printf("\nThe biconnected component(s) found in the given graph is/are: \n");
            Initialize(graph);
            FindBiconnected(graph);
            printf("\n3. The following are the edges in the constructed MST: \n");
            Initialize(graph);
            // Check the information of each edge is correct
            // for (int i = 0; i < graph->numOfEdge; i++)
            // {
            //     printf("start: %d, final: %d, weight: %d\n", edge[i]->start_point, edge[i]->end_point, edge[i]->weight);
            // }
            MST_Kruskals(edge, numOfEdge, numOfVertice);

            // Remember to close the File
            fclose(fp);
        }
        else{
            // If the user press the "Crtl + Z", then exit program
            exit(1);
        }
	}
    return 0;
}

