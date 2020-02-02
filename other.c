#include "definition.h"

//get a random number between min and max
int Random(int min, int max)
{
  return (min + (rand () % (max-min+1)));
}

