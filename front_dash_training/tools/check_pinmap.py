"""Style check for include/pinMap.h (Task 1): every pin must be written as a name
(PIN_PB3, PINB, PB3), never a bare number. It does not check that the pins are right.

Usage: python3 tools/check_pinmap.py
"""
import pathlib
import re
import sys

REQUIRED = ["CAN0_CS", "CAN1_CS", "CAN2_CS", "CAN_INT_BITS", "SD_CS", "GPIO_1", "GPIO_2",
            "PIN_ENC_A", "PIN_ENC_B", "ENC_B_PINREG", "ENC_B_BIT", "PIN_ENC_BTN", "HC12_SET"]
NAME = re.compile(r"PIN_P[B-D][0-7]|PIN[B-D]|P[B-D][0-7]")
DEFINE = re.compile(r"^[ \t]*#define[ \t]+(\w+)[ \t]*(.*?)[ \t]*(?://.*)?$", re.M)


def check(text):
    """Return a list of problems, empty if the file passes."""
    errors, seen = [], set()
    for name, value in DEFINE.findall(text):
        if name == "PIN_MAP_H":
            continue
        seen.add(name)
        tokens = re.findall(r"[^\s{},]+", value)
        bad = [t for t in tokens if not NAME.fullmatch(t)]
        if not tokens:
            errors.append(f"{name}: not filled in")
        elif bad:
            errors.append(f"{name}: '{value}' must use pin names like PIN_PB3 / PINB / PB3, not numbers")
    errors += [f"{n}: missing" for n in REQUIRED if n not in seen]
    return errors


if __name__ == "__main__":
    assert check("#define CAN1_CS 6 // pad 10") and not check(
        "#define CAN_INT_BITS {PB3, PB4, PB5}\n#define ENC_B_PINREG PINB\n"
        + "".join(f"#define {n} PIN_PB3\n" for n in REQUIRED if n != "CAN_INT_BITS")), "self-check"
    path = pathlib.Path(__file__).resolve().parent.parent / "include" / "pinMap.h"
    problems = check(path.read_text())
    print("\n".join(problems) or "pinMap.h style ok")
    sys.exit(1 if problems else 0)
