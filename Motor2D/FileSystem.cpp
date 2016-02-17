#include "FileSystem.h"
#include "p2Log.h"
#include "SDL\include\SDL.h"
#include "PhysFS\include\physfs.h"

FileSystem::FileSystem()
{
	name.create("file_system");

	// PHYSFS must be initialized before other modules awake,
	// because it will be used by them.
	if (PHYSFS_isInit() == 0)
	{
		char *base_path = SDL_GetBasePath();
		PHYSFS_init(base_path);
		SDL_free(base_path);

		addSearchPath(".");
	}	
}

FileSystem::~FileSystem()
{
	if (PHYSFS_isInit() != 0)
		PHYSFS_deinit();
}

bool FileSystem::awake(pugi::xml_node &node)
{
	bool ret = true;

	for (pugi::xml_node path = node.child("path"); path ; path = path.next_sibling("path"))
		addSearchPath(path.child_value());

	char *write_dir = SDL_GetPrefPath("Carlos", "Game_development");

	if (PHYSFS_setWriteDir(write_dir) == 0)
	{
		LOG("%s,%s","Error on setting Write Dir. Error:", PHYSFS_getLastError());
		ret = false;
	}
	else
	{
		LOG("%s %s", "Write directory is ", write_dir);
		addSearchPath(write_dir, getSaveDirectory());
	}

	SDL_free(write_dir);
	
	return ret;
}

bool FileSystem::cleanUp()
{
	removeAllSearchPaths();
	return true;
}

bool FileSystem::addSearchPath(const char *path_or_zip, const char *mount_point)
{
	bool ret = true;

	if (PHYSFS_mount(path_or_zip, mount_point, 1) == 0)
	{
		LOG("%s %s", "Failure on mounting or adding path", path_or_zip);
		LOG("%s", "Error:", PHYSFS_getLastError());
		ret = false;
	}

	return ret;
}

bool FileSystem::removeAllSearchPaths()
{
	bool ret = false;

	char **paths;
	for (paths = PHYSFS_getSearchPath(); *paths != NULL; paths++)
	{
		PHYSFS_removeFromSearchPath(*paths);
	}

	if (*(paths = PHYSFS_getSearchPath()) == NULL)
		ret = true;

	PHYSFS_freeList(paths);

	return ret;
}

bool FileSystem::removePath(const char *path_or_zip)
{
	bool ret = true;
		
	if (PHYSFS_removeFromSearchPath(path_or_zip) == 0)
	{
		LOG("%s %s", "Failure on removing directory or file on search path", path_or_zip);
		LOG("%s", "Error:", PHYSFS_getLastError());
		ret = false;
	}

	return ret;
}

uint FileSystem::load(const char* file, char **buffer) const
{
	uint ret = 0;

	PHYSFS_file *file_handle = PHYSFS_openRead(file);
	if (file_handle != NULL)
	{
		PHYSFS_sint64 size = PHYSFS_fileLength(file_handle);
		if (size > 0)
		{
			*buffer = new char[(uint)size];
			PHYSFS_sint64 bytes_readed = PHYSFS_read(file_handle, *buffer, 1, size);
			if (bytes_readed != size)
			{
				LOG("File system error while reading from file %s: %s", file, PHYSFS_getLastError());
				RELEASE(buffer);
			}
			else
				ret = (uint)size;
		}

		if (PHYSFS_close(file_handle) == 0)
			LOG("File %s is not closed properly. Error: %s", file, PHYSFS_getLastError());
	}

	return ret;
}

SDL_RWops *FileSystem::load(const char *file) const
{
	SDL_RWops *ret = NULL;
	char *buffer;
	uint size = load(file, &buffer);

	if (size > 0)
	{
		ret = SDL_RWFromConstMem(buffer, size);
		if (ret != NULL)
			ret->close = close_sdl_rwops;
	}
	
	return ret;
}

int close_sdl_rwops(SDL_RWops *rw)
{
	RELEASE(rw->hidden.mem.base);
	SDL_FreeRW(rw);
	return 0;
}

uint FileSystem::save(const char *file, const char *buffer, uint size) const
{
	uint ret = 0;

	PHYSFS_file *file_handle = PHYSFS_openWrite(file);
	if (file_handle != NULL)
	{
		PHYSFS_sint64 bytes_written = PHYSFS_write(file_handle, (const void*) buffer, 1, size);
		if (bytes_written != size)
			LOG("Failure on writing %s. Error: %s", file, PHYSFS_getLastError());
		else
			ret = (uint)size;

		if (PHYSFS_close(file_handle) == 0)
			LOG("File System can not close file %s. Error: %s", file, PHYSFS_getLastError());
	}
	else
		LOG("File System failure while opening file %s. Error: %s", file, PHYSFS_getLastError());
	
	return ret;
}

bool FileSystem::isDirectory(const char *dir) const
{
	return (PHYSFS_isDirectory(dir) == 0) ? false : true;
}

bool FileSystem::exists(const char *file) const
{
	return (PHYSFS_exists(file) == 0) ? false : true;
}

const char *FileSystem::getSaveDirectory() const
{
	return "save/";
}