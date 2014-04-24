#include "testApp.h"
#include "ofxUGen.h"


int synthX1 = 0;
int synthY1 = 0;
int synthX2 = 0;
int synthY2 = 0;
int synthX3 = 0;
int synthY3 = 0;


int synths1_2Volume = 1;
int myLFSawVolume = 1;

int random_radius;

float glitchSawX;
float glitchSawY;

float myLFSawX;
float myLFSawY;


class MySynth : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
	MySynth()
	{
		pos.x = synthX1;
		pos.y = synthY1;
		
		float freq = ofMap(pos.x, 0, ofGetHeight(), 0, 500);
		float pan = ofMap(pos.y, 0, ofGetWidth(), -1, 1);
        
		Env env = Env::perc(0.3, 0.3, 0.5, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(4.0), 0, 0.5, 0.5) * envgen;
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp * synths1_2Volume, pan)
            );
	}
	
	void draw()
	{
		ofFill();
		ofSetColor(100, amp.getValue() * 255*10);
		ofCircle(pos.x, pos.y, amp.getValue() * 20);
        
		
		ofNoFill();
		ofSetColor(100,100,100,200);
		ofCircle(pos.x, pos.y, amp.getValue() * 100);
	}
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};

class MySynth2 : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
	MySynth2()
	{
		pos.x = synthX2;
		pos.y = synthY2;
		
		float freq = ofMap(pos.x, 0, ofGetHeight(), 0, 1000);
		float pan = ofMap(pos.y, 0, ofGetWidth(), -1, 1);
        
		Env env = Env::perc(0.3, 0.6, 0.5, EnvCurve::Linear);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(10.0), 0, 0.5, 0.5) * envgen;
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp * synths1_2Volume, pan)
            );
	}
	
	void draw()
	{
         ofFill();
         ofSetColor(100,100,255, amp.getValue() * 255*20);
         ofCircle(pos.x, pos.y, amp.getValue() * 20);
         
		
		ofNoFill();
		ofSetColor(100,100,255,100);
		ofCircle(pos.x, pos.y, amp.getValue() * 100);
	}
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};

class MySynth3 : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
	MySynth3()
	{
		pos.x = synthX3;
		pos.y = synthY3;
		
		float freq = ofMap(pos.x, 0, ofGetHeight(), 0, 10000);
		float pan = ofMap(pos.y, 0, ofGetWidth(), -1, 1);
        
		Env env = Env::perc(0.8, 1.5, 0.7, EnvCurve::Welch);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(10.0), 0, 0.2, 0.2) * envgen;
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp, pan)
            );
	}
	
	void draw()
	{
         ofFill();
         ofSetColor(255,255,255,150);
         ofCircle(pos.x, pos.y, amp.getValue() * 100);
         
		
        }
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};


class glitchSaw : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
    ofTexture tex;
    
    ofImage img;
    
    glitchSaw()
	{
        pos.x = glitchSawX;
        pos.y = glitchSawY;
        
		float freq = ofMap(pos.y, 0, ofGetWidth(), 12000,14000);
		float pan = ofMap(pos.x, 200, ofGetHeight()-200, -1, 1);
        
		Env env = Env::perc(0.1,0.4,0.5, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
        amp =SinOsc::AR(ofRandom(4.0), 0, 0.5, 0.5) *  envgen;
        
        Out(
            Pan2::AR(TableOsc::AR(512,freq,1.0,1.0) * amp/100, pan)
            );
    }
	void draw()
	{
        
        ofSetColor(255,amp.getValue()*255);
        ofNoFill();
        ofCircle(pos.x, pos.y,amp.getValue()*30*ofRandom(1,3));
    }
    
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};

class myLFSaw : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
    ofTexture tex;
    
    ofImage img;
    
    myLFSaw()
	{
        pos.x = myLFSawX;
        pos.y = myLFSawY;
        
		float freq = ofMap(pos.y, 0, ofGetWidth(), 12000,14000);
		float pan = ofMap(pos.x, 200, ofGetHeight()-200, -1, 1);
        
		Env env = Env::perc(0.1,0.5,1.5, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
        amp =SinOsc::AR(ofRandom(4.0), 0, 0.5, 0.5) *  envgen;
        
        Out(
            Pan2::AR(LFSaw::AR(freq,1.0,1.0) * amp*2*myLFSawVolume, pan)
            );
    }
	void draw()
	{
        
        ofSetColor(255,amp.getValue()*255);
        ofNoFill();
        ofCircle(pos.x, pos.y,amp.getValue()*30*ofRandom(1,3));
    }
    
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};


