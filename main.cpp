#include <boost/hana.hpp>
#include <iostream>
#include <string>

#include "finite_automata.hpp"

int main() {
	using namespace boost::hana::literals;

	constexpr auto m1_q1 =
		fa::make_state(1_c, boost::hana::false_c,
					   fa::make_transition(boost::hana::char_c<'a'>, 2_c),
					   fa::make_transition(boost::hana::char_c<'b'>, 1_c));
	constexpr auto m1_q2 =
		fa::make_state(2_c, boost::hana::true_c,
					   fa::make_transition(boost::hana::char_c<'a'>, 3_c),
					   fa::make_transition(boost::hana::char_c<'b'>, 3_c));
	constexpr auto m1_q3 =
		fa::make_state(3_c, boost::hana::false_c,
					   fa::make_transition(boost::hana::char_c<'a'>, 2_c),
					   fa::make_transition(boost::hana::char_c<'b'>, 1_c));

	constexpr auto machine1 = fa::make_machine(1_c, m1_q1, m1_q2, m1_q3);
	constexpr auto result1 = fa::run(BOOST_HANA_STRING("aabb"), machine1);

	std::cout << std::boolalpha << boost::hana::first(result1) << ' '
			  << boost::hana::second(result1) << '\n';

	constexpr auto m2_q1 =
		fa::make_state(1_c, boost::hana::true_c,
					   fa::make_transition(boost::hana::char_c<'a'>, 1_c),
					   fa::make_transition(boost::hana::char_c<'b'>, 2_c));
	constexpr auto m2_q2 =
		fa::make_state(2_c, boost::hana::false_c,
					   fa::make_transition(boost::hana::char_c<'a'>, 3_c),
					   fa::make_transition(boost::hana::char_c<'b'>, 4_c));
	constexpr auto m2_q3 =
		fa::make_state(3_c, boost::hana::false_c,
					   fa::make_transition(boost::hana::char_c<'a'>, 2_c),
					   fa::make_transition(boost::hana::char_c<'b'>, 4_c));
	constexpr auto m2_q4 =
		fa::make_state(4_c, boost::hana::true_c,
					   fa::make_transition(boost::hana::char_c<'a'>, 3_c),
					   fa::make_transition(boost::hana::char_c<'b'>, 4_c));
	constexpr auto machine2 = fa::make_machine(1_c, m2_q1, m2_q2, m2_q3, m2_q4);
	constexpr auto result2 = fa::run(BOOST_HANA_STRING("aabb"), machine2);
	std::cout << std::boolalpha << boost::hana::first(result2) << ' '
			  << boost::hana::second(result2) << '\n';
}
