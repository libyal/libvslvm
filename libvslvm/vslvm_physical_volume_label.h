/*
 * Physical volume label definitions
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

#if !defined( _VSLVM_PHYSICAL_VOLUME_LABEL_H )
#define _VSLVM_PHYSICAL_VOLUME_LABEL_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vslvm_physical_volume_label_header vslvm_physical_volume_label_header_t;

struct vslvm_physical_volume_label_header
{
	/* The signature
	 * Consists of 8 bytes
	 * Contains: "LABELONE"
	 */
	uint8_t signature[ 8 ];

	/* The sector number
	 * Consists of 8 bytes
	 */
	uint8_t sector_number[ 8 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];

	/* The type indicator
	 * Consists of 8 bytes
	 * Contains: "LVM2\x20001"
	 */
	uint8_t type_indicator[ 8 ];
};

typedef struct vslvm_physical_volume_header vslvm_physical_volume_header_t;

struct vslvm_physical_volume_header
{
	/* The identifier
	 * Consists of 32 bytes
	 */
	uint8_t identifier[ 32 ];

	/* The volume size
	 * Consists of 8 bytes
	 */
	uint8_t volume_size[ 8 ];
};

typedef struct vslvm_data_area_descriptor vslvm_data_area_descriptor_t;

struct vslvm_data_area_descriptor
{
	/* The offset 
	 * Consists of 8 bytes
	 */
	uint8_t offset[ 8 ];

	/* The size 
	 * Consists of 8 bytes
	 */
	uint8_t size[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSLVM_PHYSICAL_VOLUME_LABEL_H ) */

