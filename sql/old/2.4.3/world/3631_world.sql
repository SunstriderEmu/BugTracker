DELETE FROM trinity_string WHERE entry = 11013;
INSERT INTO trinity_string (entry, content_default, content_loc2) VALUES (11013, 'There are not enough free slots in your inventory.', "Il n'y a pas assez d'espace libre dans votre inventaire.");

ALTER TABLE recups_data ADD stufflevel INT NOT NULL AFTER stuff;
DELETE FROM recups_data WHERE phase = 2 AND classe != 0;
INSERT INTO recups_data (classe, faction, phase, command, metier, stuff, stufflevel) VALUES

-- DPS: 0, Heal: 1, Tank: 2
-- S1: 0, T4: 1, T5: 2

-- S1 Warrior DPS
(1, 0, 2, 'additem 24544 1;additem 24549 1;additem 24545 1;additem 24547 1;additem 24546 1;additem 27495 1;additem 28529 1;additem 28795 1;additem 28779 1;additem 28608 1;additem 28730 1;additem 30738 1;additem 28579 1;additem 32534 1;additem 28573 1;additem 28659 1', 0, 0, 0),
-- S1 Warrier Tank
(1, 0, 2, 'additem 24544 1;additem 24549 1;additem 24545 1;additem 24547 1;additem 24546 1;additem 28516 1;additem 28660 1;additem 28502 1;additem 28566 1;additem 30641 1;additem 28675 1;additem 28730 1;additem 28528 1;additem 32534 1;additem 29362 1;additem 28606 1;additem 28581 1', 0, 2, 0),
-- S1 Paladin DPS
(2, 0, 2, 'additem 31613 1;additem 31614 1;additem 31616 1;additem 31618 1;additem 31619 1;additem 27495 1;additem 30729 1;additem 28795 1;additem 28779 1;additem 28608 1;additem 28730 1;additem 30738 1;additem 28579 1;additem 32534 1;additem 28573 1;additem 27484 1', 0, 0, 0),
-- S1 Paladin Heal
(2, 0, 2, 'additem 27702 1;additem 27703 1;additem 27704 1;additem 27705 1;additem 27706 1;additem 28731 1;additem 28582 1;additem 28512 1;additem 28733 1;additem 34612 1;additem 28661 1;additem 30736 1;additem 28590 1;additem 28727 1;additem 28522 1;additem 28611 1;additem 28296 1', 0, 1, 0),
-- S1 Paladin Tank
(2, 0, 2, 'additem 27879 1;additem 27880 1;additem 27881 1;additem 27882 1;additem 27883 1;additem 28516 1;additem 28660 1;additem 28502 1;additem 28566 1;additem 28569 1;additem 28675 1;additem 28730 1;additem 28528 1;additem 32534 1;additem 27899 1;additem 28611 1;additem 27484 1', 0, 2, 0),
-- S1 Hunter DPS
(3, 0, 2, 'additem 28334 1;additem 28335 1;additem 28331 1;additem 28332 1;additem 28333 1;additem 28509 1;additem 28672 1;additem 28454 1;additem 30643 1;additem 28610 1;additem 28649 1;additem 30738 1;additem 28288 1;additem 28034 1;additem 28587 1;additem 28504 1', 0, 0, 0),
-- S1 Rogue DPS
(4, 0, 2, 'additem 25834 1;additem 25833 1;additem 25830 1;additem 25832 1;additem 25831 1;additem 28509 1;additem 30729 1;additem 28514 1;additem 28828 1;additem 28545 1;additem 28649 1;additem 30738 1;additem 28579 1;additem 28034 1;additem 28524 1;additem 37597 1;additem 28659 1', 0, 0, 0),
-- S1 Priest DPS
(5, 0, 2, 'additem 27707 1;additem 27708 1;additem 27709 1;additem 27710 1;additem 27711 1;additem 28731 1;additem 28570 1;additem 28515 1;additem 28654 1;additem 28517 1;additem 28510 1;additem 28763 1;additem 28785 1;additem 28370 1;additem 28633 1;additem 28673 1', 0, 0, 0),
-- S1 Priest Heal
(5, 0, 2, 'additem 31409 1;additem 31410 1;additem 31411 1;additem 31412 1;additem 31413 1;additem 28731 1;additem 28582 1;additem 28511 1;additem 28652 1;additem 28663 1;additem 28661 1;additem 28763 1;additem 28590 1;additem 28727 1;additem 28604 1;additem 28588 1', 0, 1, 0),
-- S1 Shaman DPS Elem (stuff=0)
(7, 0, 2, 'additem 25997 1;additem 26000 1;additem 25998 1;additem 26001 1;additem 25999 1;additem 28762 1;additem 28570 1;additem 28503 1;additem 28828 1;additem 28177 1;additem 28510 1;additem 28763 1;additem 28785 1;additem 28370 1;additem 34611 1;additem 28611 1;additem 27544 1', 0, 0, 0),
-- S1 Shaman DPS amélio (stuff=2)
(7, 0, 2, 'additem 27469 1;additem 27470 1;additem 27471 1;additem 27472 1;additem 27473 1;additem 28509 1;additem 30729 1;additem 28454 1;additem 28828 1;additem 28610 1;additem 28730 1;additem 30738 1;additem 28288 1;additem 28579 1;additem 34616 2;additem 27815 1', 0, 2, 0),
-- S1 Shaman Heal
(7, 0, 2, 'additem 31396 1;additem 31397 1;additem 31400 1;additem 31406 1;additem 31407 1;additem 28731 1;additem 28582 1;additem 28503 1;additem 28655 1;additem 28177 1;additem 28661 1;additem 30736 1;additem 28590 1;additem 28727 1;additem 28522 1;additem 28611 1;additem 27544 1', 0, 1, 0),
-- S1 Mage DPS
(8, 0, 2, 'additem 25854 1;additem 25855 1;additem 25857 1;additem 25856 1;additem 25858 1;additem 28731 1;additem 30735 1;additem 28515 1;additem 28654 1;additem 28517 1;additem 28510 1;additem 28763 1;additem 28785 1;additem 28370 1;additem 28633 1;additem 28673 1', 0, 0, 0),
-- S1 Warlock DPS
(9, 0, 2, 'additem 24556 1;additem 24553 1;additem 24555 1;additem 24554 1;additem 24552 1;additem 28731 1;additem 30735 1;additem 28515 1;additem 28654 1;additem 28517 1;additem 28510 1;additem 28763 1;additem 28785 1;additem 28370 1;additem 28633 1;additem 28673 1', 0, 0, 0),
-- S1 Druid DPS equi (stuff=0)
(11, 0, 2, 'additem 28136 1;additem 28137 1;additem 28138 1;additem 28139 1;additem 28140 1;additem 28731 1;additem 30735 1;additem 28453 1;additem 29524 1;additem 30737 1;additem 30667 1;additem 28510 1;additem 28785 1;additem 28370 1;additem 28633 1;additem 28568 1', 0, 0, 0),
-- S1 Druid Heal
(11, 0, 2, 'additem 31375 1;additem 31376 1;additem 31377 1;additem 31378 1;additem 31379 1;additem 28731 1;additem 28582 1;additem 28453 1;additem 28655 1;additem 30737 1;additem 28661 1;additem 28763 1;additem 28590 1;additem 28727 1;additem 28604 1;additem 28568 1', 0, 1, 0),
-- S1 Druid Tank/DPS feral (stuff=2)
(11, 0, 2, 'additem 28126 1;additem 28127 1;additem 28128 1;additem 28129 1;additem 28130 1;additem 28509 1;additem 30729 1;additem 28514 1;additem 28828 1;additem 30674 1;additem 28730 1;additem 28675 1;additem 28528 1;additem 28034 1;additem 28658 1;additem 27744 1', 0, 2, 0),

