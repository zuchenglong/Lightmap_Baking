#pragma once

#include <string>

// 是否开启 渲染线程
#define ENABLE_BAKETHREAD 1
// 主线程 画面是否上屏
#define DRAW_SCREEN_MAINTHREAD 1
// 烘焙线程 画面是否上屏
#define DRAW_SCREEN_BAKETHREAD 0

const unsigned int width = 800, height = 600;

static std::string ProjectDir(PROJECT_DIR);