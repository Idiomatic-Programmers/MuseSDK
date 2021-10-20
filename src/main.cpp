#include <iostream>
#include <blepp/lescan.h>
#include <boost/optional/optional_io.hpp>

using namespace std;
using namespace BLEPP;

int main() {
    
//    log_level = LogLevels::Info;
    HCIScanner scanner;

    while (1) {
            vector<AdvertisingResponse> ads = scanner.get_advertisements();
            for (AdvertisingResponse ad : ads) {
                if (ad.local_name.is_initialized()) {
                    if (ad.local_name->name.find("MuseS") != string::npos) {
                        cout << "Found: " << ad.local_name->name << endl;
                        cout << "Address: " << ad.address << endl;
                        cout << "RSSI: " << int(ad.rssi) << endl;
                        break;
                    }
                }
            }
    }
    
    return 0;
}