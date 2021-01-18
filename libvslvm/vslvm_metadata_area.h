/*
 * Metadata area definitions
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

#if !defined( _VSLVM_METADATA_AREA_H )
#define _VSLVM_METADATA_AREA_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vslvm_metadata_area_header vslvm_metadata_area_header_t;

struct vslvm_metadata_area_header
{
	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The signature
	 * Consists of 16 bytes
	 * Contains: "\x20LVM2\x20x[5A%r0N*>"
	 */
	uint8_t signature[ 16 ];

	/* The version
	 * Consists of 4 bytes
	 */
	uint8_t version[ 4 ];

	/* The data offset
	 * Consists of 8 bytes
	 */
	uint8_t data_offset[ 8 ];

	/* The data size
	 * Consists of 8 bytes
	 */
	uint8_t data_size[ 8 ];
};

typedef struct vslvm_raw_location_descriptor vslvm_raw_location_descriptor_t;

struct vslvm_raw_location_descriptor
{
	/* The offset
	 * Consists of 8 bytes
	 */
	uint8_t offset[ 8 ];

	/* The size
	 * Consists of 8 bytes
	 */
	uint8_t size[ 8 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSLVM_METADATA_AREA_H ) */

