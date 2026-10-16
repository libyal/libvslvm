/*
 * raid functions
 *
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvslvm_libcerror.h"
#include "libvslvm_raid.h"
#include "libvslvm_types.h"

 /* Creates a raid
  * Make sure the value raid is referencing, is set to NULL
  * Returns 1 if successful or -1 on error
  */
int libvslvm_raid_initialize(
	libvslvm_raid_t **raid,  
	libcerror_error_t **error)
{
	libvslvm_internal_raid_t *internal_raid = NULL;
	static char *function = "libvslvm_raid_initialize";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	if (*raid != NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_RUNTIME,
			LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
			"%s: invalid raid value already set.",
			function);

		return(-1);
	}
	internal_raid = memory_allocate_structure(
		libvslvm_internal_raid_t);

	if (internal_raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			"%s: unable to create raid.",
			function);

		goto on_error;
	}
	if (memory_set(
		internal_raid,
		0,
		sizeof(libvslvm_internal_raid_t)) == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_SET_FAILED,
			"%s: unable to clear raid.",
			function);

		goto on_error;
	}
	*raid = (libvslvm_raid_t *)internal_raid;

	return(1);

on_error:
	if (internal_raid != NULL)
	{
		memory_free(
			internal_raid);
	}
	return(-1);
}

