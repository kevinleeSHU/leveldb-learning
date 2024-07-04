#include <iostream>

inline void EncodeFixed32(char* dst, uint32_t value) {
  uint8_t* const buffer = reinterpret_cast<uint8_t*>(dst);

  // Recent clang and gcc optimize this to a single mov / str instruction.
  buffer[0] = static_cast<uint8_t>(value);
  buffer[1] = static_cast<uint8_t>(value >> 8);
  buffer[2] = static_cast<uint8_t>(value >> 16);
  buffer[3] = static_cast<uint8_t>(value >> 24);
}

int main() {
    char buf[4];
    EncodeFixed32(buf, 0x123456);
    for(auto &var : buf) {
        std::cout << static_cast<int>(var) << std::endl;
    }

    return 0;
}