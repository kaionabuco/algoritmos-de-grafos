#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string.h>
using namespace std;

class DisjointSet {
    vector <int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n+1, 0);
        parent.resize(n+1);
        size.resize(n+1);
        for (int i = 0; i<=n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) { // encontrando o nó pai
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_u] > rank[ulp_v]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    pair<int, vector<pair<int, int> > > kruskal(int V, vector<vector<pair<int, int> > > &adj) {
        vector<pair<int, pair<int, int> > > edges;
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int adjNode = it.first;
                int weight = it.second;
                edges.push_back(make_pair(weight, make_pair(i, adjNode)));            }
        }

        DisjointSet ds(V);

        sort(edges.begin(), edges.end());

        int minWeight = 0;
        vector<pair<int, int> > mstEdges;

        for (auto it : edges) {
            int u = it.second.first;
            int v = it.second.second;

            if (ds.findUPar(u) != ds.findUPar(v)) {
                minWeight += it.first;
                mstEdges.push_back(make_pair(u, v)); 

                ds.unionByRank(u, v);
            }
        }

        return make_pair(minWeight, mstEdges);
    }
};

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    string show_output = "result";

    for (int i =1; i<argc ; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            cout << "-s : mostra a solução" << endl;

            return 0;
        }else if(strcmp(argv[i], "-o") == 0){
            output_file = argv[i+1];
            show_output = "none";
        }
        else if(strcmp(argv[i], "-f") == 0){
            input_file = argv[i+1];
        }
        else if(strcmp(argv[i], "-s") == 0){
            show_output = "vertices";
        }
    }
    if (input_file == ""){
        cout << "No input file specified. Use the -f parameter" << endl;
        return 1;
    }
    ifstream fin(input_file);
    if(!fin){
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }
    int n, m;
    fin >> n >> m;
    vector<vector<pair<int, int> > > adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    fin.close();

    Solution obj;

    pair<int, vector<pair<int, int> > > result = obj.kruskal(n, adj);

    if(!(output_file == "")){
        ofstream fout(output_file);
        if(!fout){
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        for (auto &edge : result.second) {
            fout << "(" << edge.first << ", " << edge.second << ") ";
        }   
        fout << endl;

        fout.close();
    }

    if (show_output == "result") {
        cout << result.first << endl;
    }
    
    if (show_output == "vertices") {
        for (auto &edge : result.second) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }

    return 0;
}