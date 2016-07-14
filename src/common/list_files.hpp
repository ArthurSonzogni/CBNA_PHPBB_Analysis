#include <dirent.h>
#include <vector>
#include <string>

static std::vector<std::string> list_files(const std::string& directory)
{
  std::vector<std::string> result;
  DIR *dir;
  struct dirent *ent;
  dir = opendir(directory.c_str());
  if ( dir != NULL)
  {
      while ((ent = readdir (dir)) != NULL) 
      {
          result.push_back(ent->d_name);
      }
      closedir (dir);
  }
  return result;
}
