#pragma once

#include "ofMain.h"
#include "bird.hpp"
#include "pipe.hpp"

// Enum to represent the current state of the game
enum GameState {
    START,
    FALLING,
    JUMP,
    PAUSED,
    FINISHED
};

class ofApp : public ofBaseApp{
private:
    
    GameState current_state_ = START;
    
    //Images for game
    ofImage background_image_;
    ofImage bird_falling_image_;
    ofImage bird_jumping_image_;
    ofImage pipe_down_image_;
    ofImage pipe_up_image_;
    ofImage name_image_;
    ofImage start_button_image_;
    
    //Sounds for game
    ofSoundPlayer jump_sound_;
    ofSoundPlayer intersect_sound_;
    
    //Bird of game
    Bird bird_ = Bird(ofRectangle(50,200,20,20));
    
    //Pipes bird has to jump through
    Pipe top_pipe_ = Pipe(ofRectangle(0,0,0,0));
    Pipe bottom_pipe_ = Pipe(ofRectangle(0,0,0,0));

    //Vector for top 10 scores
    std::vector<unsigned> top_scores_ = vector<unsigned>(10);
    
    //Current score
    unsigned score_ = 0;
    
    //Count for jumping animations
    unsigned jump_count = 0;
    
    /**
     Function to render start screen
     */
    void DrawStart();
    
    /**
     Function to render bird on screen
     */
    void DrawBird();
    
    /**
     Function to render pipes on screen
     */
    void DrawPipes();
    
    /**
     Function to render game over screen with top scores
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
     Method to regenerate pipes each time
     */
    void GeneratePipes();
    
    /**
     Method to move pipes along screen
     */
    void MovePipes();
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    /**
     Method to calculate speed of game based on score
     */
    double SpeedCalculator(double score);
    
    /**
     Function to check if pipe is out of bounds
     */
    bool OutOfBounds();
    
    /**
     Function to check if a bird and pipe intersect
     */
    bool Intersect(Bird, Pipe);
    
    /**
     Function to update top score vector
     */
    void UpdateTopScores(unsigned score);
};
