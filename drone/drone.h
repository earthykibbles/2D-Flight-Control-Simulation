#pragma once

#include <iostream>
#include <tuple>
#include <random>
#include <cmath>


class Rotor {
public:
	float d_cm;//Distance from centre of mass
	float k;

	Rotor(float k, float d_cm):k(k), d_cm(d_cm) {}

	// This is F
	float applyThrust(float ang_vel) {
		return k * pow(ang_vel,2);
	}
};

// All units are in metres
class Drone {
public:
	float mass;
	float height;
	float width;

	float v_x = 0.2;
	float v_y = 0.2;
	float x = 0;
	float y = 0;
	float a_x = 0.01;
	float a_y = 0.01;
	float thrust = 0;
	
	float theta = 0;
	float delta_t = 0.1;
	
	float moi;
	float tau;
	float g = 9.8;

	float d_cm;

	std::vector<float> bounds;
	std::vector<float> initialPosition;
	std::vector<float>  currentPosition;

	//Drone has two rotors
	Rotor r1;
	Rotor r2;


	Drone(float mass, float height, float width, std::vector<float> bounds): mass(mass), height(height), width(width), r1(0.01, width/2), r2(0.01, width / 2), bounds(bounds) {
		pickInitialPosition();
		moi = mass* (pow(width, 2) + pow(height, 2)) * 0.0833;
		d_cm = width / 2;
	};

	void pickInitialPosition() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> disx(bounds[0], bounds[1]);
		std::uniform_real_distribution<float> disy(bounds[2], bounds[3]);
		x = disx(gen);
		y = disy(gen);
		initialPosition = {x,y};
	}

	// What I can control is rotor speed to make it go up and down
	void flightControl(float r1ang_val, float r2ang_val) {
		// Differential thrust by rotors to pick direction
		tau = (r1.applyThrust(r1ang_val) - r2.applyThrust(r2ang_val)) * d_cm;
		
		// Total Thrust by all rotors
		thrust = r1.applyThrust(r1ang_val) + r2.applyThrust(r2ang_val);
		
		// Angle of attack
		theta = (theta + (tau / moi * delta_t));
		
		// Acceleration Component
		a_x = (thrust / mass) * sin(theta) - (mass * g * sin(theta));
		a_y = (thrust / mass) * cos(theta) - (mass * g * cos(theta));
		
		//Velocity Components
		v_x = (a_x * delta_t) + v_x;
		v_y = (a_y * delta_t) + v_y;
		
		// Position Components
		x = x + v_x * delta_t;
		y = y + v_y * delta_t;
		
		currentPosition = { x + v_x * delta_t, y + v_y * delta_t };
	}
};