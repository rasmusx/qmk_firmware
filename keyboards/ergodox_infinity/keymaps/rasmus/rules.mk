KEY_LOCK_ENABLE = yes
CONSOLE = yes
COMMAND = yes
VISUALIZER_USER_DATA_SIZE = 32

OPT_DEFS += -DVISUALIZER_USER_DATA_SIZE=$(strip $(VISUALIZER_USER_DATA_SIZE))
