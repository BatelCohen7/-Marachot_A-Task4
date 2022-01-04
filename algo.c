//
// Created by batel on 30/12/2021.
//
#include "algo.h"
/** CASES FOR MAIN **/

void build_graph_cmd(pnode* head)
{
    int num = 0;
    int flag = 0;
    flag = scanf("%d", &num);
    if (flag != EOF && flag != 0)
    {
        //printf("%d ", num);
        //node* list = (node*)malloc(sizeof(node));
        build_graph(head, num);   /** Build a graph with a pointer to the first node
                                         (head) and the number of nodes in the graph  **/
    }
}

void insert_node_cmd(pnode* head, int isB)
{
    int src = 0;
    int dest = 0;
    int w = 0;
    int flag = 0;

    flag = scanf("%d", &src);
    if (flag != EOF && flag != 0)   /**Add node type- Node**/
    {
        //printf("%d ", src);
        pnode psrc = find(src, *head);
        if (psrc != NULL)
        {
            delete_edges(psrc);
        }
        else if (isB)
        {
			insert_node(src, head);
        }
    }
    else
    {
        return;
    }

    do
    {
        flag = scanf("%d%d", &dest, &w); /**Add node type- Edge**/
        if (flag != EOF && flag != 0)
        {
            //printf("%d %d ", dest, w);
            add_edge(src, dest, w, *head);
        }

    } while (flag != EOF && flag != 0);
}

void delete_node_cmd(pnode* head)
{
    int src = 0;

    if (scanf("%d", &src) != EOF)
    {
        delete_node(src, head);
    }
}

void shortsPath_S_cmd(pnode* head) /**find the length of shortest path **/
{
    int src = 0, dest = 0;

    if (scanf("%d%d", &src, &dest) != EOF)
    {
		printf("Dijsktra shortest path: %d \n", shortestPath(src, dest, *head));
    }
}

void shortsPath_P_cmd(pnode* head) /**find the nodes of shortest path **/
{
    int src = 0, dest = 0;

    if (scanf("%d%d", &src, &dest) != EOF)
    {
		printf("Dijsktra shortest path: ");
		shortsPathAllNodes(src, dest, *head);
		printf("\n");
    }
}


void TSP_cmd(pnode head) /**Travelling Salesman Problem- **/
{
	int len = 0;
	if (scanf("%d", &len) == EOF) // if the graph is empty return
	{
		return;
	}

	int* nodes = (int*)calloc(len, sizeof(int)); // Let the graph defined place in memory
	for (int i = 0; i < len; i++)
	{
		if (scanf("%d", &nodes[i]) == EOF)
		{
			free(nodes);
			return;
		}
	}

	for (int i = 0; i < len; i++)
	{
		if (find(nodes[i], head) == NULL) // if there is empty node, delete node and free place in memory
		{
			free(nodes);
			return;
		}
	}
	printf("TSP shortest path: %d \n", TSP(nodes, len, head));
	free(nodes);
}


void printGraph_cmd(pnode head)
{
    pnode curr = head;
    printf("\n");
    while (curr != NULL)
    {
        printf("%d: ", curr->id);  // print id of node
        pedge currEdge = curr->edges; // print all the edges that connected to this node
        if (currEdge == NULL)
        {
            printf("NONE\n");
        }
        else
        {
            while (currEdge != NULL)
            {
                printf("%d (%d)", currEdge->dst->id, currEdge->weight); // print dest & weight of this edge
                if (currEdge->next != NULL)
                {
                    printf(", ");
                }
                currEdge = currEdge->next;
            }
            printf("\n");
        }
        curr = curr->next; //print all the nodes & edges in the graph

    }
}

int getLenOfPoints(pnode head) /**Count the number of nodes in the graph **/
{
    int count = 0;
    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}

