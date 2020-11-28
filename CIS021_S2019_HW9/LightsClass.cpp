// Project: CIS021_S2019_HW9
// Module:	LightsClass.cpp 
// Author:	Evan Mayhew
// Date:	5/19/2019
// Purpose:	Implementation file for LightsClass
//			

#include "stdafx.h"
#include "LightsClass.h"


LightsClass::LightsClass()
{
}

LightsClass::LightsClass(int iLight)
{
	switch (iLight)
	{
	case 0:
	{
		rDim = { 300, 380, 380, 410 };				// rectangle
		rBulb[0] = { 305, 385, 325, 405 };			// green light
		rBulb[1] = { 330, 385, 350, 405 };			// yellow light
		rBulb[2] = { 355, 385, 375, 405 };			// red light
		state = GREEN;
	}
	break;

	case 1:
	{
		rDim = { 480, 250, 560, 280 };
		rBulb[0] = { 535, 255, 555, 275 };			// green light
		rBulb[1] = { 510, 255, 530, 275 };			// yellow light
		rBulb[2] = { 485, 255, 505, 275 };			// red light
		state = GREEN;
	}
	break;

	case 2:
	{
		rDim = { 350, 200, 380, 280 };
		rBulb[2] = { 355, 255, 375, 275 };			// green light
		rBulb[1] = { 355, 230, 375, 250 };			// yellow light
		rBulb[0] = { 355, 205, 375, 225 };			// red light
		state = RED;

	}
	break;

	case 3:
	{
		rDim = { 480, 380, 510, 460 };
		rBulb[2] = { 485, 385, 505, 405 };			// green light
		rBulb[1] = { 485, 410, 505, 430 };			// yellow light
		rBulb[0] = { 485, 435, 505, 455 };			// red light
		state = RED;

	}
	break;

	default:
	{
		rDim = { 50, 50, 80, 110 };
		state = YELLOW;
		iTiming = 0;
	}
	break;

	}

	iTiming = 9;									// ready for green lights to turn yellow

}


LightsClass::~LightsClass()
{
}

void LightsClass::Draw(HDC hdc)
{
	HPEN penThick = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); ;
	HPEN penThin = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); ;
	HBRUSH brushGreen = CreateSolidBrush(RGB(0x00, 0xFF, 0x00));
	HBRUSH brushYellow = CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
	HBRUSH brushRed = CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
	HBRUSH brushWhite = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));

	HPEN oldPen = (HPEN)SelectObject(hdc, penThick);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brushWhite);

	// outside rectangle
	Rectangle(hdc, rDim.left, rDim.top, rDim.right, rDim.bottom);

	// bulbs
	SelectObject(hdc, penThin);

	switch (state)
	{
	case GREEN:
	{
		SelectObject(hdc, brushGreen);
		Ellipse(hdc, rBulb[0].left, rBulb[0].top, rBulb[0].right, rBulb[0].bottom);
		SelectObject(hdc, brushWhite);
		Ellipse(hdc, rBulb[1].left, rBulb[1].top, rBulb[1].right, rBulb[1].bottom);
		Ellipse(hdc, rBulb[2].left, rBulb[2].top, rBulb[2].right, rBulb[2].bottom);
		break;
	}
	case YELLOW:
	{
		SelectObject(hdc, brushWhite);
		Ellipse(hdc, rBulb[0].left, rBulb[0].top, rBulb[0].right, rBulb[0].bottom);
		SelectObject(hdc, brushYellow);
		Ellipse(hdc, rBulb[1].left, rBulb[1].top, rBulb[1].right, rBulb[1].bottom);
		SelectObject(hdc, brushWhite);
		Ellipse(hdc, rBulb[2].left, rBulb[2].top, rBulb[2].right, rBulb[2].bottom);
		break;
	}
	case RED:
	{
		SelectObject(hdc, brushWhite);
		Ellipse(hdc, rBulb[0].left, rBulb[0].top, rBulb[0].right, rBulb[0].bottom);
		Ellipse(hdc, rBulb[1].left, rBulb[1].top, rBulb[1].right, rBulb[1].bottom);
		SelectObject(hdc, brushRed);
		Ellipse(hdc, rBulb[2].left, rBulb[2].top, rBulb[2].right, rBulb[2].bottom);
		break;
	}
	default:
	{
		SelectObject(hdc, brushWhite);
		for (int i = 0; i < 3; i++)
			Ellipse(hdc, rBulb[i].left, rBulb[i].top, rBulb[i].right, rBulb[i].bottom);
		break;
	}
	}

	// release the line pens
	SelectObject(hdc, oldPen);
	DeleteObject(penThick);
	DeleteObject(penThin);
	// release the brushes
	SelectObject(hdc, oldBrush);
	DeleteObject(brushGreen);
	DeleteObject(brushYellow);
	DeleteObject(brushRed);
	DeleteObject(brushWhite);
}

LIGHT_POS LightsClass::GetState()
{
	return state;
}

void LightsClass::Set()
{
	iTiming++;								// add 1 second to timer

	switch (iTiming)
	{
	case 5 :								// change from yellow to red
		if (state == YELLOW)
		{
			state = RED;
			iTiming = 0;
		}
		break;
	case 10:								// change from green to yellow
		if (state == GREEN)
		{
			state = YELLOW;
			iTiming = 0;
		}
		break;

	case 15:								// change from red to green
		if (state == RED)
		{
			state = GREEN;
			iTiming = 0;
		}
		break;
	}

}
