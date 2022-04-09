#include "ApplicationModule.h"

namespace DopeEngine
{
    ApplicationSession* ApplicationModule::get_owner_session() const
    {
        return OwnerSession;
    }
    void ApplicationModule::_set_owner_session(ApplicationSession* session)
    {
        OwnerSession = session;
    }
}