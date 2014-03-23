#pragma once
#ifndef _WORLD_METHODS
#define _WORLD_METHODS

#include "WORLD.h"

/*
inputs
	unsigned int size[2] - This is the size of the world you are building
						   specifying the x and y values respectively
outputs void
This function clears all of the arrays and sets, and then builds a map
that contains only empty tiles, objects, and actors
*/
world::world(string worldFile)
{
	gameFile = new FileReader(worldFile);
	timingFunction = new counter();
	dimensions[0] = gameFile -> getX();
	dimensions[1] = gameFile -> getY();
	//Added by Ryan Davis. 
	//NPC variable initializations
	detectionRange = resolution * 100;
	frameCounter = 0;
	frameStop = 0;

	tileSet.clear();
	objectSet.clear();
	actorSet.clear();
	resolution = 64;
	
	delete[] tileLocations;
	delete[] objectLocations;
	delete[] actorLocations;

	tileLocations = new int[dimensions[0]*dimensions[1]];
	objectLocations = new int[dimensions[0]*dimensions[1]];
	
	tile block;
	addTile(block);
	
	object objectBlock;
	addObject(objectBlock);

	unsigned int temp[2];
	
	for(unsigned int i = 0; i < dimensions[0]; i++)
	{
		for(unsigned int j =0; j < dimensions[1]; j++) 
		{
			temp[0] = i, temp[1] = j;
			setTileLocation(temp, 0);
			setObjectLocation(temp, 0);
		}
	}
	playerStartLocation[0] = dimensions[0] - 1;
	playerStartLocation[1] = dimensions[1] - 1;
}

tile world::getTile(unsigned int ID) {return tileSet.at(ID);}
object world::getObject(unsigned int ID) {return objectSet.at(ID);}
actor world::getCharacter(unsigned int ID) {return actorSet.at(ID);}
vector<tile> world::getTileSet(void) {return tileSet;}
vector<object> world::getObjectSet(void) {return objectSet;}
vector<actor> world::getActorSet(void) {return actorSet;}
bool world::getTileCollision(unsigned int ID)
{
	if(ID < 0) return false;
	else if(ID > tileSet.size()) return false;
	else return tileSet.at(ID).getPassThrough();
}
bool world::getObjectCollision(unsigned int ID) {return objectSet.at(ID).getPassThrough();}
int world::getResolution(void) {return resolution;}

void world::changeResolution(int newResolution) {resolution = newResolution;}
/*
inputs
	unsigned int size[2] - This is the new dimensions of the world
outputs
	void

This function resizes the dimensions of current world, by resizing
the tile, object and actor maps
*/
void world::changeDimension(unsigned int size[2])
{
	dimensions[0] = unsigned int(size[0]);
	dimensions[1] = unsigned int(size[1]);

	delete[] tileLocations;
	delete[] objectLocations;
	delete[] actorLocations;

	tileLocations = new int[size[0]*size[1]];
	objectLocations = new int[size[0]*size[1]];
	actorLocations = new int[size[0]*size[1]];
	unsigned int temp[2];
	/*
	This will be updated later so that the existing 
	map will be maintained in the new map
	*/
	for(unsigned int i = 0; i < dimensions[0]; i++)
	{
		for(unsigned int j = 0; j < dimensions[1]; j++) 
		{
			temp[0] = i, temp[1] = j;
			setTileLocation(temp, 0);
			setObjectLocation(temp, 0);
		}
	}
	playerStartLocation[0] = dimensions[0] - 1;
	playerStartLocation[1] = dimensions[1] - 1;
}

void world::changeTilePassthrough(unsigned int ID, bool passable) {tileSet.at(ID).changePassThrough(passable);}
void world::changeObjectPassthrough(unsigned int ID, bool passable) {objectSet.at(ID).changePassThrough(passable);}
void world::setTiles(vector<tile> newTileSet) {tileSet = newTileSet;}
void world::setObjects(vector<object> newObjectSet) {objectSet = newObjectSet;}
void world::setActor(vector<actor> newActorSet) {actorSet = newActorSet;}

/*
inputs
	tile block
outputs
	void
addTile adds a new tile to the tile set, maintaining order, and therefore
making sure that all tiles still have a unique ID
*/
void world::addTile(tile block) 
{
	block.changeID(tileSet.size());
	tileSet.push_back(block);
}

/*
inputs
	object block
outputs
	void
addObject adds a new object to the object set, maintaining order, and therefore
making sure that all objects still have a unique ID
*/
void world::addObject(object block) 
{
	block.changeID(objectSet.size());
	objectSet.push_back(block);
}

/*
inputs
	actor character
outputs
	void
addObject adds a new actor to the actor set, maintaining order, and therefore
making sure that all actors still have a unique ID
*/
void world::addActor(actor character)
{
	character.changeID(actorSet.size());
	actorSet.push_back(character);
}

/*

The removal functions are unnecessary at the moment
but I will leave this prototyped incase we end up
adding in a GUI for world building

void world::removeTile(unsigned int ID) 
{
	tileSet.erase(tileSet.begin() + ID);
	for(int i = ID; i < tileSet.size(); i++) tileSet.at(i).changeID(i);
}

void world::removeObject(unsigned int ID) 
{
	objectSet.erase(objectSet.begin() + ID);
	for(int i = ID; i < objectSet.size(); i++) objectSet.at(i).changeID(i);
}

void world::removeActor(unsigned int ID)
{
	actorSet.erase(actorSet.begin() + ID);
	for(int i = ID; i < actorSet.size(); i++) actorSet.at(i).changeID(i);
}
*/

