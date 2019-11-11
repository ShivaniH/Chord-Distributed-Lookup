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

ChordNode::ChordNode() {

}

void ChordNode::create()
{
    // create and set a chord ring ID here
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