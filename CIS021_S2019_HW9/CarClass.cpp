// Project: CIS021_S2019_HW9
// Module:	CarClass.cpp 
// Author:	Evan Mayhew
// Date:	5/19/2019
// Purpose:	Implementation file for CarClass
//			

#include "stdafx.h"
#include "CarClass.h"



CarClass::CarClass()
{

	// car size (depends on direction car is facing)
	rDimT.left = 10;
	rDimT.right = rDimT.left + 20;
	rDimT.top = 10;
	rDimT.bottom = rDimT.top + 50;


	rDimR.left = 10;
	rDimR.right = rDimR.left + 20;
	rDimR.top = 10;
	rDimR.bottom = rDimR.top + 50;

	rDimB.left = 10;
	rDimB.right = rDimB.left + 20;
	rDimB.top = 10;
	rDimB.bottom = rDimB.top + 50;

	rDimL.left = 10;
	rDimL.right = rDimL.left + 20;
	rDimL.top = 10;
	rDimL.bottom = rDimL.top + 50;


	// pick a color
	r = GetRandomInt(0, 255);						// red
	g = GetRandomInt(0, 255);						// green
	b = GetRandomInt(0, 255);						// blue


}


CarClass::~CarClass()
{
}

CarClass::CarClass(HWND hWnd, int Test)
{
	// initialize to avoid deletion of incorrect car on move function
	rDimT.bottom = 0;
	rDimT.left = 0;
	rDimT.right = 0;
	rDimT.top = 0;

	rDimR.left = INT_MAX;			// initialize so delete never occurs where not appropriate
	rDimR.bottom = 0;
	rDimR.right = 0;
	rDimR.top = 0;

	rDimB.top = INT_MAX;			// initialize so delete never occurs where not appropriate
	rDimB.left = 0;
	rDimB.right = 0;
	rDimB.bottom = 0;

	rDimL.right = 0;
	rDimL.left = 0;
	rDimL.bottom = 0;
	rDimL.top = 0;

	// car size (depends on direction car is facing)
	if (Test == 1)
	{
		rDimT.left = 405;
		rDimT.right = rDimT.left + 20;
		rDimT.top = 100;
		rDimT.bottom = rDimT.top + 50;
		
	}
	else if (Test == 2)
	{
		rDimR.left = 710;
		rDimR.right = rDimR.left + 50;
		rDimR.top = 305;
		rDimR.bottom = rDimR.top + 20;
	}
	else if (Test == 3)
	{
		rDimB.left = 435;
		rDimB.right = rDimB.left + 20;
		rDimB.top = 510;
		rDimB.bottom = rDimB.top + 50;
	}
	else if (Test == 4)
	{
		rDimL.left = 100;
		rDimL.right = rDimL.left + 50;
		rDimL.top = 335;
		rDimL.bottom = rDimL.top + 20;
	}


	// pick a color
	r = GetRandomInt(0, 255);						// red
	g = GetRandomInt(0, 255);						// green
	b = GetRandomInt(0, 255);						// blue
}

