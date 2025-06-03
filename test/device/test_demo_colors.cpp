#include <unity.h>
#include <iostream>
#include <test/common/TestDisplay.h>

void setUp(void) {
    // Pas de setup spécial pour cette démo
}

void tearDown(void) {
    // Pas de teardown spécial pour cette démo
}

void test_demo_success() {
    TestDisplay::print(TestDisplay::TEST, "Test de démonstration - Succès");
    TEST_ASSERT_TRUE(true);
    TestDisplay::print(TestDisplay::SUCCESS, "Test réussi comme prévu");
}

void test_demo_failure() {
    TestDisplay::print(TestDisplay::TEST, "Test de démonstration - Échec volontaire");
    TestDisplay::print(TestDisplay::WARNING, "Ce test va échouer pour démontrer les couleurs d'erreur");
    
    // Ce test va échouer volontairement pour voir les couleurs
    TEST_ASSERT_EQUAL_STRING("Expected", "Actual");
    
    TestDisplay::print(TestDisplay::ERROR, "Cette ligne ne devrait jamais s'afficher");
}

int main() {
    TestDisplay::printSectionTitle("🎨 Démonstration des Couleurs Unity");
    
    TestDisplay::print(TestDisplay::INFO, "Ce test démontre les différents styles d'affichage :");
    TestDisplay::print(TestDisplay::SUCCESS, "Messages de succès en vert");
    TestDisplay::print(TestDisplay::ERROR, "Messages d'erreur en rouge");
    TestDisplay::print(TestDisplay::WARNING, "Messages d'avertissement en jaune");
    TestDisplay::print(TestDisplay::DEBUG, "Messages de debug en bleu");
    std::cout << std::endl;
    
    UNITY_BEGIN();
    
    RUN_TEST(test_demo_success);
    RUN_TEST(test_demo_failure);
    
    int result = UNITY_END();
    
    // Affichage du résumé avec échec attendu
    TestDisplay::printTestSummary(2, (result == 0) ? 2 : 1, result);
    
    TestDisplay::print(TestDisplay::INFO, "Ce test était prévu pour échouer afin de démontrer les couleurs !");
    
    return 0; // On retourne 0 même si un test échoue car c'était volontaire
} 