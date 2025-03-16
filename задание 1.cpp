#include <iostream>
#include <string>

// Интерфейс для оружия
class IWeapon {
public:
    virtual void use() = 0;
};

// Интерфейс для брони
class IArmor {
public:
    virtual void wear() = 0;
};

// Оружие для эльфов
class ElfWeapon : public IWeapon {
public:
    void use() override {
        std::cout << "Elf uses a bow!" << std::endl;
    }
};

// Броня для эльфов
class ElfArmor : public IArmor {
public:
    void wear() override {
        std::cout << "Elf wears light armor!" << std::endl;
    }
};

// Оружие для орков
class OrcWeapon : public IWeapon {
public:
    void use() override {
        std::cout << "Orc uses an axe!" << std::endl;
    }
};

// Броня для орков
class OrcArmor : public IArmor {
public:
    void wear() override {
        std::cout << "Orc wears heavy armor!" << std::endl;
    }
};

// Абстрактная фабрика для создания персонажей
class ICharacterFactory {
public:
    virtual IWeapon* createWeapon() = 0;
    virtual IArmor* createArmor() = 0;
};

// Фабрика для эльфов
class ElfFactory : public ICharacterFactory {
public:
    IWeapon* createWeapon() override {
        return new ElfWeapon();
    }

    IArmor* createArmor() override {
        return new ElfArmor();
    }
};

// Фабрика для орков
class OrcFactory : public ICharacterFactory {
public:
    IWeapon* createWeapon() override {
        return new OrcWeapon();
    }

    IArmor* createArmor() override {
        return new OrcArmor();
    }
};

// Клиентский код
int main() {
    ICharacterFactory* factory = nullptr;

    // Создаем эльфа
    factory = new ElfFactory();
    IWeapon* elfWeapon = factory->createWeapon();
    IArmor* elfArmor = factory->createArmor();

    elfWeapon->use();
    elfArmor->wear();

    delete elfWeapon;
    delete elfArmor;
    delete factory;

    // Создаем орка
    factory = new OrcFactory();
    IWeapon* orcWeapon = factory->createWeapon();
    IArmor* orcArmor = factory->createArmor();

    orcWeapon->use();
    orcArmor->wear();

    delete orcWeapon;
    delete orcArmor;
    delete factory;

    return 0;
}
