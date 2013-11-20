#ifndef _NPC_HANDLER_
#define _NPC_HANDLER_

#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
class world; 

using namespace std;



struct ActorVector
{
	unsigned int x;
	unsigned int y;
};

class actor
{
	private:
		
		/*This tracks the direction the actor is facing
		entities up, left, down, right*/
		enum direction{up, left, down, right};

		unsigned int ID;
		direction face;
		string bitMapName;
		string description;
		ActorVector vPosition;
		int speed;
		bool isMovingToSpot;
		double visionRange; //after being spotted the NPC vision increases
		unsigned int alert;
		double maxVision;
		bool playerWithinRange;
		bool isHittingWall;

		unsigned int frameCounter; //the NPC will move after a set number of frames

	public:

		//Modifiers
		actor(unsigned int x, unsigned int y, double speed, int newID);
		actor(void);
		void setActor(direction newFace, string newBitMapName, string newDescription);
		void moveto(unsigned int x, unsigned int y);
		void changeID(unsigned int newID);
		void changeDirection(string newFace);//
		void changeBitMapName(string newbitMapName);
		void setPosition(unsigned int x, unsigned int y);
		void setSpeed(double newSpeed);
		void setMoving(bool isMoving);
		void setVisionRange(void);
		void increaseAlert(void);
		void decreaseAlert(void);
		void setSeesPlayer(bool);
		void setIsHittingWall(bool);

		//Accessor
		int getID(void);
		string getFace(void);
		string getBitMapName(void);
		string getDescription(void);
		double getSpeed();
		ActorVector getPosition();
		bool getMoving();
		void checkMovement(world map, int x, int y);
		double getVisionRange(void);
		int getAlert(void);
		bool getSeesPlayer(void);
		bool getIsHittingWall(void);

		//Logging function
		void printLog(void);

		//Update Function
		void updateMovement(world map);
		//moveToPlayer, currently unused
		void moveToPlayer();

};


#endif