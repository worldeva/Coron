#include "../../include/physics/collisionTree.h"

collisionNode::collisionNode()
{
	isLeaf = NULL;
	aabb = {NULL, NULL, NULL, NULL};
	leftNode = NULL;
	rightNode = NULL;
	parent = NULL;
}

collisionNode::collisionNode(alignedHitbox* hitbox, int leftNod, int rightNod, int parentIndex)
{
	isLeaf = false;
	aabb = *hitbox;
	leftNode = leftNod;
	rightNode = rightNod;
	parent = parentIndex;
}

collisionNode::collisionNode(alignedHitbox* hitbox, gObject *thing, int parentIndex)
{
	isLeaf = true;
	aabb = *hitbox;
	object = thing;
	parent = parentIndex;
}

collisionNode::collisionNode(collisionTree *nodeTree, alignedHitbox *hitbox)
{
	nodeTree->createNode(hitbox);
}

collisionNode::~collisionNode() //destructor may be unecessary
{
	aabb = {NULL, NULL, NULL, NULL};
	parent = NULL;
	if(isLeaf)
	{
		object = nullptr;
	}
	else
	{
		leftNode = NULL;
		rightNode = NULL;
	}
	isLeaf = false;
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
	if(creationHitbox->xMin>=nodeVector[startingNode].aabb.xMin
	&&creationHitbox->yMin>=nodeVector[startingNode].aabb.yMin
	&&creationHitbox->xMax<=nodeVector[startingNode].aabb.xMax
	&&creationHitbox->yMax<=nodeVector[startingNode].aabb.yMax)
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
				nodeVector[freeNodes.back()] = nodeVector[startingNode];
				nodeVector[startingNode].isLeaf = false;
				nodeVector[freeNodes.back()].parent = startingNode;
				nodeVector[startingNode].leftNode = freeNodes.back();
				freeNodes.pop_back();
				nodeVector[startingNode].aabb = {
					std::min<int>(nodeVector[startingNode].aabb.xMin, creationHitbox->xMin),//minx
					std::min<int>(nodeVector[startingNode].aabb.yMin, creationHitbox->yMin),//miny
					std::max<int>(nodeVector[startingNode].aabb.xMax, creationHitbox->xMax),//maxx
					std::max<int>(nodeVector[startingNode].aabb.yMax, creationHitbox->yMax) //maxy
				};
				if(!freeNodes.empty)
				{
					int returnNumber = freeNodes.back();
					nodeVector[freeNodes.back()].isLeaf=true;
					nodeVector[freeNodes.back()].aabb = *creationHitbox;
					nodeVector[freeNodes.back()].parent = startingNode;
					nodeVector[startingNode].rightNode = freeNodes.back();
					freeNodes.pop_back();
					return returnNumber;
				}
				else
				{
					nodeVector.push_back(collisionNode(creationHitbox, nullptr, startingNode));
					return (nodeVector.size-1);
				}
			}
			else
			{
				nodeVector.push_back(nodeVector[startingNode]);
				nodeVector[startingNode].isLeaf = false;
				nodeVector[startingNode].leftNode = (nodeVector.size-1);
				nodeVector.push_back(collisionNode(creationHitbox, nullptr, startingNode));
				nodeVector[startingNode].rightNode = (nodeVector.size-1);
				return (nodeVector.size-1);
			}
		}
	}
	else
	{
		if (!freeNodes.empty)
		{
			nodeVector[freeNodes.back()] = nodeVector[startingNode];
			nodeVector[startingNode].isLeaf = false;
			nodeVector[freeNodes.back()].parent = startingNode;
			nodeVector[startingNode].leftNode = freeNodes.back();
			freeNodes.pop_back();
			nodeVector[startingNode].aabb = {
				std::min<int>(nodeVector[startingNode].aabb.xMin, creationHitbox->xMin),//minx
				std::min<int>(nodeVector[startingNode].aabb.yMin, creationHitbox->yMin),//miny
				std::max<int>(nodeVector[startingNode].aabb.xMax, creationHitbox->xMax),//maxx
				std::max<int>(nodeVector[startingNode].aabb.yMax, creationHitbox->yMax) //maxy
			};
			if(!freeNodes.empty)
			{
				int returnNumber = freeNodes.back();
				nodeVector[freeNodes.back()].isLeaf=true;
				nodeVector[freeNodes.back()].aabb = *creationHitbox;
				nodeVector[freeNodes.back()].parent = startingNode;
				nodeVector[startingNode].rightNode = freeNodes.back();
				freeNodes.pop_back();
				return returnNumber;
			}
			else
			{
				nodeVector.push_back(collisionNode(creationHitbox, nullptr, startingNode));
				return (nodeVector.size-1);
			}
		}
		else
		{
			nodeVector.push_back(nodeVector[startingNode]);
			nodeVector[startingNode].isLeaf = false;
			nodeVector[startingNode].leftNode = (nodeVector.size-1);
			nodeVector.push_back(collisionNode(creationHitbox, nullptr, startingNode));
			nodeVector[startingNode].rightNode = (nodeVector.size-1);
			return (nodeVector.size-1);
		}
	}
}

void collisionTree::deleteNode(int nodeIterator)
{
	if (nodeVector[nodeVector[nodeIterator].parent].leftNode == nodeIterator) //consider adding bool for l/r to limit ac
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
	nodeVector[nodeIterator].~collisionNode();
	freeNodes.push_back(nodeIterator);
	nodeVector[nodeVector[nodeIterator].parent].~collisionNode();
	freeNodes.push_back(nodeVector[nodeIterator].parent);
}

void collisionTree::updateCollision(int nodeIterator)
{
	updateStack.push_back(0);
	nodeCollisions.push_back(collisionEvent({nodeVector[nodeIterator].object}));
	while (updateStack.size())
	{
		if(nodeVector[nodeIterator].isCollide(&nodeVector[updateStack.back()]))
		{
			if(!nodeVector[updateStack.back()].isLeaf)
			{
				updateStack.push_back(nodeVector[updateStack.back()].leftNode);
				updateStack.push_back(nodeVector[updateStack.back()].rightNode);
			}
			else
			{
				nodeCollisions.back().collisions.push_back(updateStack.back);
			}
		}
		updateStack.pop_back();
	}
}

void collisionTree::updateBox(gObject* updatedObject)
{
	if(!(updatedObject->aabb.xMin>=nodeVector[updatedObject->nodeIterator].aabb.xMin
	&&updatedObject->aabb.yMin>=nodeVector[updatedObject->nodeIterator].aabb.yMin
	&&updatedObject->aabb.xMax<=nodeVector[updatedObject->nodeIterator].aabb.xMax
	&&updatedObject->aabb.yMax<=nodeVector[updatedObject->nodeIterator].aabb.yMax))
	{
		int temp;
		temp = createNode(&updatedObject->aabb);
		deleteNode(updatedObject->nodeIterator);
		nodeVector[temp].object = updatedObject;
		updatedObject->nodeIterator = temp;
	}
}

collisionEvent collisionTree::getNextCollision()
{

}

gObject* collisionTree::peekNextCollision()
{
	return nullptr;
}