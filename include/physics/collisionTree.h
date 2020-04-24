#pragma once
#include "gObject.h"
#include <vector>
#include <algorithm>

class collisionTree;
class collisionNode;
class collisionEvent;

class collisionEvent
{
public:
	gObject* object;
	std::vector<gObject*> collisions;
};

class collisionNode
{
public:
	collisionNode();
	collisionNode(alignedHitbox* hitbox, int leftNod, int rightNod, int parentIndex);
	collisionNode(alignedHitbox* hitbox, gObject *thing, int parentIndex);
	collisionNode(collisionTree* nodeTree, alignedHitbox* hitbox);
	~collisionNode();

	static bool isCollide(collisionNode* a, collisionNode* b);
	bool isCollide(collisionNode* check);
	static bool isCollide(collisionNode* a, alignedHitbox* b);
	bool isCollide(alignedHitbox* checkAABB);

	bool isLeaf;

	alignedHitbox aabb;

	int parent;

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
	int createNode(alignedHitbox *creationHitbox, int startingNode=0);
	void deleteNode(int nodeIterator);

	void updateCollision(int nodeIterator);
	void updateBox(gObject* updatedObject);

	collisionEvent getNextCollision();
	gObject* peekNextCollision();
private:
	std::vector<collisionNode> nodeVector;
	std::vector<int> freeNodes;
	std::vector<collisionEvent> nodeCollisions;
	std::vector<int> updateStack;
};