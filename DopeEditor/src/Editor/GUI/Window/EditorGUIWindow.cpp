#include "EditorGUIWindow.h"

namespace DopeEditor
{
    EditorGUIWindow::EditorGUIWindow()
    {
        Collapsed = false;
        FirstDraw = true;
    }

    bool EditorGUIWindow::is_collapsed() const
    {
        return Collapsed;
    }

    DopeEngine::Vector2f EditorGUIWindow::get_position() const
    {
        return Position;
    }

    DopeEngine::Vector2f EditorGUIWindow::get_size() const
    {
        return Size;
    }

    bool EditorGUIWindow::is_first_draw() const
    {
        return FirstDraw;
    }

    EditorSession* EditorGUIWindow::get_owner_session() const
    {
        return OwnerSession;
    }

    void EditorGUIWindow::_set_collapsed(const bool state)
    {
        Collapsed = state;
    }

    void EditorGUIWindow::_set_position(const DopeEngine::Vector2f& position)
    {
        Position = position;
    }

    void EditorGUIWindow::_set_size(const DopeEngine::Vector2f& size)
    {
        Size = size;
    }

    void EditorGUIWindow::_mark_first_draw()
    {
        FirstDraw = false;
    }

    void EditorGUIWindow::_set_owner_session(EditorSession* ownerSession)
    {
        OwnerSession = ownerSession;
    }
}