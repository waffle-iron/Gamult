#include "Fader.h"
#include "ofApp.h"

Fader::Fader(int x0, int y, int size, string title) {

    this->title = title;
    setDimensions(x0, y, size);

    this->id = -1; // -1 means there is no touch associated

    font.load(UI_FONT_FACE, UI_FONT_SIZE, true);

    ofAddListener(ofEvents().touchDown,  this, &Fader::touchDown);
    ofAddListener(ofEvents().touchMoved, this, &Fader::touchMoved);
    ofAddListener(ofEvents().touchUp,    this, &Fader::touchUp);

}

void Fader::setDimensions(int x0, int y, int size) {
    this->x0 = x0;
    this->y = y;
    this->size = size;
    this->x0 = x0 + 0.15 * (ofGetWidth()/NMODULES) + size; //TODO - check a better way to get this. It makes sure the fader line starts in a point which will result in the fader rectangle being in line with the Freeze buton, that is, at 0.6 of module width
    this->range = 0.7*(ofGetWidth()/NMODULES)-size;
    this->rect = ofRectangle(this->x0+range/2-size/2, y-size/2, size, size);
    this->stringOrigin = x0;
}

void Fader::touchDown(ofTouchEventArgs& event) {
    if (id == -1 && rect.inside(event.x, event.y)) {
        id = event.id;
    }
}

void Fader::touchUp(ofTouchEventArgs& event) {
    if (event.id == id) {
        id = -1;
    }
}

void Fader::touchMoved(ofTouchEventArgs& event) {

    // make sure that only updates fader position if first click was inside it
    if (event.id == id) {

        rect.setX(event.x);

        if (rect.x < x0 - size/2)
            rect.x = x0 - size/2;

        if (rect.x > x0 + range - size/2)
            rect.x = x0 + range - size/2;
    }
}

float Fader::getValue() {
    return ofMap(rect.x, x0-size/2, x0+range-size/2, 0.1, 2);
}

void Fader::draw() {

    ofSetColor(UI_COLOR);

    // draw the line in which the fader moves
    ofDrawLine(x0, y, x0+range, y);

    int middleX = x0+range/2;
    ofDrawLine(middleX, y-size/3, middleX, y+size/3);

    // draw the fader
    ofDrawRectangle(rect);

    font.drawString(title, stringOrigin, y+4);

}