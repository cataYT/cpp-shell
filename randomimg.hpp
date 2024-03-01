#ifndef RANDOMIMG_HPP
#define RANDOMIMG_HPP

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *buffer) {
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

std::string getRandImg() {
    std::string url = "https://api.unsplash.com/photos/random?client_id=MFlRACQmp3CATS_QPUT6PHZl5tyuXaq2Y7b4H7qfuoA";
    CURL *curl;
    CURLcode res;
    std::string rawData;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rawData);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    // Parse JSON
    try {
        json jsonData = json::parse(rawData);
        return jsonData["urls"]["raw"].get<std::string>();
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return "";
    }
}

#endif // RANDOMIMG_HPP