#include "ChatWin.h"
#include "Login.h"

void cb_button();
void cb_cnbutton();
bool exit_(GdkEventAny *);

chat_client *client = nullptr;
ChatWin *win;
Login *login;
io_context ioc;
tcp::resolver rs(ioc);
bool ipgetted = false;
Glib::RefPtr<Application> app;

int main(int argc, char **argv)
{
  app = Application::create(argc, argv);
  win = new ChatWin((char *)"chat");
  login = new Login();
  std::thread loop([]() {
  login->show_all();
  do
  {
    if (login->run() == RESPONSE_APPLY)
      cb_cnbutton();
    else
        return;
  } while (!ipgetted);
  login->close();
  win->show_all();
  app->run(*win);
  });
  win->signal_delete_event().connect(sigc::ptr_fun(exit_));
  win->snd_button.signal_clicked().connect(sigc::ptr_fun(cb_button));
  loop.join();
  return 0;
}

void cb_cnbutton()
{
  auto endpoint =
      rs.resolve(login->iptext->get_text(), login->porttext->get_text());
  if (client == nullptr)
    client = new chat_client(ioc, endpoint);
  else
    client->do_connect(endpoint);
  ioc.run_one();
  while (!client->tried_connect)
    ;
  ioc.restart();
  client->tried_connect = false;
  if (client->connect_result)
    return;
  ipgetted = true;
  std::thread t([]() { ioc.run(); });
  t.detach();
}

void cb_button()
{
  auto&& line = win->snd_msg.get_text();
  if (line.empty())
    return;
  chat_message msg;
  msg.body_length(line.length());
  std::memcpy(msg.body(), line.c_str(), msg.body_length());
  msg.encode_header();
  client->write(msg);
}

void handler(boost::system::error_code ec, std::size_t length)
{
  if (!ec)
  {
    TextBuffer::iterator start, end;
    win->buffer->get_bounds(start, end);
    win->buffer->insert(end, Glib::ustring(client->read_msg_.body(),
                                           client->read_msg_.body_length()));
    win->buffer->get_bounds(start, end);
    win->buffer->insert(end, "\n");
    client->do_read_header();
  }
  else
  {
    client->close();
  }
}

bool exit_(GdkEventAny *event)
{
  client->close();
  win->close();
  app->quit();
  return ipgetted;
}
