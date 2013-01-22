#include "app.h"

void pcApp::setup() {
    mesh = loadParticleSet("/Users/haldean/Downloads/wave2.obj");
    
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0, 10, 20);
    
    shader.load("shader.vert", "shader.frag");
}

void pcApp::update() {
    //move the camera around the mesh
    float xRotateAmount = 20 + ofMap(ofGetMouseX(), 0, ofGetWidth(), 180, -180);
    float yRotateAmount = -10 + ofMap(ofGetMouseY(), 0, ofGetHeight(), 180, -180);
	ofVec3f camDirection(0,0,1);
	ofVec3f centre(0., 0., 0.);
	ofVec3f camDirectionRotated = camDirection.rotated(xRotateAmount, ofVec3f(0,1,0));
    camDirectionRotated = camDirectionRotated.rotated(yRotateAmount, ofVec3f(1,0,0));
	ofVec3f camPosition = centre + camDirectionRotated * 100;
	
	cam.setPosition(camPosition);
	cam.lookAt(centre);
}

void pcApp::draw() {
    shader.begin();
    cam.begin();
    ofSetColor(255, 255, 255);
    mesh->draw();
    cam.end();
    shader.end();
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