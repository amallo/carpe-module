#pragma once
#include "core/transport/MessageTransport.h"
#include "core/peer/generators/AuthChallengeGenerator.h"
#include "core/device/providers/Screen.h"
#include "core/transport/AuthMessageEncoder.h"
#include "core/peer/model/AuthChallenge.h"
#include "core/peer/model/Message.h"
#include "core/peer/model/InitiateAuthChallengeMessage.h"

class PeerConnection {
public:
    PeerConnection(AuthChallengeGenerator* challengeGenerator, 
                  MessageTransport& transport, 
                  Screen& screen, 
                  AuthMessageEncoder& encoder);
    
    void onDeviceConnected(const std::string& deviceAddress);
    
private:
    AuthChallengeGenerator* challengeGenerator;
    MessageTransport* transport;
    Screen* screen;
    AuthMessageEncoder* encoder;
};
