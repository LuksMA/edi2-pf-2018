#include "stdafx.h"
#include "RealImage.h"


RealImage::RealImage(int i){
	id = i;
	std::cout << "Created: " << id << '\n';
}

void RealImage::draw(){
	std::cout << "   drawing image: " << id << '\n';
}