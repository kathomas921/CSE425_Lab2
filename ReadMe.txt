ReadMe.txt
Katharine Thomas
James Wilson
Lab 1
CSE 425

-----------------------------------------------------------------------------------
HOW IT WORKS

The program reads an input text file and parses it according to the following input grammer: 

	hornclause -> head [SEPARATOR body]

	head -> predicate

	body -> predicate {AND predicate}

	predicate -> name LEFTPAREN [args] RIGHTPAREN

	name -> LABEL

	args -> symbol {COMMA symbol}

	symbol -> LABEL | NUMBER

It then outputs all unique label tokens, number tokens, and all properly formed Horn Clauses (according to the following output grammer):

	hornclause -> LEFTPAREN head [body] RIGHTPAREN

	head -> predicate

	body -> LEFTPAREN predicate {predicate} RIGHTPAREN

	predicate -> LEFTPAREN name {symbol} RIGHTPAREN

	name -> LABEL

	symbol -> LABEL | NUMBER
	
The parser uses recursive descent to check if the syntax is correct.  It first calls the isHorn method, which in turns calls isHead and then isBody to determine if there is at least a properly formed Head and then if that is followed by any number of properly formed predicates.

Following a properly formed head, the parser keeps parsing to determine if there is a correctly formed [SEPARATOR body] syntax afterward. If the parser is at the end of the file or sees that the next token is not a SEPARATOR token, it adds deque of token pointers making up the horn clause to the deque of horn clauses, dequeTP hornClause, (used by the semantic analysis function later) and begins again from where it left off. If a proper [SEPARATOR body] clause is found succeeding the head clause, it adds those properly formatted tokens into the deque of token pointers before it adds the fully computed horn clause to hornClause.  If an invalid syntax occurs after the head clause, the contents since the end of the last proper horn clause are discarded, and the parser starts from the next token.

If there is an incorrectly formed instance of a non-terminal, the parser will output an error message to the standard output stream documenting where in the input file (given by an int that keeps track of the token number) the error occurred as well as what the error was (that is, the grammar expected vs what it saw), and the tokens it has seen so far since the last properly formed Horn Clause (note: this was reimplemented at the very end when I realized we hadn't adjusted it for lab 1.  I'm pretty sure I got the end cases working, but there is a chance it will break everything from trying to print a nullptr.) As always, the parser then continues starting at the next token and begins its search for a Horn Clause.


As it parses, it stores pointers to tokens in deques (used instead of vectors for the possibility to use push_front, which we ended up using for adding parentheses).  We used (smart) pointers to store these values so that both derived and  base class tokens could be pointed to in the deque and no information would be lost through class slicing, which it would be the case if we had, for example, added a dervied number token to a deque of tokens.  Smart pointers make it easy to use dynamic allocatation without having to worry about manually deleting each pointer when it is done.

-----------------------------------------------------------------------------------
TEST CASES


--INPUT FILE-- 
ancestor ( x , y ) :- parent ( x , z ) ^ ancestor ( z , y )
solo ( HAN )
solo ( HAN ) :- solo ( mio )
friends ( Alice , BOB )
notfriends ( bob , CharLIE )
nogoodsyntax ( x , y ) nogoodsyntax ( x , z ) ^ nogoodsyntax ( z , y )
badlyf0rm3dNAME ( x , y )
goodname ( badlyf0rm3dARG )
descendent ( 21 , 1 ) :- parent ( 3 , 21 ) ^ descendent ( 3 , 1 )
solo ( 8115 )
solo ( 8115 ) :- solo ( 1590 )
friends ( 17 , 90 )
notfriends ( 17 , 21 )
extraA ( x , y ) ^ extraB ( z ) :- extraC ( z , x ) ^ extraD ( y ) ^ extraE ( x )
extraF ( x , y ) ^ extraG ( z )


--OUTPUT FILE--
extraB
extraC
extraD
extraE
extraF
extraG


21
1
3
8115
1590
17
90


( ( ancestor x y ) ( ( parent x z ) ( ancestor z y ) ) ) 
( ( solo HAN ) ) 
( ( solo HAN ) ( ( solo mio ) ) ) 
( ( friends Alice BOB ) ) 
( ( notfriends bob CharLIE ) ) 
( ( nogoodsyntax x y ) ) 
( ( nogoodsyntax x z ) ) 
( ( nogoodsyntax z y ) ) 
( ( descendent 21 1 ) ( ( parent 3 21 ) ( descendent 3 1 ) ) ) 
( ( solo 8115 ) ) 
( ( solo 8115 ) ( ( solo 1590 ) ) ) 
( ( friends 17 90 ) ) 
( ( notfriends 17 21 ) ) 
( ( extraA x y ) ) 
( ( extraB z ) ( ( extraC z x ) ( extraD y ) ( extraE x ) ) ) 
( ( extraF x y ) ) 
( ( extraG z ) ) 

--OUTPUT COMMAND LINE--
Error detected @ Input token: 66 -> Expected: LABEL, Received: LEFTPAREN
Tokens seen so far in clause: badlyf0rm3dNAME (

Error detected @ Input token: 68 -> Expected: LEFTPAREN, Received: COMMA
Tokens seen so far in clause: x ( x ,

Error detected @ Input token: 70 -> Expected: LEFTPAREN, Received: RIGHTPAREN
Tokens seen so far in clause: y , y )

Error detected @ Input token: 73 -> Expected: SYMBOL, Received: UNKNOWN
Tokens seen so far in clause: goodname ) goodname ( badlyf0rm3dARG

Error detected @ Input token: 74 -> Expected: LABEL, Received: RIGHTPAREN
Tokens seen so far in clause: badlyf0rm3dARG )





--INPUT FILE--
^ nogoodsyntax ( 4 , y ) fine ( bad , y 3)

--OUTPUT FILE--
nogoodsyntax
y


4


( ( nogoodsyntax 4 y ) ) 

--OUTPUT COMMAND LINE--

H:\My Documents\Visual Studio 2013\Projects\Lab2\Debug>Lab2.exe testin2.txt test
out.txt

Error detected @ Input token: 13 -> Expected: COMMA OR RIGHTPAREN, Received: UNK
NOWN
Tokens seen so far in clause: fine ( bad , y 3)

-----------------------------------------------------------------------------------
ISSUES

We had a lot of issues getting the deques to work as we anticipated.  We kept running into what I assumed to be nullptr errors ("Lab2.exe has stopped working").  We fought tooth and nail for every line while debugging this lab and was generally a truly painful, albeit educational experience. 

I also had some fun learning about exern before I realized I should just put the semantic analysis function in the parse.cpp file.  Previously I was trying to figure out how to export the deques of horn clauses while still being able to give a logical error if the input file didn't work.  I suppose I could have thrown an error and caught it in main, but semAnalysis didn't actually need its own file anyway.  