//
//  myUgen.h
//  MEGAHERTZ
//
//  Created by 諸岡 光男 on 2013/07/06.
//
//

#ifndef __MEGAHERTZ__myUgen__
#define __MEGAHERTZ__myUgen__

#include <iostream>
#include "ofxUGen.h"
#include "ofMain.h"

#endif /* defined(__MEGAHERTZ__myUgen__) */

class MyUgenSynth : public ofxUGen::SynthDef
{
public:
	
   	
	UGen envgen;
	UGen amp;
    
    int myUgenX =0;
    int myUgenY =0;
    int myUgenVolume = 1;
    
    ofVec2f pos ;
    
    
    MyUgenSynth(int x,int y)
    	{
            pos.x = x;
            pos.y = y;
            
            float freq = ofMap(pos.x, 0, 480, 0, 500);
            float pan = ofMap(pos.y, 0, 640, -1, 1);
            
		Env env = Env::perc(0.3, 0.3, 0.5, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(4.0), 0, 0.5, 0.5) * envgen;
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp * myUgenVolume, pan)
            );
        }
    
    void draw();
	bool isAlive();
	
};






