#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "load_data.h"
#include "covariance.h"
// #include "cov_helper.h"

void exampleDataSet(int pointNum, std::vector<std::vector<double>> &data)
{

    int version = 15;

    for (int i = 0; i < 15; i++)
    {
        std::vector<double> d;
        for (int j = 0; j < pointNum * pointNum; j++)
        {
            d.push_back(j + (i + 1) * 0.1 * (j + 1));
        }
        data.push_back(d);
    }
}

int main(int argc, char *argv[])
{
    Eigen::initParallel();
    Eigen::setNbThreads(56);
    // std::string file_dir = "/Users/mengjiao/Desktop/Uncertainty/LCP_C++/datasets/txt_files/wind_pressure_200/Lead_33_";
    // std::string file_dir = "/home/mengjiao/Desktop/Probabilistic-Marching-Cubes-C-/datasets/txt_files/wind_pressure_200/Lead_33_";
    if (argc != 2)
    {
        std::cout << "<binary> <wind_data_folder, has />" << std::endl;
        exit(0);
    }

    //"/home/zw/cworkspace/Probabilistic-Marching-Cubes-C-/datasets/txt_files/wind_pressure_200/Lead_33_";

    std::string wind_data_folder = argv[1];
    std::string file_dir = wind_data_folder + "wind_pressure_200/Lead_33_";

    std::vector<std::vector<double>> data;

    int num_members = 15;
    int num_samples = 1000;
    double isovalue = 0.3;
    int size_x = 121;
    int size_y = 240;

    // Load data
    load_data(file_dir, num_members, data);

    /*
    using exmaple data for testing

    int gridsize = 2;
    exampleDataSet(gridsize, data);
    int num_members = 15;
    int num_samples = 1000;
    double isovalue = 1.5;
    int size_x = gridsize;
    int size_y = gridsize;
    */
    // Debug
    // for(int i = 0; i < data.size(); ++i){
    //     std::cout << "member " << i << " size: " << data[i].size() << "\n";
    //     for(int j = 0; j < data[i].size(); ++j){
    //         if (j < 10)
    //             std::cout << data[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }
    std::cout << "ok to load the data" << std::endl;
    
    //start the timer
    auto start = std::chrono::high_resolution_clock::now();
    cov_matrix(data, size_x, size_y, num_members, num_samples, isovalue);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Runtime: " << duration.count() << " ms " << std::endl;
    return 0;
}