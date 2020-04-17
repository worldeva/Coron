#include "../../include/physics/gObject.h"

gObject::gObject(int xPosition, int yPosition, int xVelocity, int yVelocity, int spriteNumber)
{
	xPos = xPosition;
	yPos = yPosition;
	xVel = xVelocity;
	yVel = yVelocity;
	spriteClip = spriteNumber;
}

void entity::collisonResolve(projectile* collidedObject)
{
}

void entity::collisonResolve(item* collidedObject)
{
}

void entity::collisonResolve(solid* collidedObject)
{
}

void entity::collisonResolve(entity* collidedObject)
{
}

void projectile::collisonResolve(projectile* collidedObject)
{
}

void projectile::collisonResolve(item* collidedObject)
{
}

void projectile::collisonResolve(solid* collidedObject)
{
}

void projectile::collisonResolve(entity* collidedObject)
{
}
