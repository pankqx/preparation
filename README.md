# MindMirror: Round 2 preparation

Team **HTTP Dino** (K S Pankaj, Merel Riha Dsouza, A B Kishore Krishna), St Aloysius. 1st place in Round 1.
CODE MEET 2026 Round 2, Srinivas University, **1 Nov 10:00 AM, 24 hours, offline**. Problem 2: **Mind Check**.

This repo holds the plans. The project itself is built from scratch in a new repo during the 24 hours.

## Read in this order

| File | For | What's in it |
|---|---|---|
| [TEAM_PLAN.md](TEAM_PLAN.md) | **everyone, first** | roles, the before-the-event checklist, the hour-by-hour plan, and personal guides with copy-paste ChatGPT prompts for Merel and Kishore |
| [APP_BUILD_GUIDE.md](APP_BUILD_GUIDE.md) | Pankaj (Kishore and Merel: sections 1, 6, 8) | scope, stack, setup, data model, the signal engine spec, screens, privacy wording, build order, Plan B |
| [NECKLACE_GUIDE.md](NECKLACE_GUIDE.md) | Pankaj + Kishore | the AI necklace from zero: parts, soldering, pin tables, 4 hardware tests, the laptop hub, firmware, troubleshooting, making the pendant |
| [reference/](reference) | Pankaj | hub server and ESP32 code used by the necklace guide |

## The plan in one paragraph

Build **five things that fully work**: check-in, insights against the student's own baseline with proof, the support ladder with crisis routing, the companion chat, and the **AI necklace** (hold a button, talk, hear a reply from the necklace's speaker; the turn appears live in the app). The necklace uses an ESP32 + INMP441 mic + MAX98357A amp + 8 Ω speaker, and talks over the phone hotspot to a small **hub** on the laptop that does speech-to-text, the reply and the voice. Planner and breathing room only if time allows. Everything else from Round 1 is cut on purpose.

## The three things that must happen before 1 November

1. **Solder the header pins** on the mic and amp, and pass hardware tests 1 to 4 ([necklace guide, Part 4](NECKLACE_GUIDE.md#part-4-test-one-thing-at-a-time)).
2. **Install everything** on all three laptops and get a Groq API key ([team plan, "Before the event"](TEAM_PLAN.md#before-the-event-today-and-tomorrow-30-to-31-oct)).
3. **Pack the extension board**, power bank and cables. The rules say teams bring their own.

## Status of the reference code

- `reference/hub/server.mjs`: run end to end here with a simulated necklace (chunked audio in, reply audio out, live event to the app) in mock mode. Not yet run against the real Groq and Edge services from this environment, because they're blocked here. Run it with your key on 31 Oct.
- `reference/firmware/`: checked for errors, but not compiled for the ESP32 here (the ESP32 toolchain couldn't be downloaded in this environment) and not run on hardware. Compile and run tests 1 to 4 on 31 Oct.

MindMirror is not a medical device and does not diagnose. If you are struggling, call Tele-MANAS **14416** (free, 24×7) or **112**.
