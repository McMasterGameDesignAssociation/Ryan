/*

_WORLD contains all of the basic data structures that will be used to control
the basic function of the world that the game will be using

the wrapper class world contains 3 sub classes tile, object, actor, which are used
to manage there respective entity type

*/

#ifndef _WORLD
#define _WORLD

#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class player
{
private:
	unsigned int position[2];
	string bitMapName;
	string description;

public:
	player(void);
	unsigned int getPositionX(void);
	unsigned int getPositionY(void);
	string getBitMap(void);
	string getDescription(void);
	void changeDescription(string newDescription);
	void changePosition(unsigned int pos[2]);
	void changeBitMap(string newBitMap);

};

player::player(void)
{
	position[0] = 0, position[1] = 0;
	bitMapName = "None";
	description = "This is an empty player";
}

unsigned int player::getPositionX(void) {return position[0];}
unsigned int player::getPositionY(void) {return position[1];}

string player::getBitMap(void) {return bitMapName;}
string player::getDescription(void) {return description;}
void player::changeDescription(string newDescription) {description = newDescription;}
void player::changePosition(unsigned int pos[2]) {position[0] = pos[0], position[1] = pos[1];}
void player::changeBitMap(string newBitMap) {bitMapName = newBitMap;}

/*
tile is used as the base unit of the world

variables
	unsigned int ID - An ID to track the tile through
			 the system

	bool passThrough - This boolean is used to
			 determine if the tile can be walked
			 over i.e. a pathway, or ones that 
			 can not be walked over i.e. a wall

	string bitMapName - This is the string that
			 will be used to determine the name
			 and the directory of the current
			 texture for the tile.
	string description - This will be used a documenting
						 tool, and will be used in the change logs
*/
class tile
{
private:

	unsigned int ID;
	bool passThrough;
	string bitMapName;
	string description;

public:

	//Modifiers
	tile(void);
	void setTile(bool passable, string bitMap, string newDescription);
	void changeID(unsigned int newID);
	void changePassThrough(bool passable);
	void changeBitMapName(string bitMap);
	void changeDescription(string newDescription);

	//Accessors
	int getID(void);
	bool getPassThrough(void);
	string getBitMapName(void);
	string getDescription(void);

	//Logging functions
	void printLog(void);

};

/*
inputs
	void
outputs
	void

This function sets up an empty tile
*/
tile::tile(void)
{
	ID = 0;
	passThrough = false;
	bitMapName = "None";
	description = "This is an empty tile";
}

/*
inputs
	unsigned int newID - The ID that will replace the
				current ID
	bool passable - This the boolean that 
					determines passThrough
	string bitMap - This sets the new bit map
					directory

setTile is used to completely change an existing tile
*/
void tile::setTile(bool passable, string bitMap, string newDescription)
{
	passThrough = passable;
	bitMapName = bitMap;
	description = newDescription;
}

/*
input
	void
output
	void

printLog is used to print the current
values stored in the tile to the prompt

*/
void tile::printLog(void)
{
	cout << "Current tile: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Pass through: " << passThrough << endl;
	cout << "Bit map name: " << bitMapName << endl << endl;
}

//Please do not use this function it is designed to be private
void tile::changeID(unsigned int newID) {ID = newID;}
void tile::changePassThrough(bool passable) {passThrough = passable;}
void tile::changeBitMapName(string bitMap) {bitMapName = bitMap;}
void tile::changeDescription(string newDescription) {description = newDescription;}
int tile::getID(void) {return ID;}
bool tile::getPassThrough(void) {return passThrough;}
string tile::getBitMapName(void) {return bitMapName;}
string tile::getDescription(void) {return description;}

/*

The object class is used to store the information that is
contained in each object in the world, where objects
are passive but the player can interact with them
i.e. doors, security systems, shelves, etc.
enum
	direction{up, left, down, right] - This is used as a local type
									   to track the direction of an
									   object

variables
	unsigned int ID - ID is used to distinguish each object from each other
	object::direction face - Face determines the direction
							 the front of the object is facing
	bool passThrough - This determines if the player will collide with
					   the current object
	string bitMapName - This determines the directory where every
							  texture for each version of the object's
							  sprite is located
	string description - This will be used to describe the object in the
						 logs
*/

class object
{
	private:
		
		enum direction{up, left, down, right};

		unsigned int ID;
		direction face;
		bool passThrough;
		string bitMapName;
		string description;
	
	public:

		//Modifiers
		object(void);
		void setObject(direction newFace, bool passable, string newBitMapName, string newDescription);
		void changeID(unsigned int newID);
		void changePassThrough(bool passable);
		void changeFace(direction face);
		void changeBitMapName(string newBitMapName);

