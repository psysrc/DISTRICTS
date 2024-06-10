#ifndef ID_H_
#define ID_H_

// Unique ID type
typedef unsigned int ID_t;

// NullID value indicates that an ID variable does not contain an ID
const int NullID = 0;

ID_t uniqueEntityID();
ID_t uniqueTaskID();

#endif /* ID_H_ */
