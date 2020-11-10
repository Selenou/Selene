#pragma once

#define SLN_BIND_EVENT(evt) [this](auto&&... args) { return evt(std::forward<decltype(args)>(args)...); } // Variadic Generic Lambda, C++14 (Lambda is faster than bind)