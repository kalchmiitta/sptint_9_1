#include "stat_reader.h"
#include <iomanip>
#include <iostream>

std::ostream &operator<< (std::ostream &out, const BusInfo &bus) {
    out << "Bus " << bus.bus_name << ": " << bus.number_of_stops << " stops on route, "
        << bus.number_of_unique_stops << " unique stops, ";
    out << bus.route_length << " route length";
    return out;
}

void Responses(std::istream &in, std::ostream &out, TransportCatalogue& catalogue) {
    //out << std::fixed << std::setprecision(6);
    size_t requests_count;
    in >> requests_count;
    in.get();
    
    vector<string> buses;
    buses.reserve(requests_count);
    
    while (requests_count --) {
        string text;
        std::getline(in, text);
        
        auto bus_name = text.substr(4);
    
        if (auto bus_statistics = catalogue.GetBusIfo(bus_name)) {
            out << *bus_statistics << '\n';
        } else {
            out << "Bus " << bus_name << ": not found" << std::endl;
        }
    }
}