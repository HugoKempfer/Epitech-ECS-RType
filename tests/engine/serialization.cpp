#include <memory>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "engine/prelude.hpp"
#include "network/serialize.hpp"

Test(Serialization, simple)
{
	using namespace Engine::Network;

	enum Type {DAMN, WOW};
	struct Damn {
		int damn;
		float wow;
	};
	struct Wow {
		double foo;
		char bar;
	};

	World world;
	SerializationFactory<Type> factory(world.uuidCtx);
	factory.registerMember<Damn>(Type::DAMN);
	factory.registerMember<Wow>(Type::WOW);

	//Now test the serialization
	Damn damn = {4, 4.42};
	Wow wow = {23, 'V'};
	auto sdamn = factory.serialize<Damn>(damn);
	auto swow = factory.serialize<Wow>(wow);
	auto sthrow = factory.serialize<Wow>(wow);

	auto dsdamn = sdamn.decode<Damn>();
	cr_assert_eq(dsdamn.damn, damn.damn);
	cr_assert_eq(dsdamn.wow, damn.wow);
	auto dswow = swow.decode<Wow>();
	cr_assert_eq(dswow.foo, wow.foo);
	cr_assert_eq(dswow.bar, wow.bar);
	cr_assert_any_throw(sthrow.decode<Damn>());
}
