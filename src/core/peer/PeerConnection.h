#pragma once
#include "core/transport/MessageTransport.h"
#include "ChallengeGenerator.h"
#include "core/device/providers/Screen.h"
#include "core/transport/AuthMessageEncoder.h"
#include "core/peer/model/Challenge.h"
#include "core/peer/model/Message.h"
#include "core/peer/model/AuthRequestMessage.h"

class PeerConnection {
public:
    PeerConnection(ChallengeGenerator* challengeGenerator, 
                  MessageTransport& transport, 
                  Screen& screen,
                  AuthMessageEncoder& encoder);
    
    void onDeviceConnected(const std::string& deviceAddress);
    
private:
    ChallengeGenerator* challengeGenerator;
    MessageTransport* transport;
    Screen* screen;
    AuthMessageEncoder* encoder;
};
