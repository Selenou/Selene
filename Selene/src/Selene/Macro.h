#pragma once

//#define SLN_BIND_EVENT(evt) std::bind(&evt, this, std::placeholders::_1)
//#define SLN_BIND_EVENT(evt) [this](auto& x) { return evt(x); } // Lambda is faster than bind (Generic Lambda, C++14)
#define SLN_BIND_EVENT(evt) [this](auto&&... args) { return evt(std::forward<decltype(args)>(args)...); } // Variadic Generic Lambda, C++14