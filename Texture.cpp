/* 
 * File:   Texture.cpp
 * Author: tom
 * 
 * Created on November 15, 2011, 1:09 PM
 */

#include "Texture.h"
#include "BasicMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>

using namespace std;

Texture::Texture(const char *name) {
    loadTexture(name);
}

Texture::~Texture() {
}

void Texture::bindTexture() {
  // Set this texture to be the one we are working with
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  
  // Set this texture to be the one we are working with
  glBindTexture(GL_TEXTURE_2D, texture[0]);
}

/** Load a ppm file from disk.
 @input filename The location of the PPM file.  If the file is not found, an error message
		will be printed and this function will return 0
 @input width This will be modified to contain the width of the loaded image, or 0 if file not found
 @input height This will be modified to contain the height of the loaded image, or 0 if file not found
 @return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
**/
unsigned char* Texture::loadPPM(const char* filename, int& width, int& height) {
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ( (fp=fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width  = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
	  retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

// load image file into texture object
void Texture::loadTexture(const char *name)
{
    //GLuint texture[1];     // storage for one texture
    //int twidth, theight;   // texture width/height [pixels]
    //unsigned char* tdata;  // texture pixel data

    // Load image file
    tdata = loadPPM(name, twidth, theight);
    if (tdata==NULL) return;

    // Create ID for texture
    glGenTextures(1, &texture[0]);
    
    // Set this texture to be the one we are working with
  glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Generate the texture
  glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
  
  // Select GL_MODULATE to mix texture with color for shading:
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // Use bilinear filtering:
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Wrap texture over at the edges:
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

