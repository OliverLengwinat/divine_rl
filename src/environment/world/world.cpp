#include "world.h"

namespace environment {
namespace world {

bool World::parse_proto(){
    for (int i = 0; i < world_info_.object_size(); i++) {
        const divine::Object obj = world_info_.object(i);
        
        //! create objects
        std::shared_ptr<BaseType> tmp_obj;
        if(obj.type() == 0){ //! create agent
            std::shared_ptr<Agent> agent(new Agent());
            tmp_obj = agent;

        } else if (obj.type() == 1) { //! create object
            std::shared_ptr<Object> object(new Object());
            tmp_obj = object;
        }

        //! shape
        Polygon_t<double, 2> shape;
        for (int j = 0; j < obj.shape().p_size(); j++) {
            divine::Point p = obj.shape().p(j);
            bg::append(shape, PointNd_t<double, 2>(p.x(), p.y()));
        }

        tmp_obj->set_shape(shape);
        tmp_obj->set_id(obj.id());
        tmp_obj->set_reward(obj.reward());
        tmp_obj->set_type(obj.type());

        add_object(tmp_obj);
    }

    return true;
}

}
}