#include <cstdint>
#include <iostream>

const char* GetVarint32PtrFallback(const char* p, const char* limit,
                                   uint32_t* value) {
  uint32_t result = 0;
  for (uint32_t shift = 0; shift <= 28 && p < limit; shift += 7) {
    uint32_t byte = *(reinterpret_cast<const uint8_t*>(p));
    p++;
    if (byte & 128) {
      // More bytes are present
      result |= ((byte & 127) << shift);
    } else {
      result |= (byte << shift);
      *value = result;
      return reinterpret_cast<const char*>(p);
    }
  }
  return nullptr;
}

const char* GetVarint32Ptr(const char* p, const char* limit,
                                  uint32_t* value) {
  if (p < limit) {
    uint32_t result = *(reinterpret_cast<const uint8_t*>(p));
    // 每字节最高位为1，表示后续字节还有数据；最高位为0，表示当前字节为最后一个有效字节
    if ((result & 128) == 0) {
      *value = result;
      return p + 1;
    }
  }
  return GetVarint32PtrFallback(p, limit, value);
}

int main() {
    const char code[] = {-0x25, -0x41, 0x01};
    const char* limit = code + sizeof(code);
    uint32_t value;
    const char *result = GetVarint32Ptr(code, limit, &value);

    if (result != nullptr) {
        std::cout << std::hex << value << std::endl;
        std::cout << static_cast<const void*>(code) << std::endl;
        std::cout << static_cast<const void*>(result) << std::endl;
    }

    return 0;
}
