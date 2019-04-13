#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxHersheyFont.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
    
    void extracted(float baseScale, string &topRow);
    
    void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void processText(float baseScale, string topRow, float letterSpacing, float xOffset, float yOffset);
    
    ofxHersheyFont hersheyFont;
    ofTrueTypeFont font;
    
    ofxPanel gui;
    ofParameter<float> letterSpacing;
    ofParameter<float> dotRadius;
    
    ofParameter<float> topScale;
    ofParameter<float> middleScale;
    ofParameter<float> bottomScale;
    
    ofParameter<float> topToMiddlePadding;
    ofParameter<float> middleToBottomPadding;
    
    ofParameter<float> animationLength;
    ofParameter<float> maxVerticalDisplacement;
    ofParameter<float> maxScaleFactor;
    ofParameter<float> widthFactor;
    
    
    map<int, float> keyToTimeElapsed;
   
    
    ofEasyCam easyCam;
};
