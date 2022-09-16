#pragma once
#include"core/meta/json.h"
#include"core/base/basis.h"
#include"core/log/debuger.h"

inline void traverse(const Json& js, const string& bef) {
	if (js.is_bool())debug << bef << "Bool: " << js.bool_value() << endl;
	ef(js.is_number())debug << bef << "Number: " << js.number_value() << endl;
	ef(js.is_null())debug << bef << "Null" << endl;
	ef(js.is_string())debug << bef << "String: " << js.string_value() << endl;
	ef(js.is_object()) {
		debug << bef << "______Object begin______" << endl;
		auto& m = js.object_items();
		for (auto& y : m) {
			debug << bef << "AttrName: " << y.first << endl << bef << "Value:\n";
			traverse(y.second, bef + "     ");
			debug << bef << "END AttrName: " << y.first << endl;
		}
		debug << bef << "______Object end______" << endl;
	}
	ef(js.is_array()) {
		debug << bef << "______Array begin_______" << endl;
		auto& array = js.array_items();
		for (auto& y : array) {
			traverse(y, bef + "     ");
		}
		debug << bef << "______Array begin_______" << endl;
	}

}