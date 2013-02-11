/* 
 * File:   Painter.cpp
 * Author: scribble
 * 
 * Created on October 24, 2012, 10:15 AM
 */

#include "Painter.h"

using namespace poppler;

Painter::Painter() {

    loginShown = 0;
    filelistShown = 0;
    alertShown = 0;

    scribbleArea = new ScribbleArea(0, 50, WIDTH, HEIGHT - 50);
    menu = new Menu(0, 0, WIDTH, 50);
    menu->setScribbleArea(scribbleArea);

    login = new Login(WIDTH / 2 - 656 / 2, HEIGHT / 2 - 387 / 2, 656, 387);

    interpreter = new ScreenInterpreter(scribbleArea, menu, login);
}

Painter::Painter(const Painter& orig) {

}

Painter::~Painter() {
    delete scribbleArea;
    delete menu;
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

    if (alertShown == 1) {
        drawAlert();
    }
    else if (loginShown == 1) {
        drawLogin();
    }
    else if (filelistShown == 1) {
        drawFileList();
    }
    else {
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

    for (int i = 0; i < menu->getButtonArray()->size(); ++i) {

        glColor3f(menu->getButtonArray()->at(i)->getFillColor()->getRed(), menu->getButtonArray()->at(i)->getFillColor()->getGreen(), menu->getButtonArray()->at(i)->getFillColor()->getBlue());
        
        glBegin(GL_POLYGON);

        glVertex3i(menu->getButtonArray()->at(i)->getX(), menu->getButtonArray()->at(i)->getY(), 0);
        glVertex3i(menu->getButtonArray()->at(i)->getX() + menu->getButtonArray()->at(i)->getWidth(), menu->getButtonArray()->at(i)->getY(), 0);
        glVertex3i(menu->getButtonArray()->at(i)->getX() + menu->getButtonArray()->at(i)->getWidth(), menu->getButtonArray()->at(i)->getY() + menu->getButtonArray()->at(i)->getHeight(), 0);
        glVertex3i(menu->getButtonArray()->at(i)->getX(), menu->getButtonArray()->at(i)->getY() + menu->getButtonArray()->at(i)->getHeight(), 0);

        glEnd();

    }

}

void Painter::drawPDF() {

//#warning //add centering and scaling

    glRasterPos2i(scribbleArea->getDocument()->getX(), scribbleArea->getDocument()->getY());
    glPixelZoom(1.0, -1.0);

    glDrawPixels(scribbleArea->getDocument()->getImage()->width(), scribbleArea->getDocument()->getImage()->height(), GL_BGRA, GL_UNSIGNED_BYTE, scribbleArea->getDocument()->getImage()->data());
    // glScalef(1.2,1.2,0);
}

void Painter::showLogin(bool show) {
    loginShown = show;
}

void Painter::showFilelist(bool show) {
    filelistShown = show;
}

void Painter::showAlert(bool show) {
    alertShown = show;
}

void Painter::drawLogin() {

    glRasterPos2i(login->getX(), login->getY());
    glPixelZoom(1.0, -1.0);

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;
    //decode
    unsigned error = lodepng::decode(image, width, height, login->getImagePath());

    //if there's an error, display it
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...

    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

}

void Painter::drawKeyboard() {

}

void Painter::drawFileList() {

}

void Painter::drawAlert() {

}