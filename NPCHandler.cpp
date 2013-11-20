#include <Windows.h>
#include "WORLD.h"
#include "NPCHandler.h"




actor::actor(unsigned int x, unsigned int y, double speed, int newID)
{
	this->vPosition.x = x;
	this->vPosition.y = y;
	this->speed = speed;
	this->ID = newID;
	//this->face = up;
	this->bitMapName = "None";
	this->description = "This is an empty character";
	this->frameCounter = 0;
	this->visionRange = 5*64;
	this->alert = 0;
	this->playerWithinRange;
	this->maxVision = visionRange + 4*64;
	this->isHittingWall;
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

void actor::changeDirection(string newFace)
{
	if(newFace == "up"){
		this->face = up;
	}
	if(newFace == "down"){
		this->face = down;
	}
	if(newFace == "left"){
		this->face = left;
	}
	if(newFace == "right"){
		this->face = right;
	}
}

string actor::getFace(void)
{
	if(this->face == up){
		return "up";
	}
	if(this->face == down){
		return "down";
	}
	if(this->face == left){
		return "left";
	}
	if(this->face == right){
		return "right";
	}
}

void actor::increaseAlert(void)
{
	this->alert++;
	this->visionRange = maxVision;
	this->speed = 4;
}
void actor::decreaseAlert(void)
{
	this->alert--;
	this->visionRange=5*64;
	this->speed = 2;
}

int actor::getAlert(void)
{
	return this->alert;
}

void actor::setSeesPlayer(bool canSeePlayer)
{
	this->playerWithinRange = canSeePlayer;
}

bool actor::getSeesPlayer(void)
{
	return this->playerWithinRange;
}


void actor::setVisionRange(void){
	
}

double actor::getVisionRange(void)
{
	return this->visionRange;
}

/* checkMovement
* this function checks to make sure there is no block preventing movement
* same as the function for the player 
* made by ben
*/

void actor::checkMovement(world map, int x, int y)
{
	unsigned int posOne[2];
	unsigned int posTwo[2];
	unsigned int posThree[2];
	unsigned int posFour[2];
	int speed  = getSpeed();
	x = (x >= 1) ? speed : x;
	x = (x <= -1) ? -speed : x;
	y = (y >= 1) ? speed : y;
	y = (y <= -1) ? -speed : y;
	
	speed = 64 - speed;


	//This is a check of the lower bound of movement
	posOne[0] = (x + getPosition().x)/64, posOne[1] = (y + getPosition().y)/64;
	//This is a check of the upper bound of movement
	posTwo[0] = (x + speed + getPosition().x)/64, posTwo[1] = (y + speed + getPosition().y)/64;

	//This is a check of the lower bound of movement
	posThree[0] = (x + getPosition().x)/64, posThree[1] = (y + speed + getPosition().y)/64;
	//This is a check of the upper bound of movement
	posFour[0] = (x + speed + getPosition().x)/64, posFour[1] = (y + getPosition().y)/64;

	/*cout << "pos one: " << posOne[0] << " " << posOne[1] << endl;
	cout << "pos two: " << posTwo[0] << " " << posTwo[1] << endl;
	cout << "pos three: " << posThree[0] << " " << posThree[1] << endl;
	cout << "pos four: " << posFour[0] << " " << posFour[1] << endl << endl;*/
	if(map.checkTileMap(posOne) && map.checkTileMap(posTwo) && map.checkTileMap(posThree) && map.checkTileMap(posFour)) 
	{
		posOne[0] = x + getPosition().x, posOne[1] = y + getPosition().y;
		setPosition(posOne[0], posOne[1]);
		setIsHittingWall(false);
	}else{
		setIsHittingWall(true);
	}
}

void actor::updateMovement(world map)
{
	if (this->getMoving() == true)
	{
		if(frameCounter > 10-speed){
			//cout << this->face;
			if (face == up){
				//vPosition.y += speed;
				checkMovement(map, 0, 1);
			} 
			if (face == right){
				//vPosition.x += speed;
				checkMovement(map, 1, 0);
			}
			if (face == left) {
				//vPosition.x -= speed;
				checkMovement(map, -1, 0);
			}
			if (face == down) {
				//vPosition.y -= speed;
				checkMovement(map, 0, -1);
			}

			frameCounter = 0;
		}
		frameCounter ++;
	}
}

bool actor::getIsHittingWall(void)
{
	return this->isHittingWall;
}

void actor::setIsHittingWall(bool hitWall)
{
	this->isHittingWall = hitWall;
}


void actor::moveToPlayer()
{
	
}