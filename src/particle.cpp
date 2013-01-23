#include "particleset.h"

pcParticle::pcParticle() {
    t_offset_ = rand() % 120;
    state_ = CLOSED;
}

void pcParticle::init() {
    x = tx;
    y = min_y;
    z = tz;
    wait = max_y - ty;
}

void pcParticle::waitstep(float at_y) {
    wait -= 5;
    
    t_offset_++;
    if (t_offset_ == 120) t_offset_ = 0;
    float y_offset = t_offset_ / 40.;
    y = y_offset + at_y;
}

void pcParticle::update() {
    float step = 7.;
    if (state_ == OPENING) {
        if (wait > 0) {
            waitstep(min_y);
            if (wait > 0) return;
        }
        if (y < ty) {
            y += fmin(step, ty - y);
        } else {
            state_ = OPENED;
        }
    } else if (state_ == OPENED) {
        waitstep(ty);
        wait = ty - min_y;
    } else if (state_ == CLOSING) {
        if (wait > 0) {
            waitstep(ty);
            if (wait > 0) return;
        }
        
        if (y > min_y) {
            y -= fmin(step + 2, y - min_y);
        } else {
            state_ = CLOSED;
        }
    } else if (state_ == CLOSED) {
        waitstep(min_y);
        wait = max_y - ty;
    }
}

void pcParticle::draw() {
}

void pcNoiseParticle::reset() {
    start = center + ofVec3f(0, ofRandom(min_y, max_y), 0);
    current = start;
    wait = (int) ((start.y - min_y) / 4. + ofRandom(max_y - min_y) / 2);
    float theta = ofRandom(360);
    end = start + ofVec3f(r, 0, 0).rotated(theta, ofVec3f(0, 1, 0));
}

void pcNoiseParticle::update() {
    if (wait > 0) {
        wait--;
        return;
    }
    if (state_ == CLOSED && (current - start).length() < 0.01) return;
    current += (end - current) / 10;
    if (state_ == OPENED) {
        ofVec3f d = (end - current);
        if (d.length() < 0.1) reset();
        wait = 0;
    }
}

void pcNoiseParticle::draw() {
    update();
    
    float dist_edge = ofClamp((end - current).length() / 4, 0, 1);
    float dist_center = ofClamp((current - start).length(), 0, 1);
    float dist = dist_edge * dist_center;
    ofSetColor(0, dist * 80, dist * 150);
    
    float edge_size = .3;
    ofTriangle(current.x, current.y, current.z,
               current.x + edge_size, current.y, current.z,
               current.x, current.y + edge_size, current.z + edge_size);
}