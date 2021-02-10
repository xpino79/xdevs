#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

const std::string file_path = "json.txt";

void _My_write_json_data()
{
    boost::property_tree::ptree root, items;
    boost::property_tree::ptree item1;
    item1.put("ID","1");
    item1.put("Name","wang");
    items.push_back(std::make_pair("1",item1));
 
    boost::property_tree::ptree item2;
    item2.put("ID","2");
    item2.put("Name","zhang");
    items.push_back(std::make_pair("2",item2));
 
    root.put_child("users",items);
    boost::property_tree::write_json(file_path,root);
}
void _My_read_json_data()
{
    boost::property_tree::ptree root;
    boost::property_tree::ptree items;
    boost::property_tree::read_json<boost::property_tree::ptree>(file_path,root);
 
    items = root.get_child("users");
    for(boost::property_tree::ptree::iterator it=items.begin(); it != items.end(); ++it)
    {
        std::string key=it->first;//key ID
        std::string ID=it->second.get<string>("ID");
        std::string Name=it->second.get<string>("Name");
        std::cout<<"key: "<<key.c_str()<<'\t';
        printf("ID: %s    Name: %s",ID.c_str(), Name.c_str());
        std::cout<<std::endl;
        std::cout<<"ID:"<<ID<<'\t'<<"Name:"<<Name<<std::endl;
    }
}