vector<MySynth*>   synths;
vector<MySynth2*>  synths2;
vector<MySynth3*>  synths3;
vector<glitchSaw*> glitchSawsynths;
vector<myLFSaw*>   myLFSawsynths;


bool fingersFound=false;
bool handFound=false;
int numBlobs = 0;
int numFingerPoints = 0;

bool doFingerFollow = false;
//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetCircleResolution(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);
    
    colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
    grayBg.allocate(kinect.width, kinect.height);
    graydiff.allocate(kinect.width, kinect.height);
    
    vidGrabber.listDevices();
   // vidGrabber.setDeviceID(1);
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(640, 480);
    
/*	kinect.setRegistration(true);
	//kinect.init(true,false,true);
    kinect.init();
    kinect.open();
 
 */
       
    threshold = 255;
    threshold2 = 255;
    bLearnBakground = true;
       
    centroidX1 = 0;
    centroidY1 = 0;
    centroidX2 = 0;
    centroidY2 = 0;
    centroidX3 = 0;
    centroidY3 = 0;
    centroidX4 = 0;
    centroidY4 = 0;
       
    colorImg2.allocate(kinect.width, kinect.height);
	grayImage2.allocate(kinect.width, kinect.height);
    grayBg2.allocate(kinect.width, kinect.height);
    graydiff2.allocate(kinect.width, kinect.height);
    
    grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

    ofxUGen::instance().setup();    
        
    mainOutputSyphonServer.setName("Main Output");
    
    nearThreshold = 255;
	farThreshold =240;
	bThreshWithOpenCV = true;
   
    // zero the tilt on startup
	angle = 1;
	kinect.setCameraTiltAngle(angle);
    
    bDustMask = false;
    
    pathLines.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    srcImg.loadImage("paraiso3.jpg");
    brushImg.loadImage("brush.png");
    
    int width = 640;
    int height = 480;
    
    string shaderProgram = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex0;\
    uniform sampler2DRect maskTex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    vec3 src = texture2DRect(tex0, pos).rgb;\
    float mask = texture2DRect(maskTex, pos).r;\
    \
    gl_FragColor = vec4( src , mask);\
    }";
    
    maskFbo.allocate(kinect.width,kinect.height);
    fbo.allocate(width,height);
    
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram();
    
    // Let«s clear the FBO«s
    // otherwise it will bring some junk with it from the memory
    maskFbo.begin();
    ofClear(0,0,0,255);
    maskFbo.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    bBrushDown = false;
    
    alpha = 60;
    
   // hD.houseDustVolume = 0;
    
    random_radius = ofRandom(1,5);
    
    centroidX12 = ofGetWidth()/2;
    centroidY12 = ofGetHeight()/2;
    
    bDustColor = false;
    bHouseDustDraw = false;
    bStart = false;
    
    glitch.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
   
    timeshift = 0;
    
    simpleAmount=4.0;
    
    tex_width = 50;
    tex_height = 50;
    tex.allocate(tex_width,tex_height,GL_RGBA);
        
}

