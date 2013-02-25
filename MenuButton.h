/* 
 * File:   MenuButton.h
 * Author: scribble
 *
 * Created on February 11, 2013, 5:56 AM
 */

#ifndef MENUBUTTON_H
#define	MENUBUTTON_H

#include "Button.h"
#include <string>

#define UNDO_C 0
#define REDO_C 1
#define ERASE_C 2
#define SIZE_C 3
#define COLOUR_C 4
#define NEXT_PAGE_C 5
#define PREVIOUS_PAGE_C 6
#define CLEAR_ALL_C 7
#define WRITE_C 8
#define STATUS_C 9

class MenuButton: public Button {
public:
    MenuButton();
    MenuButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_, std::string image_, int id_);
    MenuButton(const MenuButton& orig);
    virtual ~MenuButton();
    
    std::string getImagePath();
    void setImagePath(std::string image);
    int getId();
    void setSelectedImage(bool selected);
    
private:
    
    std::string imagePath;
    int id;
};

#endif	/* MENUBUTTON_H */

