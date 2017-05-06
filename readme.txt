
*************************
Compilation
*************************
make
chmod +x view.py  (nothing was mentioned about including this in the makefile)
mkdir messages (adding the messages directory)

*******************************
running the program
*****************************
./addauthor <name>
./post <name>
./view.py <name>

***************************
Notes
***************************
-my A1 is garbage so I wrote post.cc in C but still using the converted method where I can; pretty much I use function pointers in structs. My a1 converts the .cc file to .c
-I require there to be a messages folder already in the a2 directory before any of the programs execute because I don't check if it exists (instruction was added in compilation tab)
-I make multi-word usernames into one long username with underscores, so <user name> == <user_name_>, therefore if the second username is entered, it will say it's the same as the first
-there are memory leaks in my program- I was getting a seg fault and double free errors, so thats the best I was able to do
-since there was a lot of controversy about the file creation part, I believe I have adhered to the specs as much as possible as to when they are created
-I forgot to check if strings are null, so in instances such as the addauthor program, if you ctrl-d in the stream list, it will seg fault

For view.py
	-I keep track of where the user is in the messages by linecount, not the streamData file, making my streamStreamUser file keep track of line number, not # of messages viewed
	-I did not implement the "all" option to print all the streams
	-I did not impement the "o" option to order by date/username
	
