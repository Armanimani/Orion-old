#pragma once

#include <ostream>
#include <QtWidgets/QTextEdit>

namespace orion::editor
{
	class StreamOutputPipe final : public std::basic_streambuf<char>
	{
	public:
		StreamOutputPipe(std::ostream& stream, QTextEdit* text_edit);
		~StreamOutputPipe();

		StreamOutputPipe(const StreamOutputPipe& other) = delete;
		StreamOutputPipe(StreamOutputPipe&& other) noexcept = delete;
		StreamOutputPipe& operator=(const StreamOutputPipe& other) = delete;
		StreamOutputPipe& operator=(StreamOutputPipe&& other) noexcept = delete;
	protected:
		int_type overflow(int_type v) override;

		// ReSharper disable once IdentifierTypo
		std::streamsize xsputn(const char* data, std::streamsize size) override;
	private:
		std::ostream& stream;
		std::streambuf* old_buffer;
		std::string string;

		QTextEdit* text_edit_widget;
	};
}