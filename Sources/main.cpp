#include <Files.h>
#include <Path.h>
#include <Json.h>
#include <FileReader.h>
#include <StringHelper.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace kmd;

enum ServerType {
	GithubServer,
	GitblitServer
};

struct Server {
	ServerType type;
	std::string urlpart;
	std::string user;
	std::string pass;
};

int main(int argc, char** argv) {
	if (argc < 2) return 0;

	std::vector<Server> servers;
	std::string appdir = getenv("KIT_DATA_PATH");
	Path options = Paths::get(appdir, "options.json");
	if (Files::exists(options)) {
		kmd::FileReader reader(options.toString().c_str());
		char* content = (char*)reader.readAll();
		char* text = new char[reader.size() + 1];
		for (int i = 0; i < reader.size(); ++i) text[i] = content[i];
		text[reader.size()] = 0;
		Json::Data options(text);
		int serverCount = options["servers"].size();
		for (int i = 0; i < serverCount; ++i) {
			Json::Value& server = options["servers"][i];
			if (server.has("user") && server.has("pass")) {
				Server s;
				if (server["type"].string() == "gitblit") {
					s.type = GitblitServer;
					s.urlpart = server["url"].string();
				}
				else {
					s.type = GithubServer;
					s.urlpart = server["path"].string();
				}
				s.user = server["user"].string();
				s.pass = server["pass"].string();
				servers.push_back(s);
			}
		}
	}

	std::string request = argv[1];
	int urlstart = firstIndexOf(request, '\'');
	int urlend = lastIndexOf(request, '\'');
	std::string url = request.substr(urlstart + 1, urlend - urlstart - 1);
	for (unsigned i = 0; i < servers.size(); ++i) {
		if (contains(url, servers[i].urlpart)) {
			if (startsWith(request, "Username")) std::cout << servers[i].user << std::endl;
			else if (startsWith(request, "Password")) std::cout << servers[i].pass << std::endl;
			break;
		}
	}
}
