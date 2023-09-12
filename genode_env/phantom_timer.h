
#include <base/env.h>
#include <base/mutex.h>
#include <timer_session/connection.h>

namespace Phantom
{
    struct Timer_adapter;
    class SleepHandler;
}

class Phantom::SleepHandler {
    public:
    // Genode::Mutex _sync_mutex{};
    Genode::Blockade _sleep_blockade{};
    Timer::One_shot_timeout<SleepHandler> _timeout;
    int _duration = 0;

    void handler(Genode::Duration curr_time) {
        // Genode::log("!!!UNBLOCKING!!!");
        _sleep_blockade.wakeup();
    }

    SleepHandler(Timer::Connection& conn, int microseconds) : _timeout(conn, *this, &SleepHandler::handler), _duration(microseconds) {}

    void sleep(){
        _timeout.schedule(Genode::Microseconds{_duration});
        // XXX : Here is not really a good time to block if context is switched before the block
        _sleep_blockade.block();
    }
};

struct Phantom::Timer_adapter
{
    Genode::Env &_env;
    Genode::Entrypoint _ep_timer{_env, sizeof(addr_t)*2048, "timer_ep",
		             Affinity::Location()};
    Timer::Connection _timer{_env, _ep_timer, "Phantom timer"};
    const unsigned int rate_us = 1000;

    Timer::Periodic_timeout<Phantom::Timer_adapter> _periodic_timeout{
        _timer,
        *this,
        &Phantom::Timer_adapter::handle_timer_tick,
        Genode::Microseconds(rate_us)};

    Genode::Mutex _handler_mutex{};

    void (*_handler)(long long unsigned tick_rate) = nullptr;

    void handle_timer_tick(Genode::Duration duration)
    {
        Genode::Mutex::Guard guard(_handler_mutex);
        // Genode::log("TICK!!!!");

        if (_handler != nullptr)
            _handler(duration.trunc_to_plain_us().value);
    }

    void set_handler(void (*handler)(long long unsigned tick_rate))
    {
        Genode::Mutex::Guard guard(_handler_mutex);

        _handler = handler;
    }

    void sleep_microseconds(long microseconds){

        // Genode::log("Start to sleep (", microseconds, "): ", _timer.elapsed_ms());
        Phantom::SleepHandler sleep_handler{_timer, microseconds};
        sleep_handler.sleep();
        // _timer.usleep(microseconds);
        // TODO : add RTC
        // Genode::log("Finish to sleep (", microseconds, "): ", _timer.elapsed_ms());
    }


    Timer_adapter(Genode::Env &env) : _env(env)
    {
    }
};
