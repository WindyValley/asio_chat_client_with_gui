//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;
using namespace boost::asio;

typedef std::deque<chat_message> chat_message_queue;

void handler(boost::system::error_code ec, std::size_t length);

class chat_client
{
public:
	chat_client(io_context& io_context,
		const tcp::resolver::results_type& endpoints)
		: io_context_(io_context),
		socket_(io_context),
		tried_connect(false)
	{
		do_connect(endpoints);
	}

	void write(const chat_message& msg)
	{
		post(io_context_,
			[this, msg]()
		{
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress)
			{
				do_write();
			}
		});
	}

	void close()
	{
		post(io_context_, [this]() { socket_.close(); });
	}

	void do_connect(const tcp::resolver::results_type& endpoints)
	{
		async_connect(socket_, endpoints,
			[this](boost::system::error_code ec, tcp::endpoint)
		{
			connect_result=ec;
			tried_connect=true;
			if (!ec)
			{
				do_read_header();
			}
		});
	}

	void do_read_header()
	{
		async_read(socket_,
			buffer(read_msg_.data(), chat_message::header_length),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg_.decode_header())
			{
				do_read_body();
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_read_body()
	{
		async_read(socket_,
			buffer(read_msg_.body(), read_msg_.body_length()), &handler);
	}

	void do_write()
	{
		async_write(socket_,
			buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				socket_.close();
			}
		});
	}

public:
	io_context& io_context_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
	boost::system::error_code connect_result;
	bool tried_connect;
};

