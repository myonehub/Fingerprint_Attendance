# invoke SourceDir generated makefile for idle.p28L
idle.p28L: .libraries,idle.p28L
.libraries,idle.p28L: package/cfg/idle_p28L.xdl
	$(MAKE) -f C:\Users\marki\OneDrive\Desktop\Fingerprint_Attendance\12345\idle_TMS320F28027/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\marki\OneDrive\Desktop\Fingerprint_Attendance\12345\idle_TMS320F28027/src/makefile.libs clean

