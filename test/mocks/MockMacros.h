#pragma once

#include "MockFramework.h"

/**
 * @brief Macros pour simplifier la création de mocks
 * Évite la duplication de code boilerplate
 */

// Macro pour déclarer une méthode mock avec paramètre
#define MOCK_METHOD_WITH_PARAM(method_name, param_type, return_type) \
    return_type method_name(const param_type& param) override { \
        record_call({#method_name, param}); \
        return get_return_value(#method_name); \
    }

// Macro pour déclarer une méthode mock sans paramètre
#define MOCK_METHOD_NO_PARAM(method_name, return_type) \
    return_type method_name() override { \
        record_call({#method_name, ""}); \
        return get_return_value(#method_name); \
    }

// Macro pour déclarer les méthodes de configuration fluide
#define MOCK_FLUENT_CONFIG(mock_class, method_name) \
    mock_class& will_##method_name##_return(bool value) { \
        set_return_value(#method_name, value); \
        return *this; \
    }

// Macro pour déclarer les méthodes de vérification
#define MOCK_VERIFY_CALLED(method_name) \
    bool was_##method_name##_called() const { \
        return was_called(#method_name); \
    }

#define MOCK_VERIFY_CALLED_WITH(method_name, param_type) \
    bool was_##method_name##_called_with(const param_type& param) const { \
        return was_called(#method_name, param); \
    }

// Macro pour déclarer les alias de compatibilité
#define MOCK_COMPAT_ALIAS(method_name) \
    void set_##method_name##_return(bool value) { set_return_value(#method_name, value); } \
    void add_##method_name##_return(bool value) { add_return_value(#method_name, value); }

/**
 * @brief Macro complète pour créer un mock simple
 */
#define DECLARE_SIMPLE_MOCK(interface_class, mock_name) \
    class mock_name : public interface_class, public GenericMock<MethodCall<std::string>> { \
    public: \
        mock_name() = default; \
        void reset() override { GenericMock::reset(); } \
    };

/**
 * @brief Template pour créer facilement des mocks de services
 */
template<typename T>
class ServiceMock : public T, public GenericMock<MethodCall<std::string>> {
public:
    ServiceMock() = default;
    void reset() override { GenericMock::reset(); }
    
    // Méthodes helper communes
    template<typename ParamType>
    void expect_call(const std::string& method, const ParamType& param) {
        // Future: ajout d'expectations
    }
    
    void verify_all_expectations() {
        // Future: vérification des expectations
    }
}; 