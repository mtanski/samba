/*
 *  idmap_autorid: static map between Active Directory/NT RIDs
 *  and RFC 2307 accounts. This file contains common functions
 *  and structures used by idmap_autorid and net idmap autorid utilities
 *
 *  Copyright (C) Christian Ambach, 2010-2012
 *  Copyright (C) Atul Kulkarni, 2013
 *  Copyright (C) Michael Adam, 2012-2013
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _IDMAP_AUTORID_H_
#define _IDMAP_AUTORID_H_

#include "includes.h"
#include "system/filesys.h"
#include "dbwrap/dbwrap.h"
#include "dbwrap/dbwrap_open.h"
#include "../lib/util/util_tdb.h"
#include "winbindd/idmap_tdb_common.h"

#define HWM "NEXT RANGE"
#define ALLOC_HWM_UID "NEXT ALLOC UID"
#define ALLOC_HWM_GID "NEXT ALLOC GID"
#define ALLOC_RANGE "ALLOC"
#define CONFIGKEY "CONFIG"

struct autorid_global_config {
	uint32_t minvalue;
	uint32_t rangesize;
	uint32_t maxranges;
};

struct autorid_range_config {
	fstring domsid;
	uint32_t rangenum;
	uint32_t domain_range_index;
	uint32_t low_id;
};

NTSTATUS idmap_autorid_get_domainrange(struct db_context *db,
				       struct autorid_range_config *range,
				       bool read_only);

NTSTATUS idmap_autorid_init_hwm(struct db_context *db, const char *hwm);

NTSTATUS idmap_autorid_db_init(const char *path,
			       TALLOC_CTX *mem_ctx,
			       struct db_context **db);

NTSTATUS idmap_autorid_loadconfig(struct db_context *db,
				  TALLOC_CTX *ctx,
				  struct autorid_global_config **result);

NTSTATUS idmap_autorid_saveconfig(struct db_context *db,
				  struct autorid_global_config *cfg);

/**
 * get the range config string stored in the database
 */
NTSTATUS idmap_autorid_getconfigstr(struct db_context *db, TALLOC_CTX *mem_ctx,
				    char **result);

/**
 * parse the handed in config string and fill the provided config structure.
 * return false if the string could not be parsed.
 */
bool idmap_autorid_parse_configstr(const char *configstr,
				   struct autorid_global_config *cfg);

#endif /* _IDMAP_AUTORID_H_ */