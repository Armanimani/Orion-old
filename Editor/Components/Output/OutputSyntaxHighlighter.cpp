#include "Editor/Components/Output/OutputSyntaxHighlighter.hpp"

namespace orion::editor
{
	const QString k_error_token = "ERROR:";
	const QString k_warning_token = "WARNING:";
	const QString k_information_token = "INFORMATION";
	const QString k_debug_token = "DEBUG";

	std::unordered_map<QString, QColor> OutputSyntaxHighlighter::token_color_registry
	{
		{k_error_token, QColor(207, 27, 27)},
		{k_warning_token, QColor(255, 215, 0)},
		{k_information_token, QColor(50, 130, 184)},
		{k_debug_token, QColor(150, 187, 124)}
	};
	
	OutputSyntaxHighlighter::OutputSyntaxHighlighter(QObject* parent)
		: QSyntaxHighlighter(parent) {}
	
	OutputSyntaxHighlighter::OutputSyntaxHighlighter(QTextDocument* parent)
		: QSyntaxHighlighter(parent) {}

	void OutputSyntaxHighlighter::highlightBlock(const QString& text)
	{
		for (const auto& token_color_pair: token_color_registry)
		{
			const auto& [token, color] = token_color_pair;
			const auto index = text.indexOf(token);
			if (index != -1)
			{
				setFormat(index, text.length(), color);
				return;
			}
		}
	}
}
