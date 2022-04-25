#include "header.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h> // REMOVE BEFORE SUBMITTING
#include <string.h>

// ANY STATIC FUNCTIONS ARE UP HERE

static void Q1_dfs(int pres, int n, const connection_t connections[n][n], int visited[])
{
    for (int i = 0; i < n; i++)
    {
        int distance = connections[pres][i].distance;
        if (visited[i] == 0 && distance != INT_MAX)
        {
            visited[i] = 1;
            Q1_dfs(i, n, connections, visited);
        }
    }
}

static void Q2_dfs(int src, int dest, int n, int k, const connection_t connections[n][n], int visited[], int count)
{
    if (count > k)  //current node is more than k edges away
        return;
    visited[src] = 1;
    if (src == dest)    //dest already reached
        return;
    for (int i = 0; i < n; i++)
    {
        int distance = connections[src][i].distance;
        if (!visited[i] && distance != INT_MAX) //goes to adjacent unvisited nodes 
        {
            Q2_dfs(i, dest, n, k, connections, visited, count + 1);
        }
    }
}

static void Q3_dfs(int pres, int src, int n, const connection_t connections[n][n], int visited[])
{
    if (pres != src)    //mark non-src nodes as visited immediately
        visited[pres] = 1;
    if (visited[src])   //path already found
        return;
    for (int i = 0; i < n; i++) 
    {
        int distance = connections[pres][i].distance;
        if (!visited[i] && distance != INT_MAX && pres != i)    //src marked visited only when visited through another node
        {
            if (i == src)   
                visited[i] = 1;
            Q3_dfs(i, src, n, connections, visited);
        }
    }
}

static void Q4_swap(int n, airport_t airport_list[n], int x, int y)
{
    airport_t temp = airport_list[x];
    airport_list[x] = airport_list[y];
    airport_list[y] = temp;
}

static int Q4_partition(int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n], int l, int r)
{
    int p = l;
    int i = l + 1;
    int j = r;
    while (i < j)
    {
        while (strcmp(airport_list[i].airport_name, airport_list[p].airport_name) < 0)
            i++;
        while (strcmp(airport_list[p].airport_name, airport_list[j].airport_name) < 0)
            j--;
        Q4_swap(n, airport_list, i, j);
    }
    if (i >= j)
        Q4_swap(n, airport_list, i, j);
    Q4_swap(n, airport_list, l, j);
    return j;
}

static void Q4_quicksort(int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n], int l, int r)
{
    if (l < r)
    {
        int j = Q4_partition(n, predicate_func, airport_list, l, r);
        Q4_quicksort(n, predicate_func, airport_list, l, j-1);
        Q4_quicksort(n, predicate_func, airport_list, j+1, r);
    }
    for (int i = 0; i < n; i++)
        printf("%s ", airport_list[i].airport_name);
    printf("\n");
}

// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n])
{
    for (int i = 0; i < n; i++)
    {
        int source = i;
        int visited[n];
        for (int i = 0; i < n; i++)
            visited[i] = 0;
        visited[source] = 1;
        Q1_dfs(source, n, connections, visited);
        for (int i = 0; i < n; i++)
        {  
            if (visited[i] == 0)
                return 0;
        }
    }
    return 1;
}

int q2(const airport_t *src, const airport_t *dest, int n, int k, const connection_t connections[n][n])
{
    int src_id = src->num_id;
    int dest_id = dest->num_id;
    int visited[n];
    for (int i = 0; i < n; i++) //initializing visited array
        visited[i] = 0;
    Q2_dfs(src_id, dest_id, n, k, connections, visited, 0); //calling helper function 
    if (visited[dest_id] == 0)  //checking if dest was not visited
        return 0;
    return 1;
}

int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int src_id = src->num_id;
    int visited[n];
    for (int i = 0; i < n; i++) //initializing visited array
        visited[i] = 0;
    Q3_dfs(src_id, src_id, n, connections, visited);
    if (visited[src_id] == 1) //src visited 
        return 1;
    return 0;
}

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n])
{
    for (int i = 0; i < n; i++)
        printf("%s ", airport_list[i].airport_name);
    printf("\n");
    Q4_quicksort(n, predicate_func, airport_list, 0, n-1);
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
    return 0;
}

void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{

}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    return 0;
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    return 0;
}

void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{

}

// END
