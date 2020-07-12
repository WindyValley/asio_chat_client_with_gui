#ifndef CHAT_WIN_H_INCLUDED
#define CHAT_WIN_H_INCLUDED
#include "chat_client.hpp"
#include <gtkmm.h>
using namespace Gtk;

extern char line[];

class ChatWin : public Window
{
public:
  Button snd_button;
  Entry snd_msg;
  TextView recv_msgs;
  Fixed fixed;
  ScrolledWindow scroll;
  Glib::RefPtr<TextBuffer> buffer;

public:
  ChatWin(char *title);
  ~ChatWin();
  void initwindow(char *title);
  void initcontrol();
  void initlayout();
};
#endif