#include "header.h"
#include <limits.h>
#include <stdlib.h>

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
    int pivot = r;
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        if (predicate_func(&airport_list[j], &airport_list[pivot])) //if airport[j] < airport[pivot] for t1
        {
            i++;
            Q4_swap(n, airport_list, i, j);
        }
    }
    Q4_swap(n, airport_list, i + 1, pivot);
    return i + 1;
}

static void Q4_quicksort(int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n], int l, int r)
{
    if (l < r)
    {
        int j = Q4_partition(n, predicate_func, airport_list, l, r);
        Q4_quicksort(n, predicate_func, airport_list, l, j-1);
        Q4_quicksort(n, predicate_func, airport_list, j+1, r);
    }
}

static int Q5_predicate(const airport_t *x, const airport_t *y)
{   
    int i = 0;
    char ch1 = x->airport_name[i];
    char ch2 = y->airport_name[i];
    for (int i = 0; i < 3; i ++)
    {
        int dif = ch1 - ch2;
        if (dif < 0)
            return 1;
        i++;
        char ch1 = x->airport_name[i];
        char ch2 = y->airport_name[i];
    }
    return 0;
}

static void Q7_shift_table(int m, const char *p, int size, int table[size])
{
    for (int i = 0; i < size; i++)  //initializing all entries to m
        table[i] = m;
    for (int j = 0; j < m - 2; j++) //setting values of characters present in p
        table[p[j]] = m - 1 - j;
}

static int Q7_horspool(int m, const char *p, int n, const char *t)
{
    int table[26];
    Q7_shift_table(m, p, 26, table);    //generating shift table
    int i = m - 1;
    while (i <= n - 1)
    {
        int k = 0;
        while (k <= m - 1 && p[m - 1 - k] == t[i - k]) //counting number of matching characters
            k++;
        if (k == m) //complete match
            return 1;
        i += table[t[i] - 65];  //shifts i according to table value of ith character        
    }
    return 0;
}

static int Q8_mobile(int n, int airport_id[n - 1], char arrows[n - 1])
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arrows[i] == 'l')
        {
            if (i != 0 && airport_id[i] > airport_id[i - 1])
                return 1;
        }
        if (arrows[i] == 'r')
        {
            if (i != n - 2 && airport_id[i] > airport_id[i + 1])
                return 1;
        }
    }
    return 0;
}

static void Q8_swap(int *k, int n, int airport_id[n - 1], char arrows[n - 1])
{
    int index;
    if (arrows[*k] == 'l')
        index = *k - 1;
    else
        index = *k + 1;
        
    int temp = airport_id[*k];
    airport_id[*k] = airport_id[index];
    airport_id[index] = temp;

    char temp1 = arrows[*k];
    arrows[*k] = arrows[index];
    arrows[index] = temp1;

    if (arrows[*k] == 'l')
        *k = *k - 1;
    else
        *k = *k + 1;
}

static void Q8_update_order(int n, int trip_order[n - 1], int airport_id[n - 1], const connection_t connections[n][n], int *min_cost)
{
    int cost = 0;
    for (int i = 0; i < n - 2; i++) //calculating distance
    {   
        if (connections[airport_id[i]][airport_id[i + 1]].distance == INT_MAX)
            cost = INT_MAX;
        if (cost != INT_MAX)
            cost += connections[airport_id[i]][airport_id[i + 1]].distance;
    }
    if (connections[airport_id[n - 2]][airport_id[0]].distance == INT_MAX)
        cost = INT_MAX;
    if (cost != INT_MAX)
        cost += connections[airport_id[n - 2]][airport_id[0]].distance;
    if (cost < *min_cost)   //updating order if distance is lower than min
    {
        for (int i = 0; i < n - 1; i++)
            trip_order[i] = airport_id[i];
        *min_cost = cost;
    }
}

