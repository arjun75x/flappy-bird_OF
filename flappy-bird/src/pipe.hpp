//
//  pipe.hpp
//  flappy-bird
//
//  Created by Arjun Arun on 4/17/18.
//

#ifndef pipe_hpp
#define pipe_hpp

#include <stdio.h>
#include "ofMain.h"

class Pipe {
public:
    ofRectangle body;
    Pipe(ofRectangle v) : body(v) {};
    
    /**
     Method to regenerate pipes each time
     */
    void GeneratePipes();
};

#endif /* pipe_hpp */
