#ifndef DWQCP_HPP
#define DWQCP_HPP

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <network.h>
#include <errno.h>
#include <sys/dir.h>
#include <sys/fcntl.h>
#include <vector>
#include "magic_enum.hpp"
#include "screendebug.hpp"

// implementation of Dynamic Wii Quiz Configuration Protocol

/*
 Wii              WiiQuiz Server
  │                      │
  │  UDP:3112            │
  │  DWQCPDISCOVER       │
  │ ───────────────────► │
  │                      │
  │                      │
  │  UDP:3111            │
  │  DWQCPOFFER          │
  │ ◄─────────────────── │
  │                      │
  │                      │
  │  TCP:3110            │
  │  WII_REGISTER        │
  │ ───────────────────► │
  │                      │
  │                      │
  │  TCP:3110            │
  │  ACK                 │
  │ ◄─────────────────── │
  │                      │
  │                      │
*/

namespace DWQCP {
    std::string discover();
    std::string waitForOffer();
    void sendDiscover(s32 socket);
}

#endif // DWQCP_HPP
