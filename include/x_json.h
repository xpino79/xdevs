// https://www.itread01.com/content/1543368860.html

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

const std::string file_path = "json.txt";
 
void _My_write_json_data_into_string()
{
    boost::property_tree::ptree item;
    item.put("a","2");
    std::stringstream is;
    boost::property_tree::write_json(is,item);
    std::string s = is.str();
    cout<<"json s:"<<s<<endl;
}
void _My_read_json_data_from_string()
{
    std::string json_str = "{\"count\":10,\"people\":[{ \"firstName\": \"Brett\", \"lastName\":\"McLaughlin\", \"email\": \"aaaa\" },{ \"firstName\": \"Jason\", \"lastName\":\"Hunter\", \"email\": \"bbbb\"},{ \"firstName\": \"Elliotte\", \"lastName\":\"Harold\", \"email\": \"cccc\" }]}";
    std::stringstream stream(json_str);
 
    boost::property_tree::ptree props;
    boost::property_tree::read_json(stream, props);
 
    std::cout << "count" << ":" << props.get<std::string>("count") << std::endl;
    auto it = props.get_child("people");
    for (auto &kv : it)
    {
        auto field = kv.second;
        for (auto &v : field)
        {
            std::cout << v.first << ":" << field.get<std::string>(v.first) << std::endl;
        }
    }
}
