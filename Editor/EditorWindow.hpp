#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditorWindow.h"

namespace orion::editor
{
	class EditorWindow final : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit EditorWindow(QWidget* parent = Q_NULLPTR);
	private:
		Ui::EditorWindowClass ui{};
	};
}
