#include "ChordNode.hpp"
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
    string command;

    // Check whether port number is provided or not
    if(argc != 2) {
        perror("Error provide port number");
        exit(1);
    }

    // Fetch IP address and store in vector<string>
    vector<string> ip_addresses;
    system("ifconfig > ip_address.txt");
    ifstream ifs("ip_address.txt");
    string line;
    while(!ifs.eof()) {
        getline(ifs, line);
        long long int index = line.find("inet ");
        if(index != string::npos){
            line = line.substr(index+5);
            line = line.substr(0, line.find(" "));
            ip_addresses.push_back(line);
        }
    }
    ifs.close();
    remove("ip_address.txt");

    if(ip_addresses.size() == 1) { perror("Error connect to internet"); exit(1); }

    // Create chord node object
    ChordNode * c = new ChordNode(ip_addresses[1], stoi(argv[1]));

    cout << "Your network details: IP Address = " << ip_addresses[1] << " and Port number = " << argv[1] << "\n";

    
    
    while (true) {
        cin >> command;
        if(command.find("create_chord") != string::npos) {
            c->create();
        } else if(command.find("join_chord") != string::npos) {

        } else if(command.find("display_finger_table") != string::npos) {
            c->displayFingerTable();
        } else if(command.find("display_hash_table") != string::npos) {
            c->displayHashTable();
        } else if(command.find("display_node_identifier") != string::npos) {
            c->displayNodeIdentifier();
        } else if(command.find("display_predecessor") != string::npos) {
            c->displayPredecessor();
        } else if(command.find("display_successor_list") != string::npos) {
            c->displaySuccessorList();
        } else {
            cout << "Invalid command\n";
        }
    }
    
    return 0;
}