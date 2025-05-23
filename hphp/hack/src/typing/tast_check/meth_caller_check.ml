(*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the "hack" directory of this source tree.
 *
 *)

open Hh_prelude
open Aast
open Typing_defs

(* meth_caller does not support methods with inout parameters *)
let check_parameters env pos (_, ftype) =
  match
    List.find
      ~f:(fun ft_param ->
        match get_fp_mode ft_param with
        | FPnormal -> false
        | _ -> true)
      ftype.ft_params
  with
  | Some fparam ->
    let convention =
      match get_fp_mode fparam with
      | FPinout -> "`inout`"
      | FPnormal -> "normal"
    in
    Typing_error_utils.add_typing_error
      ~env:(Tast_env.tast_env_as_typing_env env)
      Typing_error.(
        primary
        @@ Primary.Invalid_meth_caller_calling_convention
             { pos; decl_pos = fparam.fp_pos; convention })
  | None -> ()

let check_readonly_return env pos (r, ftype) =
  if Flags.get_ft_returns_readonly ftype then
    let rpos = Typing_reason.to_pos r in
    Typing_error_utils.add_typing_error
      ~env:(Tast_env.tast_env_as_typing_env env)
      Typing_error.(
        primary
        @@ Primary.Invalid_meth_caller_readonly_return { pos; decl_pos = rpos })

let handler =
  object
    inherit Tast_visitor.handler_base

    method! at_expr env e =
      match e with
      | (ty, pos, Method_caller _) -> begin
        match Tast_env.get_underlying_function_type env ty with
        | None -> ()
        | Some ft ->
          check_parameters env pos ft;
          check_readonly_return env pos ft
      end
      | _ -> ()
  end
