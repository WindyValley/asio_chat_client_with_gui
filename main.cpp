#include "Window.h"
#include "Login.h"

void cb_button(GtkWidget* widget, gpointer entry);
void cb_cnbutton(GtkWidget* widget,gpointer win);
void close();
void exit();

chat_client* client=nullptr;
Window* win;
Login *login;
io_context ioc;
tcp::resolver rs(ioc);
bool ipgetted=false;

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	win = new Window((char*)"chat");
	login = new Login();
	std::thread loop([]() {
		login->show();
		gtk_main();
	});
	g_signal_connect(G_OBJECT(win->window), "delete_event", G_CALLBACK(close), NULL);
	g_signal_connect(G_OBJECT(login->dialog), "delete_event", G_CALLBACK(exit), NULL);
	g_signal_connect(G_OBJECT(win->snd_button), "clicked", G_CALLBACK(cb_button), win->snd_msg);
	g_signal_connect(G_OBJECT(login->cnbutton), "clicked", G_CALLBACK(cb_cnbutton),NULL);
	g_signal_connect(G_OBJECT(login->ccbutton), "clicked", G_CALLBACK(exit), NULL);
	loop.join();
	return 0;
}

void cb_cnbutton(GtkWidget *widget, gpointer data)
{
	GtkEntry *ip=GTK_ENTRY(login->iptext);
	GtkEntry *port=GTK_ENTRY(login->porttext);
	auto endpoint = rs.resolve(gtk_entry_get_text(ip), gtk_entry_get_text(port));
	client = new chat_client(ioc, endpoint);
	ipgetted=true;
	login->destroy();
	win->show();
	std::thread t([]() {
		ioc.run();
	});
	t.detach();
}

void cb_button(GtkWidget* widget, gpointer entry)
{
	const char* line = gtk_entry_get_text(GTK_ENTRY(entry));
	chat_message msg;
	msg.body_length(std::strlen(line));
	std::memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
}

void close()
{
	client->close();
	gtk_main_quit();
}

void exit()
{
	if(!ipgetted)
		gtk_main_quit();
}

void handler(boost::system::error_code ec, std::size_t length)
{
	if (!ec)
	{
		GtkTextIter start, end;
		gtk_text_buffer_get_bounds(win->buffer, &start, &end);
		gtk_text_buffer_insert(win->buffer, &end, client->read_msg_.body(), client->read_msg_.body_length());
		gtk_text_buffer_insert(win->buffer, &end, "\n", 1);
		client->do_read_header();
	}
	else
	{
		close();
	}
}
