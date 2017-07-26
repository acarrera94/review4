// Please do not modify any part of this file.

#include <iostream>

#include "Stack.h"
#include "TestCase.h"

using namespace std;
using namespace cs235;

struct CounterClass
{
	static int InstanceCount;

	int Data;

	CounterClass() : Data(0) { InstanceCount++; }
	CounterClass(int data) : Data(data) { InstanceCount++; }
	CounterClass(const CounterClass& other) : Data(other.Data) { InstanceCount++; }

	~CounterClass() { InstanceCount--; }

	bool operator==(const CounterClass& other) { return Data == other.Data; }
	bool operator!=(const CounterClass& other) { return Data != other.Data; }
};

int CounterClass::InstanceCount = 0;

//##############################################################################
//###   Constructor tests
//##############################################################################

/**************************************/
void Constructor_Basic()
{
	TestCase tc("Make an instance of a linked list.");

	CounterClass::InstanceCount = 0;
	try
	{
		try
		{
			Stack<int> a;
			tc.LogResult(true, "Make a list<int>");

			Stack<string> b;
			tc.LogResult(true, "Make a list<string>");

			Stack<CounterClass> stack;
			tc.LogResult(true, "Make a list<CounterClass>");
		}
		catch (exception ex)
		{
			tc.LogException(ex);
		}
	}
	catch (...)
	{
		tc.LogResult(RESULT_FAILED, "Unknown exception.  Is your destructor throwing an exception?");
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void Constructor_SizeIsZero()
{
	TestCase tc("Linked list is initialized to empty.");

	try
	{
		try
		{
			Stack<CounterClass> x;
			tc.AssertEquals(0, x.Count(), "Make sure size is zero.");
		}
		catch (exception ex)
		{
			tc.LogException(ex);
		}
	}
	catch (...)
	{
		tc.LogResult(RESULT_FAILED, "Unknown exception.  Is your destructor throwing an exception?");
	}
}


/**************************************/
void Constructor_PopFailsOnEmptyList()
{
	TestCase tc("Stack::Pop throws out_of_range on an empty list.");

	try
	{
		Stack<CounterClass> x;

		try
		{
			x.Pop();
			tc.LogResult(RESULT_FAILED, "Stack::Pop should not have succeeded on an empty list!");
		}
		catch (out_of_range ex)
		{
			tc.LogResult(RESULT_PASSED, "Caught a out_of_range exception, as expected.");
		}
		catch (...)
		{
			tc.LogResult(RESULT_FAILED, "Caught an unknown exception!");
		}
	}
	catch (...)
	{
		tc.LogResult(RESULT_FAILED, "Unknown exception.  Is your destructor throwing an exception?");
	}
}


/**************************************/
void Constructor_PeekFailsOnEmptyList()
{
	TestCase tc("Stack::Peek throws out_of_range on an empty list.");

	try
	{
		Stack<CounterClass> x;

		try
		{
			CounterClass item = x.Peek();
			tc.LogResult(RESULT_FAILED, "Stack::Peek should not have succeeded on an empty list!");
		}
		catch (out_of_range ex)
		{
			tc.LogResult(RESULT_PASSED, "Caught a out_of_range exception, as expected.");
		}
		catch (...)
		{
			tc.LogResult(RESULT_FAILED, "Caught an unknown exception!");
		}
	}
	catch (...)
	{
		tc.LogResult(RESULT_FAILED, "Unknown exception.  Is your destructor throwing an exception?");
	}
}


/**************************************/
void Constructor_ClearEmptyList()
{
	TestCase tc("Stack::Clear does nothing on an empty list.");

	try
	{
		Stack<CounterClass> x;

		try
		{
			x.Clear();
			tc.LogResult(RESULT_PASSED, "Stack::Clear worked with an empty list.");
			tc.AssertEquals(0, x.Count(), "Make sure size is zero.");
		}
		catch (exception ex)
		{
			tc.LogException(ex);
		}
	}
	catch (...)
	{
		tc.LogResult(RESULT_FAILED, "Unknown exception.  Is your destructor throwing an exception?");
	}
}


//##############################################################################
//###   Push()
//##############################################################################

/**************************************/
void Push_AddItemCheckCountAndDtor()
{
	TestCase tc("Push: add one item, check Count, and make sure ~Stack cleans up.");

	CounterClass::InstanceCount = 0;
	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));

		tc.AssertEquals(1, stack.Count(), "Count() returns 1 after inserting one item.");
		tc.Assert(CounterClass::InstanceCount == 1, "Verify one and only one instance of CounterClass after inserting.");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void Push_AddMultipleItems()
{
	TestCase tc("Push: add multiple items, check Count, and make sure dtor cleans up.");

	CounterClass::InstanceCount = 0;
	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));
		stack.Push(CounterClass(40));
		stack.Push(CounterClass(50));

		tc.AssertEquals(5, stack.Count(), "Count() returns 5 after inserting five items.");
		tc.AssertEquals(5, CounterClass::InstanceCount, "Verify five instances of CounterClass.");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void Peek_PeekAfterInsert()
{
	TestCase tc("Peek: peek after consecutive inserts.");

	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		tc.AssertEquals(1, stack.Count(), "Check count after inserting first item.");
		tc.AssertEquals(10, stack.Peek().Data, "Check start value after inserting first item.");
		stack.Push(CounterClass(20));
		tc.AssertEquals(2, stack.Count(), "Check count after inserting second item.");
		tc.AssertEquals(20, stack.Peek().Data, "Check start value after inserting second item.");
		stack.Push(CounterClass(30));
		tc.AssertEquals(3, stack.Count(), "Check count after inserting third item.");
		tc.AssertEquals(30, stack.Peek().Data, "Check start value after inserting third item.");
		stack.Push(CounterClass(40));
		tc.AssertEquals(4, stack.Count(), "Check count after inserting fourth item.");
		tc.AssertEquals(40, stack.Peek().Data, "Check start value after inserting fourth item.");
		stack.Push(CounterClass(50));
		tc.AssertEquals(5, stack.Count(), "Check count after inserting fifth item.");
		tc.AssertEquals(50, stack.Peek().Data, "Check start value after inserting fifth item.");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


//##############################################################################
//###   Pop()
//##############################################################################

/**************************************/
void Pop_PopOneByOne()
{
	TestCase tc("Pop: pop items one by one.");

	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));
		stack.Push(CounterClass(40));
		stack.Push(CounterClass(50));

		tc.AssertEquals(5, stack.Count(), "Count() returns 5 after inserting five items.");
		tc.AssertEquals(5, CounterClass::InstanceCount, "Verify five instances of CounterClass.");
		tc.AssertEquals(50, stack.Peek().Data, "Check LIFO value at head of list.");
		stack.Pop();
		tc.AssertEquals(4, stack.Count(), "Count() returns 4 items.");
		tc.AssertEquals(4, CounterClass::InstanceCount, "Verify 4 instances of CounterClass.");
		tc.AssertEquals(40, stack.Peek().Data, "Check LIFO value at head of list.");
		stack.Pop();
		tc.AssertEquals(3, stack.Count(), "Count() returns 3 items.");
		tc.AssertEquals(3, CounterClass::InstanceCount, "Verify 3 instances of CounterClass.");
		tc.AssertEquals(30, stack.Peek().Data, "Check LIFO value at head of list.");
		stack.Pop();
		tc.AssertEquals(2, stack.Count(), "Count() returns 2 items.");
		tc.AssertEquals(2, CounterClass::InstanceCount, "Verify 2 instances of CounterClass.");
		tc.AssertEquals(20, stack.Peek().Data, "Check LIFO value at head of list.");
		stack.Pop();
		tc.AssertEquals(1, stack.Count(), "Count() returns 1 items.");
		tc.AssertEquals(1, CounterClass::InstanceCount, "Verify 1 instances of CounterClass.");
		tc.AssertEquals(10, stack.Peek().Data, "Check LIFO value at head of list.");
		stack.Pop();
		tc.AssertEquals(0, stack.Count(), "Count() returns 0 items.");
		tc.AssertEquals(0, CounterClass::InstanceCount, "Verify 0 instances of CounterClass.");
		try
		{
			stack.Peek();
			tc.LogResult(RESULT_FAILED, "Peek should have thrown an exception for an empty list.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "Peek threw an exception on an empty list, as expected.");
		}
		try
		{
			stack.Pop();
			tc.LogResult(RESULT_FAILED, "Pop should have thrown an exception for an empty list.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "Pop threw an exception on an empty list, as expected.");
		}
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void Clear_HappyPath()
{
	TestCase tc("Clear: add multiple items, then clear and validate cleanup.");

	CounterClass::InstanceCount = 0;
	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));
		stack.Push(CounterClass(40));
		stack.Push(CounterClass(50));

		tc.AssertEquals(5, stack.Count(), "Count() returns 5 after inserting five items.");
		tc.AssertEquals(5, CounterClass::InstanceCount, "Verify five instances of CounterClass.");

		stack.Clear();
		tc.LogResult(RESULT_PASSED, "Cleared the contents of the list.");

		tc.AssertEquals(0, stack.Count(), "Count() returns 0 after clearing the list.");
		tc.AssertEquals(0, CounterClass::InstanceCount, "Verify zero instances of CounterClass.");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void Clear_PeekAgain()
{
	TestCase tc("Clear: add multiple items, then clear and make sure they're gone.");

	CounterClass::InstanceCount = 0;
	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));
		stack.Push(CounterClass(40));
		stack.Push(CounterClass(50));

		tc.AssertEquals(5, stack.Count(), "Count() returns 5 after inserting five items.");
		tc.AssertEquals(5, CounterClass::InstanceCount, "Verify five instances of CounterClass.");

		stack.Clear();
		tc.LogResult(RESULT_PASSED, "Cleared the contents of the list.");


		try
		{
			stack.PeekAt(0);
			tc.LogResult(RESULT_FAILED, "PeekAt(0) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "PeekAt(0) threw an exception.");
		}

		try
		{
			stack.PeekAt(4);
			tc.LogResult(RESULT_FAILED, "PeekAt(4) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "PeekAt(4) threw an exception.");
		}
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void PeekAt_HappyPath()
{
	TestCase tc("PeekAt: add five items, then peek at them one by one.");

	CounterClass::InstanceCount = 0;
	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));
		stack.Push(CounterClass(40));
		stack.Push(CounterClass(50));

		tc.AssertEquals(5, stack.Count(), "Count() returns 5 after inserting five items.");
		tc.AssertEquals(5, CounterClass::InstanceCount, "Verify five instances of CounterClass.");

		tc.AssertEquals(50, stack.PeekAt(0).Data, "Check PeekAt(0).");
		tc.AssertEquals(40, stack.PeekAt(1).Data, "Check PeekAt(1).");
		tc.AssertEquals(30, stack.PeekAt(2).Data, "Check PeekAt(2).");
		tc.AssertEquals(20, stack.PeekAt(3).Data, "Check PeekAt(3).");
		tc.AssertEquals(10, stack.PeekAt(4).Data, "Check PeekAt(4).");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void PeekAt_BeyondEndOfList()
{
	TestCase tc("PeekAt: add five items, then peek beyond the end of the list.");

	CounterClass::InstanceCount = 0;
	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));
		stack.Push(CounterClass(40));
		stack.Push(CounterClass(50));

		tc.AssertEquals(5, stack.Count(), "Count() returns 5 after inserting five items.");
		tc.AssertEquals(5, CounterClass::InstanceCount, "Verify five instances of CounterClass.");

		try
		{
			stack.PeekAt(5);
			tc.LogResult(RESULT_FAILED, "PeekAt(5) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "PeekAt(5) threw an exception.");
		}

		try
		{
			stack.PeekAt(100);
			tc.LogResult(RESULT_FAILED, "PeekAt(100) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "PeekAt(100) threw an exception.");
		}
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


//##############################################################################
//###   InsertAt()
//##############################################################################

/**************************************/
void InsertAt_Head()
{
	TestCase tc("InsertAt: starting at the head of the list.");

	try
	{
		Stack<CounterClass> stack;
		stack.InsertAt(CounterClass(10), 0);
		stack.InsertAt(CounterClass(20), 0);
		stack.InsertAt(CounterClass(30), 0);

		tc.AssertEquals(3, stack.Count(), "Count() returns 3 after inserting three items.");
		tc.AssertEquals(3, CounterClass::InstanceCount, "Verify three instances of CounterClass.");

		tc.AssertEquals(30, stack.PeekAt(0).Data, "Check value of the first item.");
		tc.AssertEquals(20, stack.PeekAt(1).Data, "Check value of the second item.");
		tc.AssertEquals(10, stack.PeekAt(2).Data, "Check value of the third item.");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void InsertAt_Tail()
{
	TestCase tc("InsertAt: starting at the tail of the list.");

	try
	{
		Stack<CounterClass> stack;
		stack.InsertAt(CounterClass(10), 0);
		stack.InsertAt(CounterClass(20), 1);
		stack.InsertAt(CounterClass(30), 2);

		tc.AssertEquals(3, stack.Count(), "Count() returns 3 after inserting three items.");
		tc.AssertEquals(3, CounterClass::InstanceCount, "Verify three instances of CounterClass.");

		tc.AssertEquals(10, stack.PeekAt(0).Data, "Check value of the first item.");
		tc.AssertEquals(20, stack.PeekAt(1).Data, "Check value of the second item.");
		tc.AssertEquals(30, stack.PeekAt(2).Data, "Check value of the third item.");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void InsertAt_Middle()
{
	TestCase tc("InsertAt: starting in the middle of the list.");

	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));

		tc.AssertEquals(3, stack.Count(), "Count() returns 3 after inserting three items.");
		tc.AssertEquals(3, CounterClass::InstanceCount, "Verify three instances of CounterClass.");

		stack.InsertAt(CounterClass(40), 1);
		tc.LogResult(RESULT_PASSED, "Insert 40 at position 1.");
		stack.InsertAt(CounterClass(50), 3);
		tc.LogResult(RESULT_PASSED, "Insert 50 at position 3.");

		tc.AssertEquals(30, stack.PeekAt(0).Data, "Check value of the first item.");
		tc.AssertEquals(40, stack.PeekAt(1).Data, "Check value of the second item.");
		tc.AssertEquals(20, stack.PeekAt(2).Data, "Check value of the third item.");
		tc.AssertEquals(50, stack.PeekAt(3).Data, "Check value of the fourth item.");
		tc.AssertEquals(10, stack.PeekAt(4).Data, "Check value of the fifth item.");
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void InsertAt_BeyondEndEmpty()
{
	TestCase tc("InsertAt: starting beyond the tail an empty list.");

	try
	{
		Stack<CounterClass> stack;
		try
		{
			stack.InsertAt(CounterClass(10), 1);
			tc.LogResult(RESULT_FAILED, "InsertAt(x, 1) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "InsertAt(x, 1) threw an exception.");
		}

		try
		{
			stack.InsertAt(CounterClass(10), 100);
			tc.LogResult(RESULT_FAILED, "InsertAt(x, 100) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "InsertAt(x, 100) threw an exception.");
		}
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}


/**************************************/
void InsertAt_BeyondEndNotEmpty()
{
	TestCase tc("InsertAt: starting beyond the tail a non-empty list.");

	try
	{
		Stack<CounterClass> stack;
		stack.Push(CounterClass(10));
		stack.Push(CounterClass(20));
		stack.Push(CounterClass(30));

		tc.AssertEquals(3, stack.Count(), "Count() returns 3 after inserting three items.");
		tc.AssertEquals(3, CounterClass::InstanceCount, "Verify three instances of CounterClass.");
		
		try
		{
			stack.InsertAt(CounterClass(99), 4);
			tc.LogResult(RESULT_FAILED, "InsertAt(x, 4) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "InsertAt(x, 4) threw an exception.");
		}

		try
		{
			stack.InsertAt(CounterClass(99), 100);
			tc.LogResult(RESULT_FAILED, "InsertAt(x, 100) should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(RESULT_PASSED, "InsertAt(x, 100) threw an exception.");
		}
	}
	catch (exception ex)
	{
		tc.LogException(ex);
	}

	tc.Assert(CounterClass::InstanceCount == 0, "Verify zero instances of CounterClass after list is destroyed.");
}




//##############################################################################
//###   main
//##############################################################################

/**************************************/
int main()
{
	try
	{
		TestCase::PrintBanner("Constructor tests");
		Constructor_Basic();
		Constructor_SizeIsZero();
		Constructor_PopFailsOnEmptyList();
		Constructor_PeekFailsOnEmptyList();

		TestCase::PrintBanner("Push() and ~Stack()");
		Push_AddItemCheckCountAndDtor();
		Push_AddMultipleItems();

		TestCase::PrintBanner("Stack funcitonality");
		Peek_PeekAfterInsert();
		Pop_PopOneByOne();
		Clear_HappyPath();
		Clear_PeekAgain();
		PeekAt_HappyPath();
		PeekAt_BeyondEndOfList();

		TestCase::PrintBanner("InsertAt");
		InsertAt_Head();
		InsertAt_Tail();
		InsertAt_Middle();
		InsertAt_BeyondEndEmpty();
		InsertAt_BeyondEndNotEmpty();

		TestCase::PrintSummary();
	}
	catch (...)
	{
		cout << "Unhandled exception.  Test run aborted (no score)." << endl;
	}
    return 0 ;
}
