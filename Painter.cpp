/* 
 * File:   Painter.cpp
 * Author: scribble
 * 
 * Created on October 24, 2012, 10:15 AM
 */

#include <FTGL/FTGLPixmapFont.h>

#include "Painter.h"

using namespace poppler;

Painter::Painter() {

    scribbleArea = new ScribbleArea(0, 50, WIDTH, HEIGHT - 50);
    menu = new Menu(0, 0, WIDTH, 50);
    login = new Login(WIDTH / 2 - 656 / 2, HEIGHT / 2 - 387 / 2, 656, 387);
    filelist = new FileList(WIDTH / 2 - 656 / 2, HEIGHT / 2 - 738 / 2, 656, 738);
    interpreter = new ScreenInterpreter(scribbleArea, menu, login, filelist);

    menu->setScreenInterpreter(interpreter);
    login->setScreenInterpreter(interpreter);
    filelist->setScreenInterpreter(interpreter);
}

Painter::Painter(const Painter& orig) {

}

Painter::~Painter() {
    delete scribbleArea;
    delete menu;
    delete login;
    delete interpreter;
    delete keyboard;
    delete alert;
}

ScribbleArea* Painter::getScribbleArea() {
    return scribbleArea;
}

Menu* Painter::getMenu() {
    return menu;
}

Login* Painter::getLogin() {
    return login;
}

Keyboard* Painter::getKeyboard() {
    return keyboard;
}

FileList* Painter::getFileList() {
    return filelist;
}

ScreenInterpreter* Painter::getInterpreter() {
    return interpreter;
}

void Painter::Draw() {

    if (interpreter->getShowAlert() == 1) {
        drawAlert();
    } else if (interpreter->getShowLogin() == 1) {
        drawLogin();
    } else if (interpreter->getShowFile() == 1) {
        drawFileList();
    } else {
        drawPDF();

        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);

        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        drawPaths();

        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_BLEND);

        drawMenu();

    }
}

