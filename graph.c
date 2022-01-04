//
// Created by batel on 04/01/2022.
//

#include "graph.h"

pnode new_node(int id, pnode next)
{
    node* p = (node*)malloc(sizeof(node));
    p->id = id;
    p->edges = NULL;
    p->next = next;
    return p;
}

pnode find(int id, pnode head)
{
    pnode p = head;
    while (p != NULL)
    {
        if (p->id == id)
        {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

pedge new_edge(int w, pnode pdest, pedge next)
{
    edge* p = (edge*)malloc(sizeof(edge));
    p->weight = w;
    p->dst = pdest;
    p->next = next;
    return p;
}

void add_edge(int src, int dest, int w, pnode head)
{
    pnode psrc = find(src, head);
    pnode pdest = find(dest, head);
    if (psrc != NULL && pdest != NULL)
    {
        if (psrc->edges == NULL)
        {
            psrc->edges = new_edge(w, pdest, NULL);
        }
        else
        {
            pedge edges = psrc->edges;
            while (edges->next != NULL)
            {
                edges = edges->next;
            }
            edges->next = new_edge(w, pdest, NULL);
        }
    }
}

void delete_edges(pnode head)
{
    if (head != NULL)
    {
        while (head->edges != NULL)
        {
            pedge currEdge = head->edges;
            head->edges = head->edges->next;
            currEdge->next = NULL;
            free(currEdge);
        }
    }
}


void build_graph(pnode* head, int n)
{
    if (head != NULL)
    {
        delete_graph(head);
        for (int i = 0; i < n; i++)
        {
            insert_node(i, head);
        }
    }
}

void insert_node(int id, pnode* head)
{
    if (*head == NULL)
    {
        (*head) = new_node(id, NULL);
    }
    else
    {
        node* p = *head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new_node(id, NULL);
    }
}

void delete_node(int data, pnode* head)
{
    pnode currNode = NULL;
    if (*head != NULL)
    {
        if ((*head)->id == data)
        {
            currNode = *head;
            *head = (*head)->next;
        }
        else
        {
            currNode = (*head);
            while (currNode->next != NULL)
            {
                if (currNode->next->id == data)
                {
                    pnode temp = currNode->next;
                    currNode->next = currNode->next->next;
                    currNode = temp;
                    break;
                }
                currNode = currNode->next;
            }

            if (currNode->next == NULL)
            {
                currNode = NULL;
            }
        }

        if (currNode != NULL)
        {
            currNode->next = NULL;
            delete_edges(currNode);
            free(currNode);
        }
    }
}

void delete_graph(pnode* head)
{
    while (*head)
    {
        delete_node((*head)->id, head);
    }
}

void print_graph(pnode head)
{
    pnode curr = head;
    while (curr != NULL)
    {
        printf("%d: ", curr->id);
        pedge currEdge = curr->edges;
        if (currEdge == NULL)
        {
            printf("NONE\n");
        }
        else
        {
            while (currEdge != NULL)
            {
                printf("%d (%d)", currEdge->dst->id, currEdge->weight);
                if (currEdge->next != NULL)
                {
                    printf(", ");
                }
                currEdge = currEdge->next;
            }
            printf("\n");
        }
        curr = curr->next;
    }
    printf("\n");
}