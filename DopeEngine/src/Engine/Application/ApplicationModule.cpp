#include "ApplicationModule.h"

namespace DopeEngine
{
    GameSession* ApplicationModule::get_owner_session() const
    {
        return OwnerSession;
    }
    void ApplicationModule::_set_owner_session(GameSession* session)
    {
        OwnerSession = session;
    }
}