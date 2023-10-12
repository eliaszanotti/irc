=================================================================
==11048==ERROR: AddressSanitizer: heap-use-after-free on address 0x611000003b38 at pc 0x000000434f84 bp 0x7ffce0b73390 sp 0x7ffce0b72b50
READ of size 7 at 0x611000003b38 thread T0
    #0 0x434f83 in memcpy (/nfs/homes/tgiraudo/Documents/irc/ircserv+0x434f83)
    #1 0x7f3e83a30c15 in void std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_construct<char*>(char*, char*, std::forward_iterator_tag) (/lib/x86_64-linux-gnu/libstdc++.so.6+0x145c15)
    #2 0x4dd806 in User::getName[abi:cxx11]() const /nfs/homes/tgiraudo/Documents/irc/srcs/User.cpp:50:52
    #3 0x4fb571 in Server::_who(int, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >) /nfs/homes/tgiraudo/Documents/irc/srcs/command/who.cpp:32:6
    #4 0x4cff4b in Server::_executeUserCommand(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:178:9
    #5 0x4cebda in Server::_processMessage(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:80:10
    #6 0x4d0ca8 in Server::_connectEachUser() /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:126:12
    #7 0x4d15ef in Server::waitingForNewUsers() /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:225:10
    #8 0x4cdebb in main /nfs/homes/tgiraudo/Documents/irc/srcs/main.cpp:39:10
    #9 0x7f3e8357e082 in __libc_start_main /build/glibc-SzIz7B/glibc-2.31/csu/../csu/libc-start.c:308:16
    #10 0x41ed4d in _start (/nfs/homes/tgiraudo/Documents/irc/ircserv+0x41ed4d)

0x611000003b38 is located 56 bytes inside of 216-byte region [0x611000003b00,0x611000003bd8)
freed by thread T0 here:
    #0 0x4cb8cd in operator delete(void*) (/nfs/homes/tgiraudo/Documents/irc/ircserv+0x4cb8cd)
    #1 0x4d07fc in Server::_closeCurrentUser(int) /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:96:2
    #2 0x500834 in Server::_quit(int, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >) /nfs/homes/tgiraudo/Documents/irc/srcs/command/quit.cpp:30:10
    #3 0x4d00cf in Server::_executeUserCommand(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:182:9
    #4 0x4cebda in Server::_processMessage(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:80:10
    #5 0x4d0ca8 in Server::_connectEachUser() /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:126:12
    #6 0x4d15ef in Server::waitingForNewUsers() /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:225:10
    #7 0x4cdebb in main /nfs/homes/tgiraudo/Documents/irc/srcs/main.cpp:39:10
    #8 0x7f3e8357e082 in __libc_start_main /build/glibc-SzIz7B/glibc-2.31/csu/../csu/libc-start.c:308:16

previously allocated by thread T0 here:
    #0 0x4cb06d in operator new(unsigned long) (/nfs/homes/tgiraudo/Documents/irc/ircserv+0x4cb06d)
    #1 0x4ce828 in Server::_addNewUser() /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:64:19
    #2 0x4d15de in Server::waitingForNewUsers() /nfs/homes/tgiraudo/Documents/irc/srcs/Server.cpp:224:10
    #3 0x4cdebb in main /nfs/homes/tgiraudo/Documents/irc/srcs/main.cpp:39:10
    #4 0x7f3e8357e082 in __libc_start_main /build/glibc-SzIz7B/glibc-2.31/csu/../csu/libc-start.c:308:16

SUMMARY: AddressSanitizer: heap-use-after-free (/nfs/homes/tgiraudo/Documents/irc/ircserv+0x434f83) in memcpy
Shadow bytes around the buggy address:
  0x0c227fff8710: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c227fff8720: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c227fff8730: fa fa fa fa fa fa fa fa fd fd fd fd fd fd fd fd
  0x0c227fff8740: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c227fff8750: fd fd fd fd fd fd fd fd fa fa fa fa fa fa fa fa
=>0x0c227fff8760: fd fd fd fd fd fd fd[fd]fd fd fd fd fd fd fd fd
  0x0c227fff8770: fd fd fd fd fd fd fd fd fd fd fd fa fa fa fa fa
  0x0c227fff8780: fa fa fa fa fa fa fa fa fd fd fd fd fd fd fd fd
  0x0c227fff8790: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0c227fff87a0: fd fd fd fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c227fff87b0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:         