// Project: CIS021_S2019_HW9
// Module:	CarClass.h 
// Author:	Evan Mayhew
// Date:	5/19/2019
// Purpose:	Header file for CarClass.h
//			


#pragma once

// structure to hold speed
struct dPOINT
{
	double x;
	double y;
};



class CarClass
{
public:
	CarClass();
	~CarClass();
	CarClass(HWND, int);				// initialize
	bool Move(HWND, int, string[4], const vector<CarClass>&);
	void Draw(HDC);							// draw the car
	bool IntersectionT(vector<CarClass>);
	bool IntersectionR(vector<CarClass>);
	bool IntersectionB(vector<CarClass>);
	bool IntersectionL(vector<CarClass>);
	RECT GetrDimT()const;					// accessors to look at cars in main module
	RECT GetrDimR()const;
	RECT GetrDimB()const;
	RECT GetrDimL()const;

private:
	RECT rDimT;								// location and size rect, one for each respective car
	RECT rDimR;								// location and size rect
	RECT rDimB;								// location and size rect
	RECT rDimL;								// location and size rect

	RECT rDimCopy;							// copy for collision testing
	enum CAR_DIRECTION { NORTH, EAST, SOUTH, WEST };
	LightsClass* Light[4];
	int r, g, b;							// color
	dPOINT dSpeed;


	int GetRandomInt(int, int);				// return random integer
};

