#pragma once

#include <string>

// �Ƿ��� ��Ⱦ�߳�
#define ENABLE_BAKETHREAD 1
// ���߳� �����Ƿ�����
#define DRAW_SCREEN_MAINTHREAD 1
// �決�߳� �����Ƿ�����
#define DRAW_SCREEN_BAKETHREAD 0

const unsigned int width = 800, height = 600;

static std::string ProjectDir(PROJECT_DIR);