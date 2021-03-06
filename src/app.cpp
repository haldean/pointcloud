#include "app.h"

void pcApp::setup() {
    mesh = loadParticleSet("/Users/haldean/Downloads/walt.obj");
    
    glEnable(GL_DEPTH_TEST);
    
    ofEnableAlphaBlending();
    //ofEnableSmoothing();
    //ofEnableBlendMode(ofBlendMode(OF_BLENDMODE_SCREEN));
    
    ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofBackground(0, 10, 20);
    
    img.setUseTexture(false);
    img.allocate(ofGetWindowWidth(), ofGetWindowHeight(), OF_IMAGE_COLOR_ALPHA);
    
    frame = 0;
    capture = false;
}

void pcApp::update() {
    //move the camera around the mesh
    float xRotateAmount = 20 + ofMap(ofGetMouseX(), 0, ofGetWidth(), 180, -180);
    float yRotateAmount = -10;// + ofMap(ofGetMouseY(), 0, ofGetHeight(), 180, -180);
	ofVec3f camDirection(0, 0, 150);
	ofVec3f centre(0., 0., 0.);
	ofVec3f camDirectionRotated;
    camDirectionRotated = camDirectionRotated.rotated(yRotateAmount, ofVec3f(1, 0, 0));
    camDirectionRotated = camDirection.rotated(xRotateAmount, ofVec3f(0, 1, 0));
	ofVec3f camPosition = centre + camDirectionRotated;
	
	cam.setPosition(camPosition);
	cam.lookAt(centre);
}

void pcApp::draw() {
    cam.begin();
    ofSetColor(255, 255, 255);
    mesh->draw();
    cam.end();
    
    if (capture) {
        stringstream outf;
        outf << "/Users/haldean/Desktop/pc/frame" << setfill('0') << setw(6) << frame++ << ".png";
        img.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        img.update();
        img.saveImage(outf.str());
    }
}

void pcApp::load(string& file) {
    
}

void pcApp::keyPressed(int key){
}

void pcApp::keyReleased(int key){
    mesh->next();
}

void pcApp::mouseMoved(int x, int y){

}

void pcApp::mouseDragged(int x, int y, int button){

}

void pcApp::mousePressed(int x, int y, int button){

}

void pcApp::mouseReleased(int x, int y, int button){

}

void pcApp::windowResized(int w, int h){

}

void pcApp::gotMessage(ofMessage msg){

}

void pcApp::dragEvent(ofDragInfo dragInfo){ 

}