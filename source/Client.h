#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <utility>
#include <vector>

#include "InputState.h"

using std::pair;
using std::string;
using std::vector;

class Client
{
private:
    InputState                      inputs;
    bool                            spectator;
    uint16_t                        playerNum;
    vector<pair<string, double>>    screenMessages;
};

#endif // CLIENT_H
