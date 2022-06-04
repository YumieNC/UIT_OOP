#include <iostream>

class CPU {
    protected:
        std::string cpuID, cpuOption;
        int cpuPrice;
    public:
        void setCPU(int cpuSelect)
        {
            std::getline(std::cin, cpuID);
            if (cpuSelect == 1) {
                cpuOption = "Core i3";
                cpuPrice = 100;
            }

            else if (cpuSelect == 2) {
                cpuOption = "Core i5";
                cpuPrice = 200;
            }

            else {
                cpuOption = "Core i7";
                cpuPrice = 300;
            }
        }

        int getCPUPrice()
        {
            return cpuPrice;
        }

        void printCPU()
        {
            std::cout << "CPU: " << cpuID
                << " " << cpuOption
                << " " << cpuPrice << "\n";
        }
};

class RAM {
    protected:
        std::string ramID, ramOption;
        int ramPrice, ramTotalPrice = 0;
    public:
        void setRAM(int ramSelect, int ramCapacity)
        {
            std::getline(std::cin, ramID);
            if (ramSelect == 1) {
                ramOption = "DDR3";
                ramPrice = 100;
            }

            else if (ramSelect == 2) {
                ramOption = "DDR4";
                ramPrice = 200;
            }
            ramTotalPrice = ramCapacity * ramPrice;
        }

        int getRAMTotalPrice()
        {
            return ramTotalPrice;
        }

        void printRAM()
        {
            std::cout << ramID << " ";
        }
};

class Monitor {
    protected:
        std::string monitorID, monitorOption, resolution, standardOption;
        int monitorPrice;
    public:
        void setMonitor(int monitorSelect, int standard = 0)
        {
            std::getline(std::cin, monitorID);
            if (monitorSelect == 1) {
                monitorOption = "Mirror";
                monitorPrice = 1000;
                resolution = "HD";
            }

            else {
                resolution = "FullHD";
                monitorOption = "AntiGlare";
                if (standard == 1) {
                    monitorPrice = 2000;
                    standardOption = "Standard 1";
                }
                else if (standard == 2) {
                    monitorPrice = 3000;
                    standardOption = "Standard 2";
                }
                else if (standard == 3) {
                    monitorPrice = 4000;
                    standardOption = "Standard 3";
                }
            }
        }

        int getMonitorPrice()
        {
            return monitorPrice;
        }

        void printMonitor()
        {
            std::cout << "Monitor: " << monitorID
                    << " " << monitorOption 
                    << " " << resolution
                    << " " << standardOption
                    << " " << monitorPrice << "\n";
        }
};

class Hardware {
    protected:
        std::string hardwareID, hardwareOption;
        int hardwarePrice, hardwareCapacity;
    public:
        virtual void setHardware()
        {
            std::getline(std::cin, hardwareID);
            std::cin >> hardwareCapacity >> hardwarePrice;
        }

        int getHardwarePrice()
        {
            return hardwarePrice;
        }

        virtual void printHardware()
        {
            std::cout << "Hardware: " << hardwareID
                    << " " << hardwareOption
                    << " " << hardwareCapacity
                    << " " << hardwarePrice;
        }
};

class HDD : public Hardware {
    private:
        int rotations;
    public:
        HDD()
        {
            hardwareOption = "HDD";
        }

        void setHardware()
        {
            Hardware::setHardware();
            std::cin >> rotations;
        }

        void printHardware()
        {
            Hardware::printHardware();
            std::cout << " " << rotations << "\n";
        }
};

class SSD : public Hardware {
    private:
        int readSpeed, writeSpeed;
    public:
        SSD()
        {
            hardwareOption = "SSD";
        }

        void setHardware()
        {
            Hardware::setHardware();
            std::cin >> readSpeed >> writeSpeed;
        }

        void printHardware()
        {
            Hardware::printHardware();
            std::cout << " " << readSpeed
                    << " " << writeSpeed << "\n";
        }
};

