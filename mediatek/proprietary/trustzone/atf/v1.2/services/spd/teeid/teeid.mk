# Copyright (c) 2015-2016 MICROTRUST Incorporated
# All rights reserved
#
# This file and software is confidential and proprietary to MICROTRUST Inc.
# Unauthorized copying of this file and software is strictly prohibited.
# You MUST NOT disclose this file and software unless you get a license
# agreement from MICROTRUST Incorporated.

TEEID_DIR		:=	services/spd/teeid
SPD_INCLUDES		:=	-I${TEEID_DIR}

SPD_SOURCES		:=	teei_fastcall.c	\
	teei_main.c		\
	teei_helpers.S		\
	teei_common.c	\
	teei_pm.c

vpath %.c ${TEEID_DIR}
vpath %.S ${TEEID_DIR}
