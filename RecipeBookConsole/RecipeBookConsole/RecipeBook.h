#pragma once

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include "Recipe.h"

using namespace std;

class RecipeBook {
private:
    vector<Recipe> recipes;
    unordered_map<string, Recipe> recipeMap;
    list<Recipe> recentRecipes;

public:
    void createRecipe();
    void addRecipe(const string& name, const vector<string>& ingredients, const string& method);
    void displayRecipes() const;
    void searchRecipes(const string& name) const;
    void displayRecentRecipes() const;
};
