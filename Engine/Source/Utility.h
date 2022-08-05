#pragma once 

//// Utility
//inline std::string HrToString(HRESULT hr)
//{
//    char s_str[64] = {};
//    sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
//    return std::string(s_str);
//}
//
//class HrException : public std::runtime_error
//{
//public:
//    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}
//    HRESULT Error() const { return m_hr; }
//private:
//    const HRESULT m_hr;
//};
//
//#define SAFE_RELEASE(p) if (p) (p)->Release()
//
//inline void ThrowIfFailed(HRESULT hr)
//{
//    if (FAILED(hr))
//    {
//        throw HrException(hr);
//    }
//}

//namespace MonkeyMachine
//{
//    template<typename T>
//    using UniquePtr = std::unique_ptr<T>;
//    template<typename T, typename ... Args>
//    constexpr UniquePtr<T> CreateUniquePtr(Args&& ... args)
//    {
//        return std::make_unique<T>(std::forward<Args>(args)...);
//    }
//
//    template<typename T>
//    using SharedPtr = std::shared_ptr<T>;
//    template<typename T, typename ... Args>
//    constexpr SharedPtr<T> CreateSharedPtr(Args&& ... args)
//    {
//        return std::make_shared<T>(std::forward<Args>(args)...);
//    }
//}