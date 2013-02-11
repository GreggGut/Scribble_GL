/* 
 * File:   Document.h
 * Author: scribble
 *
 * Created on January 28, 2013, 7:50 PM
 */

#ifndef DOCUMENT_H
#define	DOCUMENT_H

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-image.h>
#include "defines.h"
#include <string>

using namespace poppler;

class Document {
    
public:
    Document();
    Document(int x_, int y_, int w_, int h_);
    Document(const Document& orig);
    virtual ~Document();
    int getNumberOfPages();
    int getCurrentPage();
    image* getImage();
    int getX();
    int getY();
    void changePage(int page);
    void load(std::string file);
private:
    document *pdf;
    page *pdfPage;
    image *renderedImage;
    page_renderer *renderer;
    
    std::string fileName;
    int numberOfPages;
    int currentPage;
    int width;
    int height;
    int x;
    int y;
    
//#warning //could move all paths to here to save them later
    
};

#endif	/* DOCUMENT_H */

