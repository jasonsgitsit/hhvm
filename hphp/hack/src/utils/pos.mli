(*
 * Copyright (c) 2015, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the "hack" directory of this source tree.
 *
 *)

(* Note: While Pos.string prints out positions as closed intervals, pos_start
 * and pos_end actually form a half-open interval (i.e. pos_end points to the
 * character *after* the last character of the relevant lexeme.) *)
type 'a pos [@@deriving eq, hash, ord, show]

(** The underlying type used to construct Pos instances.
 *
 * See "val make: 'a -> b -> 'a pos" *)
type b = Pos_source.t

type t = Relative_path.t pos [@@deriving eq, hash]

val pp : Format.formatter -> t -> unit

type absolute = string pos [@@deriving eq, ord, show]

val none : t

val hash : t -> int

val filename : 'a pos -> 'a

val start_offset : 'a pos -> int

val end_offset : 'a pos -> int

val line : 'a pos -> int

val line_column : 'a pos -> int * int

val end_line : 'a pos -> int

val end_line_column : 'a pos -> int * int

(** Return line number, beginning of line character number and character number of start position. *)
val line_beg_offset : t -> int * int * int

val end_line_beg_offset : t -> int * int * int

(** For spans over just one line, return the line number, start column and end column.
    This returns a closed interval. Both line and column numbers are one-based.
    Undefined for multi-line spans. *)
val info_pos : 'a pos -> int * int * int

(** Return start line, end line, start column and end column.
    This returns a closed interval. *)
val info_pos_extended : 'a pos -> int * int * int * int

(** Return start character number and end character number. *)
val info_raw : 'a pos -> int * int

(** Return start line, start column, end line and end column, as 1-based indices.
    This returns a half-open interval. *)
val destruct_range_one_based : 'a pos -> int * int * int * int

val length : 'a pos -> int

(* This returns a closed interval. *)
val string : absolute -> string

(* This returns a half-open interval. *)
val multiline_string : absolute -> string

(* This returns a closed interval. *)
val string_no_file : 'a pos -> string

(* This returns a half-open interval. *)
val multiline_string_no_file : 'a pos -> string

(* This returns a closed interval. *)
val json : absolute -> Hh_json.json

val json_no_filename : absolute -> Hh_json.json

(* This returns a half-open interval. *)
val multiline_json : absolute -> Hh_json.json

val multiline_json_no_filename : 'a pos -> Hh_json.json

(** [inside_one_based span line_one_based column_one_based] determines
  whether the cursor at `line_one_based` and `column_one_based` is inside the `span`.
  `line_one_based` and `column_one_based` are one-based indices. *)
val inside_one_based : 'a pos -> int -> int -> bool

val exactly_matches_range :
  'a pos ->
  start_line:int ->
  start_col:int ->
  end_line:int ->
  end_col:int ->
  bool

val contains : t -> t -> bool

(* Does first position strictly overlap the second position? *)
val overlaps : t -> t -> bool

val make : 'a -> b -> 'a pos

val make_from_lexing_pos : 'a -> Lexing.position -> Lexing.position -> 'a pos

val make_from : 'a -> 'a pos

val btw_nocheck : 'a pos -> 'a pos -> 'a pos

val is_hhi : t -> bool

(** Fill in the gap "between" first position and second position.
    Not valid if from different files or second position precedes first *)
val btw : t -> t -> t

(* Symmetric version of above: order doesn't matter *)
val merge : 'a pos -> 'a pos -> 'a pos

val last_char : t -> t

val first_char_of_line : t -> t

val to_absolute : t -> absolute

val to_relative : absolute -> t

val to_relative_string : t -> string pos

val get_text_from_pos : content:string -> 'a pos -> string

(* Advance the ending position by one character *)
val advance_one : 'a pos -> 'a pos

(* Advance the ending position by consuming the string *)
val advance_string : string -> 'a pos -> 'a pos

(* Reduce the size of this position element by one character on the left and
 * one character on the right.  For example, if you've captured a position
 * that includes outside apostrophes, this will shrink it to only the contents
 * within the apostrophes. *)
val shrink_by_one_char_both_sides : 'a pos -> 'a pos

(* Compare by filename, then tie-break by start position, and finally by the
 * end position *)
val compare : t -> t -> int

val set_file : 'a -> 'b pos -> 'a pos

(* Return a zero-width position that occurs at the start of input position. *)
val shrink_to_start : 'a pos -> 'a pos

(* Return a zero-width position that occurs at the end of input position. *)
val shrink_to_end : 'a pos -> 'a pos

val set_col_start : int -> 'a pos -> 'a pos

val set_col_end : int -> 'a pos -> 'a pos

val make_from_lnum_bol_offset :
  pos_file:Relative_path.t ->
  pos_start:int * int * int ->
  pos_end:int * int * int ->
  t

module Map : WrappedMap.S with type key = t

module AbsolutePosMap : WrappedMap.S with type key = absolute

module Set : Set.S with type elt = t

val print_verbose_absolute : absolute -> string

val print_verbose_relative : t -> string

val pessimize_enabled : t -> float -> bool

val set_from_reason : 'a pos -> 'a pos

val get_from_reason : 'a pos -> bool
