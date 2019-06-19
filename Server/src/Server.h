#ifndef __SERVER_H__
#define __SERVER_H__

#include <Poco/Util/ServerApplication.h>

class WorkstationServerApp: public Poco::Util::ServerApplication
{
public:
	WorkstationServerApp();	
	virtual ~WorkstationServerApp();

protected:
	void initialize(Poco::Util::Application& self) override;		
	void uninitialize() override;
	void defineOptions(Poco::Util::OptionSet& options) override;
	void handleOption(const std::string& name, const std::string& value) override;

	int main(const std::vector<std::string>& args) override;

};



#endif