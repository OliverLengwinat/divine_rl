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
		std::pair<bool, double> col_rew = get_world()->collides(this->get_id());
		return std::make_tuple(sr.state, sr.action, sr.next_state, col_rew.second, col_rew.first);
}

}
}