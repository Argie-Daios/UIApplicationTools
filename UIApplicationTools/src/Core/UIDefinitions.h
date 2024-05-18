#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using UIFloat = float;
using UIInt = int;
using UIUnsignedInt = unsigned int;
using UIUnsignedByte = unsigned char;
using UIString = std::string;
using UIBool = bool;
using UIChar = char;
using UIDouble = double;
using UILongInt = long long int;
template<typename T>
using UIVector = std::vector<T>;
template<typename K, typename V>
using UIHashMap = std::unordered_map<K, V>;
template<typename T>
using UIScopePointer = std::unique_ptr<T>;
template<typename T>
using UIReferencePointer = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr UIScopePointer<T> CreateUIScopePointer(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename ... Args>
constexpr UIReferencePointer<T> CreateUIReferencePointer(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}