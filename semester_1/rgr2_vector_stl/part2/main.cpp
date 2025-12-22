#include "time_utility.h"
#include "train.h"
#include <iostream>
#include <fstream>
void isEmpty(std::ifstream& file) {
    if (file.peek() == std::ifstream::traits_type::eof()) {
        throw "File is empty";
    }
}
void isOpen(std::ifstream& file) {
    if (!(file.is_open())) {
        throw "The file cannot be opened!";
    }
}
std::vector<Train> readDataAboutTrains(std::ifstream& file) {
    std::vector<Train> trains;
    size_t id;
    int type_int;
    std::string destination;
    size_t hour, minute;
    size_t travel_hour, travel_minute;
    while (file >> id >> type_int >> destination >> hour >> minute >> travel_hour >> travel_minute) {
        std::time_t dispatch = SetTime(hour, minute);
        std::time_t travel = SetTime(travel_hour, travel_minute);
        TrainType type = static_cast<TrainType>(type_int);
        trains.emplace_back(id, type, destination, dispatch, travel);
    }
    return trains;
}
void printTrainsInTimeRange(const std::vector<Train>& trains, std::time_t from, std::time_t to) {
    std::cout << "Trains in time range: \n";
    std::for_each(trains.begin(), trains.end(), [&](const Train& train) {
        if (train.getDispatchTime() >= from && train.getDispatchTime() <= to) {
            train.print();
        }
    });
}
void printTrainsToDestination(const std::vector<Train>& trains, const std::string& destination) {
    std::cout << "Trains to destination " << destination << ":\n";
    std::for_each(trains.begin(), trains.end(), [&](const Train& train) {
        if (train.getDestination() == destination) {
            train.print();
        }
    });
}
void printTrainsByTypeAndDestination(const std::vector<Train>& trains, TrainType type,
                                     const std::string& destination) {
    std::cout << "Trains of type \"" << Train::trainTypeToString(type) << " to " << destination << "\":\n";
    std::for_each(trains.begin(), trains.end(), [&](const Train& train) {
        if (train.getType() == type && train.getDestination() == destination) {
            train.print();
        }
    });
}
void printFastestTrainToDestination(const std::vector<Train>& trains, const std::string& destination) {
    const Train* fastest = nullptr;
    for (const Train& t : trains) {
        if (t.getDestination() == destination) {
            if (!fastest || t.getTravellingTime() < fastest->getTravellingTime()) {
                fastest = &t;
            }
        }
    }
    if (fastest) {
        std::cout << "Fastest train to " << destination << ":\n";
        fastest->print();
    } else {
        std::cout << "No trains to " << destination << "found.\n";
    }
}
int main() {
    try {
        using namespace time_utility;
        std::ifstream fin("C:\\Users\\LENA\\My_staff\\TEST_RGR2\\x64\\Debug\\trains.txt");
        isOpen(fin);
        isEmpty(fin);
        std::vector<Train> trains = readDataAboutTrains(fin);
        std::sort(trains.begin(), trains.end());
        std::time_t from = SetTime(8, 0);
        std::time_t to = SetTime(12, 0);
        printTrainsInTimeRange(trains, from, to);
        printTrainsToDestination(trains, "Minsk");
        printTrainsByTypeAndDestination(trains, TrainType::PASSENGER, "Minsk");
        printFastestTrainToDestination(trains, "Minsk");
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    return 0;
   /* using namespace time_utility;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }
    std::time_t t2 = GenerateRandomTime(generator);
    std::cout << "t1: ";
    PrintTime(t1);
    std::cout << "t2: ";
    PrintTime(t2);
    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) <<'\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';
    return EXIT_SUCCESS;*/
}
