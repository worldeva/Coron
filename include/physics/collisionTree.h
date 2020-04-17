#pragma once
#include "gObject.h"
#include <vector>

class collisionTree;
class alignedHitbox;
class collisionNode;

class alignedHitbox
{
public:
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

class collisionEvent
{
public:
	gObject* 
};

class collisionNode
{
public:
	collisionNode(collisionTree* nodeTree, alignedHitbox* hitbox);

	static bool isCollide(collisionNode* a, collisionNode* b);
	bool isCollide(collisionNode* check);
	static bool isCollide(collisionNode* a, alignedHitbox* b);
	bool isCollide(alignedHitbox* checkAABB);
private:
	bool isLeaf;

	alignedHitbox aabb;

	union
	{
		int parent;
		int next;
	};

	union
	{
		class
		{
		public:
			int leftNode;
			int rightNode;
		};
		gObject* object;
	};
};

class collisionTree
{
public:
	int findSpace();
	int createNode();
	void deleteNode(int nodeIterator);

	void updateCollision(int nodeIterator);

	gObject* getNextCollision();
	gObject* peekNextCollision();
private:
	std::vector<collisionNode> nodeVector;
	std::vector<int> freeNodes;
	std::vector<gObject*> nodeCollisions;
	std::vector<int> updateStack;
};