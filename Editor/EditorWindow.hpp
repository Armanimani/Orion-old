#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditorWindow.h"

#include "Editor/Components/Output/StreamOutputPipe.hpp"

namespace orion::editor
{
	class EditorWindow final : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit EditorWindow(QWidget* parent = Q_NULLPTR);
	protected:
		void showEvent(QShowEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private:
		Ui::EditorWindowClass ui{};

		std::unique_ptr<StreamOutputPipe> output_pipe {};

		void initialize();
		void initializeStreamOutputPipe() noexcept;

		void connectActionsToSlots() const noexcept;
	};
}
