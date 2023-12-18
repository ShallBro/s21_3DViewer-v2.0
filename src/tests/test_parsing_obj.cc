#include "test_main.h"

TEST(parser, test1) {
  s21::Vertex vertex;
  s21::Polygons *polygons = nullptr;
  s21::Controller controller;
  int polygons_size = 0;
  const char *file = "../data-samples/skul.obj";
  ASSERT_EQ(controller.ParseObject(file, &vertex, &polygons, &polygons_size),
            0);
  controller.kill_structs(vertex, polygons, polygons_size);
}

TEST(parser, test2) {
  s21::Vertex vertex;
  s21::Polygons *polygons = nullptr;
  s21::Controller controller;
  int polygons_size = 0;
  const char *file = "../data-samples/skul.obj";
  controller.ParseObject(file, &vertex, &polygons, &polygons_size);
  ASSERT_EQ(vertex.amount_vert, 120186);
  ASSERT_EQ(polygons_size, 40728);
  controller.kill_structs(vertex, polygons, polygons_size);
}

TEST(parser, test3) {
  s21::Vertex vertex;
  s21::Polygons *polygons = nullptr;
  s21::Controller controller;
  int polygons_size = 0;
  const char *file = "../data-samples/wead.wtga";
  ASSERT_EQ(controller.ParseObject(file, &vertex, &polygons, &polygons_size),
            1);
}