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

// TODO: randomize sample use consistant seed!
class ReplayMemory {
public:
    ReplayMemory() : max_sample_size(5000) {};
    void push_back(const StateHistory s){
        replay_memory_.push_back(s);
        if(replay_memory_.size() > max_sample_size){
            replay_memory_.pop_front();
        }
    }

    std::vector<StateHistory> sample(size_t N){
        std::vector<StateHistory> ret;
        // TODO: make random
        for(int i = 0; i < std::min(N, replay_memory_.size()); ++i ){
            ret.push_back(replay_memory_[i]);
        }
        return ret;
    }

private:
    std::deque< StateHistory > replay_memory_;
    int max_sample_size;
};


class BaseObserver {
public:
BaseObserver(){};
virtual ~BaseObserver() = default;

void set_world(std::shared_ptr<World> w){ world_ = w; }
std::shared_ptr<World> get_world(){ return world_; }

virtual void observe_(std::pair<int, StateHistory> s) = 0;

// TODO: always call observer from the base class and access a private function of the child
virtual std::pair<int, StateHistory> observe(std::pair<int, StateHistory> s){
    std::shared_ptr<Agent> agent = get_world()->get_agent(s.first);
    std::pair<bool, double> status = get_world()->collides(agent);
    this->observe_(s);
    s.second.is_final = status.first;
    s.second.reward = status.second;
    memorize(s.second);
    return s;
}

ReplayMemory& get_replay_memory() { return replay_memory_; }
void set_replay_memory() { }
void memorize(const StateHistory s){ replay_memory_.push_back(s); }

private:
    std::shared_ptr<World> world_;
    ReplayMemory replay_memory_;
};


} // observers
} // simulation


#endif