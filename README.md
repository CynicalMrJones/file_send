# File sender
Allows user to serve a file for clients to get

### Problems
- Allocations are done all at once which leads to lots of ram usage. ex. if you server a 10gb file, it allocates it all upfront. 
- Only currently supports file names less than 10 characters
- Max size of file is dependent on 8 bytes
