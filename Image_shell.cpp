// Image_shell.cpp (shell code, ADD #1-3)
// image processing
// open an image file. blur the image. print it on screen


#include <iostream>
#include <fstream> // std::ifstream
#include <string>  // std::string
#include <iomanip> // std::setw()


//----------------------------------------------
// global declarations
//----------------------------------------------

// return values
const int SUCCESS = 0;
const int ERR_OPENFILE_FAILED = 2;
const int ERR_CORRUPTED_FILE = 4;

// max dimension of image (2D array)
const int MAX_ROW = 100;
const int MAX_COL = 100;



//----------------------------------------------
// function declarations
//----------------------------------------------

// read one image (2D array) file from input file
int openOneImage(std::string filename/*IN*/, int pic[][MAX_COL]/*OUT*/, int& height, int& width);
// Pre: filename initialized
// Post: return ERR_FAILED_OPEN if file can't open
//       return ERR_CORRUPTED_FILE if invalid data (invalid dimension data or not enough image data) from file
//       return SUCCESS if file opened and an image (2D array) read successfully.
//       pic would store the image, height stores # of rows, and width stores # of columns


// blur an image
// ADD #1
void blur(int image[][MAX_COL] /*IN OUT*/,  int& height, int& width);




// print an image to output stream obj out
void printOneImage(std::ostream& out/*INOUT*/, const int pic[][MAX_COL]/*IN*/, int height/*IN*/, int width/*IN*/);
// Pre: pic filled with height x width numbers
//      out has been openned successfully
// Post: image printed to output stream object out. The height and width are printed first and then the image file data is printed


//----------------------------------------------

int main()
{
	int image[MAX_ROW][MAX_COL] = { 0 };  // one image
	int imgHeight; // height of image
	int imgWidth; // width of image

	std::string filename = "image1.txt";

	// load an image
	int result = openOneImage(filename, image, imgHeight, imgWidth);

	if (result == ERR_OPENFILE_FAILED)
	{
		std::cerr << "Error: can't open image \"" << filename << "\". Abort. \n"; // report to cerr
		return 1; // terminate now
	}

	if (result == ERR_CORRUPTED_FILE)
	{
		std::cerr << "Error: image \"" << filename << "\" is corrupted. Abort. \n"; // report to cerr
		return 1; // terminate now
	}

	// process the image
	
    blur(image, imgHeight, imgWidth);
    printOneImage(std::cout, image, imgHeight, imgWidth);

	return 0;
} // end main


//----------------------------------------------
// Function Implementation
//----------------------------------------------

// read one image (2D array) file from input file
int openOneImage(std::string filename/*IN*/, int pic[][MAX_COL]/*OUT*/, int& height, int& width)
{
	// ADD #2

	std::ifstream inFile(filename);
	
	if (inFile.fail())
	{
		return  ERR_OPENFILE_FAILED;
	}

	// First two elements on file are height and width respectively
	inFile >> height;
	inFile >> width;

	// adding 2 rows of zeros and 2 column surrounding the original pixels
	// so all the pixels has 8 NEIGHBOURS

	int maxRow = height + 2; // Maximun row including 2 rows of zeros at top and bottom
	int maxCol = width + 2;  // Maximun row including 2 columns of zeros at outer column

	int pixel;              // each pixel read from the file
	int totalPixel = 0;     // total number of pixel read from the file

		
	for (int row = 0; row < maxRow; row++)
	{
		for (int column = 0; column < maxCol; column++)
		{
			if (row == 0 || row == (maxRow - 1) || column == 0 || column == (maxCol - 1))  // the outer layer of the image
			{
				pic[row][column] = 0;          // assigning zeros to the outer layer of the image ( 2 rows and 2 columns)
			} // end if
			else
			{
				if (inFile >> pixel)          // reading each pixel
				{ 
					totalPixel++;             // if pixel is read then incrementing the totalPixel
					pic[row][column] = pixel; // adding pixel to the array pic
				} // end if
			} // end else
		} // end inner for loop	
	} // end outer for loop

	if (height * width != totalPixel)  // if total pixel is no equal to total pixels read
	{                                  // then the file is corrupted
		return ERR_CORRUPTED_FILE;
	} // end if

	// Since we added two rows of zeros and two columns of zero on the outer layer of image
	height += 2;
	width += 2;

	inFile.close();
	return SUCCESS;
} // end readOneImage


// blur an image
// ADD #3
void blur(int image[][MAX_COL] /*IN OUT*/ , int& height/*IN OUT*/, int& width/*IN OUT*/)
{
	int old[MAX_ROW][MAX_COL] = { 0 };  // copy of image array including the zero outer layers (not blurred)
	int blur[MAX_ROW][MAX_COL] = { 0 }; // copy of the blurred image array including the zeros
	int koef;                           // sum of the weights

	 // copying image to old array
	for (int row = 0; row < height; row++) 
	{
		for (int column = 0; column < width; column++)
		{
			old[row][column] = image[row][column];
		} // end for
	} // end for

	for (int x = 0; x < height; x++)      // x is total no. of rows and y is total no. of columns
	{
		for (int y = 0; y < width; y++)
		{
			if ((x == 1 || x == height - 2) &&  (y == 1 || y == width -2)) // the corners of the image which has 3 neighbours
			{
				koef = 7;  
			}
			else if (x == 1 || x == height - 2 || y == 1 || y == width - 2) // the sides of the image which has 6 neighbours
			{
				koef = 10;
			}
			else                                                            // pixels having 8 neighbouring pixels
			{
				koef = 14;
			}
			
			if (x == 0 || x == (height - 1) || y == 0 || y == (width - 1))
			{
			   // if the pixel is outer layers of zeros then do nothing
			} // end if
			else
			{
				blur[x][y]
					= (1 * old[x - 1][y - 1] + 2 * old[x - 1][y] + 1 * old[x - 1][y + 1] +
						2 * old[x][y - 1] + 2 * old[x][y] + 2 * old[x][y + 1] +
						1 * old[x + 1][y - 1] + 2 * old[x + 1][y] + 1 * old[x + 1][y + 1]) / koef;  // blurring by image with mean of weights
			} // end else
		} // end inner for loop	
	} // end outer for loop

	// updating height and width to the original height and width of the image without the zeros
	height -= 2;
	width -= 2;

	// copying everything except the outer layers with zeros from blur array to image array
	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			image[row][column] = blur[row + 1][column + 1];  // when we add zeros in outer layer the pixels are shifted to row +1 and column +1
		}
	} // end for
} // end method blur


// print an image to output stream obj out
void printOneImage(std::ostream& out/*INOUT*/, const int pic[][MAX_COL]/*IN*/, int height/*IN*/, int width/*IN*/) 
{
  out << height << ' ' << width << '\n';
  for (int row = 0; row < height; row++)
  {
	for (int col = 0; col < width; col++)
	{
	  out << std::setw(4) << pic[row][col];
	}
	out << '\n';
  }

} // end printOneImage 
