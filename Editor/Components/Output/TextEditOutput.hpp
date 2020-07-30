#pragma once

#include <QtWidgets/QTextEdit>

namespace orion::editor
{
	class TextEditOutput final : public QTextEdit
	{
		Q_OBJECT
	public:
		TextEditOutput(QWidget* parent);
	};
}
