# OXXYEN Bot (C Edition)

🚀 A minimal, fast, and dependency-conscious Telegram bot written entirely in **pure C**.  
Designed for efficiency, transparency, and low-level control — no Python, no bloat.

> _"Less abstraction, more control."_

---

## ✨ Features

- **Lightweight**: Built with native C and the [`telebot`](https://github.com/zlgtelecom/telebot) library.
- **Secure token handling**: Reads bot token from a local `.token` file (never hardcoded).
- **Basic commands**:
  - `/start` — Welcome message
  - `/help` — Command list
  - `/dice` — Send a 🎲 animated dice
- **Admin terminal support** (pluggable): Ready for admin command integration.
- **Human-readable logs**: Real-time console output of incoming messages.
- **No external interpreters**: Runs natively — no Python, Node.js, or VM required.

---

## 🛠️ Build & Run

### Prerequisites

- Linux (tested on Arch Linux)
- `gcc` or `clang`
- [`telebot`](https://github.com/zlgtelecom/telebot) C library (v1.0+)
- `make` (optional, if using a Makefile)

### 1. Clone and set up and clone library

```bash
git clone https://github.com/oxxy3n/oxxyen-bot-c.git
git clone https://github.com/smartnode/telebot
cd oxxyen-bot-c
```

### 2. Install telebot
Follow the instructions in the telebot repository to build and install the library.

### 3. Add your bot token
Create a .token file in the project root containing only your Telegram bot token:
```bash
echo "1234567890:ABCDEFGHIJKLMNOPQRSTUVWXYZ" > .token
```
> 🔒 Security note: Ensure .token has strict permissions:
chmod 600 .token 

### 4. Compile
```bash
gcc -o oxxyen-bot bot.c -ltelebot -lcurl -lpthread -ljansson
```
### 5. Run
```bash
./oxxyen-bot
```
## 📦 Dependencies

- [`telebot`](https://github.com/zlgtelecom/telebot) — C wrapper for Telegram Bot API  
- `libcurl` — for HTTP requests  
- `jansson` — for JSON parsing  
- `pthread` — for internal threading (used by telebot)

## 🧠 Philosophy

This bot is built for developers who:

- Prefer **C** for system-level control,  
- Avoid high-level runtimes when not needed,  
- Value **auditability** and **minimal attack surface**,  
- Want a foundation for secure, low-overhead Telegram automation.

It’s not meant to be feature-rich — it’s meant to be **reliable, readable, and extensible**.

## 📬 Contact

- Bot support: [@meowmeowmez](https://t.me/meowmeowmez)  
- Author: **NorthernHush**  
- License: MIT (see `LICENSE`)

> 💡 **Pull requests and C-based enhancements welcome!**  
> No JavaScript. No Python. Just C.
