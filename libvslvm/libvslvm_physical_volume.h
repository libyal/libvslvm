/*
 * Physical volume functions
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

#if !defined( _LIBVSLVM_INTERNAL_PHYSICAL_VOLUME_H )
#define _LIBVSLVM_INTERNAL_PHYSICAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "libvslvm_data_area_descriptor.h"
#include "libvslvm_extern.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libfdata.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *vslvm_physical_volume_label_signature;

typedef struct libvslvm_internal_physical_volume libvslvm_internal_physical_volume_t;

struct libvslvm_internal_physical_volume
{
	/* The name
	 */
	char *name;

	/* The name size
	 */
	size_t name_size;

	/* The identfier
	 */
	char identifier[ 39 ];

	/* The device path
	 */
	char *device_path;

	/* The device path size
	 */
	size_t device_path_size;

	/* The size
	 */
	size64_t size;

	/* The data area descriptors array
	 */
	libcdata_array_t *data_area_descriptors_array;

	/* The metadata area descriptors array
	 */
	libcdata_array_t *metadata_area_descriptors_array;
};

int libvslvm_physical_volume_initialize(
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_free(
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error );

int libvslvm_internal_physical_volume_free(
     libvslvm_internal_physical_volume_t **internal_physical_volume,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_name_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_name(
     libvslvm_physical_volume_t *physical_volume,
     char *name,
     size_t name_size,
     libcerror_error_t **error );

int libvslvm_physical_volume_set_name(
     libvslvm_physical_volume_t *physical_volume,
     const char *name,
     size_t name_size,
     libcerror_error_t **error );

int libvslvm_physical_volume_compare_by_name(
     libvslvm_physical_volume_t *physical_volume,
     const char *name,
     size_t name_length,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_identifier_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *identifier_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_identifier(
     libvslvm_physical_volume_t *physical_volume,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

int libvslvm_physical_volume_set_identifier(
     libvslvm_physical_volume_t *physical_volume,
     const char *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_device_path_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *device_path_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_device_path(
     libvslvm_physical_volume_t *physical_volume,
     char *device_path,
     size_t device_path_size,
     libcerror_error_t **error );

int libvslvm_physical_volume_set_device_path(
     libvslvm_physical_volume_t *physical_volume,
     const char *device_path,
     size_t device_path_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_size(
     libvslvm_physical_volume_t *physical_volume,
     size64_t *size,
     libcerror_error_t **error );

int libvslvm_physical_volume_get_number_of_data_area_descriptors(
     libvslvm_physical_volume_t *physical_volume,
     int *number_of_data_area_descriptors,
     libcerror_error_t **error );

int libvslvm_physical_volume_get_data_area_descriptor(
     libvslvm_physical_volume_t *physical_volume,
     int data_area_descriptor_index,
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error );

int libvslvm_physical_volume_get_data_area_descriptor_by_offset(
     libvslvm_physical_volume_t *physical_volume,
     uint64_t offset,
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error );

int libvslvm_physical_volume_get_number_of_metadata_area_descriptors(
     libvslvm_physical_volume_t *physical_volume,
     int *number_of_data_area_descriptors,
     libcerror_error_t **error );

int libvslvm_physical_volume_get_metadata_area_descriptor(
     libvslvm_physical_volume_t *physical_volume,
     int data_area_descriptor_index,
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error );

int libvslvm_internal_physical_volume_read_label_data(
     libvslvm_internal_physical_volume_t *internal_physical_volume,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvslvm_physical_volume_read_label_file_io_pool(
     libvslvm_physical_volume_t *physical_volume,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     off64_t file_offset,
     libcerror_error_t **error );

int libvslvm_physical_volume_read_element_data(
     intptr_t *data_handle,
     libbfio_pool_t *file_io_pool,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int file_io_pool_entry,
     off64_t physical_volume_offset,
     size64_t physical_volume_size,
     uint32_t element_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_INTERNAL_PHYSICAL_VOLUME_H ) */

