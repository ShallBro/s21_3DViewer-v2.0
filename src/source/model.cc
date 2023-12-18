#include "model.h"

namespace s21 {
int Parser::MainParser(const char *filename, Vertex *vertex,
                       Polygons **polygons, int *polygons_size) {
  setlocale(LC_ALL, "en_US.UTF-8");
  int error = 0;
  Vertex vertex_local;
  vertex_local.amount_vert = 0;
  int amount_rows = 0;
  int allocated_rows = 0;
  Polygons *polygons_local = nullptr;
  int polygons_count = 0;
  vertex_local.coord = nullptr;
  FILE *file = std::fopen(filename, "r");
  if (file == nullptr) {
    error = 1;
  } else {
    char line[1024] = {'\0'};
    while (std::fgets(line, 1024, file) != nullptr && !error) {
      if (line[0] == '#') {
        continue;
      } else if (line[0] == 'v' && line[1] == ' ') {
        error = parse_v(line, &vertex_local, &amount_rows);
      } else if (line[0] == 'f') {
        error = parse_f(&polygons_local, line, &polygons_count, vertex_local,
                        &allocated_rows);
      }
    }
    std::fclose(file);
  }
  *vertex = vertex_local;
  *polygons = polygons_local;
  *polygons_size = polygons_count;
  if (vertex_local.amount_vert == 0) error = 1;
  return error;
}

int Parser::parse_v(char *line, Vertex *vertex, int *line_counter) {
  int error = 0;
  line += std::strcspn(line, "-0123456789");
  int vertices_count = 0;
  int local_i = 0;
  while (line != nullptr && *line != '\0') {
    local_i++;
    vertex->amount_vert++;
    vertices_count++;
    int shift = std::strspn(line, "-0123456789.eE");
    char str_val[shift + 1];
    str_val[shift] = '\0';
    strncpy(str_val, line, shift);
    double num_val = atof(str_val);
    line += shift;
    line = strchr(line, ' ');
    if (line != nullptr) line += std::strcspn(line, "-0123456789");
    if (vertex->amount_vert > *line_counter) {
      *line_counter += 1000;
      vertex->coord =
          (double *)realloc(vertex->coord, *line_counter * sizeof(double));
    }
    vertex->coord[vertex->amount_vert - 1] = num_val;
    SetExtrema(vertex, local_i, num_val);
  }
  if (vertices_count != 3) error = 1;
  return error;
}

void Parser::SetExtrema(Vertex *vertex, int local_i, double num_val) {
  if (vertex->amount_vert <= 3) {
    if (local_i % 3 == 1) {
      vertex->minMaxX[0] = num_val;
      vertex->minMaxX[1] = num_val;
    }
    if (local_i % 3 == 2) {
      vertex->minMaxY[0] = num_val;
      vertex->minMaxY[1] = num_val;
    }
    if (local_i % 3 == 0) {
      vertex->minMaxZ[0] = num_val;
      vertex->minMaxZ[1] = num_val;
    }
  } else {
    if (local_i % 3 == 1) {
      if (num_val < vertex->minMaxX[0]) vertex->minMaxX[0] = num_val;
      if (num_val > vertex->minMaxX[1]) vertex->minMaxX[1] = num_val;
    }
    if (local_i % 3 == 2) {
      if (num_val < vertex->minMaxY[0]) vertex->minMaxY[0] = num_val;
      if (num_val > vertex->minMaxY[1]) vertex->minMaxY[1] = num_val;
    }
    if (local_i % 3 == 0) {
      if (num_val < vertex->minMaxZ[0]) vertex->minMaxZ[0] = num_val;
      if (num_val > vertex->minMaxZ[1]) vertex->minMaxZ[1] = num_val;
    }
  }
}

int Parser::parse_f(struct Polygons **polygons_arr, char *line,
                    int *polygons_count, Vertex vertex, int *allocated_rows) {
  (*polygons_count)++;
  line += strcspn(line, "-0123456789");
  int size = 0;
  int *p = nullptr;
  int error = 0;

  while (line != nullptr && *line != '\0') {
    int shift = std::strspn(line, "-0123456789");
    char str_val[shift + 1];
    strncpy(str_val, line, shift);
    str_val[shift] = '\0';
    int num_val = std::atoi(str_val);
    int *tmp = (int *)realloc(p, (size + 1) * sizeof(int));
    if (tmp)
      p = tmp;
    else {
      error = 1;
      free(p);
      break;
    }
    if (num_val < 0) {
      p[size++] = vertex.amount_vert / 3 + 1 + num_val;
    } else
      p[size++] = num_val - 1;
    line += shift;
    line = strchr(line, ' ');
    if (line != nullptr) line += strcspn(line, "-0123456789");
  }
  if (!error) {
    size *= 2;
    int *p2 = nullptr;
    p2 = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
      if (i == 0 || i == size - 1)
        p2[i] = p[0];
      else {
        p2[i] = p[(i + 1) / 2];
      }
    }
    if (*polygons_count > *allocated_rows) {
      *allocated_rows += 1000;
      *polygons_arr = (struct Polygons *)realloc(
          (*polygons_arr), *allocated_rows * sizeof(struct Polygons));
    }
    (*polygons_arr)[*polygons_count - 1].amount_p = size;
    (*polygons_arr)[*polygons_count - 1].p = p2;
    free(p);
  }
  return error;
}

