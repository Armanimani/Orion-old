#pragma once

#include <QtWidgets/QTextEdit>

#include "Editor/Components/Output/OutputSyntaxHighlighter.hpp"

namespace orion::editor
{
	class TextEditOutput final : public QTextEdit
	{
		Q_OBJECT
	public:
		TextEditOutput(QWidget* parent);
	private:
		std::unique_ptr<OutputSyntaxHighlighter> syntax_highlighter {};
		void configureTextBlockFormatter() const noexcept;
		void configureSyntaxHighlighter() noexcept;
	private slots:
		void onTextChanged() const noexcept;
	};
}
