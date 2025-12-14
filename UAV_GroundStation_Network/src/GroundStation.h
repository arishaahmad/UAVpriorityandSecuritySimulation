#ifndef __UAV_NETWORK_GROUNDSTATION_H_
#define __UAV_NETWORK_GROUNDSTATION_H_

#include <omnetpp.h>
#include <queue>
#include <vector>
#include <string> // REQUIRED for std::string
#include "UAVMessages_m.h" // FIX: Removed erroneous backslashes

using namespace omnetpp;

// Custom comparator for priority queue
struct MessageComparator {
    bool operator()(UAVMessage* a, UAVMessage* b) {
        // Higher priority value = higher priority
        if (a->getPriority() != b->getPriority()) {
            return a->getPriority() < b->getPriority();
        }
        // If same priority, earlier timestamp has priority
        return a->getTimestamp() > b->getTimestamp();
    }
};

class GroundStation : public cSimpleModule
{
  private:
    // Priority queue for incoming messages
    std::priority_queue<UAVMessage*,
                       std::vector<UAVMessage*>,
                       MessageComparator> messageQueue;

    // Parameters
    int queueCapacity;
    simtime_t processingDelay;
    std::string encryptionKey;

    // State
    bool isProcessing;
    cMessage *processingTimer;

    // Statistics
    simsignal_t queueLengthSignal;
    simsignal_t messagesProcessedSignal;
    simsignal_t messagesDroppedSignal;
    simsignal_t processingDelaySignal;

    // Per-UAV statistics
    std::map<int, int> messagesPerUAV;
    std::map<int, simtime_t> lastHeartbeat;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    // Helper methods
    void enqueueMessage(UAVMessage *msg);
    void processNextMessage();
    void sendAck(UAVMessage *msg, bool success);
    int getGateIndexForUAV(int uavId);

    // Security and Stats Helpers
    std::string simpleXOR(const std::string& data, const std::string& key);
    void recordProcessingDelay();
};

#endif
