#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <stack>
using namespace std;
class Graph
{
public:
    unordered_map<char, vector<pair<int, char>>> adjList;
    void addEdge(char a, char b, int weight)
    {
        adjList[a].push_back({weight, b});
    }
};
struct ComparePairFirts
{
    bool operator()(const pair<int, char> &a, const pair<int, char> &b) const
    {
        return a.first > b.first;
    }
};
void bfs(Graph &graph, char start, char goal)
{
    unordered_set<char> visited;
    visited.insert(start);

    priority_queue<pair<int, char>, vector<pair<int, char>>, ComparePairFirts> q;
    unordered_map<char, char> parent;
    q.push({0, start});

    cout << "BFS Order of Nodes Visited: ";

    while (!q.empty())
    {
        auto element = q.top();
        q.pop();

        int totalWeight = element.first;
        char u = element.second;

        cout << u << " ";
        if (u == goal)
        {
            stack<char> path;
            path.push(goal);

            char current = goal;
            while (current != start)
            {
                current = parent[current];
                path.push(current);
            }
            cout << "\nPath from " << start << " to " << goal << ": ";

            while (!path.empty())
            {
                cout << path.top() << " ";
                path.pop();
            }
            return;
        }
        
        if (graph.adjList.find(u) == graph.adjList.end()) {
            cerr << "Node " << u << " not found in the adjacency list!" << endl;
            return;
        }

        for (const auto &entry : graph.adjList.at(u))
        {
            char v = entry.second;
            int edgeWeight = entry.first;

            if (visited.find(v) == visited.end())
            {
                visited.insert(v);
                q.push({totalWeight+edgeWeight, v});
                parent[v] = u;
            }
        }
    }
}

int main()
{
    Graph graph;

    // graph.addEdge(node,node,weight)
    graph.addEdge('A', 'B', 5);
    graph.addEdge('A', 'D', 3);
    graph.addEdge('B', 'C', 1);
    graph.addEdge('C', 'E', 6);
    graph.addEdge('C', 'G', 8);
    graph.addEdge('D', 'E', 2);
    graph.addEdge('D', 'F', 12);
    graph.addEdge('E', 'B', 4);
    graph.addEdge('F', 'G', 3);
    graph.addEdge('G', 'E', 4);

    char startNode = 'A';
    char goal = 'G';
    bfs(graph, startNode, goal);
    cout << endl;
}