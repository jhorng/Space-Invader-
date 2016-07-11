#include <stdlib.h>
#include <stdio.h>
#include "FSM.h"

keyboardPressed *initiateKeyboardState(){
  keyboardPressed *thisKey = malloc(sizeof(keyboardPressed));
  thisKey->buttonState = BUTTONNOHIT;
  thisKey->direction = 0;
  return thisKey;
}

movementShip *initiateMovementState(){
  movementShip *this = malloc(sizeof(movementShip));
  this->state = START;
  this->keyboard = initiateKeyboardState();
  this->coordinateX = 0;
  this->coordinateY = 0;
  this->kbPressed = 0;
  return this;
}

void keyboardFSM(keyboardPressed *thisKey){
  int ch;
  
  switch(thisKey->buttonState){
    case BUTTONNOHIT:
      thisKey->direction = thisKey->direction;
      thisKey->buttonState = BUTTONHIT;
      break;
    case BUTTONHIT:
      ch = getch();
      if (ch == 0 || ch == 224 ) {
        ch = getch();
        thisKey->direction = ch;
      }
      break;
    default: thisKey->buttonState = BUTTONNOHIT;
  }
}

void movementShipFSM(movementShip *thisMove){
  volatile int ch;
  keyboardPressed *thisKey;
  switch (thisMove->state) {
    case START:
      thisMove->coordinateX = 24;
      thisMove->coordinateY = 47;
      thisMove->state = RELEASE;
      break;
    case RELEASE:
      // if (thisMove->kbPressed = kbhit()) {
      if (getKbPressed(thisMove->kbPressed) == BUTTON_PRESSED) {
        thisMove->keyboard->buttonState = BUTTONHIT;
        keyboardFSM(thisMove->keyboard);
        thisMove->state = PRESSED;
      }
      else {
        thisMove->keyboard->buttonState = BUTTONNOHIT;
        keyboardFSM(thisMove->keyboard);
        thisMove->state = RELEASE;
      }
      break;
    case PRESSED:
      if (getKbCodeLeft(thisMove->keyboard->direction) == KEY_LEFT){
        thisMove->coordinateX = thisMove->coordinateX - 1;
        thisMove->coordinateY = thisMove->coordinateY;
      }
      else if (getKbCodeRight(thisMove->keyboard->direction) == KEY_RIGHT){
        thisMove->coordinateX = thisMove->coordinateX + 1;
        thisMove->coordinateY = thisMove->coordinateY;
      }
      else{
        thisMove->coordinateX = thisMove->coordinateX;
        thisMove->coordinateY = thisMove->coordinateY;
      }
      thisMove->state = RELEASE;
      break;
    default: thisMove->state = START;
  }
}

void moveShip(char *image, int x, int y){
  movementShip *coord = malloc(sizeof(movementShip));
  coord->coordinateX = x;
  coord->coordinateY = y;
  printf ("x = %d, y = %d\n", coord->coordinateX, coord->coordinateY);
}

int moveShipRelative(char *image, int deltaX, int deltaY){
  int newCoorX, newCoorY;
  movementShip *coord;
  printf ("coorX = %d, coorY = %d\n", coord->coordinateX, coord->coordinateY);
  newCoorX = coord->coordinateX + deltaX;
  newCoorY = coord->coordinateY + deltaY;
  
  if (newCoorX > 47){
    newCoorX = 47;
    moveShip(image, newCoorX, newCoorY);
  }
  
   else if (newCoorX <= 0){
   newCoorX = 0;
   moveShip(image, newCoorX, newCoorY);}
  
  else if (newCoorY >= 47){
   newCoorY = 47;
   moveShip(image, newCoorX, newCoorY);
  }
  
  else if (newCoorY <= 0){
   newCoorY = 0;
   moveShip(image, newCoorX, newCoorY);
   }
  
  else{
    newCoorX = newCoorX;
    newCoorY = newCoorY;
    moveShip(image, newCoorX, newCoorY);
  }
  
} 