class RAMDetail {
    private:
        std::string RAMOption;
        int RAMQuantity, RAMCapacity, RAMSelect, RAMPrice = 0;
        RAM **RAMList;
    public:
        void setRAMDetail()
        {
            std::cin >> RAMQuantity;
            RAMList = new RAM *[RAMQuantity];

            std::cin >> RAMSelect;
            if (RAMSelect == 1) RAMOption = "DDR3";
            else RAMOption = "DDR4";

            std::cin >> RAMCapacity;
            std::cin.ignore();
            for (int i = 0; i < RAMQuantity; i++) {
                RAMList[i] = new RAM;
                RAMList[i] -> setRAM(RAMSelect, RAMCapacity);
                RAMPrice += RAMList[i] -> getRAMTotalPrice();
            }
        }

        int getRAMTotalPrice()
        {
            return RAMPrice;
        }

        void printRAMDetail() 
        {
            std::cout << "RAM: ";
            for (int i = 0; i < RAMQuantity; i++) {
                RAMList[i] -> printRAM();
            }

            std::cout << RAMOption
                    << " " << RAMCapacity
                    << " " << RAMPrice << "\n";
        }
};

class Product {
    protected:
        std::string productID, productName,
                productOption;
        CPU *usingCPU;
        Hardware *usingHardware;
        Monitor *usingMonitor;
        RAMDetail *usingRAMList;
        int hardwareSelect, antiGlareStandard,
            cpuSelect;
    public:
        virtual void setProduct()
        {
            std::cin.ignore();
            std::getline(std::cin, productID);
            std::getline(std::cin, productName);
            usingCPU = new CPU;
            usingHardware = new Hardware;
            usingMonitor = new Monitor;
            usingRAMList = new RAMDetail;
        }

        int getProductPrice()
        {
            return usingRAMList -> getRAMTotalPrice() + usingCPU -> getCPUPrice() + usingHardware -> getHardwarePrice() + usingMonitor -> getMonitorPrice();
        }

        void printProduct()
        {
            std::cout << "Product: " << productID
                    << " " << productOption
                    << " " << productName
                    << " " << getProductPrice() << "\n";

            usingCPU -> printCPU();

            usingRAMList -> printRAMDetail();

            usingMonitor -> printMonitor();

            usingHardware -> printHardware();
        }
};

class Butterfly : public Product {
    public:
        Butterfly()
        {
            productOption = "Butterfly";
        }

        void setProduct()
        {
            Product::setProduct();

            usingCPU -> setCPU(3);

            usingRAMList -> setRAMDetail();

            std::cin >> antiGlareStandard;
            std::cin.ignore();
            usingMonitor -> setMonitor(2, antiGlareStandard);

            usingHardware = new SSD;
            usingHardware -> setHardware();
        }
};

class Fly : public Product {
    public:
        Fly()
        {
            productOption = "Fly";
        }

        void setProduct()
        {
            Product::setProduct();

            usingCPU -> setCPU(2);

            usingRAMList -> setRAMDetail();

            usingMonitor -> setMonitor(1);

            std::cin >> hardwareSelect;
            if (hardwareSelect == 1) usingHardware = new HDD;
            else usingHardware = new SSD;
            std::cin.ignore();
            usingHardware -> setHardware();
        }
};

class Bee : public Product {
    public:
        Bee()
        {
            productOption = "Bee";
        }

        void setProduct()
        {
            Product::setProduct();

            do {
                std::cin >> cpuSelect;
            } while (cpuSelect != 1 && cpuSelect != 2);

            usingCPU -> setCPU(cpuSelect);

            usingRAMList -> setRAMDetail();

            usingMonitor -> setMonitor(1);

            std::cin >> hardwareSelect;
            if (hardwareSelect == 1) usingHardware = new HDD;
            else usingHardware = new SSD;
            std::cin.ignore();
            usingHardware -> setHardware();
        }
};

class Order {
    private:
        int productQuantity, productSelect;
        Product **productList;
    public:
        void set()
        {
            std::cin >> productQuantity;
            productList = new Product *[productQuantity];

            for (int i = 0; i < productQuantity; i++) {
                std::cin >> productSelect;
                if (productSelect == 1) productList[i] = new Butterfly;
                else if (productSelect == 2) productList[i] = new Fly;
                else productList[i] = new Bee;
                productList[i] -> setProduct();
            }
        }

        void print()
        {
            for (int i = 0; i < productQuantity; i++) {
                productList[i] -> printProduct();
            }
        }
};

int main()
{
    Order List;
    List.set();
    List.print();
    return 0;
}