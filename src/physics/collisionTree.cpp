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

int collisionTree::createNode(alignedHitbox* creationHitbox, int startingNode)
{
	if (!nodeVector[startingNode].isLeaf) // Check if left or right node would be larger, default left
	{
		if (/*Conditional Start*/(/*leftSize Start*/(/*Find xLength*/
			std::max<int>(nodeVector[nodeVector[startingNode].leftNode].aabb.xMax, creationHitbox->xMax) //higher x coord
			-
			std::min<int>(nodeVector[nodeVector[startingNode].leftNode].aabb.xMin, creationHitbox->xMin) //lesser x coord
			)//Find xLength End
			*
			(//Find yLength
				std::max<int>(nodeVector[nodeVector[startingNode].leftNode].aabb.yMax, creationHitbox->yMax) //higher y coord
				-
				std::min<int>(nodeVector[nodeVector[startingNode].leftNode].aabb.yMin, creationHitbox->yMin) //lower y coord
				)/*Find yLength End*/) // leftSize end
			<= //less-than or equal to
			(/*RightSize Start*/(//Find xLength Start
				std::max<int>(nodeVector[nodeVector[startingNode].rightNode].aabb.xMax, creationHitbox->xMax) //higher x coord
				-
				std::min<int>(nodeVector[nodeVector[startingNode].rightNode].aabb.xMin, creationHitbox->xMin) //lower x coord
				)//Find xLength End
			*
			(//Find yLength Start
				std::max<int>(nodeVector[nodeVector[startingNode].rightNode].aabb.yMax, creationHitbox->yMax) //higher y coord
				-
				std::min<int>(nodeVector[nodeVector[startingNode].rightNode].aabb.yMin, creationHitbox->yMin) //lower y coord
				)/*Find yLength End*/)/*rightSize End*/) /*Conditional End*/
		{
			return createNode(creationHitbox, nodeVector[startingNode].leftNode);
		}
		else
		{
			return createNode(creationHitbox, nodeVector[startingNode].rightNode);
		}
	}
	else
	{
		if (!freeNodes.empty)
		{
			int returnVariable;
			returnVariable = freeNodes.back;
			freeNodes.pop_back();
			return returnVariable;
		}
		else
		{
			nodeVector.push_back(collisionNode(this, creationHitbox));
			return (nodeVector.size-1);
		}
	}
}

void collisionTree::deleteNode(int nodeIterator)
{
	if (nodeVector[nodeVector[nodeIterator].parent].leftNode == nodeIterator) //consider adding bool for l/r to limit comparisons
	{
		if (nodeVector[nodeVector[nodeVector[nodeIterator].parent].parent].leftNode == nodeIterator) //condsider making local scoped variables for these to cut down on dereferences
		{
			nodeVector[nodeVector[nodeVector[nodeIterator].parent].parent].leftNode = nodeVector[nodeVector[nodeIterator].parent].rightNode;
		}
		else
		{
			nodeVector[nodeVector[nodeVector[nodeIterator].parent].parent].rightNode = nodeVector[nodeVector[nodeIterator].parent].rightNode;
		}
	}
	else
	{
		if (nodeVector[nodeVector[nodeVector[nodeIterator].parent].parent].leftNode == nodeIterator) 
		{
			nodeVector[nodeVector[nodeVector[nodeIterator].parent].parent].leftNode = nodeVector[nodeVector[nodeIterator].parent].leftNode;
		}
		else
		{
			nodeVector[nodeVector[nodeVector[nodeIterator].parent].parent].rightNode = nodeVector[nodeVector[nodeIterator].parent].leftNode;
		}
	}
}

void collisionTree::updateCollision(int nodeIterator)
{
	do
	{
		
	} while (!updateStack.size());
}

collisionEvent collisionTree::getNextCollision()
{

}

gObject* collisionTree::peekNextCollision()
{
	return nullptr;
}
