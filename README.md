# MindMirror: Round 2 preparation

Team **HTTP Dino** (K S Pankaj, Merel Riha Dsouza, A B Kishore Krishna), St Aloysius. 1st place in Round 1.
CODE MEET 2026 Round 2, Srinivas University, **Sunday 1 Nov 10:00 AM, 24 hours, offline; final presentation Monday 2 Nov 10:00 AM**. Problem 2: **Mind Check**.

This repo holds the plans. The project itself is built from scratch in a new repo during the 24 hours.

## Read in this order

| File | For | What's in it |
|---|---|---|
| [TEAM_PLAN.md](TEAM_PLAN.md) | **everyone, first** | roles and who owns which code, the before-the-event checklist, the hour-by-hour plan (Sun 10 AM to Mon 10 AM), who presents what |
| [APP_BUILD_GUIDE.md](APP_BUILD_GUIDE.md) | Pankaj (Kishore and Merel: sections 1, 6, 8) | scope, stack, setup, data model, the signal engine spec, screens, privacy wording, build order, Plan B |
| [NECKLACE_GUIDE.md](NECKLACE_GUIDE.md) | Pankaj + Kishore | the AI necklace from zero: parts, soldering, pin tables, 4 hardware tests, the laptop hub, firmware, troubleshooting, making the pendant |
| [MEREL_GUIDE.md](MEREL_GUIDE.md) | Merel | the project in plain words, your code (3 games, Play room, Support screen, app words), interviews, leading the presentation and the demo video |
| [KISHORE_GUIDE.md](KISHORE_GUIDE.md) | Kishore | the project in plain words, the necklace explained deeply, your code (UI components, check-in, breathe), hardware tests, the pendant case |
| [PITCH_SCRIPT.md](PITCH_SCRIPT.md) | Merel (everyone: sections 1 and 9) | the full pitch in simple English with Merel speaking every slide, features, tech stack in plain words, hook points, short versions, how to speak, Q&A, practice plan, a printable cue card |
| [JUDGE_QA.md](JUDGE_QA.md) | **everyone** | ~70 judge questions with answers, who leads and who backs up, what to say when a judge walks up |
| [deck/MindMirror_Final.pptx](deck/MindMirror_Final.pptx) | **everyone** | the final presentation with a speaker script under every slide |
| [reference/](reference) | Pankaj | hub server and ESP32 code used by the necklace guide |

## The plan in one paragraph

Build **six things that fully work**: check-in, insights against the student's own baseline with proof, the support ladder with crisis routing, the companion chat, a **Play room of 3 calm games**, and the **AI necklace** (hold a button, talk, hear a reply from the necklace's speaker; the turn appears live in the app). The necklace uses an ESP32 + INMP441 mic + MAX98357A amp + 8 Ω speaker, and talks over the phone hotspot to a small **hub** on the laptop that does speech-to-text, the reply and the voice. Breathing room and planner if time allows. Visual themes are cut; the smartwatch is future work. Every teammate owns code under their own GitHub account.

## The three things that must happen before 1 November

1. **Solder the header pins** on the mic and amp, and pass hardware tests 1 to 4 ([necklace guide, Part 4](NECKLACE_GUIDE.md#part-4-test-one-thing-at-a-time)).
2. **Install everything** on all three laptops and get a Groq API key ([team plan, "Before the event"](TEAM_PLAN.md#2-before-the-event-30-to-31-oct)).
3. **Pack the extension board**, power bank and cables. The rules say teams bring their own.

## Status of the reference code

- `reference/hub/server.mjs`: run end to end here with a simulated necklace (chunked audio in, reply audio out, live event to the app) in mock mode. Not yet run against the real Groq and Edge services from this environment, because they're blocked here. Run it with your key on 31 Oct.
- `reference/firmware/`: checked for errors, but not compiled for the ESP32 here (the ESP32 toolchain couldn't be downloaded in this environment) and not run on hardware. Compile and run tests 1 to 4 on 31 Oct.

MindMirror is not a medical device and does not diagnose. If you are struggling, call Tele-MANAS **14416** (free, 24×7) or **112**.
