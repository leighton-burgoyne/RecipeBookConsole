#include <string>
#include "RecipeBook.h"
#include <iostream>

using namespace std;

#define TITLE_TEXT "\033[34m" // Blue Text Colour
#define ERROR_TEXT "\033[31m" // Red Text Colour
#define PROMPT_TEXT "\033[33m" // Yellow Text Colour
#define SUCCESS_TEXT "\033[32m" // Green Text Colour
#define DEFAULT_TEXT "\033[0m" // Default Terminal Colour

RecipeBook* recipeBook = new RecipeBook(); // Create a new instance of RecipeBook and assign to the pointer
int menuOption; // Menu Option Variable
bool active = true; // Set the program to active

int main() {
    cout << TITLE_TEXT << "===== Welcome to Recipe Book Manager =====\n" << DEFAULT_TEXT;
 
    while (active) { // Run the program while active
        cout << PROMPT_TEXT << "\n===== Main Menu =====" << DEFAULT_TEXT << endl;
        cout << "1. View Recipes\n2. Create Recipe\n3. Search Recipe\n4. Quit" << endl;

        cout << "Enter Menu Option: "; // Menu Option Selection
        cin >> menuOption;
        string searchTerm;
        switch (menuOption)
        {

        // View Recipes Option
        case 1:
            cout << PROMPT_TEXT << "\nSelected 1: View Recipes" << DEFAULT_TEXT << endl;
            cout << SUCCESS_TEXT << "\nRecent Recipes" << DEFAULT_TEXT << endl;
            recipeBook->displayRecentRecipes();
            cout << SUCCESS_TEXT << "\nAll Recipes" << DEFAULT_TEXT << endl;
            recipeBook->displayRecipes();
            break;

        // Create Recipes Option
        case 2:
            cout << PROMPT_TEXT << "\nSelected 2: Create Recipe" << DEFAULT_TEXT << endl;
            recipeBook->createRecipe();
            break;

        // Search Recipes Option
        case 3:
            cout << PROMPT_TEXT << "\nSelected 3: Search Recipe" << DEFAULT_TEXT << endl;
            cout << "Enter Recipe Name: ";
            cin.ignore();
            getline(cin, searchTerm);
            recipeBook->searchRecipes(searchTerm);
            break;

        // Exit Option
        case 4:
            cout << PROMPT_TEXT << "\nQuitting Program..." << DEFAULT_TEXT << endl;
            active = false; // Set active to false (quits the program)
            break;

        // Default Option
        default:
            cout << ERROR_TEXT << "\nInvalid Option" << DEFAULT_TEXT << endl;
            continue; // Prompt menu again
        }
    }
    delete recipeBook; // Delete RecipeBook from memory
    return 0; // Return 0 to the main function
}

// Create Recipe (handles the user input side of creating a new Recipe)
void RecipeBook::createRecipe() {
    // Temp Variables for user input handling
    string name;
    vector<string> ingredients;
    string method;
    string ingredient;
    int loopAmount;

    // Name Input
    cout << "Enter Recipe Name: ";
    cin.ignore();
    getline(cin, name);

    // Ingredient Input Loop
    cout << "Enter Number of Ingredients: ";
    cin >> loopAmount;
    cin.ignore();

    for (int i = 0; i < loopAmount; ++i) {
        cout << "Specify Ingredient " << i + 1 << ": ";
        getline(cin, ingredient);
        ingredients.push_back(ingredient);
    }

    // Method Input
    cout << "Method: ";
    getline(cin, method);

    // Add Recipe
    addRecipe(name, ingredients, method);
}

// Add Recipe (handles adding a new Recipe to the vector, list and hash table structures)
void RecipeBook::addRecipe(const string& name, const vector<string>& ingredients, const string& method) {
    Recipe recipe(name, ingredients, method);
    recipes.push_back(recipe);
    recipeMap[name] = recipe;
    recentRecipes.push_front(recipe);
    if (recentRecipes.size() > 5) {
        recentRecipes.pop_back();
    }
}

// Display Recipes (displays all contents of the recipes vector)
void RecipeBook::displayRecipes() const
{
    // If Recipe Vector Empty
    if (recipes.empty()) {
        cout << "No Recipes Stored.\n";
    }
    else
    {
        // Output Recipes
        for (const auto& recipe : recipes) {
            cout << "Recipe Name: " << recipe.name << "\nIngredients: ";
            for (const auto& ingredient : recipe.ingredients) {
                cout << ingredient << ", ";
            }
            cout << "\nMethod: " << recipe.method << "\n\n";
        }
    }
}

// Search Recipes (uses the recipeMap hash table to search for recipes with the specified name)
void RecipeBook::searchRecipes(const string& name) const
{
    auto it = recipeMap.find(name);
    if (it != recipeMap.end()) {
        const Recipe& recipe = it->second;
        cout << "Recipe Name: " << recipe.name << "\nIngredients: ";
        for (const auto& ingredient : recipe.ingredients) {
            cout << ingredient << ", ";
        }
        cout << "\nMethod: " << recipe.method << "\n\n";
    }
    // If Recipe not found
    else {
        cout << "Recipe not found with the name " + name + "\n";
    }
}

// Display Recent Recipes (displays contents of the recentRecipes list)
void RecipeBook::displayRecentRecipes() const
{
    if (recipes.empty()) {
        cout << "No Recipes Stored.\n";
    }
    else
    {
        for (const auto& recipe : recentRecipes) {
            cout << "Recipe Name: " << recipe.name << "\nIngredients: ";
            for (const auto& ingredient : recipe.ingredients) {
                cout << ingredient << ", ";
            }
            cout << "\nMethod: " << recipe.method << "\n";
        }
    }
}