#include "pch.h"
#include "Splitter.h"
// TODOO:
// Link Statically
// more error checking
// REMOVE DEPENCY ON MSVCP140.dll  (build independently of visual studio or Visual C++ Redistributable for Visual Studio 2015)
////////////////////////////////////////////////////////////////
////////////					MAIN FUNCTION
int main(int argc, char* argv[])
{
	char a;
	cout << "---------------------------/!\\--------------------------" << endl;
	cout << "IMPORTANT: READ THIS BEFORE USING\n" << endl;

	cout << "Drag both .png AND .xml files onto the executable SIMULTANEOUSLY.\n" 
	     << "A Sprites ouput folder will be created IN THE SAME DIRECTORY AS BOTH SOURCE FILES\n\n";
	cout << "---------------------------/!\\--------------------------\n" << endl;

	

	if (argc > 1)
	{
		cout <<" was provided file path: " << argv[1] << endl;
		cout <<" was provided file path: " << argv[2] << endl << endl;

			cout << "checking\n" << endl;
		
			try
			{
				if (strstr(argv[1], ".xml"))
				{
					if (argv[1])
						ParseXML(argv[1]);
					if (argv[2])
						Decode(argv[2]);
				}
				else if (strstr(argv[2], ".xml"))
				{
					if (argv[2])
						ParseXML(argv[2]);
					if (argv[1])
						Decode(argv[1]);
				}
				else
				{
					cout << "no math, file not supported... try with a .png!";
					system("PAUSE");
				}
			}
			catch (const std::exception& e1)
			{
				throw e1;
			}
	}
	else std::cerr << "No files were provided\n\nPlease close this program and drag both source files onto this executable SIMULTANEOUSLY,\nwhich will automatically launcg it\n" << endl;



	//LoadImage()
	//DecodeImage()
	//CutImage()
	//SaveImage();

	
	//LoopPrintSpriteCoordinates();
	
	system("PAUSE");
	
	return 0;
}
////////////////////////////////////////////////


std::vector<unsigned char> Decode(char* file)
{
	std::vector<unsigned char> mPngFile;
	std::vector<unsigned char> mDecodedImage;
	std::vector<unsigned char> mOut;

	
	unsigned mWidth = 0;
	unsigned mHeight = 0;

	system("DIR");

	//lodepng::load_file(mPngFile, "Resources/sprites.png");
	lodepng::load_file(mPngFile, file);
	if (mPngFile.empty())
	{
		cout << "No files specified, or file not supported\n" << endl;
		return std::vector<unsigned char>();
	}
	cout << "\n\n";
	cout << lodepng_error_text(lodepng::decode(mDecodedImage, mWidth, mHeight, mPngFile)) << endl;
	//cout << lodepng_error_text(lodepng::decompress(mOut, mDecodedImage)) << endl;      // NO NEED TO DECOMPRESS

	
	size_t mDecodedImageSize = mDecodedImage.size();
	unsigned char* mybuf = new unsigned char[(mWidth*mHeight)*4];
	std::copy(std::begin(mDecodedImage), std::end(mDecodedImage), mybuf);

	/*int mDestWidth = 2048;
	int mDestHeight = 2048;
	int x = 0;
	int y = 0;*/

	cout << "\nPLEASE PROVIDE A FOLDER NAME(avoid spaces) AND HIT ENTER.\nThe named folder will be created under the same directory as the source files and will be the output folder.\n\n";

	char mOutputFolder[50] = "d";
	//char mkdir[50] = "mkdir ";
	printf("folder name: ");
	std::cin >> mOutputFolder;
	//std::strncat(mkdir, mOutputFolder, 10);

	//system(mkdir);
	_mkdir(mOutputFolder);
	std::strncat(mOutputFolder, "/", 1);

	cout << "Created "<< mOutputFolder <<" folder in the same directory as the source files\n\n" << endl;
	system("PAUSE");
	cout << "Begin decoding at " << mOutputFolder<< "\n"<<endl;
	system("PAUSE");
	for (size_t k = 0; k < SpriteCoordinates.size(); k++)
	{

		std::string mImageName	= SpriteCoordinates.at(k).name;
		int mDestWidth		= SpriteCoordinates.at(k).width;
		int mDestHeight		= SpriteCoordinates.at(k).height;
		int x			= SpriteCoordinates.at(k).x;
		int y			= SpriteCoordinates.at(k).y;

		unsigned char* mTestBuf = new unsigned char[mDestWidth*mDestHeight * 4];

		for (size_t i = 0; i < mDestHeight; i++)
		{

			for (size_t j = 0; j < mDestWidth; j++)
			{
				*(unsigned long *)&mTestBuf[(j + i * mDestWidth) * 4] = *(unsigned long *)&mybuf[((x + j) + (y + i)*mWidth) * 4];
			}

		}

			lodepng::encode(mOut, mTestBuf, mDestWidth, mDestHeight);

			lodepng::save_file(mOut, mOutputFolder + mImageName);
			cout << "Saved at " << mOutputFolder + mImageName<< endl<<endl;
			system("PAUSE");
			
			mOut.clear();
			free(mTestBuf);

		//size_t mMybufSize = sizeof() / sizeof(mybuf[0]);
		/*for (size_t i = 0; i < 9223372036; i++)
		{
			std::cout << mybuf[i];
		}*/
	}
	return mDecodedImage;
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
	cout << "...All positions and names Loaded into memory !" << endl;

}