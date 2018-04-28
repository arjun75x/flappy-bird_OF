#include "ofApp.h"
const unsigned kWidth = 288;
const unsigned kHeight = 512;
unsigned kJumpCount = 0;

void ofApp::setup(){
    ofSetWindowTitle("Flappy Bird");
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    ofSetWindowShape(kWidth, kHeight);
    background_image_.load("graphics/background.png");
    bird_falling_image_.load("graphics/bird_falling.png");
    bird_jumping_image_.load("graphics.bird_jumping.png");
    pipe_down_image_.load("graphics/pipe_down.png");
    pipe_up_image_.load("graphics/pipe_up.png");
    start_button_image_.load("graphics/start.png");
    name_image_.load("graphics/name.png");
}

void ofApp::update(){
    if (current_state_ == FALLING) {
        MovePipes();
        bird_.body.setY(bird_.body.getY() + 2 + bird_.body.getY()*.005);
        if (Intersect(bird_, top_pipe_) || Intersect(bird_, bottom_pipe_)) {
            UpdateTopScores(score_ - 1);
            current_state_ = FINISHED;
        }
        if (top_pipe_.body.getMinX() < 0) {
            GeneratePipes();
        }
    } else if (current_state_ == JUMP) {
        MovePipes();
        bird_.body.setY(bird_.body.getY() - 5);
        kJumpCount++;
        if (kJumpCount == 10) {
            current_state_ = FALLING;
            kJumpCount = 0;
        }
        if (Intersect(bird_, top_pipe_) || Intersect(bird_, bottom_pipe_)) {
            UpdateTopScores(score_ - 1);
            current_state_ = FINISHED;
        }
        if (top_pipe_.body.getMinX() < 0) {
            GeneratePipes();
        }
    }
}

//add score to top right corner
void ofApp::draw(){
    background_image_.draw(0, 0, kWidth, kHeight);
    if (current_state_ == START) {
        DrawStart();
    } else if (current_state_ == PAUSED) {
        DrawGamePaused();
    } else if (current_state_ == JUMP) {
        DrawBird();
        DrawPipes();
    } else if (current_state_ == FALLING) {
        DrawBird();
        DrawPipes();
    } else if (current_state_ == FINISHED) {
        DrawGameOver();
    }
}

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
    ofDrawBitmapString(message, kWidth/2 - 80, kHeight/2);
}

void ofApp::DrawStart() {
    name_image_.draw(kWidth/2 - name_image_.getWidth()/2, kHeight/2 - 50);
    start_button_image_.draw(kWidth/2 - start_button_image_.getWidth()/2, kHeight/2 + 50);
}

void ofApp::DrawGamePaused() {
    string pause_message = "P to Unpause!";
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
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

double ofApp::SpeedCalculator(double score_) {
    if (score_ == 0) {
        return 1.2;
    } else if (score_ == 1) {
        return 1.5;
    } else if (score_ > 7){
        return SpeedCalculator(6) + SpeedCalculator(5) * .4;
    } else {
        return SpeedCalculator(score_ - 2) + SpeedCalculator(score_ - 1) * .4;
    }
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

void ofApp::MovePipes() {
    top_pipe_.body.setX(top_pipe_.body.getX() - SpeedCalculator(score_));
    bottom_pipe_.body.setX(top_pipe_.body.getX() - SpeedCalculator(score_));
}
