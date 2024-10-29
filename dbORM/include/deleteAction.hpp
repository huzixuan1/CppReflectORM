#ifndef DELETE_HPP
#define DELETE_HPP


#include <string>
#include <sstream>
#include <boost/type_index.hpp>
namespace deleteAction
{
    class Condition
    {

        private:    
            std::string L;
            std::string op;     // eg =,>,<...
            std::string R;

        public:
            Condition(const std::string& L,const std::string& op,const std::string& R)
            :L(L),op(op),R(R){}

            std::string to_sql() const
            {
                std::ostringstream sql;
                sql << L<<" "<<op<<" '"<<R<<"'";
                return sql.str();
            }
    };


    template<typename T>
    std::string get_table_name()
    {
        return boost::typeindex::type_id<T>().pretty_name();
    }

    template<typename T>
    std::string remove(int id)
    {
        std::ostringstream sql;
        sql<<"DELETE FROM "<<get_table_name<T>()<<" WHERE id = "<<id<<";";
        return sql.str();
    }


    template<typename T>
    std::string remove_if(const Condition& condition)
    {
        std::ostringstream sql;
        sql<<"DELETE FROM "<<get_table_name<T>()<<" WHERE "<<condition.to_sql()<<";";
        return sql.str();
    }

};




#endif  // DELETE_HPP