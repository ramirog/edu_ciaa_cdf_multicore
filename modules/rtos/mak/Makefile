###############################################################################
#
# Copyright 2014, 2015, Mariano Cerdeiro
# Copyright 2014, ACSE, CADIEEL
#    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
#    CADIEEL: http://www.cadieel.org.ar
# All rights reserved.
#
# This file is part of CIAA Firmware.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################
# library

define RTOS_TEMPLATE

LIBS        += rtos_$(1)
# version
rtos_$(1)_VERSION		    = 1.0.1
# library path
rtos_$(1)_PATH 		   	= $(ROOT_DIR)$(DS)modules$(DS)rtos
# gen dir
rtos_$(1)_GEN_DIR				 = $$(rtos_$(1)_PATH)$(DS)gen
# library source path
rtos_$(1)_SRC_PATH 	      = $$(rtos_$(1)_PATH)$(DS)src
# library include path
rtos_$(1)_INC_PATH 	      = $$(rtos_$(1)_PATH)$(DS)inc								\
	$$(rtos_$(1)_PATH)$(DS)inc$(DS)$$(ARCH)								\
	$$(rtos_$(1)_PATH)$(DS)inc$(DS)$$(ARCH)$(DS)$$(CPUTYPE)							\
	$$(rtos_$(1)_GEN_DIR)$(DS)inc														\
	$$(rtos_$(1)_GEN_DIR)$(DS)inc$(DS)$$(ARCH)											\
	$$(rtos_$(1)_GEN_DIR)$(DS)inc$(DS)$$(ARCH)$(DS)$$(CPUTYPE)
# library source files
rtos_$(1)_SRC_FILES 	  = $$(wildcard $$(rtos_$(1)_SRC_PATH)$(DS)*.c)						\
						$$(wildcard $$(rtos_$(1)_SRC_PATH)$(DS)$$(ARCH)$(DS)*.c)	\
						$$(wildcard $$(rtos_$(1)_SRC_PATH)$(DS)$$(ARCH)$(DS)*.s)	\
						$$(wildcard $$(rtos_$(1)_GEN_DIR)$(DS)src$(DS)*.c)				\
						$$(wildcard $$(rtos_$(1)_GEN_DIR)$(DS)src$(DS)$$(ARCH)$(DS)*.c)
# include needed makefiles depending on the architecture
-include modules$(DS)rtos$(DS)mak$(DS)$$(ARCH)$(DS)Makefile

endef

$(eval $(call RTOS_TEMPLATE,$(CORE_ID)))

