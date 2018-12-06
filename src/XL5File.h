#pragma once

#include <iostream>
#include <limits>
#include <cstddef>
#include <cstring>
#include <dirent.h>
#include "XL5Stack.h"
using namespace std;

class XL5File {
  public:
    XL5Stack<string>* list_dir(const string& patterns_path) {
      XL5Stack<string>* files = new XL5Stack<string>();
      files->create(10000, 100);
      struct dirent* dir_ent;
      DIR* dir = opendir(patterns_path.c_str());
      while ((dir_ent = readdir(dir)) != NULL) {
        cout << dir_ent->d_name << endl;
        string file = string(dir_ent->d_name);
        // string file = string("test");
        if(file != "." && file != "..")
          files->push(file);
      }
      (void)closedir(dir);

      files->log("Files:", XL5Color::FG_GREEN);

      return files;
    }
};
