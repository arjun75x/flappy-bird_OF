#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowTitle("Flappy Bird");
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    ofSetWindowShape(500, 500);
    ofSetWindowPosition(0, 0);
};


void ofApp::update(){
    if (should_update_) {
        if (current_state_ == IN_PROGRESS) {
            pipe_one_.body.setX(pipe_one_.body.getX() - SpeedCalculator(score_));
            pipe_two_.body.setX(pipe_one_.body.getX() - SpeedCalculator(score_));
            bird_.body.setY(bird_.body.getY() + 2);
            if (Intersect(bird_, pipe_one_) || Intersect(bird_, pipe_two_)) {
                current_state_ = FINISHED;
            }
            if (OutOfBounds()) {
                GeneratePipes();
            }
        }
    }
    
    should_update_ = true;
};

void ofApp::draw(){
    if(current_state_ == PAUSED) {
        DrawGamePaused();
    }
    else if(current_state_ == FINISHED) {
        DrawGameOver();
    }
    DrawBird();
    DrawPipes();
};

void ofApp::keyPressed(int key){
    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }
    int upper_key = toupper(key);
    
    if (upper_key == 'P' && current_state_ != FINISHED) {
        current_state_ = (current_state_ == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
    }
    else if (current_state_ == IN_PROGRESS) {
        if (upper_key == 'B') {
            bird_.body.setY(bird_.body.getY() - 25);
            DrawBird();
        }
    }
    else if (upper_key == 'R' && current_state_ == FINISHED) {
        Reset();
    }
};

void ofApp::UpdateTopScores(int score) {
    for (int i = 0; i < top_scores_.size(); i++) {
        if (score > top_scores_[i]) {
            int temp = top_scores_[i];
            top_scores_[i] = score;
            UpdateTopScores(temp);
            break;
        }
    }
};

void ofApp::DrawBird() {
    ofDrawRectangle(bird_.body);
};

void ofApp::DrawPipes() {
    ofDrawRectangle(pipe_one_.body);
    ofDrawRectangle(pipe_two_.body);
};

void ofApp::DrawGameOver() {
    string score_string = std::to_string(score_);
    string lose_message = "You Lost! Final Score: " + score_string;
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(lose_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
};

void ofApp::DrawGamePaused() {
    string pause_message = "P to Unpause!";
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
};

void ofApp::Reset() {
    score_ = 0;
    current_state_ = IN_PROGRESS;
    bird_ = Bird(ofRectangle(50,200,20,20));
    GeneratePipes();
};

bool ofApp::Intersect(Bird bird, Pipe pipe) {
    return bird.body.intersects(pipe.body);
};

bool ofApp::OutOfBounds() {
    return pipe_one_.body.getMinX() < 0;
};

void ofApp::GeneratePipes() {
    score_++;
    int random = ofRandom(100, 250);
    pipe_one_ = Pipe(ofRectangle(500,0,50,random));
    pipe_two_ = Pipe(ofRectangle(500,500 - random + 40,50,500 - random));
}

double ofApp::SpeedCalculator(double score_) {
    if (score_ == 0) {
        return .9;
    } else if (score_ == 1) {
        return 1.0;
    } else if (score_ > 7){
        return SpeedCalculator(6) + SpeedCalculator(5) * .7;
    } else {
        return SpeedCalculator(score_ - 2) + SpeedCalculator(score_ - 1) * .7;
    }
}
