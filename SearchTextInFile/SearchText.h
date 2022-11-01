#pragma once

#include "SearchText.g.h"

namespace winrt::SearchTextInFile::implementation
{
    struct SearchText : SearchTextT<SearchText>
    {
        SearchText();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::SearchTextInFile::factory_implementation
{
    struct SearchText : SearchTextT<SearchText, implementation::SearchText>
    {
    };
}
