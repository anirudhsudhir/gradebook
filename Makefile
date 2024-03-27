all:
	cc gradebook.c studentDetails.c utils.c -o gradebook
debug:
	cc -g gradebook.c studentDetails.c utils.c -o gradebook
