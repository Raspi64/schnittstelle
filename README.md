# --- BASIC README ---

##  Code expansion
For code expansion you need to register a new Command.
Just go to the the basic_register_command() in the basic_plugin.cpp file and add:

	mb_register_func(bas, "NEWKEYWORD", new_function);

Now go to the basic_function.h and add your function:

	int new_function(struct mb_interpreter_t *, void **);

Then you go to the basic_function.cpp and write there your new funktion:

	int new_function(struct mb_interpreter_t *bas, void **ptr) {
		int result = MB_FUNC_OK;		
		//code
		return result
	}	

*NOTE* If your function don't need parameters so call

	int mb_attempt_func_begin(struct mb_interpreter_t* bas, void** ptr);

and

	int mb_attempt_func_end(struct mb_interpreter_t* bas, void** ptr);


### Parameters
If you need parameters then these function will help:

	int mb_attempt_open_bracket(struct mb_interpreter_t* bas, void** ptr);
	int mb_attempt_close_bracket(struct mb_interpreter_t* bas, void** ptr);

	int mb_has_arg(struct mb_interpreter_t* bas, void** ptr);

	int mb_pop_int(struct mb_interpreter_t* bas, void** ptr, int_t* val);
	int mb_pop_real(struct mb_interpreter_t* bas, void** ptr, int_t* val);
	int mb_pop_string(struct mb_interpreter_t* bas, void** ptr, char** val);
	int mb_pop_usertype(struct mb_interpreter_t* bas, void** ptr, void** val);
 	int mb_pop_value(struct mb_interpreter_t* bas, void** ptr, mb_value_t* val);

For return values:

	int mb_push_int(struct mb_interpreter_t* bas, void** ptr, int_t val);
	int mb_push_real(struct mb_interpreter_t* bas, void** ptr, real_t val);
	int mb_push_string(struct mb_interpreter_t* bas, void** ptr, char* val);
	int mb_push_usertype(struct mb_interpreter_t* bas, void** ptr,void* val);
 	int mb_push_value(struct mb_interpreter_t* bas, void** ptr, mb_value_t val);

#### Example
A simple echo-function: 

 	int basic_echo(struct mb_interpreter_t *bas, void **ptr) {
        	char* s;

		mb_check(mb_attempt_open_bracket(bas, ptr));
		mb_check(mb_pop_string(bas, ptr, &s));
		mb_check(mb_attempt_close_bracket(bas, ptr));

		printf("%s \n", s);

	        return MB_FUNC_OK;
    	}

-----------------------

## List of implemented commands

### Keyword

	REM
	NIL
	MOD
	AND
	OR
	NOT
	IS
	LET
	DIM
	IF
	THEN
	ELSEIF
	ELSE
	ENDIF
	FOR
	IN
	TO
	STEP
	NEXT
	WHILE
	WEND
	DO
	UNTIL
	EXIT
	GOTO
	GOSUB
	RETURN
	CALL
	DEF
	ENDDEF
	CLASS
	ENDCLASS
	ME
	NEW
	VAR
	REFLECT
	LAMBDA
	MEM
	TYPE
	IMPORT
	END

	ABS
	SGN
	SQR
	FLOOR
	CEIL
	FIX
	ROUND
	SRND
	RND
	SIN
	COS
	TAN
	ASIN
	ACOS
	ATAN
	EXP
	LOG
	ASC
	CHR
	LEFT
	LEN
	MID
	RIGHT
	STR
	VAL
	PRINT
	INPUT

	LIST
	DICT
	PUSH
	POP
	BACK
	INSERT
	SORT
	EXIST
	INDEX_OF
	GET
	SEt
	REMOVE
	CLEAR
	CLONE
	TO_ARRAY
	ITERATOR
	MOVE_NEXT

	TRUE
	FALSE



### Operators

	+
	-
	*
	/
	^
	=
	<
	>
	<=
	>=
	<>
	MOD
	AND
	OR
	NOT
	IS
	
-----------------------

## Exercises
Aufgabe 1: Hello World!
Schreibe ein kleines Programm das den String “Hello World!” einmal ausgibt.

Musterlösung:


	10 PRINT “Hello World!”
	20 END
	RUN



Aufgabe 2: Hello World! To everyone
Schreib ein kleines Programm das den String “Hello World!” unendlich oft ausgibt.

Musterlösung:


	10 PRINT "Hello World!"
	20 GOTO 10
	30 END
	RUN


Aufgabe 3: Der Countdown
Schreibe ein Programm das die Zahlen von 10 bis einschließlich 0 ausgibt.

Musterlösung:


	10 FOR I = 0 TO 10 STEP 1
	20 PRINT 10-I
	30 NEXT
	40 END
	RUN


Aufgabe 4: The numbers every programmer must know
Schreibe ein Programm das die Exponenten von 2^n bis einschließlich 1024 ausgibt.

Musterlösung:


	10 FOR I = 0 TO 10 STEP 1
	20 PRINT 2^I
	30 NEXT
	40 END
	RUN


Aufgabe 5: Gauß the brain
Schreib ein Programm das die Summe von 1 bis n (z.B. 100) errechnet. Die Zahll n soll im Verlauf des Programms variabel eingegeben werden können.

Musterlösung:


	10 PRINT "Gib die höchste Zahl ein:"
	10 INPUT A
	20 PRINT (A*(A+1))/2
	30 END
	RUN

