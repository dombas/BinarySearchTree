#include "BstTreeNode.h"
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::to_string;

BstTreeNode::BstTreeNode(int value, BstTreeNode* parent) :
	value(value),
	parent(parent),
	leftChild(nullptr),
	rightChild(nullptr)
{
	levels = 0;
	maxLevelWidth = 0;
}

BstTreeNode::~BstTreeNode()
{
	if (leftChild != nullptr) {
		leftChild->forgetParent();
		delete leftChild;
	}
	if (rightChild != nullptr) {
		rightChild->forgetParent();
		delete rightChild;
	}
	if (parent != nullptr) {
		parent->forgetChild(this);
	}
}


bool BstTreeNode::isLeaf() {
	return nullptr == leftChild && nullptr == rightChild;
}

void BstTreeNode::forgetChild(BstTreeNode* child) {
	if (leftChild == child) {
		leftChild = nullptr;
	}
	else if (rightChild == child) {
		rightChild = nullptr;
	}
	else {
		// TODO somehow report bad call
	}
}


BstTreeNode* BstTreeNode::addNode(int value)
{
	if (value < getValue()) {
		if (nullptr == leftChild) {
			leftChild = new BstTreeNode(value);
			leftChild->setParent(this);
			return leftChild;
		}
		else {
			return leftChild->addNode(value);
		}
	}
	if (value > getValue()) {
		if (nullptr == rightChild) {
			rightChild = new BstTreeNode(value);
			rightChild->setParent(this);
			return rightChild;
		}
		else {
			return rightChild->addNode(value);
		}
	}
	return nullptr;
}


BstTreeNode* BstTreeNode::findNode(int value)
{
	if (value < this->value && leftChild != nullptr) {
		return leftChild->findNode(value);
	}
	if (value > this->value && rightChild != nullptr) {
		return rightChild->findNode(value);
	}
	if (value == this->value) {
		return this;
	}
	return nullptr;
}


int BstTreeNode::deleteNode()
{
	BstTreeNode* largestNodeOnTheLeft = getLargestNodeOnTheLeft();
	if (isLeaf()) {
		// no children
		parent->forgetChild(this);
	}
	else if (leftChild == nullptr
		|| rightChild == nullptr
		|| leftChild == largestNodeOnTheLeft) {
		// one child
		// or largestNodeOnTheLeft == leftChild
		BstTreeNode* heirNode;
		if (leftChild != nullptr) {
			heirNode = leftChild;
		}
		else {
			heirNode = rightChild;
		}
		parent->replaceChild(this, heirNode);
	}
	else {
		// two children
		BstTreeNode* heirNode;
		heirNode = largestNodeOnTheLeft;

		if (nullptr != heirNode->getLeftChild()) {
			//left child inherits the heirs place
			heirNode->getParent()->replaceChild(
				heirNode,
				heirNode->getLeftChild());
		}
		else
		{
			heirNode->getParent()->forgetChild(heirNode);
		}

		parent->replaceChild(this, heirNode);
		heirNode->setLeftChild(leftChild);
		heirNode->setRightChild(rightChild);
	}
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	return 0;
}


BstTreeNode* BstTreeNode::getLeftChild()
{
	return leftChild;
}


BstTreeNode* BstTreeNode::getRightChild()
{
	return rightChild;
}


void BstTreeNode::forgetParent()
{
	parent = nullptr;
}


int BstTreeNode::setLeftChild(BstTreeNode* child)
{
	// TODO: error checking
	leftChild = child;
	leftChild->setParent(this);
	return 0;
}


int BstTreeNode::setRightChild(BstTreeNode* child)
{
	// TODO: error checking
	rightChild = child;
	rightChild->setParent(this);
	return 0;
}


int BstTreeNode::setParent(BstTreeNode* parent)
{
	// TODO: error checking
	this->parent = parent;
	return 0;
}


int BstTreeNode::replaceChild(BstTreeNode* oldNode, BstTreeNode* newNode)
{
	// TODO check if newNode has correct value?
	if (oldNode == leftChild) {
		setLeftChild(newNode);
	}
	else if (oldNode == rightChild) {
		setRightChild(newNode);
	}
	else {
		// can't replace, oldNode is not a child of this node
		return -1;
	}
	return 0;
}


