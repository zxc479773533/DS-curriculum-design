#include <random>
#include <iostream>
#include <set>
#include "include/gtest/gtest.h"

extern "C" {
	#include "avltree.h"
}

class setTest : public testing::Test {
protected:
  virtual void SetUp() {
    start_time = time(NULL);
  }

  virtual void TearDown() {
    time_t end_time = time(NULL);
    std::cout << "This test takes " << end_time-start_time << "times." << std::endl;
    ASSERT_TRUE(end_time - start_time <= 30) << "The test took too long.";
  }

  time_t start_time;
};

TEST_F(setTest, random_small) {

	std::default_random_engine e(810);
	std::uniform_int_distribution<int> dis(1, 100);

	std::set<int> std_set;
	AVL_tree *custom_set;

	custom_set = Init_AVL(0, 1);

	for (unsigned int i = 1; i < 100; i++) {
		int num = dis(e);
		std_set.insert(num);
		Insert_AVL(custom_set, num);
	}

	ASSERT_EQ(std_set.size(), custom_set->num);

	for (auto s:std_set) {
		ASSERT_EQ(Search_AVL(custom_set, s), s);
		Delete_AVL(custom_set, s);
	}
	ASSERT_EQ(custom_set->num, 0);
}

TEST_F(setTest, random_large) {
	std::default_random_engine e(810);
	std::uniform_int_distribution<int> dis(1,100);

	std::set<int> std_set;
	AVL_tree *custom_set;

	custom_set = Init_AVL(0, 1);

	for (unsigned int i = 1; i < 500000; i++) {
		int num = dis(e);
		std_set.insert(num);
		Insert_AVL(custom_set, num);
	}

	ASSERT_EQ(std_set.size(), custom_set->num);

	for (auto s:std_set) {
		ASSERT_EQ(Search_AVL(custom_set, s), s);
		Delete_AVL(custom_set, s);
	}
	ASSERT_EQ(custom_set->num, 0);
}

TEST_F(setTest, only_data) {
	std::set<int> std_set;
	AVL_tree *custom_set;

	custom_set = Init_AVL(0, 1);

	for (unsigned int i = 1; i < 5000; i++) {
		std_set.insert(1);
		Insert_AVL(custom_set, 1);
	}
	ASSERT_EQ(std_set.size(), custom_set->num);
	ASSERT_EQ(Search_AVL(custom_set,1), 1);
}

TEST_F(setTest, ordered_data) {
	std::set<int> std_set;
	AVL_tree *custom_set;

	custom_set = Init_AVL(0, 1);

	for (unsigned int i = 1; i < 5000; i++) {
		std_set.insert(i);
		Insert_AVL(custom_set, i);
	}
	ASSERT_EQ(std_set.size(), custom_set->num);
	for (auto s:std_set) {
		Delete_AVL(custom_set, s);
	}
	ASSERT_EQ(custom_set->num, 0);
}

TEST_F(setTest, repeated_data) {
	std::set<int> std_set;
	AVL_tree *custom_set;

	custom_set = Init_AVL(0, 1);

	for (unsigned int i = 0; i < 5000; i++) {
		std_set.insert(i);
		std_set.insert(i+1);
		Insert_AVL(custom_set, i);
		Insert_AVL(custom_set, i+1);
	}
	ASSERT_EQ(std_set.size(), custom_set->num);
		for (auto s:std_set) {
		Delete_AVL(custom_set, s);
	}
	ASSERT_EQ(custom_set->num, 0);
}

TEST_F(setTest, random) {
	std::random_device rand_dev;

	std::default_random_engine e(810);
	std::uniform_int_distribution<int> dis(1,100);

	std::set<int> std_set;
	AVL_tree *custom_set;

	custom_set = Init_AVL(0, 1);

	for (unsigned int times = 0; times < 10; times++) {
		for (unsigned int i = 0; i < 10000; i++) {
			double num = dis(e);
			std_set.insert(num);
			Insert_AVL(custom_set, num);
		}

		ASSERT_EQ(std_set.size(), custom_set->num);

		if (times % 2) {
			for (auto s:std_set) {
				Delete_AVL(custom_set, s);
				ASSERT_EQ(Search_AVL(custom_set, s), 0);
			}
			std_set.clear();
		}
		else {
			Clear_AVL(custom_set);
			std_set.clear();
		}

		ASSERT_EQ(std_set.size(), 0);
		ASSERT_EQ(custom_set->num, 0);
	}
}
