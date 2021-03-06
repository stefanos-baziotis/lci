/*  Interface for the string interning

	Copyright (C) 2019 Stefanos Baziotis 
	This file is part of LCI
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details. */


#pragma once

const char *str_intern(const char *str);
void str_intern_initialize(void);
void str_intern_free(void);
