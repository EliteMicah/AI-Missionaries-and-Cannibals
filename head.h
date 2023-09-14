#ifndef HEAD_H
#define HEAD_H

struct mcState {
	bool boatPresent = 1; //true if boat is on the original side
	int mis; //number of missionaries on the original side
	int can; //number of cannibals on the original side
};
// Start = { 3, 3, 1 }; Goal = { 0,0,0 };
//           M, C, B

struct mcNode { //structure of each node in the tree
	mcState state; //state of the node
	mcState parent; //the state of the parent node
	double costG; //g(n), cost from start to present
	int action;
	int stateID; // why was stateID used in the other problem but not this one
	// 1 = one cannibal; 2 = two cannibals; 10 = one missionary; 20 = two missionaries;
	// 11 = one missionary + one cannibal
};

#endif
