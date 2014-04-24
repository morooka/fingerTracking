#ifndef _VIDEO_HAND_FINGER_FINDER_
#define _VIDEO_HAND_FINGER_FINDER_

#include "ofMain.h"
#include "ofxCvMain.h"




//-----------------------------------------------|
class ofxFingerDetector{
	
	public:
	
	ofxFingerDetector();
	
	bool findFingers(ofxCvBlob blob);
	bool findHands(ofxCvBlob smblob);
	void draw(float x, float y);
	void drawhands(float x, float y);
	
	
	void findFarthestPoint(vector<ofPoint> hand, ofPoint centroid, int position, int i);
	
	float dlh,max;
	
	int handPositions[2];
	
	vector  <ofPoint>		fingerPoints;
	vector  <ofPoint>		handPoints;
	
	vector	<float>				fingersPointCurve;
	vector	<float>				handPointCurve;
	
	vector	<bool>				bfingerRuns;
	
	vector  <ofPoint>		leftHand;
	vector  <ofPoint>		rightHand;
	
	ofVec2f	v1, v2, aux1;
	 
	ofVec3f	v1D, vxv;
	ofVec3f	v2D;
	 
	int k,smk;
	
	ofPoint handCentroid;
	
	 float teta,lhd;

};
//-----------------------------------------------|


#endif	
