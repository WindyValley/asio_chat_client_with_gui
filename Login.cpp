#include "Login.h"

Login::Login()
{
  initdialog((char *)"登录");
  initcontrol();
  initlayout();
}

Login::~Login()
{
  delete label1;
  delete label2;
  delete iptext;
  delete porttext;
  delete fixed;
}

void Login::initdialog(char *title)
{
  set_default_size(240, 160);
  set_title(title);
  set_position(WIN_POS_CENTER);
}

void Login::initcontrol()
{
  //按钮
  add_button("连接", RESPONSE_APPLY);
  add_button("取消", RESPONSE_CANCEL);
  //标签
  label1 = new Label("IP:");
  label2 = new Label("Port:");
  //输入框
  iptext = new Entry;
  iptext->set_placeholder_text("server's ip");
  porttext = new Entry();
  porttext->set_placeholder_text("server's port");
}

void Login::initlayout()
{
  //{{{fixed start
  fixed = new Fixed;
  // ip
  fixed->put(*label1, 0, 0);
  label1->set_size_request(80, 40);
  fixed->put(*iptext, 80, 0);
  iptext->set_size_request(160, 40);
  // port
  fixed->put(*label2, 0, 50);
  label2->set_size_request(80, 40);
  fixed->put(*porttext, 80, 50);
  porttext->set_size_request(160, 40);
  // fixed end}}}
  this->get_vbox()->add(*fixed);
}
