#include "pch.h"
#include "../BST_mine/BstTreeNode.h"

#include <array>

class SingleNodeTest : public ::testing::Test {
protected:
	//void SetUp() override {}
	//void TearDown() override {}

	BstTreeNode root;
public:
	SingleNodeTest(void) :
		root(30) {};
};
TEST_F(SingleNodeTest, TestChildPointersAreNull) {
	EXPECT_EQ(nullptr, root.getLeftChild());
	EXPECT_EQ(nullptr, root.getRightChild());
}

TEST_F(SingleNodeTest, TestValueGetter) {
	ASSERT_EQ(30, root.getValue());
}

TEST_F(SingleNodeTest, TestAddNode) {
	ASSERT_NE(nullptr, root.addNode(29));
	ASSERT_NE(nullptr, root.addNode(32));
	ASSERT_NE(nullptr, root.addNode(31));
	//    30
	//29      32
	//      31
	BstTreeNode* node29 = root.getLeftChild();
	BstTreeNode* node32 = root.getRightChild();

	ASSERT_NE(nullptr, node29);

	EXPECT_EQ(29, node29->getValue());
	EXPECT_EQ(nullptr, node29->getLeftChild());
	EXPECT_EQ(nullptr, node29->getRightChild());
	EXPECT_EQ(&root, node29->getParent());

	ASSERT_NE(nullptr, node32);

	EXPECT_EQ(32, node32->getValue());
	BstTreeNode* node31 = node32->getLeftChild();
	EXPECT_EQ(nullptr, node32->getRightChild());
	EXPECT_EQ(&root, node32->getParent());

	ASSERT_NE(nullptr, node31);

	EXPECT_EQ(31, node31->getValue());
	EXPECT_EQ(nullptr, node31->getLeftChild());
	EXPECT_EQ(nullptr, node31->getRightChild());
	EXPECT_EQ(node32, node31->getParent());
}

TEST_F(SingleNodeTest, TestUpdateStats) {
	ASSERT_EQ(0, root.updateStats());
	EXPECT_EQ(1, root.getLargestLevelWidth());
	EXPECT_EQ(1, root.getLevels());
}

class ThreeNodeTreeTest : public ::testing::Test {
	//  2
	//1   3
protected:
	void SetUp() override {
		root.addNode(1);
		root.addNode(3);
		leftNode = root.getLeftChild();
		rightNode = root.getRightChild();
	}
	//void TearDown() override {}

	BstTreeNode root;
	BstTreeNode* leftNode;
	BstTreeNode* rightNode;

public:
	ThreeNodeTreeTest(void) :
		root(2) {
		leftNode = nullptr;
		rightNode = nullptr;
	};
};

TEST_F(ThreeNodeTreeTest, TestAddedCorrectly) {
	ASSERT_NE(nullptr, leftNode);
	EXPECT_EQ(1, leftNode->getValue());

	ASSERT_NE(nullptr, rightNode);
	EXPECT_EQ(3, rightNode->getValue());
}
TEST_F(ThreeNodeTreeTest, TestFindNode) {
	EXPECT_EQ(&root, root.findNode(2));
	EXPECT_EQ(leftNode, root.findNode(1));
	EXPECT_EQ(rightNode, root.findNode(3));
}

TEST_F(ThreeNodeTreeTest, TestDeleteLeftNode) {
	ASSERT_EQ(&root, leftNode->getParent());
	ASSERT_EQ(0, leftNode->deleteNode());
	EXPECT_EQ(nullptr, root.findNode(1));
	EXPECT_EQ(nullptr, root.getLeftChild());
	EXPECT_EQ(rightNode, root.getRightChild());
}

TEST_F(ThreeNodeTreeTest, TestUpdateStats) {
	ASSERT_EQ(0, root.updateStats());
	EXPECT_EQ(2, root.getLargestLevelWidth());
	EXPECT_EQ(2, root.getLevels());
}

