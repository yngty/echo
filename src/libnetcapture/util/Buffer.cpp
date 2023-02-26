//
// Created by yngty on 2023/2/26.
//

#include "Buffer.h"

using namespace std;
void Buffer::remove_prefix(const size_t n) {
    if (n > str().size()) {
        throw out_of_range("Buffer::remove_prefix");
    }
    starting_offset_ += n;
    if (storage_ && starting_offset_ == storage_->size()) {
        storage_.reset();
    }
}