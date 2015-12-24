#pragma once

#include <string>
#include <memory>
#include <exception>
#include <vector>
#include <future>
#include <iostream>

#include <gsl.h>
#include <debugbreak.h>

#undef Expects
#undef Ensures
#include "HE_Assert.h" // Include after gsl.h, we want to use our own contract macros
#include "HE_String.h"