static int Q8_permutations(int n, int trip_order[n - 1], const connection_t connections[n][n], int *min_cost, int airport_id[n - 1])
{
    char arrows[n - 1];
    for (int i = 0; i < n - 1; i++) //initializing arrays
        arrows[i] = 'l';
    Q8_update_order(n, trip_order, airport_id, connections, min_cost);

    while (Q8_mobile(n, airport_id, arrows))
    {
        int k = -1;
        for (int i = 0; i < n - 1; i++) //finding largest mobile element
        {
            if (arrows[i] == 'l' && i != 0) 
            {
                if (airport_id[i] > airport_id[i - 1])
                {
                    if (k == -1 || airport_id[i] > airport_id[k])
                        k = i;
                }
            }
            if (arrows[i] == 'r' && i != n - 2)
            {
                if (airport_id[i] > airport_id[i + 1])
                {
                    if (k == -1 || airport_id[i] > airport_id[k])
                        k = i;
                }
            }
        }
        Q8_swap(&k, n, airport_id, arrows);  //swapping with element it points to

        for (int i = 0; i < n - 1; i++) //reversing arrow directions
        {
            if (airport_id[i] > airport_id[k])
            {   
                if (arrows[i] == 'l')
                    arrows[i] = 'r';
                else
                    arrows[i] = 'l';
            }
        }
        Q8_update_order(n, trip_order, airport_id, connections, min_cost);
    }
}

static pair_t Q9_min_edge(int n, const connection_t connections[n][n], int *visited)
{
    int min_time = INT_MAX;
    pair_t min_edge;
    for (int i = 0; i < n; i++) //iterating through visited nodes
    {
        if (visited[i] == 1)
        {
            for (int j = 0; j < n; j++) //iterating through unvisited nodes connected to each visited node
            {
                if (visited[j] == 0 && connections[i][j].time < min_time)   //current nearest node to the tree
                {
                    min_edge.first = i;
                    min_edge.second = j;
                    min_time = connections[i][j].time;
                }
            }
        }
    }
    return min_edge;
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
    Q4_quicksort(n, predicate_func, airport_list, 0, n-1);
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    Q4_quicksort(n, Q5_predicate, airports, 0, n - 1);  //sorting array in alphabetical order
    int prefix_len = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int j = 0;
        while(airports[i].airport_name[j] == airports[i + 1].airport_name[j]) //comparing only consecutive pairs
            j++;
        if (j > prefix_len) //new longest prefix
        {
            ans.first = airports[i].num_id;
            ans.second = airports[i + 1].num_id;
            prefix_len = j;
        }
    }
    return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2; //ans lies between [low, high] at all times
        if (low == high)
        {
            if (entry_fee[mid] > amount)    //check remaining value
                return mid;
            return mid + 1;
        }
        else if (entry_fee[mid] <= amount)  //discard all elements less than mid+1
            low = mid + 1;
        else if (entry_fee[mid] > amount )  //discard all elements greater than mid-1
            high = mid - 1;
        
    }
    return mid;
}

void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int m = 0;
    while (pat[m] != '\0')
        m++;
    for (int i = 0; i < n; i++)
    {
        contains[i] = Q7_horspool(m, pat, n, airports[i].airport_name);
    }
}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int min_cost = INT_MAX;
    int airport_id[n - 1];
    for (int i = 0; i < n; i++)
    {
        int id = 0;
        for (int j = 0; j < n - 1; j++) //excluding the ith airport
        {
            if (id == i)
                id++;
            airport_id[j] = id;
            id++;
        }
        Q8_permutations(n, trip_order, connections, &min_cost, airport_id);
    }
    if (min_cost == INT_MAX)
        return -1;
    return min_cost;
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    visited[0] = 1;
    int time = 0;
    for (int i = 0; i < n - 1; i++)
    {
        edges[i] = Q9_min_edge(n, connections, visited);
        visited[edges[i].second] = 1;
        time += connections[edges[i].first][edges[i].second].time; 
    }
    return time;
}

void q10(int n, int k, const airport_t *src, const connection_t connections[n][n], const int destinations[k], int costs[k])
{
    int Q[n];
    int times[n];
    for (int i = 0; i < n;  i++)    //initializing queue
        Q[i] = INT_MAX;
    Q[src->num_id] = 0;
    for (int i = 0; i < n; i++)
    {
        int min_time = INT_MAX;
        int nearest;
        for (int j = 0; j < n; j++) //finding highest priority node
        {
            if (Q[j] < min_time && Q[j] > -1)
            {
                nearest = j;
                min_time = Q[j];
            }
        }
        times[nearest] = Q[nearest];
        Q[nearest] = -1; 
        for (int j = 0; j < n; j++) //updating costs of adjacent nodes
        {
            int new_time = connections[nearest][j].time + times[nearest];
            if (new_time < Q[j] && Q[j] > -1)
                Q[j] = new_time;
        }
    }
    for (int i = 0; i < k; i++) //updating costs of specified destintions only
        costs[i] = times[destinations[i]];
}