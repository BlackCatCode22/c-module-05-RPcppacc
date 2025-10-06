#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Callback function to write received data into a std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    string* str = static_cast<string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set the URL for the Fresno forecast endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.weather.gov/gridpoints/HNX/72,30/forecast");

        // Set the User-Agent header as required by NWS API
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "User-Agent: MyCPPWeatherApp/1.0 (email@example.com)");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set callback to capture the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            try {
                // Parse the JSON response
                auto jsonData = json::parse(readBuffer);

                cout << "Forecast for Fresno, CA:" << endl;
                for (const auto& period : jsonData["properties"]["periods"]) {
                    cout << period["name"] << ": "
                         << period["temperature"] << "°F - "
                         << period["shortForecast"] << endl;
                }
            } catch (json::parse_error& e) {
                cerr << "JSON parsing error: " << e.what() << endl;
            } catch (json::type_error& e) {
                cerr << "JSON type error: " << e.what() << endl;
            }
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        cerr << "Failed to initialize curl" << endl;
    }

    curl_global_cleanup();
    return 0;
}
