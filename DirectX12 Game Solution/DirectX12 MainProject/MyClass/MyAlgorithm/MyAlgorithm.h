#pragma once
#include "Base/pch.h"

#define MathHelper_Pi             ((float)3.141592654f)
#define MathHelper_Atan2(y,x)     (::atan2f(y, x)    * (180.0f / MathHelper_Pi))
