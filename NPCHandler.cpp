#include <Windows.h>
#include "WORLD.h"
#include "NPCHandler.h"

actor::actor(unsigned int x, unsigned int y, double speed, int newID)
{
	this->vPosition.x = x;
	this->vPosition.y = y;
	this->speed = speed;
	this->ID = newID;
	this->face = up;
	this->bitMapName = "None";
	this->description = "This is an empty character";
}

bool actor::getMoving()
{
	return this->isMovingToSpot;
}

void actor::setMoving(bool isMoving)
{
	this->isMovingToSpot = isMoving;
}

double actor::getSpeed()
{
	return this->speed;
}

void actor::setSpeed(double newSpeed)
{
	this->speed = newSpeed;
}

ActorVector actor::getPosition()
{
	return this->vPosition;
}

void actor::setPosition(unsigned int x, unsigned int y)
{
	this->vPosition.x = x;
	this->vPosition.y = y;
}

void actor::moveto(unsigned int x, unsigned int y)
{
	
}

void actor::updateMovement()
{
	if(this->getMoving() == true)
	{

	}
}