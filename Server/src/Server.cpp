#include <stdafx.h>
#include "Server.h"


#include <Poco/SQL/PostgreSQL/Connector.h>



int main()
{
    Poco::SQL::PostgreSQL::Connector::registerConnector();

    return 0L;
}