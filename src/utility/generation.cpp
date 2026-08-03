#include <cstdint>
#include <random>
#include "generation.h"

namespace cerberus 
{
namespace generation
{
    std::uint64_t generateId() 
    {
        // VERY basic RN generator; for demonstration purposes.
        std::mt19937 mt;
        return mt();
    }
}
}
