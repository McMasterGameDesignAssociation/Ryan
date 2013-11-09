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
		double speed;
		bool isMovingToSpot;
		//new
		unsigned int frameCounter;

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

		//Accessor
		int getID(void);
		direction getFace(void);
		string getBitMapName(void);
		string getDescription(void);
		double getSpeed();
		ActorVector getPosition();
		bool getMoving();
		void checkMovement(world map, int x, int y);

		//Logging function
		void printLog(void);

		//Update Function
		void updateMovement(world map);
		//moveToPlayer, currently unused
		void moveToPlayer();

};


#endif