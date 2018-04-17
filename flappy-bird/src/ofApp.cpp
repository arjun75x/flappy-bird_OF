#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowTitle("Flappy Bird");
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    ofSetWindowShape(1000, 1000);
    ofSetWindowPosition(0, 0);
};

void ofApp::update(){
    if (should_update_) {
        if (current_state_ == IN_PROGRESS) {
            pipe_.body.setX(pipe_.body.getX() - 1);
            bird_.body.setY(bird_.body.getY() + 1);
            if (Intersect(pipe_.body, bird_.body)) {
                current_state_ = FINISHED;
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
    DrawPipe();
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
            bird_.body.setY(bird_.body.getY() - 15);
            DrawBird();
            update();
            should_update_ = false;
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

void ofApp::DrawPipe() {
    ofDrawRectangle(pipe_.body);
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
    current_state_ = IN_PROGRESS;
    bird_ = ofRectangle(0,1000,20,20);
    pipe_ = ofRectangle(1000,0,50,500);
};

bool ofApp::Intersect(ofRectangle one, ofRectangle two) {
    return ((two.getY() >= one.getMinY() && two.getY() <= one.getMaxY()) &&
            (two.getX() >= one.getMinX() && two.getX() <= one.getMaxX()));
};
