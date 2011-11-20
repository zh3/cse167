/* 
 * File:   Texture.h
 * Author: tom
 *
 * Created on November 15, 2011, 1:09 PM
 */

#ifndef TEXTURE_H
#define	TEXTURE_H

#include <GL/gl.h>

class Texture {
public:
    Texture(const char *name);
    virtual ~Texture();
    
    void bindTexture();
private:
    GLuint texture[1];
    int twidth, theight;
    unsigned char *tdata;
    
    void loadTexture(const char *name);
    unsigned char *loadPPM(const char* filename, int& width, int& height);
};

#endif	/* TEXTURE_H */

