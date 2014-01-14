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
	@echo "Usage (for build): make BUILD={debug | release} OMAPES={3.x | 5.x | 6.x | 8.x | 9.x} FBDEV={yes | no} all"
	@echo "      Platform       				OMAPES "
	@echo "      --------					------ "
	@echo "      OMAP35x(SGX core 1.2.1)		         3.x   "
	@echo "      OMAP37x/AM37x(SGX core 1.2.5)           	 5.x   "
	@echo "      816x(389x)/814x(387x)(SGX core 1.2.5)      6.x   "
	@echo "      335x(SGX core 1.2.5 )                      8.x   "
	@echo "      43xx(SGX core 1.2.5 )                      9.x   "
	@echo "--> Specifying OMAPES is mandatory. BUILD=release and FBDEV=yes by default"
	@echo "Usage (for install): make BUILD=(debug | release} OMAPES={3.x | 5.x | 6.x | 8.x | 9.x} install"
	@echo "--> See online Graphics Getting Started Guide for further details."
	@echo ""

###########################################################################
