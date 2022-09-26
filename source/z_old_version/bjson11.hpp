/* bJson11
 *
 * bJson11 is a tiny bJson library for C++11, providing bJson parsing and serialization.
 *
 * The core object provided by the library is bJson11::bJson. A bJson object represents any bJson
 * value: null, bool, number (int or double), string (std::string), array (std::vector), or
 * object (std::map).
 *
 * bJson objects act like values: they can be assigned, copied, moved, compared for equality or
 * order, etc. There are also helper methods bJson::dump, to serialize a bJson to a string, and
 * bJson::parse (static) to parse a std::string as a bJson object.
 *
 * Internally, the various types of bJson object are represented by the bJsonValue class
 * hierarchy.
 *
 * A note on numbers - bJson specifies the syntax of number formatting but not its semantics,
 * so some bJson implementations distinguish between integers and floating-point numbers, while
 * some don't. In bJson11, we choose the latter. Because some bJson implementations (namely
 * Javascript itself) treat all numbers as the same type, distinguishing the two leads
 * to bJson that will be *silently* changed by a round-trip through those implementations.
 * Dangerous! To avoid that risk, bJson11 stores all numbers as double internally, but also
 * provides integer helpers.
 *
 * Fortunately, double-precision IEEE754 ('double') can precisely store any integer in the
 * range +/-2^53, which includes every 'int' on most systems. (Timestamps often use int64
 * or long long to avoid the Y2038K problem; a double storing microseconds since some epoch
 * will be exact for +/- 275 years.)
 */

 /* Copyright (c) 2013 Dropbox, Inc.
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <initializer_list>
#include "core/base/basis.h"

#ifdef _MSC_VER
#if _MSC_VER <= 1800 // VS 2013
#ifndef noexcept
#define noexcept throw()
#endif

#ifndef snprintf
#define snprintf _snprintf_s
#endif
#endif
#endif




namespace bJson11 {

	enum bJsonParse {
		STANDARD, COMMENTS
	};

	class bJsonValue;

	class bJson final {
	public:
		// Types
		enum Type {
			NUL, NUMBER, BOOL, STRING, ARRAY, OBJECT
		};

		// Array and object typedefs
		typedef std::vector<bJson> array;
		typedef std::map<std::string, bJson> object;

		// Constructors for the various types of bJson value.
		bJson() noexcept;                // NUL
		bJson(std::nullptr_t) noexcept;  // NUL
		bJson(double value);             // NUMBER
		bJson(int value);                // NUMBER
		bJson(bool value);               // BOOL
		bJson(const std::string& value); // STRING
		bJson(std::string&& value);      // STRING
		bJson(const char* value);       // STRING
		bJson(const array& values);      // ARRAY
		bJson(array&& values);           // ARRAY
		bJson(const object& values);     // OBJECT
		bJson(object&& values);          // OBJECT

		// Implicit constructor: anything with a to_bJson() function.
		template <class T, class = decltype(&T::to_bJson)>
		bJson(const T& t) : bJson(t.to_bJson()) {}

		// Implicit constructor: map-like objects (std::map, std::unordered_map, etc)
		template <class M, typename std::enable_if<
			std::is_constructible<std::string, decltype(std::declval<M>().begin()->first)>::value
			&& std::is_constructible<bJson, decltype(std::declval<M>().begin()->second)>::value,
			int>::type = 0>
			bJson(const M& m) : bJson(object(m.begin(), m.end())) {}

		// Implicit constructor: vector-like objects (std::list, std::vector, std::set, etc)
		template <class V, typename std::enable_if<
			std::is_constructible<bJson, decltype(*std::declval<V>().begin())>::value,
			int>::type = 0>
			bJson(const V& v) : bJson(array(v.begin(), v.end())) {}

		// This prevents bJson(some_pointer) from accidentally producing a bool. Use
		// bJson(bool(some_pointer)) if that behavior is desired.
		bJson(void*) = delete;

		// Accessors
		Type type() const;

		bool is_null()   const { return type() == NUL; }
		bool is_number() const { return type() == NUMBER; }
		bool is_bool()   const { return type() == BOOL; }
		bool is_string() const { return type() == STRING; }
		bool is_array()  const { return type() == ARRAY; }
		bool is_object() const { return type() == OBJECT; }

		// Return the enclosed value if this is a number, 0 otherwise. Note that bJson11 does not
		// distinguish between integer and non-integer numbers - number_value() and int_value()
		// can both be applied to a NUMBER-typed object.
		double number_value() const;
		int int_value() const;

		// Return the enclosed value if this is a boolean, false otherwise.
		bool bool_value() const;
		// Return the enclosed string if this is a string, "" otherwise.
		const std::string& string_value() const;
		// Return the enclosed std::vector if this is an array, or an empty vector otherwise.
		const array& array_items() const;
		// Return the enclosed std::map if this is an object, or an empty map otherwise.
		const object& object_items() const;

		// Return a reference to arr[i] if this is an array, bJson() otherwise.
		const bJson& operator[](size_t i) const;
		// Return a reference to obj[key] if this is an object, bJson() otherwise.
		const bJson& operator[](const std::string& key) const;

		// Serialize.
		void dump(darray& out) const;
		darray dump() const {
			darray out;
			dump(out);
			return out;
		}

		// Parse. If parse fails, return bJson() and assign an error message to err.
		static bJson parse(const std::string& in,
			std::string& err,
			bJsonParse strategy = bJsonParse::STANDARD);
		static bJson parse(const char* in,
			std::string& err,
			bJsonParse strategy = bJsonParse::STANDARD) {
			if (in) {
				return parse(std::string(in), err, strategy);
			}
			else {
				err = "null input";
				return nullptr;
			}
		}
		// Parse multiple objects, concatenated or separated by whitespace
		static std::vector<bJson> parse_multi(
			const std::string& in,
			std::string::size_type& parser_stop_pos,
			std::string& err,
			bJsonParse strategy = bJsonParse::STANDARD);

		static inline std::vector<bJson> parse_multi(
			const std::string& in,
			std::string& err,
			bJsonParse strategy = bJsonParse::STANDARD) {
			std::string::size_type parser_stop_pos;
			return parse_multi(in, parser_stop_pos, err, strategy);
		}

		bool operator== (const bJson& rhs) const;
		bool operator<  (const bJson& rhs) const;
		bool operator!= (const bJson& rhs) const { return !(*this == rhs); }
		bool operator<= (const bJson& rhs) const { return !(rhs < *this); }
		bool operator>  (const bJson& rhs) const { return  (rhs < *this); }
		bool operator>= (const bJson& rhs) const { return !(*this < rhs); }

		/* has_shape(types, err)
		 *
		 * Return true if this is a bJson object and, for each item in types, has a field of
		 * the given type. If not, return false and set err to a descriptive message.
		 */
		typedef std::initializer_list<std::pair<std::string, Type>> shape;
		bool has_shape(const shape& types, std::string& err) const;

	private:
		std::shared_ptr<bJsonValue> m_ptr;
	};

	// Internal class hierarchy - bJsonValue objects are not exposed to users of this API.
	class bJsonValue {
	protected:
		friend class bJson;
		friend class bJsonInt;
		friend class bJsonDouble;
		virtual bJson::Type type() const = 0;
		virtual bool equals(const bJsonValue* other) const = 0;
		virtual bool less(const bJsonValue* other) const = 0;
		virtual void dump(darray& out) const = 0;
		virtual double number_value() const;
		virtual int int_value() const;
		virtual bool bool_value() const;
		virtual const std::string& string_value() const;
		virtual const bJson::array& array_items() const;
		virtual const bJson& operator[](size_t i) const;
		virtual const bJson::object& object_items() const;
		virtual const bJson& operator[](const std::string& key) const;
		virtual ~bJsonValue() {}
	};

} // namespace bJson11
