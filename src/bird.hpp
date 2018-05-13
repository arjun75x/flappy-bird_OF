//
//  bird.hpp
//  flappy-bird
//
//  Created by Arjun Arun on 4/17/18.
//

#ifndef bird_hpp
#define bird_hpp

#include <stdio.h>
#include "ofMain.h"

class Bird {
public:
    ofRectangle body;
    Bird(ofRectangle v) : body(v) {};
};

#endif /* bird_hpp */
