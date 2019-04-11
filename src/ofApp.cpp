#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    font.load("DIN Alternate Bold.ttf", 30, true, true, true);
    
    gui.setup();
    gui.add(letterSpacing.set("letterSpacing", 1, 0, 20));
    gui.add(resampleCount.set("resampleCount", 3, 1, 30));
    gui.add(dotRadius.set("dotRadius", 2, 0.1, 10));
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
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    vector<ofPath> letters = font.getStringAsPoints(topRow, false, false);
    for (ofPath letter : letters) {
        vector<ofPolyline> lines = letter.getOutline();
        for (ofPolyline line : lines) {
            line = line.getResampledByCount(resampleCount);
            vector<glm::vec3> points = line.getVertices();
            for (glm::vec3 point : points) {
                ofDrawCircle(point.x, point.y, dotRadius);
            }
        }
    }
    ofPopMatrix();
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
