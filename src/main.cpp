#include <drogon/drogon.h>
#include "repositories/setting/setting_repository.h"

int main()
{
    SettingRepository::initializeDefaults();

    drogon::app()
        .addListener("0.0.0.0", 8080)
        .run();

    return 0;
}
