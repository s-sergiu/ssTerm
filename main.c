#include <X11/Xlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	XEvent event;
	Display *dpy;	
	Window w;
	int s;
	char buf[1];
	int buff_ctr;

	dpy = XOpenDisplay(NULL);
	s = DefaultScreen(dpy);
	w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 10, 10, 100, 100, 1, BlackPixel(dpy, s), WhitePixel(dpy, s));
	XSelectInput(dpy, w, ExposureMask | KeyPressMask);
	XMapWindow(dpy, w);
	buf[0] = 'a';
	buff_ctr = 0;
	while (1)
	{
		XNextEvent(dpy, &event);
		if (event.type == Expose)
		{
			XClearWindow(dpy, w);
			XDrawString(dpy, w, DefaultGC(dpy, s), 10, 50, buf, 1);
		}
		if (event.type == KeyPress)
		{
			if (event.xkey.keycode == 0x18)
			{
				buf[0] = 'q';
				buff_ctr += 7;
				XDrawString(dpy, w, DefaultGC(dpy, s), 10 + buff_ctr, 50, buf, 1);
			}
			else if (event.xkey.keycode == 0x19)
			{
				buf[0] = 'w';
				buff_ctr += 7;
				XDrawString(dpy, w, DefaultGC(dpy, s), 10 + buff_ctr, 50, buf, 1);
			}
			else if (event.xkey.keycode == 0x09)
			{
				break ;
			}
		}
	}
	XCloseDisplay(dpy);
	return (0);
}
