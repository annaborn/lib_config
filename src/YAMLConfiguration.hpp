#pragma once

#include "Configuration.hpp"
#include <yaml-cpp/yaml.h>
#include <istream>

namespace libConfig
{
class YAMLConfigParser {
    bool parseAndInsert(const std::string& configName, const std::string& ymlString, std::map< std::string, Configuration >& subConfigs);
public:
    void displayMap(const YAML::Node &map, int level = 0);

    void printNode(const YAML::Node &node, int level = 0);

    std::shared_ptr<ConfigValue> getConfigValue(const YAML::Node &node);
    std::shared_ptr<ConfigValue> getConfigValue(const std::string &ymlString);
    std::shared_ptr<ComplexConfigValue> getMap(const YAML::Node &map);

    bool insetMapIntoArray(const YAML::Node &map, ArrayConfigValue &array);
    bool insetMapIntoArray(const YAML::Node &map, ComplexConfigValue &complex);
    bool insetMapIntoArray(const YAML::Node &map, Configuration &conf);
    
    bool loadConfigFile(const std::string &path, std::map<std::string, Configuration> &subConfigs);
    bool loadConfigString(const std::string &yamlstring, std::map<std::string, Configuration> &subConfigs);
    template <typename T>
    bool loadConfig(T& stream, std::map<std::string, Configuration> &subConfigs);
    
    bool parseYAML(Configuration &curConfig, const std::string &yamlBuffer);

    /**
     * This function analyses the given string and replaces variables.
     * The variables in the string taht will be evaluated are given by "<%= ENV('xyz') %>" or
     * "<%= BUNDLES('xyz') %>". In the case of ENV, the given value xyz will be treeted as an
     * environment variable that will be replaced by its current value. BUNDLES specifies that xyz in that case is a
     * relative path (relative with respect to a bundle root). This path will be converted in an absolute path
     * by adding the prefix path of the bundle in which the path was found (starting with the default bundle if specified).
     *
     * @param val Is a const string reference parameter, which contains the original string with the variables.
     * @returns String containing the enhanced string with all replacements.
     */
    static std::string applyStringVariableInsertions(const std::string &val);

    
private:
    

};
}
