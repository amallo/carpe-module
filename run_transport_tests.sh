#!/bin/bash

# CARPE MODULE - Transport Tests Runner
# Script pour exécuter les tests de transport (Bluetooth, etc.)

set -e

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🧪 CARPE MODULE - Transport Test Runner${NC}"
echo "======================================"
echo -e "Platform: ${YELLOW}Native Desktop (macOS/Linux)${NC}"
echo ""

# Fonction d'aide
show_help() {
    echo "Usage: $0 [command]"
    echo ""
    echo "Commands:"
    echo "  test     - Compile and run transport tests"
    echo "  rebuild  - Clean and rebuild tests"
    echo "  clean    - Clean build files"
    echo "  help     - Show this help"
    echo ""
    echo "Examples:"
    echo "  $0 test"
    echo "  $0 rebuild"
}

# Fonction de nettoyage
clean_build() {
    echo -e "${YELLOW}🧹 Nettoyage des fichiers de build...${NC}"
    rm -rf build/test_transport
    echo -e "${GREEN}✅ Nettoyage terminé${NC}"
}

# Fonction de compilation et test
run_tests() {
    echo -e "${BLUE}🔨 Compilation et exécution des tests de transport...${NC}"
    echo ""
    
    # Compilation du test Bluetooth PIN Authentication
    echo -e "${YELLOW}Compilation du test Bluetooth PIN Authentication...${NC}"
    g++ -std=c++17 -Wall -Wextra -DNATIVE_BUILD \
        -I. -Itest -Isrc \
        -DUNITY_INCLUDE_DOUBLE -DUNITY_DOUBLE_PRECISION=1e-12 \
        -DUNITY_SUPPORT_TEST_CASES -DUNITY_OUTPUT_COLOR \
        -Iunity/src \
        test/transport/test_bluetooth_pin_authentication.cpp \
        unity/src/unity.c \
        -o build/test_transport
    
    echo -e "${GREEN}✅ Compilation réussie${NC}"
    echo ""
    
    # Exécution du test
    echo -e "${YELLOW}Exécution du test Bluetooth PIN Authentication...${NC}"
    ./build/test_transport
    
    echo ""
    echo -e "${GREEN}🎯 Tous les tests de transport sont passés avec succès !${NC}"
    echo ""
    echo -e "${BLUE}🏗️  Architecture testée:${NC}"
    echo "   - Authentification PIN ✓"
    echo "   - Gestion des tentatives ✓"
    echo "   - Sécurité des connexions ✓"
    echo "   - Framework Unity ✓"
}

# Gestion des arguments
case "${1:-test}" in
    "test")
        run_tests
        ;;
    "rebuild")
        clean_build
        run_tests
        ;;
    "clean")
        clean_build
        ;;
    "help"|"-h"|"--help")
        show_help
        ;;
    *)
        echo -e "${RED}❌ Commande inconnue: $1${NC}"
        echo ""
        show_help
        exit 1
        ;;
esac
