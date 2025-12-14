package simulations;

// Simple module for UAV
simple UAV
{
    parameters:
        int uavId;
        string missionType;
        double xPos @unit(m);
        double yPos @unit(m);
        double zPos @unit(m);
        
        // --- FIXED MOBILITY PARAMETERS (UNIT ANNOTATION REMOVED AS WORKAROUND) ---
        // The units (m/s and s) are now implied in the C++ code.
        double xVelocity = default(1); 
        double yVelocity = default(1); 
        double moveInterval = default(0.1);
        
        // --- ADDED SECURITY PARAMETER (REQUIRED for encryption) ---
        string encryptionKey = default("simkey"); 

        double transmitPower @unit(mW) = default(100mW);
        double ackTimeout @unit(s) = default(2s);
        int maxRetries = default(3);
        @display("i=misc/node_vs,gold");
        // Statistics signals
        @signal[messagesSent](type=long);
        @signal[messagesReceived](type=long);
        @signal[retransmissions](type=long);
        @signal[timeouts](type=long);
        // Statistics recording
        @statistic[messagesSent](record=count,sum,mean,vector);
        @statistic[messagesReceived](record=count,sum,mean,vector);
        @statistic[retransmissions](record=count,sum,mean,vector);
        @statistic[timeouts](record=count,sum,mean,vector);

    gates:
        inout wireless;
}

simple GroundStation
{
    parameters:
        double xPos @unit(m) = default(0m);
        double yPos @unit(m) = default(0m);
        double zPos @unit(m) = default(0m);
        int queueCapacity = default(50);
        double processingDelay @unit(s) = default(0.1s);
        // --- ADDED SECURITY PARAMETER ---
        string encryptionKey = default("simkey"); 

        @display("i=device/antennatower");
        // Statistics signals
        @signal[queueLength](type=long);
        @signal[messagesProcessed](type=long);
        @signal[messagesDropped](type=long);
        @signal[processingDelay](type=simtime_t);
        // Statistics recording
        @statistic[queueLength](record=count,mean,max,min,vector);
        @statistic[messagesProcessed](record=count,sum,vector);
        @statistic[messagesDropped](record=count,sum,vector);
        @statistic[processingDelay](record=count,mean,max,min,vector);
    gates:
        inout wireless[3];
}

channel WirelessChannel extends ned.DatarateChannel
{
    parameters:
        datarate = 1Mbps;
        delay = 0.001ms;
        ber = 1e-6;
        per = 0.0;
        @display("ls=,3");
}

network UAVGroundStationNetwork
{
    parameters:
        @display("bgb=800,600");
    submodules:
        uav1: UAV {
            parameters:
                uavId = 1;
                missionType = "surveillance";
                xPos = 100m;
                yPos = 100m;
                zPos = 50m;
                @display("p=200,150");
        }

        uav2: UAV {
            parameters:
                uavId = 2;
                missionType = "delivery";
                xPos = 200m;
                yPos = 150m;
                zPos = 75m;
                @display("p=400,200");
        }

        uav3: UAV {
            parameters:
                uavId = 3;
                missionType = "emergency";
                xPos = 150m;
                yPos = 200m;
                zPos = 60m;
                @display("p=300,400");
        }

        groundStation: GroundStation {
            parameters:
                @display("p=400,300");
        }

    connections:
        uav1.wireless <--> WirelessChannel <--> groundStation.wireless[0];
        uav2.wireless <--> WirelessChannel <--> groundStation.wireless[1];
        uav3.wireless <--> WirelessChannel <--> groundStation.wireless[2];
}