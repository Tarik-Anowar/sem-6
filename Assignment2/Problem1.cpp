#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Graph
{
public:
    unordered_map<char, vector<char>> adjList;

    void addEdge(char a, char b)
    {
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    bool IDDFS(char start, char goal, int maxdepth)
    {

        for (int limit = 0; limit < maxdepth; limit++)
        {
            unordered_set<char> visited;
            cout << "For limt <" << limit << "> Order of Nodes Visited:  " << endl;
            if (DFS(start, goal, limit, visited))
            {
                return true;
            }
            visited.clear();
            cout << endl;
        }
        cout<<"\nGoal node not reached\n";
        return false;
    }

    bool DFS(char u, char goal, int limit, unordered_set<char> &visited)
    {
        cout << u << " ";
        if (u == goal)
        {
            cout<<"\nGoal node reached\n";
            return true;
        }

        if (visited.find(u) != visited.end())
            return false;
        visited.insert(u);

        if (limit == 0)
            return false;
        
        for (auto v : adjList[u])
        {
            if (DFS(v, goal, limit-1, visited))
                return true;
        }
        return false;
    }
};

int main()
{
    Graph graph;

    graph.addEdge('A', 'B');
    graph.addEdge('A', 'C');

    graph.addEdge('B', 'D');
    graph.addEdge('B', 'E');

    graph.addEdge('D', 'I');
    graph.addEdge('D', 'J');

    graph.addEdge('E', 'K');
    graph.addEdge('E', 'L');
    graph.addEdge('E', 'M');

    graph.addEdge('C', 'F');
    graph.addEdge('C', 'G');
    graph.addEdge('C', 'H');

    graph.addEdge('F', 'N');

    graph.addEdge('H', 'O');
    graph.addEdge('H', 'P');

    char startNode = 'G';
    char goal = 'K';

    int maxdepath = 10;

    graph.IDDFS(startNode, goal, maxdepath);

    return 0;
}