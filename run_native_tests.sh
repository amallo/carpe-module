#!/bin/bash

# Script d'exécution des tests natifs CARPE MODULE
# Clean Architecture + Dependency Injection
# Platform: Native (Desktop)

echo "🧪 CARPE MODULE - Native Test Runner"
echo "===================================="
echo "Architecture: Clean Architecture with Dependency Injection"
echo "Platform: Native Desktop (macOS/Linux)"
echo ""

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Fonction d'aide
show_help() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  test      - Exécuter les tests natifs"
    echo "  clean     - Nettoyer les fichiers de build"
    echo "  rebuild   - Clean + build + test"
    echo "  help      - Afficher cette aide"
    echo ""
    echo "Exemples:"
    echo "  $0 test     # Exécuter les tests"
    echo "  $0 rebuild  # Reconstruire et tester"
}

# Vérifier que make est disponible
check_dependencies() {
    if ! command -v make &> /dev/null; then
        echo -e "${RED}❌ Erreur: make n'est pas installé${NC}"
        exit 1
    fi
    
    if ! command -v g++ &> /dev/null; then
        echo -e "${RED}❌ Erreur: g++ n'est pas installé${NC}"
        exit 1
    fi
}

# Exécuter les tests
run_tests() {
    echo -e "${YELLOW}🔨 Compilation et exécution des tests...${NC}"
    echo ""
    
    if make test; then
        echo ""
        echo -e "${GREEN}✅ Tous les tests ont réussi !${NC}"
        echo ""
        echo "🏗️  Architecture testée:"
        echo "   - Injection de dépendances ✓"
        echo "   - Mocks déterministes ✓" 
        echo "   - Tests unitaires isolés ✓"
        echo "   - Framework Unity ✓"
        return 0
    else
        echo ""
        echo -e "${RED}❌ Certains tests ont échoué${NC}"
        return 1
    fi
}

# Nettoyer
clean_build() {
    echo -e "${YELLOW}🧹 Nettoyage des fichiers de build...${NC}"
    make clean
    echo -e "${GREEN}✅ Nettoyage terminé${NC}"
}

# Reconstruire et tester
rebuild_and_test() {
    echo -e "${YELLOW}🔄 Reconstruction complète...${NC}"
    clean_build
    echo ""
    run_tests
}

# Fonction principale
main() {
    check_dependencies
    
    case "${1:-test}" in
        "test")
            run_tests
            ;;
        "clean")
            clean_build
            ;;
        "rebuild")
            rebuild_and_test
            ;;
        "help"|"-h"|"--help")
            show_help
            ;;
        *)
            echo -e "${RED}❌ Option invalide: $1${NC}"
            echo ""
            show_help
            exit 1
            ;;
    esac
}

# Exécuter la fonction principale
main "$@" 