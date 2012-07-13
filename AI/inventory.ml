(*
 * Fiahil
 * 06.07.2012
 *)

type resources =
  | Joueur
  | Nourriture
  | Linemate
  | Deraumere
  | Sibur
  | Mendiane
  | Phiras
  | Thystame

type t =
    {
      joueur : int;
      nourriture : int;
      linemate : int;
      deraumere : int;
      sibur : int;
      mendiane : int;
      phiras : int;
      thystame : int
    }

let empty () =
  {
    joueur = 0;
    nourriture = 0;
    linemate = 0;
    deraumere = 0;
    sibur = 0;
    mendiane = 0;
    phiras = 0;
    thystame = 0
  }

let inc iv = function
  | Joueur              ->
      {
        joueur = iv.joueur + 1;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Nourriture          ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture + 1;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Linemate            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate + 1;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Deraumere           ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere + 1;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Sibur               ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur + 1;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Mendiane            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane + 1;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Phiras              ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras + 1;
        thystame = iv.thystame
      }
  | Thystame            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame + 1
      }

let dec iv = function
  | Joueur              ->
      {
        joueur = iv.joueur - 1;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Nourriture          ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture - 1;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Linemate            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate - 1;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Deraumere           ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere - 1;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Sibur               ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur - 1;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Mendiane            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane - 1;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Phiras              ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras - 1;
        thystame = iv.thystame
      }
  | Thystame            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame - 1
      }

let set iv nb = function
  | Joueur              ->
      {
        joueur = nb;
        nourriture = nb;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Nourriture          ->
      {
        joueur = iv.joueur;
        nourriture = nb;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Linemate            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = nb;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Deraumere           ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = nb;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Sibur               ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = nb;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Mendiane            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = nb;
        phiras = iv.phiras;
        thystame = iv.thystame
      }
  | Phiras              ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = nb;
        thystame = iv.thystame
      }
  | Thystame            ->
      {
        joueur = iv.joueur;
        nourriture = iv.nourriture;
        linemate = iv.linemate;
        deraumere = iv.deraumere;
        sibur = iv.sibur;
        mendiane = iv.mendiane;
        phiras = iv.phiras;
        thystame = nb
      }
