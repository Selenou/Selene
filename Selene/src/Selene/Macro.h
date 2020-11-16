#pragma once

#include "Log.h"

#define SLN_ENGINE_ASSERT(x, ...) if(!x) { SLN_ENGINE_CRITICAL(__VA_ARGS__); __debugbreak(); } 
#define SLN_BIND_EVENT(evt) [this](auto&&... args) { return evt(std::forward<decltype(args)>(args)...); } // Variadic Generic Lambda, C++14 (Lambda is faster than bind)