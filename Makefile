CC = cl
LK = link
CFLAGS = /c /O2 /I "E:/python/include"
LDFLAGS= /dll /libpath:"E:/python/libs"

spider.dll : spider.obj main.obj
	$(LK) $(LDFLAGS) /out:spider.dll /implib:spider.lib *.obj
spider.obj : spider.c spider.h
	$(CC) $(CFLAGS) spider.c
main.obj : main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	@del *.obj