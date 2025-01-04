#include <SFML/Graphics.hpp>
#include <cmath>
#include <imgui.h>
#include <imgui-SFML.h>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <iostream>

#define M_PI 3.14159
#define WIDTH 1300
#define HEIGHT 790

bool plotGraph = false;

// List of famous functions for plotting
std::vector<std::pair<std::string, std::function<double(double)>>> famousFunctions = {
    {"sin(x)", [](double x) { return std::sin(x); }},
    {"cos(x)", [](double x) { return std::cos(x); }},
    {"tan(x)", [](double x) { return std::tan(x); }},
    {"x^2", [](double x) { return x * x; }},
    {"x^3", [](double x) { return x * x * x; }},
    {"sqrt(x)", [](double x) { return std::sqrt(x); }},
    {"log(x)", [](double x) { return x > 0 ? std::log(x) : 0; }},
    {"exp(x)", [](double x) { return std::exp(x); }},
    {"1/(x+1)", [](double x) { return 1.0 / (x + 1); }},
    {"e^x", [](double x) { return std::exp(x); }},
    {"x^2 + 2x + 1", [](double x) { return x * x + 2 * x + 1; }},
    {"sin(x) + cos(x)", [](double x) { return std::sin(x) + std::cos(x); }},
    {"x^2 * sin(x)", [](double x) { return x * x * std::sin(x); }},
    {"cos(x) / x", [](double x) { return x != 0 ? std::cos(x) / x : 0; }},
    {"sin(x) / x", [](double x) { return x != 0 ? std::sin(x) / x : 0; }},
    {"log(x + 1)", [](double x) { return std::log(x + 1); }},
    {"x * exp(x)", [](double x) { return x * std::exp(x); }},
    {"x * cos(x)", [](double x) { return x * std::cos(x); }},
    {"1 / x", [](double x) { return x != 0 ? 1.0 / x : 0; }},
    {"x^3 - x^2", [](double x) { return x * x * x - x * x; }},
    {"tan(x) / x", [](double x) { return x != 0 ? std::tan(x) / x : 0; }},
    {"x^4", [](double x) { return x * x * x * x; }},
    {"sin(x^2)", [](double x) { return std::sin(x * x); }},
    {"cos(x^2)", [](double x) { return std::cos(x * x); }},
    {"x / (x + 1)", [](double x) { return x / (x + 1); }},
    {"x^2 / 10", [](double x) { return x * x / 10.0; }},
    {"1 - x^2", [](double x) { return 1 - x * x; }},
    {"x^3 - 3x^2 + 2x", [](double x) { return x * x * x - 3 * x * x + 2 * x; }},
    {"sin(2x)", [](double x) { return std::sin(2 * x); }},
    {"cos(2x)", [](double x) { return std::cos(2 * x); }},
    {"e^(-x^2)", [](double x) { return std::exp(-x * x); }},
    {"x * log(x)", [](double x) { return x * std::log(x); }},
    {"x^2 + x + 1", [](double x) { return x * x + x + 1; }},
    {"x^3 + x^2 + x + 1", [](double x) { return x * x * x + x * x + x + 1; }},
    {"x^2 - 2x + 1", [](double x) { return x * x - 2 * x + 1; }},
    {"1 / (x^2 + 1)", [](double x) { return 1 / (x * x + 1); }},
    {"x^2 / (x + 1)", [](double x) { return x * x / (x + 1); }},
    {"log(x^2)", [](double x) { return std::log(x * x); }},
    {"x^2 + 1 / x^2", [](double x) { return x * x + 1 / (x * x); }},
    {"log(x) / x", [](double x) { return std::log(x) / x; }},
    {"x^3 - 5x + 2", [](double x) { return x * x * x - 5 * x + 2; }},
    {"x^2 * cos(x)", [](double x) { return x * x * std::cos(x); }},
    {"x^2 * e^x", [](double x) { return x * x * std::exp(x); }},
    {"x * log(x + 1)", [](double x) { return x * std::log(x + 1); }},
    {"e^(x + 1)", [](double x) { return std::exp(x + 1); }},
    {"e^x / x", [](double x) { return std::exp(x) / x; }},
    {"x * tan(x)", [](double x) { return x * std::tan(x); }},
    {"cos(x) + sin(x)", [](double x) { return std::cos(x) + std::sin(x); }},
    {"log(x + 1) / x", [](double x) { return std::log(x + 1) / x; }},
    {"exp(-x)", [](double x) { return std::exp(-x); }},
    {"x^2 - 2x", [](double x) { return x * x - 2 * x; }},
    {"x * log(1 + x)", [](double x) { return x * std::log(1 + x); }},
    {"x * exp(x)", [](double x) { return x * std::exp(x); }},
    {"log(x) + 1", [](double x) { return std::log(x) + 1; }},
    {"sin(x) * cos(x)", [](double x) { return std::sin(x) * std::cos(x); }},
    {"sin(x + 1)", [](double x) { return std::sin(x + 1); }},
    {"e^(2x)", [](double x) { return std::exp(2 * x); }},
    {"x * e^(x + 1)", [](double x) { return x * std::exp(x + 1); }},
    {"log(x + 2)", [](double x) { return std::log(x + 2); }},
    {"cos(x + 1)", [](double x) { return std::cos(x + 1); }},
    {"sin(x) - cos(x)", [](double x) { return std::sin(x) - std::cos(x); }},
    {"log(x + 1) / x", [](double x) { return std::log(x + 1) / x; }},
    {"x * cos(x) / x", [](double x) { return std::cos(x); }},
    {"tan(x) - x", [](double x) { return std::tan(x) - x; }},
    {"sin(x + 1) / x", [](double x) { return std::sin(x + 1) / x; }},
    {"sin(x) * cos(x)", [](double x) { return std::sin(x) * std::cos(x); }},
};


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Function Plotter");
    window.setFramerateLimit(60);

    // Initialize ImGui
    ImGui::SFML::Init(window);

    sf::View view = window.getDefaultView();
    bool AdjustViewCoordinates = false;

    // User input for custom equation
    char userEquation[256] = "x*x";  // Default equation
    int selectedFunctionIndex = 0;  // Default to the first famous function

    // Define scale factors to fit the graph into the window
    float scaleX = WIDTH / 20.0f;  // Scaling factor for the x-axis
    float scaleY = HEIGHT / 10.0f;  // Scaling factor for the y-axis

    // Center of the window
    float centerX = WIDTH / 2;
    float centerY = HEIGHT / 2;

    sf::VertexArray graph(sf::LineStrip);
    sf::VertexArray grid(sf::Lines);

    // Add thicker lines for x and y axes
    sf::Color axisColor(255, 255, 0);
    sf::Color gridColor(255, 255, 0, 300);

    // Draw x-axis
    grid.append(sf::Vertex(sf::Vector2f(-10000, centerY), axisColor));
    grid.append(sf::Vertex(sf::Vector2f(10000, centerY), axisColor));

    // Draw y-axis
    grid.append(sf::Vertex(sf::Vector2f(centerX, -10000), axisColor));
    grid.append(sf::Vertex(sf::Vector2f(centerX, 10000), axisColor));

    // Add grid lines
    for (int i = -8000; i <= 8000; ++i) {
        if (i == 0) continue;

        // Vertical lines
        grid.append(sf::Vertex(sf::Vector2f(centerX + i * scaleX, -10000), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(centerX + i * scaleX, 10000), gridColor));

        // Horizontal lines
        grid.append(sf::Vertex(sf::Vector2f(-10000, centerY + i * scaleY), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(10000, centerY + i * scaleY), gridColor));
    }

    // Main rendering loop
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled) {
                AdjustViewCoordinates = true;
                float zoomFactor = 1.1f; // Adjust zoom sensitivity

                // Adjust zoom factor based on scroll direction
                if (event.mouseWheelScroll.delta > 0) {
                    // Zoom in
                    view.zoom(1.0f / zoomFactor);
                }
                else if (event.mouseWheelScroll.delta < 0) {
                    // Zoom out
                    view.zoom(zoomFactor);
                }
                window.setView(view);
            }
        }

        // Start ImGui frame
        ImGui::SFML::Update(window, deltaClock.restart());

        // ImGui interface to input custom equation and select famous functions
        ImGui::Begin("Graph Controls");
        if (ImGui::BeginCombo("Given Function", famousFunctions[selectedFunctionIndex].first.c_str())) {
            for (int i = 0; i < famousFunctions.size(); ++i) {
                bool isSelected = (i == selectedFunctionIndex);
                if (ImGui::Selectable(famousFunctions[i].first.c_str(), isSelected)) {
                    selectedFunctionIndex = i;
                }
            }
            ImGui::EndCombo();
        }
        ImGui::End();

        // Plot the graph based on the selected function or custom equation
        graph.clear();

        for (double i = -100; i <= 100; i += 0.001) {
            float x = static_cast<float>(i);
            float yVal;

            // Use the selected famous function or the custom equation
            if (selectedFunctionIndex >= 0 && selectedFunctionIndex < famousFunctions.size()) {
                yVal = static_cast<float>(famousFunctions[selectedFunctionIndex].second(x));
            }
           
            // Apply scaling and translation to match the window coordinates
            x *= scaleX;
            yVal *= scaleY;
            x += centerX;
            yVal = centerY - yVal;  // Invert y-axis

            // Add point to graph
            graph.append(sf::Vertex(sf::Vector2f(x, yVal), sf::Color::White));
        }

        // Draw everything
        window.setView(view);
        window.clear();
        window.draw(grid);  // Draw grid
        window.draw(graph);  // Draw graph

        // Render ImGui interface
        ImGui::SFML::Render(window);
        window.setView(view);
        window.display();
    }

    // Clean up ImGui
    ImGui::SFML::Shutdown();
    return 0;
}