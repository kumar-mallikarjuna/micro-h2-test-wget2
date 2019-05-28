README
===

This micro-project exists to test HTTP/2 support for [Wget2](https://gitlab.com/gnuwget/wget2).

The Certificates are missing, they can be generated locally using [certtool](https://gnutls.org/manual/html_node/certtool-Invocation.html).

## Dependencies
1. [libmicrohttpd-http2](https://github.com/maru/libmicrohttpd-http2)
2. [GnuTLS](https://gitlab.com/gnutls/)

## Bibliography
1. https://git.gnunet.org/libmicrohttpd.git/tree/src/examples/https_fileserver_example.c
2. https://github.com/maru/libmicrohttpd-http2/blob/master/src/examples/http2_minimal_example.c 
