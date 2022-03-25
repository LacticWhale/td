//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2022
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/files/FileId.h"
#include "td/telegram/td_api.h"
#include "td/telegram/telegram_api.h"
#include "td/telegram/UserId.h"

#include "td/actor/actor.h"

#include "td/utils/common.h"
#include "td/utils/Status.h"

namespace td {

class Td;

class AttachMenuManager final : public Actor {
 public:
  AttachMenuManager(Td *td, ActorShared<> parent);

  void init();

  void get_current_state(vector<td_api::object_ptr<td_api::Update>> &updates) const;

  void reload_attach_menu_bots();

  void on_reload_attach_menu_bots(Result<telegram_api::object_ptr<telegram_api::AttachMenuBots>> &&result);

 private:
  void start_up() final;

  void timeout_expired() final;

  void tear_down() final;

  bool is_active() const;

  struct AttachMenuBot {
    UserId user_id_;
    string name_;
    FileId default_icon_file_id_;
    FileId ios_static_icon_file_id_;
    FileId ios_animated_icon_file_id_;
    FileId android_icon_file_id_;
    FileId macos_icon_file_id_;

    template <class StorerT>
    void store(StorerT &storer) const;

    template <class ParserT>
    void parse(ParserT &parser);
  };

  class AttachMenuBotsLogEvent;

  friend bool operator==(const AttachMenuBot &lhs, const AttachMenuBot &rhs);

  friend bool operator!=(const AttachMenuBot &lhs, const AttachMenuBot &rhs);

  td_api::object_ptr<td_api::updateAttachMenuBots> get_update_attach_menu_bots_object() const;

  void send_update_attach_menu_bots() const;

  static string get_attach_menu_bots_database_key();

  void save_attach_menu_bots();

  Td *td_;
  ActorShared<> parent_;

  bool is_inited_ = false;
  int64 hash_ = 0;
  vector<AttachMenuBot> attach_menu_bots_;
};

}  // namespace td
