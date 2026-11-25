/**
 * @file Checks.hpp
 * @brief Compile-time checks for the exercises. Included at the end of main.cpp.
 * @details Set an exercise to 1 when you think it's done. A wrong answer then fails
 * the build with a message saying which case is wrong.
 */
#ifndef CHECKS_HPP
#define CHECKS_HPP

#define CHECK_TASK_2 0
#define CHECK_TASK_3 0
#define CHECK_TASK_5 0
#define CHECK_TASK_6 0
#define CHECK_TASK_8 0
#define CHECK_TASK_9 0
#define CHECK_TASK_10 0

namespace checks
{
	constexpr bool eq(const char *a, const char *b)
	{
		while (*a && *a == *b)
		{
			++a;
			++b;
		}
		return *a == *b;
	}
	constexpr bool hexByte(uint8_t v, const char *want) { char b[8] = {}; formatHexByte(v, b); return eq(b, want); }
	constexpr bool hexWord(uint16_t v, const char *want) { char b[8] = {}; formatHexWord(v, b); return eq(b, want); }
	constexpr bool signed2(int8_t v, const char *want) { char b[8] = {}; formatSignedInt2(v, b); return eq(b, want); }
	constexpr bool fixed2(uint16_t v, const char *want) { char b[8] = {}; formatFixedPoint2(v, b); return eq(b, want); }

	constexpr bool pedalRoundTrip(uint16_t a5, uint16_t a3, uint16_t br, uint16_t hall, uint8_t st, uint8_t ft)
	{
		TelemetryFramePedal in{};
		in.apps_5v = a5;
		in.apps_3v3 = a3;
		in.brake = br;
		in.hall_sensor = hall;
		in.status.byte = st;
		in.faults.byte = ft;
		TelemetryFramePedal out = unpackPedal(in.fromCanFrame());
		return out.apps_5v == a5 && out.apps_3v3 == a3 && out.brake == br && out.hall_sensor == hall &&
			   out.status.byte == st && out.faults.byte == ft;
	}
	constexpr bool motorRoundTrip(uint16_t tq, uint16_t rpm, uint16_t err, uint16_t warn)
	{
		TelemetryFrameMotor in{tq, rpm, err, warn};
		TelemetryFrameMotor out = unpackMotor(in.fromCanFrame());
		return out.torque_val == tq && out.motor_rpm == rpm && out.motor_error == err && out.motor_warn == warn;
	}

	constexpr int8_t newest(uint8_t a, uint8_t b, uint8_t c, uint8_t validMask = 0b111)
	{
		const uint8_t seq[ODO_SLOTS] = {a, b, c};
		const bool valid[ODO_SLOTS] = {(validMask & 1) != 0, (validMask & 2) != 0, (validMask & 4) != 0};
		return newestSlot(seq, valid);
	}
	constexpr int8_t encCycle(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3)
	{
		return static_cast<int8_t>(ENC_STEP[(s0 << 2) | s1] + ENC_STEP[(s1 << 2) | s2] + ENC_STEP[(s2 << 2) | s3] + ENC_STEP[(s3 << 2) | s0]);
	}
}

#if CHECK_TASK_2
static_assert(checks::hexByte(0x3C, "3C"), "Task 2: formatHexByte(0x3C) should be \"3C\"");
static_assert(checks::hexByte(0x05, "05"), "Task 2: formatHexByte(0x05) should be \"05\"");
static_assert(checks::hexByte(0xFF, "FF"), "Task 2: formatHexByte(0xFF) should be \"FF\"");
static_assert(checks::hexWord(0xBEEF, "BEEF"), "Task 2: formatHexWord(0xBEEF) should be \"BEEF\"");
static_assert(checks::signed2(7, "+07"), "Task 2: formatSignedInt2(7) should be \"+07\"");
static_assert(checks::signed2(-25, "-25"), "Task 2: formatSignedInt2(-25) should be \"-25\"");
static_assert(checks::signed2(0, " 00"), "Task 2: formatSignedInt2(0) should be \" 00\"");
static_assert(checks::signed2(99, "+99"), "Task 2: formatSignedInt2(99) should be \"+99\"");
static_assert(checks::signed2(120, "+99"), "Task 2: formatSignedInt2(120) should clamp to \"+99\"");
static_assert(checks::signed2(-128, "-99"), "Task 2: formatSignedInt2(-128) should clamp to \"-99\"");
static_assert(checks::fixed2(365, "3.65"), "Task 2: formatFixedPoint2(365) should be \"3.65\"");
static_assert(checks::fixed2(7, "0.07"), "Task 2: formatFixedPoint2(7) should be \"0.07\"");
static_assert(checks::fixed2(400, "4.00"), "Task 2: formatFixedPoint2(400) should be \"4.00\"");
static_assert(checks::fixed2(1234, "9.99"), "Task 2: formatFixedPoint2(1234) should clamp to \"9.99\"");
#endif