bool CarClass::Move(HWND hWnd, int iDirection, string strLight[4], const vector<CarClass>& vList)
{
	// get window rect
	RECT rClient;
	GetClientRect(hWnd, &rClient);

	if (rDimT.bottom > 560)				// delete if past boundary
		return false;
	if (rDimR.left < 110)
		return false;
	 if (rDimB.top < 100)
		return false;
	 if (rDimL.right > 760)
		return false;


	 // a lot of hard coding and initialization so that the values don't change unless the car was created
	 // if coordinate != initialized hardcoded coordinate, then don't change the car's position
	 // practically, if car isn't drawn, don't modify it

	 // set appropriate bools for each case, and then one compound if statement for whether the car should move
	 bool bIntersection = true;
	 bool bGreen = true;
	 bool bCollide = false;
	 bool bPastIntersection = false;
	 bool bLaneCollision = false;
	 if (rDimT.bottom != 0)
	 {
		 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
		 {
			 if (rDimT.top == vList.at(i).rDimT.top)
				 break;
			 if (rDimT.bottom + 5 >= vList.at(i).rDimT.top && vList.at(i).rDimT.top != 0)
			 {
				 int test = vList.at(i).rDimT.top;
				 bLaneCollision = true;
				 break;
			 }

		 }

		 if (rDimT.bottom + 10 >= 300)
			 bIntersection = false;

		 if (rDimT.bottom + 10 >= 310)
			 bPastIntersection = true;

		 if (strLight[2] == "RED" || strLight[2] == "YELLOW")
			 bGreen = false;


		 if (!bIntersection)
		 {
			 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			 {
				 if (((vList.at(i).rDimL.right + 1 >= 400) &&
					 (vList.at(i).rDimL.left + 1 <= 460)) ||
					 (vList.at(i).rDimR.left - 1 <= 460) &&
					 (vList.at(i).rDimR.right - 1 >= 400)) 
				 {
					 bCollide = true;
					 break;
				 }
			 }
		 }

		 if ((bIntersection && !bLaneCollision) || (bGreen && !bCollide && !bLaneCollision) || bPastIntersection)
		 {
			 rDimT.top += 1;
			 rDimT.bottom += 1;
		 }
	 }

	 ////////////////////////////////////////////////
	 bIntersection = true;
	 bGreen = true;
	 bCollide = false;
	 bPastIntersection = false;
	 bLaneCollision = false;

		 if (rDimR.left != 101)
		 {

			 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			 {
				 if (rDimR.left == vList.at(i).rDimR.left)
					 break;
				 if (rDimR.left - 5 <= vList.at(i).rDimR.right && vList.at(i).rDimR.right != 760)
				 {
					 int test = vList.at(i).rDimR.right;
					 bLaneCollision = true;
					 break;
				 }

			 }

			 if (rDimR.left - 10 <= 460)
				 bIntersection = false;

			 if (rDimR.left - 10 <= 450)
				 bPastIntersection = true;

			 if (strLight[1] == "RED" || strLight[1] == "YELLOW")
				 bGreen = false;


			 if (!bIntersection)
			 {
				 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
				 {
					 if (((vList.at(i).rDimT.bottom + 1 >= 300) &&
						 (vList.at(i).rDimT.top + 1 <= 360)) ||
						 (vList.at(i).rDimB.bottom - 1 >= 300) &&
						 (vList.at(i).rDimB.top - 1 <= 360))
					 {
						 bCollide = true;
						 break;
					 }
				 }
			 }

			 if ((bIntersection && !bLaneCollision) || (bGreen && !bCollide && !bLaneCollision) || bPastIntersection)
			 {
				 rDimR.left -= 1;
				 rDimR.right -= 1;
			 }
		 }

		//////////////////////////////////////
		 
		 bIntersection = true;
		 bGreen = true;
		 bCollide = false;
		 bPastIntersection = false;
		 bLaneCollision = false;
		 if (rDimB.bottom != 101)
		 {
			 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			 {
				 if (rDimB.top == vList.at(i).rDimB.top)
					 break;
				 if (rDimB.top - 5 <= vList.at(i).rDimB.bottom && vList.at(i).rDimB.bottom != INT_MAX)
				 {
					 int test = vList.at(i).rDimB.top;
					 bLaneCollision = true;
					 break;
				 }

			 }

			 if (rDimB.top - 10 <= 360)
				 bIntersection = false;

			 if (rDimB.top - 10 <= 350)
				 bPastIntersection = true;

			 if (strLight[3] == "RED" ||  strLight[3] == "YELLOW")
				 bGreen = false;


			 if (!bIntersection)
			 {
				 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
				 {
					 if (((vList.at(i).rDimL.right + 1 >= 400) &&
						 (vList.at(i).rDimL.left + 1 <= 460)) ||
						 (vList.at(i).rDimR.left - 1 <= 460) &&
						 (vList.at(i).rDimR.right - 1 >= 400))
					 {
						 bCollide = true;
						 break;
					 }
				 }
			 }

			 if ((bIntersection && !bLaneCollision) || (bGreen && !bCollide && !bLaneCollision) || bPastIntersection)
			 {
				 rDimB.top -= 1;
				 rDimB.bottom -= 1;
			 }
		 }

		 //////////////////////////////////////////////////////

		 bIntersection = true;
		 bGreen = true;
		 bCollide = false;
		 bPastIntersection = false;
		 bLaneCollision = false;

		 if (rDimL.left != 0)
		 {

			 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			 {
				 if (rDimL.left == vList.at(i).rDimL.left)
					 break;
				 if (rDimL.right + 5 >= vList.at(i).rDimL.left && vList.at(i).rDimL.left != 0)
				 {
					 int test = vList.at(i).rDimL.left;
					 bLaneCollision = true;
					 break;
				 }

			 }

			 if (rDimL.right + 10 >= 400)
				 bIntersection = false;

			 if (rDimL.right + 10 >= 410)
				 bPastIntersection = true;

			 if (strLight[0] == "RED" || strLight[0] == "YELLOW")
				 bGreen = false;


			 if (!bIntersection)
			 {
				 for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
				 {
					 if (((vList.at(i).rDimT.bottom + 1 >= 300) &&
						 (vList.at(i).rDimT.top + 1 <= 360)) ||
						 (vList.at(i).rDimB.bottom - 1 >= 300) &&
						 (vList.at(i).rDimB.top - 1 <= 360))
					 {
						 bCollide = true;
						 break;
					 }
				 }
			 }

			 if ((bIntersection && !bLaneCollision) || (bGreen && !bCollide && !bLaneCollision) || bPastIntersection)
			 {
				 rDimL.left += 1;
				 rDimL.right += 1;
			 }
		 }

 
	return true;
}

void CarClass::Draw(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);



	FillRect(hdc, &rDimT, brush);

	FillRect(hdc, &rDimR, brush);

	FillRect(hdc, &rDimB, brush);

	FillRect(hdc, &rDimL, brush);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

}



bool CarClass::IntersectionT(vector<CarClass>)
{
	if (rDimT.top > 150)
	{
		return false;
	}
	return true;
}

bool CarClass::IntersectionR(vector<CarClass>)
{
	if (rDimR.right < 710)
	{
		return false;
	}
	return true;
}
bool CarClass::IntersectionB(vector<CarClass>)
{
	if (rDimB.bottom < 510)
	{
		return false;
	}
	return true;
}
bool CarClass::IntersectionL(vector<CarClass>)
{
	if (rDimL.left > 150)
	{
		return false;
	}
	return true;
}

RECT CarClass::GetrDimT() const
{
	return rDimT;
}

RECT CarClass::GetrDimR() const
{
	return rDimR;
}

RECT CarClass::GetrDimB() const
{
	return rDimB;
}

RECT CarClass::GetrDimL() const
{
	return rDimL;
}

//int CarClass::ReturnDimension()
//{
//	rDimCopy = rDimT;
//	return rDimCopy.top;
//}


int CarClass::GetRandomInt(int iMin, int iMax)
{
	random_device rd;								// non-deterministic generator
	mt19937 gen(rd());								// to seed mersenne twister.
	uniform_int_distribution<> dist(iMin, iMax);	// distribute results inside center rect

	return dist(gen);								// return random # between iMin and iMax
}