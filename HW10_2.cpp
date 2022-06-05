#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;
vector<pair<int, int>> ans;
void addEdge(vector<int> graph[], int u, int v) 
{
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
}

int timee = 0;
void fap(
    vector<int> graph[], 
    vector<int>& disc, 
    vector<int>& low,
    vector<bool>& visited, 
    vector<int>& parent,
    int v)
{
    visited[v] = true;
    disc[v] = low[v] = ++timee;
    int child = 0;
    for (auto i = graph[v].begin(); i != graph[v].end(); i++) 
    {
        int av = *i;
        if (visited[av] == false) 
        {
            child++;
            parent[av] = v;
            fap(graph, disc, low, visited, parent, av);
            low[v] = min(low[v], low[av]);
            if (parent[v] == -1 and child > 1)
                ans[v].second++;
            else if (parent[v] != -1 and low[av] >= disc[v])
                ans[v].second++;
        }
        else if (av != parent[v])
            low[v] = min(low[v], disc[av]);
    }
}

bool cmp2(pair<int, int>a, pair<int, int>b)
{
    return a.second > b.second;
}

int main() 
{
    int V,M;
    cin >> V >> M;
    vector<int>* graph = new vector<int>[V];
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);
    vector<int> low(V, 0);
    vector<int> disc(V, 0);
    
    for (int i = 0; i < V; i++)
    {
        ans.emplace_back(i, 0);
    }

    int a=0, b=0;
    while (1)
    {
        cin >> a >> b;
        if (a == -1 && b == -1)
            break;
        addEdge(graph,a, b);
    }
   
    fap(graph, disc, low, visited, parent, 0);
    
    sort(ans.begin(), ans.end(), cmp2);
   
    for (int i = 0; i < M; i++)
    {
        cout << ans[i].first<<' '<< ans[i].second+1<<endl;
    }

    return 0;
}
