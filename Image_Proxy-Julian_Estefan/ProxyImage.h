#pragma once
#include "stdafx.h"

class ProxyImage : public Image
{
private:

	RealImage* realImage;
	int id;
	static int next ;

public:
	ProxyImage();
	~ProxyImage();
	void draw();
};
