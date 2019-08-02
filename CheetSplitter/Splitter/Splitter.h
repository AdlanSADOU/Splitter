#pragma once
#ifndef __SPLITTER_H
#define __SPLITTER_H

#include "tinyxml2.h"
#include "lodepng.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

void ParseXML();
void LoopPrintSpriteCoordinates();

std::vector<unsigned char> Decode();

struct Sprite
{
	std::string name;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};

std::vector<Sprite> SpriteCoordinates;

#endif
