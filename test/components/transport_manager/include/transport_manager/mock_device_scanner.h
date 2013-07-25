/*
 * \file mock_device_scanner.h
 * \brief
 *
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef APPLINK_TEST_COMPONENTS_TRANSPORTMANAGER_INCLUDE_MOCKDEVICESCANNER_H_
#define APPLINK_TEST_COMPONENTS_TRANSPORTMANAGER_INCLUDE_MOCKDEVICESCANNER_H_

#include "transport_manager/device_adapter_impl.h"

using ::transport_manager::device_adapter::DeviceAdapter;
using ::transport_manager::device_adapter::DeviceScanner;
using ::transport_manager::device_adapter::DeviceVector;

namespace test {
namespace components {
namespace transport_manager {

class MockDeviceAdapter;

class MockDeviceScanner : public DeviceScanner {
 public:
  MockDeviceScanner(MockDeviceAdapter *adapter);
  void addDevice(const std::string& name);
  void removeDevice(const std::string& name);
 protected:
  DeviceAdapter::Error init();
  DeviceAdapter::Error scan();
  void terminate();
  bool isInitialised() const;

 private:
  MockDeviceAdapter *controller_;
  DeviceVector devices_;
  bool is_initialized_;
};

}  // namespace transport_manager
}  // namespace components
}  // namespace test

#endif /* APPLINK_TEST_COMPONENTS_TRANSPORTMANAGER_INCLUDE_MOCKDEVICESCANNER_H_ */
