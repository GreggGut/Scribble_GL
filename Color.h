/* 
 * File:   Color.h
 * Author: scribble
 *
 * Created on November 5, 2012, 6:01 PM
 */

#ifndef COLOR_H
#define	COLOR_H

//add enum for common colors

class Color {
public:
    Color();
    Color(float r, float g, float b);
    Color(const Color& orig);
    virtual ~Color();
    
    float getRed();
    float getGreen();
    float getBlue();
    
private:
    float red;
    float green;
    float blue;
};

#endif	/* COLOR_H */

