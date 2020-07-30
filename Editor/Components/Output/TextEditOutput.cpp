#include "Editor/Components/Output/TextEditOutput.hpp"
#include <QtWidgets/QScrollBar>

namespace orion::editor
{
	constexpr auto k_text_block_line_height = 2;
	
	TextEditOutput::TextEditOutput(QWidget* parent)
		: QTextEdit(parent)
	{
		configureTextBlockFormatter();
		configureSyntaxHighlighter();
		
		connect(this, &QTextEdit::textChanged, this, &TextEditOutput::onTextChanged);	
	}

	void TextEditOutput::configureTextBlockFormatter() const noexcept
	{
		auto  block_formatter = this->textCursor().blockFormat();
		block_formatter.setLineHeight(k_text_block_line_height, QTextBlockFormat::LineDistanceHeight);
		this->textCursor().setBlockFormat(block_formatter);
	}

	void TextEditOutput::configureSyntaxHighlighter() noexcept
	{
		syntax_highlighter = std::make_unique<OutputSyntaxHighlighter>(this);
	}

	void TextEditOutput::onTextChanged() const noexcept
	{
		auto* vertical_scroll_bar = static_cast<QScrollBar*>(verticalScrollBar());
		vertical_scroll_bar->setValue(vertical_scroll_bar->maximum());
	}
}