class BiggerTreeTest : public ::testing::Test {
	//              543
	//       1             764
	//        457       666   991
	//    200     511
	// 199   201
protected:
	void SetUp() override {
		std::array<int, 10> valuesToAdd(
			{ 764,991,666,1001,1,457,200,199,201,511 }
		);
		for (const auto& value : valuesToAdd) {
			root.addNode(value);
		}
		node1    = root.getLeftChild();
		node457  = node1->getRightChild();
		node200  = node457->getLeftChild();
		node199  = node200->getLeftChild();
		node201  = node200->getRightChild();
		node511  = node457->getRightChild();
		node764  = root.getRightChild();
		node666  = node764->getLeftChild();
		node991  = node764->getRightChild();
		node1001 = node991->getRightChild();

	}
	/*void TearDown() override {

	}*/

	BstTreeNode root;
	BstTreeNode* node1 = nullptr;
	BstTreeNode* node457 = nullptr;
	BstTreeNode* node200 = nullptr;
	BstTreeNode* node199 = nullptr;
	BstTreeNode* node201 = nullptr;
	BstTreeNode* node511 = nullptr;
	BstTreeNode* node764 = nullptr;
	BstTreeNode* node666 = nullptr;
	BstTreeNode* node991 = nullptr;
	BstTreeNode* node1001 = nullptr;

public:
	BiggerTreeTest(void) :
		root(543)
	{
	};
};

TEST_F(BiggerTreeTest, TestAddedCorrectly) {

	ASSERT_NE(nullptr, node1);
	EXPECT_EQ(1, node1->getValue());
	EXPECT_EQ(&root, node1->getParent());

	ASSERT_NE(nullptr, node457);
	EXPECT_EQ(457, node457->getValue());
	EXPECT_EQ(nullptr, node1->getLeftChild());
	EXPECT_EQ(node1, node457->getParent());

	ASSERT_NE(nullptr, node200);
	EXPECT_EQ(200, node200->getValue());
	EXPECT_EQ(node457, node200->getParent());

	ASSERT_NE(nullptr, node199);
	EXPECT_EQ(199, node199->getValue());
	EXPECT_EQ(nullptr, node199->getLeftChild());
	EXPECT_EQ(nullptr, node199->getRightChild());
	EXPECT_EQ(node200, node199->getParent());

	ASSERT_NE(nullptr, node201);
	EXPECT_EQ(201, node201->getValue());
	EXPECT_EQ(nullptr, node201->getLeftChild());
	EXPECT_EQ(nullptr, node201->getRightChild());
	EXPECT_EQ(node200, node201->getParent());

	ASSERT_NE(nullptr, node511);
	EXPECT_EQ(511, node511->getValue());
	EXPECT_EQ(nullptr, node511->getLeftChild());
	EXPECT_EQ(nullptr, node511->getRightChild());
	EXPECT_EQ(node457, node511->getParent());

	ASSERT_NE(nullptr, node764);
	EXPECT_EQ(764, node764->getValue());
	EXPECT_EQ(&root, node764->getParent());

	ASSERT_NE(nullptr, node666);
	EXPECT_EQ(666, node666->getValue());
	EXPECT_EQ(nullptr, node666->getLeftChild());
	EXPECT_EQ(nullptr, node666->getRightChild());
	EXPECT_EQ(node764, node666->getParent());

	ASSERT_NE(nullptr, node991);
	EXPECT_EQ(991, node991->getValue());
	EXPECT_EQ(nullptr, node991->getLeftChild());
	EXPECT_EQ(node764, node991->getParent());

	ASSERT_NE(nullptr, node1001);
	EXPECT_EQ(1001, node1001->getValue());
	EXPECT_EQ(nullptr, node1001->getLeftChild());
	EXPECT_EQ(nullptr, node1001->getRightChild());
	EXPECT_EQ(node991, node1001->getParent());
}

TEST_F(BiggerTreeTest, TestGetLargestNodeOnTheLeft457) {
	BstTreeNode* nodeReturned = node457->getLargestNodeOnTheLeft();
	ASSERT_NE(nullptr, nodeReturned);
	EXPECT_EQ(201, nodeReturned->getValue());
}

TEST_F(BiggerTreeTest, TestGetLargestNodeOnTheLeft1) {
	BstTreeNode* nodeReturned = node1->getLargestNodeOnTheLeft();
	ASSERT_EQ(nullptr, nodeReturned);
}

TEST_F(BiggerTreeTest, TestGetSmallestNodeOnTheRight1) {
	BstTreeNode* nodeReturned = node1->getSmallestNodeOnTheRight();
	ASSERT_NE(nullptr, nodeReturned);
	EXPECT_EQ(199, nodeReturned->getValue());
}

