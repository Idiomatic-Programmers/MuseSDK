#include <iostream>
#include <blepp/lescan.h>

using namespace std;
using namespace BLEPP;

int main() {
    
    log_level = LogLevels::Info;
    HCIScanner scanner;

    while (1) {
        std::vector<AdvertisingResponse> ads = scanner.get_advertisements();
    }    
    
    return 0;
}