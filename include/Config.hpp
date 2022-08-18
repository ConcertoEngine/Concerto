//
// Created by arthur on 01/08/2022.
//

#ifndef CONCERTO_CONFIG_HPP
#define CONCERTO_CONFIG_HPP
#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <type_traits>
#include <memory>

namespace Concerto::Config {
	struct nullNode {};
	struct Node;

	using NodePtr = std::shared_ptr<Node>;

	template<typename T, typename Allocator = std::allocator<T>>
	//requires std::is_same_v<std::pair<std::string, NodePtr>, T>
	class Vector : public std::vector<T, Allocator>
	{
	public:
		Node& operator[](const std::string &key)
		{
			auto obj =
					std::find_if(this->begin(), this->end(),
							[&key](const auto &pair) { return pair.first == key; });
			if (obj == this->end())
				throw std::out_of_range("Key not found: " + key);
			return *obj->second;
		}

		const Node& operator[](const std::string &key) const
		{
			auto obj =
					std::find_if(this->cbegin(), this->cend(),
							[&key](const auto &pair) { return pair.first == key; });
			if (obj == this->end())
				throw std::out_of_range("Key not found: " + key);
			return *obj->second;
		}
	};


	using Array = std::vector<NodePtr>;
/**
 * @brief std::unordered_map<std::string, NodePtr> is not used because we want
 * to conserve the insertion order
 **/
	using Object = Vector<std::pair<std::string, NodePtr>>;

	using Int32 = std::int32_t;
	using UInt32 = std::uint32_t;
	using Double = double;
	using Bool = bool;
	using String = std::string;

	using Variant =
			std::variant<Bool, Int32, UInt32, Double, Array, Object, String, nullNode>;
/**
 * @brief The Node class
 *
 * This class is the base class of all the nodes of the config file.
 **/
	struct Node {
	public:
		explicit Node(const Array &array) : _variant(array) {}
		explicit Node(const Object &object) : _variant(object) {}
		explicit Node(const String &str) : _variant(str) {}
		explicit Node(Bool b) : _variant(b) {}
		explicit Node(Int32 i) : _variant(i) {}
		explicit Node(UInt32 u) : _variant(u) {}
		explicit Node(Double d) : _variant(d) {}
		Node(Node &&) = default;
		/**
		* @brief Cast the node As T
		* @return The type of the node
		**/
		template <typename T> T &As() { return std::get<T>(_variant); }

		/**
		* @brief Cast the node As const T
		* @return The type of the node
		**/
		template <typename T> [[nodiscard]] const T &As() const { return std::get<T>(_variant); }

		/**
		* @brief Cast the node As an Object
		* @return The node contained at key
		**/
		Node &operator[](const String &key) const {
			auto node =
					std::find_if(As<Object>().begin(), As<Object>().end(),
							[&key](const auto &pair) { return pair.first == key; });
			if (node == As<Object>().end())
				throw std::out_of_range("Key not found: " + key);
			return *node->second;
		}

		/**
		* @brief Cast the node As an Array
		* @return The node contained at index
		**/
		Node &operator[](std::size_t index) const { return *As<Array>().at(index); }

	private:
		Variant _variant;
	};
} // namespace Config
#endif //CONCERTO_CONFIG_HPP
