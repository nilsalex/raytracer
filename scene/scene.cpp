#include "scene/scene.hpp"

Scene::Scene(char* filename) {
  if (filename == NULL) {
    fprintf (stderr, "No Scene File - Nothing to read - Quitting\n");
    error_number_ = 101;
  } else {
    file_ = fopen (filename, "r");
    if (file_ == NULL) {
      fprintf (stderr, "Can't open the file %s\n", filename);
      error_number_ = 101;
    } else {
      Scene::filename_ = filename;
      error_number_ = 0;
      version_ = 0;
      width_ = 0;
      height_ = 0;
      bgcolour_ = RGBColour(0.0, 0.0, 0.0);
      view_type_ = 0;
      zoom_ = 1.0;
      number_of_materials_ = 0;
      number_of_spheres_ = 0;
      number_of_planes_ = 0;
      number_of_lights_ = 0;
      parse_ = new Parse();
      parse_->Digit.n = 0;
      parse_->Digit.v[0] = parse_->Digit.v[1] = parse_->Digit.v[2] = 0;
      shape_read_ = sphere_read_ = plane_read_ = light_read_ = material_read_ = 0; // = path_read_
    }
  }
}

Scene::~Scene(void) {
  if (objects) {
    delete objects;
  }
  if (parse_) {
    delete parse_;
  }
  parse_ = 0;
}

int Scene::Read(void) {
  count_ = 0;
  if (error_number_ > 0) {
    return count_;
  }

  int size;
  char *buffer, temp_buf[1024];

  fseek (file_, 0L, SEEK_END);
  size = ftell (file_);
  rewind (file_);
  buffer = (char *)calloc (size + 1, sizeof(char));
  fread (buffer, 1, size, file_);
  size = strlen(buffer);
  fclose(file_);

  // Read complete file into buffer
  while (count_ <= size) {
    switch (*buffer) {
      case '!':
        count_++;
        buffer++;
        buffer = parse_->ReadComment (count_, buffer);
        break;
      case 'S':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        if (!strcmp(temp_buf, "Scene") && !scene_read_) {
          buffer = ReadScene_(buffer);
          scene_read_ = 1;
          sphere_ = new Sphere[number_of_spheres_];
          plane_ = new Plane[number_of_planes_];
          objects = new int*[get_number_of_shapes()];
          material_ = new Material[number_of_materials_];
//        path_ = new Path[number_of_paths_];
          light_ = new Light[number_of_lights_];
        } else if (scene_read_ && material_read_ == number_of_materials_ && !strcmp(temp_buf, "Sphere") && sphere_read_ < number_of_spheres_) {
          buffer = ReadSphere_(buffer);
          sphere_read_++;
          shape_read_++;
        }
        break;
      case 'P':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        if (scene_read_ && material_read_ == number_of_materials_) {
          // Path...
          if (!strcmp(temp_buf, "Plane") && plane_read_ < number_of_planes_) {
            buffer = ReadPlane_(buffer);
            plane_read_++;
            shape_read_++;
          }
        }
        break;
      case 'L':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        if (scene_read_ && !strcmp(temp_buf, "Light") && light_read_ < number_of_lights_) {
          buffer = ReadLight_(buffer);
          light_read_++;
        }
        break;
      case 'M':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        if (scene_read_ && !strcmp(temp_buf, "Material") && material_read_ < number_of_materials_) {
          buffer = ReadMaterial_(buffer);
          material_read_++;
          if (material_read_ == number_of_materials_) {
            material_ -= number_of_materials_;
          }
        }
        break;
      default:
        count_++;
        buffer++;
        break;
    }
    if (error_number_ > 0) {
      break;
    }
  }

  if (sphere_read_ == number_of_spheres_) {
    sphere_ -= number_of_spheres_;
  } else {
    error_number_ = 102;
  }

  if (plane_read_ == number_of_planes_) {
    plane_ -= number_of_planes_;
  } else {
    error_number_ = 102;
  }

  if (light_read_ == number_of_lights_) {
    light_ -= number_of_lights_;
  } else {
    error_number_ = 102;
  }

  if (error_number_ > 0) {
    fprintf(stdout, "SPHERES      %d, PLANES      %d, LIGHTS      %d, MATERIALS      %d\n", number_of_spheres_, number_of_planes_, number_of_lights_, number_of_materials_);
    fprintf(stdout, "SPHERES_READ %d, PLANES_READ %d, LIGHTS_READ %d, MATERIALS_READ %d", sphere_read_, plane_read_, light_read_, material_read_);
    return -1;
  }

  return count_;
}

