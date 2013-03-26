/* 
 * File:   Painter.cpp
 * Author: scribble
 * 
 * Created on October 24, 2012, 10:15 AM
 */

//#include <FTGL/FTGLPixmapFont.h>

#include "Painter.h"
#include "Loading.h"

using namespace poppler;

Painter::Painter() {

    scribbleArea = new ScribbleArea(0, 50, WIDTH, HEIGHT - 50);
    menu = new Menu(0, 0, WIDTH, 50);
    login = new Login(WIDTH / 2 - 656 / 2, HEIGHT / 2 - 387 / 2, 656, 387);
    filelist = new FileList(WIDTH / 2 - 656 / 2, HEIGHT / 2 - 738 / 2, 656, 738);
    colorPicker = new ColorPicker(168, 44, 253, 121);
    sizePicker = new SizePicker(124, 44, 253, 121);
    alert = new Alert("", "", -1);
    loading = new Loading();

    interpreter = new ScreenInterpreter(scribbleArea, menu, login, filelist, colorPicker, sizePicker, alert);

    menu->setScreenInterpreter(interpreter);
    login->setScreenInterpreter(interpreter);
    filelist->setScreenInterpreter(interpreter);
    colorPicker->setScreenInterpreter(interpreter);
    sizePicker->setScreenInterpreter(interpreter);
    alert ->setScreenInterpreter(interpreter);
}

Painter::Painter(const Painter& orig) {

}

Painter::~Painter() {
    delete scribbleArea;
    delete menu;
    delete login;
    delete interpreter;
    delete colorPicker;
    delete sizePicker;
    //delete keyboard;
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

    try {

         glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if (interpreter->getShowLogin() == 1) {
            drawLogin();
        } else if (interpreter->getShowFile() == 1) {
            drawFileList();
        } else {


            drawPDF();

           
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_POINT_SMOOTH);

            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
           

            drawPaths();

            drawMenu();

            if (interpreter->getShowColorPicker() == 1) {
                drawColorPicker();
            }

            if (interpreter->getShowSizePicker() == 1) {
                drawSizePicker();
            }

            glDisable(GL_LINE_SMOOTH);
            glDisable(GL_POINT_SMOOTH);
           
        }

        if (interpreter->getShowAlert() == 1) {
            drawAlert();
        }

        if (interpreter->getShowLoading() == 1) {
            drawLoading();
        }
           glDisable(GL_BLEND);

    } catch (...) {
        return;
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

        if (scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenWidth() > 2) {
            glPointSize(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenWidth() - 1);

            glBegin(GL_POINTS);
            for (int j = 0; j < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().size(); ++j) {

                glVertex3f(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getX(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getY(), 0.0f);
            }
            glEnd();
        }
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

        if (scribbleArea->getTempPath()->getPenWidth() > 2) {
            glPointSize(scribbleArea->getTempPath()->getPenWidth() - 1);

            glBegin(GL_POINTS);
            for (int j = 0; j < scribbleArea->getTempPath()->getPath().size(); ++j) {

                glVertex3f(scribbleArea->getTempPath()->getPath().at(j)->getX(), scribbleArea->getTempPath()->getPath().at(j)->getY(), 0.0f);
            }

            glEnd();
        }
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

        if (scribbleArea->getNetworkPath()->getPenWidth() > 2) {
            glPointSize(scribbleArea->getNetworkPath()->getPenWidth() - 1);

            glBegin(GL_POINTS);
            for (int j = 0; j < scribbleArea->getNetworkPath()->getPath().size(); ++j) {

                glVertex3f(scribbleArea->getNetworkPath()->getPath().at(j)->getX(), scribbleArea->getNetworkPath()->getPath().at(j)->getY(), 0.0f);
            }

            glEnd();
        }
    }
    scribbleArea->setLockForNetworkPath(0);
}

