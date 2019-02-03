################################################################################
#			     SOL LIBRARY v1.0.0+41
#
# File: sol/Makefile
#
# Description:
# 	This Makefile is part of the Sol Library. It defines the build rules
#
# Authors:
# 	Abhishek Chakravarti <abhishek@taranjali.org>
#
# Copyright:
# 	(c) 2018, Abhishek Chakravarti.
# 	<abhishek@taranjali.org>
#
# License:
# 	Released under the GNU General Public License version 3 (GPLv3).
# 	<http://opensource.org/licenses/GPL-3.0>
# 	See the accompanying README.md file for complete licensing details.
#
# 	By continuing to use and/or distribute this file, you acknowledge that
# 	you have understood these license terms and accept them.
################################################################################




# 	Set directory paths
DIR_BLD  = bld
DIR_SRC  = src
DIR_TEST = test




# 	Set commands
CMD_CC = $(CC)
CMD_SO = $(CC)
CMD_LD = $(CC)
CMD_COV = gcov




# 	Set command options
OPT_CC = -c -fPIC -std=c99 -Wall -g -O0 -coverage
OPT_SO = -shared -g -O0 -coverage
OPT_LD = -std=c99 -Wall -g -O0 -coverage
OPT_COV = -o $(DIR_BLD)




# 	Set command inputs
INP_SO  = $(DIR_BLD)/test.o
INP_COV = $(DIR_BLD)/*.gcda
INP_LD = $(DIR_TEST)/runner.c




# 	Set command dependencies
DEP_LD = $(OUT_SO) -lgcov




# 	Set command outputs
OUT_SO = $(DIR_BLD)/libsol.so
OUT_LD = $(DIR_BLD)/runner




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
	./$(OUT_LD)
	mv *.gcno *.gcda $(DIR_BLD)
	$(CMD_COV) $(OPT_COV) $(INP_COV)




# 	Rule to clean build artefacts
clean:
	mv *.gcov $(DIR_BLD)
	rm -r $(DIR_BLD)




################################################################################
#				      EOF
#               Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
################################################################################