char* Scene::ReadScene_(char *buffer) {
  char temp_buf[1024];
  char start = 0, done = 0;
  while (1) {
    switch (*buffer) {
      case '!':
        count_++;
        buffer++;
        buffer = parse_->ReadComment(count_, buffer);
        break;
      case '}':
        count_++;
        buffer++;
        if (start != 1) {
          fprintf(stdout, "\nSyntax Error: Missing '{' in Component 'Scene' in file %s\n", filename_);
          error_number_ = 101;
        }
        done = 1;
        break;
      case '{':
        count_++;
        buffer++;
        start = 1;
        break;
      case 'V':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Version")) {
          version_ = parse_->Digit.v[0];
        } else if (!strcmp(temp_buf, "ViewType")) {
          view_type_ = parse_->Digit.v[0];
          if (view_type_ < 0 || view_type_ > VIEWING_TYPES_SUPPORTED) {
            view_type_ = 0;
          }
        }
        break;
      case 'W':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Width")) {
          width_ = parse_->Digit.v[0];
        }
        break;
      case 'H':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Height")) {
          height_ = parse_->Digit.v[0];
        }
        break;
      case 'B':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "BGColour")) {
          bgcolour_ = RGBColour(parse_->Digit.v[0], parse_->Digit.v[1], parse_->Digit.v[2]);
        }
        break;
      case 'Z':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Zoom")) {
          zoom_ = parse_->Digit.v[0];
          if (zoom_ < 0.0) {
            fprintf(stdout, "\nZoom Error: The zoom number should not be less than '0' in Component 'Scene' in file %s\n", filename_);
            error_number_ = 101;
          }
        }
        break;
      case 'G':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Gamma")) {
          gamma_ = parse_->Digit.v[0];
          if (gamma_ < 0.0) {
            fprintf(stdout, "\nGamma Error: The gamma number should not be less than '0' in Component 'Scene' in file %s\n", filename_);
            error_number_ = 101;
          }
        }
        break;
      case 'N':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "NumberOfMaterials")) {
          number_of_materials_ = parse_->Digit.v[0];
        } else if (!strcmp(temp_buf, "NumberOfSpheres")) {
          number_of_spheres_ = parse_->Digit.v[0];
        } else if (!strcmp(temp_buf, "NumberOfPlanes")) {
          number_of_planes_ = parse_->Digit.v[0];
        } else if (!strcmp(temp_buf, "NumberOfLights")) {
          number_of_lights_ = parse_->Digit.v[0];
        } // Paths!
        break;
      default:
        count_++;
        buffer++;
        break;
    }
    if (done == 1 || error_number_ > 0) {
      break;
    }
  }

  return buffer;
}

