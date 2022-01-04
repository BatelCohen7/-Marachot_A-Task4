//
// Created by batel on 30/12/2021.
//
#ifndef ALGO_H
#define ALGO_H
#include "graph.h"
#include <stdio.h>
#include <malloc.h>

void build_graph_cmd(pnode* head);
void insert_node_cmd(pnode* head, int isB);
void delete_node_cmd(pnode* head);
void shortsPath_S_cmd(pnode* head);
void shortsPath_P_cmd(pnode* head);
void TSP_cmd(pnode head);
void printGraph_cmd(pnode head); //for self debug


int shortestPath(int src, int dest, pnode head);
void shortsPathAllNodes(int src, int dest, pnode head);
path* dijkstra(int src, int dest, pnode head);
int getLenOfPoints(pnode head);
int getMaxNode(pnode head);
int TSP(int* arr, int len, pnode head);
void swap(int* x, int* y);
void permute(int* a, int l, int r, int len, int* bestP, int* bestW, int** mat);

#endif // ALGO_H
