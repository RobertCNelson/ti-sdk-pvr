include Rules.make
include Makefile.KM
include Makefile.SDK

.PHONY: all

clean: clean_km clean_sdk

all: all_km all_sdk

install: install_km install_sdk

############################# HELP ##################################
help:
	@echo ""
	@echo "Usage (for build): make BUILD={debug | release} OMAPES={3.x | 5.x | 6.x | 8.x} FBDEV={yes | no} SUPPORT_XORG= {1 | 0 }  all"
	@echo "      Platform       				OMAPES "
	@echo "      --------					------ "
	@echo "      OMAP35x(SGX core 1.2.1)		         3.x   ( Not Supported in this release )"
	@echo "      OMAP37x/AM37x(SGX core 1.2.5)           	 5.x   ( Not supported in this release )"
	@echo "      811x(SGX core 1.2.5)                        6.x   "
	@echo "      335x(SGX core 1.2.5 )                       8.x   (Not supported in this release)"
	@echo "--> Specifying OMAPES is mandatory. BUILD=release and FBDEV=yes SUPPORT_XORG=0(not enabled) by default"
	@echo "Usage (for install): make BUILD=(debug | release} OMAPES={3.x | 5.x | 6.x | 8.x} EGLIMAGE={1 | 0} install"
	@echo "--> See online Graphics Getting Started Guide for further details."
	@echo ""

###########################################################################
