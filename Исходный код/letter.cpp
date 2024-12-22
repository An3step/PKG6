#include "letter.h"
#include "ui_mainwindow.h"
#include <QDebug>
GLfloat VertexArray[32][3];
GLubyte IndexArray[30][4] = {
    {0,1,17,16},
    {1,2,18,17},
    {2,3,19,18},
    {3,7,23,19},
    {7,6,22,23},

    {6,5,21,22},
    {0, 1, 5, 4},
    {1,2,6,5},
    {2,3,7,6},
    {0,4,12,8},

    {8,12,13,9},
    {13,14,10,9},
    {14,15,11,10},
    {16, 17, 21, 20},
    {17, 18, 22, 21},

    {18, 19, 23, 22},
    {16, 20, 28, 24},
    {24, 28, 29, 25},
    {29, 30, 26, 25},
    {30, 31, 27, 26},

    {5,4,20, 21},
    {4,12,28,20},
    {12,13,29,28},
    {13,14,30,29},
    {14,15,31,30},

    {15,11,27,31},
    {11,10,26,27},
    {10,9,25,26},
    {9,8,24,25},
    {8,0,16,24}
    //////////////////////////
};

letter::letter(QWidget *parent)
    : QGLWidget(parent)
{
    setGeometry(400,200,800,600);
    xRot=-45; yRot=0; zRot=45; zTra=0; nSca=1; xTra = 0; yTra = 0;
    matrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        matrix[i] = new float[3];
    }
}

void letter::initializeGL()
{
    qglClearColor(Qt::white); // цвет для очистки буфера изображения - здесь просто фон окна
    glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
    glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов
    glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
}

void letter::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
    glLoadIdentity();            // присваивает проекционной матрице единичную матрицу

    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth; // отношение высоты окна виджета к его ширине

    // мировое окно
    if (nWidth>=nHeight)
       glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -5.0, 5.0);
    else
       glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -5.0, 5.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void letter::paintGL()
{
    glClearColor(1,1,1,0); // цвет фона
    glClear(GL_COLOR_BUFFER_BIT); // окно виджета очищается текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины
    glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
    glLoadIdentity();           // загружает единичную матрицу моделирования
    // последовательные преобразования
    glScalef(nSca, nSca, nSca);        // масштабирование
    glTranslatef(xTra, -zTra, 0);  // трансляция
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
    glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
    glRotatef(zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z
    drawAxis();
    double e=0,r=0,t=0;
    colour.getRgbF(&e,&r,&t,nullptr);
    glColor4f(e, r, t, 0.0f);
    getVertexArray(1);
    getIndexArray();
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matrix[i][j] = 0;
        }
        matrix[i][i] = 1;
    }
    draw_scaling();
    draw_transfer();
    draw_rotation_x();
    draw_rotation_y();
    draw_rotation_z();
    if(xy_proection)
    {
        draw_xy_projection();
    }
    else if(yz_proection)
    {
        draw_zy_projection();
    }
    else if(xz_proection)
    {
        draw_xz_projection();
    }
    drawFigure();
    QFont tmpfont;
            tmpfont.setFamily("Arial Black");
            tmpfont.setPointSize(10);
            tmpfont.setBold(false);
            glColor3f(0,0,0);
            renderText(10,0.0,0.0,"X",tmpfont);
            glColor3f(0,0,0);
            renderText(0.0,10,0.0,"Y",tmpfont);
            glColor3f(0,0,0);
            renderText(0.0,0.0,10,"Z",tmpfont);

}

/*virtual*/void letter::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   ptrMousePosition = pe->pos();
}

/*virtual*/void letter::mouseReleaseEvent(QMouseEvent* pe) // отжатие клавиши мыши
{

}

/*virtual*/void letter::mouseMoveEvent(QMouseEvent* pe) // изменение положения стрелки мыши
{
   xRot += 1/M_PI*(GLfloat)(pe->y()-ptrMousePosition.y());//height(); // вычисление углов поворота
   yRot += 1/M_PI*(GLfloat)(pe->x()-ptrMousePosition.x());//width();
   ptrMousePosition = pe->pos();
   updateGL(); // обновление изображения
}

/*virtual*/void letter::wheelEvent(QWheelEvent* pe) // вращение колёсика мыши
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   updateGL(); // обновление изображения
}

