/*
 *  ircd-hybrid: an advanced, lightweight Internet Relay Chat Daemon (ircd)
 *
 *  Copyright (c) 1997-2014 ircd-hybrid development team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 *  USA
 */

/*! \file ipcache.h
 * \brief Routines to count connections from particular IP addresses.
 * \version $Id: ipcache.h 4324 2014-08-01 16:59:35Z michael $
 */

#ifndef INCLUDED_ipcache_h
#define INCLUDED_ipcache_h
#include "ircd_defs.h"

/* usually, with hash tables, you use a prime number...
 * but in this case I am dealing with ip addresses,
 * not ascii strings.
 */
#define IP_HASH_SIZE 0x1000

struct ip_entry
{
  dlink_node node;                /**< Doubly linked list node. */
  struct irc_ssaddr ip;
  unsigned int count;             /**< Number of registered users using this IP */
  unsigned int connection_count;  /**< Number of connections from this IP in the last throttle_time duration */
  time_t last_attempt;            /**< The last time someone connected from this IP */
};

extern struct ip_entry *ipcache_find_or_add_address(struct irc_ssaddr *);
extern void ipcache_remove_address(struct irc_ssaddr *);
extern void ipcache_get_stats(unsigned int *, uint64_t *);
extern void ipcache_init(void);
#endif