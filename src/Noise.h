//
//  Noise.h
//  MEGAHERTZ
//
//  Created by 諸岡 光男 on 2013/07/07.
//
//

#ifndef __MEGAHERTZ__Noise__
#define __MEGAHERTZ__Noise__

#include <iostream>
#include "ofxUGen.h"

class Noise : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
    
    ofImage img;
    
    
	Noise(int x,int y)
	{
        
        pos.x = x;
        pos.y = y;
        
		float freq = ofMap(pos.y, 0, ofGetHeight(), 1000,10000);
		float pan = ofMap(pos.x, 200, ofGetWidth()-200, -1, 1);
        
		Env env = Env::perc(0.1,0.1,0.5, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
        amp =SinOsc::AR(1, 0, 0.5, 0.5) *  envgen;
        
        Out(
            Pan2::AR(WhiteNoise::AR(freq/5) * amp/400, pan)
            );
    }
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};
#endif /* defined(__MEGAHERTZ__Noise__) */
