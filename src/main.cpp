#include "app.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	ofSetupOpenGL(&window, 750, 750, OF_FULLSCREEN);
	ofRunApp(new pcApp()); // start the app
}
