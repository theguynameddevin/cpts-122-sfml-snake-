#pragma once
#include <string>
using std::string;

class Record {
	public: 
		Record(string newName = "", int newScore = 0) {
			this->mName = newName;
			this->mScore = newScore;
		}
		void setName(string newName) {
			this->mName = newName;
		}
		void setScore(int newScore) {
			this->mScore = newScore;
		}
		string getName() {
			return this->mName;
		}
		int getScore() {
			return this->mScore;
		}

	private:
		string mName;
		int mScore;
};
