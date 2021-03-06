#ifndef MODULE_H
#define MODULE_H

#include "ofMain.h"
#include "ModuleConsole.h"
#include "Particle.h"
#ifdef TARGET_OF_IOS
#include "ofxCocosDenshion.h"
#endif

class Module {

public:

    Module(int index, int x, int y, int width, int height, int maxPopulation, vector<string> soundPaths);

    void loadSounds(vector<string> paths);
    void unloadSounds();
    void update();
    void addParticle(int life, int x, int y);
    void eraseParticle();

    void draw();
    void drawBackground();
    void drawGrid();
    void drawBorders();
    void drawParticles();
    void drawChangeInstrumentButtons();

    void playSound(int index, float vol);
    void prepareInstrumentChange(int direction);
	void changeInstrument(int index);

	int getX0()                      { return x0; }
	int getX1()                      { return x1; }
	int getIndex()                   { return index; }
	int getWidth()                   { return width; }
	int getHeight()                  { return height; }
	float getSpeed()                 { return console->getSpeed(); }
	bool isFreezed()                 { return console->isFreezed(); }
	bool isLooping()                 { return console->isLooping(); }
	bool isGravityOn()               { return console->isGravityOn(); }
    int getNumberOfInstrumentNotes() { return numberOfInstruments; }
	bool anyParticles()              { return particles.size() > 0; }
	void removeParticle()            { particles.erase(particles.end() - 1); }

    void setDimensions(int x, int y, int width, int height);
    void updateParticlesOnOrientationChange();

    void touchDown(ofTouchEventArgs& event);

    void removeAllParticles()        { particles.clear(); }
    void removeParticle(int i)       { particles.erase(particles.end() + i); }
    void setParticles(vector<Particle> particles) { this->particles = particles; }

    int getNumberOfParticles()       { return particles.size(); }
    vector<Particle> getParticles()  { return particles; }
    Particle* getParticle(int i)     { return &particles[i]; }
    Particle getParticleObj(int i)   { return particles[i]; }
    bool isFull()                    { return particles.size() == maxPopulation; }
    bool isNotFull()                 { return !isFull();}
    void activate()                  { this->active = true; }
    void deactivate()                { this->active = false; }
    bool isActive()                  { return this->active; }

    void resetFaderSpeed()           { console->resetFaderSpeed(); }
    void unfreeze()                  { console->unfreeze(); }
    void enableGravity()             { console->enableGravity(); }

    void addParticle(Particle p)     { this->particles.push_back(p); }

private:

    int x0, x1;
    int y;
    int index;
    int iSoundPaths;
    int width;
    int height;
    int consoleHeight;
	int maxPopulation;
    int numberOfInstruments;
	ModuleConsole* console;
    
	vector<Particle> particles;
#ifdef TARGET_OF_IOS
    vector<ofxCocosDenshion> sounds;
#else
    vector<ofSoundPlayer> sounds;
#endif
    
    bool active;


    ofRectangle previousInstrumentRect;
    ofRectangle nextInstrumentRect;

};

#endif
