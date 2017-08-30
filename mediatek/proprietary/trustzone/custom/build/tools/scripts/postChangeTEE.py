#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2015 - 2016 MediaTek Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

import argparse
import os
import sys

DEBUG=False

HEADER = '\033[95m'
OKBLUE = '\033[94m'
OKGREEN = '\033[92m'
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'
BOLD = "\033[1m"

def infog(msg):
    print OKGREEN + msg + ENDC

def info(msg):
    print OKBLUE + msg + ENDC

def warn(msg):
    print WARNING + msg + ENDC

def err(msg):
    print FAIL + msg + ENDC

def upgrade_preloader_project_makefile(proj, base_proj):
    print "Upgrade Preloader Project Makefile ..."

    output = ""
    export = ""
    path = "./../../../../../../../.."

    makefile = "%s/vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/%s/%s.mk" % (path, proj, proj)
    if (not os.path.exists(makefile)) and (base_project != ""):
        makefile = "%s/vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/%s/%s.mk" % (path, base_proj, base_proj)

    if DEBUG:
        infog("PreloaderConfig=%s exists=%s" % (makefile, os.path.exists(makefile)))

    with open(makefile, 'r') as f:
        for line in f:
            if line.find("export") != -1:
                export = line.strip()
            else:
                output += line
        if export.find("MTK_TEE_SUPPORT") == -1:
            export += " MTK_TEE_SUPPORT"
        if export.find("TRUSTONIC_TEE_SUPPORT") == -1:
            export += " TRUSTONIC_TEE_SUPPORT"
        if export.find("MICROTRUST_TEE_SUPPORT") == -1:
            export += " MICROTRUST_TEE_SUPPORT"
        if export.find("MTK_GOOGLE_TRUSTY_SUPPORT") == -1:
            export += " MTK_GOOGLE_TRUSTY_SUPPORT"
        print export
        output += export

    if DEBUG:
        infog(output)

    with open(makefile, 'w') as f:
        f.write(output)

    print "Upgrade Preloader Project Makefile ... DONE"

def main(args):
	upgrade_preloader_project_makefile(args.project, args.base_project)
	pass

if __name__ == "__main__":

	parser = argparse.ArgumentParser()
	parser.add_argument("--project", help="MTK Project Name")
	parser.add_argument("--base_project", help="MTK Base Project Name")
	args = parser.parse_args()

	if args.project:
		main(args)
	else:
		print "Usage: %s -h or --help." % sys.argv[0]