/*virtual*/void letter::keyPressEvent(QKeyEvent* pe) // нажатие определенной клавиши
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();     // приблизить сцену
      break;

      case Qt::Key_Equal:
         scale_plus();     // приблизить сцену
      break;

      case Qt::Key_Minus:
         scale_minus();    // удалиться от сцены
      break;

      case Qt::Key_W:
         rotate_up();      // повернуть сцену вверх
      break;

      case Qt::Key_S:
         rotate_down();    // повернуть сцену вниз
      break;

      case Qt::Key_A:
        rotate_left();     // повернуть сцену влево
      break;

      case Qt::Key_D:
         rotate_right();   // повернуть сцену вправо
      break;

      case Qt::Key_B:
         translate_down(); // транслировать сцену вниз
      break;

      case Qt::Key_U:
         translate_up();   // транслировать сцену вверх
      break;

      case Qt::Key_L:
         translate_left();
      break;

      case Qt::Key_R:
         translate_right();
      break;

      case Qt::Key_Space:  // клавиша пробела
         defaultScene();   // возвращение значений по умолчанию
      break;

      case Qt::Key_Escape: // клавиша "эскейп"
         this->close();    // завершает приложение
      break;
   }

   updateGL(); // обновление изображения
}

float** letter::returnMatrix()
{
    return matrix;
}


void letter::scale_plus() // приблизить сцену
{
   nSca = nSca*1.1;
}

void letter::scale_minus() // удалиться от сцены
{
   nSca = nSca/1.1;
}

void letter::rotate_up() // повернуть сцену вверх
{
   xRot += 1.0;
}

void letter::rotate_down() // повернуть сцену вниз
{
   xRot -= 1.0;
}

void letter::rotate_left() // повернуть сцену влево
{
   zRot += 1.0;
}

void letter::rotate_right() // повернуть сцену вправо
{
   zRot -= 1.0;
}

void letter::translate_down() // транслировать сцену вниз
{
   zTra -= 0.05;
}

void letter::translate_up() // транслировать сцену вверх
{
    zTra += 0.05;
}

void letter::translate_left()
{
    xTra += 0.05;
}

void letter::translate_right()
{
    xTra -= 0.05;
}

void letter::defaultScene() // наблюдение сцены по умолчанию
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1; xTra = 0; yTra = 0;
}
void letter::drawAxis()
{
    glLineWidth(3.0f);
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glBegin(GL_LINES); // построение линии
       glVertex3f( 10.0f,  0.0f,  0.0f); // первая точка
       glVertex3f(-10.0f,  0.0f,  0.0f); // вторая точка
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
       // ось y зеленого цвета
       glVertex3f( 0.0f,  10.0f,  0.0f);
       glVertex3f( 0.0f, -10.0f,  0.0f);

       glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
       // ось z синего цвета
       glVertex3f( 0.0f,  0.0f,  10.0f);
       glVertex3f( 0.0f,  0.0f, -10.0f);

        glColor4f(0.00f, 0.00f, 0.00f, 0.0f);
       for (float i = -10; i < 10; i+=0.25){
           float k = 20.0;
           glBegin(GL_LINES);
           glVertex3f(i, -1.0 / k, 0.0f);
           glVertex3f(i, 1.0 / k, 0.0f);
           glVertex3f(-1.0 / k, i, 0.0f);
           glVertex3f(1.0 / k, i, 0.0f);
           glVertex3f( 0.0f, 1.0 / k, i);
           glVertex3f( 0.0f, -1.0 / k, i);
       }

    glEnd();
}

