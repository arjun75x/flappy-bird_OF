#pragma once

#include "ofMain.h"
#include "bird.hpp"
#include "pipe.hpp"

// Enum to represent the current state of the game
enum GameState {
    IN_PROGRESS = 0,
    PAUSED,
    FINISHED
};

class ofApp : public ofBaseApp{
private:
     //Current state of game
    GameState current_state_ = IN_PROGRESS;
    
    //actual bird
    Bird bird_ = Bird(ofRectangle(50,500,20,20));
    
    //pipe the bird has to jump through, still needs to be implemented
    Pipe pipe_ = Pipe(ofRectangle(1000,0,50,500));

    //Vector for top 10 scores
    std::vector<unsigned> top_scores_ = vector<unsigned>(10);
    
    //Current score
    unsigned score_ = 0;
    
    /**
     Function to update top score vector

     @param score score to add
     */
    void UpdateTopScores(int score);
    
    // A flag boolean used in the update() function
    bool should_update_ = true;
    
    /**
     Function to render bird on screen
     */
    void DrawBird();
    
    /**
     Function to render pipe on screen
     */
    void DrawPipe();
    
    /**
     Function to render game over screen
     */
    void DrawGameOver();
    
    /**
     Function to render game paused screen
     */
    void DrawGamePaused();
    
    /**
     Function to reset game objects to original state
     */
    void Reset();
    
    /**
     Function to check if two rectangles intersect
     */
    bool Intersect(ofRectangle one, ofRectangle two);
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
};
