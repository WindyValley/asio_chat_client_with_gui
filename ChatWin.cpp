#include "ChatWin.h"

char line[chat_message::max_body_length] = "";

ChatWin::ChatWin(char *title)
{
  initwindow(title);
  initcontrol();
  initlayout();
}

ChatWin::~ChatWin() {}

void ChatWin::initwindow(char *title)
{
  set_title(title);
  set_position(WIN_POS_CENTER);
  set_default_size(600, 400);
  set_border_width(10);
}

void ChatWin::initcontrol()
{
  // buttons
  snd_button.set_label("发送");
  // entrys
  snd_msg.set_max_length(512);
  // textviews
  buffer = recv_msgs.get_buffer();
}

void ChatWin::initlayout()
{
  //{{{fixed start
  // entry
  fixed.put(snd_msg, 0, 0);
  snd_msg.set_size_request(530, 40);
  // button
  fixed.put(snd_button, 540, 0);
  snd_button.set_size_request(70, 40);
  //{{{scroll start
  // recv_msgs
  recv_msgs.set_size_request(610, 355);
  recv_msgs.set_editable(FALSE);
  scroll.add(recv_msgs);
  scroll.set_size_request(610, 355);
  // scroll end}}}
  fixed.put(scroll, 0, 45);
  this->add(fixed);
  // fixed end}}}
}
