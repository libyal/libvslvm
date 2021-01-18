/*
 * Library to access the Linux Logical Volume Manager (LVM) volume system
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

#if !defined( _LIBVSLVM_H )
#define _LIBVSLVM_H

#include <libvslvm/codepage.h>
#include <libvslvm/definitions.h>
#include <libvslvm/error.h>
#include <libvslvm/extern.h>
#include <libvslvm/features.h>
#include <libvslvm/types.h>

#include <stdio.h>

#if defined( LIBVSLVM_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBVSLVM_EXTERN \
const char *libvslvm_get_version(
             void );

/* Returns the access flags for reading and writing
 */
LIBVSLVM_EXTERN \
int libvslvm_get_access_flags_read_write(
     void );

/* Returns the access flags for writing
 */
LIBVSLVM_EXTERN \
int libvslvm_get_access_flags_write(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_get_codepage(
     int *codepage,
     libvslvm_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_set_codepage(
     int codepage,
     libvslvm_error_t **error );

/* Determines if a file contains a LVM volume system signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_check_volume_signature(
     const char *filename,
     libvslvm_error_t **error );

#if defined( LIBVSLVM_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a LVM volume system signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_check_volume_signature_wide(
     const wchar_t *filename,
     libvslvm_error_t **error );

#endif /* defined( LIBVSLVM_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSLVM_HAVE_BFIO )

/* Determines if a file contains a LVM volume system signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvslvm_error_t **error );

#endif /* defined( LIBVSLVM_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBVSLVM_EXTERN \
void libvslvm_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_notify_set_stream(
     FILE *stream,
     libvslvm_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_notify_stream_open(
     const char *filename,
     libvslvm_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_notify_stream_close(
     libvslvm_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBVSLVM_EXTERN \
void libvslvm_error_free(
      libvslvm_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_error_fprint(
     libvslvm_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_error_sprint(
     libvslvm_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_error_backtrace_fprint(
     libvslvm_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_error_backtrace_sprint(
     libvslvm_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Handle functions
 * ------------------------------------------------------------------------- */

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_initialize(
     libvslvm_handle_t **handle,
     libvslvm_error_t **error );

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_free(
     libvslvm_handle_t **handle,
     libvslvm_error_t **error );

/* Signals a handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_signal_abort(
     libvslvm_handle_t *handle,
     libvslvm_error_t **error );

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open(
     libvslvm_handle_t *handle,
     const char *filename,
     int access_flags,
     libvslvm_error_t **error );

#if defined( LIBVSLVM_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open_wide(
     libvslvm_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libvslvm_error_t **error );

#endif /* defined( LIBVSLVM_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSLVM_HAVE_BFIO )

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open_file_io_handle(
     libvslvm_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvslvm_error_t **error );

#endif /* defined( LIBVSLVM_HAVE_BFIO ) */

/* Opens the physical volume files
 * This function assumes the physical volume files are in same order as defined by the metadata
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files(
     libvslvm_handle_t *handle,
     char * const filenames[],
     int number_of_filenames,
     libvslvm_error_t **error );

#if defined( LIBVSLVM_HAVE_WIDE_CHARACTER_TYPE )

/* Opens the physical volume files
 * This function assumes the physical volume files are in same order as defined by the metadata
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files_wide(
     libvslvm_handle_t *handle,
     wchar_t * const filenames[],
     int number_of_filenames,
     libvslvm_error_t **error );

#endif /* defined( LIBVSLVM_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSLVM_HAVE_BFIO )

/* Opens the physical volume files
 * This function assumes the physical volume files are in same order as defined by the metadata
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files_file_io_pool(
     libvslvm_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libvslvm_error_t **error );

#endif /* defined( LIBVSLVM_HAVE_BFIO ) */

/* Closes a handle
 * Returns 0 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_close(
     libvslvm_handle_t *handle,
     libvslvm_error_t **error );

/* Retrieves the volume group
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_get_volume_group(
     libvslvm_handle_t *handle,
     libvslvm_volume_group_t **volume_group,
     libvslvm_error_t **error );

/* -------------------------------------------------------------------------
 * Volume group functions
 * ------------------------------------------------------------------------- */

/* Frees a volume group
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_free(
     libvslvm_volume_group_t **volume_group,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_name_size(
     libvslvm_volume_group_t *volume_group,
     size_t *name_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_name(
     libvslvm_volume_group_t *volume_group,
     char *name,
     size_t name_size,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_identifier_size(
     libvslvm_volume_group_t *volume_group,
     size_t *identifier_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_identifier(
     libvslvm_volume_group_t *volume_group,
     char *identifier,
     size_t identifier_size,
     libvslvm_error_t **error );

/* Retrieves the sequence number
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_sequence_number(
     libvslvm_volume_group_t *volume_group,
     uint32_t *sequence_number,
     libvslvm_error_t **error );

/* Retrieves the extent size
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_extent_size(
     libvslvm_volume_group_t *volume_group,
     size64_t *extent_size,
     libvslvm_error_t **error );

/* Retrieves the number of physical volumes
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_number_of_physical_volumes(
     libvslvm_volume_group_t *volume_group,
     int *number_of_physical_volumes,
     libvslvm_error_t **error );

/* Retrieves a specific physical volume
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_physical_volume(
     libvslvm_volume_group_t *volume_group,
     int volume_index,
     libvslvm_physical_volume_t **physical_volume,
     libvslvm_error_t **error );

/* Retrieves the physical volume for an ASCII encoded volume name
 * Returns 1 if successful, 0 if no such physical volume or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_physical_volume_by_name(
     libvslvm_volume_group_t *volume_group,
     const char *volume_name,
     size_t volume_name_length,
     libvslvm_physical_volume_t **physical_volume,
     libvslvm_error_t **error );

/* Retrieves the number of logical volumes
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_number_of_logical_volumes(
     libvslvm_volume_group_t *volume_group,
     int *number_of_logical_volumes,
     libvslvm_error_t **error );

/* Retrieves a specific logical volume
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_volume_group_get_logical_volume(
     libvslvm_volume_group_t *volume_group,
     int volume_index,
     libvslvm_logical_volume_t **logical_volume,
     libvslvm_error_t **error );

/* -------------------------------------------------------------------------
 * Physical volume functions
 * ------------------------------------------------------------------------- */

/* Frees a physical volume
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_free(
     libvslvm_physical_volume_t **physical_volume,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_name_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *name_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_name(
     libvslvm_physical_volume_t *physical_volume,
     char *name,
     size_t name_size,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_identifier_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *identifier_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_identifier(
     libvslvm_physical_volume_t *physical_volume,
     char *identifier,
     size_t identifier_size,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted device path
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_device_path_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *device_path_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted device path
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_device_path(
     libvslvm_physical_volume_t *physical_volume,
     char *device_path,
     size_t device_path_size,
     libvslvm_error_t **error );

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_physical_volume_get_size(
     libvslvm_physical_volume_t *physical_volume,
     size64_t *size,
     libvslvm_error_t **error );

/* -------------------------------------------------------------------------
 * Logical volume functions
 * ------------------------------------------------------------------------- */

/* Frees a logical volume
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_free(
     libvslvm_logical_volume_t **logical_volume,
     libvslvm_error_t **error );

/* Reads (logical volume) data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBVSLVM_EXTERN \
ssize_t libvslvm_logical_volume_read_buffer(
         libvslvm_logical_volume_t *logical_volume,
         void *buffer,
         size_t buffer_size,
         libvslvm_error_t **error );

/* Reads (logical volume) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBVSLVM_EXTERN \
ssize_t libvslvm_logical_volume_read_buffer_at_offset(
         libvslvm_logical_volume_t *logical_volume,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libvslvm_error_t **error );

/* Seeks a certain offset of the (logical volume) data
 * Returns the offset if seek is successful or -1 on error
 */
LIBVSLVM_EXTERN \
off64_t libvslvm_logical_volume_seek_offset(
         libvslvm_logical_volume_t *logical_volume,
         off64_t offset,
         int whence,
         libvslvm_error_t **error );

/* Retrieves the the current offset of the (logical volume) data
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_offset(
     libvslvm_logical_volume_t *logical_volume,
     off64_t *offset,
     libvslvm_error_t **error );

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_size(
     libvslvm_logical_volume_t *logical_volume,
     size64_t *size,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_name_size(
     libvslvm_logical_volume_t *logical_volume,
     size_t *name_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_name(
     libvslvm_logical_volume_t *logical_volume,
     char *name,
     size_t name_size,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_identifier_size(
     libvslvm_logical_volume_t *logical_volume,
     size_t *identifier_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_identifier(
     libvslvm_logical_volume_t *logical_volume,
     char *identifier,
     size_t identifier_size,
     libvslvm_error_t **error );

/* Retrieves the number of segments
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_number_of_segments(
     libvslvm_logical_volume_t *logical_volume,
     int *number_of_segments,
     libvslvm_error_t **error );

/* Retrieves a specific segment
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_segment(
     libvslvm_logical_volume_t *logical_volume,
     int segment_index,
     libvslvm_segment_t **segment,
     libvslvm_error_t **error );

/* -------------------------------------------------------------------------
 * Segment functions
 * ------------------------------------------------------------------------- */

/* Frees a segment
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_segment_free(
     libvslvm_segment_t **segment,
     libvslvm_error_t **error );

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_segment_get_offset(
     libvslvm_segment_t *segment,
     off64_t *offset,
     libvslvm_error_t **error );

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_segment_get_size(
     libvslvm_segment_t *segment,
     size64_t *size,
     libvslvm_error_t **error );

/* Retrieves the number of stripes
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_segment_get_number_of_stripes(
     libvslvm_segment_t *segment,
     int *number_of_stripes,
     libvslvm_error_t **error );

/* Retrieves a specific stripe
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_segment_get_stripe(
     libvslvm_segment_t *segment,
     int stripe_index,
     libvslvm_stripe_t **stripe,
     libvslvm_error_t **error );

/* -------------------------------------------------------------------------
 * Stripe functions
 * ------------------------------------------------------------------------- */

/* Frees a stripe
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_stripe_free(
     libvslvm_stripe_t **stripe,
     libvslvm_error_t **error );

/* Retrieves the size of the ASCII formatted physical volume name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_stripe_get_physical_volume_name_size(
     libvslvm_stripe_t *stripe,
     size_t *physical_volume_name_size,
     libvslvm_error_t **error );

/* Retrieves the ASCII formatted physical volume name
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_stripe_get_physical_volume_name(
     libvslvm_stripe_t *stripe,
     char *physical_volume_name,
     size_t physical_volume_name_size,
     libvslvm_error_t **error );

/* Retrieves the data area offset
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_stripe_get_data_area_offset(
     libvslvm_stripe_t *stripe,
     off64_t *data_area_offset,
     libvslvm_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_H ) */

