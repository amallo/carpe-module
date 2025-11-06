# CARPE Module

An ESP32 firmware module implementing secure peer-to-peer authentication over BLE (Bluetooth Low Energy).

## 🎯 Overview

CARPE Module is an embedded system firmware designed for ESP32 devices, implementing a secure authentication protocol between devices and mobile applications. The project is organized with clear separation between business logic and platform-specific code, making it maintainable and testable.

## 🏗️ Architecture

The project is organized with clear separation between:

- **Core Logic**: Business rules, use cases, and domain models
- **Platform Code**: ESP32 and Arduino-specific implementations
- **Interfaces**: Abstract contracts for providers and generators

### Module Structure

```
src/core/
├── config/          # Configuration management
├── device/          # Device setup and ID generation
├── logging/         # Logging abstraction
├── peer/            # Peer authentication and messaging
├── random/          # Random number generation
└── time/            # Time abstraction
```

Each module follows a consistent structure:
- Interfaces at the module root
- Implementations in `providers/infra/` or `generators/infra/`
- Use cases at module root when applicable

## 🔌 Communication Protocol

The module implements a binary messaging protocol over BLE for secure authentication. The protocol specification is documented in **[protocol.md](protocol.md)**.

### Key Features

- **Binary Protocol**: Efficient fixed-size message encoding
- **Anti-replay Protection**: NONCE-based message validation
- **Type-safe Messages**: Strongly-typed message classes with dedicated encoders
- **Extensible**: Easy to add new message types

For complete protocol specification including all message types, see **[protocol.md](protocol.md)**.

## 🚀 Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) installed
- ESP32 development board (tested with TTGO LoRa32 v1)
- USB cable for programming

### Building

```bash
# Build firmware for ESP32
pio run -e carpe-lora

# Upload to device
pio run -e carpe-lora --target upload

# Monitor serial output
pio device monitor
```

### Testing

The project includes comprehensive test suites:

```bash
# Run native desktop tests (fast, recommended for development)
make test

# Or use the test script
./run_native_tests.sh test

# Run ESP32 integration tests (requires hardware)
pio test -e test
```

For detailed testing documentation, see [test/README.md](test/README.md).

## 📦 Dependencies

### Core Libraries

- **NimBLE-Arduino** (v1.4.0+): Lightweight BLE stack
- **LoRa** (v0.8.0): LoRa communication (if needed)
- **Adafruit GFX & SSD1306**: OLED display support

### Build Configuration

- **Platform**: ESP32 (espressif32)
- **Framework**: Arduino
- **C++ Standard**: C++17
- **Optimization**: `-Os` (size optimization)

## 🏛️ Design Principles

The project follows these design principles:

1. **Separation of Concerns**: Business logic separated from platform code
2. **Interface-based Design**: Small, focused interfaces for flexibility
3. **Dependency Injection**: Dependencies provided via constructors
4. **Testability**: Core logic can be tested without hardware

### Design Patterns

- **Provider Pattern**: Abstract interfaces with platform-specific implementations
- **Use Case Pattern**: Business logic organized in use case classes
- **Encoder Pattern**: Message encoding handled by dedicated encoder classes
- **Factory Pattern**: Message creation via factory methods

## 📁 Project Structure

```
carpe-module/
├── src/
│   ├── core/              # Core domain logic
│   │   ├── config/        # Configuration management
│   │   ├── device/        # Device setup
│   │   ├── peer/          # Peer authentication
│   │   │   ├── model/     # Message models
│   │   │   ├── encoders/  # Message encoders
│   │   │   └── usecases/  # Authentication use cases
│   │   └── ...
│   └── main.cpp           # Application entry point
├── test/                  # Test suite
│   ├── peer/              # Peer authentication tests
│   └── transport/         # Transport layer mocks
├── protocol.md            # Protocol specification
├── platformio.ini         # PlatformIO configuration
└── README.md              # This file
```

## 🔐 Security Features

- **NONCE-based Anti-replay**: Each message includes a random nonce
- **Fixed-size Encoding**: Predictable message sizes prevent buffer overflow
- **Type Validation**: Message type validation at protocol level
- **Session Management**: Secure session creation after authentication

## 🧪 Testing Strategy

### Unit Tests (Desktop)

Fast, hardware-independent tests for business logic:
- Use case validation
- Message encoding/decoding
- Business rule verification

### Integration Tests (ESP32)

Hardware-specific tests:
- BLE communication
- Memory constraints
- Real-time behavior

See [test/README.md](test/README.md) for detailed testing documentation.

## 📚 Documentation

- **[protocol.md](protocol.md)**: Complete protocol specification
- **[test/README.md](test/README.md)**: Testing guide and best practices
- **Code Comments**: Inline documentation following Doxygen style

## 🛠️ Development

### Code Style

- Keep business logic separate from platform code
- Use dependency injection
- Keep interfaces small and focused
- Write tests for new features

### Adding New Messages

1. Define message payload structure
2. Create message encoder in the same `.cpp` file
3. Update `protocol.md` with message specification
4. Add tests for encoding/decoding

### Module Organization

When adding new modules:

1. Create interface at module root
2. Place implementations in `providers/infra/` or `generators/infra/`
3. Add use cases at module root if needed
4. Update includes in dependent files

## 📄 License

[Add your license information here]

## 🤝 Contributing

[Add contribution guidelines here]

## 📞 Support

[Add support/contact information here]

---

**Note**: This project is actively developed. The protocol and architecture may evolve. Always refer to the latest `protocol.md` for the current protocol specification.

