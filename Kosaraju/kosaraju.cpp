#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stack>
using namespace std;

int cont = 0;

void dfs_rec(vector<vector<int>> & grafo, vector<int> & pre, stack<int> & post, int v) {
	pre[v] = cont++;

	for (int e : grafo[v]) {
		if(pre[e] == -1) {
			dfs_rec(grafo, pre, post, e);
		}
	}
    post.push(v);
	return;
}

void dfs(vector<vector<int>> & grafo, vector<int> & pre, stack<int> & post, int V) {
	for (int i = 0; i <= V; i++) {
		pre[i] = -1;
	}

	for (int i = 1; i <= V; i++) {
		if (pre[i] == -1)
			dfs_rec(grafo, pre, post, i);
	}
}

void componentes(vector<vector<int>> & grafo, vector<int> & pre, vector<int> & componente, int v) {
    pre[v] = +1;
    componente.push_back(v);
    for (int e : grafo[v]) {
        if (pre[e] == -1) {
            componentes(grafo, pre, componente, e);
        }
    }
}

int main(int argc, char *argv[]) {

    string in = "";
    string out = "";
    bool ans = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Imprime as componentes fortemente conexas do grafo" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            return 0;
        }

        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            out = argv[++i];
        }

        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            in = argv[++i];
        }
    }

    if (in == "") {
        cerr << "Nenhum input especificado. Use o parâmetro -f com um arquivo de entrada como argumento." << endl;
        return 1;
    }

    ifstream grafoEntrada(in);
    if (!grafoEntrada){
        cerr << "Incapaz de abrir arquivo: " << in << endl;
        return 1;
    }

    int V, E;
    grafoEntrada >> V >> E;

    vector<vector<int>> grafo(V + 1);
    vector<vector<int>> grafoReverso(V + 1);

    vector<int> pre(V+1);
    stack<int> post;
    stack<int> posOrdem;

    for (int i = 0; i < E; ++i) {
        int u, w;
        grafoEntrada >> u >> w;

        grafo[u].push_back(w);
        grafoReverso[w].push_back(u);
    }

    grafoEntrada.close();

    dfs(grafoReverso, pre, post, V);

    posOrdem = post;

    cont = 0;
    
    dfs(grafo, pre, post, V);

	for (int i = 0; i <= V; i++) {
		pre[i] = -1;
    }

    while (!posOrdem.empty()) {
        int v = posOrdem.top();
        posOrdem.pop();

        if (pre[v] == -1) {
            vector<int> componente;
            componentes(grafo, pre, componente, v);
            for (int v_ : componente) {
                cout << v_ << " ";
            }
            cout << endl;
        }
    }
    return 0;
}