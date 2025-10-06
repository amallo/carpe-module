#pragma once
#include "MessageTransport.h"
#include "core/transport/model/Challenge.h"
#include "core/transport/model/AuthRequestMessage.h"

// Forward declarations
class MockChallengeGenerator;
class MockScreen;

class PeerConnection {
public:
    PeerConnection(MockChallengeGenerator* challengeGenerator, 
                  MessageTransport& transport, 
                  MockScreen& screen);
    
    void onDeviceConnected(const std::string& deviceAddress);
    
private:
    MockChallengeGenerator* challengeGenerator;
    MessageTransport* transport;
    MockScreen* screen;
};
