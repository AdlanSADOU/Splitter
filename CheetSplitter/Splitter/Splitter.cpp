#include "Splitter.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODOO:
// DONE		Link Statically 
// PARTIALLY	more error checking
// MAYBE	REMOVE DEPENCY ON MSVCP140.dll  (build independently of visual studio or Visual C++ Redistributable for Visual Studio 2015)

///////////////////////////////////////////////////////////////////////////////////////////
////////////							MAIN FUNCTION

std::vector<Sprite> SpriteCoordinates;
std::vector<unsigned char> gPngFile;
std::vector<unsigned char> gOut;

unsigned char* gDImgTempBuffer;


/////////////////////////////////////////////////////

void Start(int argc, char ** argv)
{

	if (argc > 2)
	{
		CoverMessage();

		cout << "Files :" << endl;
		cout << argv[1] << endl;
		cout << argv[2] << endl;
		cout << "\nchecking" << endl;


		try
		{
			if (strstr(argv[1], ".xml"))
			{
				if (argv[1])
					ParseXML(argv[1]);
				if (argv[2])
					LoadImage(argv[2]);
			}
			else if (strstr(argv[2], ".xml"))
			{
				if (argv[2])
					ParseXML(argv[2]);
				if (argv[1])
					LoadImage(argv[1]);
			}
			else
			{
				cout << "no match, files not supported... try with a .png!" << endl;
				system("PAUSE");
			}

			Splitter();
		}
		catch (const std::exception& e1)
		{
			throw e1;
		}
	}
	else if (argc <= 2)
	{
		cout << "---------------------------/!\\--------------------------\n"
			"            IMPORTANT: READ THIS BEFORE USING\n\n"

			"Drag both.png AND.xml files SIMULTANEOUSLY onto this executable.\n"
			"A Sprites output folder will be created IN THE SAME DIRECTORY AS BOTH SOURCE FILES\n"

				"------------------------ --/!\\--------------------------\n\n\n"

			"No files were provided\n\n\n"

			"Please close this program and drag both source files SIMULTANEOUSLY onto this executable,\n"
			"which will automatically launch.it\n\n" << endl;
	}
	else std::cerr << "No files were provided\n"
		"\nPlease close this program and drag both source files SIMULTANEOUSLY onto this executable," << endl;
	
	
}
////////////////////////////////////////////////



	DecIMG DImage;
	std::string mName;
void Splitter()
{
	cout << lodepng_error_text(lodepng::decode(DImage.Image, DImage.Width, DImage.Height, gPngFile)) << endl;
	gDImgTempBuffer = new unsigned char[(DImage.Width*DImage.Height)*4];
	std::copy(std::begin(DImage.Image), std::end(DImage.Image), gDImgTempBuffer);

	//Sprite sprite = GetSprite("TILE00614.png");
	
	int i=0;

	cout << "\n\nChoose an option\n";
	cout << "-------------------------------------------------------";
	cout << "\n1 > Extract all " << SpriteCoordinates.size() << " sprites." << endl;
	cout << "2 > Extract one specific sprite by name. (ex: ICON00270.png)" << endl;

	printf("\nYour choice: ");
	std::cin >> i;
	switch (i)
	{
	case 1:
		SaveAllSprites();
		break;
	case 2:
		AskSpriteName();
		break;
	default:
		break;
	}
}

LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
LARGE_INTEGER Frequency;

void SaveAllSprites()
{
	cout << "\nPLEASE PROVIDE A FOLDER NAME(avoid spaces) AND HIT ENTER.\nThe named folder will be created under the same directory as the source files and will be the output folder.\n\n";

	char mOutputFolder[50] = "a";
	printf("Folder name: ");
	std::cin >> mOutputFolder;
	_mkdir(mOutputFolder);
	std::strncat(mOutputFolder, "/", 1);
	cout << "Created " << mOutputFolder << " folder in the same directory as the source files\n\n" << "\nBegin decoding at " << mOutputFolder << "\n" << endl;
	system("PAUSE");

	

	for (size_t k = 0; k < SpriteCoordinates.size(); k++)
	{


		std::string mImageName = SpriteCoordinates.at(k).name;
		int mDestWidth = SpriteCoordinates.at(k).width;
		int mDestHeight = SpriteCoordinates.at(k).height;
		int x = SpriteCoordinates.at(k).x;
		int y = SpriteCoordinates.at(k).y;


		cout << mImageName << " " << mDestHeight << " " << mDestWidth << " " << x << " " << y << endl;

		unsigned char* mOutSpriteBuffer = new unsigned char[mDestWidth*mDestHeight * 4];


		for (size_t i = 0; i < mDestHeight; i++)
			for (size_t j = 0; j < mDestWidth; j++)
				*(unsigned long *)&mOutSpriteBuffer[(j + i * mDestWidth) * 4] = *(unsigned long *)&gDImgTempBuffer[((x + j) + (y + i)* DImage.Width) * 4];


		lodepng::encode(gOut, mOutSpriteBuffer, mDestWidth, mDestHeight);


		//TODO:   CHECK IF FOLDER EXISTS !!!
		lodepng::save_file(gOut, mOutputFolder + mImageName);
		cout << "Saved at " << mOutputFolder + mImageName << endl << endl;


		gOut.clear();
		free(mOutSpriteBuffer);

		
	}

}


