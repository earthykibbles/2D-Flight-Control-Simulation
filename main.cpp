

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


    float epsilon = 0.9;

    Model model({10,10});
    std::vector<std::vector<float>> memory(0);
    
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
                if (memory.size() < 20) {
                    std::vector<std::vector<float>> mem_feed(memory.begin(), memory.begin() + 9);
                    std::cout << mem_feed.size() << std::endl;
                    /* std::cout << model.predict(mem_feed)[0] << model.predict(mem_feed)[1]<< std::endl;
                     r1_ang_vel = model.predict(mem_feed)[0];
                     r2_ang_vel = model.predict(mem_feed)[1];
                     mem_feed.clear();
                 }*/
                }
                else {
                    r1_ang_vel = dist(gen);
                    r2_ang_vel = dist(gen);
                }
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

            std::vector<float> state = { delta_t , drone.x , drone.y, drone.v_x, drone.v_y, drone.a_x, drone.a_y, drone.theta, drone.tau , drone.thrust };
            memory.push_back(state);

            if (drone.y <= 0) {
                break;
            }

            delta_t += 0.1;
            epsilon -= 0.001;
        }
    }

    // Close the file
    csvFile.close();
    std::cout << "Data written to data.csv successfully." << std::endl;
}

