#include "chat_client.hpp"
#include <gtk/gtk.h>

extern char line[];

class Window
{
public:
  GtkWidget *window;
  GtkWidget *snd_button, *snd_msg, *recv_msgs;
  GtkWidget *fixed;
  GtkWidget *scroll;
  GtkTextBuffer *buffer;

public:
  Window(char *title);
  ~Window();
  void show();
  void initwindow(char *title);
  void initcontrol();
  void initlayout();
};