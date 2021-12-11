#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODE_NUM 500
#define MAX_EXIT_NUM 20

typedef struct {
    int index;
    bool is_exit;
} Node_t;

Node_t *nodes[] = {0};
int links[MAX_NODE_NUM][MAX_NODE_NUM] = {0};
int exits[MAX_EXIT_NUM] = {0};
int paths[MAX_NODE_NUM] = {0};
int path_length;
int node_num = 0;

bool is_an_exit(int n)
{
    for (int i=0; i<MAX_EXIT_NUM; i++) {
        if (exits[i] == n)
            return true;
        if (exits[i] == -1)
            return false;
    }
    return false;
}

void bfs(int skynet_idx, int *path, int *path_length)
{
    bool used[MAX_NODE_NUM];
    memset(used, false, MAX_NODE_NUM);
    int queue[MAX_NODE_NUM];
    memset(queue, -1, MAX_NODE_NUM);
    int queue_idx = 0;
    int dist[MAX_NODE_NUM];
    memset(dist, 999999, MAX_NODE_NUM);
    int pred[MAX_NODE_NUM];
    memset(pred, -1, MAX_NODE_NUM);
    *path_length = 0;
    memset(path, -1, MAX_NODE_NUM);
    int idx = 0;

    used[skynet_idx] = true;
    dist[skynet_idx] = 0;
    queue[queue_idx++] = skynet_idx;
    bool exit_needed = false;
    int dest = -1;

    while (queue[idx] != -1 && !exit_needed) {
        int node = queue[idx];
        fprintf(stderr, "checking node:%d (idx:%d) used:%d\n", node, idx, used[node]);
        for (int i=0; i<node_num; i++) {
            if (links[node][i] && !used[i] && i != node) {
                queue[queue_idx++] = i;
                used[i] = true;
                dist[links[node][i]] = dist[node] + 1; 
                pred[i] = node; 

                if (is_an_exit(i)) {
                    dest = i;
                    exit_needed = true;
                }
            }
        }
        idx++;
    }

    if (exit_needed) {
        // vector path stores the shortest path 
        int crawl = dest;
        path[(*path_length)++] = crawl;

        while (pred[crawl] != -1) {
            path[(*path_length)++] = pred[crawl];
            crawl = pred[crawl];
        }
    }
}

int main()
{
    memset(exits, -1, MAX_EXIT_NUM);

    // the number of links
    int L;
    // the number of exit gateways
    int E;
    scanf("%d%d%d", &node_num, &L, &E);
    
    for (int i=0; i<node_num; i++) {
        nodes[i] = (Node_t *)malloc(sizeof(Node_t));
        nodes[i]->index = i;
        nodes[i]->is_exit = false;
    }

    for (int i=0; i<L; i++) {
        // N1 and N2 defines a link between these nodes
        int N1;
        int N2;
        scanf("%d%d", &N1, &N2);
        links[N1][N2] = 1;
        links[N2][N1] = 1;
    }

    for (int i = 0; i < E; i++) {
        // the index of a gateway node
        int EI;
        scanf("%d", &EI);
        exits[i] = EI;
    }

    while (1) {
        // The index of the node on which the Skynet agent is positioned this turn
        int SI;
        scanf("%d", &SI);

        bfs(SI, paths, &path_length);
        printf("%d %d\n", paths[1], paths[0]);

        links[paths[1]][paths[0]] = 0;
        links[paths[0]][paths[1]] = 0;
    }

    for (int i=0; i<node_num; i++) 
        free(nodes[i]);

    return 0;
}