-- T4 Warrior DPS
(1, 0, 2, 'additemset 655;additem 27495 1;additem 28529 1;additem 28795 1;additem 28779 1;additem 28608 1;additem 28730 1;additem 30738 1;additem 28288 1;additem 28034 1;additem 28657 1;additem 28768 1;additem 28659 1', 0, 0, 1),
-- T4 Warrier Tank
(1, 0, 2, 'additemset 654;additem 28516 1;additem 28660 1;additem 28502 1;additem 28566 1;additem 30641 1;additem 28675 1;additem 28730 1;additem 28528 1;additem 32534 1;additem 29362 1;additem 28606 1;additem 28581 1', 0, 2, 1),
-- T4 Paladin DPS
(2, 0, 2, 'additemset 626;additem 27495 1;additem 30729 1;additem 28795 1;additem 28779 1;additem 28608 1;additem 28730 1;additem 30738 1;additem 28288 1;additem 28034 1;additem 28573 1;additem 27484 1', 0, 0, 1),
-- T4 Paladin Heal
(2, 0, 2, 'additemset 624;additem 28731 1;additem 28582 1;additem 28512 1;additem 28733 1;additem 34612 1;additem 28661 1;additem 30736 1;additem 28590 1;additem 28190 1;additem 28522 1;additem 28611 1;additem 25644 1', 0, 1, 1),
-- T4 Paladin Tank
(2, 0, 2, 'additemset 625;additem 28516 1;additem 28660 1;additem 28502 1;additem 28566 1;additem 28569 1;additem 28675 1;additem 28730 1;additem 28528 1;additem 32534 1;additem 27899 1;additem 28611 1;additem 27484 1', 0, 2, 1),
-- T4 Hunter DPS
(3, 0, 2, 'additemset 651;additem 28509 1;additem 28672 1;additem 28454 1;additem 30643 1;additem 28610 1;additem 28649 1;additem 30738 1;additem 28288 1;additem 28034 1;additem 28587 1;additem 28504 1', 0, 0, 1),
-- T4 Rogue DPS
(4, 0, 2, 'additemset 621;additem 28509 1;additem 28672 1;additem 28514 1;additem 28828 1;additem 28545 1;additem 28649 1;additem 28757 1;additem 28288 1;additem 28034 1;additem 28584 1;additem 28572 1;additem 28659 1', 0, 0, 1),
-- T4 Priest DPS
(5, 0, 2, 'additemset 664;additem 30666 1;additem 28570 1;additem 28515 1;additem 28654 1;additem 28517 1;additem 28510 1;additem 28753 1;additem 28785 1;additem 28418 1;additem 28770 1;additem 28603 1;additem 28673 1', 0, 0, 1),
-- T4 Priest Heal
(5, 0, 2, 'additemset 663;additem 28731 1;additem 28582 1;additem 28511 1;additem 28652 1;additem 28663 1;additem 28661 1;additem 28763 1;additem 28190 1;additem 28370 1;additem 28604 1;additem 28588 1', 0, 1, 1),
-- T4 Shaman DPS Elem (stuff=0)
(7, 0, 2, 'additemset 632;additem 28762 1;additem 28570 1;additem 28503 1;additem 28654 1;additem 28517 1;additem 28510 1;additem 30667 1;additem 28785 1;additem 28370 1;additem 28770 1;additem 28611 1;additem 28248 1', 0, 0, 1),
-- T4 Shaman DPS amélio (stuff=2)
(7, 0, 2, 'additemset 633;additem 28509 1;additem 30729 1;additem 28454 1;additem 28828 1;additem 28610 1;additem 28649 1;additem 30738 1;additem 28288 1;additem 28034 1;additem 28657 1;additem 28524 1;additem 27815 1', 0, 2, 1),
-- T4 Shaman Heal
(7, 0, 2, 'additemset 631;additem 28731 1;additem 28582 1;additem 28503 1;additem 28567 1;additem 28177 1;additem 28661 1;additem 30736 1;additem 28590 1;additem 28190 1;additem 28522 1;additem 29267 1;additem 28523 1', 0, 1, 1),
-- T4 Mage DPS
(8, 0, 2, 'additemset 648;additem 28762 1;additem 30735 1;additem 28515 1;additem 28654 1;additem 28517 1;additem 28510 1;additem 30667 1;additem 28785 1;additem 28418 1;additem 28770 1;additem 28603 1;additem 28673 1', 0, 0, 1),
-- T4 Warlock DPS
(9, 0, 2, 'additemset 645;additem 28762 1;additem 30735 1;additem 28515 1;additem 28654 1;additem 28517 1;additem 28510 1;additem 30667 1;additem 28785 1;additem 28418 1;additem 28770 1;additem 28603 1;additem 28673 1', 0, 0, 1),
-- T4 Druid DPS equi (stuff=0)
(11, 0, 2, 'additemset 639;additem 28762 1;additem 30735 1;additem 28453 1;additem 28654 1;additem 27914 1;additem 30667 1;additem 28510 1;additem 28785 1;additem 28418 1;additem 28770 1;additem 28603 1;additem 28568 1', 0, 0, 1),
-- T4 Druid Heal
(11, 0, 2, 'additemset 638;additem 28731 1;additem 28582 1;additem 27827 1;additem 28655 1;additem 30737 1;additem 28661 1;additem 28763 1;additem 28590 1;additem 28727 1;additem 28604 1;additem 28568 1', 0, 1, 1),
-- T4 Druid Tank/DPS feral (stuff=2)
(11, 0, 2, 'additemset 640;additem 28509 1;additem 30729 1;additem 28514 1;additem 28828 1;additem 30674 1;additem 28730 1;additem 28675 1;additem 28528 1;additem 28034 1;additem 28658 1;additem 27744 1', 0, 2, 1),

