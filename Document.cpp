/* 
 * File:   Document.cpp
 * Author: scribble
 * 
 * Created on January 28, 2013, 7:50 PM
 */

#include <iostream>

#include "Document.h"

using namespace poppler;

Document::Document() {
}

Document::Document(int x_, int y_, int w_, int h_) {
    width = w_;
    height = h_;
    x = x_;
    y = y_;
 
    renderer = new page_renderer();
  
    renderer->set_render_hint(renderer->antialiasing,true);
    renderer->set_render_hint(renderer->text_antialiasing,true);
    renderer->set_render_hint(renderer->text_hinting,true);

    //renderer->set_paper_color(0x00000000);
    renderedImage = new image(); 
    //std::cout << std::endl << renderedImage->data();
   
}

Document::Document(const Document& orig) {
}

Document::~Document() {
}

void Document::load(std::string file){
      
    std::string userName = "";
    std::string password = "";

    pdf = document::load_from_file(file, userName, password);

    if (pdf == NULL || file == "blank") {
        numberOfPages = 1;
        currentPage = 0;
        std::cout << "failed";
    }
    
    else {
        numberOfPages = pdf->pages();
        currentPage = 0;
         changePage(0);
       //std::cout << "good";
    }
    
}

void Document::changePage(int page) {
    currentPage = page;
    
    pdfPage = pdf->create_page(currentPage);
           
    *renderedImage = renderer->render_page(pdfPage, PDF_RESOLUTION, PDF_RESOLUTION, -1, -1, -1, -1, rotate_0);
}

int Document::getNumberOfPages() {
    return numberOfPages;
}

int Document::getCurrentPage() {
    return currentPage;
}

image* Document::getImage() {
    return renderedImage;
}

int Document::getX() {
    return x;
}

int Document::getY() {
    return y;
}