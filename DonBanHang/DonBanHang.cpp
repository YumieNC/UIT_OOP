#include <iostream>

class Customer {
    protected:
        std::string customerID, customerName,
                customerAddress, customerPhoneNumber,
                customerOption;
    public:
        virtual void setCustomer()
        {
            std::getline(std::cin, customerID);
            std::getline(std::cin, customerName);
            std::getline(std::cin, customerAddress);
            std::getline(std::cin, customerPhoneNumber);
        }

        virtual void printCustomer()
        {
            std::cout << "Customer" << ": " << customerID
                    << " " << customerOption
                    << " " << customerName
                    << " " << customerAddress
                    << " " << customerPhoneNumber;
        }
};

class Individual : public Customer {
    public: 
    Individual()
    {
        customerOption = "Individual";
    }
};

class Business : public Customer {
    private:
        std::string taxCode;
    public:
        Business()
        {
            customerOption = "Business";
        }

        void setCustomer()
        {
            Customer::setCustomer();
            std::getline(std::cin, taxCode);
        }

        void printCustomer()
        {
            Customer::printCustomer();
            std::cout << " " << taxCode;
        }
};

class Product {
    protected:
        std::string productID, productName, manufacturer, productOption;
        int productUnitPrice;
    public:
        virtual void setProduct()
        {
            std::cin.ignore();
            std::getline(std::cin, productID);
            std::getline(std::cin, productName);
            std::cin >> productUnitPrice;
            std::cin.ignore();
            std::getline(std::cin, manufacturer);
        }

        int getProductPrice() {
            return productUnitPrice;
        }

        virtual void printProduct()
        {
            std::cout << "\nProduct: " << productID
                    << " " << productName
                    << " " << manufacturer
                    << " " << productUnitPrice
                    << " " << productOption;
        }
};

class Food : public Product {
    private:
        int netWeight;
    public:
        Food()
        {
            productOption = "Food";
        }

        void setProduct()
        {
            Product::setProduct();
            std::cin >> netWeight;
        }
        
        void printProduct()
        {
            Product::printProduct();
            std::cout << " " << netWeight;
        }
};

class Beverage : public Product {
    protected:
        std::string beverageOption;
        int capacity;
    public:
        Beverage()
        {
            productOption = "Beverage";
        }

        void setProduct()
        {
            Product::setProduct();
            std::cin >> capacity;
        }

        void printProduct()
        {
            Product::printProduct();
            std::cout << " " << capacity;
        }
};

class Coke : public Beverage {
    public:
        Coke()
        {
            beverageOption = "Coke";
        }
};

class Ancohol : public Beverage {
    private:
        float concentration;
    public:
        Ancohol()
        {
            beverageOption = "Ancohol";
        }

        void setProduct()
        {
            Beverage::setProduct();
            std::cin >> concentration;
        }

        void printProduct()
        {
            Beverage::printProduct();
            std::cout << " " << concentration;
        }
};

class Detail {
    protected:
        int productQuantity, productSelect, 
            beverageSelect, quantity, listPrice = 0;
        Product **productList;
    public:
        void setDetail()
        {
            std::cin >> productQuantity;
            productList = new Product *[productQuantity];

            for (int i = 0; i < productQuantity; i++) {
                std::cin >> productSelect;
                if (productSelect == 1) productList[i] = new Food;
                else if (productSelect == 2) {
                    productList[i] = new Beverage;
                    std::cin >> beverageSelect;
                    if (beverageSelect == 1) productList[i] = new Coke;
                    else productList[i] = new Ancohol;
                }

                productList[i] -> setProduct();
                listPrice += productList[i] -> getProductPrice();
            }

            std::cin >> quantity;
        }

        int getDetailPrice()
        {
            return listPrice * quantity;
        }

        void printDetail()
        {
            for (int i = 0; i < productQuantity; i++) {
                productList[i] -> printProduct();
            }

            std::cout << " " << quantity << "\n";
        }
};

class Order {
    protected:
        std::string orderID, orderOption, orderDate, deliveryDate, deliveryAddress;
        float valueIndex;
        Customer *customer;
        Detail *detail;
    public:
        virtual void setOrder()
        {
            std::cin.ignore();
            std::getline(std::cin, orderID);
            std::getline(std::cin, orderDate);
            std::getline(std::cin, deliveryDate);
            std::getline(std::cin, deliveryAddress);
            customer = new Customer;
            detail = new Detail;
        } 

        float getOrderValue()
        {
            return (float)detail -> getDetailPrice() * valueIndex; 
        }

        void printOrder()
        {
            std::cout << "Order: " << orderID
                    << " " << orderOption
                    << " " << getOrderValue()
                    << " " << orderDate
                    << " " << deliveryDate
                    << " " << deliveryAddress << "\n";
            customer -> printCustomer();
            detail -> printDetail();
        }
};

class Retail : public Order {
    public:
        Retail()
        {
            orderOption = "Retail";
            valueIndex = 1.0;
        }

        void setOrder()
        {
            Order::setOrder();
            customer = new Individual;
            customer -> setCustomer();   
            detail -> setDetail();         
        }
};

class Wholesale : public Order {
    public:
        Wholesale()
        {
            orderOption = "Wholesale";
            valueIndex = 0.85;
        }

        void setOrder() 
        {
            Order::setOrder();
            customer = new Business;
            customer -> setCustomer();
            detail -> setDetail();
        }
};

class OrderList {
    private:
        int orderQuantity, orderSelect;
        Order **orderList;
    public:
        void input()
        {
            std::cin >> orderQuantity;
            orderList = new Order *[orderQuantity];
            for (int i = 0; i < orderQuantity; i++) {
                std::cin >> orderSelect;
                if (orderSelect == 1) orderList[i] = new Retail;
                else orderList[i] = new Wholesale;
                orderList[i] -> setOrder();
            }
        }

        void output()
        {
            for (int i = 0; i < orderQuantity; i++) {
                orderList[i] -> printOrder();
            }
        }
};

int main()
{
    OrderList List;
    List.input();
    List.output();
    return 0;
}