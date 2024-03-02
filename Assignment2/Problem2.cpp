#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

class Graph
{
public:
    unordered_map<char, vector<pair<char, double>>> adjList;
    multimap<char, double> openList;
    unordered_map<char, double> closedList;

    unordered_map<char, double> g;

    unordered_map<char, char> parent;

    vector<pair<char, char>> edges_traversed;

    void addEdge(char a, char b, double w)
    {
        adjList[a].push_back({b, w});
        adjList[b].push_back({a, w});
    }

    bool aStar(char start, char goal, unordered_map<char, double> &heuristic)
    {
        openList.insert({start, 0}); 
        bool reached = false;

        while (!openList.empty())
        {
            auto curr_node = openList.begin()->first;
            double curr_cost = openList.begin()->second;

            openList.erase(openList.begin());

            if (curr_node == goal)
            {
                cout << "Reached to goal\n";
                reached = true;
                break;
            }

            for (auto neighbour : adjList[curr_node])
            {
                char v = neighbour.first;
                double edge_cost = neighbour.second;

                double new_cost = g[curr_node] + edge_cost;
                if (!g.count(v) || new_cost < g[v])
                {
                    g[v] = new_cost;
                    double fval = new_cost + heuristic[v];
                    parent[v] = curr_node;

                    openList.insert({v, fval});
                }
            }
        }

        if (reached)
        {
            cout << "\nA* Search nodes : ";
            for (auto n : closedList)
                cout << n.first << ",";
            cout << "\n";
            vector<char> path;
            char curr = goal;
            while (curr != start)
            {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            cout << "Path : ";
            for (auto n : path)
                cout << n << " ";
            cout << "\n";
        }
        else
        {
            cout << "No available path\n";
        }

        return reached;
    }
};
inline double findEuclideanDist(int x1, int y1, int x2, int y2)
{
    return (double)sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

int main()
{
    Graph graph;

    unordered_map<char, double> huristic;

    graph.addEdge('A', 'B', 8);

    graph.addEdge('B', 'D', 12);
    graph.addEdge('B', 'E', 6);
    graph.addEdge('B', 'C', 10);

    graph.addEdge('E', 'G', 7);
    graph.addEdge('E', 'C', 10);

    graph.addEdge('G', 'F', 7); 
    graph.addEdge('G', 'H', 15);
    graph.addEdge('F', 'C', 9);
    graph.addEdge('H', 'F', 100);

    char startNode = 'A';
    char goal = 'H';

    int goalX = 19;
    int goalY = 19;

    huristic['A'] = findEuclideanDist(goalX, goalY, 1, 1);
    huristic['B'] = findEuclideanDist(goalX, goalY, 8, 4);
    huristic['C'] = findEuclideanDist(goalX, goalY, 17, 2);
    huristic['D'] = findEuclideanDist(goalX, goalY, 5, 13);
    huristic['E'] = findEuclideanDist(goalX, goalY, 10, 9);
    huristic['F'] = findEuclideanDist(goalX, goalY, 1, 9);
    huristic['G'] = findEuclideanDist(goalX, goalY, 13, 13);
    huristic['H'] = findEuclideanDist(goalX, goalY, 19, 19);

    if (!graph.aStar(startNode, goal, huristic))
        cout << "No available path\n";
}