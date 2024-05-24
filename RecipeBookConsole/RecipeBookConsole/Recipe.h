#include <string>
#include <vector>

#pragma once

using namespace std;

class Recipe {
public:
	string name;
	vector<string> ingredients;
	string method;

	Recipe() : name(""), ingredients(), method("") {}

	Recipe(const string& n, const vector<string>& ingr, const string& mthd)
		: name(n), ingredients(ingr), method(mthd) {}
};