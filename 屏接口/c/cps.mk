
cps.dll: dlldata.obj c_p.obj c_i.obj
	link /dll /out:cps.dll /def:cps.def /entry:DllMain dlldata.obj c_p.obj c_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del cps.dll
	@del cps.lib
	@del cps.exp
	@del dlldata.obj
	@del c_p.obj
	@del c_i.obj
