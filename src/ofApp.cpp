#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    font.load("AVHersheySimplexLight.otf", 100, true, true, true);
    
    gui.setup();
    gui.add(letterSpacing.set("letterSpacing", 1, 0, 20));
    gui.add(resampleCount.set("resampleCount", 30, 1, 100));
    gui.add(dotRadius.set("dotRadius", 2, 0.1, 10));
    gui.add(hersheyScale.set("hersheyScale", 0.75, 0.1, 10));
    gui.add(animationLength.set("animationLength", 0.25, 0.1, 1.5));
    gui.add(maxVerticalDisplacement.set("maxVertDisplacement", 100, 10, 300));
    gui.add(maxScaleFactor.set("maxScaleFactor", 2, 1, 10));
    gui.add(widthFactor.set("widthFactor", 0.175, 0, 5));
    
    hersheyFont.setColor(255);
    easyCam.setScale(1, -1, 1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    easyCam.begin();
    string topRow = "q w e r t y u i o p";
    
    ofSetColor(255);
    ofFill();
    
    ofPushMatrix();
    ofTranslate(-hersheyFont.getWidth(topRow, hersheyScale) * 0.5, 0);
    
    vector<ofPath> paths = hersheyFont.getPaths(topRow, hersheyScale);
    for (int i = 0; i < paths.size(); i++) {
        float timeElapsed = 0;

        auto iterator = keyToTimeElapsed.find(topRow[i]);
        if (iterator != keyToTimeElapsed.end()) {
            timeElapsed = ofGetElapsedTimef() - iterator->second;
            if (timeElapsed > animationLength) {
                keyToTimeElapsed.erase(topRow[i]);
                timeElapsed = 0;
            }
        }
        
        ofPath letter = paths.at(i);
        if (timeElapsed == 0) {
            letter.draw();
            continue;
        }
        float scaleFactor = maxScaleFactor*hersheyScale*sin(ofMap(timeElapsed, 0, animationLength, 0, PI/2, true));
        string currLetter = topRow.substr(i, 1);
        ofPath scaledLetter = hersheyFont.getPaths(currLetter, scaleFactor).at(0);
        
        string strTilNow = topRow.substr(0, i);
        float widthTilNow = hersheyFont.getWidth(strTilNow, hersheyScale);
        float widthOfScaledLetter = hersheyFont.getWidth(currLetter, scaleFactor);

        float xOffset = widthTilNow - widthFactor*widthOfScaledLetter;
        letter = scaledLetter;
        
        int pointsToSamplePerLine = resampleCount / letter.getOutline().size();
        for (ofPolyline line : letter.getOutline()) {
            for (glm::vec3 point : line.getResampledByCount(pointsToSamplePerLine)) {
                float yDisplacement = maxVerticalDisplacement*sin(ofMap(timeElapsed, 0, animationLength, 0, PI));
                ofDrawCircle(point.x + xOffset, point.y - yDisplacement, dotRadius*sqrt(scaleFactor));
            }
        }
    }
    
    ofPopMatrix();
    easyCam.end();
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
    if (key >= 'a' || key <= 'z') {
        keyToTimeElapsed.insert(make_pair(key, ofGetElapsedTimef()));
    }
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
