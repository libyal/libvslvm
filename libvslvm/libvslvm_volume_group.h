/*
 * Volume group functions
 *
 * Copyright (C) 2014-2021, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBVSLVM_INTERNAL_VOLUME_GROUP_H )
#define _LIBVSLVM_INTERNAL_VOLUME_GROUP_H

#include <common.h>
#include <types.h>

#include "libvslvm_extern.h"
#include "libvslvm_io_handle.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_physical_volume.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_internal_volume_group libvslvm_internal_volume_group_t;

struct libvslvm_internal_volume_group
{
	/* The IO handle
	 */
	libvslvm_io_handle_t *io_handle;

	/* The physical volume file IO pool
	 */
	libbfio_pool_t *physical_volume_file_io_pool;

	/* The name
	 */
	char *name;

	/* The name size
	 */
	size_t name_size;

	/* The identfier
	 */
	char identifier[ 39 ];

	/* The sequence number
	 */
	uint32_t sequence_number;

	/* The status
	 */
	uint32_t status;

	/* The flags
	 */
	uint32_t flags;

	/* The extent size
	 */
	size64_t extent_size;

	/* The number of metadata copies
	 */
	int number_of_metadata_copies;

	/* The physical volumes array
	 */
	libcdata_array_t *physical_volumes_array;

	/* The logical volumes array
	 */
	libcdata_array_t *logical_volumes_array;
};

int libvslvm_volume_group_initialize(
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_free(
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error );

int libvslvm_internal_volume_group_free(
     libvslvm_internal_volume_group_t **internal_volume_group,
     libcerror_error_t **error );

int libvslvm_volume_group_set_io_values(
     libvslvm_volume_group_t *volume_group,
     libvslvm_io_handle_t *io_handle,
     libbfio_pool_t *physical_volume_file_io_pool,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_name_size(
     libvslvm_volume_group_t *volume_group,
     size_t *name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_name(
     libvslvm_volume_group_t *volume_group,
     char *name,
     size_t name_size,
     libcerror_error_t **error );

int libvslvm_internal_volume_group_set_name(
     libvslvm_internal_volume_group_t *internal_volume_group,
     const char *name,
     size_t name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_identifier_size(
     libvslvm_volume_group_t *volume_group,
     size_t *identifier_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_identifier(
     libvslvm_volume_group_t *volume_group,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

int libvslvm_volume_group_set_identifier(
     libvslvm_volume_group_t *volume_group,
     const char *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_sequence_number(
     libvslvm_volume_group_t *volume_group,
     uint32_t *sequence_number,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_extent_size(
     libvslvm_volume_group_t *volume_group,
     size64_t *extent_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_number_of_physical_volumes(
     libvslvm_volume_group_t *volume_group,
     int *number_of_physical_volumes,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_physical_volume(
     libvslvm_volume_group_t *volume_group,
     int volume_index,
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_physical_volume_by_name(
     libvslvm_volume_group_t *volume_group,
     const char *volume_name,
     size_t volume_name_length,
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error );

int libvslvm_volume_group_append_physical_volume(
     libvslvm_volume_group_t *volume_group,
     libvslvm_physical_volume_t *physical_volume,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_number_of_logical_volumes(
     libvslvm_volume_group_t *volume_group,
     int *number_of_logical_volumes,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_logical_volume(
     libvslvm_volume_group_t *volume_group,
     int volume_index,
     libvslvm_logical_volume_t **logical_volume,
     libcerror_error_t **error );

int libvslvm_volume_group_append_logical_volume(
     libvslvm_volume_group_t *volume_group,
     libvslvm_logical_volume_values_t *logical_volume_values,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_INTERNAL_VOLUME_GROUP_H ) */

