#ifndef __UTILS_ID_GENERATOR_HPP__
#define __UTILS_ID_GENERATOR_HPP__

namespace utils {
    template <typename t>
    auto id_generator() {
        static unsigned long long next_id = 0;
        return ++next_id;
    }
}

#endif
