THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))
THIS_DIR := $(dir $(realpath $(THIS_MAKEFILE)))

SCALA_SRCS-y :=
SCALA_SRCS-y +=  $(THIS_DIR)InstDecode.scala


