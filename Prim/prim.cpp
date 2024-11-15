#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <limits.h>
using namespace std;

class Solution {
public:
    pair<int, vector<pair<int, int> > > prim(int V, vector<vector<pair<int, int> > > &adj, int start) {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        vector<int> vis(V, 0);
        vector<int> minEdge(V, INT_MAX);  // Track minimum edge to reach each node
        vector<int> parent(V, -1);        // Track MST parent for each node
        int totalWeight = 0;
        vector<pair<int, int> > mstEdges;

        // Start from the initial node
        minEdge[start] = 0;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            auto [peso, node] = pq.top();
            pq.pop();

            if (vis[node] == 1) continue; // Skip if already part of MST
            vis[node] = 1;               // Mark node as part of MST
            totalWeight += peso;         // Add edge weight to MST total

            // Record the edge added to MST (skip for starting node)
            if (node != start && parent[node] != -1) {
                mstEdges.push_back(make_pair(parent[node], node));
            }

            // Explore adjacent nodes to update minimum edges
            for (auto [adjNode, edPeso] : adj[node]) {
                if (!vis[adjNode] && edPeso < minEdge[adjNode]) {
                    minEdge[adjNode] = edPeso; // Update the edge to reach adjNode
                    parent[adjNode] = node;    // Set parent in MST
                    pq.push(make_pair(edPeso, adjNode));
                }
            }
        }
        return make_pair(totalWeight, mstEdges);
    }
};

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    string show_output = "result";
    int start_node = 0;

    for (int i =1; i<argc ; i++) {
        if(strcmp(argv[i], "-h") == 0) {
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            cout << "-s : mostra a solução" << endl;
            cout << "-i : vértice inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            output_file = argv[i+1];
            show_output = "none";
        } else if (strcmp(argv[i], "-f") == 0) {
            input_file = argv[i+1];
        } else if (strcmp(argv[i], "-s") == 0) {
            show_output = "vertices";
        } else if (strcmp(argv[i], "-i") == 0) {
            start_node = atoi(argv[i+1]) - 1;
        }
    }

    if (input_file == "") {
        cout << "No input file specified. Use the -f parameter" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<vector<pair<int, int> > > adj(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u - 1].push_back(make_pair(v - 1, w));
        adj[v - 1].push_back(make_pair(u - 1, w));
    }

    fin.close();

    Solution obj;
    pair<int, vector<pair<int, int> > > result = obj.prim(n, adj, start_node);

    if (!(output_file == "")) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        for (auto &edge : result.second) {
            fout << "(" << edge.first + 1 << "," << edge.second + 1 << ") ";
        }   
        fout << endl;
        fout.close();
    }

    if (show_output == "result") {
        cout << result.first << endl;
    }
    
    if (show_output == "vertices") {
        for (auto &edge : result.second) {
            cout << "(" << edge.first + 1 << "," << edge.second + 1 << ") ";
        }
        cout << endl;
    }

    return 0;
}