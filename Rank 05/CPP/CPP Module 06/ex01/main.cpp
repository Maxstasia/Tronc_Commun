#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main(void)
{
	// Test 1: Basic serialization/deserialization
	{
		std::cout << "=== Test 1: Basic Serialization ===" << std::endl;
		Data* original = new Data("Test Data", 42);
		
		std::cout << "Original Data:" << std::endl;
		std::cout << "  Address: " << original << std::endl;
		std::cout << "  Name: " << original->name << std::endl;
		std::cout << "  Value: " << original->value << std::endl;
		
		uintptr_t serialized = Serializer::serialize(original);
		std::cout << "\nSerialized: " << serialized << std::endl;
		
		Data* deserialized = Serializer::deserialize(serialized);
		std::cout << "\nDeserialized Data:" << std::endl;
		std::cout << "  Address: " << deserialized << std::endl;
		std::cout << "  Name: " << deserialized->name << std::endl;
		std::cout << "  Value: " << deserialized->value << std::endl;
		
		std::cout << "\nPointers match: " << (original == deserialized ? "YES" : "NO") << std::endl;
		
		delete original;
		std::cout << std::endl;
	}

	// Test 2: Multiple objects
	{
		std::cout << "=== Test 2: Multiple Objects ===" << std::endl;
		Data* data1 = new Data("First", 1);
		Data* data2 = new Data("Second", 2);
		Data* data3 = new Data("Third", 3);
		
		uintptr_t ser1 = Serializer::serialize(data1);
		uintptr_t ser2 = Serializer::serialize(data2);
		uintptr_t ser3 = Serializer::serialize(data3);
		
		Data* deser1 = Serializer::deserialize(ser1);
		Data* deser2 = Serializer::deserialize(ser2);
		Data* deser3 = Serializer::deserialize(ser3);
		
		std::cout << "Data 1: " << (data1 == deser1 ? "OK" : "FAIL") 
				  << " - " << deser1->name << " = " << deser1->value << std::endl;
		std::cout << "Data 2: " << (data2 == deser2 ? "OK" : "FAIL") 
				  << " - " << deser2->name << " = " << deser2->value << std::endl;
		std::cout << "Data 3: " << (data3 == deser3 ? "OK" : "FAIL") 
				  << " - " << deser3->name << " = " << deser3->value << std::endl;
		
		delete data1;
		delete data2;
		delete data3;
		std::cout << std::endl;
	}

	// Test 3: Stack-allocated Data
	{
		std::cout << "=== Test 3: Stack-Allocated Data ===" << std::endl;
		Data stackData("Stack Data", 100);
		
		std::cout << "Original address: " << &stackData << std::endl;
		
		uintptr_t serialized = Serializer::serialize(&stackData);
		Data* deserialized = Serializer::deserialize(serialized);
		
		std::cout << "Deserialized address: " << deserialized << std::endl;
		std::cout << "Pointers match: " << (&stackData == deserialized ? "YES" : "NO") << std::endl;
		std::cout << "Data: " << deserialized->name << " = " << deserialized->value << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
