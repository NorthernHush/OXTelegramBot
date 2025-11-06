gcc -Itelebot/include \
    main.c \
    admin/admin.c \
    admin/terminal_chat.c \
    telebot/src/telebot.c \
    telebot/src/telebot-core.c \
    telebot/src/telebot-parser.c \
    -lcurl -lpthread -ljson-c \
    -o main
