#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "telebot/include/telebot.h"

int main(int argc, char *argv[])
{
    printf("🚀 OXXYEN Bot v1.1 (C edition)\n");
    printf("─────────────────────────────\n");

    // Загружаем токен
    FILE *fp = fopen(".token", "r");
    if (fp == NULL) {
        fprintf(stderr, "❌ Не найден файл .token\n");
        return -1;
    }

    char token[1024];
    if (fscanf(fp, "%1023s", token) != 1) {
        fprintf(stderr, "❌ Ошибка чтения токена\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);

    telebot_handler_t handle;
    if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE) {
        fprintf(stderr, "❌ Ошибка инициализации Telebot\n");
        return -1;
    }

    telebot_user_t me;
    if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE) {
        fprintf(stderr, "❌ Не удалось получить информацию о боте\n");
        telebot_destroy(handle);
        return -1;
    }

    printf("✅ Бот запущен: %s (@%s)\n", me.first_name, me.username);
    telebot_put_me(&me);

    admin_terminal_start(handle);

    int offset = -1;
    telebot_update_t *updates;
    telebot_error_e ret;
    int count;

    while (1)
    {
        ret = telebot_get_updates(handle, offset, 20, 0, NULL, 0, &updates, &count);
        if (ret != TELEBOT_ERROR_NONE) {
            sleep(1);
            continue;
        }

        for (int i = 0; i < count; i++)
        {
            telebot_message_t msg = updates[i].message;
            if (msg.text == NULL) continue;

            long long chat_id = msg.chat->id;
            printf("📩 [%s]: %s\n", msg.from->first_name, msg.text);

            // if(admin_is_admin(msg.chat->id)) {
            //     admin_handle_command(handle, &msg);
            //     continue;
            // }

            if (strcmp(msg.text, "/start") == 0)
            {
                char reply[2048];
                snprintf(reply, sizeof(reply),
                    "👋 Привет, %s!\n\n"
                    "Я — <b>OXXYEN Bot</b> 🧠\n"
                    "Бот, написанный полностью на чистом C.\n\n"
                    "⚙️ Команды:\n"
                    "  • /help — справка\n"
                    "  • /dice — бросить кубик 🎲",
                    msg.from->first_name);

                telebot_send_message(handle, chat_id, reply, "HTML", false, false, msg.message_id, "");
            }
            else if (strcmp(msg.text, "/help") == 0)
            {
                const char *help_msg =
                    "📘 <b>Помощь</b>\n\n"
                    "Мои команды:\n"
                    "  • /start — приветствие\n"
                    "  • /help — показать это сообщение\n"
                    "  • /dice — бросить случайный кубик 🎲\n\n"
                    "👨‍💻 Минимализм и скорость — сила C.";

                telebot_send_message(handle, chat_id, help_msg, "HTML", false, false, msg.message_id, "");
            }
            else if(msg.text && strcmp(msg.text, "admin_chat") == 0) {
                admin_notify_incoming(&msg);
                telebot_send_message(handle, chat_id, "✅ Ваше сообщение доставлено администратору.", "", false, false, msg.message_id, "");
            }
            else if (strcmp(msg.text, "/dice") == 0)
            {
                telebot_send_dice(handle, chat_id, false, 0, "");
            }
            else
            {
                telebot_send_message(handle, chat_id,
                    "🤖 Неизвестная команда.\nВведите /help, чтобы узнать доступные.", 
                    "", false, false, msg.message_id, "");
            }

            offset = updates[i].update_id + 1;
        }

        telebot_put_updates(updates, count);
        sleep(1);
    }

    admin_terminal_stop();

    telebot_destroy(handle);
    return 0;
}
