## CARPE Messaging Protocol v0 – Authentication (BLE)

This document defines the minimal binary exchange between the App and the Device for PIN-based pairing/authentication.

### Scope (v0)
- App ↔ Device over BLE characteristic write/notify
- Authentication only (PIN validation). Future messages will extend this spec.

### Conventions
- Byte order: big-endian (network order) for multi-byte integers.
- All numeric values are unsigned unless stated otherwise.
- All fields are mandatory unless stated otherwise.

### Message Frame
Each message is a concatenation of HEADER then PAYLOAD.

```
[HEADER][PAYLOAD]
```

#### HEADER (6 bytes)
- TYPE (1 byte): Message type code
- LENGTH (2 bytes): Payload length in bytes (0..65535)
- FLAGS (1 byte): Reserved for future use (must be 0x00 in v0)
- NONCE (2 bytes): Anti-replay value (see Security)

#### PAYLOAD (variable)
Depends on TYPE. See per-message tables below.

### Message Types
| TYPE | Name           | Direction      | Description |
|------|----------------|----------------|-------------|
| 0x01 | PAIR_REQUEST   | App → Device   | Submit 4-digit PIN with timestamp |
| 0x02 | PAIR_RESPONSE  | Device → App   | Result, attempts left, session id |
| 0x03 | PAIR_CONFIRM   | App → Device   | Confirm session on success |

---

### PAIR_REQUEST (TYPE = 0x01)

Header
| Field | Size | Notes |
|-------|------|-------|
| TYPE  | 1    | 0x01 |
| LENGTH| 2    | Must be 0x0006 |
| FLAGS | 1    | 0x00 in v0 |
| NONCE | 2    | Random per message (App generated) |

Payload
| Field     | Size | Type | Description |
|-----------|------|------|-------------|
| PIN_CODE  | 4    | u32  | 4-digit PIN encoded as integer (e.g., 1234 → 0x000004D2) |
| TIMESTAMP | 2    | u16  | Seconds since app start (mod 65536) at send time |

Example (PIN=1234, TS=9):
```
01 00 06 00 AA BB 00 00 04 D2 00 09
```
Where AA BB is NONCE (big-endian).

---

### PAIR_RESPONSE (TYPE = 0x02)

Header
| Field | Size | Notes |
|-------|------|-------|
| TYPE  | 1    | 0x02 |
| LENGTH| 2    | Must be 0x0003 |
| FLAGS | 1    | 0x00 in v0 |
| NONCE | 2    | Echo or fresh (Device generated) – see Security |

Payload
| Field         | Size | Type | Description |
|---------------|------|------|-------------|
| STATUS        | 1    | u8   | See Status Codes |
| ATTEMPTS_LEFT | 1    | u8   | Remaining tries in current window (0..3) |
| SESSION_ID    | 1    | u8   | Valid if STATUS=OK, undefined otherwise |

Status Codes
| Code | Name          | Meaning |
|------|---------------|---------|
| 0x00 | OK            | PIN valid |
| 0x01 | INVALID_PIN   | PIN incorrect |
| 0x02 | ERROR         | Internal error |
| 0x03 | TIMEOUT       | Validation window exceeded |
| 0x04 | MAX_ATTEMPTS  | Too many attempts |

Example (OK, 2 left, session 0x7F):
```
02 00 03 00 CC DD 00 02 7F
```
Where CC DD is NONCE.

---

### PAIR_CONFIRM (TYPE = 0x03)

Header
| Field | Size | Notes |
|-------|------|-------|
| TYPE  | 1    | 0x03 |
| LENGTH| 2    | Must be 0x0001 |
| FLAGS | 1    | 0x00 in v0 |
| NONCE | 2    | New random (App generated) or echo per session policy |

Payload
| Field      | Size | Type | Description |
|------------|------|------|-------------|
| SESSION_ID | 1    | u8   | Session to confirm (from PAIR_RESPONSE) |

Example (session 0x7F):
```
03 00 01 00 EE FF 7F
```

---

### Flow
```
App → Device:   PAIR_REQUEST  (PIN_CODE, TIMESTAMP, NONCE_app)
Device → App:   PAIR_RESPONSE (STATUS, ATTEMPTS_LEFT, SESSION_ID, NONCE_dev)
App → Device:   PAIR_CONFIRM  (SESSION_ID, NONCE_app2)   [only if STATUS = OK]
```

### Constraints
- PIN length: 4 digits
- Max attempts: 3 (per pairing window/session)
- Validation timeout: 10 seconds (from Device receive to decision)
- FLAGS must be 0x00 in v0 (senders must set to 0; receivers must ignore non-zero but may reject in strict mode)

### Security Notes
- NONCE: 16-bit random value to mitigate replay; sender must vary per message. Receiver should track recent nonces per peer/session for a short window.
- TIMESTAMP in PAIR_REQUEST: Used to validate freshness; Device should compare against its receive time and reject if delta > 10s.
- SESSION_ID: 8-bit identifier chosen by Device on OK; must be echoed by App in PAIR_CONFIRM.

### Validation Rules (Receiver)
1. Verify header size and LENGTH matches expected for TYPE.
2. FLAGS must be 0 in v0 (or be tolerated/ignored per policy).
3. Check anti-replay: NONCE not seen recently for this peer/session.
4. For PAIR_REQUEST: validate 10s freshness using TIMESTAMP and local time; then validate PIN; decrement remaining attempts; respond accordingly.
5. For PAIR_RESPONSE: App logic uses STATUS and ATTEMPTS_LEFT; on OK, store SESSION_ID and continue with PAIR_CONFIRM.
6. For PAIR_CONFIRM: Verify SESSION_ID is active; on success, mark session authenticated.

### Error Handling (Recommendations)
- On malformed frame or header/type mismatch: ignore silently or respond with ERROR depending on UX strategy.
- On MAX_ATTEMPTS: Device should throttle or require backoff/reset.

### Future Extensions (Out of scope v0)
- Additional message types for configuration and data
- Optional MIC/HMAC and encryption
- Larger NONCE and synchronized counters


