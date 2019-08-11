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
#include <cassert>

using std::cout;
using std::endl;

struct DecIMG
{
	std::vector<unsigned char> Image;
	unsigned Width = 0;
	unsigned Height = 0;
};

struct Sprite
{
	std::string name;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};

void CoverMessage();
void ParseXML(char* m_XMLfile);
void LoopPrintSpriteCoordinates();
std::shared_ptr<std::vector<unsigned char>> LoadImage(const char* mFile);
Sprite GetSprite(std::string mName);
void Splitter();
void Start(int argc, char ** argv);
char* CreateFolder();
void SaveAllSprites();



#endif
