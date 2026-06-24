#pragma once
#include <string>
#include <cstdint>

#include "crt.hpp"

class fname {
public:
	fname() : comparison_index(std::uint32_t()), number(std::int32_t()) {};
	fname(std::uint32_t index) : comparison_index(index), number(std::int32_t()) {};

public:
	std::uint32_t comparison_index;
	std::int32_t number;
};

class fkey {
public:
	fkey() : name() {}
	fkey(fname name) : name(name) {}

public:
	fname name;
	std::uint8_t details[24] = {};
};

class ftextdata {
public:
	char pad_0[0x30];
	wchar_t* name;
	__int32 length;
};

class ftext {
public:
	ftextdata* data;
	char pad_0[0x10];

	wchar_t* c_str() const {
		if (this->data) {
			return data->name;
		}

		return nullptr;
	}
};

template <class type>
struct tarray2 {
public:
	tarray2() { this->data = nullptr; this->count = this->max = 0; };
	tarray2(type* dataPtr, int count, int max) {
		this->data = dataPtr;
		this->count = count;
		this->max = max;
	}

	type* data;
	std::int32_t count, max;

	type& operator[](int i) {
		return this->data[i];
	};

	int size() {
		return this->count;
	}


	int Num() const
	{
		return this->count;
	}



	bool IsValidIndex(std::int32_t index) const
	{
		return index < Num();
	}

	bool valid(int i) {
		return bool(i < this->count);
	}

	void add(const type& item) {
		if (count >= max) {
			std::int32_t new_max = (max == 0) ? 1 : max * 2;
			type* new_data = (type*)::operator new[](new_max * sizeof(type));
			if (data) {
				memcpy(new_data, data, count * sizeof(type));
				::operator delete[](data);
			}
			data = new_data;
			max = new_max;
		}
		data[count++] = item;
	}


	void Add(const type& value)
	{
		if (count >= max) // Expand
		{
			std::int32_t newMax = (max == 0) ? 1 : max * 2;
			type* newData = new type[newMax];
			for (std::int32_t i = 0; i < count; i++)
				newData[i] = data[i];
			delete[] data;
			data = newData;
			max = newMax;
		}
		data[count++] = value;
	}


	void Remove(const type& item) {
		for (int i = 0; i < count; i++) {
			if (data[i] == item) {
				for (int j = i; j < count - 1; j++)
					data[j] = data[j + 1];
				count--;
				return;
			}
		}
	}

	void Empty() {
		delete[] data;
		data = nullptr;
		count = 0;
		max = 0;
	}


	type* begin() const { return data; }
	type* end() const { return data + count; }
};


template<typename T>
struct tarray {
public:
	tarray() : data(nullptr), count(0), maxCount(0) {}
	T* data;
	std::int32_t count;
	std::int32_t maxCount;

	T& operator[](std::int32_t i) {
		return this->data[i];
	}
	const T& operator[](std::int32_t i) const {
		return this->data[i];
	}
	std::int32_t Num() const {
		return count;
	}
	std::int32_t size() const {
		return count;
	}
	bool IsValidIndex(std::int32_t i) const {
		return i >= 0 && i < count && data != nullptr;
	}
	bool IsEmpty() const {
		return count <= 0;
	}
	T* GetData() const {
		return data;
	}
	T* GetPtr(std::int32_t i) const {
		return IsValidIndex(i) ? &data[i] : nullptr;
	}

	// ========== MÉTHODES AJOUTÉES ==========
	void add(const T& element) {
		if (count >= maxCount) {
			// Réallocation automatique
			std::int32_t newMax = (maxCount == 0) ? 4 : maxCount * 2;
			T* newData = new T[newMax];
			for (std::int32_t i = 0; i < count; i++)
				newData[i] = data[i];
			delete[] data;
			data = newData;
			maxCount = newMax;
		}
		data[count++] = element;
	}

	// Méthode Add (avec majuscule)
	void Add(const T& element) {
		add(element);
	}

