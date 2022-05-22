#include "EditorGUIModule.h"


namespace DopeEditor
{
    EditorSession* EditorGUIModule::get_owner_session() const
    {
        return OwnerSession;
    }

    void EditorGUIModule::_set_owner_session(EditorSession* ownerSession)
    {
        OwnerSession = ownerSession;
    }

}