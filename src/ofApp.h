#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxHersheyFont.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
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
    
    ofRectangle getBoundingBoxOfPath(ofPath &path);

    ofxHersheyFont hersheyFont;
    ofTrueTypeFont font;
    
    ofxPanel gui;
    ofParameter<float> letterSpacing;
    ofParameter<int> resampleCount;
    ofParameter<float> dotRadius;
    ofParameter<float> hersheyScale;
    ofParameter<float> animationLength;
    ofParameter<float> maxVerticalDisplacement;
    ofParameter<float> maxScaleFactor;
    ofParameter<float> widthFactor;
    
    map<int, float> keyToTimeElapsed;
    
    ofEasyCam easyCam;
};
