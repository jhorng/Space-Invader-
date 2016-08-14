#include <stdio.h>
#include <stdlib.h>
#include "FSM.h"
#include "BlockDiagram.h"
#include "linkList.h"
#include "main.h"

int main(void){
  movementShip *pShip = initiateMovementState();
  pShip->moveShipState = START;
  while (1){
    movementShipFSM(pShip);
    transferImageToConsole();
  }
  return 1;
}