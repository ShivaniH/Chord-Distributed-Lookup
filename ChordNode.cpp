#include "ChordNode.hpp"

using namespace std;

// FingerTableEntry methods
FingerTableEntry::FingerTableEntry(std::string ipAddress, int portNumber, ulli nodeIdentifier) {
    // Initialize the object
    this->ipAddress = ipAddress;
    this->portNumber = portNumber;
    this->nodeIdentifier = nodeIdentifier;
}

std::string FingerTableEntry::getIPAddress() {
    // Fetch the ip address
    return this->ipAddress;
}

int FingerTableEntry::getPortNumber() {
    // Fetch the port number
    return this->portNumber;
}

ulli FingerTableEntry::getNodeIdentifier() {
    // Fetch the node identifier
    return this->nodeIdentifier;
}

void FingerTableEntry::setIPAddress(string value) {
    this->ipAddress = value;
}

void FingerTableEntry::setNodeIdentifier(ulli value) {
    this->nodeIdentifier = value;
}

void FingerTableEntry::setPortNumber(int value) {
    this->portNumber = value;
}

// ChordNode methods
ChordNode::ChordNode(string ipAddress, int portNumber) {
    // Initialize the object
    this->ipAddress = ipAddress;
    this->portNumber = portNumber;
    this->nodeIdentifier = NULL;
    this->hashTable = NULL;
    this->fingerTable = NULL;
    this->successorList = NULL;
    this->predecessor = NULL;
}

void ChordNode::displayFingerTable() {
    if(this->fingerTable == NULL) cout << "You are not a part of any chord ring\n";
    else {
        cout << "Finger table entries:\n";
        for(auto i:*(this->fingerTable)) {
            if(i->getIPAddress() == "") {
                cout << "No entries are present\n";
                break;
            }
            cout << i->getIPAddress() << " " << i->getPortNumber() << " " << i->getNodeIdentifier() << "\n";
        }
    }
}

void ChordNode::displayHashTable() {
    if(this->hashTable == NULL) cout << "You are not a part of any chord ring\n";
    else {
        cout << "Hash table entries:\n";
        if(this->hashTable->size() == 0) {
            cout << "No entries are present\n";
        } else {
            for(auto i:*(this->hashTable)) {
                cout << i.first << " " << i.second << "\n";
            }
        }
    }
}

void ChordNode::displayNodeIdentifier() {
    if(this->nodeIdentifier == NULL) cout << "You are not a part of any chord ring\n";
    else {
        cout << "Node identifier: " << *nodeIdentifier << "\n";
    }
}

void ChordNode::displayPredecessor() {
    if(this->predecessor == NULL) cout << "You are either not a part of any chord ring or no predecessor yet\n";
    else {
        cout << predecessor->getIPAddress() << " " << predecessor->getPortNumber() << " " << predecessor->getNodeIdentifier() << "\n";
    }
}

void ChordNode::displaySuccessorList() {
    if(this->successorList == NULL) cout << "You are not a part of any chord ring\n";
    else {
        cout << "Successor table entries:\n";
        for(auto i:*(this->successorList)) {
            if(i->getIPAddress() == "") break;
            cout << i->getIPAddress() << " " << i->getPortNumber() << " " << i->getNodeIdentifier() << "\n";
        }
    }
}

void ChordNode::create() {
    if(this->fingerTable != NULL) {
        cout << "You are already part of a chord ring\n";
        return;
    }

    // Create a chord ring here
    this->fingerTable = new vector<FingerTableEntry *>(m, new FingerTableEntry("", -1, __LONG_LONG_MAX__));
    this->hashTable = new unordered_map<ulli, string>();
    this->nodeIdentifier = (ulli *) malloc(sizeof(ulli));
    *(this->nodeIdentifier) = calculateIdentifier(this->ipAddress + ":" + to_string(this->portNumber));
    this->predecessor = NULL;
    this->successorList = new vector<FingerTableEntry *>(r, new FingerTableEntry("", -1, __LONG_LONG_MAX__));
    (*(this->successorList))[0]->setIPAddress(this->ipAddress);
    (*(this->successorList))[0]->setNodeIdentifier(*this->nodeIdentifier);
    (*(this->successorList))[0]->setPortNumber(this->portNumber);
    cout << "Ring created successfully\n";
}

