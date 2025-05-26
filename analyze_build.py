#!/usr/bin/env python3
import os
import re

def analyze_build():
    print("🔍 ANALYSE COMPLÈTE DU BUILD ACTUEL\n")
    
    # Données du build actuel
    text = 228985
    data = 85668
    bss = 7041
    flash_total = 4 * 1024 * 1024  # 4MB
    ram_total = 320 * 1024  # 320KB
    
    flash_used = text + data
    ram_used = data + bss
    
    print("📊 USAGE MÉMOIRE:")
    print(f"  💾 FLASH: {flash_used:,} bytes ({flash_used/1024:.1f} KB) = {flash_used/flash_total*100:.1f}%")
    print(f"  🧠 RAM:   {ram_used:,} bytes ({ram_used/1024:.1f} KB) = {ram_used/ram_total*100:.1f}%")
    print()
    
    print("📋 SEGMENTS DÉTAILLÉS:")
    print(f"  - TEXT (code exécutable):     {text:,} bytes ({text/1024:.1f} KB)")
    print(f"  - DATA (variables initialisées): {data:,} bytes ({data/1024:.1f} KB)")
    print(f"  - BSS (variables non-init):   {bss:,} bytes ({bss/1024:.1f} KB)")
    print()
    
    print("📚 LIBRAIRIES UTILISÉES:")
    libs = [
        ("LoRa", "~5-8 KB", "Communication LoRa"),
        ("Adafruit GFX", "~15-25 KB", "Graphiques de base"),
        ("Adafruit SSD1306", "~10-20 KB", "Driver écran OLED"),
        ("WiFi", "~30-50 KB", "Stack WiFi (via NVS)"),
        ("Wire", "~3-5 KB", "Communication I2C"),
        ("Preferences/NVS", "~8-15 KB", "Stockage persistant"),
        ("Framework Arduino", "~150-200 KB", "Core Arduino ESP32")
    ]
    
    total_estimated = 0
    for name, size_str, desc in libs:
        # Extraire la taille moyenne
        sizes = re.findall(r'(\d+)', size_str)
        if len(sizes) >= 2:
            avg_size = (int(sizes[0]) + int(sizes[1])) / 2
        else:
            avg_size = int(sizes[0]) if sizes else 10
        total_estimated += avg_size
        print(f"  - {name:<20} {size_str:<12} {desc}")
    
    print(f"\n  Total estimé: ~{total_estimated:.0f} KB (vs {flash_used/1024:.1f} KB réel)")
    print()
    
    print("⚠️  POINTS D'ATTENTION:")
    print(f"  - Flash à {flash_used/flash_total*100:.1f}% pour un projet basique")
    print(f"  - RAM à {ram_used/ram_total*100:.1f}% (acceptable)")
    print(f"  - Adafruit libs sont volumineuses (~35-45 KB)")
    print(f"  - WiFi/NVS ajoutent ~40-65 KB")
    print()
    
    print("🎯 OPTIMISATIONS POSSIBLES:")
    print("  1. Remplacer Adafruit SSD1306 → SSD1306Ascii (-25-35 KB)")
    print("  2. Remplacer NVS → EEPROM (-15-25 KB)")
    print("  3. Flags optimisation compilateur (-10-20 KB)")
    print("  4. Éviter WiFi si pas nécessaire (-30-50 KB)")
    print()
    
    print("🚀 PROJECTION AVEC BLE/CRYPTO:")
    ble_estimate = 80  # KB
    crypto_estimate = 30  # KB
    parsing_estimate = 20  # KB
    
    future_total = flash_used/1024 + ble_estimate + crypto_estimate + parsing_estimate
    print(f"  - BLE Stack: ~{ble_estimate} KB")
    print(f"  - Crypto (mbedTLS): ~{crypto_estimate} KB")
    print(f"  - Parsing/Protocol: ~{parsing_estimate} KB")
    print(f"  - TOTAL PROJETÉ: ~{future_total:.0f} KB ({future_total/4096*100:.1f}% de flash)")
    
    if future_total/4096 > 0.5:
        print("  ⚠️  RISQUE: Dépassement probable des 50% de flash !")
    else:
        print("  ✅ Projection acceptable")

if __name__ == "__main__":
    analyze_build() 