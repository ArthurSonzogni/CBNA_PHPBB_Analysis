#include <dirent.h>
#include <string>
#include <vector>

static std::vector<std::string> list_files(const std::string &directory) {
  std::vector<std::string> result;
  DIR *dir;
  struct dirent *ent;
  dir = opendir(directory.c_str());
  if (dir != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      std::string file = ent->d_name;
      if (file != "." && file != "..")
        result.push_back(ent->d_name);
    }
    closedir(dir);
  }
  return result;
}
