#pragma once

#include "weasel/weasel.hpp"

#include "../../model/Discount.h"
#include "../../model/Product.h"
#include "../../model/ReceiptItem.h"

template <>
struct weasel::convert::Conversion<Product>
{
    std::shared_ptr<types::IType> operator()(const Product& value)
    {
        auto out = std::make_shared<types::Object>("Product");
        out->add("name", value.getName());
        out->add("unit", ProductUnit::Each == value.getUnit() ? "each" : "kilo");
        return out;
    }
};

template <>
struct weasel::convert::Conversion<Discount>
{
    std::shared_ptr<types::IType> operator()(const Discount& value)
    {
        auto out = std::make_shared<types::Object>("Product");
        out->add("description", value.getDescription());
        out->add("discount", value.getDiscountAmount());
        out->add("product", value.getProduct());
        return out;
    }
};

template <>
struct weasel::convert::Conversion<ReceiptItem>
{
    std::shared_ptr<types::IType> operator()(const ReceiptItem& value)
    {
        auto out = std::make_shared<types::Object>("ReceiptItem");
        out->add("product", value.getProduct());
        out->add("unit price", value.getPrice());
        out->add("quantity", value.getQuantity());
        out->add("total price", value.getTotalPrice());
        return out;
    }
};