void Painter::drawMenu() {

    getPNG(menu->getBackground(), menu->getX(), menu->getY());

    for (int i = 0; i < menu->getButtonArray()->size(); ++i) {
        int btnx = menu->getX() + menu->getButtonArray()->at(i)->getX();
        int btny = menu->getY() + menu->getButtonArray()->at(i)->getY();

        getPNG(menu->getButtonArray()->at(i)->getImagePath(), btnx, btny);
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

    getPNG(menu->getOwnershipBTN()->getImagePath(), menu->getOwnershipBTN()->getX(), menu->getOwnershipBTN()->getY());

    glColor3f(Color(DARK_GRAY).getRed(), Color(DARK_GRAY).getGreen(), Color(DARK_GRAY).getBlue());
    glPixelZoom(1.0, 1.0);

    // Create a pixmap font from a TrueType file.
    FTGLPixmapFont font("./resources/fonts/century_gothic.ttf");

    // If something went wrong, bail out.
    if (font.Error())
        std::cout << "ERROR: FONT WAS NOT LOADED\n";

    // Set the font size and render a small text.
    font.FaceSize(25);

    float width = font.Advance(menu->getPageIndicator().c_str(), -1, FTPoint());
    float height = font.LineHeight();

    glRasterPos2i(WIDTH - width - (44 + 5)*2, height);

    font.Render(menu->getPageIndicator().c_str(), -1, FTPoint(), FTPoint(), FTGL::RENDER_ALL);

}

void Painter::drawAlert() {

    getPNG(alert->getImagePath(), alert->getX(), alert->getY());

    for (int i = 0; i < alert->getButtonArray()->size(); ++i) {
        int btnx = alert->getButtonArray()->at(i)->getX();
        int btny = alert->getButtonArray()->at(i)->getY();

        getPNG(alert->getButtonArray()->at(i)->getImagePath(), btnx, btny);
    }

    glColor3f(Color(DARK_GRAY).getRed(), Color(DARK_GRAY).getGreen(), Color(DARK_GRAY).getBlue());
    glPixelZoom(1.0, 1.0);

    FTPixmapFont *font = new FTPixmapFont("./resources/fonts/century_gothic.ttf");

    // If something went wrong, bail out.
    if (font->Error())
        std::cout << "ERROR: FONT WAS NOT LOADED\n";

    // Set the font size and render a small text.
    font->FaceSize(35);

    float width = font->Advance(alert->getTitle().c_str(), -1, FTPoint());
    float height = font->LineHeight();

    glRasterPos2i((alert->getX() + alert->getWidth() / 2)-(width / 2), alert->getY() + height - 5);

    font->Render(alert->getTitle().c_str(), -1, FTPoint(), FTPoint(), FTGL::RENDER_ALL);

    FTSimpleLayout layout;

    layout.SetFont(font);
    layout.SetAlignment(FTGL::ALIGN_CENTER);
    layout.SetLineLength(500);

    glRasterPos2i((alert->getX() + alert->getWidth() / 2)-(layout.GetLineLength() / 2), alert->getY() + 140 / 2 + layout.GetFont()->LineHeight());

    layout.Render(alert->getMessage().c_str(), -1, FTPoint(), FTGL::RENDER_ALL);
    // Set the font size and render a small text.

    delete font;
}

void Painter::drawPDF() {

    //#warning //add centering and scaling

    glPixelZoom(1.0, -1.0);

    char *_image = scribbleArea->getDocument()->getImage()->data();
    int _x = scribbleArea->getDocument()->getX();
    int _y = scribbleArea->getDocument()->getY();
    int width = scribbleArea->getDocument()->getImage()->width();
    int height = scribbleArea->getDocument()->getImage()->height();
    // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
    size_t u2 = 1;
    while (u2 < width) u2 *= 2;
    size_t v2 = 1;
    while (v2 < height) v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    double u3 = (double) width / u2;
    double v3 = (double) height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++)
            for (size_t c = 0; c < 4; c++) {
                image2[4 * u2 * y + 4 * x + c] = _image[4 * width * y + 4 * x + c];
            }

    glColor3f(1.0, 1.0, 1.0);
    // Enable the texture for OpenGL.
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);

    // Draw the texture on a quad, using u3 and v3 to correct non power of two texture size.
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex2f(_x, _y);
    glTexCoord2d(u3, 0);
    glVertex2f(width + _x, _y);
    glTexCoord2d(u3, v3);
    glVertex2f(width + _x, height + _y);
    glTexCoord2d(0, v3);
    glVertex2f(_x, height + _y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Painter::drawLogin() {

    getPNG(login->getImagePath(), login->getX(), login->getY());

    drawText(login->getUserName(), 35, login->getX() + 78, login->getY() + 128, Color(DARK_GRAY));
    drawText(login->getPassword(), 35, login->getX() + 78, login->getY() + 205, Color(DARK_GRAY));
}

void Painter::drawKeyboard() {

}

void Painter::drawFileList() {

    getPNG(filelist->getImagePath(), filelist->getX(), filelist->getY());

    for (int i = 0; i < filelist->getButtonArray()->size(); ++i) {

        int x = filelist->getButtonArray()->at(i)->getX();
        int y = filelist->getButtonArray()->at(i)->getY();

        glRasterPos2i(x, y);
        getPNG(filelist->getButtonArray()->at(i)->getImagePath(), x, y);

    }

    for (int i = 0; i < filelist->getFileListTable()->size(); ++i) {

        int x = filelist->getFileListTable()->at(i)->getX();
        int y = filelist->getFileListTable()->at(i)->getY();

        glRasterPos2i(x, y);
        getPNG(filelist->getFileListTable()->at(i)->getImagePath(), x, y);

        drawText(filelist->getFileListTable()->at(i)->getFileName(), 25, x + 56, y + 20, Color(DARK_GRAY));
    }


    std::string page;
    page = "Page " + filelist->getCurrentPage() + "/" + filelist->getNumberOfPages();

    drawText(page, 35, filelist->getX() + 18, filelist->getY() + 690, Color(GREEN));
}

void Painter::drawColorPicker() {
    getPNG(colorPicker->getImagePath(), colorPicker->getX(), colorPicker->getY());

    for (int i = 0; i < colorPicker->getButtonArray()->size(); ++i) {
        int btnx = colorPicker->getButtonArray()->at(i)->getX();
        int btny = colorPicker->getButtonArray()->at(i)->getY();

        getPNG(colorPicker->getButtonArray()->at(i)->getImagePath(), btnx, btny);
    }
}

void Painter::drawSizePicker() {
    getPNG(sizePicker->getImagePath(), sizePicker->getX(), sizePicker->getY());

    for (int i = 0; i < sizePicker->getButtonArray()->size(); ++i) {
        int btnx = sizePicker->getButtonArray()->at(i)->getX();
        int btny = sizePicker->getButtonArray()->at(i)->getY();

        getPNG(sizePicker->getButtonArray()->at(i)->getImagePath(), btnx, btny);
    }
}

void Painter::getPNG(std::string imagePath, int _x, int _y) {
    //decode
    glPixelZoom(1.0, -1.0);

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, imagePath);

    if (error) {
        return;
    }

    drawPixels(_x, _y, width, height, image);
}

