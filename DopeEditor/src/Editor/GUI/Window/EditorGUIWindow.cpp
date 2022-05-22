#include "EditorGUIWindow.h"

namespace DopeEditor
{
    bool EditorGUIWindow::is_visible() const
    {
        return false;
    }

    bool EditorGUIWindow::is_collapsed() const
    {
        return false;
    }

    void EditorGUIWindow::_set_visiblity(const bool state)
    {
        Visible = state;
    }

    void EditorGUIWindow::_set_collapsed(const bool state)
    {
        Collapsed = state;
    }


}