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

class pcParticleSet {
public:
    pcParticleSet();
    void draw();
    void next();
    long int size() const;
    friend pcParticleSet* loadParticleSet(const char* path);
    
private:
    vector<pcParticle> particles_;
    char state_;
};

pcParticleSet* loadParticleSet(const char* path);