-- T5 Warrior DPS
(1, 0, 2, 'additemset 657;additem 30022 1;additem 30098 1;additem 30057 1;additem 33331 1;additem 30081 1;additem 29997 1;additem 33055 1;additem 28288 1;additem 28034 1;additem 30082 1;additem 29962 1;additem 28659 1', 0, 0, 2),
-- T5 Warrior Tank
(1, 0, 2, 'additemset 656;additem 30099 1;additem 33593 1;additem 32515 1;additem 33279 1;additem 32267 1;additem 30083 1;additem 30028 1;additem 28528 1;additem 30629 1;additem 30058 1;additem 33326 1;additem 28581 1', 0, 2, 2),
-- T5 Paladin DPS
(2, 0, 2, 'additemset 629;additem 30022 1;additem 30098 1;additem 30057 1;additem 33331 1;additem 30081 1;additem 29997 1;additem 33055 1;additem 28288 1;additem 28034 1;additem 28774 1;additem 27484 1', 0, 0, 2),
-- T5 Paladin Heal
(2, 0, 2, 'additemset 627;additem 29374 1;additem 28765 1;additem 33520 1;additem 33446 1;additem 33207 1;additem 30110 1;additem 28790 1;additem 29376 1;additem 28190 1;additem 34611 1;additem 33332 1;additem 25644 1', 0, 1, 2),
-- T5 Paladin Tank
(2, 0, 2, 'additemset 628;additem 30099 1;additem 33593 1;additem 32515 1;additem 33524 1;additem 33523 1;additem 30083 1;additem 30028 1;additem 28528 1;additem 30629 1;additem 29962 1;additem 29388 1', 0, 2, 2),
-- T5 Hunter DPS
(3, 0, 2, 'additemset 652;additem 29381 1;additem 29994 1;additem 30026 1;additem 30068 1;additem 29951 1;additem 30052 1;additem 30738 1;additem 28288 1;additem 28034 1;additem 29924 2;additem 28772 1', 0, 0, 2),
-- T5 Rogue DPS
(4, 0, 2, 'additemset 622;additem 29381 1;additem 28672 1;additem 33540 1;additem 33211 1;additem 33222 1;additem 30052 1;additem 29997 1;additem 28288 1;additem 28034 1;additem 30082 1;additem 28572 1;additem 28659 1', 0, 0, 2),
-- T5 Priest DPS
(5, 0, 2, 'additemset 666;additem 30666 1;additem 28766 1;additem 33588 1;additem 33291 1;additem 30050 1;additem 33058 1;additem 30109 1;additem 28785 1;additem 29370 1;additem 28770 1;additem 29272 1;additem 29982 1', 0, 0, 2),
-- T5 Priest Heal
(5, 0, 2, 'additemset 665;additem 28731 1;additem 29989 1;additem 32516 1;additem 30036 1;additem 30100 1;additem 28661 1;additem 30110 1;additem 28370 1;additem 29376 1;additem 29981 1;additem 30080 1', 0, 1, 2),
-- T5 Shaman DPS Elem (stuff=0)
(7, 0, 2, 'additemset 635;additem 28762 1;additem 29369 1;additem 33535 1;additem 33536 1;additem 33537 1;additem 33058 1;additem 30109 1;additem 28785 1;additem 29370 1;additem 28770 1;additem 28611 1;additem 33506 1', 0, 0, 2),
-- T5 Shaman DPS amélio (stuff=2)
(7, 0, 2, 'additemset 636;additem 30022 1;additem 30098 1;additem 33529 1;additem 30068 1;additem 29951 1;additem 29997 1;additem 33055 1;additem 28288 1;additem 28034 1;additem 29924 1;additem 30103 1;additem 27815 1', 0, 2, 2),
-- T5 Shaman Heal
(7, 0, 2, 'additemset 634;additem 29374 1;additem 28765 1;additem 33532 1;additem 33386 1;additem 30066 1;additem 28790 1;additem 30110 1;additem 28590 1;additem 30619 1;additem 30108 1;additem 29458 1;additem 27544 1', 0, 1, 2),
-- T5 Mage DPS
(8, 0, 2, 'additemset 649;additem 28762 1;additem 28766 1;additem 33588 1;additem 33291 1;additem 30050 1;additem 33058 1;additem 30109 1;additem 28418 1;additem 29370 1;additem 30095 1;additem 30049 1;additem 29982 1', 0, 0, 2),
-- T5 Warlock DPS
(9, 0, 2, 'additemset 646;additem 28762 1;additem 28766 1;additem 33588 1;additem 33291 1;additem 30050 1;additem 33058 1;additem 30109 1;additem 27683 1;additem 29370 1;additem 30095 1;additem 30049 1;additem 29982 1', 0, 0, 2),
-- T5 Druid DPS equi (stuff=0)
(11, 0, 2, 'additemset 643;additem 28762 1;additem 28766 1;additem 33578 1;additem 33559 1;additem 33577 1;additem 33058 1;additem 30109 1;additem 27683 1;additem 29370 1;additem 28770 1;additem 30049 1;additem 27518 1', 0, 0, 2),
-- T5 Druid Tank/DPS feral (stuff=2)
(11, 0, 2, 'additemset 641;additem 30099 1;additem 33593 1;additem 29966 1;additem 33583 1;additem 33582 1;additem 30083 1;additem 30052 1;additem 28528 1;additem 28034 1;additem 30021 1;additem 27744 1', 0, 2, 2),
-- T5 Druid Heal
(11, 0, 2, 'additemset 642;additem 28731 1;additem 29989 1;additem 33557 1;additem 29984 1;additem 30092 1;additem 28661 1;additem 30110 1;additem 28370 1;additem 28727 1;additem 29981 1;additem 30051 1', 0, 1, 2);