void Painter::drawPaths() {

    scribbleArea->setLockForPath(1);

    for (int i = 0; i < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).size(); ++i) {

        glColor3f(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenColor().getRed(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenColor().getGreen(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenColor().getBlue());
        glLineWidth(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenWidth());

        /*glEnableClientState( GL_VERTEX_ARRAY );

        glVertexPointer(2,GL_INT,0,scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->pointsArray());
 
        glDrawArrays(GL_QUADS,0,2*scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPointsCount());
         */

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().size(); ++j) {

            glVertex3f(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getX(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getY(), 0.0f);
        }
        glEnd();
    }

    scribbleArea->setLockForPath(0);

    scribbleArea->setLockForTempPath(1);
    if (scribbleArea->getTempPath() != NULL) {

        glColor3f(scribbleArea->getTempPath()->getPenColor().getRed(), scribbleArea->getTempPath()->getPenColor().getGreen(), scribbleArea->getTempPath()->getPenColor().getBlue());
        glLineWidth(scribbleArea->getTempPath()->getPenWidth());

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getTempPath()->getPath().size(); ++j) {

            glVertex3f(scribbleArea->getTempPath()->getPath().at(j)->getX(), scribbleArea->getTempPath()->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }
    scribbleArea->setLockForTempPath(0);
    //Path that is being received through the network
    scribbleArea->setLockForNetworkPath(1);

    if (scribbleArea->getCurrentPage() == scribbleArea->getNetworkPage() && scribbleArea->getNetworkPath() != NULL) {

        glColor3f(scribbleArea->getNetworkPath()->getPenColor().getRed(), scribbleArea->getNetworkPath()->getPenColor().getGreen(), scribbleArea->getNetworkPath()->getPenColor().getBlue());
        glLineWidth(scribbleArea->getNetworkPath()->getPenWidth());

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getNetworkPath()->getPath().size(); ++j) {

            glVertex3f(scribbleArea->getNetworkPath()->getPath().at(j)->getX(), scribbleArea->getNetworkPath()->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }
    scribbleArea->setLockForNetworkPath(0);

}

void Painter::drawMenu() {

    glRasterPos2i(menu->getX(), menu->getY());
    getPNG(menu->getBackground());

    int size = menu->getButtonArray()->size();
    
    for (int i = 0; i < size; ++i) {

        glRasterPos2i(menu->getButtonArray()->at(i)->getX(), menu->getButtonArray()->at(i)->getY());
        getPNG(menu->getButtonArray()->at(i)->getImagePath());
    }

    std::string ownershipImage;
    
    int ownership = scribbleArea->getOwnershipValue();

    if (ownership == 0) { //ME
        //release it since I already have it
        ownershipImage = "OwnershipMine.png";

    } else if (ownership == 1) { //Taken
        //busy
        ownershipImage = "OwnershipTaken.png";
    } else if (ownership == 2) { //Free
        //send to get it
        ownershipImage = "GetOwnership.png";
        
    } else {
        std::cout << "ERROR WITH OWNERSHIP\n";
    }
    
     ownershipImage.insert(0, IMAGE_PATH);
     menu->getOwnershipBTN()->setImagePath(ownershipImage);
     
     glRasterPos2i(menu->getOwnershipBTN()->getX(), menu->getOwnershipBTN()->getY());
     getPNG(menu->getOwnershipBTN()->getImagePath());
}

void Painter::drawPDF() {

    //#warning //add centering and scaling
    glRasterPos2i(scribbleArea->getDocument()->getX(), scribbleArea->getDocument()->getY());
    glPixelZoom(1.0, -1.0);

    glDrawPixels(scribbleArea->getDocument()->getImage()->width(), scribbleArea->getDocument()->getImage()->height(), GL_BGRA, GL_UNSIGNED_BYTE, scribbleArea->getDocument()->getImage()->data());
    // glScalef(1.2,1.2,0);
}

void Painter::drawLogin() {

    glRasterPos2i(login->getX(), login->getY());

    getPNG(login->getImagePath());
       
    drawText(login->getUserName(), 35, login->getX() + 78, login->getY() + 128, Color(DARK_GRAY));
    drawText(login->getPassword(), 35, login->getX() + 78, login->getY() + 205, Color(DARK_GRAY));
}

void Painter::drawKeyboard() {

}

void Painter::drawFileList() {
    
    glRasterPos2i(filelist->getX(), filelist->getY());

    getPNG(filelist->getImagePath());

    int buttonSize = filelist->getButtonArray()->size();
    
    for (int i = 0; i < buttonSize; ++i) {

        int x = filelist->getButtonArray()->at(i)->getX();
        int y = filelist->getButtonArray()->at(i)->getY();
        
        glRasterPos2i(x,y);
        getPNG(filelist->getButtonArray()->at(i)->getImagePath());
 
    }

    int fileSize = filelist->getFileListTable()->size();
    
    for (int i = 0; i < fileSize; ++i) {
        
        int x = filelist->getFileListTable()->at(i)->getX();
        int y = filelist->getFileListTable()->at(i)->getY();
        
        glRasterPos2i(x,y);
        getPNG(filelist->getFileListTable()->at(i)->getImagePath());
               
        drawText(filelist->getFileListTable()->at(i)->getFileName(), 25, x + 56, y + 20, Color(DARK_GRAY));
    }
    
    std::string page;
    page = "Page " + filelist->getCurrentPage() + "/" + filelist->getNumberOfPages();
    
    drawText(page, 35, filelist->getX() + 18, filelist->getY() + 690, Color(GREEN));
}

void Painter::drawAlert() {

}

void Painter::getPNG(std::string imagePath) {
    //decode
    glPixelZoom(1.0, -1.0);

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, imagePath);

    //if there's an error, display it
    //if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

}

void Painter::drawText(std::string text, int size, int x, int y, Color color) {
    
    glColor3f(color.getRed(), color.getGreen(), color.getBlue());
    glPixelZoom(1.0, 1.0);
    glRasterPos2i(x, y+size-5);
    // Create a pixmap font from a TrueType file.
    FTGLPixmapFont font("./resources/fonts/century_gothic.ttf");

    // If something went wrong, bail out.
    if (font.Error())
        std::cout << "ERROR: FONT WAS NOT LOADED\n";

    // Set the font size and render a small text.
    font.FaceSize(size);
    font.Render(text.c_str(), -1, FTPoint(), FTPoint(), FTGL::RENDER_ALL);
}