#include <iostream>
#include <fstream>
#include "main_include.hpp"

#include <yaml-cpp/yaml.h>
#include <assert.h>

using namespace std;
using namespace YAML;

void emit_demo(void) {
	YAML::Emitter out;

	out << 1;
	out << 1.1;
	out << "1.1";
	out << true;

	out << YAML::BeginSeq;
	out << YAML::Comment("This is a comment!");
	out << "eggs";
	out << "milk";
	out << "fruit" << YAML::BeginSeq << "apple" << "banana" << YAML::EndSeq;
	out << YAML::EndSeq;

	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << "Barack Obama";
	out << YAML::Key << "children";
	out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
	out << YAML::Key << "fruit" ;
		out << YAML::BeginMap;
		out << YAML::Key << "apple";
		out << YAML::Value << "10kg";
		out << YAML::Key << "banana";
		out << YAML::Value << "20kg";
		out << YAML::EndMap;
	out << YAML::EndMap;

	out << YAML::Literal << "A\n B\n  C";
	out << YAML::Flow;
	out << YAML::BeginSeq << 2 << 3 << 5 << 7 << 11 << YAML::EndSeq;

	std::vector <int> squares;
	squares.push_back(1);
	squares.push_back(4);
	squares.push_back(9);
	squares.push_back(16);
	std::map <std::string, int> ages;
	ages["Daniel"] = 26;
	ages["Jesse"] = 24;
	out << YAML::BeginSeq;
	out << YAML::Flow << squares << ages;
	out << YAML::EndSeq;

	out << YAML::BeginSeq;
	out << YAML::Anchor("fred");
	out << YAML::BeginMap;
	out << YAML::Key << "name" << YAML::Value << "Fred";
	out << YAML::Key << "age" << YAML::Value << "42";
	out << YAML::EndMap;
	out << YAML::Alias("fred");
	out << YAML::EndSeq;

//	cout << out.c_str() <<endl;

	ofstream fout;
	fout.open("src/output.yaml");

	if (!fout.is_open()) {
		cerr << "Could not open " << endl;
		fout.clear();
	}

	fout << out.c_str() <<endl;
	fout.close();

}

void parse_demo1(void) {
	YAML::Node node = YAML::Load("[1, 2, 3]");
	assert(node.Type() == YAML::NodeType::Sequence);
	assert(node.IsSequence());  // a shortcut
}

void parse_demo2(void) {
	YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
//	for (std::size_t i=0;i<primes.size();i++) {
//		std::cout << primes[i].as<int>() << "\n";
//	}
// or:
	for (YAML::const_iterator it=primes.begin();it!=primes.end();++it) {
		std::cout << it->as<int>() << "\n";
	}
	cout << "size:\t" << primes.size() <<endl;
	primes.push_back(13);
	cout << "size:\t" << primes.size() <<endl;

}

void parse_demo3(void) {
	YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun}");
	for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
		std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() << "\n";
	}
	cout << "size:\t" << lineup.size() <<endl;
	lineup["RF"] = "Corey Hart";
	lineup["C"] = "Jonathan Lucroy";
	cout << "size:\t" << lineup.size() <<endl;
}

void parse_demo4(void) {
	YAML::Node node = YAML::Load("{name: Brewers, city: Milwaukee}");
	if (node["name"]) {
		std::cout << node["name"].as<std::string>() << "\n";
	}
	if (node["mascot"]) {
		std::cout << node["mascot"].as<std::string>() << "\n";
	}
	if (node["city"]) {
		std::cout << node["city"].as<std::string>() << "\n";
	}
	cout << "size:\t" << node.size() <<endl;
}

void parse_demo5(void) {
	YAML::Node node;  // starts out as null
	node["key"] = "value";  // it now is a map node
	node["seq"].push_back("first element");  // node["seq"] automatically becomes a sequence
	node["seq"].push_back("second element");

	cout << node["seq"][0] << endl;
	cout << node["seq"][1] << endl;

	node["mirror"] = node["seq"][0];  // this creates an alias
	node["seq"][0] = "1st element";  // this also changes node["mirror"]
	node["mirror"] = "element #1";  // and this changes node["seq"][0] - they're really the "same" node

	node["self"] = node;  // you can even create self-aliases
	// the alias ia auto-ordered
	cout<< node;
}

void parse_demo6(void) {
	YAML::Node node  = YAML::Load("[1, 2, 3]");
	node[1] = 5;  // still a sequence, [1, 5, 3]
	node.push_back(-3);// still a sequence, [1, 5, 3, -3]
	node["key"] = "value"; // now it's a map! {0: 1, 1: 5, 2: 3, 3: -3, key: value}

	cout << node << endl;
}

void parse_demo7(void) {
	YAML::Node node = YAML::Load("[1, 2, 3]");
	cout << node << endl;
	node[3] = 4; // still a sequence, [1, 2, 3, 4]
	cout << node << endl;
	node[10] = 10;  // now it's a map! {0: 1, 1: 2, 2: 3, 3: 4, 10: 10}
	cout << node << endl;

}

void parse_demo8(void) {
	YAML::Node node = YAML::Load("{pi: 3.14159, [0, 1]: integers}");
	cout << node << endl;

// this needs the conversion from Node to double
	double pi = node["pi"].as<double>();
	cout << pi << endl;

// this needs the conversion from double to Node
	node["e"] = 2.71828;
	cout << node << endl;

// this needs the conversion from Node to std::vector<int> (*not* the other way around!)
	std::vector<int> v;  // Flow mode
	v.push_back(0);
	v.push_back(1);
	std::string str = node[v].as<std::string>();
	cout << str << endl;
}

struct Vec3 { double x, y, z; /* etc - make sure you have overloaded operator== */ };
namespace YAML {
	template<>
	struct convert<Vec3> {
		static Node encode(const Vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, Vec3& rhs) {
			if(!node.IsSequence() || node.size() != 3) {
				return false;
			}

			rhs.x = node[0].as<double>();
			rhs.y = node[1].as<double>();
			rhs.z = node[2].as<double>();
			return true;
		}
	};
}

void parse_file_demo(void) {

	YAML::Node config = YAML::LoadFile("src/config.yaml");

	const std::string username = config["user_info"]["username"].as<std::string>();
	const std::string password = config["user_info"]["password"].as<std::string>();
	cout << username << endl;
	cout << password << endl;

	const std::string start_index = config["start_index"].as<std::string>();
	const std::string end_index = config["end_index"].as<std::string>();
	cout << start_index << endl;
	cout << end_index << endl;;
}

int main() {
//	emit_demo();
//	parse_demo1();
//	parse_demo2();
//	parse_demo3();
//	parse_demo4();
//	parse_demo5();
//	parse_demo6();
//	parse_demo7();
//	parse_demo8();

/* Converting To/From Native Data Types */
//	YAML::Node node = YAML::Load("start: [1, 3, 0]");
//	Vec3 v = node["start"].as<Vec3>();
//	node["end"] = Vec3(2, -1, 0);


	parse_file_demo();

}