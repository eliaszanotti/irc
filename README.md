# IRC

### ENUM: MODE
```c++
enum {
	OPEN,
	INVITE,
	LIMITED
}
```

---
### CLASS: SERVER
Private attributes:

| TYPE      | VARIABLE |
|-----------|:---------|
| string    | ip       |
| int       | port     |
| container | channels |
| container | users    |

Methods:

| TYPE |      NAME     | ARGUMENTS        |
|------|--------------:|------------------|
| bool | createChannel | (string topic)   |
| bool | createUser    | (User &new_user) |


---
### CLASS: USER
Private attributes:

| TYPE                    | VARIABLE   | INIT VALUE       |
|-------------------------|:-----------|------------------|
| string                  | name       | default/argument |
| string                  | nickname   | default/argument |
| map <channel,privilege> | privileges | void             |
	

---
### CLASS: CHANNEL:
Private attributes:

| TYPE      | VARIABLE | INIT VALUE       |
|-----------|:---------|------------------|
| container | messages | void             |
| container | users    | void             |
| string    | password | void             |
| enum      | mode     | OPEN             |
| string    | topic    | default/argument |

Methods:

| TYPE |  NAME  | ARGUMENTS                |
|------|-------:|--------------------------|
| bool | kick   | (User &user)             |
| bool | invite | (User &user)             |
| bool | topic  | (const string new_topic) |
| bool | mode   | (char <i, t, k, o, l>)   |


### IDEAS
- Create an admin user with all the access ?
- Each client is distinguished from other clients by a unique nickname having a maximum length of nine (9) characters