/**
 * @file
 * Заголовочный файл, описывающий модель.
 *
 */

#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_H
#define CPP4_3DVIEWER_V2_0_1_MODEL_H

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

namespace s21 {
/*!
 \brief Структура вершин

 Данная структура содержит минимальные и максимальные значения по осям
 координат, координаты вершин и их количество.
*/
typedef struct Vertex {
  int amount_vert;
  double *coord;
  double minMaxX[2];
  double minMaxY[2];
  double minMaxZ[2];
} Vertex;

/*!
     \brief Структура, описывающая полигон

     Данная структура содержит указатель на массив с вершинами полигона,
   количество полигонов.

*/
typedef struct Polygons {
  int *p;
  int amount_p;
} Polygons;

/*!
     \brief Структура, описывающая полную отображаемую модель

     Данная структура содержит структуры полигона, координат, а также
   количество полигонов.

*/
typedef struct Main_parser {
  Vertex *v;
  Polygons *p;
  int *amount_polygons;
} Main_parser;

class Parser {
 public:
  Parser() {}
  Parser(const Parser &);
  // Parser& operator=(Parser&);
  ~Parser() = default;
  /*!
\brief Метод для парсинга файла объекта
\param filename - Имя файла.
\param vertex - Указатель на структуру вершин.
 \param polygons - Указатель на структуру полигонов.
 \param polygons_size - Указатель на количество полигонов.
\return Возвращает 1 в случае ошибки и 0 при нормальной отработке программы.

Данный метод производит парсинг файла объекта, вычленяет координаты вершин,
полигонов и их количество.

*/

  int MainParser(const char *filename, Vertex *vertex, Polygons **polygons,
                 int *polygons_size);
  static Parser &getParser() {
    static Parser parser;
    return parser;
  }

  /*!
\brief Метод для очистки памяти, выделенной подструктуры данных
\param vertex - Указатель на структуру вершин.
\param polygons - Указатель на структуру полигонов.

Данный метод производит очистку памяти, выделенной под структуры данных.

*/
  void kill_structs(Vertex vertex, Polygons *polygons, int polygons_size);

 private:
  /*!
\brief Метод для парсинга вершин объекта
\param line - Подаваемая строка.
\param vertex - Указатель на структуру вершин.
 \param line_counter - Указатель на счетчик строк.
\return Возвращает 1 в случае ошибки и 0 при нормальной отработке программы.

Данный метод производит парсинг файла объекта, вычленяет координаты вершин.

*/
  int parse_v(char *line, Vertex *vertex, int *line_counter);
  /*!
\brief Метод, определяющий экстремумы по осям координат
\param vertex - Структура вершин.
\param local_i - Намименование оси координат.
\param num_val - Значение координаты.

Данный метод вычисляет экстремумы по осям координат и записывает в структуру
вершин.

*/
  static void SetExtrema(Vertex *vertex, int local_i, double num_val);
  /*!
\brief Метод для парсинга полигонов объекта из файла
\param line - Подаваемая строка.
\param polygons_arr - Указатель на структуру полигонов.
\param polygons_count - Указатель на счетчик полигонов.
\param vertex - Структура вершин.
\param allocated_rows - Указатель на количество строк, на которые выделена
память.
\return Возвращает 1 в случае ошибки и 0 при нормальной отработке
программы.

Данный метод производит парсинг файла объекта, вычленяет координаты полигонов и
их количество.

*/
  int parse_f(struct Polygons **polygons_arr, char *line, int *polygons_count,
              Vertex vertex, int *allocated_rows);
};

class Affine {
 public:
  Affine(){};
  ~Affine() = default;

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
};

class Model {
 public:
  Model(){};
  ~Model() = default;
  /*!
\brief Метод для парсинга файла объекта
\param filename - Имя файла.
\param vertex - Указатель на структуру вершин.
\param polygons - Указатель на структуру полигонов.
\return Возвращает Возвращает 1 в случае ошибки и 0 при нормальной отработке
программы.

Данный метод производит парсинг файла объекта, вычленяет координаты вершин,
полигонов и их количество.

*/
  int ParseObject(const char *filename, Vertex *vertex, Polygons **polygons,
                  int *polygons_size);
  Affine affine;
};

class Strategy {
 public:
  virtual ~Strategy() = default;
  /*!
\brief Виртуальный обобщенный метод для трансформации объекта (вращения,
перемещения) \param inp - Указатель на структуру вершин. \param value -
Величина, на которую будет произведено вращение (перемещение). \param XYZ -
Символ, обозначающий необходимую ось координат.

*/
  virtual void Transform(Vertex *inp, double value, char XYZ) = 0;
};

class MoveStrategy : public Strategy {
 public:
  MoveStrategy(Model &model);
  /*!
\brief Метод для перемещения объекта
\param inp - Указатель на структуру вершин.
\param value - Величина, на которую будет произведено перемещение.
\param XYZ - Символ, обозначающий необходимую ось координат.

*/
  void Transform(Vertex *inp, double value, char XYZ) override;

 private:
  Model model;
};

class RotateStrategy : public Strategy {
 public:
  RotateStrategy(Model &model);
  /*!
\brief Метод для вращения объекта
\param inp - Указатель на структуру вершин.
\param value - Величина, на которую будет произведено вращение.
\param XYZ - Символ, обозначающий необходимую ось координат.

*/
  void Transform(Vertex *inp, double value, char XYZ) override;

 private:
  Model model;
};

class Fascade {
 public:
  ~Fascade() = default;
  int ParseObject(const char *filename, Vertex *vertex, Polygons **polygons,
                  int *polygons_size) {
    return model.ParseObject(filename, vertex, polygons, polygons_size);
  }
  /*!
\brief Метод для вращения объекта
\param inp - Указатель на структуру вершин.
\param value - Величина, на которую будет произведено вращение.
\param XYZ - Символ, обозначающий необходимую ось координат.

*/
  void rotateOXYZ(Vertex *inp, double value, char XYZ) {
    RotateStrategy rotate(model);
    rotate.Transform(inp, value, XYZ);
  }
  /*!
\brief Метод для перемещения объекта
\param inp - Указатель на структуру вершин.
\param value - Величина, на которую будет произведено перемещение.
\param XYZ - Символ, обозначающий необходимую ось координат.

*/
  void moveOXYZ(Vertex *inp, double value, char XYZ) {
    MoveStrategy move(model);
    move.Transform(inp, value, XYZ);
  }
  /*!
\brief Метод для нормализации величины объекта или его центровки
\param inp - Указатель на структуру вершин.
\param flag - Если значение переменной - true, будет выполнена центровка, в
противном случе будет производиться нормализация размера.

*/
  void centerOrNormalize(Vertex *inp, bool flag = true) {
    if (flag) {
      model.affine.center(inp);
    } else {
      model.affine.normalize_size(inp);
    }
  }
  /*!
\brief Метод для масштабирования модели
\param inp - Указатель на структуру вершин.
\param value - Значение, кратно которому происходит масштабирование.

Данный метод производит масштабирования модели.

*/
  void scale(Vertex *inp, double value) { model.affine.scale(inp, value); }

  /*!
\brief Метод для очистки памяти, выделенной подструктуры данных
\param vertex - Указатель на структуру вершин.
\param polygons - Указатель на структуру полигонов.

Данный метод производит очистку памяти, выделенной под структуры данных.

*/

  void kill_structs(Vertex vertex, Polygons *polygons, int polygons_size) {
    parser.kill_structs(vertex, polygons, polygons_size);
  }

 private:
  Model model;
  Parser parser;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_H
