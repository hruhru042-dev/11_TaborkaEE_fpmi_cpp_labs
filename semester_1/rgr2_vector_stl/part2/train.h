#pragma once

#include <string>
#include "time_utility.h"
#include <iostream>
#include <ctime>

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train()
        : id_(0),
          type_(TrainType::PASSENGER),
          destination_(""),
          dispatch_time_(0),
          travelling_time_(0) {
    }
    Train(size_t id, TrainType type, const std::string& destination, std::time_t dispatch_time, //инициализация полей
          std::time_t traveling_time)
        : id_(id),
          type_(type),
          destination_(destination),
          dispatch_time_(dispatch_time),
          travelling_time_(traveling_time) {}
    //гетеры
    TrainId getId() const {
        return id_;
    }
    TrainType getType() const {
        return type_;
    }
    const std::string& getDestination() const {
        return destination_;
    }
    std::time_t getDispatchTime() const {
        return dispatch_time_;
    }
    std::time_t getTravellingTime() const {
        return travelling_time_;
    }
    //сеттеры
    void setId(TrainId id) {
        id_ = id;
    }
    void setType(TrainType type) {
        type_ = type;
    }
    void setDetination(const std::string& destination) {
        destination_ = destination;
    }
    void setDispatchTime(std::time_t dispatch_time) {
        dispatch_time_ = dispatch_time;
    }
    void setTravellingTime(std::time_t travelling_time) {
        travelling_time_ = travelling_time;
    }
    void print() const {
        std::cout << "Train ID: " << id_ << "\n";
        std::cout << "Train type: " << trainTypeToString(type_) << "\n";
        std::cout << "Destination: " << destination_ << "\n";
        std::cout << "Dispatch time: ";
        PrintTime(dispatch_time_);
        std::cout << "Travelling time: ";
        PrintTime(travelling_time_);
        std::cout << "-----------------------------\n";
    }
    static std::string trainTypeToString(TrainType type) {
        switch (type) {
            case TrainType::PASSENGER:
                return "Passenger";
            case TrainType::FREIGHT:
                return "Freight";
            case TrainType::HIGH_SPEED:
                return "High speed";
            case TrainType::SUBWAY:
                return "Subway";
            case TrainType::SPECIALIZED:
                return "Specialized";
            default:
                return "Unknown";
        }
    }
    bool operator<(const Train& other) const {
        return dispatch_time_ < other.dispatch_time_;
    }


    //по умолчанию с полями
    // your code goes here
};
