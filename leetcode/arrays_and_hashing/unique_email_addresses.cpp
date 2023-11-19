#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include <unordered_set>

using Param = std::tuple<std::vector<std::string>, int>;

class Solution1 : public testing::TestWithParam<Param> {
public:

    int numUniqueEmails(std::vector<std::string>& emails) {
        for (const auto& email : emails) {
            processEmail(email);
        }
        return emails_.size();
    }
protected:
    std::unordered_set<std::string> emails_;
    void obfuscateLocalName(std::string& localName) {
        if (std::size_t plusPos = localName.find('+'); plusPos != std::string::npos)
            localName = localName.substr(0, plusPos);
        std::size_t dotPos = localName.find('.');
        while (dotPos != std::string::npos) {
            localName.replace(dotPos, 1, "");
            dotPos = localName.find('.');
        }
    }
    void processEmail(const std::string& email) {
        std::size_t atPos = email.find('@');
        if (atPos == std::string::npos)
            return;
        std::string localName = email.substr(0, atPos);
        obfuscateLocalName(localName);
        std::string domainName = email.substr(atPos+1);
        emails_.insert(localName+"@"+domainName);
    }

};


// TODO: Typed test suite?
TEST_P(Solution1, TestCase1) {
    auto parameter = GetParam();
    auto emails = std::get<0>(parameter);
    auto expected = std::get<1>(parameter);
    EXPECT_EQ(expected, numUniqueEmails(emails));
}

static auto testCases = testing::Values(
        Param({"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"}, 2),
        Param({"a@leetcode.com","b@leetcode.com","c@leetcode.com"}, 3)
        );

INSTANTIATE_TEST_SUITE_P(TestSolution, Solution1, testCases);

