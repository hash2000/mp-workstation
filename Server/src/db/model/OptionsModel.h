#ifndef __OPTIONSMODEL_H__
#define __OPTIONSMODEL_H__

#include "ModelWrapper.h"
#include <string>


class OptionsModel : public ModelWrapper
{
public:
    virtual ~OptionsModel() {
    }

    bool Set(const std::string & name, const std::string & value);
    bool Setup(const std::string & name, const std::string & value);
    std::string GetString(const std::string & name) const;
    bool GetBoolean(const std::string & name) const;
    int GetInteger(const std::string & name, int defaultValue = 0) const;
    double GetDouble(const std::string & name, double defaultValue = 0.) const;
};

#endif // !__OPTIONSMODEL_H__