char* Scene::ReadSphere_(char *buffer) {
  char temp_buf[1024];
  char start = 0, done = 0;
  while (1) {
    switch (*buffer) {
      case '!':
        buffer = parse_->ReadComment(count_, buffer);
        break;
      case '}':
        count_++;
        buffer++;
        if (start != 1) {
          fprintf(stdout, "\nScene::ReadSphere_: Syntax Error: Missing '{' in Component 'Sphere' in file %s\n", filename_);
          error_number_ = 101;
        }
        done = 1;
        objects[shape_read_] = (int *)sphere_;
        sphere_++;
        break;
      case '{':
        count_++;
        buffer++;
        start = 1;
        break;
      case 'C':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Center")) {
          sphere_->set_center(Vector(parse_->Digit.v[0], parse_->Digit.v[1], parse_->Digit.v[2]));
        }
        break;
      case 'R':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Radius")) {
          sphere_->set_radius(parse_->Digit.v[0]);
        }
        break;
      case 'M':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Material.Id")) {
          int value = int(parse_->Digit.v[0]);
          material_ += value;
          if (value >= number_of_materials_) {
            fprintf(stdout, "\nScene::ReadSphere_: Error: Wrong material ID in Component 'Sphere' in file %s\n", filename_);
            error_number_ = 101;
          } else {
            sphere_->set_material(material_);
          }
          material_ -= value;
        }
        break;
// Path!
      case 'S':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "StartAngle")) {
          sphere_->set_start_angle(parse_->Digit.v[0]);
        }
        break;
      default:
        count_++;
        buffer++;
        break;
    }
    if (done == 1 || error_number_ > 0) {
      break;
    }
  }

  return buffer;
}

char* Scene::ReadPlane_(char* buffer) {
  char temp_buf[1024];
  char start = 0, done = 0;
  while (1) {
    switch (*buffer) {
      case '!':
        buffer = parse_->ReadComment (count_, buffer);
        break;
      case '}':
        count_++;
        buffer++;
        if (start != 1) {
          fprintf(stdout, "\nScene::ReadPlane_: Syntax Error: Missing '{' in Component 'Plane' in file %s\n", filename_);
          error_number_ = 101;
        }
        done = 1;
        objects[shape_read_] = (int *)plane_;
        plane_++;
        break;
      case '{':
        count_++;
        buffer++;
        start = 1;
        break;
      case 'P':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Point")) {
          plane_->set_point(Vector(parse_->Digit.v[0], parse_->Digit.v[1], parse_->Digit.v[2]));
        }
        break; // Path!
      case 'N':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "NormalVector")) {
          plane_->set_normal_vector(Vector(parse_->Digit.v[0], parse_->Digit.v[1], parse_->Digit.v[2]));
        }
        break; // Path!
      case 'M':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Material.Id")) {
          int value = int(parse_->Digit.v[0]);
          material_ += value;
          if (value >= number_of_materials_) {
            fprintf(stdout, "\nScene::ReadPlane_: Error: Wrong material ID in Component 'Plane' in file %s\n", filename_);
            error_number_ = 101;
          } else {
            plane_->set_material(material_);
          }
          material_ -= value;
        }
        break;
      default:
        count_++;
        buffer++;
        break;
    }
    if (done == 1 || error_number_ > 0) {
      break;
    }
  }

  return buffer;
}

char* Scene::ReadLight_(char* buffer) {
  char temp_buf[1024];
  char start = 0, done = 0;
  while (1) {
    switch (*buffer) {
      case '!':
        buffer = parse_->ReadComment (count_, buffer);
        break;
      case '}':
        count_++;
        buffer++;
        if (start != 1) {
          fprintf(stdout, "\nScene::ReadLight_: Syntax Error: Missing '{' in Component 'Light' in file %s\n", filename_);
          error_number_ = 101;
        }
        done = 1;
        light_++;
        break;
      case '{':
        count_++;
        buffer++;
        start = 1;
        break;
      case 'P':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Position")) {
          light_->set_position(Vector(parse_->Digit.v[0], parse_->Digit.v[1], parse_->Digit.v[2]));
        }
        break; // Path!
      case 'C':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Colour")) {
          light_->set_colour(RGBColour(parse_->Digit.v[0], parse_->Digit.v[1], parse_->Digit.v[2]));
        }
        break;
      default:
        count_++;
        buffer++;
        break;
    }
    if (done == 1 || error_number_ > 0) {
      break;
    }
  }

  return buffer;
}