/*
inputs
	tile newTile - This is the new tile to be used in the tile set
	int ID - This is the position that new tile will be stored
This function will overwrite an existing tile in the tile set
*/
void world::swapTile(tile newTile,unsigned int ID)
{
	newTile.changeID(ID);
	if(ID > tileSet.size());
	else tileSet.at(ID) = newTile;
}

/*
inputs
	object newObject - This is the new object to be used in the object set
	int ID - This is the position that new object will be stored
This function will overwrite an existing object in the object set
*/
void world::swapObject(object newObject,unsigned int ID)
{
	newObject.changeID(ID);
	if(ID > objectSet.size());
	else objectSet.at(ID) = newObject;
}

/*
inputs
	object newCharacter - This is the new actor to be used in the actor set
	int ID - This is the position that new actor will be stored
This function will overwrite an existing actor in the object set
*/
void world::swapActor(actor newCharacter,unsigned int ID)
{
	newCharacter.changeID(ID);
	if(ID > actorSet.size());
	else actorSet.at(ID) = newCharacter;
}

//x are the columns and y are the rows
/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
outputs
	integer ID of what ever is located in the tile that the user is checking
This function checks the map in the world and returns the ID of the entity in the
space it is viewing

	*This function needs to have error checking added to make sure that the user 
does not check for spaces that do not exist
*/
int world::checkTileMap(unsigned int pos[2]) 
{
	unsigned int ID;
	//If the map has spaces outside of the range then they are empty tiles
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]) return 0;
	ID = tileLocations[pos[0] + pos[1]*dimensions[0]];
	return ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
outputs
	integer ID of what ever is located in the tile that the user is checking
This function checks the map in the world and returns the ID of the entity in the
space it is viewing

	*This function needs to have error checking added to make sure that the user 
does not check for spaces that do not exist
*/
int world::checkObjectMap(unsigned int pos[2]) 
{
	unsigned int ID;
	//If the map has spaces outside of the range then they are empty tiles
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]) return NULL;
	ID = objectLocations[pos[0] + pos[1]*dimensions[0]];
	return ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
	int ID - This sets the ID of the entity positioned at that position
output
	void
This function sets the position of the entity in the world
*/
void world::setTileLocation(unsigned int pos[2], unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]) return;
	else tileLocations[pos[0] + pos[1]*dimensions[0]] = ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
	int ID - This sets the ID of the entity positioned at that position
output
	void
This function sets the position of the entity in the world
*/
void world::setObjectLocation(unsigned int pos[2], unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1] || objectSet.size() < ID);
	else objectLocations[pos[0] + pos[1]*dimensions[0]] = ID;
}

//getX returns the world's x dimension size
int world::getX(void) {return dimensions[0];}
//getY returns the world's y dimension size
int world::getY(void) {return dimensions[1];}

/*
inputs
	void
outputs
	void
This function prints a complete report of all of the
entities in the world
*/
void world::printLog(void)
{
	cout << "Current world" << endl;
	cout << "Sizes " << dimensions[0] << " " << dimensions[1] << endl << endl;
	for(unsigned int i = 0; i < tileSet.size(); i++) tileSet.at(i).printLog();
	for(unsigned int i = 0; i < objectSet.size(); i++) objectSet.at(i).printLog();
	for(unsigned int i = 0; i < actorSet.size(); i++) actorSet.at(i).printLog();
}

void world::changePlayerStart(unsigned int playerLocation[2]) {playerStartLocation[0] = playerLocation[0], playerStartLocation[1] = playerLocation[1];}
unsigned int* world::getPlayerStart(void) {return playerStartLocation;}
int world::getTileSetSize(void) {return tileSet.size();}
int world::getObjectSetSize(void) {return objectSet.size();}

void world::populateWorld(void)
{
	vector<vector<int>> currentMap = gameFile -> getMap();
	gameFile -> print2dIntVector(currentMap);

	int n = 0;
	//Quick modification this starts at 0, and the top runs down
	//cause the reads in top to bottom and not bottom to top
	//and the -1 is because the array goes from 0 to size -1
	unsigned int mapLocation[2] = {0,currentMap.size()-1};
	for(unsigned int i = 0; i < currentMap.size(); i++)
	{
		for(unsigned int j = 0; j < currentMap.at(0).size(); j++)
		{	
			setTileLocation(mapLocation, currentMap.at(i).at(j));
			mapLocation[0]++;
		}
		//The map reads in from the top to the bottom
		mapLocation[1]--;
		mapLocation[0] = 0;
	}
}


//Created by Ryan for the NPC 
/* (+) NPC idler

        /*
        This for loop makes the NPCs move
        */
//Added by ryan davis 
void world::updateNPCSet(player* currentPlayer, renderer* act)
{
	for(unsigned int i = 0; i < actorSet.size(); i++)
	{
		actorSet.at(i).runAI(this, currentPlayer);
		actorSet.at(i).updateMovement(this, act);
	}
}

void world::updateWorldClock(void)
{
	frameCounter++;
	if(frameCounter > frameStop) frameCounter = 0;
	if((time(0)) > timingFunction -> getTiming()) 
		frameStop = (timingFunction -> getInc()/30) + 1;
	timingFunction -> updateSystem();
}

int world::getFrameStop(void) {return frameStop;}
int world::getFrameCounter(void) {return frameCounter;}

#endif