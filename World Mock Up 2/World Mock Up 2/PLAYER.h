/*
COPYRIGHT BENJAMIN ISHERWOOD 25/02/2014
THIS SOFTWARE IS INTENDED FOR OPEN SOURCE USE, REDISTRIBUTION
IS ENCOURAGE

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _PLAYER
#define _PLAYER

#include "COLLECTIONS.h"

class player : public entity, public gamepiece, public sprite
{

private:
	int playerResolution;
	bool suspicious;

public:
	player(void);
	player(world* map);
	//Base
	//void followMouse(int pos[2], int worldDim[2]);
	void changeSize(int newSize);
	void checkMovement(world *map, int x, int y);
	int getID(); // added by ryan for pathfinding usage
	//added by ryan davis for suspicion
	bool getSuspicious(void);
	void setSuspicous(bool newSuspicion);
};

#endif