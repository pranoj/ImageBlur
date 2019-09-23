# ImageBlur
This project blurs the given image.
This program simulates image processing. More about image processing can be found at https://bit.ly/2Hror6D.
An image file is simulated by a 2D array of ints.  Shell code is provided in Image_shell.cpp.  The program includes the following functions:    
•	Open an image file (input a 2D array of ints from a text file).  The first two numbers from the file are the dimension of the image (2D array), the first number is height (# of rows) and the second number is width (# of columns).  Next comes the 2D array stored in row order (row 0, row1, …). There should be (# of rows) × (# of columns) integers.  Sometimes an image file has been corrupted (not invalid dimension or not enough numbers in the file). This program tests and reports such a files.  
•	Process an image file (blur the image). This program uses blurring algorithm which was taught in my c++ class.
•	Print out blurred image on screen. 
 
