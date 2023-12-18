/**
 * @file
 * Заголовочный файл, описывающий контроллер.
 *
 */
#ifndef CPP4_3DVIEWER_V2_0_1_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_1_CONTROLLER_H

#include "model.h"

namespace s21 {
class Controller {
 public:
  ~Controller() = default;
  /*!
\brief Метод для парсинга файла объекта
\param filename - Имя файла.
\param vertex - Указатель на структуру вершин.
\param polygons - Указатель на структуру полигонов.
\param polygons_size - Указатель на количество полигонов.
\return Возвращает вВозвращает 1 в случае ошибки и 0 при нормальной отработке
программы.

Данный метод производит парсинг файла объекта, вычленяет координаты вершин,
полигонов и их количество.

*/
  int ParseObject(const char *filename, s21::Vertex *vertex,
                  s21::Polygons **polygons, int *polygons_size);
  /*!
\brief Метод для центровки модели
\param inp - Указатель на структуру вершин.

Данный метод производит выравнивание отображаемого объекта по центру.

*/
  void center(Vertex *inp);

  /*!
\brief Метод для перемещения модели по оси Х
\param inp - Указатель на структуру вершин.
\param value - Значение, на которое происходит смещение.

Данный метод производит смещение по оси Х на заданное значение.

*/
  void moveOX(Vertex *inp, double value);

  /*!
\brief Метод для перемещения модели по оси У
\param inp - Указатель на структуру вершин.
\param value - Значение, на которое происходит смещение.

Данный метод производит смещение по оси У на заданное значение.

*/
  void moveOY(Vertex *inp, double value);

  /*!
\brief Метод для перемещения модели по оси Z
\param inp - Указатель на структуру вершин.
\param value - Значение, на которое происходит смещение.

Данный метод производит смещение по оси Z на заданное значение.

*/
  void moveOZ(Vertex *inp, double value);

  void normalize_size(Vertex *inp);

  /*!
\brief Метод для масштабирования модели
\param inp - Указатель на структуру вершин.
\param value - Значение, кратно которому происходит масштабирование.

Данный метод производит масштабирования модели.

*/
  void scale(Vertex *inp, double value);

  /*!
\brief Метод для вращения модели по оси Х
\param inp - Указатель на структуру вершин.
\param angle - Значение угла, на которое происходит вращение.

Данный метод производит вращение по оси Х на заданное значение.

*/
  void rotateOX(Vertex *inp, double angle);

  /*!
\brief Метод для вращения модели по оси У
\param inp - Указатель на структуру вершин.
\param angle - Значение угла, на которое происходит вращение.

Данный метод производит вращение по оси У на заданное значение.

*/
  void rotateOY(Vertex *inp, double angle);

  /*!
\brief Метод для вращения модели по оси Z
\param inp - Указатель на структуру вершин.
\param angle - Значение угла, на которое происходит вращение.

Данный метод производит вращение по оси Z на заданное значение.

*/
  void rotateOZ(Vertex *inp, double angle);

  /*!
\brief Метод для очистки памяти, выделенной подструктуры данных
\param vertex - Указатель на структуру вершин.
\param polygons - Указатель на структуру полигонов.

Данный метод производит очистку памяти, выделенной под структуры данных.

*/
  void kill_structs(Vertex vertex, Polygons *polygons, int polygons_size);

 private:
  Fascade model;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_CONTROLLER_H
