#include "ofApp.h"

//constants
const unsigned kWidth = 288;
const unsigned kHeight = 512;

void ofApp::setup(){
    //Setup window
    ofSetWindowTitle("Flappy Bird");
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    ofSetWindowShape(kWidth, kHeight);
    
    //Load images
    background_image_.load("graphics/background.png");
    bird_falling_image_.load("graphics/bird_falling.png");
    bird_jumping_image_.load("graphics/bird_jumping.png");
    pipe_down_image_.load("graphics/pipe_down.png");
    pipe_up_image_.load("graphics/pipe_up.png");
    start_button_image_.load("graphics/start.png");
    name_image_.load("graphics/name.png");
    
    //Load sounds
    jump_sound_.load("sounds/sfx_wing.wav");
    intersect_sound_.load("sounds/sfx_hit.wav");
}

void ofApp::update(){
    if (current_state_ == FALLING) {
        MovePipes();
        bird_.body.setY(bird_.body.getY() + 2 + (bird_.body.getY() * .007));
        
        if (Intersect(bird_, top_pipe_) || Intersect(bird_, bottom_pipe_)) {
            intersect_sound_.play();
            UpdateTopScores(score_ - 1);
            current_state_ = FINISHED;
        }
        if (top_pipe_.body.getMinX() < 0) {
            GeneratePipes();
        }
    } else if (current_state_ == JUMP) {
        MovePipes();
        bird_.body.setY(bird_.body.getY() - 5);
        jump_count++;
        if (jump_count == 10) {
            jump_sound_.play();
            current_state_ = FALLING;
            jump_count = 0;
        }
        
        if (Intersect(bird_, top_pipe_) || Intersect(bird_, bottom_pipe_)) {
            UpdateTopScores(score_ - 1);
            current_state_ = FINISHED;
            intersect_sound_.play();
        }
        if (top_pipe_.body.getMinX() < 0) {
            GeneratePipes();
        }
    }
}

void ofApp::draw(){
    background_image_.draw(0, 0, kWidth, kHeight);
    if (current_state_ == START) {
        DrawStart();
    } else if (current_state_ == PAUSED) {
        DrawGamePaused();
    } else if (current_state_ == JUMP || current_state_ == FALLING) {
        DrawBird();
        DrawPipes();
    } else if (current_state_ == FINISHED) {
        DrawGameOver();
    }
}

//Some code adapted from of_snake application
void ofApp::keyPressed(int key){
    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }
    
    int upper_key = toupper(key);
    if (upper_key == 'P' && current_state_ != FINISHED) {
        current_state_ = (current_state_ == FALLING) ? PAUSED : FALLING;
    } else if (current_state_ == FALLING) {
        if (upper_key == ' ') {
            current_state_ = JUMP;
        }
    } else if (current_state_ == START) {
        if (upper_key == 'V') {
            current_state_ = FALLING;
        }
    } else if (upper_key == 'R' && current_state_ == FINISHED) {
        Reset();
    }
}

void ofApp::DrawBird() {
    bird_falling_image_.draw(bird_.body);
}

void ofApp::DrawPipes() {
    pipe_down_image_.draw(top_pipe_.body);
    pipe_up_image_.draw(bottom_pipe_.body);
}

//Some code adapted from of_snake application
void ofApp::DrawGameOver() {
    string score_string = std::to_string(score_ - 1);
    string message = "You Lost! Final Score: " + score_string;
    stringstream out;
    out << endl;
    out << "Top Scores: " << endl;
    for (int i = 0 ; i < top_scores_.size(); i++) {
        out << i + 1 << ". " << top_scores_[i] << endl;
    }
    message += out.str();
    ofDrawBitmapString(message, kWidth/2 - 90, kHeight/2 - 150);
    
    string restart = "Press R to restart!";
    ofDrawBitmapString(restart, kWidth/2 - 70, kHeight/2 + 40);
}

void ofApp::DrawStart() {
    name_image_.draw(kWidth/2 - name_image_.getWidth()/2, kHeight/2 - 50);
    start_button_image_.draw(kWidth/2 - start_button_image_.getWidth()/2, kHeight/2 + 50);
    ofDrawBitmapString("Instructions:", kWidth/2 - start_button_image_.getWidth()/2 - 5, kHeight/2 + 150);
    ofDrawBitmapString("Press the space bar to jump", kWidth/2 - start_button_image_.getWidth()/2 - 50, kHeight/2 + 170);
    ofDrawBitmapString("Press P pause the game!", kWidth/2 - start_button_image_.getWidth()/2 - 50, kHeight/2 + 190);
    ofDrawBitmapString("Press V to start the game!", kWidth/2 - start_button_image_.getWidth()/2 - 50, kHeight/2 + 210);
}

void ofApp::DrawGamePaused() {
    string pause_message = "P to Unpause!";
    ofDrawBitmapString(pause_message, start_button_image_.getWidth()/2 + 35, kHeight/2 - 40);
}

void ofApp::Reset() {
    score_ = 0;
    current_state_ = FALLING;
    bird_ = Bird(ofRectangle(50,200,20,20));
    GeneratePipes();
}

bool ofApp::Intersect(Bird bird, Pipe pipe) {
    return bird.body.intersects(pipe.body);
}

bool ofApp::OutOfBounds() {
    return top_pipe_.body.getMinX() < 0;
}

void ofApp::GeneratePipes() {
    score_++;
    int random = ofRandom(100, 250);
    top_pipe_ = Pipe(ofRectangle(kWidth,0,50,random));
    bottom_pipe_ = Pipe(ofRectangle(kWidth,kHeight - random + 50,50,kHeight - random));
}

void ofApp::MovePipes() {
    top_pipe_.body.setX(top_pipe_.body.getX() - SpeedCalculator(score_));
    bottom_pipe_.body.setX(top_pipe_.body.getX() - SpeedCalculator(score_));
}

void ofApp::UpdateTopScores(unsigned score) {
    for (int i = 0; i < top_scores_.size(); i++) {
        if (score > top_scores_[i]) {
            int temp = top_scores_[i];
            top_scores_[i] = score;
            UpdateTopScores(temp);
            break;
        }
    }
}
