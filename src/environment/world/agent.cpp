#include "src/environment/world/agent.h"
#include "src/environment/commons/common.h"
#include "src/environment/world/world.h"

namespace environment {
namespace world {

using namespace environment::kinematics;
using namespace environment::commons;
using namespace environment::observers;


StepRet Agent::step(const Matrix_t<double>& u, double dt){
		StepReturn sr;
		sr.state = get_world()->get_observer()->convert_state(get_world()->get_agent(get_id()));
		sr.action = u;
		kinematic_model_->step(u, dt);
		sr.next_state = get_world()->get_observer()->convert_state(get_world()->get_agent(get_id()));

		//! reward and collision
		// TODO: should the reward calculation really be here
		CollisionWith reason_for_collision = get_world()->collides(this->get_id());
		
		//! convert reward
		get_world()->get_observer()->convert_reward(sr, get_world()->get_agent(get_id()), reason_for_collision);

		bool is_colliding = false;
		//std::cout << reason_for_collision << std::endl;
		if(reason_for_collision <= 3)
			is_colliding = true;

		// TODO: add state to last_trajectory_ if there is no collision
		// if no last_trajectory_ exists create otherwise append
		if(is_colliding == false){
			if(last_trajectory_.rows() == 0){
				last_trajectory_ = Matrix_t<double>(1, kinematic_model_->get_state().cols());
				last_trajectory_ << kinematic_model_->get_state();
			} else {
				Matrix_t<double> tmp_trajectory(last_trajectory_.rows() + 1, kinematic_model_->get_state().cols());
				tmp_trajectory << last_trajectory_, kinematic_model_->get_state();
				last_trajectory_ = tmp_trajectory;
			}
		}

		//! returns a tuple of (state, action, next_state, reward, is_terminal)
		return std::make_tuple(sr.state, sr.action, sr.next_state, sr.reward, is_colliding);
}

}
}