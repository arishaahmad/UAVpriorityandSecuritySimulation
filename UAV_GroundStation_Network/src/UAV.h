#ifndef __UAV_NETWORK_UAV_H_
#define __UAV_NETWORK_UAV_H_

#include <omnetpp.h>
#include <map>
#include <string>
#include <cmath> // For fmax/fmin
#include "UAVMessages_m.h"

using namespace omnetpp;

class UAV : public cSimpleModule
{
  private:
    // Parameters
    int uavId;
    std::string missionType;
    double xPos, yPos, zPos;
    simtime_t ackTimeout;
    int maxRetries;

    // Mobility Parameters
    double xVel, yVel;

    // Security Parameter (NEW)
    std::string encryptionKey;

    // State tracking
    int sequenceNumber;
    std::map<int, int> retryCount;
    std::map<int, UAVMessage*> pendingAcks;

    // Statistics
    simsignal_t messagesSentSignal;
    simsignal_t messagesReceivedSignal;
    simsignal_t retransmissionsSignal;
    simsignal_t timeoutsSignal;

    // Self-messages for periodic tasks
    cMessage *generateDataMsg;
    cMessage *heartbeatMsg;
    cMessage *moveMsg;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    // Helper methods
    void sendDataToGroundStation();
    void sendHeartbeat();
    void scheduleTimeout(int seqNum);
    void handleTimeout(TimeoutMsg *timeoutMsg);
    void handleAck(AckMessage *ack);
    MessagePriority getPriorityForMission();
    double calculateDistance(double x1, double y1, double z1,
                            double x2, double y2, double z2);
    void updatePosition();

    // NEW: Security and Data Helpers
    std::string simpleXOR(const std::string& data, const std::string& key);
    double getFloraValue();

};

#endif
