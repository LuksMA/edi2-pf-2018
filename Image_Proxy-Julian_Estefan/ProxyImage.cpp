#include "stdafx.h"

ProxyImage::ProxyImage(){
	id = next++;
	realImage = nullptr;
}

ProxyImage::~ProxyImage(){
	delete realImage;
}

int ProxyImage::next = 1;

void ProxyImage::draw(){
	if (!realImage)
		realImage = new RealImage(id);

	realImage->draw();
}