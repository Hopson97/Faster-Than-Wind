#include "random.h"

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <random>

namespace random
{


/**
=================================================================================================================================================================
*   random::num() returns a random number between param 1 and param 2
*   param1  :   The lower bound of the random number to be returned
*   param2  :   The upper bound of the random number to be returned
=================================================================================================================================================================
*/
int num(int low, int high)
{
	return (rand() % (high - low + 1) + low);
}

/**
=================================================================================================================================================================
*   random::colour()    returns a RBG random colour
=================================================================================================================================================================
*/
sf::Color colour()
{
    return sf::Color(
                     num(0, 255),
                     num(0, 255),
                     num(0, 255)
                     );
}

}//namespace rand
