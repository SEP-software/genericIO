cmake_minimum_required(VERSION 2.8)
project(Generic-IO)

add_subdirectory(base)

if (USE_SEP)
   add_subdirectory(sep)
endif (USE_SEP)
if (USE_RSF)
   add_subdirectory(rsf)
endif (USE_RSF)
#if (USE_SU)
#   add_subdirectory(su)
#endif (USE_SU)
#if (USE_SEISPAK)
#   add_subdirectory(seispak)
#endif (USE_SEISPAK)

