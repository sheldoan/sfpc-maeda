#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    font.load("DIN Alternate Bold.ttf", 100, true, true, true);
    
    gui.setup();
    gui.add(letterSpacing.set("letterSpacing", 1, 0, 20));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    string topRow = "qwertyuiop";
    font.setLetterSpacing(letterSpacing);
    ofRectangle bounds = font.getStringBoundingBox(topRow, 0, 0);
    
    float x = (ofGetWidth() - bounds.getWidth()) / 2;
    float y = ofGetHeight()*0.5 + bounds.getHeight()*0.5;

    ofSetColor(255);
    ofFill();
    ofDrawCircle(x, y, 10);
    font.drawStringAsShapes(topRow, x, y);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 10);
    
    ofNoFill();
    ofDrawRectangle(font.getStringBoundingBox(topRow, x, y));
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
