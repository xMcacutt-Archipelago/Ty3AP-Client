#pragma once

class APSaveData
{
public:
	APSaveData();
	bool hasBoughtItem(int id) {
		return ItemMap[id];
	}
	void updateBoughtItem(int id, bool bought) {
		ItemMap[id] = bought;
	}
	int pLastReceivedIndex = -1;
	int berryCount = 0;
	int orbCount = 0;
	int bilbyCount = 0;
	std::list<int> UnlockedParkingPads = {
	};
	std::list<int> UnlockedBarriers = {
	};
	const std::list<int> AllParkingPads = 
	{ 
	
	};
	std::map<int, bool> ItemMap = {
		
	};
};