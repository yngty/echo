//
// Created by yngty on 2023/2/26.
//

#ifndef ECHO_PARSER_H
#define ECHO_PARSER_H

#include "Buffer.h"

#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>

enum class ParseResult {
    NoError = 0,
    BadChecksum,
    PacketTooShort,
    WrongIPVersion,
    HeaderTooShort,
    TruncatedPacket,
    Unsupported
};

std::string as_string(const ParseResult r);
class NetParser {
private:
    Buffer buffer_;
    ParseResult error_ = ParseResult::NoError;

    void _check_size(const size_t size);

    template<typename T>
    T _parse_int();

public:
    NetParser(Buffer buffer) : buffer_(buffer) {}
    Buffer buffer() const { return buffer_; }
    ParseResult get_error() const { return error_; }
    void set_error(ParseResult res) { error_ = res; }
    bool error() const { return get_error() != ParseResult::NoError; }

    uint32_t u32();
    uint16_t u16();
    uint8_t u8();

    void remove_prefix(const size_t n);
};

struct NetUnparser {
    template<typename T>
    static void _unparse_int(std::string& s, T val);
    static void u32(std::string &s, const uint32_t val);
    static void u16(std::string &s, const uint16_t val);
    static void u8(std::string &s, const uint8_t val);
};


#endif //ECHO_PARSER_H
