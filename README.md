# Project Title: Chord 


## Team members:

<pre>
   Roll number   Name
1. 2019201016    Shivani Hanji
2. 2019201046    Akash Kumar
3. 2019201074    Pratikkumar Bulani
4. 2019202004    Pranshi Yadav
</pre>

An implementation of the Chord protocol, which efficiently finds the node in a distributed system that has a particular data value.


# Instructions to run code:
## 1. Download or clone this repository
```bash
git clone https://github.com/ShivaniH/Chord-Distributed-Lookup.git
```
      
## 2. To compile the code: 
```bash
cd your-download-path/Chord-Distributed-Lookup
make 
```

## 3. To run
Each machine that will act as a Chord node needs to run
```bash
./ChordClient specify-some-port-number-here
eg.: ./ChordClient 12345
```
      
To create a new Chord ring:
```bash
create_chord
```

To join a Chord ring created by another node (NOTE: Can specify the IP and port of ANY node which is a part of that Chord ring, not necessarily the creator):
```bash
join_chord node-ip-address node-port-number
```

To check who is(are) the current node's successor(s):
```bash
display_successor_list
```

To check who is the current node's predecessor:
```bash
display_predecessor
```

To view the current node's finger table:
```bash
display_finger_table
```

To insert a new key value pair into the chord ring:
```bash
insert_key put-some-string-key put-some-string-value
```

To display the entries in the current node's hash table:
```bash
display_hash_table
```

To search for a key in the chord ring (and retrieve its value, from whichever node has it):
```bash
search_key put-key-string-here
```
