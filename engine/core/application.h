#include <memory>
#include "window.h"

namespace Apex
{
    class Application
    {
        public:
            Application();
            ~Application() = default;

            void run();

        private:
            std::unique_ptr<Window> m_WindowInstance;
    };
}