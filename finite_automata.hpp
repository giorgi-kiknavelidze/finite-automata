#ifndef FINITE_AUTOMATA_HPP
#define FINITE_AUTOMATA_HPP 1
#include <boost/hana.hpp>

namespace fa {
namespace detail {
template <typename C, class T>
constexpr auto get_next_state(C c, T state) {
	using namespace boost::hana::literals;
	auto state_map = state[2_c];
	auto find_result = boost::hana::find(state_map, c);
	static_assert(find_result != boost::hana::nothing,
				  "transition not found in state");
	return state_map[c];
}

template <typename StateId, typename States>
constexpr auto get_state_by_id(StateId state_id, States states) {
	using namespace boost::hana::literals;
	const auto result = boost::hana::find_if(
		states, [state_id](auto state) { return state[0_c] == state_id; });
	return result.value();
};

template <typename StartStateId, typename String, typename States>
constexpr auto get_last_state(StartStateId start_state_id, String input,
							  States states) {
	using namespace boost::hana::literals;
	if constexpr (boost::hana::length(input) == boost::hana::size_c<0>) {
		return start_state_id;
	} else {
		const auto current_state = get_state_by_id(start_state_id, states);
		return get_last_state(
			get_next_state(input[0_c], current_state),
			boost::hana::drop_front_exactly(input, boost::hana::size_c<1>),
			states);
	}
}

}  // namespace detail
template <typename Char, typename Destination>
constexpr auto make_transition(Char c, Destination d) {
	return boost::hana::make_pair(c, d);
}

template <typename StateId, typename StateAccept, typename... Args>
constexpr auto make_state(StateId state_id, StateAccept state_accept,
						  Args... args) {
	return boost::hana::make_tuple(state_id, state_accept,
								   boost::hana::make_map(args...));
}

template <typename StartState, typename... States>
constexpr auto make_machine(StartState start_state_id, States... states) {
	return boost::hana::make_pair(start_state_id,
								  boost::hana::make_tuple(states...));
}

template <typename String, typename Machine>
constexpr auto run(String input, Machine machine) {
	using namespace boost::hana::literals;
	auto last_state_id = detail::get_last_state(
		boost::hana::first(machine), input, boost::hana::second(machine));
	auto ending_state =
		detail::get_state_by_id(last_state_id, boost::hana::second(machine));
	return boost::hana::make_pair(ending_state[1_c], last_state_id);
}

}  // namespace fa
#endif
