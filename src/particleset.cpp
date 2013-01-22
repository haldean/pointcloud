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
    update();
    ofSetColor(0, 200, 255);
    float edge_size = .2;
    ofTriangle(x, y, z,
               x + edge_size, y, z,
               x, y + edge_size, z + edge_size);
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
}

void pcParticleSet::draw() {
    for (auto p = particles_.begin(); p != particles_.end(); p++) {
        p->draw();
    }
}

long int pcParticleSet::size() const {
    return particles_.size();
}

pcParticleSet* loadParticleSet(const char* path) {
    pcParticleSet* s = new pcParticleSet();
    ifstream in(path);
    string line;
    float x, y, z;
    float min_y = 0;
    float max_y = 0;
    
    while (in.good() && !in.eof()) {
        getline(in, line);
        if (line[0] == 'v' && line[1] == ' ') {
            pcParticle particle;
            sscanf(line.c_str(), "v %f %f %f",
                   &(particle.tx), &(particle.ty), &(particle.tz));
            if (particle.ty < min_y) {
                min_y = particle.ty;
            }
            if (particle.ty > max_y) {
                max_y = particle.ty;
            }
            s->particles_.push_back(particle);
        }
    }
    
    for (auto p = s->particles_.begin(); p != s->particles_.end(); p++) {
        p->min_y = min_y - 10;
        p->max_y = max_y;
        p->init();
    }
    
    printf("Loaded %ld particles\n", s->particles_.size());
    return s;
}