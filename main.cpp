#include "transport_catalogue.h"
#include "input_reader.h"
#include "stat_reader.h"

int main(){
    TransportCatalogue cataloge;
    FillDatabase(std::cin, cataloge);
    Responses(std::cin, std::cout, cataloge);
    
}