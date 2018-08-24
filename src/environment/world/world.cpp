#include "world.h"

namespace environment {
namespace world {

bool World::parse_proto(){
    for (int i = 0; i < world_info_.object_size(); i++) {
        const divine::Object& obj = world_info_.object(i);
        
        //! create objects
        std::shared_ptr<BaseType> tmp_obj;

        if(obj.type() == 0){ //! create agent
            std::shared_ptr<Agent> agent(new Agent());

            //! pose
            PointNd_t<double, 3> pose(obj.pose().x(), obj.pose().y(), obj.pose().theta());
            agent->set_pose(pose);

            Matrix_t<double> state(1, obj.state().e_size());
            //! state
            for (int j = 0; j < obj.state().e_size(); j++) {
                double value = obj.state().e(j);
                state(0,j) = value;
            }
            agent->set_state(state);
            tmp_obj = agent;

        } else { //! create object
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

        this->add_object(tmp_obj);
    }
    return true;
}

}
}