/*
 * The metadata functions
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

#if !defined( _LIBVSLVM_METADATA_H )
#define _LIBVSLVM_METADATA_H

#include <common.h>
#include <types.h>

#include "libvslvm_libbfio.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcsplit.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_segment.h"
#include "libvslvm_volume_group.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_metadata libvslvm_metadata_t;

struct libvslvm_metadata
{
	/* The volume group
	 */
	libvslvm_volume_group_t *volume_group;
};

int libvslvm_metadata_initialize(
     libvslvm_metadata_t **metadata,
     libcerror_error_t **error );

int libvslvm_metadata_free(
     libvslvm_metadata_t **metadata,
     libcerror_error_t **error );

int libvslvm_metadata_read_data(
     libvslvm_metadata_t *metadata,
     const uint8_t *data,
     size_t data_size,
     uint32_t stored_checksum,
     libcerror_error_t **error );

int libvslvm_metadata_read_file_io_handle(
     libvslvm_metadata_t *metadata,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     size64_t metadata_size,
     uint32_t stored_checksum,
     libcerror_error_t **error );

int libvslvm_metadata_read_volume_group(
     libvslvm_metadata_t *metadata,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error );

int libvslvm_metadata_read_physical_volumes(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error );

int libvslvm_metadata_read_physical_volume(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error );

int libvslvm_metadata_read_logical_volumes(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error );

int libvslvm_metadata_read_logical_volume(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error );

int libvslvm_metadata_read_segment(
     libvslvm_metadata_t *metadata,
     libvslvm_logical_volume_values_t *logical_volume_values,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error );

int libvslvm_metadata_read_stripes_list(
     libvslvm_metadata_t *metadata,
     libvslvm_segment_t *segment,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error );

int libvslvm_metadata_get_volume_group(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_METADATA_H ) */

