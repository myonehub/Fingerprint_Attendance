#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_76_02_02/packages;C:/Users/marki/OneDrive/Desktop/12345/idle_TMS320F28027/.config
override XDCROOT = C:/ti/xdctools_3_51_01_18_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_76_02_02/packages;C:/Users/marki/OneDrive/Desktop/12345/idle_TMS320F28027/.config;C:/ti/xdctools_3_51_01_18_core/packages;..
HOSTOS = Windows
endif