#include"global_values.h"

float	globals::Priority = 0.0;
uint	globals::defaultShader;
uint	globals::defaultVAO;
uint	globals::defaultVBO;
uint	globals::defaultTex = 0;
bool	globals::eventAble = true;//�¼��Ƿ����
bool	globals::timerAble = true;//��ʱ���Ƿ񱻿���
bool	globals::transViewport = true;
float	globals::win_w = 600;//��ʵ���
float	globals::win_h = 600;
float	globals::pre_w = 600;//���ڱ仯֮ǰ��ǰ�Ŀ��
float	globals::pre_h = 600;
float	globals::scaleTimes = 1.0;
int		globals::clickX = 0;
int		globals::clickY = 0;
bool	globals::useScale = true;//��ͼ�Ƿ�ʹ�����ţ���glPixel�Ƿ�����
bool	globals::sticking = false;//��곤��
bool	globals::mouseMoved = false;//��갴�º��Ƿ��ƶ��������ж�����Ƿ񳤰�
int		globals::mouseX = 0;
int		globals::mouseY = 0;//ʵʱ���������ڴ������λ��
int		globals::mBtn = 0;
int		globals::mState = 0;//ʵʱ�İ��������״̬
float	globals::deltaX = 0;//һ���϶����൱����һ����仯��
float	globals::deltaY = 0;
int		globals::oldX;
int		globals::oldY;
bool	globals::specialKey = true;//�Ƿ������ⰴ��
Color	globals::curColor = Color(25, 125, 255);
GLenum	globals::currentMode;
float	globals::curPriority = 0.0;
Color	globals::curColor3 = Color(25, 125, 255);
mat4	globals::curModel = gm::mat4(1.0f);
vec3	globals::curNormal = gm::vec3(1.0f);
float	globals::translateX = 0;
float	globals::translateY = 0;//����ڣ�0,0�����ƽ�Ƶ�Ŀ��
int		globals::timeDelay = 0;//��ʱ���ӳ�
bool	globals::fixed = false;
bool	globals::LEFT_UP = true;
float	globals::line_width = 1;
float	globals::point_size = 1;
float	globals::origin_x = 0.0f;
float	globals::origin_y = 0.0f;
bool	globals::isEditorMode{ 1 };