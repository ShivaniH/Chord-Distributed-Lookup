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
        if(this->fingerTable->size() == 0) {
            cout << "No entries are present\n";
        } else {
            for(auto i:*(this->fingerTable)) {
                cout << i->getIPAddress() << " " << i->getPortNumber() << " " << i->getNodeIdentifier() << "\n";
            }
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
    if(this->predecessor == NULL) cout << "You are not a part of any chord ring\n";
    else {
        cout << predecessor->getIPAddress() << " " << predecessor->getPortNumber() << " " << predecessor->getNodeIdentifier() << "\n";
    }
}

void ChordNode::displaySuccessorList() {
    if(this->successorList == NULL) cout << "You are not a part of any chord ring\n";
    else {
        cout << "Successor table entries:\n";
        if(this->successorList->size() == 0) {
            cout << "No entries are present\n";
        } else {
            for(auto i:*(this->successorList)) {
                cout << i->getIPAddress() << " " << i->getPortNumber() << " " << i->getNodeIdentifier() << "\n";
            }
        }
    }
}

void ChordNode::create() {
    // Create a chord ring here
    this->fingerTable = new vector<FingerTableEntry *>(m, new FingerTableEntry("", -1, __LONG_LONG_MAX__));
    this->hashTable = new unordered_map<ulli, string>();
    *(this->nodeIdentifier) = calculateIdentifier(this->ipAddress + ":" + to_string(this->portNumber));
    this->predecessor = NULL;
    this->successorList = new vector<FingerTableEntry *>(r, new FingerTableEntry("", -1, __LONG_LONG_MAX__));
    (*(this->successorList))[0]->setIPAddress(this->ipAddress);
    (*(this->successorList))[0]->setNodeIdentifier(*this->nodeIdentifier);
    (*(this->successorList))[0]->setPortNumber(this->portNumber);
}

void ChordNode::join(string nodeID)
{
    // Join a chordRing which contains a node with nodeIdentifier = nodeID
}

string ChordNode::findSuccessor(string ID)
{
    // from research paper
}

string ChordNode::closestPrecedingNode(string ID)
{
    // from research paper
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