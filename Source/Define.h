#pragma once

#include <string>

// 主线程 画面是否上屏
#define DRAW_SCREEN_MAINLOOP 1
// 是否开启 渲染线程
#define ENABLE_RENDERTHREAD 1

const unsigned int width = 800, height = 600;

static std::string ProjectDir(PROJECT_DIR);