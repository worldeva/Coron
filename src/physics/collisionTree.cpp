#include "../../include/physics/collisionTree.h"

collisionNode::collisionNode(collisionTree *nodeTree, alignedHitbox *hitbox)
{
	
}

bool collisionNode::isCollide(collisionNode *a, collisionNode *b)
{
	if(((a->aabb.xMin>= b->aabb.xMin)&&(a->aabb.xMin<= b->aabb.xMax)) || ((a->aabb.xMax >= b->aabb.xMin) && (a->aabb.xMax <= b->aabb.xMax)))
	{
		if (((a->aabb.yMin >= b->aabb.yMin) && (a->aabb.yMin <= b->aabb.yMax)) || ((a->aabb.yMax >= b->aabb.yMin) && (a->aabb.yMax <= b->aabb.yMax)))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool collisionNode::isCollide(collisionNode *check)
{
	if (((aabb.xMin >= check->aabb.xMin) && (aabb.xMin <= check->aabb.xMax)) || ((aabb.xMax >= check->aabb.xMin) && (aabb.xMax <= check->aabb.xMax)))
	{
		if (((aabb.yMin >= check->aabb.yMin) && (aabb.yMin <= check->aabb.yMax)) || ((aabb.yMax >= check->aabb.yMin) && (aabb.yMax <= check->aabb.yMax)))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool collisionNode::isCollide(collisionNode *a, alignedHitbox *b)
{
	if (((a->aabb.xMin >= b->xMin) && (a->aabb.xMin <= b->xMax)) || ((a->aabb.xMax >=b->xMin) && (a->aabb.xMax <=b->xMax)))
	{
		if (((a->aabb.yMin >=b->yMin) && (a->aabb.yMin <=b->yMax)) || ((a->aabb.yMax >=b->yMin) && (a->aabb.yMax <=b->yMax)))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool collisionNode::isCollide(alignedHitbox* checkAABB)
{
	if (((aabb.xMin >= checkAABB->xMin) && (aabb.xMin <= checkAABB->xMax)) || ((aabb.xMax >= checkAABB->xMin) && (aabb.xMax <= checkAABB->xMax)))
	{
		if (((aabb.yMin >= checkAABB->yMin) && (aabb.yMin <= checkAABB->yMax)) || ((aabb.yMax >= checkAABB->yMin) && (aabb.yMax <= checkAABB->yMax)))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

int collisionTree::createNode()
{
	return 0;
}

void collisionTree::deleteNode(int nodeIterator)
{
	
}

void collisionTree::updateCollision(int nodeIterator)
{
	do
	{
		
	} while (!updateStack.size());
}

gObject* collisionTree::getNextCollision()
{
	return collision;
}
