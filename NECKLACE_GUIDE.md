# MindMirror AI Necklace: build it from scratch

**Who this is for:** Pankaj and Kishore, with no hardware experience needed. Follow it top to bottom. Do not skip the tests in Part 4: each one proves one part works, so when something breaks you know exactly where.

**What it does:** the student holds the button on the necklace, says how they feel, and lets go. A second later the necklace answers out loud through its own speaker, and the MindMirror app on the laptop logs that voice check-in.

---

## Part 0. The big picture (read this once)

```
 ┌──────────── NECKLACE ────────────┐          ┌──────────── LAPTOP ─────────────┐
 │                                  │          │                                 │
 │  [button] ──► ESP32 ◄── INMP441  │  Wi-Fi   │  MindMirror Hub (server.mjs)    │
 │                │        (mic)    │ ───────► │   1. speech → text  (Groq)      │
 │                ▼                 │  audio   │   2. text → reply   (Groq AI)   │
 │           MAX98357A (amp)        │ ◄─────── │   3. reply → voice  (Edge TTS)  │
 │                │                 │  reply   │          │                      │
 │            speaker 8Ω            │  audio   │          ▼  live events         │
 └──────────────────────────────────┘          │  MindMirror web app (React)     │
        powered by USB power bank              └─────────────────────────────────┘
                     both join the same PHONE HOTSPOT (2.4 GHz)
```

- The **ESP32** is the brain of the necklace. It reads the button, records from the mic, sends audio over Wi-Fi, and plays the reply.
- The **INMP441** is a digital microphone. It sends sound to the ESP32 as numbers over 3 wires (a protocol called I2S).
- The **MAX98357A** is an amplifier. It takes numbers from the ESP32 over 3 wires (also I2S) and drives the speaker.
- The **Hub** is a small program on the laptop. It does the heavy AI work, because the ESP32 is far too small for that.
- The ESP32 finds the laptop by itself: the hub calls out "I'm here" on the hotspot every 2 seconds.

### Why Wi-Fi to a laptop, and not Bluetooth to the phone like Round 1?

