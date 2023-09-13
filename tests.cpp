#include "tests.h"

// Utility function to check and report test results
void TestRunner::testResultTrue(bool condition, const std::string& testName) {
    totalTests++;
    if (condition) {
        std::cout << testName << " - Passed" << std::endl;
        passedTests++;
    }
    else {
        std::cout << testName << " - Failed" << std::endl;
        failedTests.push_back(testName);
    }
}


// Utility function to check and report test results
void TestRunner::testResultFalse(bool condition, const std::string& testName) {
    totalTests++;
    if (!condition) {
        std::cout << testName << " - Passed" << std::endl;
        passedTests++;
    }
    else {
        std::cout << testName << " - Failed" << std::endl;
        failedTests.push_back(testName);
    }
}

// Function to test the checkKingQueenRule
void TestRunner::testCheckKingQueenRule() {
    {
        Deck deck1, deck2;
        deck1.addCard(Kaart(KING, Spades));
        deck2.addCard(Kaart(QUEEN, Clubs));

        Player player1("Alice", deck1);
        Player player2("Bob", deck2);

        std::vector<Player> players = { player1, player2 };

        testResultTrue(checkKingQueenRule(players), "checkKingQueenRule test1");
    }

    // Test Case 2: Two players with a King and Queen in the same deck.
    {
        Deck deck1, deck2;
        deck1.addCard(Kaart(KING, Spades));
        deck1.addCard(Kaart(QUEEN, Clubs));
        deck2.addCard(Kaart(ACE, Diamonds)); // No King or Queen

        Player player1("Alice", deck1);
        Player player2("Bob", deck2);

        std::vector<Player> players = { player1, player2 };

        testResultFalse(checkKingQueenRule(players), "checkKingQueenRule test2");
    }

    // Test Case 3: Three players with a King in one deck and a Queen in another.
    {
        Deck deck1, deck2, deck3;
        deck1.addCard(Kaart(KING, Spades));
        deck2.addCard(Kaart(ACE, Diamonds)); // No King or Queen
        deck3.addCard(Kaart(QUEEN, Clubs));

        Player player1("Alice", deck1);
        Player player2("Bob", deck2);
        Player player3("Charlie", deck3);

        std::vector<Player> players = { player1, player2, player3 };

        testResultTrue(checkKingQueenRule(players), "checkKingQueenRule test3");
    }
}

int TestRunner::runAutomatedTestCases() {
    // Run the tests
    testCheckKingQueenRule();

    // Print a summary
    std::cout << std::endl << std::endl << "Summary: " << passedTests << " out of " << totalTests << " tests passed." << std::endl;

    // Print the list of failed tests
    if (!failedTests.empty()) {
        std::cout << std::endl << std::endl << "Failed Tests:" << std::endl;
        for (const std::string& testName : failedTests) {
            std::cout << "  " << testName << std::endl;
        }
    }
    return 0;
}