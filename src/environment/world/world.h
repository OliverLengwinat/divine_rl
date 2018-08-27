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
#ifndef _WORLD_H_
#define _WORLD_H_
#include <vector>
#include "src/environment/commons/common.h"
#include "src/environment/commons/utilities.h"
#include "src/environment/world/agent.h"
#include "src/environment/world/object.h"
#include "src/proto/object.pb.h"
#include "src/proto/world.pb.h"

namespace environment {
namespace world {

class World {
public:


    World() : agent_count_(0) {};

    bool load_proto(const std::string& data){
        divine::World world_info;
        world_info.ParseFromString(data);
        world_info_ = world_info;
        this->parse_proto();
        return true;
    }

    // TODO: initialize from proto
    bool parse_proto();

    void add_object(std::shared_ptr<BaseType> obj){
        obj->set_id(agent_count_);
        objects_.push_back(obj);
        agent_count_++;
    }

    // TODO: get agents
    std::vector<std::shared_ptr<Agent>> get_agents(){
        std::vector<std::shared_ptr<Agent>> agents;
        for (std::shared_ptr<BaseType> obj : objects_){
            std::shared_ptr<Agent> agent = std::dynamic_pointer_cast<Agent>(obj);
            if (agent != NULL)
                agents.push_back(agent);
        }
        return agents;
    }

    std::pair<bool, double> collides(std::shared_ptr<Agent> agent){
        for (std::shared_ptr<BaseType> obj : objects_){
            if(agent != obj){
                if ( environment::commons::collides<double, 2>(obj->get_shape(), agent->get_transformed_shape()) )
                    return std::make_pair(true, obj->get_reward());
            }
        }
        return std::make_pair(false, 0.0);
    }

    std::shared_ptr<Agent> get_agent(uint agent_id){
        for (std::shared_ptr<BaseType> obj : objects_){
            if(obj->get_id() == agent_id){
                return std::dynamic_pointer_cast<Agent>(obj);
            }
        }
        return nullptr;
    }

    void reset(){
        objects_.clear();
        lines_.clear();
        agent_count_ = 0;
        parse_proto();
    }


    std::vector<std::shared_ptr<BaseType>> get_objects() { return objects_; }

private:
    std::vector<std::shared_ptr<BaseType>> objects_; // list of base objects
    std::vector<std::shared_ptr<Linestring_t<double, 2>>> lines_;
    divine::World world_info_;
    uint agent_count_;
};

} // environment
} // world

#endif // _WORLD_H_