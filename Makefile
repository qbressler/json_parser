main:
	gcc -o json_parser main.c cJSON.c -lm
clean:
	rm json_parser
