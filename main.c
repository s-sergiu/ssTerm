#include <X11/Xlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	XEvent event;
	Display *dpy;	
	Window w;
	int s;
	int buff_ctr;
	int buff_width;
	KeySym key;

	dpy = XOpenDisplay(NULL);
	s = DefaultScreen(dpy);
	w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 10, 10, 100, 100, 1, BlackPixel(dpy, s), WhitePixel(dpy, s));
	XSelectInput(dpy, w, ExposureMask | KeyPressMask);
	XMapWindow(dpy, w);
	buff_ctr = 0;
	buff_width = 50;
	while (1)
	{
		XNextEvent(dpy, &event);
		if (event.type == Expose)
			XClearWindow(dpy, w);
		if (event.type == KeyPress)
		{
			if (event.xkey.keycode == 36)
			{
				XClearArea(dpy, w, buff_ctr + 17, buff_width + 2, 15, 5, 0);
				buff_width += 13;
				buff_ctr = 0;
			}
			else
			{
				printf("Key detail: %d\n", event.xkey.keycode);
				buff_ctr += 7;
				key = XKeycodeToKeysym(dpy, event.xkey.keycode, 0);
				XDrawString(dpy, w, DefaultGC(dpy, s), 10 + buff_ctr, buff_width, XKeysymToString(key), 1);
			}
			if (event.xkey.keycode == 9)
				break ;
			XClearArea(dpy, w, buff_ctr, buff_width + 2, 15, 5, 0);
		//	XFillRectangle(dpy, w, DefaultGC(dpy, s), buff_ctr + 18, buff_width, 3, 1);
			XDrawLine(dpy, w, DefaultGC(dpy, s), buff_ctr + 17, buff_width + 2, buff_ctr + 20, buff_width + 2);
		}
	}
	XCloseDisplay(dpy);
	return (0);
}
