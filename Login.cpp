#include "Login.h"

char *_(const char *c) { return g_locale_to_utf8(c, -1, NULL, NULL, NULL); }

Login::Login()
{
  initdialog((char *)"登录");
  initcontrol();
  initlayout();
}

Login::~Login()
{
  delete dialog;
  delete iptext;
  delete porttext;
  delete cnbutton;
  delete fixed;
}

void Login::initdialog(char *title)
{
  dialog = gtk_dialog_new();
  gtk_window_set_default_size(GTK_WINDOW(dialog), 240, 160);
  gtk_window_set_title(GTK_WINDOW(dialog), title);
  gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
}

void Login::initcontrol()
{
  //按钮
  cnbutton = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(cnbutton), "连接");
  ccbutton = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(ccbutton), "取消");
  //标签
  label1 = gtk_label_new("IP:");
  label2 = gtk_label_new("Port:");

  //输入框
  iptext = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(iptext), "server's ip");
  porttext = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(iptext), "server's port");
}

void Login::initlayout()
{
  //{{{fixed start
  fixed = gtk_fixed_new();
  // ip
  gtk_fixed_put(GTK_FIXED(fixed), label1, 0, 0);
  gtk_widget_set_size_request(label1, 80, 40);
  gtk_fixed_put(GTK_FIXED(fixed), iptext, 80, 0);
  gtk_widget_set_size_request(iptext, 160, 40);
  // port
  gtk_fixed_put(GTK_FIXED(fixed), label2, 0, 50);
  gtk_widget_set_size_request(label2, 80, 40);
  gtk_fixed_put(GTK_FIXED(fixed), porttext, 80, 50);
  gtk_widget_set_size_request(porttext, 160, 40);
  // cnbutton
  gtk_fixed_put(GTK_FIXED(fixed), cnbutton, 30, 100);
  gtk_widget_set_size_request(cnbutton, 75, 40);
  // ccbutton
  gtk_fixed_put(GTK_FIXED(fixed), ccbutton, 135, 100);
  gtk_widget_set_size_request(ccbutton, 75, 40);
  // fixed end}}}
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
                     fixed, false, true, 0);
}

void Login::show() { gtk_widget_show_all(dialog); }

void Login::destroy() { gtk_widget_destroy(dialog); }
