/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2020 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#include "MotionMonitor.h"
#include "utils.h"

namespace {
    using WPEFramework::Plugin::CamMotionMonitor;
    using CamMotionMonitorConstMethod = uint32_t (CamMotionMonitor::*)(const JsonObject &parameters, JsonObject &response) const;
    using CamMotionMonitorMethod = uint32_t (CamMotionMonitor::*)(const JsonObject &parameters, JsonObject &response);

    std::vector<std::pair<const char*, CamMotionMonitorMethod>> mutableMethods = {
        {"sendPath", &CamMotionMonitor::sendPath},
    };

    std::vector<std::pair<const char*, CamMotionMonitorConstMethod>> constMethods = {
    };
}

namespace WPEFramework
{
    namespace Plugin
    {
        SERVICE_REGISTRATION(CamMotionMonitor, 1, 0);

        CamMotionMonitor::CamMotionMonitor()
        : PluginHost::JSONRPC(),
          apiVersionNumber(1),
        {
        }

        CamMotionMonitor::~CamMotionMonitor()
        {
        }

        const string CamMotionMonitor::Initialize(PluginHost::IShell* service)
        {
            LOGINFO();

            if (instance != nullptr) {
                LOGERR("Expecting 'instance' to be initially unset; two instances of the plugin?");
                return string("Expecting m_instance to be initially unset");
            }
            instance = this;

            // Initialize other parts of the implementation
            std::string msg;

            // Combine their error messages (if any)
            return msg;
        }

        void CamMotionMonitor::Deinitialize(PluginHost::IShell* service)
        {
            LOGINFO();

            instance = nullptr;
        }

        string CamMotionMonitor::Information() const
        {
            LOGINFO();

            // No additional info to report.
            return string();
        }

        // ###### Method Implementation ######
        uint32_t CamMotionMonitor::sendPath(const JsonObject& parameters, JsonObject& response) const
        {
            LOGINFOMETHOD();

            m_ipAddress = parameters["ipaddress"];
            m_imagePath = parameters["imagepath"];

            LOGTRACEMETHODFIN();
            returnResponse(true);
        }

        /**
         * \brief Send an event that the Camera module sent the captured notification.
         *
         * \param url http url of the image file.
         */
        void CamMotionMonitor::onMotionCaptured(const string &url)
        {
            JsonObject params;
            
            url = "http://" + m_ipAddress + "/" + m_imagePath;
            params["url"] = url;

            sendNotify("onMotionCaptured", params);
        }

        /**
        * \brief Get the current CamMotionMonitor instance
        *
        * WPEFramework will only have one instance of this plugin at any one time and so only one instance of this class.
        *
        * \return The single instance.
        */
        CamMotionMonitor& CamMotionMonitor::getInstance() {
            if (!instance) {
                LOGERR("No instances of 'CamMotionMonitor' have been created");
                throw std::logic_error("No instances of 'CamMotionMonitor' have been created");
            }

            return *instance;
        }

        // This instance is generally accessed via CamMotionMonitor::getInstance.
        CamMotionMonitor* CamMotionMonitor::instance = nullptr;
    } // namespace Plugin
} // namespace WPEFramework