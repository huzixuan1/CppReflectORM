#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <vector>
#include "./converter.hpp"
#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <boost/core/type_name.hpp>
#include <boost/type_index.hpp>
namespace utility
{

/**
 * @brief Get struct name with auto.
 * 
 * @param T:The type of the c++ struct
 * @return get_table_name(user) and user is struct or struct object.
 */
    template <typename T>
    std::string get_table_name()
    {
        return boost::typeindex::type_id<T>().pretty_name();
    }

    /**
     * @brief Retrieves the field names and SQL types of a C++ struct.
     *
     * @tparam T The type of the C++ struct.
     * @param struct_t An instance of the struct.
     * @return A vector of pairs where each pair contains the field name and its corresponding SQL type.
     */

    template <typename T>
    std::vector<std::pair<std::string, std::string>> getStructFieldsInfo(const T &struct_t)
    {
        std::vector<std::pair<std::string, std::string>> fieldsInfo;
        constexpr auto names = boost::pfr::names_as_array<T>();
        boost::pfr::for_each_field(
            struct_t, [&fieldsInfo, &names](const auto &field, std::size_t idx)
            {
            using fileType = std::decay_t<decltype(field)>;
            std::string fieldName = std::string(names[idx]);
            std::string typeName = converter::TypeConverter<fileType>::converter();
            fieldsInfo.emplace_back(fieldName, typeName); });

        return fieldsInfo;
    }

};

#endif // UTILITY_HPP
