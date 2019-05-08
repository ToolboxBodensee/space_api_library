#ifndef SPACE_API
#define SPACE_API

#include "cJSON.h"
#include <ESP8266HTTPClient.h>

namespace spaceAPI {
	namespace detail {
		const char* space_api_url = "https://bodensee.space/spaceapi/toolboxbodenseeev.json";
		signed int getSpaceStatus(const char* payload);
	}
	signed int is_open();
}

signed int spaceAPI::detail::getSpaceStatus(const char* payload) {
	cJSON *json = cJSON_Parse(payload);
	signed int return_val = -1;
	if (!json) return return_val;

	cJSON *spaceState = cJSON_GetObjectItemCaseSensitive(json, "state");
	cJSON *spaceOpen = cJSON_GetObjectItemCaseSensitive(spaceState, "open");

	if (cJSON_IsBool(spaceOpen))
	{
		if (cJSON_IsTrue(spaceOpen)) {
			return_val = 1;
		}
		else {
			return_val = 0;
		}
	}
	return return_val;
}

signed int spaceAPI::is_open() {
	signed int spaceStatus = -1;
	if (WiFi.status() = WL_CONNECTED)
	{
		HTTPClient http;
		http.begin(space_api_url);
		int httpCode = http.GET();
		if (httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			spaceStatus = detail::getSpaceStatus(payload.c_str());
		}
		http.end();
	}
	return spaceStatus;
}

#endif /* SPACE_API */
