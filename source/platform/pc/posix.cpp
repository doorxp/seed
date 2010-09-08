/******************************************************************************
 ** Copyright (c) 2010 Seed Developers
 ** All rights reserved
 ** Contact: licensing@seedframework.org
 ** Website: http://www.seedframework.org

 ** This file is part of the Seed Framework.

 ** Commercial Usage
 ** Seed Framework is available under proprietary license for those who cannot,
 ** or choose not to, use LGPL and GPL code in their projects (eg. iPhone,
 ** Nintendo Wii and others).

 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Seed developers gives you certain
 ** additional rights. These rights are described in the Seed Framework LGPL
 ** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
 ** package.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Seed developers at licensing@seedframework.org.
 **
 *****************************************************************************/

#include "platform/pc/platform.h"

#if defined(__linux__) || defined(__APPLE_CC__)

#include "Log.h"

#include <wchar.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define TAG	"[Platform] "

#if defined(_IPHONE_)
#undef WideChar
#include "platform/iphone/IphoneView.h"
#elif defined(__APPLE_CC__)
#include "SeedInit.h"
static char pcBundle[2048];
#endif

BOOL create_directory(const wchar_t *path)
{
	BOOL ret = FALSE;
	int err = mkdir((const char *)path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	if (err == -1)
	{
		switch (errno)
		{
			case EACCES:
			{
				Info(TAG "Permission denied to create '%s'.", path);
			}
			break;

			case EEXIST:
			{
				Info(TAG "Path '%s' already exists.", path);
			}
			break;

			case ENAMETOOLONG:
			{
				Info(TAG "Path name too long: '%s'", path);
			}
			break;

			case ENOENT:
			{
				Info(TAG "Path '%s' does not name an existin entry.", path);
			}
			break;

			case ENOSPC:
			{
				Info(TAG "Not enought space to create '%s'.", path);
			}
			break;

			case ENOTDIR:
			{
				Info(TAG "A component of the path '%s' is not a directory.", path);
			}
			break;

			case EROFS:
			{
				Info(TAG "Read-only filesystem, could not create '%s'.", path);
			}
			break;

			default:
			{
				Info(TAG "An error '%d' ocurred trying to create '%s'.", err, path);
			}
			break;
		}
	}
	else
	{
		ret = TRUE;
	}

	return ret;
}

const wchar_t *get_user_name()
{
	const wchar_t *name = (wchar_t *)getenv("LOGNAME");
	if (!name)
		name = (const wchar_t *)"Noname";
	return name;
}

const wchar_t *get_user_savegame_folder()
{
	return get_user_home_folder();
}

const wchar_t *get_user_appdata_folder()
{
	return get_user_home_folder();
}

const wchar_t *get_user_home_folder()
{
	const wchar_t *home = (wchar_t *)getenv("HOME");
	if (!home)
		home = (const wchar_t *)"./";
	return home;
}

void get_current_directory(wchar_t *buff, int size)
{
#if defined(_IPHONE_)
	memset(buff, '\0', size);
	memcpy(buff, iphGetRootPath(), size);
#elif defined(__APPLE_CC__)
	Seed::Private::iArgc = 1;
	int len = strlen(Seed::Private::pcArgv[0]);
	memcpy(pcBundle, Seed::Private::pcArgv[0], len);
	while (pcBundle[len] != '/') len--;
	len -= strlen("MacOS");
	memset(&pcBundle[len], '\0', sizeof(pcBundle) - len);
	strcpy(&pcBundle[len], "Resources");

	memcpy(buff, pcBundle, size);
#else
	char *b = (char *)static_cast<void *>(buff);
	getcwd(b, size);
#endif
}

BOOL change_directory(const wchar_t *to)
{
	BOOL ret = FALSE;
	const char *path = (const char *)to;
	int err = chdir(path);

	if (err == -1)
	{
		switch (errno)
		{
			case EACCES:
			{
				Info(TAG "Permission denied to create '%s'.", path);
			}
			break;

			case EEXIST:
			{
				Info(TAG "Path '%s' already exists.", path);
			}
			break;

			case ENAMETOOLONG:
			{
				Info(TAG "Path name too long: '%s'", path);
			}
			break;

			case ENOENT:
			{
				Info(TAG "Path '%s' does not name an existin entry.", path);
			}
			break;

			case ENOSPC:
			{
				Info(TAG "Not enought space to create '%s'.", path);
			}
			break;

			case ENOTDIR:
			{
				Info(TAG "A component of the path '%s' is not a directory.", path);
			}
			break;

			case EROFS:
			{
				Info(TAG "Read-only filesystem, could not create '%s'.", path);
			}
			break;

			default:
			{
				Info(TAG "An error '%d' ocurred trying to create '%s'.", err, path);
			}
			break;
		}
	}
	else
	{
		ret = TRUE;
	}

	return ret;

}

void print_system_info()
{
	#warning "Must implement function print_system_info"
}

BOOL system_check_multiple_instance(bool warnUser)
{
	UNUSED(warnUser);
	#warning "Must implement function system_check_multiple_instance"
	return TRUE;
}

#endif // _LINUX_
