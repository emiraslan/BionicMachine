#ifndef _CHARACTER_H
#define _CHARACTER_H

#ifndef _MOVEMENT_H
	#include "Movement.h"
#endif // !_MOVEMENT_H

class Character 
{
private:
	float maxSpeed;
	float maxKinetic;
	float maxPotential;
	
	float GravityCoef;

	float posX;
	float posY;

	int Health;

	void Gravity();

public:
	Character();
	~Character();

	Movement *movement;
};


#endif // !_CHARACTER_H