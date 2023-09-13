#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Kaart.h"
#include "logic.h"
#include "Player.h"
#include "Table.h"

class TestRunner {
	int passedTests = 0;
	int totalTests = 0;
	std::vector<std::string> failedTests;
public:
	int runAutomatedTestCases();
private:
	void testResultTrue(bool condition, const std::string& testName); // Utility function to check and report test results
	void testResultFalse(bool condition, const std::string& testName); // Utility function to check and report test results
	void testCheckKingQueenRule(); // Function to test the checkKingQueenRule
};