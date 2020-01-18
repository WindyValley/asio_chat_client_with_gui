#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include <gtkmm.h>
using namespace Gtk;

class Login:public Dialog
{
public:
    Login();
    ~Login();
	void initdialog(char* title);
	void initcontrol();
	void initlayout();
public:
    Label *label1,*label2;
    Entry *iptext, *porttext;
    Fixed *fixed;
};
#endif // LOGIN_H_INCLUDED
