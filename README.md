#leetcode 146 lru cache

#combine hashtable and lru
#we store "lru node address" and "key" in hashtable
#In search, we first search the key in hashtable
#The key in lru if the key hit in hashtable
#we jump to the lru node address
