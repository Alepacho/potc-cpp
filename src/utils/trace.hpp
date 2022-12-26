#ifndef POTC_TRACE_H
#define POTC_TRACE_H

#include <iomanip>
#include <iostream>
#include <sstream>

template <typename T> static std::string hex(T i) {
	std::stringstream stream; // << std::setfill('0')
	stream << std::setw(sizeof(T) * 2) << std::hex << i;
	return stream.str();
}

template <typename T> static std::string tstr(T v) {
  	return std::to_string(v);
}

template <typename T> static void trace(T message) {
  	std::cout << message << std::endl;
}

template <typename T> static void trace(std::string info, T message) {
	std::cout << '[' << info << ']';
	std::cout << ' ';
	std::cout << message << std::endl;
}

#endif // POTC_TRACE_H