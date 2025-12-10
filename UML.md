classDiagram

%% ===================== USUÁRIOS =====================
class User {
<<abstract>>
+int id
+string name
+string email
+UserType type
+double calculateDiscount(orderTotal)
}

class Employee {
+string cpf
+EmployeeRole role
+bool active
}

class Customer {
+string phone
+int loyaltyPoints
}

User <|-- Employee
User <|-- Customer

%% ===================== TABLE & RESERVATION =====================
class Table {
+int id
+int number
+int capacity
+bool available
}

class Reservation {
+int id
+int customerId
+int tableId
+string startDateTime
+string endDateTime
+string notes
+bool active
}

Customer "1" -- "0.._" Reservation : reservations
Table "1" -- "0.._" Reservation : reservations

%% ===================== CATEGORY (NOVA) =====================
class Category {
+int id
+string name
+string description
+bool active
}

%% ===================== MENU & ORDER =====================
class MenuItem {
+int id
+string name
+string description
+double price
+bool active
+int categoryId
}

MenuItem --> Category : belongsTo

class Order {
+int id
+int tableId
+int waiterId
+double subtotal
+double discount
+double fee
+double total
+bool closed
+PaymentType paymentType
+int calculateLoyaltyPoints()
}

class OrderMenuItem {
+int id
+int orderId
+int menuItemId
+int quantity
+double unitPrice
+double getTotalPrice()
}

Table "1" -- "0.._" Order : orders
Employee "1" -- "0.._" Order : waiter

Customer "1" -- "0.._" Order : discountCustomer
Employee "1" -- "0.._" Order : discountEmployee

Order "1" -- "0.._" OrderMenuItem : items
MenuItem "1" -- "0.._" OrderMenuItem : items

%% ===================== PAYMENT =====================
class PaymentMethod {
<<abstract>>
+PaymentType type
+string getMethodName()
+double calculateFee(amount)
}

class CashPayment {
+string getMethodName()
+double calculateFee(amount)
}

class CardPayment {
+string cardBrand
+string last4Digits
+double percentageFee
+double fixedFee
+string getMethodName()
+double calculateFee(amount)
}

PaymentMethod <|-- CashPayment
PaymentMethod <|-- CardPayment
Order ..> PaymentMethod : calcula fee

%% ===================== SETTINGS (NOVA) =====================
class Setting {
+string key
+string valueString
+double valueNumber
+bool valueBool
+SettingValueType valueType
}

class SettingValueType {
<<enumeration>>
STRING
NUMBER
BOOLEAN
}

Setting --> SettingValueType

%% ===================== ENUMERAÇÕES =====================
class EmployeeRole {
<<enumeration>>
CASHIER
COOK
MANAGER
WAITER
}

class PaymentType {
<<enumeration>>
CASH
CARD
}

class UserType {
<<enumeration>>
EMPLOYEE
CUSTOMER
}

User --> UserType
Employee --> EmployeeRole
Order --> PaymentType
PaymentMethod --> PaymentType
