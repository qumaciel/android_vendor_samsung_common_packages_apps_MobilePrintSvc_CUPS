#!/usr/bin/env python
# -*- Mode: python -*-

#    Copyright (C) 2001 Artifex Software Inc.
#    All Rights Reserved.
#
# This file is part of GNU ghostscript
#
# GNU ghostscript is free software; you can redistribute it and/or
# modify it under the terms of the version 2 of the GNU General Public
# License as published by the Free Software Foundation.
#
# This software is provided AS-IS with no warranty, either express or
# implied. That is, this program is distributed in the hope that it will 
# be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA, 02110-1301.

# $Id: get_baselines.py,v 1.2 2008/05/04 14:35:06 Arabidopsis Exp $

#
# get_baselines <date>
#
# This script gets the baseline log entries since DATE.  DATE should
# be provided in ctime format (eg: 'Thu Jun 12 12:17:28 2003')

import sys
import time
import string

import gsconf

def usage():
    print "usage: get_baselines <date>"
    print
    print "Dates should be specificied in ctime format."
    print
    sys.exit(1)

if len(sys.argv) == 2:
    try:
        from_date = time.mktime(time.strptime(sys.argv[1]))
    except:
        print "ERROR: Could not parse date."
        sys.exit(1)
else:
    usage()


try:
    baseline_log = open(name)
except:
    print "ERROR: cannot open baseline log",name
    sys.exit(1)

changes = {}
for line in baseline_log.readlines():
    line = line[:-1]
    tokens = string.split(line)
    tm = time.mktime(time.strptime(string.join(tokens[:5])))
    if from_date <= tm:
        changes[string.join(tokens[5:])] = 1

if len(changes) > 0:
    for k in changes.keys():
        print k
else:
    print "No baseline updates."

   
