#include"base/ui_base.h"
#include"render/render.h"
#include"audio/audio.h"
#include"ui/window.h"
#include"scene/scene_builder.h"
void* ui::win;
char Encoder::outbuf[4096];
int ui::BaseWidget::curPrior = 1.0;
StringConventer sc;
double globals::gameTime;
double globals::clockTime;
double globals::frameps = 60.0f;//记录平均的帧率
double globals::frameTime = 10;
bool Window::first_win = false;