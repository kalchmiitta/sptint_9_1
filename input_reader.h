#pragma once

#include <iostream>
#include <string>

#include "transport_catalogue.h"

void FillDatabase(std::istream &in, TransportCatalogue& catalogue);
void ParseStop(string_view text, TransportCatalogue& catalogue);
void ParseBus(string_view text, TransportCatalogue& catalogue);