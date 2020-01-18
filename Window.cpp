#include "Window.h"

char line[chat_message::max_body_length] = "";


Window::Window(char* title)
{
	initwindow(title);
	initcontrol();
	initlayout();
}

Window::~Window()
{
	delete window;
	delete snd_button;
	delete snd_msg;
	delete recv_msgs;
	delete fixed;
	delete buffer;
}

void Window::initwindow(char* title)
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
}

void Window::initcontrol()
{
	//buttons
	snd_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(snd_button),"发送");
	//entrys
	snd_msg = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(snd_msg), 512);
	//textviews
	recv_msgs = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(recv_msgs));
}

void Window::initlayout()
{
	//{{{fixed start
	fixed = gtk_fixed_new();
	//entry
	gtk_fixed_put(GTK_FIXED(fixed), snd_msg, 0, 0);
	gtk_widget_set_size_request(snd_msg, 530, 40);
	//button
	gtk_fixed_put(GTK_FIXED(fixed), snd_button, 540, 0);
	gtk_widget_set_size_request(snd_button, 70, 40);
	//recv_msgs
	gtk_fixed_put(GTK_FIXED(fixed), recv_msgs, 0, 45);
	gtk_widget_set_size_request(recv_msgs, 610, 355);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(recv_msgs), FALSE);
	//fixed end}}}
	gtk_container_add(GTK_CONTAINER(window), fixed);
}
void Window::show()
{
	gtk_widget_show_all(window);
}
