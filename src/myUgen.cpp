//
//  myUgen.cpp
//  MEGAHERTZ
//
//  Created by 諸岡 光男 on 2013/07/06.
//
//

#include "myUgen.h"

void MyUgenSynth::draw(){
    
        ofFill();
        ofSetColor(100, amp.getValue() * 255*10);
        ofCircle(pos.x, pos.y, amp.getValue() * 20);
        
        
        ofNoFill();
        ofSetColor(100,100,100,100);
        ofCircle(pos.x, pos.y, amp.getValue() * 80);
}

bool MyUgenSynth::isAlive()
{
    return !Out().isNull();
}
