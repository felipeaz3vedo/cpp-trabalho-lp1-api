cmake_minimum_required(VERSION 3.15)
project(cpp_trabalho_lp1_api LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)

add_executable(cpp_trabalho_lp1_api
    src/main.cpp

    # Controllers
    src/controllers/user/user_controller.cpp
    src/controllers/table/table_controller.cpp
    src/controllers/reservation/reservation_controller.cpp
    src/controllers/menu_item/menu_item_controller.cpp
    src/controllers/order/order_controller.cpp
    src/controllers/setting/setting_controller.cpp  

    # Services
    src/services/user/user_service.cpp
    src/services/table/table_service.cpp
    src/services/reservation/reservation_service.cpp
    src/services/menu_item/menu_item_service.cpp
    src/services/order/order_service.cpp
    src/services/payment/payment_service.cpp
    src/services/setting/setting_service.cpp        
    src/services/setting/csv_settings_file_parser.cpp       # <- novo

    # Repositories
    src/repositories/user/employee_repository.cpp
    src/repositories/user/customer_repository.cpp
    src/repositories/table/table_repository.cpp
    src/repositories/reservation/reservation_repository.cpp
    src/repositories/menu_item/menu_item_repository.cpp
    src/repositories/order/order_repository.cpp
    src/repositories/order_menu_item/order_menu_item_repository.cpp
    src/repositories/setting/setting_repository.cpp 

    # Models - User
    src/models/user/user.cpp
    src/models/user/employee.cpp
    src/models/user/customer.cpp

    # Models - Table
    src/models/table/table.cpp

    # Models - Reservation
    src/models/reservation/reservation.cpp

    # Models - Order
    src/models/order/order.cpp
    src/models/order_menu_item/order_menu_item.cpp

    # Models - Menu
    src/models/menu_item/menu_item.cpp

    # Models - Payment
    src/models/payment/payment_method.cpp
    src/models/payment/card_payment.cpp
    src/models/payment/cash_payment.cpp

    # Models - Setting
    src/models/setting/setting.cpp

    # DTOs
    src/shared/dtos/setting/setting_response_dto.cpp

    # Helpers
    src/shared/helpers/http_response_helper.cpp
    src/shared/helpers/employee_role_helper.cpp
    src/shared/helpers/payment_type_helper.cpp
)

target_include_directories(cpp_trabalho_lp1_api PRIVATE
    src
)

target_link_libraries(cpp_trabalho_lp1_api PRIVATE Drogon::Drogon)
