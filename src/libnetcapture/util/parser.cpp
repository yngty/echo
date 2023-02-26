//
// Created by yngty on 2023/2/26.
//

#include "parser.h"

using namespace std;

string as_string(const ParseResult r) {
    static constexpr const char *names[] = {
            "NoError",
            "BadChecksum",
            "PacketTooShort",
            "WrongIPVersion",
            "HeaderTooShort",
            "TruncatedPacket",
    };

    return names[static_cast<size_t>(r)];
}

void NetParser::_check_size(const size_t size) {
    if (size > buffer_.size()) {
        set_error(ParseResult::PacketTooShort);
    }
}

template<typename T>
T NetParser::_parse_int() {
    constexpr size_t len = sizeof (T);
    _check_size(len);
    if (error()) {
        return 0;
    }

    T ret = 0;
    for (size_t i = 0; i < len; i++) {
        ret <<= 8;
        ret += uint8_t (buffer_.at(i));
    }
    buffer_.remove_prefix(len);

    return ret;
}

void NetParser::remove_prefix(const size_t n) {
    _check_size(n);
    if (error()) {
        return;
    }
    buffer_.remove_prefix(n);
}

uint32_t NetParser::u32() { return _parse_int<uint32_t>(); }

uint16_t NetParser::u16() { return _parse_int<uint16_t>(); }

uint8_t NetParser::u8() { return _parse_int<uint8_t>(); }

template <typename T>
void NetUnparser::_unparse_int(string &s, T val) {
    constexpr size_t len = sizeof(T);
    for (size_t i = 0; i < len; ++i) {
        const uint8_t the_byte = (val >> ((len - i - 1) * 8)) & 0xff;
        s.push_back(the_byte);
    }
}

void NetUnparser::u32(string &s, const uint32_t val) { return _unparse_int<uint32_t>(s, val); }

void NetUnparser::u16(string &s, const uint16_t val) { return _unparse_int<uint16_t>(s, val); }

void NetUnparser::u8(string &s, const uint8_t val) { return _unparse_int<uint8_t>(s, val); }
