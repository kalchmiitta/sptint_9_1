#include "input_reader.h"
#include <iomanip>
//#include <iostream>

//обработка запросов остановок - добавляет в каталог
void ParseStop (string_view text, TransportCatalogue &catalogue) {
    Stop new_stop;
    size_t name_end = text.find(':');
    new_stop.name = text.substr(0, name_end);
    size_t lat_end = text.find(',', name_end + 1);
    new_stop.stop_coordinate.lat = std::stod(string(text.substr(name_end + 2, text.size() - lat_end - 2)));
    new_stop.stop_coordinate.lng = std::stod(string(text.substr(lat_end + 2)));
    //std::cout <<std::fixed<<std::setprecision(6)<<"***"<< new_stop.name;
    //std::cout <<"*"<< new_stop.stop_coordinate.lat<<"*";
    //std::cout <<"*"<< new_stop.stop_coordinate.lng<<"*\n";
    catalogue.AddStop(new_stop);
}

//обработка запросов автобусов - добавляет в каталог
void ParseBus (string_view text, TransportCatalogue &catalogue) {
    Bus new_bus;
    
    size_t name_end = text.find(':');
    new_bus.name = text.substr(0, name_end);
    
    string_view separator;
    if (text.find(" > ") != string::npos) {
        new_bus.type = RouteType::ring;
        separator = " > ";
    } else {
        new_bus.type = RouteType::forward;
        separator = " - ";
    }
    
    size_t stop_name_start = text.find(':') + 2;
    while (stop_name_start < text.size()) {
        size_t stop_name_end = text.find(separator, stop_name_start);
        if (stop_name_end == string::npos) {
            stop_name_end = text.size();
        }
        new_bus.stops.push_back(text.substr(stop_name_start, stop_name_end - stop_name_start));
        stop_name_start = stop_name_end + 3;
    }
    new_bus.unique_stops = {new_bus.stops.begin(), new_bus.stops.end()};
    catalogue.AddBus(new_bus);
    
}

//основная функция на заполнение базы, вызывается первой после создания каталога
void FillDatabase (std::istream &in, TransportCatalogue &catalogue) {
    
    size_t requests_count;
    in >> requests_count;
    in.get();
    
    vector<string> buses;
    buses.reserve(requests_count);
    
    while (requests_count --) {
        string text;
        std::getline(in, text);
        text.substr(0, 4) == "Stop" ? ParseStop(text.substr(5), catalogue) : buses.push_back(std::move(text.substr(4)));
    }
    
    for (const auto &bus_stops: buses) {
        ParseBus(bus_stops, catalogue);
    }
    
}