path* dijkstra(int src, int dest, pnode head) /** finding the shortest paths between nodes in a graph**/
{
    int len = getMaxNode(head) + 1;

    path* paths = (path*)calloc(len, sizeof(path));
    pnode curr = head;
    pnode Q = NULL; // create list of node

    while (curr)
    {                       //for each node (ind) in the graph- find paths from source to ind
        int ind = curr->id;
        paths[ind].src = curr->id;
        paths[ind].dist = ((curr->id == src) ? 0 : -1);
        paths[ind].prev = -1;
        insert_node(ind, &Q); // insert node to Q list
        curr = curr->next;
    }

    while (Q) //the main loop return best-vertex (node)
    {
        int uInd = Q->id;
        int bestV = paths[uInd].dist;
        curr = Q;

        while (curr)  //for each neighbor v of u (only v that are still in Q)
        {
            int i = curr->id;
            if (bestV < 0 && paths[i].dist >= 0)
            {
                bestV = paths[i].dist;
                uInd = i;
            }
            else if (bestV >= 0 && paths[i].dist >= 0)
            {
                if (paths[i].dist < bestV)
                {
                    bestV = paths[i].dist;
                    uInd = i;
                }
            }
            curr = curr->next;
        }

        if (uInd == dest)
        {
            delete_graph(&Q);
            return paths;
        }

        delete_node(uInd, &Q);

        curr = find(uInd, head);
        pedge currEdge = curr->edges;
        while (currEdge)
        {
            int v = currEdge->dst->id;
            if (find(v, Q))
            {
                int alt = paths[uInd].dist + currEdge->weight; // alt ← dist[u] + length(u, v)
				if (paths[uInd].dist >= 0 && currEdge->weight >= 0)
				{
					if (alt < paths[v].dist || paths[v].dist < 0) // if alt < dist[v]
					{
						paths[v].dist = alt;  // dist[v] ← alt
						paths[v].prev = uInd; //  prev[v] ← u
					}
				}
                
            }
            currEdge = currEdge->next;
        }
    }
    free(paths);
    return (NULL);

}


int getMaxNode(pnode head)
{
    int max = 0;
    while (head)
    {
        if (head->id > max)
        {
            max = head->id;
        }

        head = head->next;

    }
    return max;
}

void shortsPathAllNodes(int src, int dest, pnode head)
{
    path* paths = dijkstra(src, dest, head); // find the shortest paths among all the
                                            // nodes in the graph with dijkstra algorithm
    if (paths == NULL)
    {
        printf("-1 ");
    }
    else
    {
        pnode p = NULL;
        int v = dest;
        if (paths[v].prev >= 0 || v == src)
        {
            while (v >= 0)
            {
				p = new_node(v, p);
                v = paths[v].prev;
            }
        }

        while (p)
        {
            printf("%d ", p->id);
            delete_node(p->id, &p);
        }
        free(paths);
    }
}

int TSP(int* arr, int len, pnode head)
{
    int max = 0; // find the max value
    for (int i = 0; i < len; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    max += 1;

    int** mat = (int**)malloc(max*sizeof(int*)); // Let the matrix dynamic place in memory
    for (int i = 0; i < max; i++)
    {
        mat[i] = (int*)malloc(max*sizeof(int));
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
			//printf("%d %d\n", arr[i], arr[j]);
			mat[arr[i]][arr[j]] = shortestPath(arr[i], arr[j], head);
        }
    }

    int* tempArr = (int*)malloc(sizeof(int) * len);
    memcpy(tempArr, arr, sizeof(int) * len);
    int bestW = -1;
    permute(arr, 0, len - 1, len, tempArr, &bestW, mat);
    free(tempArr);
	return (bestW);
}

int shortestPath(int src, int dest, pnode head)
{
    path* paths = dijkstra(src, dest, head);
    if (paths == NULL)
    {
        return (-1);
    }

    int w = paths[dest].dist;
    free(paths);

    return (w);
}

int sumRoute(int nodes[], int len, int** shortest)
{
    int sum = 0;

    for (int i = 0; i < len - 1; i++)
    {
		int curr = shortest[nodes[i]][nodes[i + 1]];
        if (curr == -1)
        {
            return (-1);
        }
        sum += curr;
    }
    return (sum);
}

void permute(int* a, int l, int r, int len, int* bestP, int* bestW, int** mat)
{
    if (l == r)
    {
        int sum = sumRoute(a, len, mat);
        if (*bestW < 0 && sum >= 0)
        {
            *bestW = sum;
            memcpy(bestP, a, sizeof(int) * len);
        }
        else if (*bestW >= 0 && sum >= 0 && sum < *bestW)
        {
            *bestW = sum;
            memcpy(bestP, a, sizeof(int) * len);
        }
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap((a + l), (a + i));
            permute(a, l + 1, r, len, bestP, bestW, mat);
            swap((a + l), (a + i)); //backtrack
        }
    }
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}