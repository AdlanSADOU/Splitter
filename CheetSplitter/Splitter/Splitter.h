#pragma once
#ifndef __SPLITTER_H
#define __SPLITTER_H

#include "tinyxml2.h"
#include "lodepng.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <direct.h>

using std::cout;
using std::endl;

void ParseXML(char* m_XMLfile);
void LoopPrintSpriteCoordinates();
void Splitter(char* file);
void ProcessFileArguments(char ** argv);
char* CreateFolder();

std::vector<unsigned char> gPngFile;
std::vector<unsigned char> gDecodedImage;
std::vector<unsigned char> gOut;

unsigned gDecodedImageWidth = 0;
unsigned gDecodedImageHeight = 0;

unsigned char* gOutBuffer;

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
