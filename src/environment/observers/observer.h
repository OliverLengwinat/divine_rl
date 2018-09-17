/*
 * MIT License
 *
 * Copyright (c) 2018 Patrick Hart
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _OBSERVERS_H_
#define _OBSERVERS_H_

#include <algorithm>
#include <random>
#include "src/environment/world/world.h"
#include "src/environment/world/agent.h"

namespace environment {

//! fw decleration
namespace world {
    class World;
    class Agent;
}

namespace observers {

using namespace environment::world;


// the observer will be used to calculate the reward and state; collisions, however, are handled in the step function itself
class BaseObserver {
public:
BaseObserver(){};
virtual ~BaseObserver() = default;

void set_world(std::shared_ptr<World> w){ world_ = w; }
std::shared_ptr<World> get_world(){ return world_; }

virtual Matrix_t<double> convert_state(std::shared_ptr<Agent> a) = 0; // could be an image; trajectory etc.
virtual void convert_reward(StepReturn& step_return,std::shared_ptr<Agent> a) = 0;

Matrix_t<int> get_shape() const {return shape_;}
void set_shape(const Matrix_t<int>& shape){shape_=shape;}

private:
    std::shared_ptr<World> world_;
    Matrix_t<int> shape_;

};


} // observers
} // simulation


#endif