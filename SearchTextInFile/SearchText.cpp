#include "pch.h"
#include "SearchText.h"
#if __has_include("SearchText.g.cpp")
#include "SearchText.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SearchTextInFile::implementation
{
    SearchText::SearchText()
    {
        InitializeComponent();
    }

    int32_t SearchText::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SearchText::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void SearchText::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
