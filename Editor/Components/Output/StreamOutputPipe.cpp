#include "Editor/Components/Output/StreamOutputPipe.hpp"

namespace orion::editor
{
	StreamOutputPipe::StreamOutputPipe(std::ostream& stream, QTextEdit* text_edit)
		: stream(stream)
	{
		text_edit_widget = text_edit;
		old_buffer = stream.rdbuf();
		stream.rdbuf(this);
	}

	StreamOutputPipe::~StreamOutputPipe()
	{
		if (!string.empty())
			text_edit_widget->append(string.c_str());

		stream.rdbuf(old_buffer);
	}

	std::basic_streambuf<char>::int_type StreamOutputPipe::overflow(int_type v)
	{
		if (v == '\n')
		{
			text_edit_widget->append(string.c_str());
			string.erase(string.begin(), string.end());
		}
		else
			string += v;

		return v;
	}

	std::streamsize StreamOutputPipe::xsputn(const char* p, std::streamsize n)
	{
		string.append(p, p + n);

		auto pos = 0;
		while (pos != std::string::npos)
		{
			pos = string.find('\n');
			if (pos != std::string::npos)
			{
				std::string tmp(string.begin(), string.begin() + pos);
				text_edit_widget->append(tmp.c_str());
				string.erase(string.begin(), string.begin() + pos + 1);
			}
		}

		return n;
	}
}
