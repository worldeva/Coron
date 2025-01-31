#pragma once
#include "../screen/tSprite.h"
#include <string>
#include <vector>

class alignedHitbox
{
public:
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

class gObject
{
public:
	gObject(int xPosition, int yPosition, int xVelocity, int yVelocity, int spriteNumber);
	alignedHitbox aabb;
	int nodeIterator;
protected:
	int spriteClip;

	int xPos;
	int yPos;

	double xVel;
	double yVel;
};

class entity;
class player;
class projectile;
class item;
class solid;

class entity : public gObject
{
public:
	void collisonResolve(projectile* collidedObject);
	void collisonResolve(item* collidedObject);
	void collisonResolve(solid* collidedObject);
	void collisonResolve(entity* collidedObject);
private:
};

class player : public gObject
{

private:
};

class projectile : public gObject
{
public:
	void collisonResolve(projectile* collidedObject);
	void collisonResolve(item* collidedObject);
	void collisonResolve(solid* collidedObject);
	void collisonResolve(entity* collidedObject);
private:

};

class item : public gObject
{

};

class solid : public gObject
{

};