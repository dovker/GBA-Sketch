#include "Input.h"

uint INPUT_DATA;

void InputPoll()
{
  INPUT_DATA = INPUT_MASK | INPUT_MEMORY;
}
uint GetKeyDown(uint key)
{
  return !(INPUT_DATA & key);
}