My opinion, for a 24-hour rebuild with two first-timers: **Wi-Fi + laptop hub is the right call.** The Round 1 design (Bluetooth, on-phone AI) needed a custom Bluetooth audio protocol, audio compression and on-device AI models. It is impressive but has many places to fail, and you would be rebuilding all of it. The Wi-Fi version is about 300 lines of firmware, uses plain HTTP, and every piece can be tested on its own. The cost: voice is sent to an AI service to be transcribed. We say so honestly in the pitch (see the app guide's privacy section), and nothing is stored there.

---

## Part 1. Parts check

| Part | What it does | Check before you start |
|---|---|---|
| ESP32 development board (ESP32-WROOM-32 "DevKit", 30 or 38 pins) | the brain, has Wi-Fi | Says ESP32 on the metal can. Micro-USB or USB-C port. |
| INMP441 microphone module | hears the student | 6 pins: **L/R, WS, SCK, SD, VDD, GND** |
| MAX98357A amplifier module | powers the speaker | 7 pins: **LRC, BCLK, DIN, GAIN, SD, GND, VIN**, plus a 2-screw speaker terminal |
| 8 Ω 0.5 W speaker | talks | two wires, or two metal tabs |
| USB **data** cable | flashes the ESP32 | Some cables only charge. If the laptop doesn't see the board, try another cable first. |
| Header pins | let modules plug into a breadboard | must be **soldered** onto the mic and amp |
| Breadboard + jumper wires | connects everything without soldering wires | get male-male **and** female-female jumpers if you can |
| Push button (4-leg tactile) | the talk button | |
| Also bring | USB power bank + its cable, insulation tape, cardboard/foam, a cord or lanyard, hot glue | the necklace runs from the power bank |

**There is no battery or charger in this parts list, so the necklace is powered by a USB cable to a small power bank in the student's pocket.** That is normal for a hackathon prototype. Say "battery version is next" if judges ask.

### The one thing you must do before the event: solder the headers

The mic and amp modules usually arrive with their header pins loose. **Solder them on before 1 November** (college lab, or a ₹300 iron). Soldering header pins onto a module is preparation, not building the project, so it's fine under the rules. If nobody can solder, tell Pankaj today.

How to solder headers (10 minutes, watch one YouTube video first: search "how to solder header pins"):
1. Push the long side of the header strip into the breadboard, put the module on top (pins through its holes).
2. Iron tip touches the pin **and** the copper ring together for 2 seconds, then feed solder in. It should flow into a small shiny cone.
3. Do every pin. Don't let solder bridge two neighbouring pins.

---

## Part 2. Install the software (on Pankaj's and Kishore's laptops)

1. **Arduino IDE 2** from arduino.cc/en/software.
2. In Arduino IDE: **File → Preferences → Additional boards manager URLs**, paste:
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. **Tools → Board → Boards Manager**, search **esp32**, install **"esp32 by Espressif Systems"**, version **3.x** (the code uses the 3.x `ESP_I2S` library; version 2.x will not compile it).
4. Plug in the ESP32. **Tools → Board → esp32 → ESP32 Dev Module**. **Tools → Port** → pick the new COM port (Windows) or `/dev/cu.usbserial…` (Mac).
   - No port appears? Install the USB driver: look at the small chip next to the USB port. **CP2102** → "CP210x driver" from Silicon Labs. **CH340** → "CH340 driver". Then replug.
5. **Node.js 22 LTS** from nodejs.org (for the hub).

---

## Part 3. Wiring

### Pin table (this is the source of truth)

Use the **labels printed on the ESP32 board** (D32, D25…), not the physical position. 30-pin and 38-pin boards place them differently, but the labels are the same.

**INMP441 microphone → ESP32**

| INMP441 pin | ESP32 pin | Wire colour (suggested) |
|---|---|---|
| VDD | **3V3** | red |
| GND | **GND** | black |
| SCK | **D32** (GPIO32) | yellow |
| WS | **D25** (GPIO25) | green |
| SD | **D33** (GPIO33) | blue |
| L/R | **GND** | black (this picks the "left" side) |

> ⚠️ The mic is a **3.3 V** part. Never connect its VDD to VIN/5V.

**MAX98357A amplifier → ESP32**

| MAX98357A pin | ESP32 pin | Wire colour |
|---|---|---|
| VIN | **VIN** (5V from USB; called **5V** on 38-pin boards) | orange |
| GND | **GND** | black |
| BCLK | **D26** (GPIO26) | yellow |
| LRC | **D27** (GPIO27) | green |
| DIN | **D22** (GPIO22) | white |
| GAIN | not connected | |
| SD | not connected | |
| Speaker + / − | speaker's two wires, into the screw terminal | either way round |

**Button and LED**

| Part | Connect |
|---|---|
| Button, one leg | **D13** (GPIO13) |
| Button, the diagonally opposite leg | **GND** |
| Status LED | the blue LED already on the board (GPIO2), nothing to wire |

Button tip: a 4-leg button has two pairs of legs that are always joined. Using **diagonally opposite** legs always works.

### Why these pins?

GPIO 0, 2, 5, 12 and 15 affect how the ESP32 boots, so we avoid them for inputs. GPIO 34 to 39 can only read, so they're kept free. Mic and amp each get their own set of I2S pins, because the ESP32 has two I2S engines and we use one for each.

### Breadboard layout

```
          ESP32 DevKit straddles the centre gap (USB facing you)
     left pins                                  right pins
   ┌─────────────────────────────────────────────────────────┐
   │ D32 ── yellow ──► mic SCK          D22 ── white ──► amp DIN
   │ D33 ── blue ────► mic SD           3V3 ── red ────► mic VDD
   │ D25 ── green ───► mic WS
   │ D26 ── yellow ──► amp BCLK
   │ D27 ── green ───► amp LRC
   │ D13 ── button ── GND
   │ GND ── black ───► blue (−) rail ──► mic GND, mic L/R, amp GND
   │ VIN ── orange ──► amp VIN
   └─────────────────────────────────────────────────────────┘
```

**The ESP32 is wide.** On many breadboards it covers almost all the holes, leaving one free hole per pin on one side and none on the other. Two easy fixes:
- Use **two breadboards side by side**, the ESP32 bridging them, or
- Skip the breadboard for the ESP32: connect **female-to-female jumpers** straight from the ESP32 pins to the mic and amp pins. This is also what you'll do for the wearable version.

### Wiring checklist (tick each one, then check again with another person)

- [ ] Mic VDD on **3V3**, not VIN
- [ ] Mic L/R to GND
- [ ] Amp VIN on **VIN/5V**
- [ ] All GNDs connected together
- [ ] No bare wire ends touching each other
- [ ] USB unplugged while you wire

---

## Part 4. Test one thing at a time

All test sketches are in [`reference/firmware/`](reference/firmware). Open one in Arduino IDE, click **Upload** (→ arrow), then open **Tools → Serial Monitor** at **115200** baud.

> If upload fails with "Failed to connect… Timed out waiting for packet header": hold the **BOOT** button on the ESP32, click Upload, let go when you see "Connecting…".

| Test | What to do | It works if | If not |
|---|---|---|---|
| **01_blink_button** | upload | blue LED blinks; holding the button keeps it on and prints `PRESSED` | button on the wrong legs (try the diagonal pair); wrong pin |
| **02_speaker_tone** | upload | beep-beep every 2 s; button plays a little tune | check VIN/GND/BCLK/LRC/DIN; speaker screws tight; try another USB port |
| **03_mic_level** | upload, open **Tools → Serial Plotter**, clap and talk | one line (`side0` or `side1`) jumps when you make noise | both flat: check SCK/WS/SD and that L/R goes to GND. Write down which side moved. |
| **04_echo** | set `MIC_CHANNEL` to the side from test 3, upload, hold button, talk, let go | you hear your own voice back | quiet: lower `MIC_SHIFT` to 12. Distorted: raise it to 15. |

**When test 4 works, all the hardware is correct.** Anything that goes wrong after this is Wi-Fi or the hub, not wiring.

---

## Part 5. The hub on the laptop

Code: [`reference/hub/server.mjs`](reference/hub/server.mjs). It has been run here end to end with a fake necklace (sends chunked audio, gets reply audio back, the app event fires).

1. Get a free **Groq API key**: console.groq.com → sign in → API Keys → Create. (Groq is free for this amount of use. Keep the key secret: never commit it, never paste it in a chat.)
2. In the project repo: `cd hub`, `npm install`.
3. Copy `.env.example` to `.env` and paste the key after `GROQ_API_KEY=`.
4. `npm start`. You should see:
   ```
   MindMirror Hub on http://localhost:8787  (mock: false)
     necklace can reach me at 192.168.43.120:8787
   ```
5. **Windows:** a firewall popup appears. Tick **both Private and Public** and click Allow. (Phone hotspots are usually "Public", and if you only allow Private the necklace can't connect.)
6. Open `http://localhost:8787/health` in the browser. It should say `"ok":true` and `"hasKey":true`.

No internet or no key yet? Run `MOCK_AI=1 npm run mock` (Mac/Linux) or `set MOCK_AI=1 && npm run mock` (Windows cmd). The hub then answers with a fixed sentence and a beep, so you can test the necklace link anyway.

What the hub uses:

| Step | Service | Why |
|---|---|---|
| Speech → text | Groq `whisper-large-v3-turbo` | fast and free |
| Reply | Groq `openai/gpt-oss-20b` | fast, free; `llama-3.x` models were retired in Aug 2026 so don't use old tutorials' model names |
| Text → voice | Microsoft Edge voice `en-IN-NeerjaNeural` (Indian English) via `msedge-tts` | free, no key, natural voice |
| Format conversion | `ffmpeg-static` (installs with npm) | turns the voice into raw 16 kHz audio the ESP32 can play |

**Safety rule built in:** if the student says anything like "I want to die" or "hurt myself", the hub never asks the AI. It always answers with a fixed message pointing to **Tele-MANAS 14416** and **112**. Don't remove this.

---

## Part 6. The necklace firmware

Code: [`reference/firmware/mindmirror_necklace/`](reference/firmware/mindmirror_necklace). Two files: `mindmirror_necklace.ino` (the program) and `config.h` (your settings).

1. On the phone that will be the hotspot: **Settings → Hotspot → Band: 2.4 GHz** (the ESP32 can't see 5 GHz). Name `MindMirror`, password `mindmirror123`, or change both in `config.h`.
2. Connect the **laptop** to the same hotspot. (Not the venue Wi-Fi: venue networks often block devices from talking to each other.)
3. In `config.h`, set `MIC_CHANNEL` to the number from test 3.
4. Upload. Serial Monitor should show:
   ```
   Connecting to MindMirror....
   Wi-Fi OK, my IP 192.168.43.57
   Hub found at 192.168.43.120:8787
   Ready. Hold the button and talk.
   ```
   and you hear a rising two-note "ready" chime.
5. Hold the button, wait for the short beep, say *"I only slept four hours and I have two deadlines tomorrow"*, let go.

### What the LED and sounds mean

| LED | Sound | Meaning |
|---|---|---|
| slow blink | | looking for Wi-Fi |
| solid on | rising chime | ready |
| fast blink | short beep | listening (button held) |
| short blip every half second | | thinking, then speaking |
| | single soft beep | you let go too fast; hold a bit longer |
| | falling two-note "uh-oh" | can't reach the hub (see troubleshooting) |

### How it works, in plain words

1. While you hold the button, the mic task reads sound 16,000 times a second, cleans it, and puts it in a 1-second waiting area (so a Wi-Fi hiccup doesn't lose words).
2. The main loop sends that sound to the hub in small pieces while you're still talking (HTTP "chunked" upload), so there's no memory limit on how long you talk (it stops at 10 s).
3. When you let go, it waits for the hub's answer and plays it as it arrives.
4. Settings worth knowing: `VOLUME` (keep ≤ 0.5 with the 0.5 W speaker), `MIC_SHIFT` (mic loudness), `MAX_RECORD_SECONDS`, and `HUB_HOST` (type the laptop IP here if auto-find fails).

> **Not yet tested on real hardware.** The hub has been run end to end here; the firmware was checked for typos but could not be compiled for the ESP32 in my environment. **Compile and run tests 1 to 4 on 31 October**, so any surprise happens before the clock starts. Paste any compile error to Pankaj (Claude) as-is.

---

## Part 7. Troubleshooting

| Problem | Most likely cause | Fix |
|---|---|---|
| No COM port | charge-only cable, or no driver | other cable; CP210x/CH340 driver |
| Upload "Timed out waiting for packet header" | board not in download mode | hold BOOT while uploading |
| Board resets when the speaker plays (Serial shows boot text again) | not enough power | plug into the laptop directly, not a hub; lower `VOLUME`; use a 2 A power bank |
| Stuck on "Connecting to MindMirror……" | hotspot is 5 GHz, or name/password wrong | set hotspot to 2.4 GHz; check spelling (case matters) |
| "No hub" | hub not running, or laptop on a different network | start the hub; put the laptop on the same hotspot |
| "Can't reach hub" | Windows firewall | allow Node.js on Public networks (Windows Security → Firewall → Allow an app) or type the IP in `HUB_HOST` |
| Hub log shows `transcribe 401` | bad API key | re-copy the key into `.env`, restart hub |
| Reply is just "I couldn't hear that" | mic side wrong or too quiet | redo test 3; lower `MIC_SHIFT` |
| Reply sounds like static | amp wiring | redo test 2; check DIN on D22 and LRC on D27 |
| Loud buzz or hum | loose ground | push all GND wires in firmly |
| Hub log shows `tts` error | Edge voice blocked on this network | switch to phone hotspot data; or ask Pankaj to swap TTS (see app guide, "Plan B") |

---

## Part 8. Make it a necklace (Kishore's craft job, overnight after the MVP works)

Only after the breadboard version works end to end.

1. Move from breadboard to **female-female jumpers** (same pin table). Keep the I2S wires short (under 15 cm).
2. **Pendant box:** a small box from mount board, foam sheet or a 3D-printed case if the lab has a printer. About 6 × 4 × 2.5 cm fits the ESP32 lying flat with the amp beside it.
3. **Speaker** faces outward through a grid of holes (poke with a compass point). Hot-glue the rim.
4. **Mic** gets its own small hole near the top, facing up towards the mouth. Don't cover the tiny hole on the mic chip with glue.
5. **Button** sticks out of the front or side where a thumb finds it.
6. USB cable exits at the bottom and runs to the power bank in a pocket.
7. Cord or lanyard through two holes at the top.
8. Decorate it to match the app's look (soft indigo, sage, warm cream). Add the MindMirror logo sticker.
9. Insulation tape over any exposed metal so nothing shorts when it's squeezed.

Test it again after boxing it. Glue and squeezing is where wires come loose.

---

## Part 9. Demo-day tips

- **Bring a backup**: the web app has a "talk to MindMirror" mic button that uses the same hub. If the necklace dies on stage, use that and keep going.
- Charge the power bank the night before. Bring two USB cables.
- In a noisy hall: hold the necklace close to the mouth to speak, then hold it up near the judge to hear the reply.
- Keep the Serial Monitor open on a second laptop during practice. It tells you what went wrong.
- Rehearse the exact sentence you'll say on stage at least 5 times with the real hardware.
