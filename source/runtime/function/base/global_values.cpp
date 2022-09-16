#include"global_values.h"

float	globals::Priority = 0.0;
uint	globals::defaultShader;
uint	globals::defaultVAO;
uint	globals::defaultVBO;
uint	globals::defaultTex = 0;
bool	globals::eventAble = true;//事件是否可用
bool	globals::timerAble = true;//定时器是否被可用
bool	globals::transViewport = true;
float	globals::win_w = 600;//真实宽高
float	globals::win_h = 600;
float	globals::pre_w = 600;//窗口变化之前的前的宽高
float	globals::pre_h = 600;
float	globals::scaleTimes = 1.0;
int		globals::clickX = 0;
int		globals::clickY = 0;
bool	globals::useScale = true;//绘图是否使用缩放，即glPixel是否缩放
bool	globals::sticking = false;//鼠标长按
bool	globals::mouseMoved = false;//鼠标按下后是否移动，用来判断鼠标是否长按
int		globals::mouseX = 0;
int		globals::mouseY = 0;//实时的鼠标相对于窗口鼠标位置
int		globals::mBtn = 0;
int		globals::mState = 0;//实时的按键和鼠标状态
float	globals::deltaX = 0;//一次拖动的相当于上一个点变化量
float	globals::deltaY = 0;
int		globals::oldX;
int		globals::oldY;
bool	globals::specialKey = true;//是否是特殊按键
Color	globals::curColor = Color(25, 125, 255);
GLenum	globals::currentMode;
float	globals::curPriority = 0.0;
Color	globals::curColor3 = Color(25, 125, 255);
mat4	globals::curModel = gm::mat4(1.0f);
vec3	globals::curNormal = gm::vec3(1.0f);
float	globals::translateX = 0;
float	globals::translateY = 0;//相对于（0,0）点的平移的目标
int		globals::timeDelay = 0;//定时器延迟
bool	globals::fixed = false;
bool	globals::LEFT_UP = true;
float	globals::line_width = 1;
float	globals::point_size = 1;
float	globals::origin_x = 0.0f;
float	globals::origin_y = 0.0f;
bool	globals::isEditorMode{ 1 };