		//Accessors
		int getID(void);
		direction getFace(void);
		bool getPassThrough(void);
		string getBitMapName(void);
		string getDescription(void);

		//Logging function
		void printLog(void);

};

object::object(void)
{
	ID = 0;
	face = up;
	passThrough = false;
	bitMapName = "None";
	description = "This is an empty object";
}

void object::setObject(direction newFace, bool passable, string newBitMapName, string newDescription)
{
	face = newFace;
	passThrough = passable;
	bitMapName = newBitMapName;
	description = newDescription;
}

void object::printLog(void)
{
	cout << "Current object: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Pass through: " << passThrough << endl;
	cout << "Bit map: " << bitMapName << endl;
	cout << "Face: " << face << endl << endl;
}

//Please do not use this function it is designed to be private
void object::changeID(unsigned int newID) {ID = newID;}
void object::changePassThrough(bool passable){passThrough = passable;}
void object::changeFace(direction newFace){face = newFace;}
void object::changeBitMapName(string newbitMapName) {bitMapName = newbitMapName;}

int object::getID(void) {return ID;}
object::direction object::getFace(void) {return face;}
bool object::getPassThrough(void) {return passThrough;}
string object::getBitMapName(void) {return bitMapName;}

/*
contains
	enum direction - direction will be used to determine the direction 
					 that the actor is facing
	unsigned unsigned int ID - ID provides a unique ID for each actor so 
		    		  they can be tracked through the system
	direction face - face determines the standing direction the actor
					 is facing
	string bitMapName - bitMapName is the current name of the bitMap
						that the actor uses as a costume

The actor class is used to make instances of NPCs to be used in the world
*/
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

	public:

		//Modifiers
		actor(void);
		void setActor(direction newFace, string newBitMapName, string newDescription);
		void changeID(unsigned int newID);
		void changeDirection(direction newFace);
		void changeBitMapName(string newbitMapName);

		//Accessor
		int getID(void);
		direction getFace(void);
		string getBitMapName(void);
		string getDescription(void);

		//Logging function
		void printLog(void);

};

/*
input
	void
output
	void

This function initializes the current actor
*/
actor::actor(void)
{
	ID = 0;
	face = up;
	bitMapName = "None";
	description = "This is an empty character";
}

/*
inputs
	direction newFace - This defines the new direction of an actor
	string newBitMapName - This defines the new bit map file name
	string newDescription - This will set the new description of the
							character
output
	void
This function changes the current actor to the new one specified
*/
void actor::setActor(direction newFace, string newBitMapName, string newDescription)
{
	face = newFace;
	bitMapName = newBitMapName;
	description = newDescription;
}

/*
inputs
	void
output
	void
This function prints the change log for the current actor
*/
void actor::printLog(void)
{
	cout << "Current actor: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Bit map name: " << bitMapName << endl << endl;
}

//This function should be private
void actor::changeID(unsigned int newID) {ID = newID;}
void actor::changeDirection(direction newFace) {face = newFace;}
void actor::changeBitMapName(string newbitMapName) {bitMapName = newbitMapName;}
string actor::getDescription(void) {return description;}
int actor::getID(void) {return ID;}
actor::direction actor::getFace(void) {return face;}
string actor::getBitMapName(void) {return bitMapName;}

/*
contains
	vector<tile> tileSet - This is the set of tiles used in the world
	vector<object> objectSet - This is the set of objects used in the world
	vector<actor> actorSet - This is the set of actors used in the world
	int* tileLocations - This is the locations of all of the current tiles
	int* objectLocations - This is the locations of all of the current objects
	int* actorLocations - This is the locations of all of the current actors
	unsigned int dimensions[2] - This is the current dimensions of the world

world is used to control and maintain all of the in world
game elements
*/
class world
{
	private:

		vector<tile> tileSet;
		vector<object> objectSet;
		vector<actor> actorSet;
		int* tileLocations;
		int* objectLocations;
		int* actorLocations;
		unsigned int dimensions[2];

	public:

		world(unsigned int size[2]);
		void setTiles(vector<tile> newTileSet);
		void setObjects(vector<object> newObjectSet);
		void setActor(vector<actor> newActorSet);
		void changeDimension(unsigned int size[2]);
		void addTile(tile block);
		void addObject(object block);
		void addActor(actor character);
		void removeTile(unsigned int ID);
		void removeObject(unsigned int ID);
		void removeActor(unsigned int ID);
		void getLog(void);
		void setTileLocation(unsigned int pos[2], unsigned int ID);
		void setObjectLocation(unsigned int pos[2], unsigned int ID);
		void setActorLocation(unsigned int pos[2], unsigned int ID);
		void swapTile(tile newTile, int ID);
		void swapObject(object newObject, int ID);
		void swapActor(actor newCharacter, int ID);

