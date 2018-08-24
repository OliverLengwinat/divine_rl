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
#ifndef _COMMOONS_KINEMATICS_H_
#define _COMMOONS_KINEMATICS_H_
#include "src/environment/commons/common.h"

namespace environment {
namespace kinematics {

using namespace environment::commons;

template<typename T>
struct KinematicModel {
	KinematicModel(){};

	virtual Matrix_t<T> step(const Matrix_t<T>& state, const Matrix_t<T>& u, T dt) { return state;};
	virtual PointNd_t<T, 3> get_pose(const Matrix_t<T>& state){PointNd_t<T, 3> p; return p;};

};


template<typename T>
struct SingleTrackModel : public KinematicModel<T> {
	SingleTrackModel() {};

	// TODO: flexible wheel-base
	Matrix_t<T> step(const Matrix_t<T>& state, const Matrix_t<T>& u, T dt){
		Matrix_t<T> A(1, 4);
		A << state(3)*cos(state(2)), state(3)*sin(state(2)), tan(u(0))/T(1.5), u(1); 
		return state + dt * A;
	}
	
	PointNd_t<T, 3> get_pose(const Matrix_t<T>& state){
		PointNd_t<T, 3> pt;
		bg::set<0>(pt, state(0,0));
		bg::set<1>(pt, state(0,1));
		bg::set<2>(pt, state(0,2));
		return pt;
	}

};

}
}
#endif //_COMMOONS_KINEMATICS_H_