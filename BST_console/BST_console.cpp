// BST_console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include "../BST_mine/BstTreeNode.h"

using std::cout;
using std::endl;
using std::string;

BstTreeNode root(543);

void printLine() {
	cout << endl << string(100, '-') << endl << endl;
}

void printTree() {
	cout << root.stringRepr();
}

void setUp() {
	std::array<int, 10> valuesToAdd(
		{ 764,991,666,1001,1,457,200,199,201,511 }
	);
	for (const auto& value : valuesToAdd) {
		root.addNode(value);
		printTree();
		printLine();
	}
}

int main()
{
	setUp();
	root.findNode(457)->deleteNode();
	printTree();

}