/* Frees a raid
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raid_free(
	libvslvm_raid_t **raid,
	libcerror_error_t **error)
{
	static char *function = "libvslvm_raid_free";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	if (*raid != NULL)
	{
		*raid = NULL;
	}
	return(1);
}

/* Frees a raid
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_raid_free(
	libvslvm_internal_raid_t **internal_raid,
	libcerror_error_t **error)
{
	static char *function = "libvslvm_internal_raid_free";

	if (internal_raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	if (*internal_raid != NULL)
	{
		if ((*internal_raid)->meta_name != NULL)
		{
			memory_free(
				(*internal_raid)->meta_name);
		}
		if ((*internal_raid)->image_name != NULL)
		{
			memory_free(	(*internal_raid)->image_name);
		}
		memory_free(
			*internal_raid);

		*internal_raid = NULL;
	}
	return(1);
}

/* Retrieves the size of the ASCII formatted meta name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raid_get_meta_name_size(
	libvslvm_raid_t *raid,
	size_t *meta_name_size,
	libcerror_error_t **error)
{
	libvslvm_internal_raid_t *internal_raid = NULL;
	static char *function = "libvslvm_raid_get_meta_name_size";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	internal_raid = (libvslvm_internal_raid_t *)raid;

	if (meta_name_size == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid image name size.",
			function);

		return(-1);
	}
	*meta_name_size = internal_raid->meta_name_size;

	return(1);
}

/* Retrieves the ASCII formatted meta name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raid_get_meta_name(
	libvslvm_raid_t *raid,
	char *meta_name,
	size_t meta_name_size,
	libcerror_error_t **error)
{
	libvslvm_internal_raid_t *internal_raid = NULL;
	static char *function = "libvslvm_raid_get_meta_name";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	internal_raid = (libvslvm_internal_raid_t *)raid;

	if (meta_name == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid meta name.",
			function);

		return(-1);
	}
	if (meta_name_size > (size_t)SSIZE_MAX)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			"%s: invalid meta name size value exceeds maximum.",
			function);

		return(-1);
	}
	if (meta_name_size < internal_raid->meta_name_size)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			"%s: invalid meta name size value too small.",
			function);

		return(-1);
	}
	if (memory_copy(
		meta_name,
		internal_raid->meta_name,
		internal_raid->meta_name_size) == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			"%s: unable to copy meta name.",
			function);

		return(-1);
	}
	meta_name[internal_raid->meta_name_size - 1] = 0;

	return(1);
}

/* Sets the physical volume name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raid_set_meta_name(
	libvslvm_raid_t *raid,
	const char *meta_name,
	size_t meta_name_size,
	libcerror_error_t **error)
{
	libvslvm_internal_raid_t *internal_raid = NULL;
	static char *function = "libvslvm_raid_set_meta_name";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	internal_raid = (libvslvm_internal_raid_t *)raid;

	if (meta_name == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid physical volume name.",
			function);

		return(-1);
	}
	if (meta_name_size > (size_t)SSIZE_MAX)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			"%s: physical volume name size value exceeds maximum.",
			function);

		return(-1);
	}
	if (internal_raid->meta_name != NULL)
	{
		memory_free(
			internal_raid->meta_name);

		internal_raid->meta_name = NULL;
		internal_raid->meta_name_size = 0;
	}
	internal_raid->meta_name = (char *)memory_allocate(
		sizeof(char) * meta_name_size);

	if (internal_raid->meta_name == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			"%s: unable to create physical volume name.",
			function);

		goto on_error;
	}
	if (memory_copy(
		internal_raid->meta_name,
		meta_name,
		meta_name_size) == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			"%s: unable to copy physical volume name.",
			function);

		goto on_error;
	}
	internal_raid->meta_name[meta_name_size - 1] = 0;

	internal_raid->meta_name_size = meta_name_size;

	return(1);

on_error:
	if (internal_raid->meta_name != NULL)
	{
		memory_free(
			internal_raid->meta_name);

		internal_raid->meta_name = NULL;
	}
	internal_raid->meta_name_size = 0;

	return(-1);
}


/* Retrieves the size of the ASCII formatted image name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raid_get_image_name_size(
	libvslvm_raid_t *raid,
	size_t *image_name_size,
	libcerror_error_t **error)
{
	libvslvm_internal_raid_t *internal_raid = NULL;
	static char *function = "libvslvm_raid_get_image_name_size";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	internal_raid = (libvslvm_internal_raid_t *)raid;

	if (image_name_size == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid image name size.",
			function);

		return(-1);
	}
	*image_name_size = internal_raid->image_name_size;

	return(1);
}

/* Retrieves the ASCII formatted image name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raid_get_image_name(
	libvslvm_raid_t *raid,
	char *image_name,
	size_t image_name_size,
	libcerror_error_t **error)
{
	libvslvm_internal_raid_t *internal_raid = NULL;
	static char *function = "libvslvm_raid_get_image_name";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	internal_raid = (libvslvm_internal_raid_t *)raid;

	if (image_name == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid image name.",
			function);

		return(-1);
	}
	if (image_name_size > (size_t)SSIZE_MAX)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			"%s: invalid image name size value exceeds maximum.",
			function);

		return(-1);
	}
	if (image_name_size < internal_raid->image_name_size)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			"%s: invalid image name size value too small.",
			function);

		return(-1);
	}
	if (memory_copy(
		image_name,
		internal_raid->image_name,
		internal_raid->image_name_size) == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			"%s: unable to copy image name.",
			function);

		return(-1);
	}
	image_name[internal_raid->image_name_size - 1] = 0;

	return(1);
}

/* Sets the physical volume name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raid_set_image_name(
	libvslvm_raid_t *raid,
	const char *image_name,
	size_t image_name_size,
	libcerror_error_t **error)
{
	libvslvm_internal_raid_t *internal_raid = NULL;
	static char *function = "libvslvm_raid_set_image_name";

	if (raid == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid raid.",
			function);

		return(-1);
	}
	internal_raid = (libvslvm_internal_raid_t *)raid;

	if (image_name == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			"%s: invalid physical volume name.",
			function);

		return(-1);
	}
	if (image_name_size > (size_t)SSIZE_MAX)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			"%s: physical volume name size value exceeds maximum.",
			function);

		return(-1);
	}
	if (internal_raid->image_name != NULL)
	{
		memory_free(
			internal_raid->image_name);

		internal_raid->image_name = NULL;
		internal_raid->image_name_size = 0;
	}
	internal_raid->image_name = (char *)memory_allocate(
		sizeof(char) * image_name_size);

	if (internal_raid->image_name == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			"%s: unable to create physical volume name.",
			function);

		goto on_error;
	}
	if (memory_copy(
		internal_raid->image_name,
		image_name,
		image_name_size) == NULL)
	{
		libcerror_error_set(
			error,
			LIBCERROR_ERROR_DOMAIN_MEMORY,
			LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			"%s: unable to copy physical volume name.",
			function);

		goto on_error;
	}
	internal_raid->image_name[image_name_size - 1] = 0;

	internal_raid->image_name_size = image_name_size;

	return(1);

on_error:
	if (internal_raid->image_name != NULL)
	{
		memory_free(
			internal_raid->image_name);

		internal_raid->image_name = NULL;
	}
	internal_raid->image_name_size = 0;

	return(-1);
}

