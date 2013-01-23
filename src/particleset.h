#pragma once

#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <vector>
#include "ofMain.h"

#define CLOSED 0
#define OPENING 1
#define OPENED 2
#define CLOSING 3

// must be called before drawing pcParticles
void init_cube_mesh();

class pcParticle {
public:
    pcParticle();
    
    float x, y, z, tx, ty, tz, wait, min_y, max_y;
    char state_;
    int t_offset_;
    
    void init();
    void draw();
    void update();
    
    void waitstep(float at_y);
};

class pcNoiseParticle {
public:
    ofVec3f start, current, center, end;
    float max_y, min_y, r;
    int wait;
    char state_;
    void draw();
    void update();
    void reset();
};

class pcParticleSet {
public:
    void draw();
    void next();
    long int size() const;
    friend pcParticleSet* loadParticleSet(const char* path);
    
private:
    pcParticleSet();
    
    ofMesh disk_mesh_;
    ofVec3f disk_center_;
    float disk_r_;
    vector<pcParticle> particles_;
    vector<pcNoiseParticle> noise_;
    char state_;
};

pcParticleSet* loadParticleSet(const char* path);