void letter::getVertexArray(float k)
{
    VertexArray[0][0] = 0.58*k;
    VertexArray[0][1] = 0;

    VertexArray[1][0] = 0;
    VertexArray[1][1] = 0.58*k;

    VertexArray[2][0] = 0;
    VertexArray[2][1] = 0.87 * k;

    VertexArray[3][0] = 0.58 * k;
    VertexArray[3][1] = 1.46 * k;

    VertexArray[4][0] = 0.58 * k;
    VertexArray[4][1] = 0.29 * k;

    VertexArray[5][0] = 0.29 * k;
    VertexArray[5][1] = 0.58 * k;

    VertexArray[6][0] = 0.29 * k;
    VertexArray[6][1] = 0.87* k;

    VertexArray[7][0] = 0.58 * k;
    VertexArray[7][1] = 1.16 * k;

    for(int i = 8; i <= 15; i++)
    {
        VertexArray[i][0] = 1.75*k - VertexArray[i - 8][0];
        VertexArray[i][1] = VertexArray[i - 8][1];
    }

    for(int i = 0; i < 16; i++)
    {
        VertexArray[i][2] = 0;
    }

    for(int i = 16; i <= 31; i++)
    {
        VertexArray[i][0] = VertexArray[i - 16][0];
        VertexArray[i][1] = VertexArray[i - 16][1];
        VertexArray[i][2] = 0.25*k;
    }

    for(int i = 0; i <= 31; i++)
    {
        std::swap(VertexArray[i][0], VertexArray[i][2]);
    }

    for(int i = 0; i <= 31; i++)
    {
        VertexArray[i][1] *= -1;
    }
}

void letter::getIndexArray()
{

}
void letter::draw_rotation_z()
{
    GLfloat conv[3][3] ;
    conv[0][0]=cos(z_angle*(M_PI/180.0));;
    conv[0][1]=-sin(z_angle*(M_PI/180.0));;
    conv[0][2]=0;

    conv[1][0]=sin(z_angle*(M_PI/180.0));
    conv[1][1]=cos(z_angle*(M_PI/180.0));
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
        matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     {
     c[i][j]+=VertexArray[i][k]*conv[k][j];

     }
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
}
void letter::draw_rotation_y()
{
    GLfloat conv[3][3] ;
    conv[0][0]=cos(y_angle*(M_PI/180.0));
    conv[0][1]=0;
    conv[0][2]=sin(y_angle*(M_PI/180.0));

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=-sin(y_angle*(M_PI/180.0));
    conv[2][1]=0;
    conv[2][2]=cos(y_angle*(M_PI/180.0));
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
     matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     {
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
}
void letter::draw_rotation_x()
{
    GLfloat conv[3][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=cos(x_angle*(M_PI/180.0));
    conv[1][2]=-sin(x_angle*(M_PI/180.0));

    conv[2][0]=0;
    conv[2][1]=sin(x_angle*(M_PI/180.0));
    conv[2][2]=cos(x_angle*(M_PI/180.0));
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
     matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     {
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
}
void letter::draw_transfer()
{
    GLfloat conv[4][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;

    conv[3][0]=x_transfer;
    conv[3][1]=y_transfer;
    conv[3][2]=z_transfer;
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
     matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 4; k++)
     {
         if(k==3)
      c[i][j]+=1*conv[k][j];
         else
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
}
void letter::draw_scaling()
{
    GLfloat conv[3][3] ;
    conv[0][0]=x_scale;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=y_scale;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=z_scale;

    qDebug()<<"scale matrix"<<endl;
    for(int i=0; i < 3; i++)
    {
     qDebug()<<conv[i][0]<<" "<<conv[i][1]<<" "<<conv[i][2]<<" ";
     qDebug()<<endl;
    }
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
     matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
}
void letter::draw_xy_projection()
{
    GLfloat conv[3][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=0;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
     matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
}
void letter::draw_xz_projection()
{
    GLfloat conv[3][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=0;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
     matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
}
void letter::draw_zy_projection()
{
    GLfloat conv[3][3] ;
    conv[0][0]=0;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;
    for(int i=0; i < 32; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    for(int i = 0; i < 32; i++)
    {
        for(int j=0; j < 3; j++)
        {
            VertexArray[i][j] = c[i][j];
        }
    }
    float** newMatrix = new float*[3];
    for(int i = 0; i < 3; i++)
    {
        newMatrix[i] = new float[3];
        for(int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for(int i=0; i < 3; i++)
    {
     for(int j=0; j < 3; j++)
     {
         matrix[i][j] = 0;
     for(int k=0; k < 3; k++)
     {
     matrix[i][j] += newMatrix[i][k]*conv[k][j];
     }
     }
    }
    for(int i = 0; i < 3; i++)
    {
        delete newMatrix[i];
    }
    delete[] newMatrix;
}
void letter::drawFigure(){
    glVertexPointer(3, GL_FLOAT, 0, VertexArray);
    glDrawElements(GL_QUADS, 120, GL_UNSIGNED_BYTE, IndexArray);
}
