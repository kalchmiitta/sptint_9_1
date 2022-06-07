#include "transport_catalogue.h"



size_t Bus::StopsCounter () const {
    return (type == RouteType::ring ? stops.size() : (stops.size() * 2 - 1));
}

void TransportCatalogue::AddBus (Bus bus) {
    for (auto &stop: bus.stops) {
        stop = stops_.find(stop)->first;
    }
    
    const auto added_bus = all_buses_.insert(all_buses_.begin(), std::move(bus));
    buses_.insert({added_bus->name, &(*added_bus)});
    
}

std::optional<BusInfo> TransportCatalogue::GetBusIfo (string_view bus_name) const {
    if (! buses_.count(bus_name))
        return std::nullopt;
    
    const Bus *bus = buses_.at(bus_name);
    
    BusInfo bus_inf_result;
    bus_inf_result.bus_name = bus->name;
    bus_inf_result.number_of_stops = bus->StopsCounter();
    bus_inf_result.number_of_unique_stops = bus->unique_stops.size();
    bus_inf_result.route_length = GetRouteLength(bus_name);
    
    return bus_inf_result;
}

void TransportCatalogue::AddStop (Stop stop) {
    if (!stops_.count(stop.name)) {
        const auto added_stop = all_stops_.insert(all_stops_.begin(), std::move(stop));
        stops_.insert({added_stop->name, &(*added_stop)});
    }
}

double TransportCatalogue::GetRouteLength (std::string_view bus_name) const {
    double result_length = 0.;
    
    if (buses_.at(bus_name)->type == RouteType::ring) {
        // расчет длины кольцевого маршрута - пройдем по всем остановками и посчитаем длину
        
        for (auto itr = buses_.at(bus_name)->stops.begin(); itr + 1 != buses_.at(bus_name)->stops.end(); itr ++) {
            auto start = stops_.at(*itr)->stop_coordinate;
            auto end = stops_.at(*(itr + 1))->stop_coordinate;
            result_length += ComputeDistance(start, end);
        }
    } else {
        // расчет длины прямого возвращающегося маршрута - пройдем по всем остановками и удвоим расстояние
        for (auto itr = buses_.at(bus_name)->stops.begin(); itr + 1 < buses_.at(bus_name)->stops.end(); itr ++) {
            Coordinates crd1{stops_.at(*itr)->stop_coordinate};
            Coordinates crd2{stops_.at(*(itr + 1))->stop_coordinate};
            result_length += ComputeDistance(crd1, crd2);
        }
        result_length *= 2.;
    }
    
    return result_length;
    
}