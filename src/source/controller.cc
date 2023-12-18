#include "controller.h"

namespace s21 {
int Controller::ParseObject(const char *filename, s21::Vertex *vertex,
                            s21::Polygons **polygons, int *polygons_size) {
  return model.ParseObject(filename, vertex, polygons, polygons_size);
}
// -----
// -----
void Controller::moveOX(Vertex *inp, double value) {
  model.moveOXYZ(inp, value, 'X');
}
void Controller::moveOY(Vertex *inp, double value) {
  model.moveOXYZ(inp, value, 'Y');
}
void Controller::moveOZ(Vertex *inp, double value) {
  model.moveOXYZ(inp, value, 'Z');
}
// -----
void Controller::normalize_size(Vertex *inp) {
  model.centerOrNormalize(inp, false);
}

void Controller::center(Vertex *inp) { model.centerOrNormalize(inp); }

void Controller::scale(Vertex *inp, double value) { model.scale(inp, value); }
// -----
void Controller::rotateOX(Vertex *inp, double angle) {
  model.rotateOXYZ(inp, angle, 'X');
}
void Controller::rotateOY(Vertex *inp, double angle) {
  model.rotateOXYZ(inp, angle, 'Y');
}
void Controller::rotateOZ(Vertex *inp, double angle) {
  model.rotateOXYZ(inp, angle, 'Z');
}

void Controller::kill_structs(Vertex vertex, Polygons *polygons,
                              int polygons_size) {
  model.kill_structs(vertex, polygons, polygons_size);
}

}  // namespace s21
