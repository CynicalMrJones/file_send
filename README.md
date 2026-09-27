# File sender
Allows user to serve a file for clients to get

### Problems
- Allocations are done all at once which leads to lots of ram usage. ex. if you server a 10gb file, it allocates it all upfront. 
