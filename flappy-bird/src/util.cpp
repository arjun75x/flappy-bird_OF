//
//  util.cpp
//  flappy-bird
//
//  Created by Arjun Arun on 4/30/18.
//

#include "util.hpp"

double SpeedCalculator(double score_) {
    if (score_ == 0) {
        return 1.2;
    } else if (score_ == 1) {
        return 1.5;
    } else if (score_ > 8){
        return SpeedCalculator(7) + SpeedCalculator(6) * .4;
    } else {
        return SpeedCalculator(score_ - 2) + SpeedCalculator(score_ - 1) * .4;
    }
}
