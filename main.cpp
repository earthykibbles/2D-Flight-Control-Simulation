

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <deque>
#include "drone/drone.h"
#include "policy/policy.h"
#include "model/model.h"



int main()
{
    // Open a CSV file for writing
    std::ofstream csvFile("data.csv");
    Drone drone(3.0, 0.6, 0.6);
    float delta_t = 0;

    // Check if the file opened successfully
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    csvFile << "Time,X,Y,V_X,V_Y,A_X,A_Y,Theta,Tau,Thrust" << std::endl;


    float epsilon = 0.6;
    for (int episodes = 0; episodes < 100; episodes++) {
        while (delta_t < 2000) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<float> dist(120, 2);
            std::uniform_real_distribution<float> disep(0, 1);

            float r1_ang_vel;
            float r2_ang_vel;

            if (disep(gen) < epsilon) {
                r1_ang_vel = dist(gen);
                r2_ang_vel = dist(gen);
            }
            else {
                r1_ang_vel = 120;
                r2_ang_vel = 120;
            }

            drone.flightControl(r1_ang_vel, r2_ang_vel);

            //std::cout << std::fixed << std::setprecision(2) <<drone.v_x << "\t" << drone.v_y << "\t" << drone.a_x <<"\t" << drone.a_y << "\t" << drone.theta << "\t" << drone.tau << "\t" << drone.thrust << "\n";
            // Write the data to the CSV file with precision set to 2 decimal places
            csvFile 
                << std::fixed 
                << std::setprecision(2)
                << delta_t << ","
                << drone.x << ","
                << drone.y << ","
                << drone.v_x << ","
                << drone.v_y << ","
                << drone.a_x << ","
                << drone.a_y << ","
                << drone.theta << ","
                << drone.tau << ","
                << drone.thrust << ","
                << std::endl;

            if (drone.y <= 0) {
                break;
            }


            delta_t += 0.1;
            epsilon -= 0.01;
        }
    }

    // Close the file
    csvFile.close();
    std::cout << "Data written to data.csv successfully." << std::endl;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);

    std::vector<std::vector<float>> randomData;
    for (int i = 0; i < 10; ++i) {
        std::vector<float> rDph;
        for (int j = 0; j < 10; ++j) {
            rDph.push_back(dis(gen));
        }
        randomData.push_back(rDph);
    }

    Model model({32,10});
    model.forward(randomData);
}

