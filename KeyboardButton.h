/* 
 * File:   KeyboardButton.h
 * Author: scribble
 *
 * Created on March 18, 2013, 2:44 AM
 */

#ifndef KEYBOARDBUTTON_H
#define	KEYBOARDBUTTON_H

#include "Button.h"
#include <string>

#define Q 0
#define W 1
#define E 2
#define R 3
#define T 4
#define Y 5
#define U 6
#define I 7
#define O 8
#define P 9
#define A 10
#define S 11
#define D 12
#define F 13
#define G 14
#define H 15
#define J 16
#define K 17
#define L 18
#define Z 19
#define C 20
#define V 21
#define B 22
#define N 23
#define M 24
#define SPACE 25
#define ENTER 26
#define SHIFT 27
#define BACKSPACE 28
#define HIDE 29
#define NUMBERS 29

class KeyboardButton: public Button {
public:
    KeyboardButton();
    KeyboardButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_, std::string image_, int id_);
    KeyboardButton(const KeyboardButton& orig);
    virtual ~KeyboardButton();
    
    std::string getImagePath();
    void setImagePath(std::string image);
    int getId();
    void setSelectedImage(bool selected);
    
private:
    
    std::string imagePath;
    int id;

};

#endif	/* KEYBOARDBUTTON_H */

