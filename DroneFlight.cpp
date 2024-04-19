

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <deque>
#include "drone/drone.h"
//#include "ATen/ATen.h"



int main()
{
  /*  at::Tensor a = at::ones({ 2, 2 }, at::kInt);
    at::Tensor b = at::randn({ 2, 2 });
    auto c = a + b.to(at::kInt);*/

    // Open a CSV file for writing
    std::ofstream csvFile("data.csv");
    Drone drone(2.0, 0.6, 0.6);
    float delta_t = 0;

    // Check if the file opened successfully
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    csvFile << "X,Y,V_X,V_Y,A_X,A_Y,Theta,Tau,Thrust" << std::endl;


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
            csvFile << std::fixed << std::setprecision(2)
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


            // Our aim is to build a control system by q-learning 
            // that will help the drone capture the flag by controlling the angular velocity of each rotor
            //
        }
    }

    // Close the file
    csvFile.close();

    // Inform the user that the data was written successfully
    std::cout << "Data written to data.csv successfully." << std::endl;

    std::cout << "Hello World!\n";
}

