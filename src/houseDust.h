//
//  houseDust.h
//  MEGAHERTZ
//
//  Created by 諸岡 光男 on 2013/07/07.
//
//

#ifndef __MEGAHERTZ__houseDust__
#define __MEGAHERTZ__houseDust__

#include <iostream>
#include "ofxUGen.h"

#endif /* defined(__MEGAHERTZ__houseDust__) */


class houseDust : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
    ofTexture tex;
    
    ofImage img;
    
    int houseDustVolume;
    int houseDustPositionX;
    int houseDustPositionY;
    int random_radius;
    
	houseDust(int x, int y)
	{
        pos.x = x;
        pos.y = y;
        
		float freq = ofMap(pos.y, 0, ofGetHeight(), 100,20000);
		float pan = ofMap(pos.x, 200, ofGetWidth()-200, -1, 1);
        
		Env env = Env::perc(0.1,0.2,1.0, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
        amp =SinOsc::AR(5, 0, 1.0, 1.0) *  envgen;
        
        Out(
            Pan2::AR(Dust2::AR(5,1,0) * amp/2, pan)
            );
    }
	void draw()
	{
       // ofSetColor(255);
       // ofFill();
       // ofCircle(houseDustPositionX, houseDustPositionY,6*amp.getValue()*random_radius);
    }
    
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};

