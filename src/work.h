#pragma once

#include <string>

/// @brief Executes a "slow" computation step (sleeps for 7 seconds and prints the name).
/// @param name Name of the computation step.
void slow(const std::string& name);

/// @brief Executes a "quick" computation step (sleeps for 1 second and prints the name).
/// @param name Name of the computation step.
void quick(const std::string& name);

/// @brief Executes the computation scheme for Variant 22 in minimum time
/// with the minimum number of threads, then prints elapsed time and "Work is done!".
void work();