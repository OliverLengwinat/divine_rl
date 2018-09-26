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
#ifndef _COMMONS_KINEMATICS_H_
#define _COMMONS_KINEMATICS_H_
#include "src/environment/commons/common.h"
#include "src/environment/world/road_network.h"

namespace environment {
namespace kinematics {

using namespace environment::commons;
using namespace environment::world;

/**
 * @brief Base KinematicModel class
 * 
 * @tparam T 
 */
template<typename T>
class KinematicModel {
public:
	KinematicModel(){};

	virtual void step(const Matrix_t<T>& u, T dt) = 0;
	virtual PointNd_t<T, 3> get_pose() = 0;
	void set_state(const Matrix_t<T>& state){state_ = state; };
	
    void set_road_network(std::shared_ptr<RoadNetwork> rn){ road_network_ = rn; }
    std::shared_ptr<RoadNetwork> get_road_network(){ return road_network_; }

	Matrix_t<T> get_state() { return state_; };
	virtual ~KinematicModel() = default;

	void set_reference_road_id(int id){ reference_road_id_ = id; }
	int get_reference_road_id(){ return reference_road_id_; }

private:
	Matrix_t<double> state_;
	std::shared_ptr<RoadNetwork> road_network_;
	int reference_road_id_;
};


/**
 * @brief Single-Trackmodel
 * 
 * @tparam T 
 */
template<typename T>
struct SingleTrackModel : public KinematicModel<T> {
	SingleTrackModel(){ KinematicModel<T>::get_state().resize(1,4); };

	// TODO: flexible wheel-base
	void step(const Matrix_t<T>& u, T dt){
		Matrix_t<T> A(1, 4);
		std::cout << "still got here" << std::endl;

		Matrix_t<T> state = KinematicModel<T>::get_state();
		std::cout << "still got here" << std::endl;
		A << state(3)*cos(state(2)), state(3)*sin(state(2)), tan(u(0))/T(1.5), u(1); 
		KinematicModel<T>::set_state(state + dt * A);
	}
	
	PointNd_t<T, 3> get_pose(){
		Matrix_t<T> state = KinematicModel<T>::get_state();
		PointNd_t<T, 3> pt;
		bg::set<0>(pt, state(0,0));
		bg::set<1>(pt, state(0,1));
		bg::set<2>(pt, state(0,2));
		return pt;
	}

};

/**
 * @brief Tripple Integrator Model
 * 
 * @tparam T 
 */
template<typename T>
struct TrippleIntModel : public KinematicModel<T> {
	TrippleIntModel() { KinematicModel<T>::get_state().resize(1,3); };

	void step(const Matrix_t<T>& u, T dt){
		Matrix_t<T> A(3, 3);
		Matrix_t<T> B(1, 3);
		Matrix_t<T> state = KinematicModel<T>::get_state();
		A << 0, 1, 0, 0, 0, 1, 0, 0, 0;
		B << 0, 0, 1;
		KinematicModel<T>::set_state(state + dt * ((A*state.transpose()).transpose() + B*u(0,0)));
	}
	
	PointNd_t<T, 3> get_pose(){
		Matrix_t<T> state = KinematicModel<T>::get_state();
		std::pair<int, double> id_s_start = this->get_road_network()->get_segment_id(this->get_road_network()->get_reference_road(this->get_reference_road_id()), state(0,0));
		PointNd_t<T, 3> pose = get_pose_at_s<T>(this->get_road_network()->get_line_segment(id_s_start.first), state(0,0)-id_s_start.second);
		return pose;
	}
};


}
}
#endif //_COMMOONS_KINEMATICS_H_