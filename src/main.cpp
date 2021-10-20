#include <iostream>
#include <blepp/lescan.h>
#include <blepp/blestatemachine.h>


using namespace std;
using namespace BLEPP;

class MuseDevice{
    public:
        string name;
        string address;
        int rssi;

        bool connect() {
            cout << "Attempting to connect to " << this->name << " with address " << this->address << endl;
        }

};

int main() {
    HCIScanner scanner;
    BLEGATTStateMachine gatt;
    MuseDevice device;

    bool flag = true;

    while (flag) {
            vector<AdvertisingResponse> ads = scanner.get_advertisements();
            for (AdvertisingResponse ad : ads) {
                if (ad.local_name.is_initialized()) {
                    if (ad.local_name->name.find("MuseS") != string::npos) {
                        cout << "Found: " << ad.local_name->name << endl;
                        cout << "Address: " << ad.address << endl;
                        cout << "RSSI: " << int(ad.rssi) << endl;

                        device.name = ad.local_name->name;
                        device.address = ad.address;
                        device.rssi = int(ad.rssi);
                        flag = false;
                        break;
                    }
                }
            }
    }

    if (device.connect()) {
        cout << "Successfully Connected" << endl;
    } else {
        cout << "Could not connect to " << device.name << endl;
        return 1;
    }

    return 0;
}