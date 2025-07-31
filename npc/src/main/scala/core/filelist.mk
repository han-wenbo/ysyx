THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))
THIS_DIR := $(dir $(realpath $(THIS_MAKEFILE)))

SCALA_SRCS_BLACKLIST-y +=  $(THIS_DIR)io.scala
SCALA_DIRS-y +=$(THIS_DIR)
