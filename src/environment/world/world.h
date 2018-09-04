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
#include "src/environment/world/base_type.h"
#include "src/environment/world/agent.h"
#include "src/environment/world/object.h"
#include "src/environment/world/road_network.h"
#include "src/proto/object.pb.h"
#include "src/proto/world.pb.h"

namespace environment {
namespace world {

class World {
public:


    World() : agent_count_(0) {};

    std::pair<bool, double> collides(int agent_id){
        if(environment::commons::disjoint<double, 2>(this->get_bounding_box(), this->get_agent(agent_id)->get_transformed_shape()))
            return std::make_pair(true, 0.0); 
            
        for (std::shared_ptr<BaseType> obj : objects_){
            if(this->get_agent(agent_id) != obj){
                std::shared_ptr<Agent> other_agent = std::dynamic_pointer_cast<Agent>(obj);
                if(other_agent != NULL){
                    if ( environment::commons::collides<double, 2>(other_agent->get_transformed_shape(), this->get_agent(agent_id)->get_transformed_shape()))
                        return std::make_pair(true, obj->get_reward());
                } else {
                    if ( environment::commons::collides<double, 2>(obj->get_shape(), this->get_agent(agent_id)->get_transformed_shape()))
                        return std::make_pair(true, obj->get_reward());
                }
            }
        }
        return std::make_pair(false, 0.0);
    }
    
    void reset(){
        objects_.clear();
        agent_count_ = 0;
        road_network_ = nullptr;
    };


    //! Setter
    void set_bounding_box(const Polygon_t<double, 2>& bb){ bounding_box_=bb; }
    
    void set_road_network(std::shared_ptr<RoadNetwork> rn){ road_network_ = rn; }

    void add_object(std::shared_ptr<BaseType> obj){
        obj->set_id(agent_count_);
        objects_.push_back(obj);
        agent_count_++;
    }


    //! Getter
    std::shared_ptr<RoadNetwork> get_road_network(){ return road_network_; }

    Polygon_t<double, 2>& get_bounding_box(){ return bounding_box_; }

    std::vector<std::shared_ptr<BaseType>> get_objects() { return objects_; }

    std::shared_ptr<Agent> get_agent(int agent_id){
        for (std::shared_ptr<BaseType> obj : objects_){
            if(obj->get_id() == agent_id){
                return std::dynamic_pointer_cast<Agent>(obj);
            }
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<Agent>> get_agents(){
        std::vector<std::shared_ptr<Agent>> agents;
        for (std::shared_ptr<BaseType> obj : objects_){
            std::shared_ptr<Agent> agent = std::dynamic_pointer_cast<Agent>(obj);
            if (agent != NULL)
                agents.push_back(agent);
        }
        return agents;
    }

private:
    std::vector<std::shared_ptr<BaseType>> objects_;
    std::shared_ptr<RoadNetwork> road_network_;

    Polygon_t<double, 2> bounding_box_;
    int agent_count_;

};

} // environment
} // world

#endif // _WORLD_H_