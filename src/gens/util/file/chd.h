#ifndef HAD_CHD_H

/*
  NiH: chd.h,v 1.3 2004/06/25 23:31:08 dillo Exp

  chd.h -- accessing chd files
  Copyright (C) 2004 Dieter Baron and Thomas Klausner

  This file is part of ckmame, a program to check rom sets for MAME.
  The authors can be contacted at <nih@giga.or.at>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#define CHD_ERR_NONE	0	/* N no error */
#define CHD_ERR_OPEN	1	/* S cannot open file */
#define CHD_ERR_READ	2	/* S read error */
#define CHD_ERR_NO_CHD	3	/* N not a CHD file */
#define CHD_ERR_VERSION	4	/* N unsupported version */
#define CHD_ERR_INVAL	5	/* N invalid argument */
#define CHD_ERR_SEEK	6	/* S seek error */
#define CHD_ERR_NOTSUP	7	/* N unsupported chd feature */
#define CHD_ERR_ZLIB	8	/* Z zlib error */
#define CHD_ERR_CRC	9	/* N CRC mismatch */
#define CHD_ERR_NOMEM	10	/* N out of memory */

#define CHD_MAP_TYPE_COMPRESSED		0x01
#define CHD_MAP_TYPE_UNCOMPRESSED	0x02
#define CHD_MAP_TYPE_MINI		0x03
#define CHD_MAP_TYPE_SELF_HUNK		0x04
#define CHD_MAP_TYPE_PARENT_HUNK	0x05
#define CHD_MAP_TYPE_MASK		0x0f
#define CHD_MAP_FL_NOCRC		0x10

#define CHD_COMP_NONE			0x0
#define CHD_COMP_ZLIB			0x1
#define CHD_COMP_ZLIB_PLUS		0x2



struct chd_map_entry {
    uint64_t offset;	/* offse t within the file of the data */
    uint32_t crc;	/* 32-bit CRC of the data */
    uint16_t length;	/* length of the data */
    uint16_t flags;	/* misc flags */
};

struct chd {
    FILE *f;
    char *name;
    int error;

    uint32_t hdr_length;	/* length of header data */
    uint32_t version;		/* drive format version */
    uint32_t flags;		/* flags field */
    uint32_t compression;	/* compression type */
    uint32_t hunk_len;		/* number of bytes per hunk */
    uint32_t total_hunks;	/* total # of hunks represented */
    uint64_t total_len;		/* logical size of the data */
    uint64_t meta_offset;	/* offset in file of first metadata */
    uint8_t md5[16];		/* MD5 checksum of raw data */
    uint8_t parent_md5[16];	/* MD5 checksum of parent file */
    uint8_t sha1[20];           /* SHA1 checksum of raw data */
    uint8_t parent_sha1[20];	/* SHA1 checksum of parent file */

    struct chd_map_entry *map;	/* hunk map */
    char *buf;			/* decompression buffer */
    z_stream z;			/* decompressor */
    int hno;			/* hunk currently in hbuf */
    char *hbuf;			/* hunk data buffer */
};



void chd_close(struct chd *);
struct chd *chd_open(const char *, int *);
int chd_read_hunk(struct chd *, int, char *);
int chd_read_range(struct chd *, char *, int, int);

#endif /* chd.h */
