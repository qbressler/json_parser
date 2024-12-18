#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

void format_json(const char *filename) {
	FILE *file = fopen(filename, "r");
	if(!file) {
		printf("Unable to open file %s\n", filename);
		return;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *json_data = (char *)malloc(length + 1);

	if(!json_data) {
		printf("Memory fault\b");
		fclose(file);
		return;
	}

	fread(json_data, 1, length, file);
	json_data[length] = '\0';

	fclose(file);

	cJSON *json = cJSON_Parse(json_data);
	if(json == NULL) {
		printf("Could not read json file %s", cJSON_GetErrorPtr());
		free(json_data);
		return;
	}

	char *formatted_json = cJSON_Print(json);
	if(formatted_json) {
		printf("%s", formatted_json);
		free(formatted_json);
	}

	cJSON_Delete(json);
	free(json_data);
}
int main() {
	printf("reading json file...\n");
	const char *filename = "test.json";
	format_json(filename);
	return 0;
	
}
