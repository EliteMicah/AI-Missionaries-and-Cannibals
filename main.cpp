#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include "head.h"
using namespace std;


vector<int> breadth_first_searchMC(mcNode, int, int);
vector<mcNode> expand(mcNode, int, int, vector<int>);
vector<mcNode> solution(mcNode, map<int, mcNode>&);

int main() {

    mcNode curr = {3, 3, 1};
    
    string miss = "";
    string cann = "";

    cout << "Number of Missionaries: "; 
    getline(cin, miss);

    cout << "Number of Cannibals: ";
    getline(cin, cann);

    curr.state.mis = stoi(miss);
    curr.state.can = stoi(cann);

    cout << "Missionaries: " << curr.state.mis << ", Cannibals: " << curr.state.can;

    cout << breadth_first_searchMC(curr, curr.state.mis, curr.state.can)[0];
    


    cout << endl;
    system("pause");
    return 0;
}

vector<int> breadth_first_searchMC(mcNode curr, int M, int C) {

    mcNode start = {0, -1, 0, -1};
    
    // If mis == goal && can == goal && boat == 0/false
    if (M == 0 && C == 0 && curr.state.boatPresent == 0)
        return { 0, 0, 0 };

    queue<mcNode> frontier; //Frontier is a queue for BFS
    map<int, mcNode> reached; //Explored set implemented as STL map
    reached[start.stateID] = start; // FIX
    frontier.push(start); //initialize the frontier with the start node

    vector<int> final = {};


    while (frontier.empty()) {
        
        //take next node from frontier
        mcNode curr = frontier.front();
        frontier.pop();

        vector<mcNode> children = expand(curr, M, C, final);
        for (auto x : children) {
            if ((x.state.mis == 0 && x.state.can == 0 && x.state.boatPresent == 0)) {
                for (int i = 0; i < children.size(); i++) {
                    final.push_back(children[i].stateID);
                }

                return final;
                //return solution(x, reached); //reached the goal state, return solution
                // converting solution to vector<int> so I can return it
                
                //insert the children nodes into frontier if not explored yet
                if (reached.find(x.stateID) == reached.end())
                    frontier.push(x);
            }
        }

    }

    /*
    measNode start = { 0, -1, 0, -1 }; //the start node
    if (goal == 0)
        return {start};
    queue<measNode> frontier; //Frontier is a queue for BFS
    map<int, measNode> reached; //Explored set implemented as STL map
    reached[start.stateId]=start;
    frontier.push(start); //initialize the frontier with the start node

    while (!frontier.empty()) {
        mcNode curr = frontier.front(); frontier.pop(); //take next node from frontier
        vector<mcNode> children = Expand(curr,A,B); //get the children nodes
        for (auto x:children) {
            if ((x.stateId / 100 == goal) || (x.stateId % 100 == goal))
                return Solution(x, reached); //reached the goal state, return solution

            //insert the children nodes into frontier if not explored yet
            if (reached.find(x.stateId) == reached.end()){
                frontier.push(x);
        }
    reached[x.stateId]=x;
    */

    // failure
    cout << endl;
    return { -1 };
}

vector<mcNode> expand(mcNode curr, int M, int C, vector<int> final) {

    int m = curr.state.mis;
    int c = curr.state.can;
    mcNode newnode{};
    vector<mcNode> children;
    newnode.parent = curr.state;
    newnode.costG = curr.costG + 1;

    // Move 1 Can to other side
    if (c == 1 && m == 0) {
        newnode.state.mis = C - 1;
        newnode.action = 1;
        newnode.state.boatPresent = 0;
        children.push_back(newnode);
    }

    // Move 2 Can to other side
    if (c == 2) {
        newnode.state.mis = C - 2;
        newnode.action = 2;
        newnode.state.boatPresent = 0;
        children.push_back(newnode);
    }

    // Move 1 Mis to other side
    if (m == 1 && c == 0) { 
        newnode.state.mis = M - 1;
        newnode.action = 10;
        newnode.state.boatPresent = 0;
        children.push_back(newnode);
    }

    // Move 1 Mis to other side
    if (m == 2) {
        newnode.state.mis = M - 2;
        newnode.action = 20;
        newnode.state.boatPresent = 0;
        children.push_back(newnode);
    }

    // Move 1 Mis and Can to the other side
    if (m == 1 && c == 1) {
        newnode.state.mis = M - 1;
        newnode.state.can = C - 1;
        newnode.action = 11;
        newnode.state.boatPresent = 0;
        children.push_back(newnode);
    }

    // Returning the boat back motion/function ??
    return children;
}

/*
function SOLUTION(node) returns a list of nodes
    persistent : explored, a map indexed by state holding the nodes explored
    sol ← an empty list of nodes
    sol.insert(node)
    while node.PARENT do
        node = explored[node.PARENT]
        sol.insert(node) insert at the beginning of the list
    return sol
*/

vector<mcNode> solution(mcNode curr, map<int, mcNode>& reached) {
    vector<mcNode> sol;
    sol.push_back(curr);
    while (curr.stateID >= 0) { // has not reached the start state FIX ?
        curr = reached[curr.stateID];
        sol.push_back(curr);
    }
    return sol;
}


/*
Rules:
1. The boat can carry at most two people
2. If cannibals num greater than missionaries then the cannibals would eat the missionaries
3. The boat cannot cross the river by itself with no people on board
*/
