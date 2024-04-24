#include <iostream>
#include <string>
//ЗАДАНИЕ 17
/* Есть класс «Оплата за телефон», в котором учитывается, сколько
было исходящих вызовов, сколько времени занял каждый из них, и учитывается вид тарифа.
При помощи паттерна Strategy реализуйте следуюшее поведение в классе :
1. тариф с абонентской платой
2. посекундная тарификация
3. поминутная тарификация
*/

// Интерфейс стратегии тарификации
class PaymentStrategy {
public:
    virtual double calculateCost(int numOutgoingCalls, int callDuration) = 0;
};

//конкретнные стратегии
class AbonentPaymentStrategy : public PaymentStrategy{
public:
    double calculateCost(int num_call, int call_time) {
        return 200;//абонентская плата фиксированна
    }
};

class MinutePaymentStrategy : public PaymentStrategy {
public:
    double calculateCost(int num_call, int call_time) {//время отправляется в секундах
        return num_call * (call_time/60) * 3;//поминутный тариф где каждая минута стоит 3 рубля
    }
};

class SecondPaymentStrategy : public PaymentStrategy {
public:
    double calculateCost(int num_call, int call_time) {
        return  num_call * call_time * 0.03;//посекундный тариф где каждая секунда стоит 3 копейки ~ 2 рубля в минуту
    }
};

// Класс "Оплата за телефон"
class PhonePayment {
private:
    PaymentStrategy* paymentStrategy;

public:
    PhonePayment(PaymentStrategy* strategy) : paymentStrategy(strategy) {}//установка стратегии

    void setPaymentStrategy(PaymentStrategy* strategy) {
        paymentStrategy = strategy;
    }

    double calculateTotalCost(int num_call , int call_time) {//вычисление стоимости оплаты
        return paymentStrategy->calculateCost(num_call, call_time);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    PhonePayment phone(new AbonentPaymentStrategy());

    int num = 10;
    int sec = 300; // 5 минут

    double cost = phone.calculateTotalCost(num, sec);

    std::cout << "Стоимость для тарифа с абонентской платой: " << cost << std::endl;

    phone.setPaymentStrategy(new MinutePaymentStrategy());
    cost = phone.calculateTotalCost(num, sec);

    std::cout << "Стоимость для тарифа поминутная тарификация: " << cost << std::endl;
    phone.setPaymentStrategy(new SecondPaymentStrategy());
    cost = phone.calculateTotalCost(num, sec);

    std::cout << "Стоимость для тарифа посекундная тарификация: " << cost << std::endl;

    return 0;
}
