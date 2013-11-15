/*
 * Paint.h
 *
 * (c) 2013 Sofian Audry -- info(@)sofianaudry(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PAINT_H_
#define PAINT_H_

#include <wx/wx.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

class Paint
{
protected:
  Paint() {}
public:
  virtual ~Paint() {}
  virtual void build() {}
};

class Texture : public Paint
{
protected:
  GLuint textureId;
  Texture(GLuint textureId_=0) : textureId(textureId_) {}
  virtual ~Texture() {}

public:
  GLuint getTextureId() const { return textureId; }
  virtual void loadTexture() = 0;
  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
};

class Image : public Texture
{
protected:
  std::string imagePath;
  int width;
  int height;

public:
  Image(const std::string imagePath_) : Texture(), imagePath(imagePath_), width(-1), height(-1) {}
  virtual ~Image() {}

  virtual void loadTexture() {
    unsigned char * data = SOIL_load_image(imagePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB );
    wxASSERT(data);
    textureId = SOIL_create_OGL_texture ( data, width, height, 3, textureId, 0);
    // TODO: free data?
  }

  virtual void build() {
  }

  virtual int getWidth() const { return width; }
  virtual int getHeight() const { return height; }
};

#endif /* PAINT_H_ */