#if CHECK_TASK_3
static_assert(throttlePercent(0) == 0, "Task 3: below THROTTLE_ADC_MIN is 0");
static_assert(throttlePercent(THROTTLE_ADC_MIN) == 0, "Task 3: THROTTLE_ADC_MIN is 0");
static_assert(throttlePercent(120) == 0, "Task 3: 2 % is inside the deadband, should be 0");
static_assert(throttlePercent(130) == 3, "Task 3: raw 130 should be 3 %");
static_assert(throttlePercent(511) == 49, "Task 3: raw 511 should be 49 % (round down)");
static_assert(throttlePercent(900) == 97, "Task 3: raw 900 should be 97 %");
static_assert(throttlePercent(910) == 100, "Task 3: 98 % is inside the deadband, should be 100");
static_assert(throttlePercent(1023) == 100, "Task 3: above THROTTLE_ADC_MAX is 100");
#endif

#if CHECK_TASK_5
static_assert(isStale(1000, 0, 500), "Task 5: 1000 ms after 0 with a 500 ms timeout is stale");
static_assert(!isStale(500, 0, 500), "Task 5: exactly the timeout is not stale yet");
static_assert(!isStale(10, 0xFFFFFF00UL, 500), "Task 5: 266 ms across the millis() wrap is not stale");
static_assert(!isStale(0xFFFFFF10UL, 0xFFFFFF00UL, 500), "Task 5: 16 ms before the wrap is not stale (last + timeout overflows!)");
static_assert(isStale(1000, 0xFFFFFF00UL, 500), "Task 5: 1256 ms across the wrap is stale");
static_assert(isStale(0, ~0UL - STALE_MS_BMS, STALE_MS_BMS), "Task 5: the boot value of lastRxMs must read as stale");
static_assert(!isStale(1000, 0, 2500), "Task 5: use the timeout parameter: 1000 ms is not stale with a 2500 ms timeout");
static_assert(isStale(3000, 0, 2500), "Task 5: use the timeout parameter: 3000 ms is stale with a 2500 ms timeout");
#endif

#if CHECK_TASK_6
static_assert(checks::encCycle(0b00, 0b01, 0b11, 0b10) == 4, "Task 6: 00>01>11>10>00 should be +4");
static_assert(checks::encCycle(0b00, 0b10, 0b11, 0b01) == -4, "Task 6: 00>10>11>01>00 should be -4");
static_assert(ENC_STEP[0b0000] == 0 && ENC_STEP[0b0101] == 0 && ENC_STEP[0b1111] == 0 && ENC_STEP[0b1010] == 0, "Task 6: no change = 0");
static_assert(ENC_STEP[0b0011] == 0 && ENC_STEP[0b1100] == 0 && ENC_STEP[0b0110] == 0 && ENC_STEP[0b1001] == 0, "Task 6: both pins flipped = 0");
#endif

#if CHECK_TASK_9
static_assert(checks::pedalRoundTrip(0, 0, 0, 0, 0, 0), "Task 9: all zero");
static_assert(checks::pedalRoundTrip(1023, 1023, 1023, 1023, 0xFF, 0xFF), "Task 9: all max");
static_assert(checks::pedalRoundTrip(1023, 0, 0, 0, 0, 0), "Task 9: apps_5v only");
static_assert(checks::pedalRoundTrip(0, 1023, 0, 0, 0, 0), "Task 9: apps_3v3 only");
static_assert(checks::pedalRoundTrip(0, 0, 1023, 0, 0, 0), "Task 9: brake only");
static_assert(checks::pedalRoundTrip(0, 0, 0, 1023, 0, 0), "Task 9: hall_sensor only");
static_assert(checks::pedalRoundTrip(0x2AA, 0x155, 0x3C3, 0x0F0, 0x83, 0x41), "Task 9: mixed bits");
#endif

#if CHECK_TASK_8
static_assert(checks::motorRoundTrip(0x1234, 0x5678, 0x9ABC, 0xDEF0), "Task 8: field order / byte order");
static_assert(checks::motorRoundTrip(0xFFFF, 0, 0xFFFF, 0), "Task 8: alternating max");
static_assert(checks::motorRoundTrip(0x00FF, 0xFF00, 0x0001, 0x8000), "Task 8: high/low byte swap");
#endif

#if CHECK_TASK_10
static_assert(checks::newest(5, 6, 7) == 2, "Task 10: seq 5,6,7 -> slot 2");
static_assert(checks::newest(9, 7, 8) == 0, "Task 10: seq 9,7,8 -> slot 0");
static_assert(checks::newest(255, 0, 1) == 2, "Task 10: seq 255,0,1 -> slot 2 (wrap)");
static_assert(checks::newest(0, 254, 255) == 0, "Task 10: seq 0,254,255 -> slot 0 (wrap)");
static_assert(checks::newest(5, 6, 7, 0b011) == 1, "Task 10: slot 2 invalid -> slot 1");
static_assert(checks::newest(5, 6, 7, 0b001) == 0, "Task 10: only slot 0 valid -> slot 0");
static_assert(checks::newest(5, 6, 7, 0b000) == -1, "Task 10: no valid slot -> -1");
#endif

#endif // CHECKS_HPP
