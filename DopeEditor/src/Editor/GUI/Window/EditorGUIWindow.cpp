#include "EditorGUIWindow.h"

namespace DopeEditor
{
    EditorGUIWindow::EditorGUIWindow()
    {
        Collapsed = false;
    }


    bool EditorGUIWindow::is_collapsed() const
    {
        return Collapsed;
    }


    void EditorGUIWindow::_set_collapsed(const bool state)
    {
        Collapsed = state;
    }


}