#pragma once

#include <iostream>
#include <memory>
#include <utility>

#ifndef VANIM_WINDOWS
#error Only supports Windows!
#endif

#define VANIM_INFO(message) std::cout << "\033[32m[" << __FILE__ << ":" << __LINE__ << "]: " << message << "\033[0m" << std::endl;
#define VANIM_WARN(message) std::cout << "\033[33m[" << __FILE__ << ":" << __LINE__ << "]: " << message << "\033[0m" << std::endl;
#define VANIM_ERROR(message) std::cout << "\033[31m[" << __FILE__ << ":" << __LINE__ << "]: " << message << "\033[0m" << std::endl;

template <typename T>
decltype(auto) Move(T&& arg)
{
	return std::move(arg);
}

// ---------------- smart pointers --------------------------------

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Shared<T> MakeShared(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Unique<T> MakeUnique(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Weak = std::weak_ptr<T>;

// ----------------------------------------------------------------