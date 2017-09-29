/*
Codeforces Alpha Round #20 C. Dijksrta?
http://codeforces.com/problemset/problem/20/C

Yudhistira Erlandinata
*/

#include <bits/stdc++.h>

using namespace std;

const long long INF = 0x7FFFFFFFFFFFFFFF;

struct Node;
struct Edge;

struct Node{
    int index;
    Node* before;
    vector<Edge> edgeList;
    long long cost = INF;

    Node(int i){
        index = i;
    }

};

struct Edge{
    Node* left;
    Node* right;
    int weight;
};

struct NodeComparator{
    bool operator()(const Node* a, const Node* b){
        return a->cost > b->cost;
    }
};

void printAns(Node* dest){
    stack<int> idx;
    while(dest->index != 1){
        idx.push(dest->index);
        dest = dest->before;
    }

    cout << "1 ";
    while(!idx.empty()){
        cout << idx.top() << ' ';
        idx.pop();
    }
    cout << endl;

}


Node* nodes[100005];

int main(){
    int n, m;
    cin >> n >> m;
    int a, b, w;
    for(int i = 1; i <= n; i++) 
        nodes[i] = new Node(i);
    nodes[1]->cost = 1;
    for(int i = 0; i < m; i++){
        cin >> a >> b >> w;
        if (a == b) continue;
        Edge edge;
        edge.left = nodes[a];
        edge.right = nodes[b];
        edge.weight = w;
        nodes[a]->edgeList.push_back(edge);
        nodes[b]->edgeList.push_back(edge);
    }


    //dijkstra
    priority_queue<Node*, vector<Node*>, NodeComparator> pq;
    pq.push(nodes[1]);

    while(!pq.empty()){
        Node* current = pq.top();
        pq.pop();
        if (current->index == n){
            printAns(current);
            return 0;
        }

        for(int i = 0; i < current->edgeList.size(); i++){
            if (current->edgeList[i].left->index != current->index){
                if (current->edgeList[i].left->cost > current->cost + current->edgeList[i].weight){ //update
                    current->edgeList[i].left->cost = current->cost + current->edgeList[i].weight;
                    current->edgeList[i].left->before = current;
                    pq.push(current->edgeList[i].left);
                }
            } else if (current->edgeList[i].right->index != current->index){
                if (current->edgeList[i].right->cost > current->cost + current->edgeList[i].weight){ //update
                    current->edgeList[i].right->cost = current->cost + current->edgeList[i].weight;
                    current->edgeList[i].right->before = current;
                    pq.push(current->edgeList[i].right);
                }
            }
        }

    }

    cout << "-1\n";

    return 0;
}