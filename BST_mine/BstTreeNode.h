#pragma once
#include <string>
class BstTreeNode
{

protected:
	BstTreeNode* parent;
	BstTreeNode* leftChild;
	BstTreeNode* rightChild;

	int value;

	void forgetChild(BstTreeNode* child);
	void forgetParent();
	int setParent(BstTreeNode* parent);
	int setLeftChild(BstTreeNode* node);
	int setRightChild(BstTreeNode* child);
	int replaceChild(BstTreeNode* oldNode, BstTreeNode* newNode);

	unsigned int levels;
	size_t maxLevelWidth;

public:
	BstTreeNode(int value, BstTreeNode* parent = nullptr);
	~BstTreeNode();

	BstTreeNode* addNode(int value);
	BstTreeNode* findNode(int value);
	int deleteNode();

	BstTreeNode* getLargestNodeOnTheLeft();
	BstTreeNode* getSmallestNodeOnTheRight();
	BstTreeNode* getLeftChild();
	BstTreeNode* getRightChild();
	BstTreeNode* getParent();
	
	int getValue();
	bool isLeaf();

	int updateStats();
	size_t getLargestLevelWidth();
	size_t getLevels();

	std::string stringRepr();

};

