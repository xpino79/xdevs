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
    boost::property_tree::ptree root;
    boost::property_tree::read_json(stream, root);
 
    std::cout << "count" << ":" << root.get<std::string>("count") << std::endl;
    auto ptree = root.get_child("people");
    for (auto elem : ptree)
    {
        auto inner = elem.second;
        for (auto inner_elem : inner)
        {
            std::cout << inner_elem.first << ":" << inner.get<std::string>(inner_elem.first) << std::endl;
        }
    }
}
