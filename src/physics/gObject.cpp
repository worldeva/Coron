#include "../../include/physics/gObject.h"

gObject::gObject(int xPosition, int yPosition, int xVelocity, int yVelocity, int spriteNumber)
{
	xPos = xPosition;
	yPos = yPosition;
	xVel = xVelocity;
	yVel = yVelocity;
	nodeIterator = NULL;
	spriteClip = spriteNumber;
}