//--------------------------------------------------------------
void testApp::update(){
    
  //  kinect.update();
    vidGrabber.update();

 //   if(kinect.isFrameNew()) {
        
     //   grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        colorImg.setFromPixels(vidGrabber.getPixels(),kinect.width,kinect.height);
        
        //contourFinder2!!
        grayImage2=colorImg;
        if(bLearnBakground==true){
            grayBg2=grayImage2;
            bLearnBakground=false;
        }
        graydiff2.absDiff(grayBg2,grayImage2);
        graydiff2.threshold(threshold);
        contourFinder2.findContours(graydiff2, 10, (kinect.width*kinect.height)/3, 5, false);
               
	/*	if(bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
            
		} else {
			
			// or we do it ourselves - show people how they can work with the pixels
			unsigned char * pix = grayImage.getPixels();
			
			int numPixels = grayImage.getWidth() * grayImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}*/
	//	}
        // update the cv images
		grayImage.flagImageChanged();
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
        
     //   contourFinder.findContours(grayImage, 20, (640*480)/3, 10, false);
   // }
    
    counter = counter + 0.033f;
    
 /*   for (blob=contourFinder.blobs.begin(); blob!= contourFinder.blobs.end(); blob++) {
   
        centroidX1 = contourFinder.blobs[0].centroid.x;
        centroidY1 = contourFinder.blobs[0].centroid.y;
        centroidX2 = contourFinder.blobs[1].centroid.x;
        centroidY2 = contourFinder.blobs[1].centroid.y;
        centroidX3 = contourFinder.blobs[2].centroid.x;
        centroidY3 = contourFinder.blobs[2].centroid.y;
        centroidX4 = contourFinder.blobs[3].centroid.x;
        centroidY4 = contourFinder.blobs[3].centroid.y;
        
        synthX1 = centroidX1;
        synthY1 = centroidY1;
        synthX2 = centroidX2;
        synthY2 = centroidY2;
    }
    current.x = centroidX1;
    current.y = centroidY1;
    
    // add the current position to the pathVertices deque
    pathVertices.push_back(current);
    // if we have too many vertices in the deque, get rid of the oldest ones
    while(pathVertices.size() > 100) {
        pathVertices.pop_front();
    }
    
    // clear the pathLines ofMesh from any old vertices
    pathLines.clear();
    // add all the vertices from pathVertices
    for(int i = 0; i < pathVertices.size(); i++) {
        pathLines.addVertex(pathVertices[i]);
    }
    
    // MASK (frame buffer object)
    //
    maskFbo.begin();
    if (bBrushDown == true){
        for(int i = 0; i < pathVertices.size(); i++) {
        brushImg.draw(pathVertices[i].x-(30+random_radius*10),pathVertices[i].y-(30+random_radius*10),60+random_radius*20,60+random_radius*20);
        }
    }
    if (bHouseDustDraw == true) {
        vector<houseDust*>::iterator it4 = synthshouseDust.begin();
        while (it4 != synthshouseDust.end())
        {
            houseDust *s = *it4;
            s->draw();
            
            if (!s->isAlive())
            {
                it4 = synthshouseDust.erase(it4);
                delete s;
            }
            else
                it4++;
        }
    }
    
    maskFbo.end();
    
    // HERE the shader-masking happends
    //
    fbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent for default
    ofClear(0, 0, 0, 0);
    shader.begin();
    shader.setUniformTexture("maskTex", maskFbo.getTextureReference(), 1 );
    srcImg.draw(0,0);
    shader.end();
    fbo.end();
   
    houseDustX = ofRandom(0,ofGetWidth());
    houseDustY = ofRandom(0,ofGetHeight());
    
    synthshouseDust.push_back(new houseDust);
    synthshouseDust.back()->play();
    
    if (contourFinder2.nBlobs > 0) {
        sineHighX = contourFinder2.blobs[0].centroid.x;
        sineHighY = contourFinder2.blobs[0].centroid.y;
        if (bDustColor == true) {
            
            glitchSawX = houseDustX;
            glitchSawY = houseDustY;
        }
    }
    if ((bDustColor == true) || (contourFinder2.nBlobs > 0) ) {
        string comressedFilename = "compressed.jpg";
        glitch.allocate(640, 480, OF_IMAGE_COLOR);
        glitch.saveImage(comressedFilename,quality);
        ofBuffer file = ofBufferFromFile(comressedFilename);
        int fileSize = file.size();
        char * buffer = file.getBinaryBuffer();
        int whichByte = (int) ofRandom(fileSize);
        int whichBit  = ofRandom(8);
        char bitMask = 1 << whichBit;
        buffer[whichByte] |= bitMask;
        ofBufferToFile(comressedFilename, file);
        glitch.loadImage(comressedFilename);
    }
    
    timeshift += 2;
    if (timeshift == ofGetHeight()) {
        timeshift = 0;
    }
  */

    
    if(contourFinder2.nBlobs > 0)
    {
        contourAnalysis.simplify(contourFinder2.blobs[0].pts,simpleCountour,simpleAmount);
        fingersFound=fingerFinder.findFingers(contourFinder2.blobs[0]);
        handFound=fingerFinder.findHands(contourFinder2.blobs[0]);
        numFingerPoints= fingerFinder.fingerPoints.size();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    ofSetLineWidth(1);
    ofBackground(0);
    ofColor cyan = ofColor::fromHex(0x00abec);
    ofColor magenta_custom = ofColor::fromHex(0xfeeefe);
    
    if (bDustMask == false) {                       //========================================bGrayImage
        bHouseDustDraw = true;
        if (contourFinder.nBlobs > 0) {
             synthshouseDust[0]->houseDustVolume = 10;
            bBrushDown = true;
        }
        ofSetColor(magenta_custom);
       // ofLine(houseDustX, houseDustY, pathVertices.back().x, pathVertices.back().y);
    }
    
    if(contourFinder.nBlobs == 0){
        if(synthshouseDust.size() > 0)
        synthshouseDust[0]->houseDustVolume = 2;
    }
    
    ofSetColor(cyan,200);
   // pathLines.draw();
   
  if (pathVertices.size()> 2) {
        if (contourFinder.nBlobs == 0) {
           for (int i = 0; i < 2; i++) {
            pathVertices.pop_front();
           }
        }
   }
    
    if (bDustMask == true) {                            //=====================bGrayImage == true
        bHouseDustDraw = false;
        bBrushDown = false;
        synthshouseDust[0]->houseDustVolume = 0;
        magenta_custom = ofColor::fromHex(0x000000);
        if (contourFinder.nBlobs > 0) {
            bHouseDustDraw = true;
            synthshouseDust[0]->houseDustVolume= 3;
            vector<MySynth*>::iterator it = synths.begin();
            while (it != synths.end())
            {
                MySynth *s = *it;
                s->draw();
                
                if (!s->isAlive())
                {
                    it = synths.erase(it);
                    delete s;
                }
                else
                    it++;
            }
            for (int i = 0; i < synths.size()/5; i++)
                synths[i]->release();
            
            synths.push_back(new MySynth);
            synths.back()->play();
        }
        if(contourFinder.nBlobs > 1) {
            ofSetColor(100, 200, 200,230);
            ofLine(centroidX1, centroidY1, centroidX2, centroidY2);
            
            ofSetColor(200, 150, 150,200);
            vector<MySynth2*>::iterator it2 = synths2.begin();
            while (it2 != synths2.end())
            {
                MySynth2 *s = *it2;
                s->draw();
                if (!s->isAlive())
                {
                    it2 = synths2.erase(it2);
                    delete s;
                }
                else
                    it2++;
            }
            for (int i = 0; i < synths2.size()/5; i++)
                synths2[i]->release();
            synths2.push_back(new MySynth2);
            synths2.back()->play();
        }
        
        if(contourFinder2.nBlobs > 1){
            ofSetColor(255, 255, 255,40);
            vidGrabber.draw(0, 0, 640, 480);
            glEnable(GL_BLEND);
            ofSetColor(255*ofRandom(1.0),255*ofRandom(1.0),255*ofRandom(1.0),100);
            ofFill();
            ofTriangle(centroidX1, centroidY1, centroidX2, centroidY2, contourFinder2.blobs[0].centroid.x, contourFinder2.blobs[0].centroid.y);
            synthX3 = contourFinder2.blobs[0].centroid.x;
            synthY3 = contourFinder2.blobs[0].centroid.y;
            vector<MySynth3*>::iterator it3 = synths3.begin();
            while (it3 != synths3.end())
            {
                MySynth3 *s = *it3;
                s->draw();
                
                if (!s->isAlive())
                {
                    it3 = synths3.erase(it3);
                    delete s;
                }
                else
                    it3++;
            }
            for (int i = 0; i < synths3.size()/5; i++)
                synths3[i]->release();
            
            synths3.push_back(new MySynth3);
            synths3.back()->play();
        }
        ofSetColor(magenta_custom,alpha);
        for (int i = 0; i < pathVertices.size(); i++) {
            ofLine(synthshouseDust[0]->houseDustPositionX, synthshouseDust[0]->houseDustPositionY, pathVertices[i].x, pathVertices[i].y);
        }
    }//bGrayImage == true end
    
   
    ofSetColor(255, 255, 255);
    maskFbo.begin();
    ofClear(0,0,0,255);
    maskFbo.end();
    fbo.draw(0,0);
    
    if (bDustColor == true) {                             //========================================bDustColor
        ofSetLineWidth(2);
        synths1_2Volume = 0;
        synthshouseDust[0]->houseDustPositionX = centroidX1+ofRandom(-50,50);
        synthshouseDust[0]->houseDustPositionY = centroidY1+ofRandom(-240,240);

        if (contourFinder.nBlobs > 0 ) {
            vector<myLFSaw*>::iterator it7 = myLFSawsynths.begin();
            while (it7 != myLFSawsynths.end())
            {
                myLFSaw *s = *it7;
                s->draw();
                if (!s->isAlive())
                {
                    it7 = myLFSawsynths.erase(it7);
                    delete s;
                }
                else
                    it7++;
            }
           
            ofSetColor(255, 255, 255);
            
            myLFSawVolume = 2;
            
            ofSetColor(255, 255, 255, 100);
            vidGrabber.draw(0, 0, 640, 480);
        }
        
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        grayImage.draw(0,0,640,480);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        ofSetColor(255,200);
        synthshouseDust[0]->houseDustVolume= 0;
        
        myLFSawX = centroidX1;
        myLFSawY = centroidY1;
       
        myLFSawsynths.push_back(new myLFSaw);
        myLFSawsynths.back()->play();
        
        if (contourFinder.nBlobs == 0) {
            ofSetColor(255);
            ofLine(ofRandom(0,ofGetWidth()), timeshift, ofRandom(0,ofGetWidth()), timeshift);
        }

        if (contourFinder2.nBlobs > 0) {
            
            ofSetColor(255, 255, 255, 110);
            vidGrabber.draw(0, 0, 640, 480);
            
        }
        
        if(contourFinder2.nBlobs > 1){
            glEnable(GL_BLEND);
            ofSetColor(255*ofRandom(1.0),255*ofRandom(1.0),255*ofRandom(1.0),150);
            ofFill();
            glBegin(GL_POLYGON);
            glVertex2i(contourFinder2.blobs[0].centroid.x,contourFinder2.blobs[0].centroid.y);
            glVertex2i(synthshouseDust[0]->houseDustPositionX,synthshouseDust[0]->houseDustPositionY-75);
            glVertex2i(synthX1, synthY1);
            glEnd();
            
            vector<glitchSaw*>::iterator it6 = glitchSawsynths.begin();
            while (it6 != glitchSawsynths.end())
            {
                glitchSaw *s = *it6;
                //s->draw();
                
                if (!s->isAlive())
                {
                    it6 = glitchSawsynths.erase(it6);
                    delete s;
                }
                else
                    it6++;
            }
            glitchSawsynths.push_back(new glitchSaw);
            glitchSawsynths.back()->play();
            
            ofSetColor(255);
            glitch.draw(0,0,ofGetWidth(),ofGetHeight());
            
        }
    }
    
    if (bStart == false) {
        if (synthshouseDust.size() > 0) {
        synthshouseDust[0]->houseDustVolume = 0;
        }
        ofSetColor(255);
       // kinect.draw(0,0,640,480);
        //glBlendFunc(GL_DST_COLOR, GL_ZERO);
      //  grayImage.draw(0, 0,ofGetWidth(),ofGetHeight());
    }
    
    colorImg.draw(0,0,640,480);
    ofPushMatrix();
    ofPushStyle();
    if(fingersFound) fingerFinder.draw(0, 0);
    if(fingersFound) fingerFinder.draw(640, 0);
    if(handFound)fingerFinder.drawhands(640, 0);
    ofPopStyle();
    ofPopMatrix();
    
    if (fingerFinder.fingerPoints.size() > 0) {
    
    vector<MyUgenSynth*>::iterator it10 = MyUgenSynths.begin();
    while (it10 != MyUgenSynths.end())
    {
        MyUgenSynth *s = *it10;
     //   s->pos.x = ofGetMouseX();
     //   s->pos.y = ofGetMouseY();
        s->draw();
        
        if (!s->isAlive())
        {
            it10 = MyUgenSynths.erase(it10);
            delete s;
        }
        else
            it10++;
    }
    MyUgenSynths.push_back(new MyUgenSynth(fingerFinder.fingerPoints[0].x,fingerFinder.fingerPoints[0].y));
    MyUgenSynths.back()->play();
        
        vector<houseDust*>::iterator it4 = synthshouseDust.begin();
        while (it4 != synthshouseDust.end())
        {
            houseDust *s = *it4;
            s->draw();
            
            if (!s->isAlive())
            {
                it4 = synthshouseDust.erase(it4);
                delete s;
            }
            else
                it4++;
        }
        synthshouseDust.push_back(new houseDust(fingerFinder.fingerPoints[0].x,fingerFinder.fingerPoints[0].y));
        synthshouseDust.back()->play();
    }
    
    if (fingerFinder.fingerPoints.size() > 30) {
        vector<SineHIGH*>::iterator it9 = synthsSineHIGH.begin();
        while (it9 != synthsSineHIGH.end())
        {
            SineHIGH *s = *it9;
            s->draw();
            
            if (!s->isAlive())
            {
                it9 = synthsSineHIGH.erase(it9);
                delete s;
            }
            else
                it9++;
        }
        synthsSineHIGH.push_back(new SineHIGH(fingerFinder.fingerPoints[30].x,fingerFinder.fingerPoints[20].y));
        synthsSineHIGH.back()->play();
    }
    
    if (fingerFinder.fingerPoints.size() > 50) {
        vector<Noise*>::iterator it3 = synthsNoise.begin();
        while (it3 != synthsNoise.end())
        {
            Noise *s = *it3;
           // s->draw();
            
            if (!s->isAlive())
            {
                it3 = synthsNoise.erase(it3);
                delete s;
            }
            else
                it3++;
        }
        synthsNoise.push_back(new Noise(fingerFinder.fingerPoints[50].x,fingerFinder.fingerPoints[50].y));
        synthsNoise.back()->play();
        
        unsigned char pixels[tex_width*tex_height*4];
        
        for (int i = 0; i < tex_width*tex_height*4; i++)
        {
            pixels[i] = (int)(255 * ofRandomuf());
        }
        tex.loadData(pixels, tex_width,tex_height, GL_RGBA);
        ofSetColor(255, 255, 255,240);
        tex.draw(fingerFinder.fingerPoints[50].x-tex_width/2 ,fingerFinder.fingerPoints[50].y-tex_height/2);
    }
    
    


    
    mainOutputSyphonServer.publishScreen();
    
    
    ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr 
    << "threshold " << threshold << endl
     << "nearThreshold:" << nearThreshold << endl
    <<"farThreshold:"<< farThreshold << endl
    << "cF1 " << contourFinder.nBlobs << endl
    << "cF2 " << contourFinder2.nBlobs << endl
    <<"fps: " << ofGetFrameRate()<<endl
    <<"numFingerPoints: " << numFingerPoints ;
	ofDrawBitmapString(reportStr.str(), 20, 20);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
        case ';':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
        case 'v':
            vidGrabber.videoSettings();
            break;
        case 't':
			bThreshWithOpenCV = !bThreshWithOpenCV;
			break;
            
        case '>':
		case '.':
			farThreshold ++;
			if (farThreshold > 255) farThreshold = 255;
			break;
			
		case '<':
		case ',':
			farThreshold --;
			if (farThreshold < 0) farThreshold = 0;
			break;
        case '/':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
			break;
        case '_':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
        case 'g':
            bDustMask = !bDustMask;
            break;
        case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
        case 'd':
            bDustColor = !bDustColor;
			break;
        case 'z':
            bStart = !bStart;
            break;
        case 's':
            vidGrabber.videoSettings();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
