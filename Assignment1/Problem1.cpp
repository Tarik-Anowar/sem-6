#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;
class Graph
{
public:
    unordered_map<int, vector<int>> adjList;
    void addEdge(int a, int b)
    {
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
};

void bfs(Graph &graph, int start, int goal)
{
    unordered_set<int> visited;
    visited.insert(start);

    queue<int> q;
    q.push(start);

    cout << "BFS Order of Nodes Visited: ";
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";
        if (u == goal)
            return;
        for (int v : graph.adjList[u])
        {
            if (visited.find(v) == visited.end())
            {
                q.push(v);
                visited.insert(v);
            }
        }
    }
    cout << endl;
}

bool dfs(Graph &graph, int u, unordered_set<int> &visited, int goal)
{
    if (visited.find(u) != visited.end())
        return false;
    visited.insert(u);
    cout << u << " ";
    if (u == goal)
        return true;
    for (int v : graph.adjList[u])
    {

        if (dfs(graph, v, visited, goal))
            return true;
    }
    return false;
}

int main()
{
    Graph graph;

    graph.addEdge(1, 8);
    graph.addEdge(1, 5);
    graph.addEdge(1, 2);
    graph.addEdge(8, 6);
    graph.addEdge(8, 4);
    graph.addEdge(8, 3);
    graph.addEdge(6, 10);
    graph.addEdge(6, 7);
    graph.addEdge(2, 9);

    // Starting node for BFS
    int startNode = 1;
    int goal = 7;

    // BFS
    bfs(graph, startNode, goal);

    unordered_set<int> visited;
    cout << "\nDFS Order of Nodes Visited: ";
    dfs(graph, startNode, visited, goal);

    return 0;
}