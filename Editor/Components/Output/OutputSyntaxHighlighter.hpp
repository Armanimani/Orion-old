#pragma once

#include <QSyntaxHighlighter>
#include <unordered_map>

namespace orion::editor
{
	class OutputSyntaxHighlighter : public QSyntaxHighlighter
	{
	public:
		explicit OutputSyntaxHighlighter(QObject* parent);
		explicit OutputSyntaxHighlighter(QTextDocument* parent);

		void highlightBlock(const QString& text) override;
	private:
		static std::unordered_map<QString, QColor> token_color_registry;
	};
}