void ChordNode::join(FingerTableEntry * fte) {
    // Make the fte node join the chord ring
    pair<FingerTableEntry *, bool> result = this->findSuccessor(fte->getNodeIdentifier());
    
    int socket_fd; struct sockaddr_in server_details;
    do{
		socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd == -1) perror("Error opening socket");
	} while (socket_fd == -1);

    bzero((char *) &server_details, sizeof(server_details));
	server_details.sin_family = AF_INET;
    server_details.sin_port = htons(result.first->getPortNumber());
    server_details.sin_addr.s_addr = inet_addr(result.first->getIPAddress().c_str());

    if(connect(socket_fd, (struct sockaddr *)&server_details, sizeof(server_details)) == -1) { perror("Error connecting with peer"); pthread_exit(NULL); }
    string command;

    if(result.second) {
        command = "change_predecessor " + fte->getIPAddress() + " " + to_string(fte->getPortNumber()) + " " + to_string(fte->getNodeIdentifier());
    } else {
        command = "join_chord " + fte->getIPAddress() + " " + to_string(fte->getPortNumber()) + " " + to_string(fte->getNodeIdentifier());
    }

    // PKB
    // long long int command_size = command.size();
    // if(send(socket_fd, &command_size, sizeof(long long int), 0) == -1) { perror("Error sending command size to peer"); pthread_exit(NULL); }
	// if(send(socket_fd, command.c_str(), command_size, 0) == -1) { perror("Error sending command to peer"); pthread_exit(NULL); }

    sendData((char *)command.c_str(), command.size(), socket_fd);
}


pair<FingerTableEntry *, bool> ChordNode::findSuccessor(ulli id) {
    // Finding successor of id
    if(id <= *this->nodeIdentifier) {
        id = id + pow(2, m);
    }
    ulli successorIdentifier = this->successorList->at(0)->getNodeIdentifier();
    if(successorIdentifier <= *this->nodeIdentifier) {
        successorIdentifier += pow(2, m);
    }
    if(id > *this->nodeIdentifier && id <= successorIdentifier) {
        return make_pair(this->successorList->at(0), true);
    } else {
        return make_pair(this->closestPrecedingNode(id), false);
    }
}

FingerTableEntry* ChordNode::closestPrecedingNode(ulli id) {
    if(id <= *this->nodeIdentifier) {
        id = id + pow(2, m);
    }
    for(int i=m-1; i>=0; i--) {
        if(this->fingerTable->at(i)->getNodeIdentifier() > *this->nodeIdentifier) {
            // Normal
            if(this->fingerTable->at(i)->getNodeIdentifier() < id) {
                return this->fingerTable->at(i);
            }
        }
        else {
            // Rotation performed
            if(this->fingerTable->at(i)->getNodeIdentifier() + pow(2, m) < id) {
                return this->fingerTable->at(i);
            }
        }
    }
    return new FingerTableEntry(this->ipAddress, this->portNumber, *this->nodeIdentifier);
}

void ChordNode::checkPredecessor()
{

}

void ChordNode::fixFingers()
{

}

void ChordNode::stabilize()
{

}

void ChordNode::notify(string nodeID)
{

}

// Threads
struct thread_arguments_structure {
	char command[256]; ChordNode* c; int dataTransferFD;
};

void* interpretCommand(void* thread_arguments) {
    char * command = ((struct thread_arguments_structure *) thread_arguments)->command;
}

// Listening port
void* startListeningPort(void* thread_arguments) {
    int socket_fd, data_transfer_fd, port_number = ((ChordNode *)thread_arguments)->portNumber, number_of_characters;
	unsigned int sockaddr_struct_length; long long int command_size; string command; char buffer[256]; bzero(buffer, 256);

    do{
		socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd == -1) perror("Error opening socket");
	} while (socket_fd == -1);


	struct sockaddr_in server_details, client_details;
	bzero((char *) &server_details, sizeof(server_details));
	server_details.sin_family = AF_INET;
	server_details.sin_addr.s_addr = INADDR_ANY;
	server_details.sin_port = htons(port_number);

	if (bind(socket_fd, (struct sockaddr *) &server_details, sizeof(server_details)) == -1) { perror("Error binding"); pthread_exit(NULL); }

    listen(socket_fd, INT_MAX);
	sockaddr_struct_length = sizeof(struct sockaddr_in);

    while(1) {
        data_transfer_fd = accept(socket_fd, (struct sockaddr *) &client_details, &sockaddr_struct_length);
        if(data_transfer_fd == -1) { perror("Error accepting"); pthread_exit(NULL); }

        long long int receiver_size;
        string command(receiveData(receiver_size, data_transfer_fd));

        cout << "Command Received: " << command << "\n";

        pthread_t interpret_command_thread;
        struct thread_arguments_structure * send_chunk_thread_arg = (struct thread_arguments_structure *)malloc(sizeof(struct thread_arguments_structure));
        send_chunk_thread_arg->dataTransferFD = data_transfer_fd;
        strcpy(send_chunk_thread_arg->command, command.c_str());
        send_chunk_thread_arg->c = (ChordNode *)thread_arguments;
		if(pthread_create(&interpret_command_thread, NULL, interpretCommand, (void *) send_chunk_thread_arg)) { perror("Error creating interpret command thread"); pthread_exit(NULL); }
		pthread_detach(interpret_command_thread);
    }
}