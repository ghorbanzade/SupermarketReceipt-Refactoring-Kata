#include "catch2/catch.hpp"

#include "../../model/SupermarketCatalog.h"
#include "../../model/ShoppingCart.h"
#include "../../model/Teller.h"
#include "../FakeCatalog.h"

#include "weasel/weasel.hpp"
#include "weasel_types.hpp"

TEST_CASE("configure client")
{
    Receipt receipt;
    SupermarketCatalog *catalog = new FakeCatalog();

    SECTION("basic-example")
    {
        weasel::declare_testcase("basic-example");

        // ARRANGE
        Product toothbrush("toothbrush", ProductUnit::Each);
        catalog->addProduct(toothbrush, 0.99);
        Product apples("apples", ProductUnit::Kilo);
        catalog->addProduct(apples, 1.99);
        Teller teller(catalog);
        teller.addSpecialOffer(SpecialOfferType::TenPercentDiscount, toothbrush, 10.0);

        ShoppingCart cart;
        cart.addItemQuantity(apples, 2.5);

        // ACT
        receipt = teller.checksOutArticlesFrom(cart);
    }

    // ASSERT

    weasel::add_result("total price", receipt.getTotalPrice());
    weasel::add_result("discounts", receipt.getDiscounts());
    for (const auto& receiptItem: receipt.getItems())
    {
        weasel::add_hit_count("items count");
        weasel::add_array_element("receipt items", receiptItem);
    }
}
