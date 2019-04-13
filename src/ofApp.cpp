#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    font.load("AVHersheySimplexLight.otf", 100, true, true, true);
    
    gui.setup();
    gui.add(letterSpacing.set("letterSpacing", 5, 0.1, 20));
    gui.add(dotRadius.set("dotRadius", 2, 0.1, 10));
    gui.add(topScale.set("topScale", 0.75, 0.1, 10));
    gui.add(middleScale.set("middleScale", 1.5, 0.5, 10));
    gui.add(bottomScale.set("bottomScale", 2.325, 0.5, 10));
    
    gui.add(topToMiddlePadding.set("topToMiddlePadding", 50, 0, 200));
    gui.add(middleToBottomPadding.set("midToBottomPadding", 120, 0, 300));
    
    gui.add(animationLength.set("animationLength", 0.25, 0.1, 1.5));
    gui.add(keyPressAnimationLength.set("keyPressAnimationLength", 0.075, 0.01, 1));
    gui.add(keyPressDisplacementFactor.set("keyPressDisplacementScaleFactor", 0.5, 0.01, 2));
    gui.add(maxVerticalDisplacement.set("maxVertDisplacement", 195, 10, 300));
    gui.add(maxScaleFactor.set("maxScaleFactor", 6, 1, 10));
    gui.add(widthFactor.set("widthFactor", 0.175, 0, 5));
    gui.add(alphaValue.set("alphaValue", 200, 0, 255));
    
    hersheyFont.setColor(255);
    easyCam.setScale(1, -1, 1);
    
    ofSetFrameRate(60);
    keySound.load("Typewriter-Key.mp3");
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::processText(float baseScale, string text, float letterSpacing, float xOffset, float yOffset) {
    ofPushMatrix();
    ofTranslate(xOffset, yOffset);

    vector<ofPath> paths = hersheyFont.getPaths(text, baseScale);
    map<char, vector<int>> charToPointCounts;
    for (int i = 0; i < paths.size(); i++) {
        float timeElapsedFromKeyPress = 0;
        
        auto iterator = keyToTimeElapsed.find(text[i]);
        if (iterator != keyToTimeElapsed.end()) {
            timeElapsedFromKeyPress = ofGetElapsedTimef() - iterator->second;
            if (timeElapsedFromKeyPress > animationLength + keyPressAnimationLength) {
                keyToTimeElapsed.erase(text[i]);
                timeElapsedFromKeyPress = 0;
            }
        }
        
        if (timeElapsedFromKeyPress > 0) {
            ofSetColor(255, 255, 255, alphaValue);
        } else {
            ofSetColor(255);
        }
        
        char letterChar = text[i];
        ofPath letter = paths.at(i);
        if (letterChar == ' ') {
            letter.draw();
            continue;
        }
        
        vector<int> countsPerLine;
        for (ofPolyline line : letter.getOutline()) {
            ofPolyline resampled = line.getResampledBySpacing(letterSpacing);
            int count = resampled.getVertices().size();
            countsPerLine.push_back(count);
        }
        charToPointCounts.insert(make_pair(letterChar, countsPerLine));
        
        // from 0 to keyPressAnimationLength, this will remain as baseScale
        float scaleFactor = maxScaleFactor*sin(ofMap(timeElapsedFromKeyPress, keyPressAnimationLength, keyPressAnimationLength + animationLength, 0, PI, true)) + baseScale;
        string currLetter = text.substr(i, 1);
        ofPath scaledLetter = hersheyFont.getPaths(currLetter, scaleFactor).at(0);
        
        string strTilNow = text.substr(0, i);
        float widthTilNow = hersheyFont.getWidth(strTilNow, baseScale);
        float widthOfScaledLetter = hersheyFont.getWidth(currLetter, scaleFactor);
        
        float xOffset = widthTilNow - widthFactor*widthOfScaledLetter;
        letter = scaledLetter;
        
        float maxYDisplacement = (yOffset + maxVerticalDisplacement);
        vector<ofPolyline> lines = letter.getOutline();
        for (int j = 0; j < lines.size(); j++) {
            int pointCount = charToPointCounts[text[i]].at(j);
            ofPolyline resampled = lines.at(j).getResampledByCount(pointCount + 1);
            for (int k = 0; k < resampled.size(); k++) {
                glm::vec3 point = resampled.getVertices().at(k);
                
                float yDisplacement;
                if (timeElapsedFromKeyPress > 0 && timeElapsedFromKeyPress < keyPressAnimationLength) {
                    float maxKeyPressDisplacement = keyPressDisplacementFactor * hersheyFont.getHeight(baseScale);
                    
                    yDisplacement = -1 * maxKeyPressDisplacement*sin(ofMap(timeElapsedFromKeyPress, 0, keyPressAnimationLength, 0, PI, true));
                    cout << "Keypress displacement: " << yDisplacement << "/" << maxKeyPressDisplacement << endl;
                    
                } else {
                    yDisplacement = maxYDisplacement*sin(ofMap(timeElapsedFromKeyPress, keyPressAnimationLength, animationLength +   keyPressAnimationLength, 0, PI, true));
                }
                ofDrawCircle(point.x + xOffset, point.y - yDisplacement, dotRadius*sqrt(scaleFactor));
            }
        }
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw(){
    easyCam.begin();
    string topRow = "q w e r t y u i o p";
    string middleRow = "a s d f g h j k l";
    string bottomRow = "z x c v b n m ,";
    
    ofSetColor(255);
    ofFill();
    
    processText(topScale, topRow, 5, -hersheyFont.getWidth(topRow, topScale) * 0.5, 0);
    processText(middleScale, middleRow, 5.75, -hersheyFont.getWidth(middleRow, middleScale) * 0.5, hersheyFont.getHeight(topScale) + topToMiddlePadding);
    processText(bottomScale, bottomRow, 8, -hersheyFont.getWidth(bottomRow, bottomScale) * 0.5, hersheyFont.getHeight(bottomScale) + middleToBottomPadding);
    
    easyCam.end();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key >= 'a' || key <= 'z') {
        keyToTimeElapsed.insert(make_pair(key, ofGetElapsedTimef()));
        keySound.play();
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
