#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    font.load("AVHersheySimplexLight.otf", 100, true, true, true);
    
    gui.setup();
    gui.add(letterSpacing.set("letterSpacing", 1, 0, 20));
    gui.add(resampleCount.set("resampleCount", 3, 1, 30));
    gui.add(dotRadius.set("dotRadius", 2, 0.1, 10));
    
    hersheyFont.setColor(255);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    string topRow = "qwertyuiop";
    
    ofSetColor(255);
    ofFill();

    ofPath path = hersheyFont.getPath(topRow, 3);
    
    float x = (ofGetWidth() - getBoundingBoxOfPath(path).getWidth()) * 0.5;
    float y = ofGetHeight() * 0.5;

    ofPushMatrix();
    ofTranslate(x, y);
    
    for (ofPolyline line : path.getOutline()) {
        for (glm::vec3 point : line.getResampledByCount(resampleCount)) {
            ofDrawCircle(point.x, point.y, dotRadius);
        }
    }
    
    ofPopMatrix();
    gui.draw();
}

ofRectangle ofApp::getBoundingBoxOfPath(ofPath &path) {
    ofRectangle rect;
    for (int i=0; i<path.getOutline().size(); i++) {
        ofRectangle b = path.getOutline().at(i).getBoundingBox();
        if (i==0) rect = b;
        else rect.growToInclude(b);
    }
    return rect;
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
