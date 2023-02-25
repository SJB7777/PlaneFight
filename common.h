#ifndef __COMMON_H__
#define __COMMON_H__

#include "logger.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <memory>
#include <iostream>
#include <random>
#include <charconv>


#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

enum class ApplicationStates {
	Startup,
	Loading,
	Menu,
	Running,
	Paused,
	GameOver,
	Quiting
}; 

inline ApplicationStates ApplicationState = ApplicationStates::Running;

bool IsAnyKeyPressed();

#endif // __COMMON_H__
