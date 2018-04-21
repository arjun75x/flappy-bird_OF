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
    
    ofImage background_image_;
    ofImage bird_falling_image_;
    ofImage bird_jumping_image_;
    ofImage pipe_down_image_;
    ofImage pipe_up_image_;
    ofImage name_image_;
    ofImage start_button_image_;
    
    //actual bird
    Bird bird_ = Bird(ofRectangle(50,200,20,20));
    
    //pipe the bird has to jump through, still needs to be implemented
    Pipe top_pipe_ = Pipe(ofRectangle(0,0,0,0));
    Pipe bottom_pipe_ = Pipe(ofRectangle(0,0,0,0));

    //Vector for top 10 scores
    std::vector<unsigned> top_scores_ = vector<unsigned>(10);
    
    //Current score
    unsigned score_ = 0;
    
    /**
     Function to update top score vector

     @param score score to add
     */
    void UpdateTopScores(unsigned);
    
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
     Function to check if a bird and pipe intersect
     */
    bool Intersect(Bird, Pipe);
    
    /**
     Function to check if pipe is out of bounds
     */
    bool OutOfBounds();
    
    /**
     Method to regenerate pipes each time
     */
    void GeneratePipes();
    
    /**
     Method to calculate speed of game based on score
     */
    double SpeedCalculator(double);
    
    
    /**
     Method to move pipes
     */
    void MovePipes();
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
};
