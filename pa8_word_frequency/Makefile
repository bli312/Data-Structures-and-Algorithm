#  ***
#  * Leo Li
#  * bli312
#  * 2024 Fall CSE101 PA8
#  * Makefile
#  * Makefile for CSE 101 Programming Assignment 8
#  ***


#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

ORDERMAIN 	   = Order
ORDERSOURCE    = $(ORDERMAIN).cpp
ORDEROBJECT    = $(ORDERMAIN).o


# WordFrequency: WordFrequency.o Dictionary.o
$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)


$(ORDERMAIN): $(ORDEROBJECT) $(ADT_OBJECT)
	$(LINK) $(ORDERMAIN) $(ORDEROBJECT) $(ADT_OBJECT)


$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)


$(ORDEROBJECT): $(ORDERSOURCE) $(ADT_HEADER)
	$(COMPILE) $(ORDERSOURCE)


$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT_TEST) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT) $(ORDEROBJECT) $(ORDERMAIN)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) ./$(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) ./$(ADT_TEST)

