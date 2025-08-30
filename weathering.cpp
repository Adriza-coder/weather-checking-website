#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for getenv
using namespace std;

int main() {
    // Required header for HTML output
    cout << "Content-type: text/html; charset=UTF-8\n\n";


    // Start HTML with styling
    cout << "<html><head><title>Weather Result</title></head>";
    cout << "<body style='font-family:Segoe UI; text-align:center; background:linear-gradient(to bottom,#d4f1f9,#ffffff); padding-top:50px;'>";

    // Get city name from browser query
    string query = getenv("QUERY_STRING") ? getenv("QUERY_STRING") : "";
    string city = query.substr(5); // removes "city=" from start

    // Replace '+' with space (because browser sends spaces as '+')
    for (char &c : city) {
        if (c == '+') c = ' ';
    }

    // Open weather data file
    ifstream file("weather_data.txt");

    string name, condition;
    int temp, humidity;
    bool found = false;

    // Search each line for the entered city
    while (file >> name >> temp >> humidity >> condition) {
        // Compare lowercase versions
        string nameLower = name, cityLower = city;
        for (char &c : nameLower) c = tolower(c);
        for (char &c : cityLower) c = tolower(c);

        if (nameLower == cityLower) {
            // Show results with colors and emojis
            cout << "<h1 style='color:#003366;'>🌆 Weather in " << name << "</h1>";
            cout << "<p style='font-size:20px;color:#ff6600;'>🌡 Temperature: " << temp << "°C</p>";
            cout << "<p style='font-size:20px;color:#0099cc;'>💧 Humidity: " << humidity << "%</p>";
            cout << "<p style='font-size:20px;color:#006600;'>🌤 Condition: " << condition << "</p>";
            found = true;
            break;
        }
    }

    // If city not found
    if (!found) {
        cout << "<p style='color:red;font-size:20px;'>❌ City not found in database.</p>";
    }

    // Link back to form
    cout << "<br><br><a href='/weather_form.html' style='text-decoration:none; color:#0066cc; font-weight:bold;'>🔍 Search Again</a>";

    cout << "</body></html>";

    return 0;
}
