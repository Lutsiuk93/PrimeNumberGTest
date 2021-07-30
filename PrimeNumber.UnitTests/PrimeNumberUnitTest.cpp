#include <PrimeNumber.Core/PrimeNumberCalculator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>

using namespace ::testing;

class PrimeNumberTest : public TestWithParam<std::tuple<int, std::vector<int>>>
{
protected:
	PrimeNumberCalculator<int> calc;
};

//-----------------------------------------------------------------------------------------------------------------------------------------
//Use TEST_F to have common setup for some unit tests
TEST_F(PrimeNumberTest, ValuesTill_4)
{
	auto expected = calc.GetPrimeNumbers(4);
	EXPECT_THAT(expected, ElementsAre(2, 3));
}

TEST_F(PrimeNumberTest, ValuesTill_15)
{
	auto expected = calc.GetPrimeNumbers(15);
	EXPECT_THAT(expected, ElementsAre(2, 3, 5, 7, 11, 13));
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//Use TEST_P to unify multiple tests with similar checks
using intV = std::vector<int>;

TEST_P(PrimeNumberTest, inVector)
{
	auto expected = std::get<1>(GetParam());
	auto result = calc.GetPrimeNumbers(std::get<0>(GetParam()));
	EXPECT_THAT(expected, ElementsAreArray(result.begin(), result.end()));
}

INSTANTIATE_TEST_SUITE_P(MultiInVectorTest, PrimeNumberTest,
	Values
	(
		std::make_tuple(4, intV{ 2, 3 }), 
		std::make_tuple(15, intV{ 2, 3, 5, 7, 11, 13 })
	)
);

//-----------------------------------------------------------------------------------------------------------------------------------------
//It should work at least for size_t, int, double, std::string, std::wstring.Use TYPED_TEST to test it.
template <typename T>
using TypedParam = std::tuple<int, std::vector<T>>;

static std::tuple<TypedParam<size_t>, TypedParam<int>, TypedParam<double>, TypedParam<std::string>, TypedParam<std::wstring>>testData
{
	std::make_tuple(15, std::vector<size_t>{ 2, 3, 5, 7, 11, 13 }),
	std::make_tuple(25, std::vector<int>{ 2, 3, 5, 7, 11, 13, 17, 19, 23 }),
	std::make_tuple(40, std::vector<double>{ 2., 3., 5., 7., 11., 13., 17., 19., 23., 29., 31., 37. }),
	std::make_tuple(7, std::vector<std::string>{ "2", "3", "5", "7"}),
	std::make_tuple(15, std::vector<std::wstring>{ L"2", L"3", L"5", L"7", L"11", L"13"})
};

template <typename T>
class PrimeNumberTypedTest : public Test
{
public:
	PrimeNumberTypedTest()
		: data( std::get<TypedParam<T>>(testData)) {}

	PrimeNumberCalculator<T> calc;
	TypedParam<T> data;
};

TYPED_TEST_SUITE_P(PrimeNumberTypedTest);

TYPED_TEST_P(PrimeNumberTypedTest, TypedInVector)
{
	auto expected = std::get<1>(this->data);
	auto result = this->calc.GetPrimeNumbers(std::get<0>(this->data));
	EXPECT_THAT(expected, ElementsAreArray(result.begin(), result.end()));
}

using MyTypes = Types<size_t, int, double, std::string, std::wstring>;
REGISTER_TYPED_TEST_SUITE_P(PrimeNumberTypedTest, TypedInVector);

INSTANTIATE_TYPED_TEST_SUITE_P(TypedTest, PrimeNumberTypedTest, MyTypes);