void Parser::kill_structs(Vertex vertex, Polygons *polygons,
                          int polygons_size) {
  free(vertex.coord);
  vertex.coord = NULL;
  for (int i = 0; i < polygons_size; i++) {
    free(polygons[i].p);
  }
  free(polygons);
}

void Affine::center(Vertex *inp) {
  double xShift = (inp->minMaxX[0] + inp->minMaxX[1]) / 2;
  double yShift = (inp->minMaxY[0] + inp->minMaxY[1]) / 2;
  double zShift = (inp->minMaxZ[0] + inp->minMaxZ[1]) / 2;
  moveOX(inp, -xShift);
  moveOY(inp, -yShift);
  moveOZ(inp, -zShift);
}

void Affine::moveOX(Vertex *inp, double value) {
  for (int i = 0; i < inp->amount_vert; i++) {
    if (i % 3 == 0) inp->coord[i] += value;
  }
}

void Affine::moveOY(Vertex *inp, double value) {
  for (int i = 0; i < inp->amount_vert; i++) {
    if (i % 3 == 1) inp->coord[i] += value;
  }
}

void Affine::moveOZ(Vertex *inp, double value) {
  for (int i = 0; i < inp->amount_vert; i++) {
    if (i % 3 == 2) inp->coord[i] += value;
  }
}

void Affine::normalize_size(Vertex *inp) {
  double scope = 1;
  scope = fabs(inp->minMaxX[0]);
  if (fabs(inp->minMaxX[1]) > scope) scope = inp->minMaxX[1];
  if (fabs(inp->minMaxY[0]) > scope) scope = inp->minMaxY[0];
  if (fabs(inp->minMaxY[1]) > scope) scope = inp->minMaxY[1];
  if (fabs(inp->minMaxZ[0]) > scope) scope = inp->minMaxZ[0];
  if (fabs(inp->minMaxZ[1]) > scope) scope = inp->minMaxZ[1];
  scale(inp, 2.5 / scope);
}

void Affine::scale(Vertex *inp, double value) {
  if (value == 0) value = 1;
  for (int i = 0; i < inp->amount_vert; i++) {
    inp->coord[i] *= value;
  }
  inp->minMaxX[0] *= value;
  inp->minMaxX[1] *= value;
  inp->minMaxY[0] *= value;
  inp->minMaxY[1] *= value;
  inp->minMaxZ[0] *= value;
  inp->minMaxZ[1] *= value;
}

void Affine::rotateOX(Vertex *inp, double angle) {
  for (int i = 0; i < inp->amount_vert - 2; i += 3) {
    double temp_y = inp->coord[i + 1];
    double temp_z = inp->coord[i + 2];
    inp->coord[i + 1] = (cos(angle) * temp_y - sin(angle) * temp_z);
    inp->coord[i + 2] = (sin(angle) * temp_y + cos(angle) * temp_z);
  }
}

void Affine::rotateOY(Vertex *inp, double angle) {
  for (int i = 1; i < inp->amount_vert - 1; i += 3) {
    double temp_x = inp->coord[i - 1];
    double temp_z = inp->coord[i + 1];
    inp->coord[i - 1] = (cos(angle) * temp_x - sin(angle) * temp_z);
    inp->coord[i + 1] = (sin(angle) * temp_x + cos(angle) * temp_z);
  }
}

void Affine::rotateOZ(Vertex *inp, double angle) {
  for (int i = 2; i < inp->amount_vert; i += 3) {
    double temp_x = inp->coord[i - 2];
    double temp_y = inp->coord[i - 1];
    inp->coord[i - 2] = (cos(angle) * temp_x - sin(angle) * temp_y);
    inp->coord[i - 1] = (sin(angle) * temp_x + cos(angle) * temp_y);
  }
}

int Model::ParseObject(const char *filename, s21::Vertex *vertex,
                       s21::Polygons **polygons, int *polygons_size) {
  return Parser::getParser().MainParser(filename, vertex, polygons,
                                        polygons_size);
}

MoveStrategy::MoveStrategy(Model &model) : model(model) {}

void MoveStrategy::Transform(Vertex *inp, double value, char XYZ) {
  switch (XYZ) {
    case 'X':
      model.affine.moveOX(inp, value);
      break;
    case 'Y':
      model.affine.moveOY(inp, value);
      break;
    case 'Z':
      model.affine.moveOZ(inp, value);
      break;
  }
}

RotateStrategy::RotateStrategy(Model &model) : model(model) {}

void RotateStrategy::Transform(Vertex *inp, double value, char XYZ) {
  switch (XYZ) {
    case 'X':
      model.affine.rotateOX(inp, value);
      break;
    case 'Y':
      model.affine.rotateOY(inp, value);
      break;
    case 'Z':
      model.affine.rotateOZ(inp, value);
      break;
  }
}
}  // namespace s21
