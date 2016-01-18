#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NONSTDC_NO_WARNINGS
#define  _SCL_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "bitmap_image.hpp"
using namespace std;

int n, m; //globals

void subsample()       // subsampler - use if image is too big 
{
	string file_name("image.bmp");
	
	bitmap_image image(file_name);
	bitmap_image subsampled_image1;
	bitmap_image subsampled_image2;
	bitmap_image subsampled_image3;
	bitmap_image subsampled_image4;
	bitmap_image subsampled_image5;

	image.subsample(subsampled_image1);
	subsampled_image1.save_image("1xsubsampled_image.bmp");

	subsampled_image1.subsample(subsampled_image2);
	subsampled_image2.save_image("2xsubsampled_image.bmp");

	subsampled_image2.subsample(subsampled_image3);
	subsampled_image3.save_image("3xsubsampled_image.bmp");

	subsampled_image3.subsample(subsampled_image4);
	subsampled_image4.save_image("4xsubsampled_image.bmp");

	subsampled_image4.subsample(subsampled_image5);
	subsampled_image5.save_image("5xsubsampled_image.bmp");

}

void upsample() // upsampler - if image is too small *not usual*
{
	string file_name("image.bmp");

	bitmap_image image(file_name);
	bitmap_image upsampled_image1;
	bitmap_image upsampled_image2;
	bitmap_image upsampled_image3;
	bitmap_image upsampled_image4;
	bitmap_image upsampled_image5;

	image.upsample(upsampled_image1);
	upsampled_image1.save_image("1xupsampled_image.bmp");

	upsampled_image1.upsample(upsampled_image2);
	upsampled_image2.save_image("2xupsampled_image.bmp");

	upsampled_image2.upsample(upsampled_image3);
	upsampled_image3.save_image("3xupsampled_image.bmp");

	upsampled_image3.upsample(upsampled_image4);
	upsampled_image4.save_image("4xupsampled_image.bmp");

	upsampled_image4.upsample(upsampled_image5);
	upsampled_image5.save_image("5xupsampled_image.bmp");
}

void lame_interface(int &n,int &m)
{
	cout << "Hello m8, what type of image would you like to process?" << endl;
	cout << "For an upsampled image, press 1." << endl;
	cout << "For a normal image, press 2." << endl;
	cout << "For a subsampled image, press 3." << endl;
	cout << "Value: ";

	cin >> n;

	if (n == 1)
	{
		cout << "Ook, so you have chosen the upsampled image." << endl;
		cout << "For a 1x upsampled image, press 1" << endl;
		cout << "For a 2x upsampled image, press 2" << endl;
		cout << "For a 3x upsampled image, press 3" << endl;
		cout << "For a 4x upsampled image, press 4" << endl;
		cout << "For a 5x upsampled image, press 5" << endl;
		cout << "Value: ";
		cin >> m;
	}
	else if (n == 2)
	{
		cout << "Ook, so you have chosen the normal image." << endl;
	}
	else
	{
		cout << "Ook, so you have chosen the subsampled image." << endl;
		cout << "For a 1x subsampled image, press 1" << endl;
		cout << "For a 2x subsampled image, press 2" << endl;
		cout << "For a 3x subsampled image, press 3" << endl;
		cout << "For a 4x subsampled image, press 4" << endl;
		cout << "For a 5x subsampled image, press 5" << endl;
		cout << "Value: ";
		cin >> m;

	}
	cout << "Ok, now I'm doing my job..." << endl;
}

int main()
{
	
	subsample();
	//upsample();

	char s[255];
	lame_interface(n, m);

	ofstream fout("output.txt");
	if (n == 1)
	{
		if (m == 1)
			strcpy(s,"1xupsampled_image.bmp");
		if(m == 2)
			strcpy(s,"2xupsampled_image.bmp");
		if (m == 3)
			strcpy(s,"3xupsampled_image.bmp");
		if (m == 4)
			strcpy(s,"4xupsampled_image.bmp");
		if (m == 5)
			strcpy(s,"5xupsampled_image.bmp");
	}
	else if (n == 2)
	{
		strcpy(s,"image.bmp");
	}
	else if (n == 3)
	{
		if (m == 1)
			strcpy(s,"1xsubsampled_image.bmp");
		if (m == 2)
			strcpy(s,"2xsubsampled_image.bmp");
		if (m == 3)
			strcpy(s,"3xsubsampled_image.bmp");
		if (m == 4)
			strcpy(s,"4xsubsampled_image.bmp");
		if (m == 5)
			strcpy(s,"5xsubsampled_image.bmp");
	}
	bitmap_image image(s);

	unsigned char red;
	unsigned char green;
	unsigned char blue;

	unsigned int aux = 0, i = 0, j = 0, vect[] = { 7,6,5,4,3,2,1,0 };
	unsigned int height = image.height();
	unsigned int width = image.width();

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			image.get_pixel(x, y, red, green, blue);
			aux = (red*75 + green*155 + blue*25) / 255;   // rgb to some sort of grayscale convertion
			aux /= 32; // reducing the number of needed ascii chars - lossy conversion indeed
			//aux -= 7;
			aux = vect[aux];
			if (aux == 0)
				fout << ' ';
			if (aux == 1)
				fout << '.';
			if (aux == 2)
				fout << ':';
			if (aux == 3)
				fout << 'i';
			if (aux == 4)
				fout << 'o';
			if (aux == 5)
				fout << 'V';
			if (aux == 6)
				fout << 'M';
			if (aux == 7)
				fout << '@';
		}
		fout << endl;
	}
	system("pause");
	return 0;
}
