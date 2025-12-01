#pragma once

#include <functional>
#include <windows.h>

#include "auge.h"

const POINT INVALID_WINDOW_MOUSE_POS{-1, -1};

LoopThread createMousePositionThread(HWND hWindow, std::function<void(POINT)> command, long timeout);