	void push_back(const T& element) {
		add(element);
	}
	void remove(std::int32_t index) {
		if (!IsValidIndex(index)) return;
		for (std::int32_t i = index; i < count - 1; i++) {
			data[i] = data[i + 1];
		}
		count--;
	}
	void clear() {
		count = 0;
	}
	bool contains(const T& element) const {
		for (std::int32_t i = 0; i < count; i++) {
			if (data[i] == element) return true;
		}
		return false;
	}
	std::int32_t find(const T& element) const {
		for (std::int32_t i = 0; i < count; i++) {
			if (data[i] == element) return i;
		}
		return -1;
	}
};

class fstring : public tarray<wchar_t>
{
public:
	inline fstring()
	{
	};
	fstring(const wchar_t* other)
	{
		maxCount = count = *other ? static_cast<int>(crt::wcslen(other)) + 1 : 0;
		if (count)
		{
			data = const_cast<wchar_t*>(other);
		}
	};
	fstring(const wchar_t* other, int count)
	{
		data = const_cast<wchar_t*>(other);
		maxCount = count = count;
	};

	// AJOUTEZ CES OPÉRATEURS :
	bool operator<(const fstring& other) const
	{
		// Gérer les cas de pointeurs nuls
		if (!data && !other.data) return false;
		if (!data) return true;
		if (!other.data) return false;

		// Comparaison lexicographique
		return crt::wcscmp(data, other.data) < 0;
	}

	bool operator==(const fstring& other) const
	{
		// Gérer les cas de pointeurs nuls
		if (!data && !other.data) return true;
		if (!data || !other.data) return false;

		return crt::wcscmp(data, other.data) == 0;
	}

	bool operator!=(const fstring& other) const
	{
		return !(*this == other);
	}
	// FIN DES AJOUTS

	bool is_valid() const
	{
		return data != nullptr;
	}
	const wchar_t* wide() const
	{
		return data;
	}
	const wchar_t* c_str() const
	{
		return this->data;
	}
	std::string ToString() const
	{
		auto length = std::wcslen(data);
		std::string str(length, '\0');
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(data, data + length, '?', &str[0]);
		return str;
	}
	std::string to_str() const
	{
		auto length = crt::wcslen(data);
		std::string str(length, '\0');
		for (size_t i = 0; i < length; ++i) {
			wchar_t wc = data[i];
			if (wc >= 0 && wc < 128) {
				str[i] = static_cast<char>(wc);
			}
			else {
				str[i] = '?';
			}
		}
		return str;
	}
};

struct flinearcolor
{
	float r, g, b, a;
	flinearcolor() : r(0), g(0), b(0), a(0) { }
	flinearcolor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }
	flinearcolor(float r, float g, float b) : r(r), g(g), b(b), a(1.f) {}
};

enum class earesalliance : uint8_t {
	ally = 0,
	enemy = 1,
	neutral = 2,
	any = 3,
	count = 4
};

enum class e_blend_mode : uint8_t
{
	opaque = 0,
	masked = 1,
	translucent = 2,
	additive = 3,
	modulate = 4,
	alpha_composite = 5,
	max = 6,
};

enum class EAresOutlineMode : uint8_t {
	None = 0,
	Outline = 1,
	Block = 2,
	Enemy = 3,
	AlwaysOutline = 4,
	AlwaysEnemy = 5,
	EAresOutlineMode_MAX = 6
};



struct FPlane {
	double X;
	double Y;
	double Z;
	double W;


	FPlane() : X(0.0), Y(0.0), Z(0.0), W(0.0) {}


	FPlane(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w) {}
};


struct FMatrix {
	FPlane XPlane;
	FPlane YPlane;
	FPlane ZPlane;
	FPlane WPlane;

	
	FMatrix() {}

	
	FMatrix(const FPlane& x, const FPlane& y, const FPlane& z, const FPlane& w)
		: XPlane(x), YPlane(y), ZPlane(z), WPlane(w) {
	}
};