///////////////////////////////////////////////////////////////
///// OPTIMIZATION ATEMPT
/////               |cycles
///// 32bit 1st Pass 93 438
///// 64bit 1st Pass 108 931
///// 64bit 2nd Pass

Sprite GetSprite(std::string mName)
{
	//std::shared_ptr<Sprite> sprite;
	Sprite sprite;
	bool found = false;
#ifdef DEBUG
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
#endif // DEBUG

	for (size_t k = 0; k < SpriteCoordinates.size(); k++)
	{
		SpriteCoordinates.at(k).name;

		if (mName == SpriteCoordinates.at(k).name)
		{
			found = true;

			sprite.name	= SpriteCoordinates.at(k).name;
			sprite.width	= SpriteCoordinates.at(k).width;
			sprite.height	= SpriteCoordinates.at(k).height;
			sprite.x	= SpriteCoordinates.at(k).x;
			sprite.y	= SpriteCoordinates.at(k).y;
			
			//cout << "found " << sprite.name << " !" << endl;

			/*DecIMG DImage;
			cout << lodepng_error_text(lodepng::decode(DImage.Image, DImage.Width, DImage.Height, gPngFile)) << endl;
*/

			gDImgTempBuffer = new unsigned char[(DImage.Width*DImage.Height) * 4];
			std::copy(std::begin(DImage.Image), std::end(DImage.Image), gDImgTempBuffer);

			unsigned char* mOutSpriteBuffer = new unsigned char[sprite.width * sprite.height * 4];

			for (size_t i = 0; i < sprite.height; i++)
				for (size_t j = 0; j < sprite.width; j++)
					*(unsigned long *)&mOutSpriteBuffer[(j + i * sprite.width) * 4] = *(unsigned long *)&gDImgTempBuffer[((sprite.x + j) + (sprite.y + i)* DImage.Width) * 4];

			lodepng::encode(gOut, mOutSpriteBuffer, sprite.width, sprite.height);

			//TODO:   CHECK IF FOLDER EXISTS !!!
			lodepng::save_file(gOut, sprite.name);
			cout << "Saved " << sprite.name << endl << endl;
			

			gOut.clear();
			delete mOutSpriteBuffer;
			
			cout << "\nDone...!" << endl;
			break;
		}
		
	}
#ifdef DEBUG


	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	LONGLONG Tick = ElapsedMicroseconds.QuadPart;
	printf("\n%I64d Cycles: ", Tick);

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	LONGLONG TicksPsecond = ElapsedMicroseconds.QuadPart;
	printf("\n%I64d Cycles/s: ", TicksPsecond);
#endif // DEBUG


	printf("\n\n");
	if(!found)
	{
		cout << "\nNo match. Are you sure about that name ?\n" << endl;
		AskSpriteName();
		
	}
	

	return sprite;
}



std::shared_ptr<std::vector<unsigned char>> LoadImage(const char* mFile)
{
	std::shared_ptr<std::vector<unsigned char>> pngFile;
	lodepng::load_file(gPngFile, mFile);
	if (gPngFile.empty())
	{
		cout << endl << "No files specified, or file not supported\n" << endl;
		return pngFile;
	}
	cout << "Loaded .png file...!" << endl;
	cout << "\n\n";

	return pngFile;
}



void AskSpriteName()
{
	cout << "\nSprite name: ";
	std::cin >> mName;
	GetSprite(mName);
}



void CoverMessage()
{
	//cout << "Author: Adlan Sadou  (Khaldro)\n" << endl;
	cout << "---------------------------/!\\--------------------------" << endl;
	cout << "                READ THIS BEFORE USING\n" << endl;

	cout << "Drag both .png AND .xml files SIMULTANEOUSLY onto this executable.\n";
	cout << "A Sprites output folder will be created \nIN THE SAME DIRECTORY AS BOTH SOURCE FILES\n\n";
	cout << "Individual Sprites are saved under the source files folder\n\n";
	cout << "---------------------------/!\\--------------------------\n\n" << endl;
}



void ParseXML(char* m_XMLfile)
{
	tinyxml2::XMLDocument m_doc;
	//m_doc.LoadFile("Resources/sprites.xml");
	m_doc.LoadFile(m_XMLfile);
	
	tinyxml2::XMLElement* m_rootElement = m_doc.FirstChildElement();
	tinyxml2::XMLElement* m_secondElement = m_rootElement->FirstChildElement();

	for (m_secondElement; m_secondElement!=NULL; m_secondElement = m_secondElement->NextSiblingElement())
	{
		Sprite m_tempSprite;
		
		m_tempSprite.name = m_secondElement->FirstAttribute()->Value();
		m_tempSprite.x = m_secondElement->IntAttribute("x");
		m_tempSprite.y = m_secondElement->IntAttribute("y");
		m_tempSprite.width = m_secondElement->IntAttribute("width");
		m_tempSprite.height = m_secondElement->IntAttribute("height");

		SpriteCoordinates.push_back(m_tempSprite);
	}
	cout << "Loaded .xml file...!" << endl;
}

void LoopPrintSpriteCoordinates()
{
	for (size_t i = 0; i < SpriteCoordinates.size(); i++)
	{
		std::cout << SpriteCoordinates.at(i).name << " "
			<< SpriteCoordinates.at(i).x << " "
			<< SpriteCoordinates.at(i).y << " "
			<< SpriteCoordinates.at(i).width << " "
			<< SpriteCoordinates.at(i).height << " "
			<< std::endl;
	}
	cout << "...All positions and names loaded into memory !" << endl;

}