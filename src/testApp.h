#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxSyphon.h"
#include "ofxKinect.h"
#include "ofxSimpleSerial.h"

#include "ofxFingerDetector.h"
#include "ofxContourAnalysis.h"

#include "myUgen.h"
#include "houseDust.h"
#include "SineHIGH.h"
#include "Noise.h"


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    bool                LearnBakground,bDustMask,bfeedback,bImage;
    
    ofxCvColorImage     colorImg,colorImg2;
	ofxCvGrayscaleImage grayImage,grayImage2; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear;       // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar;        // the far thresholded image
	ofxCvGrayscaleImage graydiff,grayBg,graydiff2,grayBg2;
    
	ofxCvContourFinder  contourFinder,contourFinder2;
    ofVideoGrabber      vidGrabber,vidGrabber2;
    
    int                 threshold,threshold2;
    bool				bLearnBakground,bDrawVideo;
    
    std::vector<ofxCvBlob>::iterator blob;
    std::vector<ofxCvBlob>::iterator blob2;
    
    int centroidX1,centroidY1,centroidX2,centroidY2,centroidX3,
        centroidY3,centroidX4,centroidY4,centroidX12,centroidY12;
    
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonClient client;
    
    ofxKinect kinect;
    
    bool      bThreshWithOpenCV;
	bool      bDrawPointCloud;
    bool      bReversePoints;
	
	int       nearThreshold;
	int       farThreshold;
    int       angle;
       
    ofxSimpleSerial	serial;
    string		    message;
    bool		    remember;
    
    float counter;
    
    ofVec3f previous, current;
    
    deque<ofVec3f> pathVertices;
    ofMesh pathLines;
    
    ofEasyCam easyCam;
    
    int GLtimenow  = 0;
    int GLtimebase = 0;
    
    ofImage     srcImg;
    ofImage     brushImg;
    
    ofFbo       maskFbo,maskFbo2;
    ofFbo       fbo;
    
    ofShader    shader;
    
    bool        bBrushDown,bDustColor,bHouseDustDraw,bStart;
    
    int                       alpha;
    
    ofImage                   glitch;
    ofImageQualityType        quality;
    
    int                       timeshift;
    
    ofxFingerDetector         fingerFinder;
    
    vector<vector <ofPoint> > simpleContours;
    vector <ofPoint>          contourReg;
    vector <ofPoint>          contourSmooth;
    vector <ofPoint>          contourSimple;
    
     vector <ofPoint>        simpleCountour;
    
    float                    simpleAmount;
    ofxContourAnalysis       contourAnalysis;
    
    vector<houseDust*>   synthshouseDust;
    vector<MyUgenSynth*> MyUgenSynths;
    vector<SineHIGH*>    synthsSineHIGH;
    vector<Noise*>       synthsNoise;

    ofTexture tex;
    int tex_width;
    int tex_height;

};
