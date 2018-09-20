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

#ifndef _WORLD_BASE_TYPE_H_
#define _WORLD_BASE_TYPE_H_

#include "src/environment/commons/common.h"
#include "src/proto/commons.pb.h"

namespace environment {
namespace world {

class World;

using namespace environment::commons;

class BaseType {
public:
    BaseType() : shape_offset_(PointNd_t<double, 2>(0,0)), id_(0), reward_(0.0) {};
    
    virtual ~BaseType() = default;

    //! Setter
    /**
     * @brief Set the id object
     * 
     * @param id 
     */
    void set_id(int id){id_=id;};

    /**
     * @brief Set the type object
     * 
     * @param type 
     */
    void set_type(int type){ type_=type; };

    /**
     * @brief Set the reward object
     * 
     * @param reward 
     */
    void set_reward(double reward){reward_=reward;};

    /**
     * @brief Set the shape object
     * 
     * @param s 
     */
    void set_shape(const Polygon_t<double, 2>& s){ shape_ = s; };

    /**
     * @brief Set the shape offset object
     * 
     * @param s 
     */
    void set_shape_offset(const PointNd_t<double, 2>& s){ shape_offset_ = s; };

    /**
     * @brief Set the properties object
     * 
     * @param data 
     */
    void set_properties(const std::string& data){
        divine::Properties properties;
        properties.ParseFromString(data);
        properties_ = properties;
    }

    /**
     * @brief Set the world object
     * 
     * @param world 
     */
    void set_world(std::shared_ptr<World> world){world_=world;}


    //! Getter
    /**
     * @brief Get the reward object
     * 
     * @return double 
     */
    double get_reward() const { return reward_; };

    /**
     * @brief Get the type object
     * 
     * @return int 
     */
    int get_type() const { return type_; };

    /**
     * @brief Get the id object
     * 
     * @return int 
     */
    int get_id() const { return id_; };

    /**
     * @brief Get the shape object
     * 
     * @return Polygon_t<double, 2> 
     */
    Polygon_t<double, 2> get_shape() const { return shape_; };

    /**
     * @brief Get the shape offset object
     * 
     * @return PointNd_t<double, 2> 
     */
    PointNd_t<double, 2> get_shape_offset() const { return shape_offset_; };

    /**
     * @brief Get the properties object
     * 
     * @return std::string 
     */
    std::string get_properties() const { std::string str = ""; properties_.SerializeToString(&str); return str; };
    
    /**
     * @brief Get the world object
     * 
     * @return std::shared_ptr<World> 
     */
    std::shared_ptr<World> get_world(){return world_;}


private:
    Polygon_t<double, 2> shape_;
    PointNd_t<double, 2> shape_offset_;
    int id_;
    double reward_;
    int type_;
    divine::Properties properties_;
    std::shared_ptr<World> world_;

};

} // environment
} // world

#endif // _WORLD_BASE_TYPE_H_