#include "test_main.h"

TEST(affine, test1) {
  s21::Vertex vertex;
  s21::Polygons *polygons = nullptr;
  s21::Vertex vertex1;
  s21::Polygons *polygons1 = nullptr;
  s21::Controller controller;
  int polygons_size = 0;
  const char *file = "../data-samples/skul.obj";

  controller.ParseObject(file, &vertex, &polygons, &polygons_size);
  controller.ParseObject(file, &vertex1, &polygons1, &polygons_size);
  controller.center(&vertex);
  controller.normalize_size(&vertex);
  controller.rotateOX(&vertex, 1);
  controller.rotateOY(&vertex, 1);
  controller.rotateOZ(&vertex, 1);
  controller.moveOX(&vertex, 1);
  controller.moveOY(&vertex, 1);
  controller.moveOZ(&vertex, 1);
  ASSERT_FALSE(polygons == polygons1);
  controller.kill_structs(vertex, polygons, polygons_size);
  controller.kill_structs(vertex1, polygons1, polygons_size);
}