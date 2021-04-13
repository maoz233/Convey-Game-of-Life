#include "GameLevel.h"

#include <fstream>
#include <sstream>

#include <iostream>

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight) {
  // clear old data
  this->cells.clear();
  // load from file
  GLuint cellCode;
  std::string line;
  std::ifstream fstream(file);
  if (fstream) {
    while (std::getline(fstream, line)) {
      std::istringstream sstream(line);
      std::vector<GLuint> row;
      while (sstream >> cellCode) {
        row.push_back(cellCode);
      }
      this->cellData.push_back(row);
    }
    if (this->cellData.size() > 0) {
      this->Init(levelWidth, levelHeight);
    }
  }
}

void GameLevel::Draw(SpriteRenderer &renderer) {
  for (GameObject &cell : this->cells) {
    cell.Draw(renderer);
  }
}

void GameLevel::Conway() {
  std::vector<unsigned int> data(this->cellData.size(), 0);
  std::vector<std::vector<unsigned int>> prevData(this->cellData[0].size(), data);

  for (int i = 0; i < this->cellData.size(); ++i) {
    for (int j = 0; j < this->cellData[0].size(); ++j) {
      prevData[i][j] = (this->cellData)[i][j];
    }
  }

  for (GLuint x = 1; x < prevData.size() - 1; ++x) {
    for (GLuint y = 1; y < prevData[0].size() - 1; ++y) {
      unsigned int neighbor = 0;
      for (int row = -1; row < 2; ++row) {
        for (int col = -1; col < 2; ++col) {
          if (!(row == 0 && col == 0)) {
            if (prevData[x + row][y + col]) {
              ++neighbor;
            }
          }
        }
      }

      if (neighbor < 2) {
        this->cellData[x][y] = 0;
      } else if (neighbor == 3) {
        this->cellData[x][y] = 1;
      } else if (neighbor > 3) {
        this->cellData[x][y] = 0;
      }
    }
  }
}

void GameLevel::Init(unsigned int levelWidth, unsigned int levelHeight) {
  // clear old data
  this->cells.clear();
  // calculate dimensions
  GLuint height = this->cellData.size();
  GLuint width = this->cellData[0].size();
  GLfloat unit_width = levelWidth / static_cast<float>(width);
  GLfloat unit_height = levelHeight / static_cast<float>(height);
  // initialize cells
  for (GLuint y = 0; y < height; ++y) {
    for (GLuint x = 0; x < width; ++x) {
      if (1 == cellData[y][x]) {
        glm::vec2 pos(unit_width * x, unit_height * y);
        glm::vec2 size(unit_width, unit_height);
        GameObject obj(pos, size, ResourceManager::GetTexture2D("cell"), glm::vec3(1.0f, 1.0f, 1.0f));
        this->cells.push_back(obj);
      }
    }
  }
}