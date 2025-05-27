#include "espresso_based.h"
#include <memory>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>
#include <chrono>
#include <iostream>

EspressoBased::EspressoBased(){};

EspressoBased::EspressoBased(const EspressoBased& esp):name(esp.name)
{
    for(const auto& ingredient : esp.ingredients)
    {
        ingredients.push_back(std::shared_ptr<Ingredient>(ingredient->clone()));
    }
};

void EspressoBased::operator=(const EspressoBased& esp)
{
    this->name = esp.name;
    this->ingredients = esp.ingredients;
}
EspressoBased::~EspressoBased()
{
    std::cout << "EsspressoBased destructor called" << std::endl;
    ingredients.clear();
}

std::vector<std::shared_ptr<Ingredient>>& EspressoBased::get_ingredients()
{
    return this->ingredients;
};

void EspressoBased::brew() {
    using namespace ftxui;
    using namespace std::chrono_literals;
    
    auto screen = ScreenInteractive::TerminalOutput();
    
    // The brewing steps - customize based on ingredients
    std::vector<std::string> steps;
    steps.push_back("Grinding coffee beans...");
    steps.push_back("Heating water...");
    steps.push_back("Extracting espresso...");
    
    // Count units of each ingredient to determine proportions
    int espresso_units = 0;
    int milk_units = 0;
    int milk_foam_units = 0;
    int chocolate_units = 0;
    int total_units = 0;
    
    for (const auto& ingredient : ingredients) {
        if (ingredient->get_name() == "Espresso") {
            espresso_units += ingredient->get_units();
        } else if (ingredient->get_name() == "Milk") {
            milk_units += ingredient->get_units();
            steps.push_back("Steaming milk...");
        } else if (ingredient->get_name() == "MilkFoam") {
            milk_foam_units += ingredient->get_units();
            steps.push_back("Adding milk foam...");
        } else if (ingredient->get_name() == "Chocolate") {
            chocolate_units += ingredient->get_units();
            steps.push_back("Adding chocolate...");
        }
        total_units += ingredient->get_units();
    }
    
    steps.push_back("Finishing " + name + "...");
    
    int current_step = 0;
    int max_steps = steps.size();
    
    // Progress percentage
    int progress = 0;
    
    // Create animated component
    auto component = Container::Vertical({
        Renderer([&] {
            std::vector<Element> brew_representation;
            
            // Title with coffee name
            brew_representation.push_back(
                text(name + " Brewing Process") | bold | color(Color::Blue) | center
            );
            
            // Current step display
            if (current_step < max_steps) {
                brew_representation.push_back(
                    text(steps[current_step]) | color(Color::Green)
                );
            } else {
                brew_representation.push_back(
                    text("Brewing complete!") | color(Color::Green) | bold
                );
            }
            
            // Progress bar
            brew_representation.push_back(
                hbox({
                    text("Progress: "),
                    gauge(float(progress) / 100.0f) | flex,
                })
            );
            
            // Visual representation of coffee
            std::vector<Element> cup_elements;
            
            // Cup rim
            cup_elements.push_back(
                text("  ____________  ") | color(Color::GrayDark)
            );
            
            // Coffee level (increases as progress increases)
            int coffee_level = 10 * progress / 100;
            
            // Colors for different ingredients
            Color espresso_color = Color::GrayDark;      // Dark brown for espresso
            Color milk_color = Color::RGB(225, 190, 160);      // Light beige for milk
            Color chocolate_color = Color::RGB(110, 60, 25);   // Medium brown for chocolate
            Color foam_color = Color::RGB(245, 240, 220);      // Off-white for milk foam
            
            // Calculate layer heights based on ingredient proportions
            int espresso_height = 0;
            int chocolate_height = 0;
            int milk_height = 0;
            int foam_height = 0;
            
            if (total_units > 0) {
                // We'll use 10 layers total for a filled cup
                espresso_height = (espresso_units * 10) / total_units;
                chocolate_height = (chocolate_units * 10) / total_units;
                milk_height = (milk_units * 10) / total_units;
                foam_height = (milk_foam_units * 10) / total_units;
                
                // Ensure at least 1 layer for any ingredient with units > 0
                if (espresso_units > 0 && espresso_height == 0) espresso_height = 1;
                if (chocolate_units > 0 && chocolate_height == 0) chocolate_height = 1;
                if (milk_units > 0 && milk_height == 0) milk_height = 1;
                if (milk_foam_units > 0 && foam_height == 0) foam_height = 1;
                
                // Adjust to ensure total is 10
                int total_height = espresso_height + chocolate_height + milk_height + foam_height;
                if (total_height < 10) {
                    // Add the remaining to the largest component
                    if (espresso_height >= chocolate_height && espresso_height >= milk_height && espresso_height >= foam_height) {
                        espresso_height += (10 - total_height);
                    } else if (chocolate_height >= espresso_height && chocolate_height >= milk_height && chocolate_height >= foam_height) {
                        chocolate_height += (10 - total_height);
                    } else if (milk_height >= espresso_height && milk_height >= chocolate_height && milk_height >= foam_height) {
                        milk_height += (10 - total_height);
                    } else {
                        foam_height += (10 - total_height);
                    }
                } else if (total_height > 10) {
                    // Reduce proportionally
                    espresso_height = (espresso_height * 10) / total_height;
                    chocolate_height = (chocolate_height * 10) / total_height;
                    milk_height = (milk_height * 10) / total_height;
                    foam_height = (foam_height * 10) / total_height;
                    
                    // Ensure we get exactly 10
                    total_height = espresso_height + chocolate_height + milk_height + foam_height;
                    if (total_height < 10) {
                        espresso_height += (10 - total_height);
                    }
                }
            }
            
            // Draw layers from bottom to top based on the actual recipe
            int current_layer = 0;
            
            // Draw the cup based on progress
            for (int i = 0; i < 10; i++) {
                if (i >= (10 - coffee_level)) {
                    Color layer_color;
                    
                    // Determine color based on layer type
                    if (current_layer < espresso_height) {
                        layer_color = espresso_color;
                    } else if (current_layer < espresso_height + chocolate_height) {
                        layer_color = chocolate_color;
                    } else if (current_layer < espresso_height + chocolate_height + milk_height) {
                        layer_color = milk_color;
                    } else {
                        layer_color = foam_color;
                    }
                    
                    cup_elements.push_back(
                        text(" |||||||||||||| ") | color(layer_color)
                    );
                    current_layer++;
                } else {
                    // Empty space
                    cup_elements.push_back(
                        text(" |            | ") | color(Color::GrayDark)
                    );
                }
            }
            
            // Cup bottom
            cup_elements.push_back(
                text(" |____________| ") | color(Color::GrayDark)
            );
            cup_elements.push_back(
                text("  ‾‾‾‾‾‾‾‾‾‾‾‾  ") | color(Color::GrayDark)
            );
            
            // Add cup to brewing representation
            brew_representation.push_back(vbox(cup_elements));
            
            // Ingredients list with proportions
            std::vector<Element> ingredients_elements;
            ingredients_elements.push_back(
                text("Ingredients:") | bold
            );
            
            for (const auto& ingredient : ingredients) {
                // Color-code the ingredients
                Color ingredient_color = Color::White;
                if (ingredient->get_name() == "Espresso") {
                    ingredient_color = espresso_color;
                } else if (ingredient->get_name() == "Milk") {
                    ingredient_color = milk_color;
                } else if (ingredient->get_name() == "MilkFoam") {
                    ingredient_color = foam_color;
                } else if (ingredient->get_name() == "Chocolate") {
                    ingredient_color = chocolate_color;
                }
                
                // Show proportion percentage
                int percentage = (ingredient->get_units() * 100) / total_units;
                
                ingredients_elements.push_back(
                    text(" • " + ingredient->get_name() + 
                         " (" + std::to_string(ingredient->get_units()) + " units, " + 
                         std::to_string(percentage) + "%)") 
                    | color(ingredient_color)
                );
            }
            
            brew_representation.push_back(vbox(ingredients_elements));
            
            // Recipe summary
            brew_representation.push_back(text("Recipe: ") | bold);
            std::string recipe_text = name + ": ";
            if (espresso_units > 0) recipe_text += std::to_string(espresso_units) + " Espresso ";
            if (chocolate_units > 0) recipe_text += std::to_string(chocolate_units) + " Chocolate ";
            if (milk_units > 0) recipe_text += std::to_string(milk_units) + " Milk ";
            if (milk_foam_units > 0) recipe_text += std::to_string(milk_foam_units) + " MilkFoam";
            
            brew_representation.push_back(text(recipe_text));
            
            return vbox(brew_representation) | border;
        }),
    });
    
    // Thread to update the progress
    std::thread update_thread([&] {
        for (current_step = 0; current_step < max_steps; current_step++) {
            // Each step takes some time to complete
            int step_frames = 100 / max_steps;
            for (int i = 0; i < step_frames; i++) {
                std::this_thread::sleep_for(100ms);
                progress = (current_step * step_frames) + i;
                
                // Request screen refresh
                screen.PostEvent(Event::Custom);
            }
        }
        
        // Ensure we reach 100%
        progress = 100;
        screen.PostEvent(Event::Custom);
        
        // Wait a moment at 100% before exiting
        std::this_thread::sleep_for(2s);
        
        // Exit the animation
        screen.Exit();
    });
    
    // Run the UI loop
    screen.Loop(component);
    
    // Clean up thread
    if (update_thread.joinable()) {
        update_thread.join();
    }
    
    // Print a message to console after visualization is done
    std::cout << "Your " << name << " is ready!" << std::endl;
}

