#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "Module.h"
#include "PugiXml\src\pugixml.hpp"

struct SDL_RWops;
int close_sdl_rwops(SDL_RWops *rw);

class FileSystem : public Module
{
public:

	FileSystem();
	~FileSystem();

	bool awake(pugi::xml_node &node);
	bool cleanUp();

	bool addSearchPath(const char *path_or_zip, const char *mount_point = NULL);
	bool removeAllSearchPaths();
	bool removePath(const char *path_or_zip);
	uint load(const char* file, char **buffer) const;
	SDL_RWops *load(const char* file) const;
	uint save(const char *file, const char *buffer, uint size) const;

	const char *getSaveDirectory() const;
	bool isDirectory(const char *dir) const;
	bool exists(const char *file) const;
};


#endif //!__FILESYSTEM_H__