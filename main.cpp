#include <iostream>
#include <string>
#include <cmath>    // abs()

#include "TextReader.hpp"
using namespace std;

// Global static variables
static int testCount = 0;
static const int testTotal = 16;
static const string GREEN = "\033[32m";
static const string RED = "\033[31m";
static const string RESET = "\033[0m";

// Prototypes

template <typename T, typename U>
bool assertEquals(const string& nameOfTest, const T& expected, const U& actual);


template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual);




// Main
int main(int argc, char const *argv[]) {
    TextReader gen;
    assertEquals("'.' is Punctuation :", true, gen.isEndPunctuation('.'));
    assertEquals("'?' is Punctuation :", true, gen.isEndPunctuation('?'));
    assertEquals("'!' is Punctuation :", true, gen.isEndPunctuation('!'));
    assertEquals("'a' is Punctuation :", false, gen.isEndPunctuation('a'));

    TextReader Frankenstein;
    Frankenstein.readIn("Frankenstein or The Modern Prometheus by Mary Shelley.txt");

    {
        vector<string> expected = { "lovers,", "days", "lovers" };
        assertVectorEquals("Values : Frankenstein 'youthful'", expected, Frankenstein.getValues("youthful"));

        expected = { "out", "the", "the", "by", "in", "their", "on" };
        assertVectorEquals("Values : Frankenstein 'marked'", expected, Frankenstein.getValues("marked"));

        assertEquals("Value Count : Frankenstein '^' > 0: ", true, Frankenstein.getValues("^").size() > 10);
        
        assertEquals("Searching : Frankenstein 'rejoice' found", true, Frankenstein.search("rejoice"));

        assertEquals("Followers Count : Frankenstein 'breeze'", 8, Frankenstein.howManyfollowers("breeze"));
    
        assertEquals("Followers Count : Frankenstein 'river'", 9, Frankenstein.howManyfollowers("river"));
    }

    TextReader SleepyHollow;
    SleepyHollow.readIn("The Legend of Sleep Hollow by Washington Irving.txt");

    {
        vector<string> expected = { "hill,","crests", "dell," };
        assertVectorEquals("Values : SleepyHollow 'woody'", expected, SleepyHollow.getValues("woody"));

        expected = { "which", "of", "of" };
        assertVectorEquals("Values : SleepyHollow 'quarter'", expected, SleepyHollow.getValues("quarter"));

        assertEquals("Value Count : SleepyHollow '^' < 0", false, SleepyHollow.getValues("^").size() < 10);

        assertEquals("Searching : SleepyHollow 'complexity' found", false, SleepyHollow.search("complexity"));

        assertEquals("Followers Count : SleepyHollow 'complexity'", 0, SleepyHollow.howManyfollowers("complexity"));
        
        assertEquals("Followers Count : SleepyHollow 'river'", 2, SleepyHollow.howManyfollowers("river"));
        

    }
	

    cout << endl << testCount << " tests passed out of " << testTotal << " total tests" << endl
		<< 100.0 * (float)testCount / (float)testTotal << "/100" << endl;

	cin.get();
    return 0;
}

// Helper Functions


template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual) {
    if (expected.size() == actual.size()) {
        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != actual[i]) {
                // Red colored text
                cout << RED << "FAILED "
                     << RESET << nameOfTest << ": expected '" << expected[i] << "' but actually '" << actual[i] << "'" << endl;
                return false;
            }
        }

        // Green colored text
        cout << GREEN << "PASSED "
             << RESET << nameOfTest << ": expected and actual lists match: {";
        for (int i = 0; i < expected.size(); i++) {
            cout << " " << expected[i];
        }
        cout << " }" << endl;

        testCount++;
        return true;
    }

    // Red colored text
    cout << RED << "FAILED "
         << RESET << nameOfTest << ": expected size '" << expected.size() << "' but actually size is '" << actual.size() << "'" << endl;
    return false;
}



template <typename T, typename U>
bool assertEquals(const string& nameOfTest, const T& expected, const U& actual) {
    if (expected == actual) {
        // Green colored text
        cout << RESET << GREEN << "PASSED "
            << RESET << nameOfTest << GREEN << ": expected and actual '" << RESET << actual << GREEN << "'" << RESET << endl;
        testCount++;
        return true;
    }
    // Red colored text
    cout << RESET << RED << "FAILED "
        << RESET << nameOfTest << RED << ": expected '" << RESET << expected << RED << "' but actually '" << RESET << actual << RED << "'" << RESET << endl;
    return false;
}