void Painter::drawPixels(int _x, int _y, int width, int height, std::vector<unsigned char> _image) {

    // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
    size_t u2 = 1;
    while (u2 < width) u2 *= 2;
    size_t v2 = 1;
    while (v2 < height) v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    double u3 = (double) width / u2;
    double v3 = (double) height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++)
            for (size_t c = 0; c < 4; c++) {
                image2[4 * u2 * y + 4 * x + c] = _image[4 * width * y + 4 * x + c];
            }

    glColor3f(1.0, 1.0, 1.0);
    // Enable the texture for OpenGL.
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);

    // Draw the texture on a quad, using u3 and v3 to correct non power of two texture size.
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex2f(_x, _y);
    glTexCoord2d(u3, 0);
    glVertex2f(width + _x, _y);
    glTexCoord2d(u3, v3);
    glVertex2f(width + _x, height + _y);
    glTexCoord2d(0, v3);
    glVertex2f(_x, height + _y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Painter::drawText(std::string text, int size, int x, int y, Color color) {

    glColor3f(color.getRed(), color.getGreen(), color.getBlue());
    glPixelZoom(1.0, 1.0);
    glRasterPos2i(x, y + size - 5);
    // Create a pixmap font from a TrueType file.
    FTGLPixmapFont font("./resources/fonts/century_gothic.ttf");

    // If something went wrong, bail out.
    if (font.Error())
        std::cout << "ERROR: FONT WAS NOT LOADED\n";

    // Set the font size and render a small text.
    font.FaceSize(size);
    font.Render(text.c_str(), -1, FTPoint(), FTPoint(), FTGL::RENDER_ALL);
}

void Painter::drawLoading() {

    getPNG(loading->getBackground(), (WIDTH / 2) - (150 / 2), (HEIGHT / 2) - (150 / 2));

    int x = (WIDTH / 2) - (90 / 2);
    int y = (HEIGHT / 2) - (90 / 2);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  
    glTranslatef((WIDTH/2),(HEIGHT/2),0.0);
    
    glRotatef(loading->getTopAngle(), 0.0, 0.0, 1.0);
    
    glTranslatef(-(WIDTH/2),-(HEIGHT/2), 0.0);
    
    getPNG(loading->getTopRing(),x,y);
     
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  
    glTranslatef((WIDTH/2),(HEIGHT/2),0.0);
    
    glRotatef(loading->getBottomAngle(), 0.0, 0.0, 1.0);
    
    glTranslatef(-(WIDTH/2),-(HEIGHT/2), 0.0);
    
    getPNG(loading->getBottomRing(),x,y);
     
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    loading->setTopAngle();
    loading->setBottomAngle();
}