#ifndef CPP_FAKECATALOG_H
#define CPP_FAKECATALOG_H


#include <map>
#include "../model/SupermarketCatalog.h"

class FakeCatalog : public SupermarketCatalog {
public:

    void addProduct(const Product& product, double price) override
    {
        products[product.getName()] = product;
        prices[product.getName()] = price;
    }

    double getUnitPrice(const Product& product) override
    {
        return prices[product.getName()];
    }

private:
    std::map<std::string, Product> products;
    std::map<std::string, double> prices;
};


#endif //CPP_FAKECATALOG_H
