#!/usr/bin/env python3

"""视点系统和投影矩阵"""

import numpy as np
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

dist = 5.0                      # 全局变量：相机与坐标原点之间的距离
azim = 0.0                      # 全局变量：方位角
elev = 0.0                      # 全局变量：高度角
fovy = 40.0                     # 全局变量：水平视野角度
near = 2.0                      # 全局变量：最近对焦距离
far = 1000.0                    # 全局变量：最远对焦距离
cam = (0.0, 0.0, 5.0)           # 全局变量：相机位置
csize = (800, 600)              # 全局变量：窗口大小
aspect = csize[0]/csize[1]      # 全局变量：窗口宽高比
mouse_pos = None                # 全局变量：鼠标位置

def click(btn, state, x, y):
    """鼠标按键和滚轮事件函数"""

    global mouse_pos

    if (btn == 0 or btn == 2) and state == 0: # 左键或右键被按下
        mouse_pos = (x, y) # 记录鼠标位置

    glutPostRedisplay() # 更新显示

def drag(x, y):
    """鼠标拖拽事件函数"""

    global mouse_pos, azim, elev, cam

    dx, dy = x-mouse_pos[0], y-mouse_pos[1] # 计算鼠标拖拽距离
    mouse_pos = (x, y) # 更新鼠标位置
    azim = azim - 180*dx/csize[0] # 计算方位角
    elev = elev + 90*dy/csize[1] # 计算高度角

    d = dist * np.cos(np.radians(elev))
    x_cam = d*np.sin(np.radians(azim))
    y_cam = dist*np.sin(np.radians(elev))
    z_cam = d*np.cos(np.radians(azim))
    cam = [x_cam, y_cam, z_cam] # 更新相机位置
 
    glutPostRedisplay() # 更新显示

def reshape(w, h):
    """改变窗口大小事件函数"""

    global csize, aspect    

    csize = (w, h) # 保存窗口大小
    aspect = w/h if h > 0 else 1e4 # 更新窗口宽高比
    glViewport(0, 0, w, h) # 设置视口

    glutPostRedisplay() # 更新显示

def draw():
    """绘制模型"""

    glClear(GL_COLOR_BUFFER_BIT)            # 清除缓冲区

    glMatrixMode(GL_PROJECTION)             # 操作投影矩阵
    glLoadIdentity()                        # 将投影矩阵设置为单位矩阵
    gluPerspective(fovy, aspect, near, far) # 生成透视投影矩阵
    gluLookAt(*cam, *[0,0,0], *[0,1,0])     # 设置视点矩阵

    glBegin(GL_TRIANGLES)                   # 开始绘制三角形
    glColor(1.0, 0.0, 0.0)                  # 设置当前颜色为红色
    glVertex(0.0, 1.0, 0.0)                 # 设置顶点
    glColor(0.0, 1.0, 0.0)                  # 设置当前颜色为绿色
    glVertex(-1.0, -1.0, 0.0)               # 设置顶点
    glColor(0.0, 0.0, 1.0)                  # 设置当前颜色为蓝色
    glVertex(1.0, -1.0, 0.0)                # 设置顶点
    glEnd()                                 # 结束绘制三角形

    glBegin(GL_LINES)                       # 开始绘制线段
    glColor(1.0, 0.0, 1.0)                  # 设置当前颜色为紫色
    glVertex(0.0, 0.0, -1.0)                # 设置线段顶点（z轴负方向）
    glColor(0.0, 0.0, 1.0)                  # 设置当前颜色为蓝色
    glVertex(0.0, 0.0, 1.0)                 # 设置线段顶点（z轴正方向）
    glEnd()                                 # 结束绘制线段

    glFlush()                               # 执行缓冲区指令

if __name__ == "__main__":
    glutInit()                              # 1. 初始化glut库
    glutInitWindowSize(*csize)              # 2.1 设置窗口大小
    glutCreateWindow('OpenGL Demo')         # 2.2 创建glut窗口
    glutDisplayFunc(draw)                   # 3.1 绑定模型绘制函数
    glutReshapeFunc(reshape)                # 3.2 绑定窗口大小改变事件函数
    glutMouseFunc(click)                    # 3.3 绑定鼠标按键
    glutMotionFunc(drag)                    # 3.4 绑定鼠标拖拽事件函数
    glutMainLoop()                          # 4. 进入glut主循环
