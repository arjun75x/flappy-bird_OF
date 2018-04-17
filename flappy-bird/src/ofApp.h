#pragma once

#include "ofMain.h"

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
    
    //actual bird, still needs to be implemented
    ofRectangle bird_ = ofRectangle(50,500,20,20);
    
    //pipe the bird has to jump through, still needs to be implemented
    ofRectangle pipe_ = ofRectangle(1000,0,50,500);

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
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
};
