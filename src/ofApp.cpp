#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    font.load("AVHersheySimplexLight.otf", 100, true, true, true);
    
    gui.setup();
    gui.add(letterSpacing.set("letterSpacing", 1, 0, 20));
    gui.add(resampleCount.set("resampleCount", 30, 1, 100));
    gui.add(dotRadius.set("dotRadius", 2, 0.1, 10));
    gui.add(hersheyScale.set("hersheyScale", 3, 0.1, 10));
    gui.add(animationLength.set("animationLength", 0.5, 1, 10));
    gui.add(maxVerticalDisplacement.set("maxVertDisplacement", 20, 10, 100));
    
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

    float x = (ofGetWidth() - hersheyFont.getWidth(topRow, hersheyScale)) * 0.5;
    float y = ofGetHeight() * 0.5;

    ofPushMatrix();
    ofTranslate(x, y);

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
        int pointsToSamplePerLine = resampleCount / letter.getOutline().size();
        for (ofPolyline line : letter.getOutline()) {
            for (glm::vec3 point : line.getResampledByCount(pointsToSamplePerLine)) {
                ofDrawCircle(point.x, point.y - maxVerticalDisplacement*sin(ofMap(timeElapsed, 0, animationLength, 0, PI)), dotRadius);
            }
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
