#Build the executable
fileSearch:
	gcc -o fileSearch fileSearch.c

#Remove the executable
clean:
	rm -f fileSearch