int BstTreeNode::updateStats()
{
	std::vector<BstTreeNode*> currentLevelList = { this };
	std::vector<BstTreeNode*> nextLevelList;
	maxLevelWidth = 0;
	levels = 0;
	while (currentLevelList.size() != 0) {
		maxLevelWidth = std::max(currentLevelList.size(), maxLevelWidth);
		levels++;
		for (BstTreeNode* node : currentLevelList)
		{
			BstTreeNode* left = node->getLeftChild();
			BstTreeNode* right = node->getRightChild();
			if (nullptr != left) {
				nextLevelList.push_back(left);
			}
			if (nullptr != right) {
				nextLevelList.push_back(right);
			}
		}
		currentLevelList = nextLevelList;
		nextLevelList.clear();
	}
	return 0;
}


string BstTreeNode::stringRepr()
{
	updateStats();
	unsigned int valueSize = 4;
	unsigned int spacing = 1;
	char paddingChar = ' ';
	char spacingChar = ' ';
	char nullChar = ' ';
	char fillChar = '0';
	bool stillMoreLevels = true;
	vector<BstTreeNode*> currentLevelNodes = { this };
	vector<BstTreeNode*> nextLevelNodes = {};

	// HACK
	// not tested for more than 4 levels
	//generate paddings (two for each level: 
	//	- padding before 1st element
	//	- padding before every other element
	vector<int> firstPaddings = {0};
	vector<int> secondPaddings = {0};
	int firstPadding = (valueSize + 1) / 2;
	int secondPadding = firstPadding * 2 + (valueSize + 1) % 2;
	for (size_t i = levels-1; i > 0; i--) {
		firstPaddings.push_back(firstPadding);
		secondPaddings.push_back(secondPadding);

		firstPadding = firstPadding * 2 + (valueSize + 2) / 2;
		secondPadding = firstPadding * 2 + (valueSize + 1) % 2;
	}

	string representation = "";
	while (stillMoreLevels) {
		stillMoreLevels = false;
		bool firstNode = true;
		firstPadding = firstPaddings.back();
		firstPaddings.pop_back();
		secondPadding = secondPaddings.back();
		secondPaddings.pop_back();

		for (BstTreeNode* node : currentLevelNodes) {
			string nodeRepresentation = "";
			if (nullptr == node) {
				nodeRepresentation.append(valueSize, nullChar);
				nextLevelNodes.push_back(nullptr);
				nextLevelNodes.push_back(nullptr);
			}
			else {
				nodeRepresentation = to_string(node->getValue());
				size_t checkIt = valueSize - nodeRepresentation.length();
				nodeRepresentation.insert(nodeRepresentation.begin(), valueSize - nodeRepresentation.length(), fillChar);

				nextLevelNodes.push_back(node->getLeftChild());
				nextLevelNodes.push_back(node->getRightChild());
				if (node->getLeftChild() != nullptr || node->getRightChild() != nullptr)
				{
					stillMoreLevels = true;
				}
			}
			if (firstPadding > 0 && firstNode) {
				representation.append(firstPadding, paddingChar);
			}
			else {
				representation.append(secondPadding, paddingChar);
			}
			representation.append(nodeRepresentation);
			representation.append(spacing, spacingChar);
			firstNode = false;
		}
		representation.append(1, '\n');

		currentLevelNodes = nextLevelNodes;
		nextLevelNodes.clear();
	}

	//build the string

	return representation;
}

int BstTreeNode::getValue() {
	return value;
}
BstTreeNode* BstTreeNode::getLargestNodeOnTheLeft()
{
	BstTreeNode* largestNodeOnTheLeft = nullptr;
	if (nullptr != leftChild) {
		largestNodeOnTheLeft = leftChild;
		while (largestNodeOnTheLeft->getRightChild() != nullptr) {
			largestNodeOnTheLeft = largestNodeOnTheLeft->getRightChild();
		}
	}
	return largestNodeOnTheLeft;
}
BstTreeNode* BstTreeNode::getSmallestNodeOnTheRight()
{
	BstTreeNode* smallestNodeOnTheLeft = nullptr;
	if (nullptr != rightChild) {
		smallestNodeOnTheLeft = rightChild;
		while (smallestNodeOnTheLeft->getLeftChild() != nullptr) {
			smallestNodeOnTheLeft = smallestNodeOnTheLeft->getLeftChild();
		}
	}
	return smallestNodeOnTheLeft;
}
BstTreeNode* BstTreeNode::getParent()
{
	return parent;
}


size_t BstTreeNode::getLargestLevelWidth()
{
	return maxLevelWidth;
}


size_t BstTreeNode::getLevels()
{
	return levels;
}
