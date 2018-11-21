#pragma once
#include "stdafx.h"

class RealImage : public Image
{
private:

	int id;

public:

	RealImage(int i);
	~RealImage() {};
	void draw();
};

