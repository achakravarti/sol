################################################################################
#			     SOL LIBRARY v1.0.0+41
#
# File: sol/Makefile
#
# Description:
# 	This Makefile is part of the Sol Library. It defines the build rules.
#
# Authors:
# 	Abhishek Chakravarti <abhishek@taranjali.org>
#
# Copyright:
# 	(c) 2019, Abhishek Chakravarti.
# 	<abhishek@taranjali.org>
#
# License:
# 	Released under the GNU General Public License version 3 (GPLv3)
# 	<http://opensource.org/licenses/GPL-3.0>. See the accompanying LICENSE
# 	file for complete licensing details.
#
# 	BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT
# 	YOU HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
################################################################################




# 	Set directory paths
DIR_BLD  = bld
DIR_BIN  = $(DIR_BLD)/bin
DIR_COV  = $(DIR_BLD)/cov
DIR_SRC  = src
DIR_TEST = test




# 	Set commands
CMD_CC  = $(CC)
CMD_SO  = $(CC)
CMD_LD  = $(CC)
CMD_COV = gcov
CMD_RUN = ./$(OUT_LD)




# 	Set command options
OPT_CC  = -c -fPIC -std=c99 -Wall -Wextra -g -O0 -coverage
OPT_SO  = -shared -g -O0 -coverage
OPT_LD  = -std=c99 -Wall -Wextra -g -O0 -coverage
OPT_COV = -o $(DIR_BLD)




# 	Set command inputs
INP_SO  = $(DIR_BLD)/error.o \
	  $(DIR_BLD)/test.o  \
	  $(DIR_BLD)/ptr.o   \
	  $(DIR_BLD)/log.o   \
	  $(DIR_BLD)/prim.o  \
	  $(DIR_BLD)/elem.o  \
	  $(DIR_BLD)/list.o
INP_LD  = $(DIR_TEST)/runner.c   \
	  $(DIR_TEST)/ts-error.c \
	  $(DIR_TEST)/ts-test.c  \
	  $(DIR_TEST)/ts-hint.c  \
	  $(DIR_TEST)/ts-env.c   \
	  $(DIR_TEST)/ts-ptr.c   \
	  $(DIR_TEST)/ts-ptr2.c  \
	  $(DIR_TEST)/ts-log.o   \
	  $(DIR_TEST)/ts-prim.o  \
	  $(DIR_TEST)/ts-elem-meta.o
INP_COV = $(DIR_BLD)/error.gcda $(DIR_BLD)/test.gcda $(DIR_BLD)/ptr.gcda \
	  $(DIR_BLD)/log.gcda $(DIR_BLD)/prim.gcda $(DIR_BLD)/elem.gcda
INP_RUN = $(DIR_BLD)/test.log




# 	Set command dependencies
DEP_LD  = $(OUT_SO) -lgcov
DEP_COV = *.gcno *.gcda




# 	Set command outputs
OUT_SO  = $(DIR_BLD)/libsol.so
OUT_LD  = $(DIR_BLD)/runner
OUT_COV = *.gcov




# 	Set rule to build test runner
$(OUT_LD): $(OUT_SO) $(INP_LD)
	$(CMD_LD) $(OPT_LD) $(INP_LD) $(DEP_LD) -o $@




# 	Set rule to build shared library
$(OUT_SO): $(INP_SO)
	$(CMD_SO) $(OPT_SO) $(INP_SO) -o $@




# 	Set rule to build objects for shared library
$(DIR_BLD)/%.o: $(DIR_SRC)/%.c
	mkdir -p $(DIR_BLD); $(CMD_CC) $(OPT_CC) $< -o $@




# 	Rule to generate integration build
integration: $(OUT_LD)
	$(CMD_RUN) $(INP_RUN)
	mv $(DEP_COV) $(DIR_BLD)
	$(CMD_COV) $(OPT_COV) $(INP_COV)
	mkdir -p $(DIR_BIN)
	mkdir -p $(DIR_COV)
	mv $(OUT_LD) $(OUT_SO) $(DIR_BLD)/*.o $(DIR_BIN)
	mv $(OUT_COV) $(DIR_BLD)/*.gcno $(DIR_BLD)/*.gcda $(DIR_COV)




# 	Rule to clean build artefacts
clean:
	rm -rf $(DIR_BLD)




################################################################################
#				      EOF
#               Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
################################################################################

