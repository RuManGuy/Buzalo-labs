#pragma once

#include <utility>
#include <list>
#include <string>
#include <optional>

using namespace std;

template <typename T>
class Dict
{
public:
	using Pair = pair<string, T>;
	using List = list<Pair>;
private:
	List* arr;

	int maxHashValue;

	unsigned int makeHash(string key) {
		unsigned long long sum = 0, t = 1;

		for (int i = 0; i < key.length(); i++) {
			sum += (int)key.at(i) * t;
			t *= 100;
		}

		return sum % maxHashValue;
	}
public:
	Dict() : Dict(10) {};
	Dict(int maxSize) {
		maxHashValue = maxSize;

		arr = new List[maxHashValue];

		for (int i = 0; i < maxHashValue; i++) {
			arr[i] = List();
		}
	}

	/*
		Если значение с ключом key уже есть, оно будет перезаписано
		Иначе просто добавлено
	*/
	void insert(string key, T value) {
		int h = makeHash(key);

		bool isExists = false;

		for (auto& pairOfList : arr[h]) {
			if (pairOfList.first == key) {
				pairOfList.second = value;

				isExists = true;
				break;
			}
		}

		if (!isExists) {
			arr[h].push_back(make_pair(key, value));
		}
	};

	optional<T> find(string key) {
		int h = makeHash(key);

		for (auto& pairOfList : arr[h]) {
			if (pairOfList.first == key) {
				return { pairOfList.second };
			}
		}

		return {};
	};

	optional<T> erase(string key) {
		int h = makeHash(key);

		for (auto& pairOfList : arr[h]) {
			if (pairOfList.first == key) {
				T t = pairOfList.second;

				// Удалить пару в которой первый элемент равен key
				arr[h].remove_if([key](Pair it) { return it.first == key; });

				return { t };
			}
		}

		return {};
	};

	List convertToList() {
		List tempList;

		for (int i = 0; i < maxHashValue; i++) {
			for (auto& pairOfList : arr[i]) {
				tempList.push_back(pairOfList);
			}
		}

		return tempList;
	}
};
