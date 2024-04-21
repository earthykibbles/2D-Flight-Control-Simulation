

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <deque>
#include "drone/drone.h"
#include "model/model.h"
#include "environment/environment.h"


int main()
{
    Environment env(-5000, 5000, 0, 5000);
  
    Drone drone(3.0, 0.6, 0.6, env.bounds);
    
    Model model({ 10,10 });

    float delta_t = 0;
    float epsilon = 0.9;
    std::vector<std::vector<float>> memory(0);

    // Open a CSV file for writing
    std::ofstream csvFile("data.csv");
    // Check if the file opened successfully
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    csvFile << "Time,X,Y,V_X,V_Y,A_X,A_Y,Theta,Tau,Thrust" << std::endl;
  
    float r1_ang_vel;
    float r2_ang_vel;
    bool modela = false;
    
    for (int episodes = 0; episodes < 100; episodes++) {
        std::cout << "Episode " << episodes << " started running." << std::endl;
        while (delta_t < 200) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<float> dist(120, 2);
            std::uniform_real_distribution<float> disep(0, 1);
            std::uniform_real_distribution<float> disreward(0, 5);

            
            // This is both the reward and the loss of the neural network
            float reward = disreward(gen);

            if (disep(gen) < epsilon) {
                r1_ang_vel = dist(gen);
                r2_ang_vel = dist(gen);
            }
            else {
                if (memory.size() > 20) {
                    modela = true;
                    std::vector<std::vector<float>> mem_feed(memory.begin(), memory.begin() + 10);
                    r1_ang_vel = model.predict(mem_feed)[0];
                    r2_ang_vel = model.predict(mem_feed)[1];
                    mem_feed.clear();
                    model.backward(reward);
                }
                else {
                    modela = false;
                    r1_ang_vel = dist(gen);
                    r2_ang_vel = dist(gen);
                }
            }

            drone.flightControl(r1_ang_vel, r2_ang_vel);
 

            std::cout << env.targetPosition[0] << "\t" << drone.x << "\t" << env.targetPosition[1] <<"\t" << drone.y << std::endl;
           

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

           /* if (drone.y <= env.ymin or drone.x <= env.xmin 
                or drone.y >= env.ymax or drone.x >= env.xmax) 
            {
                break;
            }*/

            delta_t += 0.1;
            epsilon -= 0.001;
        }
    }

    // Close the file
    csvFile.close();
    std::cout << "Data written to data.csv successfully." << std::endl;
}