char* Scene::ReadMaterial_(char* buffer) {
  char temp_buf[1024];
  char start = 0, done = 0;
  while (1) {
    switch (*buffer) {
      case '!':
        buffer = parse_->ReadComment (count_, buffer);
        break;
      case '}':
        count_++;
        buffer++;
        if (start != 1) {
          fprintf(stdout, "\nScene::ReadMaterial_: Syntax Error: Missing '{' in Component 'Material' in file %s\n", filename_);
          error_number_ = 101;
        }
        done = 1;
        material_++;
        break;
      case '{':
        count_++;
        buffer++;
        start = 1;
        break;
      case 'R':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Reflection")) {
          material_->set_reflection(parse_->Digit.v[0]);
        } else if (!strcmp(temp_buf, "RefractionIn")) {
          material_->set_refraction_in(parse_->Digit.v[0]);
        } else if (!strcmp(temp_buf, "RefractionOut")) {
          material_->set_refraction_out(parse_->Digit.v[0]);
        }
        break;
      case 'T':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Transparency")) {
          material_->set_transparency(parse_->Digit.v[0]);
        }
        break;
      case 'C':
        sscanf(buffer, "%s", temp_buf);
        count_ += strlen(temp_buf);
        buffer += strlen(temp_buf);
        buffer = parse_->ReadDigits(count_, buffer, error_number_, filename_);
        if (!strcmp(temp_buf, "Colour")) {
          material_->set_colour(RGBColour(parse_->Digit.v[0], parse_->Digit.v[1], parse_->Digit.v[2]));
        }
        break;
      default:
        count_++;
        buffer++;
        break;
    }
    if (done == 1 || error_number_ > 0) {
      break;
    }
  }

  return buffer;
}


// Path!

int Scene::get_version(void) const {
  return version_;
}

int Scene::get_width(void) const {
  return width_;
}

int Scene::get_height(void) const {
  return height_;
}

int Scene::get_view_type(void) const {
  return view_type_;
}

double Scene::get_zoom(void) const {
  return zoom_;
}

double Scene::get_gamma(void) const {
  return gamma_;
}

RGBColour Scene::get_bgcolour(void) const {
  return bgcolour_;
}

int Scene::get_number_of_shapes(void) const {
  return (number_of_spheres_ + number_of_planes_);
}

int Scene::get_number_of_spheres(void) const {
  return number_of_spheres_;
}

// Paths!

int Scene::get_number_of_planes(void) const {
  return number_of_planes_;
}

int Scene::get_number_of_lights(void) const {
  return number_of_lights_;
}

Sphere* Scene::get_spheres(void) {
  return sphere_;
}

// Paths!

Plane* Scene::get_planes(void) {
  return plane_;
}

Light* Scene::get_lights(void) {
  return light_;
}

void Scene::set_zoom(double const& zoom) {
  zoom_ = zoom;
}

void Scene::Print(void) const {
  fprintf (stdout, "\nVersion            = %5d\n", version_);
  fprintf (stdout, "Width              = %5d\n", width_);
  fprintf (stdout, "Height             = %5d\n", height_);
  fprintf (stdout, "ViewType           = %5d\n", view_type_);
  fprintf (stdout, "Zoom               = %7.2f\n", zoom_);
  fprintf (stdout, "Gamma              = %7.2f\n", gamma_);
  fprintf (stdout, "BGColor            = %7.2f\n", bgcolour_.get_red());
  fprintf (stdout, "                   = %7.2f\n", bgcolour_.get_green());
  fprintf (stdout, "                   = %7.2f\n", bgcolour_.get_blue());
  fprintf (stdout, "NumberOfMaterials  = %5d\n", number_of_materials_);
//  fprintf (stdout, "NumberOfPaths      = %5d\n", number_of_paths_);
  fprintf (stdout, "NumberOfSpheres    = %5d\n", number_of_spheres_);
  fprintf (stdout, "NumberOfPlanes     = %5d\n", number_of_planes_);
  fprintf (stdout, "NumberOfLights     = %5d\n", number_of_lights_);
}

