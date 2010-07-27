// This file has been automatically generated by "generate_keys.sh"
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with this library; see the file COPYING.LIB.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
#ifndef KCKEY_H
#define KCKEY_H

typedef struct {
	const char *name;
	int code;
} KKeys;

#define MAX_KEY_LENGTH           15   // should be calculated (gawk ?)
#define MAX_KEY_MODIFIER_LENGTH   21  // "SHIFT + CRTL + ALT + " :
#define MAX_FCTN_LENGTH           50  // arbitrary limit
#define NB_KEYS                 278
extern const KKeys kde_KKEYS[NB_KEYS];

#endif
