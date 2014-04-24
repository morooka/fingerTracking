//
//  SineHIGH.h
//  MEGAHERTZ
//
//  Created by 諸岡 光男 on 2013/07/07.
//
//

#ifndef __MEGAHERTZ__SineHIGH__
#define __MEGAHERTZ__SineHIGH__

#include <iostream>
#include "ofxUGen.h"

#endif /* defined(__MEGAHERTZ__SineHIGH__) */

class SineHIGH : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
	SineHIGH(int x,int y)
	{
        pos.x = x;
        pos.y = y;
        
		
        float freq = ofMap(pos.y,0, ofGetHeight(), 6000, 12000);
		float pan = ofMap(pos.x, 200, ofGetWidth()-200, -1, 1);
        
		Env env = Env::perc(0.3,0.5,0.4, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
        amp =SinOsc::AR(1, 0, 0.3, 0.3) *  envgen;
        
        Out(
            Pan2::AR(SinOsc::AR(freq) * amp/2, pan)
            );
        
	}
	void draw()
	{
		ofNoFill();
		ofSetColor(255,amp.getValue() * 255);
		ofCircle(pos.x, pos.y, amp.getValue() * 50);
	}
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};



