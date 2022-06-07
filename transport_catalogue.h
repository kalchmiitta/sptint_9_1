#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <optional>

#include "geo.h"

using std::string;
using std::string_view;
using std::vector;
using std::unordered_map;
using std::deque;

enum RouteType {
    ring,
    forward
};

struct Stop {
    string name;
    Coordinates stop_coordinate;
    
    [[nodiscard]]size_t Hash () const {
        return std::hash<string>{}(name) +
               std::hash<double>{}(stop_coordinate.lat) * prime_num +
               std::hash<double>{}(stop_coordinate.lat) * prime_num * prime_num;
    }
    
private:
    static const size_t prime_num = 13;
};


struct Bus {
    string name;
    RouteType type;
    vector<string_view> stops;
    std::unordered_set<string_view> unique_stops;
    
    size_t StopsCounter () const;
    
};

struct BusInfo {
    string_view bus_name;
    size_t number_of_stops;
    size_t number_of_unique_stops;
    double route_length;
};


class TransportCatalogue {

public:
    TransportCatalogue() = default;
    void AddBus(Bus bus);
    void AddStop(Stop bus);
    std::optional<BusInfo> GetBusIfo(string_view bus_name) const;
    double GetRouteLength(std::string_view bus_name) const;
    
    
private:
    
    deque<Stop> all_stops_;
    unordered_map<string_view, const Stop *> stops_;
    
    deque<Bus> all_buses_;
    unordered_map<string_view, const Bus *> buses_;
    
};