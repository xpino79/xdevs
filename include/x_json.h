// https://www.itread01.com/content/1543368860.html

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

const std::string file_path = "json.txt";
 
void _My_write_json_data_into_string()
{

    boost::property_tree::ptree pt;
    boost::property_tree::ptree children;
    boost::property_tree::ptree child1, child2, child3;

    // { \"firstName\": \"Brett\", \"lastName\":\"McLaughlin\", \"email\": \"aaaa\" }
    child1.put("firstName", "Brett");
    child1.put("lastName", "McLaughlin");
    child1.put("email", "aaaa");
    // { \"firstName\": \"Jason\", \"lastName\":\"Hunter\", \"email\": \"bbbb\"}
    child2.put("firstName", "Jason");
    child2.put("lastName", "Hunter");
    child2.put("email", "bbbb");
    // { \"firstName\": \"Elliotte\", \"lastName\":\"Harold\", \"email\": \"cccc\" }
    child3.put("firstName", "Elliotte");
    child3.put("lastName", "Harold");
    child3.put("email", "cccc");

    children.push_back(std::make_pair("", child1));
    children.push_back(std::make_pair("", child2));
    children.push_back(std::make_pair("", child3));

    pt.put("count", "10");
    pt.add_child("people", children);

    std::stringstream is;
    boost::property_tree::write_json(is, pt);
    std::cout << is.str() << std::endl; 
 
}
void _My_read_json_data_from_string()
{
    std::string json_str = "{\"count\":10,\"people\":[{ \"firstName\": \"Brett\", \"lastName\":\"McLaughlin\", \"email\": \"aaaa\" },{ \"firstName\": \"Jason\", \"lastName\":\"Hunter\", \"email\": \"bbbb\"},{ \"firstName\": \"Elliotte\", \"lastName\":\"Harold\", \"email\": \"cccc\" }]}";
    std::stringstream stream(json_str);
 
    boost::property_tree::ptree props;
    boost::property_tree::read_json(stream, props);
 
    std::cout << "count" << ":" << props.get<std::string>("count") << std::endl;
    auto c = props.get_child("people");
    for (auto &kv : c)
    {
        // kv is of type ptree::value_type
        // kv.first is the name of the child
        // kv.second is the child tree
        auto ct = kv.second;
        for (auto &v : ct)
        {
            std::cout << v.first << ":" << ct.get<std::string>(v.first) << std::endl;
        }
    }
    /*
 	  const auto &node = json.get_child("people", boost::property_tree::ptree{});
	   std::cout << node.size() << " " << (node.begin() == node.end()) << std::endl;

	   for (const auto &[k, v] : node) {
		    std::cout << k << " " << v << std::endl;
    }
    */
}
