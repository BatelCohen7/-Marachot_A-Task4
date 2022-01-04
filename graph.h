#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>

#define FALSE 0
#define TRUE 1

typedef struct edge
{
    int weight;
    struct node* dst;
    struct edge *next;
} edge, *pedge;


typedef struct node
{
    int id;
    pedge edges;
    struct node *next;
} node, *pnode;


typedef struct path
{
    int src;
    int dist;
    int prev;
} path, *ppath;

typedef pnode* GRAPH_NODE;

void build_graph(pnode* head, int n);

pnode new_node(int id, pnode next);
pnode find(int id, pnode head);
void insert_node(int data, pnode* head);
void delete_node(int data, pnode* head);

void add_edge(int src, int dest, int w, pnode head);
void delete_edges(pnode head);
pedge new_edge(int w, pnode pdest, pedge next);

void delete_graph(pnode* head);
void print_graph(pnode head); //for self debug

#endif // GRAPH_H