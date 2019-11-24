#include "ChordNode.hpp"
#include <fstream>
#include <iostream>

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

    // Listening thread
    pthread_t listening_thread;
	if(pthread_create(&listening_thread, NULL, startListeningPort, (void *) c)) { perror("Error creating listening thread"); exit(0); }
	pthread_detach(listening_thread);

    while (true) {
        getline(cin, command);
        if(command.find("create_chord") != string::npos) {
            c->create();
        } else if(command.find("join_chord") != string::npos) {
            vector<string> result;
            boost::split(result, command, boost::is_any_of(" "));
            // for(string i:result){
            //     cout << i << "\n";
            // }

            if(result.size() != 3) { perror("Error the required parameters are join_chord <ip address> <port number>\n"); exit(0); }

            int socket_fd; struct sockaddr_in server_details;
            do{
                socket_fd = socket(AF_INET, SOCK_STREAM, 0);
                if (socket_fd == -1) perror("Error opening socket");
            } while (socket_fd == -1);

            bzero((char *) &server_details, sizeof(server_details));
            server_details.sin_family = AF_INET;
            server_details.sin_port = htons(stoi(result[2]));
            server_details.sin_addr.s_addr = inet_addr(result[1].c_str());

            if(connect(socket_fd, (struct sockaddr *)&server_details, sizeof(server_details)) == -1) { perror("Error connecting with peer"); pthread_exit(NULL); }
            sendData((char *)command.c_str(), command.size(), socket_fd);
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