TEST_F(BiggerTreeTest, TestGetSmallestNodeOnTheRight666) {
	BstTreeNode* nodeReturned = node666->getLargestNodeOnTheLeft();
	ASSERT_EQ(nullptr, nodeReturned);
}

TEST_F(BiggerTreeTest, TestIsLeaf) {
	ASSERT_NE(nullptr, node1);
	EXPECT_FALSE(node1->isLeaf());

	ASSERT_NE(nullptr, node457);
	EXPECT_FALSE(node457->isLeaf());

	ASSERT_NE(nullptr, node200);
	EXPECT_FALSE(node200->isLeaf());

	ASSERT_NE(nullptr, node764);
	EXPECT_FALSE(node764->isLeaf());

	ASSERT_NE(nullptr, node991);
	EXPECT_FALSE(node991->isLeaf());

	ASSERT_NE(nullptr, node199);
	EXPECT_TRUE(node199->isLeaf());

	ASSERT_NE(nullptr, node201);
	EXPECT_TRUE(node201->isLeaf());

	ASSERT_NE(nullptr, node511);
	EXPECT_TRUE(node511->isLeaf());

	ASSERT_NE(nullptr, node666);
	EXPECT_TRUE(node666->isLeaf());

	ASSERT_NE(nullptr, node1001);
	EXPECT_TRUE(node1001->isLeaf());
}

TEST_F(BiggerTreeTest, TestDelete199) {
	// tree after delete
	//           543
	//    1             764
	//     457       666   991
	// 200     511
	//    201
	// check node 200
	ASSERT_EQ(0, node199->deleteNode());
	EXPECT_EQ(nullptr, node200->getLeftChild());
}

TEST_F(BiggerTreeTest, TestDelete1) {
	// tree after delete
	//              543
	//        457         764
	//    200     511  666   991
	// 199   201
	// check node 457, 543
	ASSERT_NE(nullptr, node1);
	ASSERT_NE(nullptr, node457);

	ASSERT_EQ(0, node1->deleteNode());
	EXPECT_EQ(node457, root.getLeftChild());
	EXPECT_EQ(node200, node457->getLeftChild());
	EXPECT_EQ(node511, node457->getRightChild());
}
TEST_F(BiggerTreeTest, TestDelete457) {
	
	// tree after delete
	//              543
	//       1             764
	//        201       666   991
	//    200     511
	// 199   
	// check nodes 1, 201, 511, 200
	ASSERT_NE(nullptr, node457);
	EXPECT_EQ(0, node457->deleteNode());

	// check node 1
	ASSERT_NE(nullptr, node1);
	EXPECT_EQ(&root, node1->getParent());
	EXPECT_EQ(nullptr, node1->getLeftChild());
	EXPECT_EQ(node201, node1->getRightChild());

	// check node 201
	ASSERT_NE(nullptr, node201);
	EXPECT_EQ(node1, node201->getParent());
	EXPECT_EQ(node200, node201->getLeftChild());
	EXPECT_EQ(node511, node201->getRightChild());

	// check node 511
	ASSERT_NE(nullptr, node511);
	EXPECT_EQ(node201, node511->getParent());
	EXPECT_EQ(nullptr, node511->getLeftChild());
	EXPECT_EQ(nullptr, node511->getRightChild());

	// check node 200
	ASSERT_NE(nullptr, node200);
	EXPECT_EQ(node201, node200->getParent());
	EXPECT_EQ(node199, node200->getLeftChild());
	EXPECT_EQ(nullptr, node200->getRightChild());

	// check node 457
	ASSERT_NE(nullptr, node457);
	EXPECT_EQ(nullptr, node457->getParent());
	EXPECT_EQ(nullptr, node457->getLeftChild());
	EXPECT_EQ(nullptr, node457->getRightChild());

	// check can't find node 457
	EXPECT_EQ(nullptr, root.findNode(457));
}

TEST_F(BiggerTreeTest, TestUpdateStats) {
	ASSERT_EQ(0, root.updateStats());
	EXPECT_EQ(3, root.getLargestLevelWidth());
	EXPECT_EQ(5, root.getLevels());
}