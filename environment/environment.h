#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "../drone/drone.h"

class Environment {
public:
	float xmax;
	float xmin;
	float ymax;
	float ymin;
	std::vector<float> bounds;

	std::vector<float> targetPosition;

	Environment(float xmin, float xmax, float ymin, float ymax): xmax(xmax), xmin(xmin), ymax(ymax), ymin(ymin) {
		targetPosition = generateTargetPosition();
		bounds = { xmin, xmax, ymin, ymax };
	}

	std::vector<float> generateTargetPosition() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> disx(xmin, xmax);
		std::uniform_real_distribution<float> disy(ymin, ymax);

		return { disx(gen), disy(gen) };
	}



	float reward(Drone &drone) {
		// Calculate Theta between Drone and Target
		float theta = acos((drone.x * targetPosition[0] + drone.y * targetPosition[1])/ sqrt(pow(drone.x, 2)) + sqrt(pow(drone.y, 2)) * sqrt(pow(targetPosition[0], 2)) + sqrt(pow(targetPosition[1], 2)));
			
		float distance = abs(drone.x - targetPosition[0]) + abs(drone.y - targetPosition[1]);
		return 1 / distance;
	}
};