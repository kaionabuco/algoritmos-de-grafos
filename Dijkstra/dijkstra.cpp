#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <limits.h>
using namespace std;

void dijkstra(vector<vector<pair<int, int>>> & grafo, vector<int> & dist, int V, int init) {
    for (int i = 0; i <= V; i++) {
    dist[i] = INT_MAX;
    }
    dist[init] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> H;
    H.push({init, 0});

    while(!H.empty()) {
        int u = H.top().first;
        int tempDist = H.top().second;
        H.pop();

        for (auto e : grafo[u]) {
            int v = e.first;
            int peso = e.second;

            if (dist[v] > (dist[u] + peso)) {
                dist[v] = (dist[u] + peso);
                H.push({v, dist[v]});
            }
        }
    }
}

int main(int argc, char *argv[]) {

    string in = "";
    string out = "";
    int init = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Imprime a distância do vértice inicial 1 até os demais" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial (como numero inteiro)" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            in = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            init = atoi(argv[++i]);
        }
    }

    if (in == "") {
        cerr << "Nenhum input especificado. Use o parâmetro -f com um arquivo de entrada como argumento." << endl;
        return 1;
    }

    ifstream grafoEntrada(in);
    if (!grafoEntrada) {
        cerr << "Incapaz de abrir arquivo: " << in << endl;
        return 1;
    }

    int V, E;
    grafoEntrada >> V >> E;

    vector<vector<pair<int, int>>> grafo(V + 1);

    vector<int> dist(V + 1);

    for (int i = 0; i < E; ++i) {
        int u, w, peso; // Não confundir vértice 'w' com abreviação de weight!
        grafoEntrada >> u >> w >> peso;

        grafo[u].push_back(make_pair(w, peso));
        grafo[w].push_back(make_pair(u, peso));
    }

    grafoEntrada.close();

    dijkstra(grafo, dist, V, init);

    for (int i = 1; i <= V; i++) {
        if (dist[i] == INT_MAX)
            cout << i << ":" << -1 << " ";
        else
            cout << i << ":" << dist[i] << " ";
    }
    cout << endl;

    return 0;
}