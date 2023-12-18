#ifndef GLVIEW_H
#define GLVIEW_H

#include <QFloat16>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLWidget>

#include "../source/controller.h"
#include "../source/model.h"

#define WIDTH 800
#define HEIGHT 560
#define K 0.001f
#define K_ORTHO 4.0f

class GlView : public QOpenGLWidget {
  Q_OBJECT

 private:
  s21::Controller controller;
  float left;
  float right;
  float bottom;
  float top;

  QPoint lastMousePosition;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void updateStatusBarText(QString text);
  void drawLineView();
  void drawPointView();

 public:
  GlView(QWidget *parent = nullptr);
  void open_file(char *filename);
  s21::Vertex vertex;
  s21::Polygons *polygons = nullptr;
  int polygons_size;

  int ortho;
  quint8 line_width;
  quint8 point_width;
  quint8 draw_style;
  quint8 point_round;
  quint8 joy_step;

  QString background_color;
  qfloat16 bg_red;
  qfloat16 bg_green;
  qfloat16 bg_blue;
  qfloat16 bg_alpha;

  QString line_color;
  qfloat16 line_red;
  qfloat16 line_green;
  qfloat16 line_blue;
  qfloat16 line_alpha;

  QString point_color;
  qfloat16 point_red;
  qfloat16 point_green;
  qfloat16 point_blue;
  qfloat16 point_alpha;

 signals:
  void signalTextToForm(const QString &message);
};

#endif  // GLVIEW_H
