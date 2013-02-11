/* 
 * File:   Color.h
 * Author: scribble
 *
 * Created on November 5, 2012, 6:01 PM
 */

#ifndef COLOR_H
#define	COLOR_H

#define GREEN 0
#define LIGHT_GRAY 1
#define DARK_GRAY 2
#define WHITE 3

//add enum for common colors
#include <string>

class Color {
public:
    Color();
    Color(float r, float g, float b);
    Color(int color);
    Color(const Color& orig);
    virtual ~Color();
    
    float getRed();
    float getGreen();
    float getBlue();
    void setColor(int r, int g, int b);
    //void setColor(Color c);
    //void setColorFromColor(float r, float g, float b);

    
private:
    float red;
    float green;
    float blue;
    float convertToFloat(int x);
};

#endif	/* COLOR_H */

