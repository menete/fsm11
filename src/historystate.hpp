/*******************************************************************************
  fsm11 - A C++11-compliant framework for finite state machines

  Copyright (c) 2015, Manuel Freiberger
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  - Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef FSM11_HISTORYSTATE_HPP
#define FSM11_HISTORYSTATE_HPP

#include "statemachine_fwd.hpp"
#include "state.hpp"

namespace fsm11
{

template <typename TStateMachine>
class ShallowHistoryState : public State<TStateMachine>
{
    using base_type = State<TStateMachine>;

public:
    explicit ShallowHistoryState(const char* name,
                                 base_type* parent = nullptr) noexcept
        : base_type(name, parent)
    {
        base_type::m_flags |= base_type::ShallowHistory;
    }

private:
    base_type* m_latestActiveChild{nullptr};

    template <typename TDerived>
    friend class fsm11_detail::EventDispatcherBase;
};

template <typename TStateMachine>
class DeepHistoryState : public State<TStateMachine>
{
    using base_type = State<TStateMachine>;

public:
    explicit DeepHistoryState(const char* name,
                              base_type* parent = nullptr) noexcept
        : base_type(name, parent)
    {
        base_type::m_flags |= base_type::DeepHistory;
    }

private:
    base_type* m_latestActiveChild{nullptr};

    template <typename TDerived>
    friend class fsm11_detail::EventDispatcherBase;
};

} // namespace fsm11

#endif // FSM11_HISTORYSTATE_HPP
