#include "mvDocWindow.h"
#include <imgui.h>
#include "mvInterfaceRegistry.h"

namespace Marvel {

	mvDocWindow* mvDocWindow::s_instance = nullptr;

	mvDocWindow* mvDocWindow::GetWindow()
	{
		if (s_instance)
			return s_instance;

		s_instance = new mvDocWindow();
		return s_instance;
	}

	mvDocWindow::mvDocWindow()
	{
		m_sbWidgets = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceCommands("sbWidgets");
		m_sbApp = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceCommands("sbApp");
		m_sbLog = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceCommands("sbLog");
		m_sbInput = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceCommands("sbInput");
		m_sbPlot = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceCommands("sbPlot");
		m_sbDraw = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceCommands("sbDraw");
		m_sbConstants = mvInterfaceRegistry::GetRegistry()->getConstantsCommands();

		m_sbDocWidgets = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceDoc("sbWidgets");
		m_sbDocApp = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceDoc("sbApp");
		m_sbDocLog = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceDoc("sbLog");
		m_sbDocInput = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceDoc("sbInput");
		m_sbDocPlot = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceDoc("sbPlot");
		m_sbDocDraw = mvInterfaceRegistry::GetRegistry()->getPythonInterfaceDoc("sbDraw");
	}

	void mvDocWindow::render(bool& show)
	{
		if (m_mainMode)
		{
			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			ImGui::SetNextWindowSize(ImVec2(m_width, m_height));
			m_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings
				| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
		}

		if (!ImGui::Begin("Documentation", &show, m_flags))
		{
			ImGui::End();
			return;
		}

		ImGui::BeginGroup();
		ImGui::SetNextItemWidth(500);
		ImGui::ListBox("Modules", &m_moduleSelection, &m_modules[0], 7, 7);

		ImGui::SetNextItemWidth(500);
		if (m_moduleSelection == 0)
		{
			static int selection = 0;
			if (ImGui::ListBox("Commands", &selection, m_sbWidgets.data(), m_sbWidgets.size(), 30))
			{
				m_doc = m_sbDocWidgets[selection];
			}
		}

		else if (m_moduleSelection == 1)
		{
			static int selection = 0;
			if (ImGui::ListBox("Commands", &selection, m_sbApp.data(), m_sbApp.size(), 30))
			{
				m_doc = m_sbDocApp[selection];
			}
		}

		else if (m_moduleSelection == 2)
		{
			static int selection = 0;
			if (ImGui::ListBox("Commands", &selection, m_sbLog.data(), m_sbLog.size(), 30))
			{
				m_doc = m_sbDocLog[selection];
			}
		}

		else if (m_moduleSelection == 3)
		{
			static int selection = 0;
			if (ImGui::ListBox("Commands", &selection, m_sbInput.data(), m_sbInput.size(), 30))
			{
				m_doc = m_sbDocInput[selection];
			}
		}

		else if (m_moduleSelection == 4)
		{
			static int selection = 0;
			if (ImGui::ListBox("Commands", &selection, m_sbPlot.data(), m_sbPlot.size(), 30))
			{
				m_doc = m_sbDocPlot[selection];
			}
		}

		else if (m_moduleSelection == 5)
		{
			static int selection = 0;
			if (ImGui::ListBox("Commands", &selection, m_sbDraw.data(), m_sbDraw.size(), 30))
			{
				m_doc = m_sbDocDraw[selection];
			}
		}

		else if (m_moduleSelection == 6)
		{
			static int selection = 0;
			if (ImGui::ListBox("Commands", &selection, m_sbConstants.data(), m_sbConstants.size(), 30))
			{
				m_doc = "A constant.";
			}
		}

		ImGui::EndGroup();

		ImGui::SameLine();
		ImGui::BeginChild("DocChild", ImVec2(500, 600), true);
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 400);
		ImGui::Text(m_doc);
		ImGui::PopTextWrapPos();
		ImGui::EndChild();


		ImGui::End();
	}

}