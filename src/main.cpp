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


        void startStream() {
            cout << "Attempting to connect to " << this->name << " with address " << this->address << endl;
            BLEGATTStateMachine gatt;
            function<void(const PDUNotificationOrIndication&)> notify_cb = [&](const PDUNotificationOrIndication& n) {
                cout << "Notification 1: " << n.value().first << endl;
                cout << "Notification 2: " << n.value().second << endl;
            };

            function<void()> cb = [&gatt, &notify_cb]() {
                pretty_print_tree(gatt);

                for (auto& service: gatt.primary_services) {
                    for (auto& characteristic: service.characteristics) {
                        try{
                            characteristic.cb_notify_or_indicate = notify_cb;
                            characteristic.set_notify_and_indicate(true, true);
                        } catch (exception& e) {}

                    }
                }
            };

            gatt.cb_disconnected = [](BLEGATTStateMachine::Disconnect d) {
                cerr << "Disconnected for reason " << BLEGATTStateMachine::get_disconnect_string(d) << endl;
                exit(1);
            };

            gatt.setup_standard_scan(cb);
            gatt.connect_blocking(this->address);

            for(;;)
                gatt.read_and_process_next();
        }

};

int main() {
    HCIScanner scanner;
    MuseDevice device;

    bool flag = true;

    cout << "Searching for a Muse device..." << endl << endl;

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

    device.startStream();

    return 0;
}