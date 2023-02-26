//
// Created by yngty on 2023/2/26.
//

#ifndef ECHO_ETHERNET_HEADER_H
#define ECHO_ETHERNET_HEADER_H
#include <array>
#include <string>
#include "util/parser.h"

using EthernetAddress = std::array<uint8_t, 6>;
constexpr EthernetAddress ETHERNET_BROADCAST =  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
std::string to_string(const EthernetAddress address);

class EthernetHeader {
    static constexpr size_t LENGTH =14;
    static constexpr uint16_t TYPE_IPv4 = 0x800;
    static constexpr uint16_t TYPE_ARP = 0x806;

    EthernetAddress dst;
    EthernetAddress src;
    uint16_t type;

    ParseResult parse(NetParser &p);
    std::string serialize() const;
    std::string to_string() const;
};


#endif //ECHO_ETHERNET_HEADER_H
