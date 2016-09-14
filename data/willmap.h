#include <map>
#include <vector>

/*******************
 * Tristan Mcswain *
 *     s3528615    *
 *******************/ 

template <typename...> class willmap;

template <typename K, typename T>
class willmap<K, T>
{
	std::vector<K> keys;
	std::map<K, T> mymap;
	public:
		willmap<K, T> (){}
		//add a value
		void add(K k, T t)
		{
			mymap.insert({k, t});
			keys.push_back(k);
		}
		//check if a key exists
		bool exists(K k)
		{
			if (mymap.count(k) > 0)
			{
				return true;
			}
			return false;
		}
		//get the value for the given key
		T get(K k)
		{
			return mymap.at(k);
		}
		// Delete a loop
		void del_loop(K k)
		{
			bool found = false;
			unsigned int i, point;
			for (i = 0; i < keys.size(); ++i)
			{
				if(keys[i] == k)
				{
					point = i;
					found = true;
					break;
				}
				
			}
			if (found)
			{
				keys.erase(keys.begin() + point, keys.end());		
			}
		}
		// takes a map data structure as an arg
		void move_data(std::multimap<K, T> newmap)
		{
			for (unsigned i = 0; i < keys.size(); ++i)
			{
				newmap.insert({keys[i], mymap.at(keys[i])});
			}
			mymap.clear();
			keys.clear();
		}
		
};