#include <unordered_map>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include "Utilities.hpp"
#include <cmath>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define r 1

class FingerTableEntry {
private:
    // IP address of the finger table entry
    std::string ipAddress;
    
    // portNumber of finger table entry
    int portNumber;
    
    // Node identifier of finger table entry
    ulli nodeIdentifier;
public:
    // Constructor
    FingerTableEntry(std::string ipAddress, int portNumber, ulli nodeIdentifier);
    
    // Fetch IP address
    std::string getIPAddress();
    
    // Fetch port number
    int getPortNumber();
    
    // Fetch node identifier
    ulli getNodeIdentifier();

    // Set IP address
    void setIPAddress(std::string value);

    // Set port number
    void setPortNumber(int value);

    // Set node identifier
    void setNodeIdentifier(ulli value);
};

class ChordNode {
    /*
    TODO: create(), join(), findSuccessor(), notify(), closestPrecedingNode(), stabilize(), checkPredecessor(), fixFingers(), displays()
    
    RUN PERIODICALLY: stabilize(), checkPredecessor(), fixFingers()
    */

private:
    // IP Address of current node
    std::string ipAddress;
    
    // Port number of current node
    int portNumber;
    
    // Obtained using SHA-1. Identifies the node in the chord
    ulli * nodeIdentifier;
    
    // Stores the key value pair in the current node
    std::unordered_map<ulli, std::string> * hashTable;
    
    // Finger table of current node // Maximum of m entries
    std::vector<FingerTableEntry *> * fingerTable;
    
    // Successor list of current node // Required for failure handling // Maximum of r entries
    std::vector<FingerTableEntry *> * successorList;
    
    // Predecessor of current node
    FingerTableEntry * predecessor;

    // Searching the local finger table for the highest predecessor of id
    FingerTableEntry * closestPrecedingNode(ulli ID);

    // Finding successor of id
    std::pair<FingerTableEntry *, bool>  findSuccessor(ulli id);
public:
    // Initialize the objects
    ChordNode(std::string ipAddress, int portNumber);

    // Creates a chord ring with one node only
    void create();

    // Display the finger table
    void displayFingerTable();

    // Display hash table
    void displayHashTable();

    // Display node identifier
    void displayNodeIdentifier();

    // Display successorList
    void displaySuccessorList();

    // Display predecessor
    void displayPredecessor();

    // Make the fte node join the chord ring
    void join(FingerTableEntry * fte);

    void checkPredecessor();

    void fixFingers();

    void stabilize();

    void notify(std::string nodeID);
};