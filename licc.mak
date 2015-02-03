# IBM Developer's Workframe/2 Make File Creation run at 17:47:57 on 03/03/93

# Make File Creation run in directory:
#   E:\NBUILD\DEV\TEST;

CCL = /DINCL_32 /W3 /Ss+ /Gd- /Ge+ /Q+ /Kbcepr /Gm- /Gs- /O+ /Gn- /Rn /C

.SUFFIXES:

.SUFFIXES: .c

licc.exe:  \
  licc.OBJ \
  licc.MAK
   @REM @<<licc.@0
     /NOI /PACKD /PACKC /ST:4096 /BAS:0x10000 /PM:VIO +
     licc.OBJ
     licc.exe
     
     
     ;
<<
   LINK386.EXE @licc.@0
   msgbind licc.msg

{.}.c.obj:
   ICC.exe $(CCL) .\$*.c

!include licc.DEP
