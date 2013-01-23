#include "particleset.h"
#include <iostream>
using namespace std;



ofMesh cube_mesh;
GLuint cube_dl;

void init_cube_mesh() {
    if (1) {
        cube_mesh.addVertex(ofVec3f(-0.5, -0.5, -0.5));
        cube_mesh.addVertex(ofVec3f(0.5, -0.5, -0.5));
        cube_mesh.addVertex(ofVec3f(0, -0.5, 0.5));
        cube_mesh.addVertex(ofVec3f(0, 0.5, 0));
        cube_mesh.addTriangle(0, 1, 2);
        cube_mesh.addTriangle(0, 1, 3);/*
        cube_mesh.addTriangle(0, 2, 3);
        cube_mesh.addTriangle(1, 2, 3);*/
    } else {
        for (float i = -0.5; i <= 0.5; i++) {
            for (float j = -0.5; j <= 0.5; j++) {
                for (float k = -0.5; k <= 0.5; k++) {
                    cube_mesh.addVertex(ofVec3f(i, j, k));
                }
            }
        }
        
        cube_mesh.addTriangle(0, 1, 2);
        cube_mesh.addTriangle(0, 1, 5);
        cube_mesh.addTriangle(0, 2, 6);
        cube_mesh.addTriangle(0, 4, 5);
        cube_mesh.addTriangle(0, 4, 6);
        cube_mesh.addTriangle(1, 2, 3);
        cube_mesh.addTriangle(1, 3, 5);
        cube_mesh.addTriangle(2, 3, 7);
        cube_mesh.addTriangle(2, 6, 7);
        cube_mesh.addTriangle(3, 5, 7);
        cube_mesh.addTriangle(4, 5, 7);
        cube_mesh.addTriangle(4, 6, 7);
    }
    
    cube_dl = glGenLists(1);
    glNewList(cube_dl, GL_COMPILE);
    cube_mesh.draw();
    glEndList();
}

pcParticleSet::pcParticleSet() {
}

void pcParticleSet::next() {
    char setstate;
    if (state_ == OPENED) {
        setstate = CLOSING;
        state_ = CLOSED;
    } else if (state_ == CLOSED) {
        setstate = OPENING;
        state_ = OPENED;
    }
    for (auto p = particles_.begin(); p != particles_.end(); p++) {
        p->state_ = setstate;
    }
    for (auto p = noise_.begin(); p != noise_.end(); p++) {
        p->state_ = state_;
        if (state_ == OPENED) {
            p->reset();
        }
    }
}

void pcParticleSet::draw() {
    ofSetColor(0, 200, 255, 128);
    for (auto p = particles_.begin(); p != particles_.end(); p++) {
        p->update();
        glPushMatrix();
        glTranslatef(p->x, p->y, p->z);
        glCallList(cube_dl);
        glPopMatrix();
    }
    for (auto p = noise_.begin(); p != noise_.end(); p++) {
        p->draw();
    }
    
    ofSetColor(0, 0, 10);
    disk_mesh_.draw();
}

long int pcParticleSet::size() const {
    return particles_.size();
}

pcParticleSet* loadParticleSet(const char* path) {
    pcParticleSet* s = new pcParticleSet();
    ifstream in(path);
    string line;
    float min_x = 0, max_x = 0;
    float min_y = 0, max_y = 0;
    float min_z = 0, max_z = 0;
    
    while (in.good() && !in.eof()) {
        getline(in, line);
        if (line[0] == 'v' && line[1] == ' ') {
            pcParticle particle;
            sscanf(line.c_str(), "v %f %f %f",
                   &(particle.tx), &(particle.ty), &(particle.tz));
            if (particle.tx < min_x) {
                min_x = particle.tx;
            }
            if (particle.tx > max_x) {
                max_x = particle.tx;
            }
            if (particle.ty < min_y) {
                min_y = particle.ty;
            }
            if (particle.ty > max_y) {
                max_y = particle.ty;
            }
            if (particle.tz < min_z) {
                min_z = particle.tz;
            }
            if (particle.tz > max_z) {
                max_z = particle.tz;
            }
            s->particles_.push_back(particle);
        }
    }
    
    for (auto p = s->particles_.begin(); p != s->particles_.end(); p++) {
        p->min_y = min_y - 10;
        p->max_y = max_y;
        p->init();
    }
    
    s->disk_center_ = ofVec3f((max_x - min_x) / 2. + min_x,
                              min_y + .1,
                              (max_z - min_z) / 2. + min_z);
    float r = 1.2 * sqrt(pow((max_x - min_x) / 2, 2) + pow((max_z - min_z) / 2, 2));
    s->disk_r_ = r;
    
    for (int i = 0; i < 800; i++) {
        pcNoiseParticle np;
        np.min_y = min_y;
        np.max_y = max_y;
        np.state_ = CLOSED;
        np.r = r;
        np.reset();
        s->noise_.push_back(np);
    }
    
    s->disk_mesh_.addVertex(s->disk_center_);
    ofVec3f radius_sweep(s->disk_r_, 0, 0);
    for (float theta = 0; theta <= 360; theta += 10) {
        s->disk_mesh_.addVertex(
            s->disk_center_ + radius_sweep.rotated(theta, ofVec3f(0, 1, 0)));
    }
    for (int i = 1; i <= 36; i++){
        s->disk_mesh_.addIndex(0);
        s->disk_mesh_.addIndex(i);
        s->disk_mesh_.addIndex((i % 37) + 1);
    }
    
    init_cube_mesh();
    printf("Loaded %ld particles\n", s->particles_.size());
    return s;
}