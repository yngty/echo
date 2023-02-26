//
// Created by yngty on 2023/2/26.
//

#include "ethernet_header.h"
#include <sstream>
#include <iomanip>

using namespace std;

ParseResult EthernetHeader::parse(NetParser &p) {
    if (p.buffer().size() < EthernetHeader::LENGTH)
        return ParseResult::PacketTooShort;

    for (auto& byte : dst) {
        byte = p.u8();
    }

    for (auto& byte : src) {
        byte = p.u8();
    }

    type = p.u16();

    return p.get_error();
}
std::string EthernetHeader::serialize() const {
    string ret;
    ret.reserve(LENGTH);

    /* write destination address */
    for (auto &byte : dst) {
        NetUnparser::u8(ret, byte);
    }

    /* write source address */
    for (auto &byte : src) {
        NetUnparser::u8(ret, byte);
    }

    /* write the frame's type (e.g. IPv4, ARP or something else) */
    NetUnparser::u16(ret, type);

    return ret;
}

string to_string(const EthernetAddress address) {
    stringstream ss{};
    for (auto it = address.begin(); it != address.end(); it++) {
        ss.width(2);
        ss << setfill('0') << hex << int(*it);
        if (it != address.end() - 1) {
            ss << ":";
        }
    }
    return ss.str();
}
string EthernetHeader::to_string() const {
    stringstream ss{};
    ss << "dst=" << ::to_string(dst);
    ss << ", src=" << ::to_string(src);
    ss << ", type=";
    switch (type) {
        case TYPE_IPv4:
            ss << "IPv4";
            break;
        case TYPE_ARP:
            ss << "ARP";
            break;
        default:
            ss << "[unknown type " << hex << type << "!]";
            break;
    }

    return ss.str();
}