		void printLog(void);
		
		tile getTile(unsigned int ID);
		object getObject(unsigned int ID);
		actor getCharacter(unsigned int ID);
		vector<tile> getTileSet(void);
		vector<object> getObjectSet(void);
		vector<actor> getActorSet(void);

		bool getTileCollision(unsigned int ID);
		bool getObjectCollision(unsigned int ID);

		void changeTilePassthrough(unsigned int ID, bool passable);
		void changeObjectPassthrough(unsigned int ID, bool passable);
		
		int checkTileMap(unsigned int pos[2]);
		int checkObjectMap(unsigned int pos[2]);
		int checkActorMap(unsigned int pos[2]);

		int getX(void);
		int getY(void);


};


/*
inputs
	unsigned int size[2] - This is the size of the world you are building
						   specifying the x and y values respectively
outputs void
This function clears all of the arrays and sets, and then builds a map
that contains only empty tiles, objects, and actors
*/
world::world(unsigned int size[2])
{
	tileSet.clear();
	objectSet.clear();
	actorSet.clear();
	
	delete[] tileLocations;
	delete[] objectLocations;
	delete[] actorLocations;

	dimensions[0] = unsigned int(size[0]);
	dimensions[1] = unsigned int(size[1]);

	tileLocations = new int[size[0]*size[1]];
	objectLocations = new int[size[0]*size[1]];
	actorLocations = new int[size[0]*size[1]];
	
	tile block;
	addTile(block);
	
	object objectBlock;
	addObject(objectBlock);

	actor character;
	addActor(character);
	unsigned int temp[2];
	
	for(int i = 0; i < dimensions[0]; i++)
	{
		for(int j =0; j < dimensions[1]; j++) 
		{
			temp[0] = i, temp[1] = j;
			setTileLocation(temp, 0);
			setObjectLocation(temp, 0);
			setActorLocation(temp, 0);
		}
	}
}

tile world::getTile(unsigned int ID) {return tileSet.at(ID);}
object world::getObject(unsigned int ID) {return objectSet.at(ID);}
actor world::getCharacter(unsigned int ID) {return actorSet.at(ID);}
vector<tile> world::getTileSet(void) {return tileSet;}
vector<object> world::getObjectSet(void) {return objectSet;}
vector<actor> world::getActorSet(void) {return actorSet;}
bool world::getTileCollision(unsigned int ID) {return tileSet.at(ID).getPassThrough();}
bool world::getObjectCollision(unsigned int ID) {return objectSet.at(ID).getPassThrough();}

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
	for(int i = 0; i < dimensions[0]; i++)
	{
		for(int j =0; j < dimensions[1]; j++) 
		{
			temp[0] = i, temp[1] = j;
			setTileLocation(temp, 0);
			setObjectLocation(temp, 0);
			setActorLocation(temp, 0);
		}
	}
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
void world::swapTile(tile newTile, int ID)
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
void world::swapObject(object newObject, int ID)
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
void world::swapActor(actor newCharacter, int ID)
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
outputs
	integer ID of what ever is located in the tile that the user is checking
This function checks the map in the world and returns the ID of the entity in the
space it is viewing

	*This function needs to have error checking added to make sure that the user 
does not check for spaces that do not exist
*/
int world::checkActorMap(unsigned int pos[2])
{
	unsigned int ID;
	//If the map has spaces outside of the range then they are empty tiles
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]) return NULL;
	ID = actorLocations[pos[0] + pos[1]*dimensions[0]];
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
void world::setTileLocation(unsigned int pos[2], unsigned unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]);
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
void world::setObjectLocation(unsigned int pos[2], unsigned unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1] || objectSet.size() < ID);
	else objectLocations[pos[0] + pos[1]*dimensions[0]] = ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
	int ID - This sets the ID of the entity positioned at that position
output
	void
This function sets the position of the entity in the world
*/
void world::setActorLocation(unsigned int pos[2], unsigned unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1] || actorSet.size() < ID);
	else actorLocations[pos[0] + pos[1]*dimensions[0]] = ID;
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
	for(int i = 0; i < tileSet.size(); i++) tileSet.at(i).printLog();
	for(int i = 0; i < objectSet.size(); i++) objectSet.at(i).printLog();
	for(int i = 0; i < actorSet.size(); i++) actorSet.at(i).printLog();
}

#endif // !_WORLD