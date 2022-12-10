#include <string>
#include <map>
#include <string_view>


enum class HCKey {
	login = 0,
	signup,
	logout,
	profile,
	create_event,
	profile_settings,
	visit_event,
	events,
	size
};

std::map<std::string_view, HCKey> HCKeyMap{
	{"profile", HCKey::profile},
	{"events",  HCKey::events},
	{"auth/login",   HCKey::login},
	{"auth/logout", HCKey::logout},
	{"auth/signup", HCKey::signup},
	{"events/create", HCKey::create_event},
	{"profile/setting", HCKey::profile_settings},
	{"events/visit", HCKey::visit_event}
};

HCKey parseHCKey(const std::string &target) {
	auto it = target.begin();
	for (int i = 0; i < 3; it = std::find(it, target.end(), '/'), ++i);
	return HCKeyMap.at(target);
}

