#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include <gtk/gtk.h>

char* _(char* c);

class Login
{
public:
    Login();
    ~Login();
    void show();
    void destroy();
	void initdialog(char* title);
	void initcontrol();
	void initlayout();
public:
    GtkWidget *dialog;
    GtkWidget *label1,*label2;
    GtkWidget *iptext, *porttext;
    GtkWidget *cnbutton, *ccbutton;
    GtkWidget *fixed;
};
#endif // LOGIN_H_INCLUDED
