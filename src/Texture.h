#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glad/glad.h>

class Texture2D {
 public:
  // texture object
  unsigned int id;
  // texture demension
  int width, height;
  // texture format
  unsigned int internal_format;
  unsigned int image_format;
  // texture configuration
  unsigned int wrap_s;      // warpping mode on S axis
  unsigned int wrap_t;      // srapping mode on T axis
  unsigned int filter_min;  // filtering mode when texture pixels < screen pixels
  unsigned int filter_max;  // filtering mode when texture pixels . screen pixels

  // constructor
  Texture2D();
  // generates texture
  void Generate(unsigned int _width, unsigned _height, unsigned char* data);
  // bind texture object
  void Bind() const;
};

#endif