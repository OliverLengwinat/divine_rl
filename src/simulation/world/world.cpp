#include "world.h"

namespace simulation {
namespace world {

bool World::parse_proto(){
   /*
    for (int i = 0; i < address_book.people_size(); i++) {

    }
    */
    for (int i = 0; i < world_info_.object_size(); i++) {
        const divine::Object& obj = world_info_.object(i);
        
        //! create objects
        std::cout << "  Object name: " << obj.type() << std::endl;
        std::shared_ptr<BaseType> tmp_obj;

        if(obj.type() == 0){ //! create agent
            std::shared_ptr<Agent> agent(new Agent());
            /*
            PointNd_t<double, 3> pose;
            agent->set_pose();
            */
            tmp_obj = agent;

        } else if(obj.type() == 1){ //! create object
            std::shared_ptr<Object> object(new Object());
            tmp_obj = object;
        }

        this->add_object(tmp_obj);
    }
    return true;
}

}
}