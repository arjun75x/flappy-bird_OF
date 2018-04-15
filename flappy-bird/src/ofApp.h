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
     // Current state of game
    GameState current_state_ = IN_PROGRESS;
    
    //actual bird, still needs to be implemented
    //Bird bird_;
    
    //pipe the bird has to jump through, still needs to be implemented
    //Pipe pipe_;

    //Vector for top 10 scores
    std::vector<unsigned> top_scores_ = vector<unsigned>(10); //vector for top scores
    
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
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
};
