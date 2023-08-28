#pragma once

#include <time.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <type_traits>

#define _ASSERT(msg) Debug::assert(msg, __FILE__, __LINE__, false)
#define _ASSERT_FATAL(msg) Debug::assert(msg, __FILE__, __LINE__, true)

#ifdef DEBUG_USE_SIMPLIFIED_NAMES

typedef std::string str;
//etc.

#endif

namespace Debug {

	template <typename T>
    using isStrable = std::bool_constant<
        !std::is_convertible_v<T, std::string> && 
        !std::is_same_v<T, std::stringstream> &&
        !std::is_same_v<T, std::string>
    >;

	inline void assert(const char* message, const char* file = __FILE__, int line = __LINE__, bool fatal = false) {

		time_t timet = time(NULL);
		std::string t = std::string(ctime(&timet));
		t.replace(t.find("\n"), 2, "");
		
		std::cout << "[TIME:" + t + "][TICKS:" + std::to_string(SDL_GetTicks()) + "][FILE:" + file + "][LINE:" + std::to_string(line) + "]" + " DEBUG " + (fatal ? "FATAL:" : ": ") + message + "\n";
		if (fatal) {
			
			SDL_Quit();
			std::terminate();
		}
		

	}

	template <typename T, typename = typename std::enable_if_t<isStrable<T>::value>>
	inline void assert(const T& message, const char* file = __FILE__, int line = __LINE__, bool fatal = false) {

		assert(std::to_string(message).c_str(), file, line, fatal);

	}

	inline void assert(const std::string& message, const char* file = __FILE__, int line = __LINE__, bool fatal = false) {

		assert(message.c_str(), file, line, fatal);

	}



}