#include "app.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	ofSetupOpenGL(&window, 500, 500, OF_WINDOW);
	ofRunApp(new pcApp()); // start the app
}
