//
// Created by yngty on 2023/2/26.
//

#ifndef ECHO_BUFFER_H
#define ECHO_BUFFER_H

#include <string>
#include <string_view>
#include <memory>

class Buffer {
private:
    std::shared_ptr<std::string> storage_{};
    size_t starting_offset_ {};

public:
    Buffer() = default;

    Buffer(std::string && str) noexcept : storage_(std::make_shared<std::string>(std::move(str))){}

    std::string_view str() const {
        if (!storage_)
            return {};
        return {storage_->data() + starting_offset_, storage_->size() - starting_offset_};
    }

    operator std::string_view() const { return str(); }

    uint8_t at(const size_t n) const { return str().at(n); }

    size_t size() const { return str().size(); }

    std::string copy() const { return std::string(str()); }

    void remove_prefix(const size_t n);
};


#endif //ECHO_BUFFER_H