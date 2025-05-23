/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-present Facebook, Inc. (http://www.facebook.com)  |
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/
#include "hphp/runtime/ext/intervaltimer/ext_intervaltimer.h"

#include "hphp/runtime/base/array-init.h"
#include "hphp/runtime/base/builtin-functions.h"
#include "hphp/runtime/base/req-optional.h"
#include "hphp/runtime/base/surprise-flags.h"
#include "hphp/runtime/base/request-info.h"
#include "hphp/runtime/ext/asio/ext_waitable-wait-handle.h"
#include "hphp/runtime/vm/native-data.h"
#include "hphp/util/rds-local.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

struct TimerPool final : RequestEventHandler {
  using TimerSet = req::fast_set<IntervalTimer*>;
  TimerSet& timers() { return *m_timers; }

  void requestInit() override {
    m_timers.emplace();
  }

  void requestShutdown() override {
    while (!m_timers->empty()) {
      (*m_timers->begin())->stop();
    }

    m_timers.reset();
  }

 private:
  req::Optional<TimerSet> m_timers;
};

IMPLEMENT_STATIC_REQUEST_LOCAL(TimerPool, s_timer_pool);

///////////////////////////////////////////////////////////////////////////////

namespace {

bool Enabled;

const StaticString
  s_IOWait("IOWait"),
  s_ResumeAwait("ResumeAwait"),
  s_Enter("Enter"),
  s_Exit("Exit");

static StaticString sample_type_string(IntervalTimer::SampleType type) {
  switch (type) {
    case IntervalTimer::IOWaitSample: return s_IOWait;
    case IntervalTimer::ResumeAwaitSample: return s_ResumeAwait;
    case IntervalTimer::EnterSample: return s_Enter;
    case IntervalTimer::ExitSample: return s_Exit;
  }
  not_reached();
}

}

void IntervalTimer::RunCallbacks(
  IntervalTimer::SampleType type,
  c_WaitableWaitHandle* wh
) {
  clearSurpriseFlag(IntervalTimerFlag);

  auto const timers = s_timer_pool->timers(); // makes a copy!
  for (auto timer : timers) {
    if (!s_timer_pool->timers().contains(timer)) {
      // This timer has been removed from the pool by one of the callbacks.
      continue;
    }
    int count = 0;
    {
      std::lock_guard<std::mutex> lock(timer->m_signalMutex);
      count = timer->m_count;
      timer->m_count = 0;
      if (count == 0) {
        continue;
      }
    }
    try {
      auto args = make_vec_array(sample_type_string(type), count, Object{wh});
      vm_call_user_func(timer->m_callback, args);
    } catch (Object& ex) {
      raise_error("Uncaught exception escaping IntervalTimer: %s",
                  throwable_to_string(ex.get()).data());
    }
  }
}

IntervalTimer::~IntervalTimer() {
  stop();
}

void IntervalTimer::init(double interval,
                         double initial,
                         const Variant& callback,
                         RequestInjectionData* data) {
  assertx(data);
  m_interval = interval;
  m_initial = initial;
  m_callback = callback;
  m_data = data;
}

void IntervalTimer::start() {
  if (m_thread.joinable()) return;
  m_thread = std::thread([](IntervalTimer* t) { t->run(); }, this);
  s_timer_pool->timers().insert(this);
}

void IntervalTimer::stop() {
  if (!m_thread.joinable()) return;
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_stopping = true;
  }
  m_cv.notify_one();
  m_thread.join();
  m_stopping = false;
  s_timer_pool->timers().erase(this);
}

void IntervalTimer::run() {
  auto waitTime = m_initial;
  do {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto status = m_cv.wait_for(lock,
#ifdef MSVC_NO_STD_CHRONO_DURATION_DOUBLE_ADD
                                std::chrono::duration<__int64>((__int64)waitTime),
#else
                                std::chrono::duration<double>(waitTime),
#endif
                                [this]{ return m_stopping; });
    if (status) break;
    {
      std::lock_guard<std::mutex> l(m_signalMutex);
      m_data->setFlag(IntervalTimerFlag);
      ++m_count;
    }
    waitTime = m_interval;
  } while (waitTime != 0.0);
}

///////////////////////////////////////////////////////////////////////////////

Class* IntervalTimer::c_Class = nullptr;
const StaticString IntervalTimer::c_ClassName("IntervalTimer");

void HHVM_METHOD(IntervalTimer, __construct,
                 double interval,
                 double initial,
                 const Variant& callback) {
  auto data = Native::data<IntervalTimer>(this_);
  data->init(interval, initial, callback,
             &RequestInfo::s_requestInfo->m_reqInjectionData);
}

void HHVM_METHOD(IntervalTimer, start) {
  if (!Enabled) return;
  auto data = Native::data<IntervalTimer>(this_);
  data->start();
}

void HHVM_METHOD(IntervalTimer, stop) {
  if (!Enabled) return;
  auto data = Native::data<IntervalTimer>(this_);
  data->stop();
}

///////////////////////////////////////////////////////////////////////////////

static struct IntervalTimerExtension final : Extension {
  IntervalTimerExtension() : Extension("intervaltimer", NO_EXTENSION_VERSION_YET, NO_ONCALL_YET) {}

  void moduleLoad(const IniSetting::Map& ini, Hdf hdf) override {
    Config::Bind(Enabled, ini, hdf, "IntervalTimer.Enable", true);
  }

  void moduleRegisterNative() override {
    HHVM_ME(IntervalTimer, __construct);
    HHVM_ME(IntervalTimer, start);
    HHVM_ME(IntervalTimer, stop);
    Native::registerNativeDataInfo<IntervalTimer>(
      IntervalTimer::c_ClassName.get(),
      Native::NDIFlags::NO_SWEEP);
  }
} s_intervaltimer_extension;

///////////////////////////////////////////////////////////////////////////////
}
