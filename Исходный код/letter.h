#ifndef LETTER_H
#define LETTER_H

#include <QMainWindow >

#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QGLWidget>


class letter : public QGLWidget
{
public:
   GLfloat c[64][3];
   GLfloat xRot; // переменная хранит угол поворота вокруг оси X
   GLfloat yRot; // переменная хранит угол поворота вокруг оси Y
   GLfloat zRot; // переменная хранит угол поворота вокруг оси Z
   GLfloat zTra = 0; // переменная хранит величину трансляции оси Z
   GLfloat xTra = 0;
   GLfloat yTra = 0;
   float** matrix;
   GLfloat nSca = 1; // переменная отвечает за масштабирование обьекта
   int check=0;
   float x_angle = 0;
   float y_angle = 0;
   float z_angle = 0;
   float x_transfer=0,y_transfer=0,z_transfer=0,x_scale=1,y_scale=1,z_scale=1;
   QColor colour;
   bool xz_proection = false, xy_proection = false, yz_proection = false;
   QPoint ptrMousePosition; // переменная хранит координату указателя мыши в момент нажатия
   void scale_plus();     // приблизить сцену
   void scale_minus();    // удалиться от сцены
   void rotate_up();      // повернуть сцену вверх
   void rotate_down();    // повернуть сцену вниз
   void rotate_left();    // повернуть сцену влево
   void rotate_right();   // повернуть сцену вправо
   void translate_down(); // транслировать сцену вниз
   void translate_up();   // транслировать сцену вверх
   void translate_left();
   void translate_right();
   void defaultScene();   // наблюдение сцены по умолчанию

   void drawAxis();       // построить оси координат

   void drawFigure();     // построить фигуру
   void getVertexArray(float k);
   void getIndexArray();
   void draw_xy_projection();
   void draw_xz_projection();
   void draw_zy_projection();
   void draw_scaling();
   void draw_transfer();
   void draw_rotation_x();
   void draw_rotation_y();
   void draw_rotation_z();
  /*virtual*/ void initializeGL();                     // метод для проведения инициализаций, связанных с OpenGL
   /*virtual*/ void resizeGL(int nWidth, int nHeight);  // метод вызывается при изменении размеров окна виджета
   /*virtual*/ void paintGL();                          // метод, чтобы заново перерисовать содержимое виджета

   /*virtual*/ void mousePressEvent(QMouseEvent* pe);   // методы обработки события мыши при нажатии клавиши мыши
   /*virtual*/ void mouseMoveEvent(QMouseEvent* pe);    // методы обработки события мыши при перемещении мыши
   /*virtual*/ void mouseReleaseEvent(QMouseEvent* pe); // методы обработки событий мыши при отжатии клавиши мыши
   /*virtual*/ void wheelEvent(QWheelEvent* pe);        // метод обработки событий колесика мыши
   /*virtual*/ void keyPressEvent(QKeyEvent* pe);       // методы обработки события при нажатии определенной клавиши

   float** returnMatrix();

public:
    letter(QWidget *parent = nullptr);
virtual ~letter() = default;
};


#endif // LETTER_H
