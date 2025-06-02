void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Que voulez-vous?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Oh, quelle chaleur aujourd'hui. Autant s'attacher un boulet ramé à la jambe et sauter à la mer, juste pour se débarrasser de cette étouffante!";
			link.l1 = "Ha-ha, Charlie!.. Ce sont des mesures extrêmes, si tu veux mon avis. Mais je ne dirais pas non à une petite goutte - il fait vraiment trop chaud aujourd'hui. T'es partant?";
			link.l1.go = "DTSG_Knippel_2";
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Boire un coup ou deux avec vous, Capitaine ? Toujours !";
			link.l1 = "C'est ce que j'aime entendre. Allons-y !";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
			FreeSitLocator("BasTer_tavern", "sit_base2");
			FreeSitLocator("BasTer_tavern", "sit_front2");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Hé, marin, tu as l'air d'avoir tout vu ! Allons boire un coup et échanger quelques histoires ? C'est moi qui régale !";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Euh, non merci, l'ami. Je suis venu ici avec mon capitaine. Trouve quelqu'un d'autre.";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ha, un vaurien comme toi a de si hautes opinions, tu ne bois qu'avec des capitaines ?";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Grandes opinions ?! J'ai servi pendant des décennies dans la Royal Navy ! Et je n'ai pas combattu pour les seigneurs, mais pour les gens ordinaires comme toi et moi, pour assurer la loi et l'ordre partout !..";
			link.l1 = " ";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Tu parles fort, mais tu ne bois qu'avec des capitaines et des nobles ! On dirait bien que la Marine t'a appris à astiquer les canons comme il faut, ha !";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Je t'enfoncerai une mitraille dans le gosier, morveux !";
			link.l1 = "Charlie, ne t'affole pas comme ça, ça n'en vaut pas la peine.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Laissez-moi m'occuper de cela, Capitaine. L'honneur de la Marine est en jeu, je dois le défendre moi-même et ne pas me cacher derrière quelqu'un...";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("Blaze");
			LAi_SetImmortal(sld, true);
			LAi_CharacterDisableDialog(sld);
			LAi_SetSitType(sld);
			sld = CharacterFromID("Baster_Smuggler");
			LAi_SetImmortal(sld, true);
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = CharacterFromID("DTSG_Ohotnik");
			ChangeCharacterAddressGroup(sld, "BasTer_tavern", "tables", "stay7");
			DoQuestReloadToLocation("BasTer_tavern", "tables", "stay6", "DTSG_BasTerTavern_7");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Merci d'avoir attendu, Capitaine. J'espère ne pas avoir pris trop de temps.";
			link.l1 = "Ne t'en fais pas. Tu n'es pas blessé ? Ce scélérat était plutôt bon.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Ne vous inquiétez pas, Capitaine. L'important, c'est qu'il a eu ce qu'il méritait. J'ai récupéré une sorte de clé sur son corps...";
			link.l1 = " ";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "J'ai ramassé une sorte de clé sur son corps... Je me demande à quoi elle pourrait servir ?";
			link.l1 = "Elementaire, Charlie... Pour une porte ou un coffre, ha-ha. Nous devrions parler à l'aubergiste au sujet de ce scélérat, cela pourrait être utile.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			pchar.questTemp.DTSG_BasTerTavern = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Incroyable...";
			link.l1 = "Tu penses à ce que je pense, Charlie ?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Je ne sais pas pour vous, monsieur, mais je suis surpris de voir combien d'argent il y a ici - il avait l'air d'un homme ordinaire, pas d'un marchand ou d'un noble.";
			link.l1 = "Ce n'est pas grand-chose, vraiment, mais tu as raison. Ce qui me surprend, c'est cette étrange lettre brûlée.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Oui, ce n'était pas très malin de sa part - c'est comme tirer une mitraille sur une coque robuste. Il aurait dû détruire la lettre complètement.";
			link.l1 = "Vrai. Mais cela ne nous aide pas - nous ne savons pas qui il était ni avec qui il correspondait. Allons-y, Charlie, il n'y a plus rien pour nous ici.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			Return_KnippelOfficer();;

			AddQuestRecord("DTSG", "2");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.DTSG_Nastoroje1 = true;
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "Tellement pour ta vantée Marine Royale, pfft !";
			link.l1 = "Charlie etait un bon, brave homme. Et il etait un canonnier, pas un marine.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Un canonnier ?! Alors, c'est exactement comme je l'ai dit, ha-ha-ha ! Et ne me regarde pas de travers - tu aurais dû savoir qui tu prenais dans ton équipage.";
			link.l1 = "Tu aurais dû savoir avec qui tu t'embarquais.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Tu es encore en vie seulement parce que tu as gagné honnêtement, alors tiens ta langue pourrie et dégage d'ici.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Eh bien, je pensais que je devrais te combattre ensuite. C'est agréable d'entendre que l'honneur signifie quelque chose pour toi.";
			link.l1 = "Ce n'étaient pas que de vains mots pour Charlie non plus. Mais en ce qui te concerne, j'ai des doutes. Quoi qu'il en soit, cela n'a plus d'importance maintenant.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			ChangeCharacterComplexReputation(pchar, "fame", -3);	
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "Et avec qui ai-je eu des ennuis, un faible gâté ?! As-tu même vu ta propre fine moustache ?..";
			link.l1 = "Tu sais vraiment appuyer sur les nerfs... Ce sera d'autant plus satisfaisant de passer ma colère sur toi.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("DTSG_Ohotnik");
			DeleteAttribute(sld, "CantLoot");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Attendez, Capitaine. Je vois que vous êtes un homme digne et noble, pouvez-vous m'aider avec quelque chose ? C'est une question d'honneur.";
			link.l1 = "Peut-être que je peux, mais quel est le problème ? Et pourquoi es-tu venu me voir ? Il y a beaucoup de nobles par ici. A qui ai-je l'honneur de parler, d'ailleurs ?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. Je vois bien que tu n'es pas un descendant gâté d'une vieille famille, mais un homme fiable avec une main ferme.";
			link.l1 = "Oh, vous auriez dû me voir quand je suis arrivé aux Caraïbes pour la première fois, monsieur. Mais allez-y, de quoi avez-vous besoin d'aide?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Pourriez-vous... vous battre en duel à ma place, monsieur ? Un fauteur de troubles local, Ralph Faggle, a insulté ma femme. Et il l'a harcelée, publiquement. Juste devant moi. Pouvez-vous imaginer cela ?";
			link.l1 = "Il n'y a pas beaucoup d'honneur à provoquer un duel puis à se cacher derrière quelqu'un d'autre. Surtout quand ce n'est pas seulement votre honneur personnel en jeu, mais celui d'une femme, votre épouse qui plus est. Ne le pensez-vous pas, Adams? Pourquoi ne pouvez-vous pas vous battre pour votre femme vous-même?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "Et vous avez raison, absolument raison. Mais j'ai récemment souffert d'une forte fièvre, et je peux à peine me tenir sur mes pieds\nIl est vrai que ce n'est pas facile pour moi de vous demander quelque chose comme ça. S'il m'avait insulté, je l'aurais supporté. Mais pas quand l'honneur de ma femme est en jeu ! Je ne suis pas un lâche, monsieur. J'ai servi autrefois dans la Marine Royale et j'ai navigué sur le même navire que Robert Blake lui-même !";
			link.l1 = "Je...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Nous t'aiderons.";
			link.l1 = "Charlie ?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "C'est un homme digne, Capitaine. Et que je sois damné à l'éternité par des boulets de canon si ce n'est pas vrai ! De grands hommes ont servi avec l'amiral Blake. Ils se sont battus ensemble pour que personne n'opprime le peuple\nEt grâce à lui, la Jamaïque a été libérée de la tyrannie des Espagnols !";
			link.l1 = "  Même si c'est le cas, je n'autoriserai pas mes hommes d'équipage à m'interrompre ou à prendre des décisions pour moi. Est-ce clair ?  ";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Je comprends, vraiment. Cependant, je n'ai même pas eu la chance de répondre. Essaie de ne pas être si hâtif et de m'interrompre à l'avenir, d'accord ?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Je vous le dis, Capitaine - si vous n'aidez pas cet homme, le vieux Charlie laissera tout tomber et se battra en duel pour lui-même, que je sois damné sur place !";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Calme-toi, je n'ai pas dit que je refuse d'aider. N'est-ce pas, M. Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Honnêtement, Charlie, tu me fais passer pour un lâche. Et je ne l'ai jamais été. Tu devrais le savoir.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "  Euh, pardon, Capitaine, je me suis laissé emporter.  ";
			link.l1 = "C'est bon. Mais restez maître de vous-même, d'accord ?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Je me battrai en duel pour vous, Mr. Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Merci, monsieur ! Que Dieu vous bénisse !";
			link.l1 = "Et bénissez aussi le Lord Protecteur, n'est-ce pas, M. Adams ? Ne t'inquiète pas, Charles de Maure ne laisse jamais un homme honnête dans le pétrin.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Nous vous en sommes reconnaissants, Monsieur de Maure, monsieur ! Voudriez-vous venir dîner avec Jane et moi ?";
			link.l1 = "Eh bien, je...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "J'insiste !";
			link.l1 = "Eh bien, seulement si tu insistes. Merci, Peter. Montre le chemin.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Bien sûr, c'est vrai, monsieur ! Voudriez-vous venir avec Jane et vous reposer après votre voyage ?";
			link.l1 = "Je vous remercie, mais est-il juste de profiter de votre hospitalité ?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "Oh, au contraire, Capitaine, nous serions offensés si vous ne veniez pas.";
			link.l1 = "Comment aurais-je pu refuser à l'époque ? Après vous, Peter !";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "C'est nous ! S'il vous plaît, entrez.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Merci. Puis-je parler à Jane? Demande-lui comment cela s'est passé - j'ai besoin de tous les détails.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Je vous présente mes plus sincères excuses, mais après réflexion, je dois décliner. J'ai un duel à préparer. Au fait, où et quand est-il prévu ?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Eh bien, bien sûr, monsieur. Nous serons tous deux ravis de vous parler et de répondre à toutes vos questions. Veuillez me suivre, je vous prie.";
			link.l1 = "Merci, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Quel dommage ! Mais tu as raison, tu devrais te préparer soigneusement, bien sûr. Deux heures. Juste à l'extérieur des portes de la ville.";
			link.l1 = "Compris, merci. Je viendrai avec plaisir une fois que ce sera terminé. À bientôt !";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			npchar.location = "None";
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
			
			PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
			PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
			
			AddQuestRecord("DTSG", "3");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Bienvenue ! Chéri, tu ne m'as pas dit que tu amenais des invités - j'aurais fait les choses comme il faut.";
			link.l1 = "Merci, madame, nous ne serons pas longs. Charles de Maure, à votre service. J'ai accepté d'entendre votre histoire avec votre mari. Dites-moi comment cela s'est passé.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Oh, c'était horrible ! Ralph était complètement ivre. Il a commencé à m'harceler devant les voisins, même devant Peter, en disant des choses obscènes...";
			link.l1 = "Que t'a-t-il dit exactement ?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Je suis trop embarrassé pour en parler. Puis il a dégrisé, et...";
			link.l1 = "Avez-vous présenté des excuses et demandé d'annuler le duel, peut-être ?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Pas une seule fois.";
			link.l1 = "Je suis désolé pour vous. J'aimerais savoir une chose de plus, si vous le permettez, madame.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "Et qu'est-ce que c'est, monsieur?";
			link.l1 = "Quelles circonstances de vie et épreuves vous ont forcés, vous et votre mari, à vivre ici ? Dans n'importe quelle ville anglaise, étant donné les mérites de votre mari, vous auriez déjà remis Ralph à sa place.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Je vous demande pardon, monsieur, mais comment osez-vous ?! Si vous n'étiez pas mon capitaine, je prendrais une mitraille et je vous donnerais une bonne raclée !\nNon seulement vous vous méfiez d'un homme aussi digne que M. Adams, mais vous vous moquez aussi d'une dame en détresse...";
			link.l1 = "As-tu entendu que je me moquais d'une dame? Non? Alors ne me calomnie pas. Nos gens auraient pu les aider, c'est pourquoi j'ai demandé.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Calme-toi, Charlie ! Comment as-tu pu... Je voulais juste en savoir plus sur les difficultés de Jane et Peter et compatir avec eux. Dans les colonies anglaises, ils auraient sûrement été aidés à présent.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "La vie peut prendre bien des tournures... Le naufrage. Ou la calomnie de quelqu'un, qui peut parfois forcer même des gens aussi honnêtes à se cacher dans la disgrâce. \nSi tu es si méfiant et suspicieux - tu peux parler aux voisins. Je suis sûr qu'ils confirmeront chaque mot. Mais le vieux Charlie ne se rabaisserait pas à discuter du chagrin des gens dans leur dos !";
			link.l1 = "N'as-tu pas entendu? J'ai dit que j'aiderais ces gens.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "La vie peut prendre bien des tournures... Le naufrage. Ou les calomnies de quelqu'un, qui peuvent parfois forcer même des gens honnêtes à se cacher dans la honte.\nSi vous êtes si méfiant et suspicieux - vous pouvez parler aux voisins. Je suis sûr qu'ils confirmeront chaque mot. Mais le vieux Charlie ne s'abaisserait pas à discuter de la peine des gens derrière leur dos !";
			link.l1 = "N'as-tu pas entendu ce que je dis ? J'ai dit que j'aiderais ces gens.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Merci du fond du coeur. Nous te garderons dans nos prières.";
			link.l1 = "C'est bien. Au fait, concernant notre affaire. Où et quand avez-vous arrangé le duel, Monsieur Adams ?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "Devant les portes de la ville, monsieur. Dans deux heures.";
			link.l1 = "Je m'en sortirai. Attendez-moi avec de bonnes nouvelles. Et ne pensez pas à allumer une chandelle pour mon repos avant l'heure !";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Quelque chose te tracasse, Capitaine ? Tu as l'air bien pensif.";
			link.l1 = "Tu sais, oui. Il y a quelque chose dans l'histoire d'Adams qui ne colle pas, et...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Combien de temps cela va-t-il durer, monsieur ?! Réagissez-vous ainsi chaque fois que quelqu'un a besoin d'aide ?";
			link.l1 = "Pour l'amour du ciel, parle doucement. Tu vas le crier à toute la rue. J'ai dit que j'irais au duel. Cela ne te suffit-il pas ? Maintenant, écoute-moi attentivement.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Hmm, d'accord, Capitaine. Désolé pour mon emportement - je me soucie du sort de ceux qui ont servi dans la Marine Royale. Beaucoup d'entre nous étaient de braves gars, méritant un meilleur sort que celui qu'ils ont reçu.";
			link.l1 = "Je te comprends, Charlie. Maintenant, souviens-toi de ce qui doit être fait. Je veux que tu envoies quelques membres de l'équipage aux portes de la ville. À l'approche de l'heure du duel, qu'ils se rassemblent discrètement et soient prêts pour mon signal.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Comptes-tu transformer un duel honnête en meurtre ?";
			link.l1 = "Je soupçonne que ce ne sera pas entièrement honnête. Je signalerai seulement si nécessaire. Si tout est vraiment en règle, je serai heureux de m'être trompé. Comprends-tu maintenant ? Te souviens-tu de ce qui s'est passé il y a un mois ?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Compris, monsieur. Franchement, ça ne me plaît pas trop, mais je ferai ce qui est nécessaire. Ne vous inquiétez pas.";
			link.l1 = "C'est ce que je voulais entendre.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.location = "None";
			AddDialogExitQuestFunction("DTSG_Knippel_36");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "Alors, de Maure. Tu es en avance. Et nous sommes encore en ville. Bien que cela ne fasse pas de différence. Dommage que tu n'aies pas amené ce vieux fou avec toi. Mais ne t'inquiète pas, nous le trouverons en temps voulu.";
			link.l1 = "À votre service à tout moment. Mercenaires, hein ? Qui ai-je froissé ?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "C'est bien ça, personne d'autre. On est après ce vieux schnock, Charlie, et c'est plus facile de le trouver par ton intermédiaire, car on a appris qu'il est maintenant sur ton bateau. Ce n'est pas la jungle ici, donc il faudra agir rapidement pour éviter de faire du tapage. Mais ici, au moins, tu ne pourras pas t'échapper.";
			link.l1 = "Je suppose que toute cette affaire de duel était un piège ?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Un peu tard pour s'en rendre compte, ami. Nous nous serions battus de toute façon - je suis Ralph Faggle, à votre service.";
			link.l1 = "En fait, je m'en doutais un peu, alors j'ai décidé de parler aux voisins. Au fait, Adams est-il aussi impliqué là-dedans ? Et Jane ? Pourrait-elle être...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "La curiosité a tué le chat, tu n'as pas entendu ? On t'avait dit de te présenter pour le duel, pas de fouiner. Tu pourrais avoir une chance de survivre à ce pétrin\nBien sûr. Provoquer le vieux marin et forcer son officier commandant à un duel - un plan parfait que nous avons concocté avec Peter, je pense. Et Jane a bien joué son rôle aussi.";
			link.l1 = "Dis-moi, qui voulait se débarrasser de Charlie ?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ha, comme si je te le dirais ? Défends-toi.";
			link.l1 = "Quel dommage. Alors je demanderai à Peter plus tard.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Oh, je vois que vous avez pris mon histoire à coeur et déjà puni Ralph, Capitaine.";
			link.l1 = "Bien sûr, puisque comme vous l'avez noté, je suis un homme digne et noble. Et maintenant, je vais devoir vous punir pour ce piège traître.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Vous êtes le bienvenu pour essayer, Capitaine - sûrement vous êtes déjà épuisé et blessé.";
			link.l1 = "Alors faisons une pause. En attendant, dis-moi, pour qui travailles-tu ?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Désolé, mais mon patron n'aimerait pas ça, même si j'arrivais à m'occuper de toi ensuite. Ce qui, soit dit en passant, va se produire maintenant.";
			link.l1 = "Merde !..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Je ne peux pas croire que ces... ces vauriens nous aient non seulement trompés, mais aussi menti sur la Royal Navy ! Comment osent-ils ! S'ils n'étaient pas morts, je leur ferais avaler quelques boulets ramés pour une telle trahison !..";
			link.l1 = "Les gens mentent sur toutes sortes de choses, Charlie. Je pensais que tu le savais bien. Mais ce que tu sais sûrement, c'est qui les a envoyés. Ce n'est pas le premier piège tendu pour toi récemment. Ils avaient une lettre avec une description détaillée de toi. Qui as-tu tant mis en colère ?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Eh bien, je... Peut-être que nous trouverons autre chose dans la maison des Adams, monsieur ?";
			link.l1 = "Esquiver la question ? Mais tu as raison, j'avais de toute façon prévu de fouiller tout cela à fond. Allons-y.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Sacrés boulets de canon, tant d'or !";
			link.l1 = "Dommage qu'il n'y ait rien d'autre ici. 'Jane' n'est nulle part non plus. Penses-tu qu'elle soit encore en vie ?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Je ne sais pas, monsieur, ces vauriens sont capables de tout...";
			link.l1 = "C'est vrai, mais il me semble que tu en sais plus que tu ne le dis. Ce n'est pas la première fois qu'ils te traquent. Et chaque fois, nous trouvons un tas d'argent sur eux.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Je ne suis pas sûr, Capitaine, mais peut-être que c'était un prêteur sur gages de Saint-Jean.";
			link.l1 = "Comment l'as-tu contrarié?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Eh bien... il y a quelque temps, j'ai emprunté de l'argent à lui pour rembourser toutes mes autres dettes. Richard a promis de payer, mais...";
			link.l1 = "Penses-tu qu'il ne l'a pas fait ?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Je ne l'aurais pas cru auparavant, mais après ce qu'il vous a fait et a quitté précipitamment les Caraïbes avec Abi... Peut-être qu'il a oublié la dette. Ou il ne l'a pas fait mais est parti quand même... Richard s'est comporté comme un vrai salaud, monsieur. Je ne serais pas surpris mais tout de même déçu si cela s'avérait à nouveau vrai.";
			link.l1 = "Ne sois pas si catégorique prématurément, Charlie. Alors, c'est Saint John's.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Ah, vous voilà, monsieur - il semble que tout le monde ait décidé de venir tôt. A en juger par votre apparence, vous semblez assez léger d’esprit, êtes-vous si sûr de vos capacités ?";
				link.l1 = "Naturellement, ce n'est pas mon premier duel.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "J'avais peur que vous ne veniez pas, monsieur. Les autres sont déjà là.";
				link.l1 = "Un vrai noble ne peut être en retard que pour sa mort.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Des mots merveilleux, monsieur ! Voici notre adversaire, Ralph Faggle. Et voici notre second, Frederick Stokes.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Rencontrer...";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Notre adversaire, Ralph Faggle.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "Et voici notre second, Frederick Stokes.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "... ";
			link.l1 = "Alors c'est Ralph ? Il n'a pas l'air d'un ivrogne de voisin typique.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "On ne sait jamais qui pourrait être son voisin, y avez-vous pensé, M. de Maure ? Heh-heh-heh.";
			link.l1 = "Alors, c'est un piège... Je vois que tu as même cessé de trembler. Fatigué de jouer le fiévreux ?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = " La seule chose dont je pourrais me débarrasser maintenant, c'est de rire de ta naïveté.";
			link.l1 = "Eh bien, eh bien. Je ne regrette qu'une chose, c'est que Charlie soit venu - il aurait été plus facile et plus discret de régler cela seul avec toi...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Eh bien, c'est merveilleux !";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Permettez-moi de vous présenter...";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "M. Stokes, notre second.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "Et voici Ralph Faggle.";
			link.l1 = "Alors c'est Ralph ? Je dois admettre que je l'imaginais différemment. Mais peu importe, j'ai affronté pire.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hmm, je me demande, es-tu naïf, ne comprenant rien ? Ou tellement sûr de toi ?";
			link.l1 = "Et qu'est-ce que je ne comprends pas, Monsieur Adams ? Allez, surprenez-moi.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "En général, les gens ont l'air surpris ou effrayés dans de telles situations, mais vous semblez être d'un autre genre. Ce sera d'autant plus agréable d'effacer ce sourire suffisant de votre visage, Monsieur de Maure.";
			link.l1 = "Quelles menaces ! Ne sommes-nous pas du même côté, Peter ?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Ne me dis pas que tu espères nous vaincre tous avec ce vieil homme. Vous êtes en infériorité numérique, mon cher monsieur.";
			link.l1 = "Comme je l'ai dit, c'est TOI qui ne comprends pas. Charlie a grogné un peu, mais je lui ai quand même dit de ramener les gars ici au cas où. Comme il se trouve, pas en vain. LES GARS, VENEZ ICI !!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "Quoi ?..";
			link.l1 = "Surpris et effrayé, M. Adams? Bon à savoir.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "C'est ainsi qu'il faut traiter ces scélérats menteurs. Je n'arrive toujours pas à croire qu'ils aient eu le culot de mentir sur la Royale Marine ! Je les étranglerais avec une chaîne de boulets !..";
			link.l1 = "A présent, tu devrais savoir que certains n'ont aucun scrupule, Charlie. J'ai dit que je m'en occuperais, tu aurais pu rester sur le navire. Vouliez-vous vous assurer que j'aiderais ces 'braves gens' ? Et qui avait encore raison, que ce n'était pas aussi simple que tu le pensais ?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Vous, monsieur...";
			link.l1 = "Exactement. Mais dis-moi, pourquoi quelqu'un voudrait-il te chasser ? Ce n'est pas la première fois.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Je ne sais pas, Capitaine. Le vieux Charlie n'est qu'un simple canonnier.";
			link.l1 = "Hmm, bon, bon. D'accord, puisque nos pauvres duellistes n'avaient rien d'utile avec eux... Non, allons voir si nous pouvons trouver quelque chose dans la maison d'Adams.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "Alors, cette femme a disparu aussi... Peut-être qu'ils se préparaient à fuir la ville juste après ce 'duel'? Et en hâte - tant d'or ici !";
			link.l1 = "Tu as raison, car l'or n'est pas la seule chose qu'ils ont laissée derrière. Une autre lettre. Ils étaient tellement pressés qu'ils ont oublié de la brûler. Regarde, tu vas aimer son contenu.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(lit) Eh bien, je discuterais sur 'vieux'.";
			link.l1 = "Ce n'est pas la question maintenant. C'est la deuxième fois qu'ils envoient des mercenaires après toi et qu'ils leur fournissent de l'argent et des informations. Et c'est toi qu'ils veulent spécifiquement. Dis-moi, simple canonnier, qui as-tu pu mettre en colère à ce point ?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "J'ai une seule hypothèse, monsieur, une seule, et je ne veux vraiment pas qu'elle soit vraie.";
			link.l1 = "Alors, c'est très probablement vrai. Parle.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "J'avais autrefois des dettes envers diverses personnes à St. John's, et...";
			link.l1 = "... et maintenant tu penses qu'ils te chassent ? Combien peuvent se permettre des mercenaires et de telles sommes ?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "Vous réfléchissez bien, monsieur. Finalement, j'ai remboursé presque toutes mes dettes en empruntant à un prêteur sur gages. Il peut se permettre tout cela, bien sûr. Mais...";
			link.l1 = "Mais quoi ? Nous paierons votre dette, et c'est tout. Qu'est-ce qui vous inquiète ?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Voyez-vous, Capitaine, Richard m'a promis qu'il le réglerait pour moi.";
			link.l1 = "Tu penses qu'il ne l'a pas fait ?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Je ne sais plus quoi penser, monsieur. Tout le temps que nous nous connaissions, je le voyais comme un modèle de gentleman. Mais après qu'il vous ait quitté et se soit enfui avec Abigail... Je ne serais pas surpris. C'est pourquoi j'ai dit que je ne voudrais pas que ce soit vrai.";
			link.l1 = "Il faut d'abord vérifier les suppositions, ensuite tu pourras t'énerver, Charlie. Allons-y, tu retourneras à St. John's.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Capitaine!!!";
			link.l1 = "Qu'y a-t-il, Charlie, que s'est-il passé ?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Arrivé ?! Ne me dites pas que vous avez oublié le duel, monsieur ! Adams pourrait déjà être réduit en morceaux pendant que vous vous prélassez ici !";
			link.l1 = "D'accord!.. Je quitterai la ville immédiatement.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Capitaine Charles de Maure ? Est-ce que c'est Charlie Knippel avec vous ?";
			link.l1 = "Non, ceci...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Ne le niez pas, monsieur - tout le monde dans cette colonie connaît Charlie.";
			link.l1 = "Alors pourquoi demander? Comment puis-je aider?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Vous ne pouvez pas. S'il vous plaît, ne résistez pas - Charlie est recherché ici. Nous devons le mettre en détention.";
			link.l1 = "Puis-je savoir quelles accusations sont portées contre mon homme ? Est-ce à cause de sa dette ? Je peux la payer pour lui. Allons chez le banquier tout de suite, en votre présence.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Une dette ? C'est la première fois que j'en entends parler. Je ne connais pas les détails, mais s'il vous plaît, ne compliquez pas les choses - je ne fais que suivre les ordres.";
			link.l1 = "Oh, c'est vraiment génial...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Capitaine...";
			link.l1 = "Charlie, si nous fuyons maintenant, la prime sur nos têtes sera encore plus élevée. Et nous ne pouvons pas nous frayer un chemin à travers ça ? Je vais essayer de te sortir de là, ne fais juste rien de stupide !";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Arrêtez de faire du bruit et de menacer cet homme immédiatement, monsieur. Rendez vos armes et suivez-moi sur-le-champ !";
			link.l1 = "Je n'ai menacé personne, il y a eu une erreur. C'est une affaire commerciale, pas une tentative de meurtre.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Ça n'en a pas l'air pour moi. Vous devrez répondre devant la loi.";
			link.l1 = "Et si je m'excuse et m'en vais ?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "Alors tu peux te faufiler et finir ce que j'ai interrompu ? Tu me prends pour un idiot ?";
			link.l1 = "Tu dois l'etre si tu ne veux pas regler cela pacifiquement. Dieu sait, je ne voulais pas en arriver la...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "Tu l'as tué !..";
			link.l1 = "Considérez cela fait de vos propres mains, monsieur. Vous auriez pu simplement répondre à mes questions au lieu d'être hystérique. Je jure, un cri de plus et je vous fais sauter la cervelle.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Oui, je l'ai tué. Il m'y a forcé. Mais tu n'es pas aussi stupide que lui et tu ne suivras pas son exemple, n'est-ce pas ?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "Que veux-tu ?!";
			link.l1 = "Il y a quelque temps, Charlie Knippel vous a emprunté de l'argent. Son ami a promis de rembourser sa dette mais ne l'a apparemment pas fait. J'exige que vous arrêtiez immédiatement d'envoyer des mercenaires après nous. Je suis prêt à payer la dette de Charlie sur-le-champ si je le peux.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "Que veux-tu?!";
			link.l1 = "Il y a quelque temps, Charlie Knippel vous a emprunté de l'argent. Son ami a promis de rembourser sa dette mais apparemment ne l'a pas fait. J'exige que vous arrêtiez immédiatement d'envoyer des mercenaires après nous. Je suis prêt à rembourser la dette de Charlie dès maintenant si je peux me le permettre.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! I would never do that to him; he's a good, honest man. Besides, his debt has long been paid off. Mr. Fleetwood, the captain of the Valkyrie, settled it to the last peso.";
			link.l1 = "Vraiment ? Je sais qui c'est. Vous auriez dû le dire tout de suite. Désolé pour le dérangement, au revoir.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Juste comme ça ?! Tu m'as menacé ! Et tu as tué un homme !..";
			link.l1 = "As-tu oublié ce que j'ai dit ? Un cri de plus et tu le rejoindras. Adieu.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Encore là et pas encore pendu ? Eh bien, salutations du Sussex, Charlie.";
			link.l1 = "Salutations à vous, qui que vous soyez.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Ah, Charles de Maure. C'est bien aimable de ta part de rendre visite au pauvre Charlie. Nous comptions là-dessus.";
			link.l1 = "Qui sommes-nous ?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Peu importe. Vous nous avez coûté un temps et de l'argent considérables, M. de Maure. Je pense qu'ils ne verront pas d'inconvénient si je m'occupe de Charlie et de vous ici même.";
			link.l1 = "Eh bien, puisque nous sommes de toute façon déjà morts, pourriez-vous, par bonté de cœur, nous dire qui nous avons tant contrarié ? Nous promettons de ne pas recommencer. Et qui est Sussex ?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Impossible. Le devoir m'appelle et, contrairement à toi, je suis un homme d'action, pas de paroles.";
			link.l1 = "Bon sang, quelqu'un va-t-il jamais m'expliquer ce qui se passe ?!";
			link.l1.go = "DTSG_Killer_5";
		break;
		
		case "DTSG_Killer_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			
			for (i=1; i<=12; i++)
			{
				if (GetCharacterIndex("SentJonsPrisoner_"+i) != -1)
				{
					sld = CharacterFromID("SentJonsPrisoner_"+i);
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = GetCharacter(i);
				if (sld.city == "sentjons" && sld.location == "SentJons_prison")
				{
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			sld = CharacterFromID("SentJonsJailOff");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SentJonsJailOff", "off_eng_1", "man", "man", 30, PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto18");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(15)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto22");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			for (i=4; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(15)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			/*sld = CharacterFromID("SentJons_Mayor");
			LAi_group_Attack(sld, Pchar);*/
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_TurmaDayPobeda");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Eh bien, je serai damné, Capitaine, quel massacre vous avez fait ici !";
			link.l1 = "Vous objectez ? Préférez-vous la potence ? Ou peut-être pourrir ici indéfiniment ?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "Non, monsieur. Merci de m'avoir sauvé. Pour être honnête, je suis surpris que vous soyez venu, étant donné la facilité avec laquelle vous m'avez laissé être capturé. Et surpris de la facilité avec laquelle vous vous êtes occupé du garde - c'était un Renard des Mers. Un marine.";
			link.l1 = "Je t'avais dit que je te sortirais de là, tu n'aurais pas dû douter. Maintenant, sors de cette cellule avant que toute la garnison ne débarque.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Oui oui, Capitaine.";
			link.l1 = "";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "Merde, monsieur, j'ai du mal à y croire...";
			link.l1 = "Au fait, dis-moi, de quoi t'accuse-t-on? Et qui est Sussex?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Je ne sais pas, monsieur. Je n'ai aucune idée de qui ils voulaient parler par là...";
			link.l1 = "Très bien, nous découvrirons plus tard. Maintenant, nous devons sortir d'ici.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Quelles sont vos prochaines étapes, monsieur ? Tabasser cet escroc en plein jour est une affaire risquée.";
			link.l1 = "Tu viens de me donner une idée. Pourquoi lui faire entendre raison en plein jour alors qu'on peut le faire maintenant, à la faveur de la nuit ?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Diable m'emporte, c'est une idée brillante, Capitaine!";
			link.l1 = "Exactement. Dis-moi, Charlie, tu as vécu ici un moment. Sais-tu où vit l'usurier ?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Je le savais autrefois, monsieur, mais la dernière fois que j'étais ici, il vendait sa maison. Aucune idée d'où est la nouvelle.";
			link.l1 = "Eh bien, c'est un problème...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Je suis sûr que tu trouveras une solution, Capitaine, après tout, tu as vaincu le grand et effrayant Lucas Rodenburg !";
			link.l2 = "D'accord, je m'en occuperai. Mais, si tu savais où se trouve la maison de l'usurier, ce serait mieux !";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "Je l'ai fait. Mais le matin est plus sage que le soir, Charlie. Reposons-nous du voyage et allons-y en plein jour - nous ne sommes pas ici pour assassiner l'homme après tout.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "En es-tu sûr, monsieur ? Nous perdrons l'effet de surprise.";
			link.l1 = "Je suis sûr et je suis fatigué. De plus, je veux juste parler. Lui faire peur un peu si nécessaire.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "Ce que je ne sais pas - je ne sais pas, désolé, monsieur.";
			link.l1 = "Ah, tant pis, cherchons-le.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Pensez-vous ce que je pense, monsieur ?";
			link.l1 = "J'ai bien peur que oui, Charlie. Il n'y a pas d'autre capitaine célèbre avec ce nom dans les Caraïbes. Et Richard est bien allé à Londres. Donc, il est peu probable que ce soit une coïncidence.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Terrible... Bien que j'aie dit beaucoup de mots durs à son sujet, je ne lui ai jamais souhaité une telle chose ! Et pauvre Abi !.. Elle attendait un enfant. J'espère qu'elle est en vie...";
			link.l1 = "En effet, je ne le souhaiterais à personne. Espérons qu'Abi va bien. Une idée de qui pourrait faire ça à Dick ? Des ennemis puissants dont il aurait parlé ?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Tu plaisantes, Capitaine. J'ignore ce qu'il en est en Europe, mais ici, chaque Hollandais voulait voir Richard mort.";
			link.l1 = "Vrai. Peut-être que quelqu'un ici a dépensé gros et envoyé des assassins après lui dans le Vieux Monde. Se pourrait-il que ce ne soit pas ce petit prêteur sur gages qui soit derrière les attaques contre vous, mais un ennemi mystérieux de Richard ?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Je ne sais pas, monsieur. Tout est possible à ce stade. Mais cela compliquerait les choses pour nous tous...";
			link.l1 = "Oui, tu as raison, cette possibilité ne me plaît pas non plus.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "Quoi, qui... QUOI?! Que se passe-t-il?.. Qui êtes-vous ?!..";
			link.l1 = "Oh, allez. Si je voulais te tuer, je le ferais dans ton sommeil. Alors ne compliquons pas ou ne raccourcissons pas nos vies. Hoche la tête si tu comprends.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Mm-hmm...";
			link.l1 = "Très bien. Calmez-vous - je ne suis pas ici pour vous voler, vous kidnapper ou vous faire du mal.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Alors... pourquoi es-tu ici? Pourquoi n'as-tu pas pu venir le matin?";
			link.l1 = "Parce qu'une personne riche et influente chasse mon ami. Nous avons des raisons de croire que c'est vous, donc il est probablement dangereux pour lui de se promener dans ces rues en plein jour.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "Mais je ne comprends vraiment pas de quoi vous parlez, monsieur...";
			link.l1 = "Charlie Knippel. Tout le monde en ville le connaît. Réfléchis bien. Il te doit de l'argent.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Notre vieux Charlie ?? C'est vrai, mais sa dette a été payée il y a longtemps, bien que pas par lui personnellement.";
			link.l1 = "Et qui était ce bienfaiteur ?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "Son capitaine, lord Richard Fleetwood. Si vous ne me croyez pas, je peux vous montrer mes registres.";
			link.l1 = "Fleetwood, dites-vous? Alors je vous crois. Donc, vous n'avez pas envoyé de mercenaires après Charlie?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Bien sûr que non, pourquoi ferais-je cela ?? Et dis-moi, quel sens cela aurait-il ?";
			link.l1 = "En effet. Eh bien, désolé pour la visite tardive. Bonne nuit.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "Quoi, Charlie, tu espérais te cacher avec ton ancien patron ce soir ? Il n'est pas là. Mais tu le rencontreras bientôt. Salutations de la part du Sussex.";
			link.l1 = "Nous le savions déjà. Et qui est Sussex ? Et qui êtes-vous ?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "Ce n'est pas votre affaire, M. de Maure. Dommage que vous soyez impliqué dans ce pétrin plus que nous le souhaiterions. Vous êtes une nuisance.";
			link.l1 = "Une contrariété pour qui ? Je vous en prie, ne me dites pas que j'ai couché avec la femme d'un Anglais très influent et très en colère.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Très drôle. Trouvé le temps de plaisanter. Apparemment, ce que j'ai entendu sur vous est vrai\nQue voulons-nous? La tête de Charlie suffirait. Mais compte tenu des ennuis que vous nous avez causés, cette fois cela vous concerne aussi - vous continuez à fourrer votre nez là où il ne faut pas.";
			link.l1 = "Je suppose que nous sommes en état d'arrestation ?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Arrestation ? Non, cher monsieur, le temps des demi-mesures est révolu. C'est une exécution, Capitaine de Maure.";
			link.l1 = "D'accord. La seule question est, à qui.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Je ne pensais pas que les Renards de Mer seraient impliqués...";
			link.l1 = "Eh bien, il y a une première fois pour tout. Dis-moi, Charlie, qui est Sussex ?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Je...";
			link.l1 = "Ne vois-tu pas à quel point cela a dégénéré ? Et il semble que nous sommes dans le même bateau, Charlie. J'ai donc le droit de connaître les détails.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Bien sûr, Capitaine. Mais pas ici, n'est-ce pas ? Quittons l'île et parlons sur le navire.";
			link.l1 = "Tu as raison. D'accord, dépêchons-nous.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Vous avez appelé, Capitaine ?";
			link.l1 = "Oui, Charlie. Nous devons parler. Je pense que tu as déjà deviné de quoi il s'agit.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Oui, monsieur...";
			link.l1 = "Bien. Dis-moi pourquoi tes compatriotes, y compris les forces d'élite, te chassent alors que tu n'es pas un criminel ou quoi que ce soit.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Je ne sais vraiment pas, monsieur...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Ce n'est pas une plaisanterie, Charlie. Quiconque te chasse peut donner des ordres aux renards de mer. Il est probablement aussi derrière le meurtre de Richard. Alors si tu as des idées, partage-les. Quel genre de salutations du Sussex, qui est-ce ?";
			}
			else
			{
				link.l1 = "Arrête de détourner le regard, Charlie. Je vois que tu sais quelque chose. En tant que ton capitaine, je t'ordonne de tout me dire. Qui est Sussex ?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "D'accord, Capitaine. Sussex n'est pas une personne. C'est... un navire.";
			link.l1 = "Des salutations d'un navire ? C'est des balivernes.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Permettez-moi d'expliquer. Puis-je m'asseoir, monsieur? L'histoire est longue et peu agréable.";
			link.l1 = "Bien sûr, Charlie. Vas-y.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Hé, Charlie, je viens de la part du capitaine Fleetwood. Il veut te voir.";
			link.l1 = "Merci, mate. Quelque chose est arrivé ? D'habitude, il te transmet tout de suite.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Je ne sais pas. Il dit qu'il veut discuter de cela directement avec vous. C'est votre affaire, débrouillez-vous entre vous.";
			link.l1 = "Oh, j'ai un mauvais pressentiment à ce sujet...";
			link.l1.go = "DTSG_Kurier_3";
		break;
		
		case "DTSG_Kurier_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			PChar.quest.DTSG_KD1.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD1.win_condition.l1.location = "SentJons_houseH1";
			PChar.quest.DTSG_KD1.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD1.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_KD1.win_condition = "DTSG_KD1";
			
			PChar.quest.DTSG_KD2.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD2.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD2.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD2.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_KD2.win_condition = "DTSG_KD2";
			
			pchar.questTemp.Knippel.Soldiers_1 = true;
		break;
		
		case "DTSG_Cortny":
			dialog.text = "... ";
			link.l1 = "Bonne nuit, monsieur !";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Bonne nuit. Laisse-moi passer.";
			link.l1 = "Bien sûr, allez-y, je m'excuse, monsieur.";
			link.l1.go = "DTSG_Cortny_3";
		break;
		
		case "DTSG_Cortny_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			PChar.quest.DTSG_KD4.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD4.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_KD4.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD4.win_condition.l1.locator = "reload2";
			PChar.quest.DTSG_KD4.win_condition = "DTSG_KD4";
			
			sld = CharacterFromID("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Fleetwood";
			sld.greeting = "";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Ah, c'est toi, Charlie. Entre, entre. Ferme la porte derrière toi.";
			link.l1 = "Bonne nuit, Capitaine. Que se passe-t-il ? Et qui était cet homme ? Un paon pompeux...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Ca, je ne peux pas le dire. Et je ne peux pas permettre à quiconque d'entendre notre conversation. N'en parle à personne, compris ?";
			link.l1 = "Oui, monsieur. Est-ce qu'il s'est passé quelque chose ? Vous avez l'air inhabituellement inquiet, ce n'est pas dans vos habitudes.";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Il te semble que c'est le cas. Tu n'as pas l'air au mieux non plus - c'est la nuit, après tout. Mais je crains que ton sommeil soit terminé pour cette nuit, mon ami - nous avons une mission urgente et confidentielle.";
			link.l1 = "Et qu'est-ce que cela impliquera, Capitaine ?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Eliminer un traître. De notre propre camp. Bientôt, un navire diplomatique du Vieux Monde apparaîtra au large de la Dominique - la frégate 'Sussex'. Officiellement, ils doivent négocier une bonne affaire avec les Hollandais. Mais en réalité...";
			link.l1 = "... vont-ils transmettre des informations à nos ennemis, monsieur ?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Encore pire. Défaut complet à leur côté. Et bien qu'ils seront épuisés après avoir traversé l'Atlantique, à la fin, c'est une bonne frégate qui essaiera sûrement de s'échapper si nous attaquons avec un vaisseau lourd\nNous devons donc agir rapidement et avec détermination. Nous ne pouvons compter que sur la 'Valkyrie' - elle est la seule capable d'une telle mission.";
			link.l1 = "Le vieux 'Valkyrie' peut-il tenir tête à une frégate ?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ha-ha, Charlie, doutes-tu de ton capitaine ? De plus, comme je l'ai dit, ils seront épuisés. Si nous attaquons soudainement, tous les avantages sont pour nous.";
			link.l1 = "Jamais de la vie ! Mais j'espère que vous savez ce que vous faites, monsieur...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "J'en suis sûr. Et encore une chose. Ce déserteur occupe une position élevée au Parlement lui-même, tu comprends ? Il peut avoir des yeux et des oreilles partout - pas seulement chez lui, mais déjà ici, dans les Caraïbes. Alors ne mentionne pas le Sussex ou aucun détail de notre mission en ville.";
			link.l1 = "Vous n'aviez pas besoin de me le dire, monsieur. Vous pouvez toujours compter sur le vieux Charlie.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Je sais. C'est juste que les enjeux sont plus élevés que jamais cette fois. Rassemble tes affaires et prépare-toi - nous prenons la mer à l'aube.";
			link.l1 = "Oui, monsieur. Bonne nuit, monsieur.";
			link.l1.go = "DTSG_Fleetwood_9";
		break;
		
		case "DTSG_Fleetwood_9":
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSp3", "");
			
			PChar.quest.DTSG_KD5.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD5.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD5.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD5.win_condition.l1.locator = "houseH1";
			PChar.quest.DTSG_KD5.win_condition = "DTSG_KD5";
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Je n'ai jamais vu Richard comme ça... Il était si inquiet ou même... effrayé ?";
			link.l1 = "Mais pourquoi ? Il ne m'en a même pas parlé. Bon, peu importe. C'est un grand capitaine, donc nous gérerons sûrement cette frégate et son équipage fatigué.";
			link.l1.go = "DTSG_Knippel_SamSoboi_2";
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Knippel_SamSoboi_2":
			DialogExit();
			SetLaunchFrameFormParam("August 17th, 1654"+ NewStr() +", SE of Dominica", "DTSG_ProshloeDominika", 0, 4.0);
			LaunchFrameForm();
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "Le 'Sussex' est à l'horizon, Charlie, prépare-toi.";
			link.l1 = "Toujours prêt, Capitaine.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Très bien. Je compte sur toi et ton tir en chaîne. Essaie de déchiqueter leurs voiles aussi rapidement que possible, ou mieux encore, abats un mât. S'engager dans un combat risqué pour les couler n'a aucun sens, alors je vais essayer de les aborder\nDe plus, nous devons nous assurer que le traître est mort - si nous les coulons, il faudra quand même s'approcher et s'assurer que personne ne survit.";
			link.l1 = "Et tuer tant de compatriotes pour un seul traître...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Hélas. Cela me peine aussi, Charlie. Mais les ordres sont les ordres. Au moins, nous ne faisons pas cela pour le plaisir. Alors finissons-en rapidement.";
			link.l1 = "Oui, monsieur...";
			link.l1.go = "DTSG_Fleetwood_13";
		break;
		
		case "DTSG_Fleetwood_13":
			DialogExit();
			EndQuestMovie();
			AddItems(pchar, "potion4", 10);
			AddItems(pchar, "bullet", 10);
			AddItems(pchar, "GunPowder", 10);
			AddItems(pchar, "grapeshot", 10);
			AddItems(pchar, "cartridge", 10);
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
			PlaySound("interface\MusketFire1.wav");
			PlaySound("interface\MusketFire1.wav");
			
			SetLaunchFrameFormParam("2 hours later..."+ NewStr() +"Boarding the 'Sussex'", "DTSG_ProshloeDominika_11", 0, 4.0);
			LaunchFrameForm();
			
			n = Findlocation("Location_reserve_06");
			DeleteAttribute(&locations[n], "IslandId");
			DeleteAttribute(&locations[n], "type");
			DeleteAttribute(&locations[n], "models");
			DeleteAttribute(&locations[n], "environment");
			DeleteAttribute(&locations[n], "Box1");
			DeleteAttribute(&locations[n], "Box2");
			DeleteAttribute(&locations[n], "Box3");
			Locations[n].id.label = "Orlop deck";
			Locations[n].filespath.models = "locations\decks\oldeck";
			Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
			//Sound
			locations[n].type = "deck_fight";
			//Models
			//Always
			Locations[n].models.always.ODeck = "oldeck";
			Locations[n].models.always.locators = "oldeck_locators";

			//Day
			Locations[n].models.day.charactersPatch = "oldeck_patch";
			Locations[n].models.day.fonar = "oldeck_fday";
			//Night
			Locations[n].models.night.charactersPatch = "oldeck_patch";
			Locations[n].models.night.fonar = "oldeck_fnight";
			//Environment
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
		break;
		
		case "DTSG_Graf_Sheffild_1":
			StartQuestMovie(true, false, true);
			dialog.text = "Assez ! Je suis prêt à rendre mon épée et à discuter de vos exigences. Mais d'abord, présentez-vous ! Qui êtes-vous et comment osez-vous nous attaquer ?! C'est une trahison !";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Capitaine Richard Fleetwood. Et vous devez être le comte Sheffield ? Et vous avez absolument raison, c'est de la trahison.";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "Tu sais qui je suis ? Nom d'un chien ! Je savais que quelque chose comme ça arriverait, des rats partout, alors j'ai demandé, même supplié pour un vaisseau de guerre...";
			link.l1 = " ";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "Ça ne t'aurait pas sauvé, juste prolongé l'inévitable, car je trouverais une autre approche. Et oui, par trahison, je veux dire la tienne, Comte de Sheffield.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Alors vous ne savez rien de moi, monsieur ! Tout le monde sait qu'il n'y a pas d'homme plus loyal à l'Angleterre que moi ! Vous regretterez cette erreur, souvenez-vous de mes paroles.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Je n'ai rien à regretter, car je ne suis pas celui qui fait défection aux Hollandais.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "Quoi ?! Quelles sornettes débites-tu ?! Tu as été égaré, et tu as suivi une fausse piste comme un chien enragé\nAhem, c'est vrai, je me dirige vers des négociations avec la Compagnie néerlandaise des Indes occidentales. Mais dans l'intérêt de notre Angleterre, Capitaine. C'est une terrible erreur, mais nous pouvons encore la corriger.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "J'ai bien peur que cela ne dépende pas de moi. Et certainement pas de vous. Vous avez choisi le mauvais camp, messieurs. Adieu.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Nous avons terminé ici. Je pensais que ce gros homme ne cesserait jamais de piailler. Oh, ces comtes, n'est-ce pas, Charlie ?";
			link.l1 = "Je me demande juste, monsieur, et si le colonel avait tort ? Ou, que Dieu nous en garde, nous avait menti pour se débarrasser du comte ?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Ecoute-moi, mon ami. Et écoute attentivement. Notre service est très dangereux et difficile, dans tous les sens. Tout peut arriver - une triste erreur, une coïncidence ridicule, ou une trahison perfide\nServir le pays, ce n'est pas seulement charger des canons avec des boulets, Charlie. Pour les puissants, c'est prendre des décisions difficiles. Et pour des soldats comme nous - exécuter ces décisions.";
			link.l1 = "Mais que ferons-nous si un jour nous versons le sang d'innocents, Capitaine ? Cela sera sur nos mains, notre conscience.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Alors le sang sera autant sur leurs mains que sur les nôtres, sinon plus. Que cela te réconforte. L'essentiel est que nos intentions étaient pures - éliminer l'ennemi de la patrie\nMaintenant aide-moi, Charlie, il faut encore faire croire à une attaque hollandaise.";
			link.l1 = "Oui, monsieur...";
			link.l1.go = "DTSG_Graf_Sheffild_25";
		break;
		
		case "DTSG_Graf_Sheffild_25":
			DialogExit();
			EndQuestMovie();
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kortni", "off_eng_5", "man", "man", 40, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Lynch";
			sld.rank = 40;
			GiveItem2Character(sld, "blade_16");
			EquipCharacterByItem(sld, "blade_16");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterByItem(sld, "pistol6");
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			LAi_SetHP(sld, 400.0, 400.0);
			FantomMakeCoolSailor(sld, SHIP_HIMERA, "Сhimera", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.Ship.Mode = "war";
			sld.alwaysEnemy = true;
			sld.Coastal_Captain = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("DTSG_KortniAttack");
			Group_SetType("DTSG_KortniAttack", "pirate");
			Group_AddCharacter("DTSG_KortniAttack", "DTSG_Kortni");

			Group_SetGroupCommander("DTSG_KortniAttack", "DTSG_Kortni");
			Group_SetTaskAttack("DTSG_KortniAttack", PLAYER_GROUP);
			Group_SetAddress("DTSG_KortniAttack", "Antigua", "Quest_Ships", "Quest_Ship_10");
			Group_LockTask("DTSG_KortniAttack");
			
			SetLaunchFrameFormParam("Present time", "DTSG_SegodnyaVremya", 0, 4.0);
			LaunchFrameForm();
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Alors, nous avons laissé de fausses preuves pour faire croire que les Hollandais étaient responsables. Richard et moi n'avons jamais reparlé de ce jour.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Eh bien, beaucoup de choses prennent sens maintenant. Je pense qu'un parent ou un partisan du comte est derrière la mort de Richard. Mais pourquoi vous viser ? Vous n'êtes qu'un canonnier et vous n'avez pris aucune décision ce jour funeste.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "En effet. C'est une sale affaire et ça pue. Peut-être que quelqu'un l'a découvert et a décidé de venger le Comte. Mais un seul canonnier vaut-il de telles dépenses ? De l'argent, des mercenaires, employer les Renards des Mers... Impossible, Charlie.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Peut-être que cette personne traque tout l'équipage de l'ancien navire de Richard. Qu'en pensez-vous, monsieur?";
			link.l1 = "Je pense que nous devrions nous éloigner d’Antigua, et le plus tôt sera le mieux.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Je me suis posé cette question aussi, Capitaine, mais je n'ai pas trouvé de réponse.";
			link.l1 = "Merde. Quelqu'un arrive. J'ai dit de ne pas me déranger !";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Helena_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Tichingitu_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Alonso", "citiz_36", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
				sld.name 	= "Alonso";
				sld.lastname = "";
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Alonso_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.location = "None";
			}
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles !..";
				link.l1 = "Qu'est-ce qui ne va pas, Helen ??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, je me souviens que tu m'as demandé de ne laisser entrer personne et de ne pas te déranger avec Charlie, mais...";
				link.l1 = "... tu as décidé de venir toi-même. D'accord, c'est bon, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Un navire de guerre anglais ! On l'a repéré il y a quelque temps. Au début, je n'y ai pas prêté attention, mais elle nous atteindra d'une minute à l'autre ! Je n'ai jamais vu un navire aussi rapide.";
				link.l1 = "Alors merci de m'avoir prévenu. J'espère que nous aurons le temps de nous préparer avant qu'elle ne s'approche. Helen, Charlie, à vos postes de combat !";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... vous pouvez continuer votre réunion secrète plus tard. Un vaisseau de guerre anglais se dirige vers nous. Je pensais que c'était important.";
				link.l1 = "Eh bien, je vais aller jeter un oeil. Merci, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Capitaine, un navire rapide vient vers nous. Très rapide. Les esprits me murmurent que leurs intentions sont maléfiques.";
			link.l1 = "Merci à vous et aux esprits pour l'avertissement. Préparez-vous au combat, juste au cas où. Et transmettez ce message aux autres de ma part.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Excusez-moi, pour l'interruption, Capitaine, mais c'est urgent.";
			link.l1 = " Oh, j'espère que c'est vraiment important, Alonso. Rapport.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "Un navire anglais approche. C'est... le 'Mirage', Capitaine.";
			link.l1 = "Quoi ? En es-tu absolument sûr ? Tu as encore bu, hein ?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Je suis sûr, Capitaine - il n'y a pas d'autre navire comme celui-ci dans les Caraïbes, vous le savez.";
			link.l1 = "En effet. Je vais aller jeter un œil moi-même - voyons si ce 'Mirage' est réel.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Oh... Mais ce n'est pas encore fini ! Brian, te voilà ! Où diable étais-tu ?";
			link.l1 = " Cela ne fera que retarder l'inévitable.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. Penser jusqu'où tu es arrivé. Dommage. J'espérais te prendre au dépourvu sur ce navire.";
			link.l1 = "Vous savez qui je suis ? Alors, c'est vous derrière nos récents ennuis - on dirait un oiseau de haute volée forcé de quitter son nid douillet et de sortir personnellement au lieu d'envoyer un autre vautour.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Correct, sur les deux points. Je suppose qu'un noble peut reconnaître un autre de loin. Colonel Thomas Lynch. Il semble qu'il soit temps de parler comme des gentilshommes, plutôt que d'essayer de nous détruire mutuellement. Peut-être pouvons-nous parvenir à un accord mutuellement bénéfique.";
			link.l1 = "Je ne peux rien promettre, mais je vous donne ma parole de gentilhomme qu'au moins nous parlerons comme des gens civilisés, Colonel.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Très bien. Je n'aurais pas pu avoir une telle conversation avec Fleetwood. Pourtant, nous avons trouvé un levier contre lui, et il ne nous causera plus de soucis. Dommage que cela n'ait pas fonctionné avec vous, mais peu importe.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Tout les Caraïbes parlent de la mort de Richard. Alors, c'était toi ! Et je suppose que la pression dont tu parlais, c'était Abigail? Que lui est-il arrivé, d'ailleurs ?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Pas une menace, tu dis?.. Alors, tu l'as tué? Es-tu un partisan du comte?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail ? Ah, la jeune Juive, sa fiancée. Encore une fois, vous vous êtes avéré être une personne fort perspicace. Elle est vivante et en bonne santé - nous avons promis et tenu parole en échange de la coopération de Fleetwood.";
				link.l1 = "Quelle collaboration, je dois dire. Mais pourquoi l'as-tu fait ? Es-tu un partisan du comte ?";
			}
			else
			{
				dialog.text = "Soutenir ? Oh, bien au contraire. Mais voyez-vous, certaines cartes ne peuvent plus être jouées lorsqu'elles deviennent un fardeau pour le joueur. Malheureusement, Richard est devenu l'une d'elles.";
				link.l1 = "Je vois. Vous éliminez tous les témoins. Qu'est-il arrivé à Abigail ? L'avez-vous tuée aussi ?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Pas du tout. Au contraire. Mais Richard en savait trop, et en retournant dans l'Ancien Monde, il est devenu dangereux. Il aurait dû rester ici, et nous n'aurions pas pris sa vie.";
				link.l1 = "Eliminez-vous tous ceux qui ont jamais travaillé pour vous, Colonel ?";
			}
			else
			{
				dialog.text = "Qui ? Ah, sa fiancée, je suppose. Elle était le moyen de pression. Sa vie contre la sienne. Elle va bien, je le jure sur mon honneur.";
				link.l1 = "Je doute que vous sachiez ce qu'est l'honneur, vu ce que vous avez fait, Colonel.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Je ne répondrai pas à cette provocation, monsieur.";
				link.l1 = "Alors réponds à ceci - comment as-tu obtenu ce navire ? Est-ce... le 'Mirage' ?";
			}
			else
			{
				dialog.text = "Je passerai outre cet affront parce qu'il vient de quelqu'un qui n'a jamais eu à exercer le pouvoir et influencer l'ordre des choses.";
				link.l1 = "En parlant de choses, où as-tu trouvé le 'Mirage' ? C'est elle ?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Pas exactement. Un navire magnifique, n'est-ce pas? Dommage qu'il n'ait pas rempli son but contre vous. Connaissez-vous l'histoire de ce navire, Capitaine de Maure?";
			link.l1 = "Tu parles du navire fantôme et de la chasse aux marchands anglais ?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "Ça ? Oh, non. Je ne parle pas de choses bien connues. Je veux dire des choses qui sont cachées à la vue. Ce ketch a été conçu par Johan van Merden et Lucas Rodenburg\nCe doux couple a créé une chaîne de stratagèmes, et le navire a finalement été lancé depuis le chantier naval de La Havane. Nous avons eu la chance de mettre la main sur les plans originaux. Et au final, nous avons recréé le Mirage dans toute sa splendeur et même l'avons améliorée, corrigeant certains défauts de sa conception.";
			link.l1 = "Quel dommage, comme vous l'avez vous-même remarqué, cela ne vous a pas beaucoup aidé, Colonel.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Es-tu d'humeur à rire? N'y pense même pas. J'admets que tu m'as surpassé à la fois comme capitaine et comme combattant. Mais j'ai encore le dessus ici.";
			link.l1 = "Est-ce une ruse de mourant? Ou juste la confiance excessive habituelle des gens comme toi? Que se cache-t-il derrière ces mots?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Excellente question. Il me semble que vous êtes plus qu'un débauché et un duelliste, comme mes recherches le suggéraient. J'ai pris des mesures pour tous les résultats de cette rencontre. Même celui où je meurs de votre lame, de votre balle, ou d'un boulet de canon égaré. Si je meurs aujourd'hui, vous et Charlie regretterez de ne pas avoir rejoint Fleetwood.";
			link.l1 = "Encore des chasseurs de primes ? S'il te plaît. C'était désagréable et fastidieux, mais pas mortel. Nous les avons repoussés alors - nous les repousserons à nouveau.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Je n'ai aucun doute. Maintenant je vois le duelliste insouciant parler à nouveau. Pas seulement des chasseurs de primes. Toute la force des Renards des Mers et l'intelligence navale anglaise s'abattra sur ta tête comme une vague de tempête sur le bateau d'un pêcheur.";
			link.l1 = "Que veux-tu de moi ? Tu ne t'attends pas à ce que je me rende ?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Bien sûr que non. Nous vous avons bien étudié pendant tout ce temps. Je veux vous proposer un accord mutuellement bénéfique. Un que ce serait imprudent de refuser. Et en tant que deux gentilshommes, j'espère que nous pourrons parvenir à un accord.";
			link.l1 = "Alors je répète la question, Colonel, que voulez-vous? Je suppose Charlie?.. Et vous pensez pouvoir m'offrir quelque chose en retour? Je ne trahirai pas pour quelques pièces d'or.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Exactement. Ce n'est pas juste une question de quelques pièces d'or, comme vous le dites, mais d'une montagne entière - 10,000 doublons. Le dépôt vous attendra chez le banquier à Port Royal si nous parvenons à un accord\nMais la chose la plus importante que j'offre, c'est votre vie, Capitaine de Maure. Vous m'avez bien entendu. Nous cesserons toute poursuite si nous déposons tous les armes maintenant, et que vous nous remettez Charlie\nAvez-vous entendu l'expression 'un homme contre la société'? Dans votre cas, si vous refusez, ce sera 'un homme contre l'état'. Décidez, Charles. Ici et maintenant.";
			link.l1 = "Tu peux facilement utiliser ton titre et ton influence pour intimider un imbécile ou deux. Mais je ne suis pas un imbécile. Et je sens le désespoir à un mile de distance. Dégage. Et sois heureux que je ne t'ai pas tué - tu le mérites plus que bien.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Vous n'avez pas vraiment besoin de Charlie, Colonel. Vous avez besoin de son silence.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "J'accepte cela pour la sécurité de moi-même et de mes hommes, pas par cupidité pour votre argent, juste pour que vous le sachiez.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Vous avez pris l'une des pires décisions de votre vie, Capitaine de Maure. Je ne vous envie pas. Honnêtement. Vous n'aurez à vous en prendre qu'à vous-même - personne ne vous fera d'offres similaires à nouveau. Surtout pas moi. Adieu.";
			link.l1 = "Attendez, Colonel.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "Quoi, tu as changé d'avis ? Mes paroles ont enfin eu un effet ?";
			link.l1 = "Exactement, tout le contraire.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "Que veux-tu dire? Explique-toi.";
			link.l1 = "Tes paroles n'ont fait que renforcer ma détermination contre toi. Ne fais pas cette tête - je ne te tuerai pas. Et comme je l'ai dit, je te laisserai même partir. Mais je pense que tu te débrouilleras sans bateau.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Je n'en ai pas besoin, car j'ai un navire.";
			link.l1 = "Tu as raison. Mais seulement à propos de ne pas en avoir besoin. Tu es peut-être un homme influent. Mais tu manques de mesure. Et de tact. Je ferai ce que tu as l'habitude de faire - être maître de la situation.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Vous ne l'êtes pas, Capitaine de Maure. Ne vous trompez pas.";
			link.l1 = "Entièrement ? Peut-être pas. Mais toi non plus - ta vie est maintenant entre mes mains, Colonel. Peu importe ce qui m'arrive plus tard - maintenant je peux faire ce que je veux. Et moi... je prends ce navire. Vous êtes libre. La côte n'est pas loin.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Tu n'oserais pas. Mais à en juger par ton regard... Savoure ta petite victoire. Tu as fait...";
			link.l1 = "Oui, oui, une des pires décisions de ma vie. Je l'ai déjà entendu. Hors de ce navire. Mon navire. Vas-tu sauter toi-même, ou devrions-nous te jeter par-dessus bord ?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
			npchar.lifeday = 0;
			npchar.location = "None";
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Je n'aurais jamais cru le voir ainsi - humilié, sautant par la fenêtre, et nageant jusqu'au rivage à quatre pattes.";
			link.l1 = "Tu as eu un aperçu? Satisfait? Merveilleux. À ton tour.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "What are you saying, sir? We're not enemies; I was just following orders!.. Can I at least ask for a boat? You'll never see me again!";
			link.l1 = "Tu ne m'épargnerais pas si tu étais à ma place et venais de perdre une bataille contre moi. Alors sois heureux que je ne t'aie pas tué. Par la fenêtre. Maintenant. Peut-être que tu rattraperas ton mécène.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Je préférerais mourir que de subir une telle humiliation, monsieur !";
			link.l1 = "Comme tu veux.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "C'était le Colonel, n'est-ce pas, Capitaine ?";
			link.l1 = "Bien. Regarde par la fenêtre, Charlie, tu ne le regretteras pas.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "Le Colonel?.. Je n'aurais jamais imaginé voir une chose pareille, monsieur. Que quelqu'un ose jeter un homme avec un tel titre par-dessus bord comme un vulgaire matelot! Richard ne ferait jamais cela - le respect des rangs faisait partie intégrante de lui.";
			link.l1 = "Ca lui a été enfoncé dans la tête au fil de nombreuses années d'exercices. C'est un homme militaire, avec l'état d'esprit correspondant. Moi, je ne le suis pas, et je pense plus largement, sans ces... restrictions.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "Et nous n'aurons pas d'ennuis pour lui avoir fait ça ?";
			link.l1 = "Heh, tu blâmes Richard, mais tu penses comme lui. Nous avons osé résister, alors nous serons traqués pendant un temps. Mais tôt ou tard, même la marine anglaise nous laissera tranquilles. Et pour Lynch, cela deviendra une affaire personnelle. Mais nous avons fait en sorte qu'il n'aura pas de ressources d'État derrière lui la prochaine fois.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Vous savez, Capitaine, à partir de ce jour, je vous respecte encore plus. Je ne regretterai jamais de ne pas être parti avec Dick sur le Valkyrie et d'avoir décidé de vous rejoindre.";
			link.l1 = "Merci, mon ami ! Sois prêt - la tempête se lève sur nous. Mais tu sais quoi ? Quelque chose me dit que nous sortirons à nouveau victorieux. Allons-y, il est temps de retourner sur le pont.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "Ce n'est pas tout à fait vrai, bien que personnellement, je me fiche de Charlie s'il garde la bouche fermée à partir de maintenant. Mais mes collègues aimeraient voir son corps. Et ils savent à quoi il ressemble\nC'est la vie réelle, Charles, pas un conte de fées pour enfants ou un poème chevaleresque que nos nourrices nous lisaient dans l'enfance, et je ne vois aucune solution qui satisfasse tout le monde.";
			link.l1 = "Mais moi, oui. Tu peux toujours trouver un corps similaire. Et acheter des vêtements similaires. Graisser quelques pattes. Et je parlerai à Charlie. Et je te donne ma parole en garantie.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				dialog.text = "C'est... un grand risque. Et ce n'est pas seulement une question de savoir si je peux faire confiance à ta parole. Mais si mes collègues me croiront quand ils verront un corps ressemblant à celui de Charlie. Et je ne prendrai pas ce risque... comme ça.";
				link.l1 = "Combien?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				dialog.text = "La parole d'un homme avec votre réputation ? Vous plaisantez. La naissance noble à elle seule ne suffit pas pour la confiance.";
				link.l1 = "Entendre cela d'un autre homme de naissance et d'actions similaires, pardonnez-moi, Colonel.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Tu as raison, bien sûr. Mais dans ce cas, il s'agit de ma confiance, pas de celle de quelqu'un d'autre. Et toi comme garant, tu ne me conviens pas\nJe te le dis une dernière fois. Donne-moi Charlie. Si, bien sûr, tu ne veux pas partager le sort de Fleetwood.";
			link.l1 = "Vous pouvez facilement utiliser votre titre et votre influence pour intimider un imbécile ou deux. Mais je ne suis pas un imbécile. Et je sens le désespoir à un kilomètre. Sortez. Et soyez heureux que je ne vous aie pas tué - vous le méritez amplement.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Enfin, droit au but. Un million de pesos. Offre finale.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Je te paierai l'argent. Ne pense pas que je suis pauvre ou que je ne valorise pas la vie de mes hommes. Ni l'un ni l'autre n'est vrai. Prends-le.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " Tu as bon appétit, bien que je ne m'attendais pas à moins. Mais en ce moment, je n'en ai pas autant, et...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Pas d'argent - pas d'affaire. Pensiez-vous que je ferais preuve de clémence ? Ai-je l'air d'un saint, monsieur ?";
			link.l1 = "Mais peut-être pourriez-vous attendre un peu ? Où et quand serait-il commode pour vous de nous revoir ? Je pourrais emprunter les doublons à un prêteur sur gages.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "Alors tu penses que je suis encore plus naïve que je ne le pensais\nJe ne suis pas une fille de la campagne prête à attendre éternellement quelqu'un qui a déjà obtenu ce qu'il voulait d'elle\nPas d'argent ? Je ne l'ai pas demandé de toute façon. Je veux seulement Charlie. Vous ne me servez à rien malgré tous les ennuis que vous avez causés.";
			link.l1 = "Tu peux facilement utiliser ton titre et ton influence pour intimider un ou deux imbéciles. Mais je ne suis pas un imbécile. Et je sens la désespoir à un mille de distance. Sors. Et sois content que je ne t'ai pas tué - tu le mérites plus que largement.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Es-tu vraiment si attaché au pauvre Charlie ? Quoi qu'il en soit, ta noblesse mérite le respect. Assure-toi que ton canonnier soit muet comme une tombe. Sinon, vous finirez tous les deux là-bas.";
			link.l1 = "Je promets. Et tu tiens ta parole et cesses toute poursuite.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Je le promets aussi. Et une chose de plus. Malgré ta victoire honnête, j'emmènerai mon navire avec moi. C'est une pièce sur mesure, tu sais. Et très coûteuse.";
			link.l1 = "Qu'en est-il du droit du vainqueur ? Mais je ne tenterai pas ma chance. Cette fois.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Je suis presque désolé de dire cela, Brian, mais j'ai bien peur que notre coopération s'arrête ici.";
			link.l1 = " ";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Je... suis libre, Colonel? Allez-vous lever la prime sur ma tête, et je pourrai repartir à zéro comme si j'étais un homme respectueux des lois?";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Je dirais que tu as trop vu - tout comme le défunt Fleetwood. Je viens essentiellement de recevoir un pot-de-vin juste devant toi à l'instant.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "Je... je ne dirai rien à personne, je le jure devant Dieu !";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Bien sûr que non, vous ne le ferez pas.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "Non !..";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Ne me regarde pas comme ça, Charles. Si je m'inquiète constamment de savoir si Brian va vendre la mèche, je ne pourrai pas dormir du tout.";
			link.l1 = "Je ne sais même pas si je devrais être surpris par ce que j'ai vu ou non.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Tu ne devrais pas. Je suis engagé. Tout ce que je vous demande, c'est de garder le silence sur ce qui s'est passé. Je vais essayer de trouver un corps similaire, arranger son visage correctement, faire bon usage de l'argent et persuader mes collègues.";
			link.l1 = "Merci, Colonel.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Il n'y a pas encore de raison de me remercier. Il y a toujours un risque qu'ils ne me croient pas, et alors la chasse reprendra. Pour l'instant, adieu, Capitaine de Maure. Je pars sur mon navire. Aucune objection ici - je vous ai déjà rendu, à vous et à Charlie, un grand service.";
			link.l1 = "Eh bien, adieu alors.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_26";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Savais-tu seulement à qui tu parlais, Capitaine ? Un colonel ! Était-ce lui qui a orchestré tout ce bazar ?";
			link.l1 = "Je sais, il s'est présenté. Et tu as raison - il l'était.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "C'est étrange, monsieur, car je l'ai autrefois connu comme le supérieur de Richard. Comment est-ce possible ? Et pourquoi part-il comme si de rien n'était ? Que voulait-il, de toute façon ?";
			link.l1 = "En fait, il n'y a rien d'étrange à cela. Ceux qui exécutent des ordres louches risquent souvent leur vie non pas tant à cause des ennemis, mais à cause de leurs supérieurs. Et il voulait ta tête, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Je ne comprends pas, Capitaine. Pourquoi part-il alors ? A-t-il accepté la défaite ?";
			link.l1 = "Ce n'est pas du tout son genre. J'ai dû lui donner de l'or pesant à peu près autant que ta tête. Peut-être un peu plus que ça. Un million de pesos, pour être exact.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "Et toi... tu lui as payé cette somme énorme? Pour moi?..";
			link.l1 = "Eh bien, pas seulement pour toi. Pour moi aussi. Et pour tous les gars, aussi. Mais oui, Charlie, principalement pour toi. Si nous l'avions tué, nous aurions fait face à des expéditions punitives pour l'éternité ensuite.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "Je... ne peux pas y croire, monsieur. Juste... merci. Je ne pensais pas que Fleetwood ferait cela à votre place.";
			link.l1 = "Vous êtes trop biaisé contre lui après son évasion. Richard voulait juste une vie tranquille et paisible avec Abigail. Je suis désolé que cela n'ait pas marché pour lui. De plus, il a tenu sa parole et a payé votre dette. Heh, moi, Fleetwood - tu as vraiment de la chance avec les capitaines, hein, Charlie ?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "Pas de blague, Capitaine. Alors, tout est fini maintenant ?";
			link.l1 = "Oui, mon très cher ami. Du moins pour l'instant. Le combat est terminé - tu peux dire aux gars de ranger leurs armes. Et qu'ils se préparent à hisser les voiles.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Je m'en fiche de savoir pourquoi tu es d'accord - que ce soit par avidité, peur ou devoir envers tes hommes. L'essentiel, c'est que tu sois d'accord. J'enverrai mon homme à Port Royal avec des instructions pour le banquier.";
			link.l1 = "Très bien. Je ne peux pas croire que ce soit enfin terminé.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "Tu sais quoi, au diable l'argent. On peut toujours en trouver davantage. Il y a autre chose que je veux de toi en échange de Charlie, Colonel.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Oh? Je dois admettre, vous me surprenez, Capitaine de Maure. Et qu'est-ce qui, selon vous, équivaudrait à la tête chauve du vieux canonnier si une montagne d'or ne vous convient pas ?";
			link.l1 = "Tu l'as dit toi-même - un navire magnifique, avec les défauts corrigés. Je suis impatient de l'essayer moi-même. Tu as encore les plans. Mais il n'y a qu'un seul Charlie. De plus, c'est dans ton intérêt de me garder satisfait.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Vous êtes un sacré négociateur. Avez-vous la moindre idée de combien il nous en coûte pour construire ne serait-ce qu'un de ceux-là ?";
				link.l1 = "(Digne de confiance) (Honneur) Je le sais parfaitement bien, c'est pourquoi je demande. Ta main est dans ma gueule jusqu'au coude. Tu peux essayer de tirer sur ce loup. Mais tu perdras la main. Et pas seulement elle.";
			}
			else
			{
				dialog.text = "Je crains que construire l'un de ceux-là coûte bien plus que l'or que nous avons préparé pour vous. Mais tu m'as amusé, Charles. D'une bonne manière.";
				link.l1 = "Cela valait la peine d'essayer.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Je vois que tu sais ce que tu veux et que tu poursuis tes buts dans la vie\nEh bien, d'accord. Le cotre est à toi. Mais oublie l'argent - l'usurier te dira qu'il ne sait rien.";
				link.l1 = "Ça me convient.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Certainement. Ma vie a été une histoire de saisir des opportunités et de me protéger des risques\nAlors amène Charlie ici, et nous nous séparerons en paix. Après cela, tu peux même prendre le dépôt. Mais je pars sur ce navire.";
				link.l1 = "Alors réglons ça.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Je ne peux pas dire que je suis pleinement satisfait. Mais je veux en finir rapidement. Maintenant donne-moi ce que je veux.";
			link.l1 = "Pas 'quoi', mais 'qui'. Mais comme tu veux.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Moi non plus. Je commence à croire que ce n'est pas seulement ce qu'est un homme, mais aussi avec qui il s'entoure - un simple travail de capture d'un vieux canonnier s'est transformé en casse-tête à cause de son capitaine, c'est-à-dire toi, Charles\nAppelle Charlie ici. Ce bazar va finir pour de bon - nous lèverons l'ancre, et nos navires se sépareront.";
			link.l1 = "Partir, tu dis ?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Vous avez l'air surpris ? Vous pensiez que la goélette était votre juste prix ? Nous ne sommes pas des pirates, Capitaine de Maure. Les gens civilisés vivent selon des règles différentes, bien plus complexes. Le navire reste avec moi.";
			link.l1 = "Eh bien alors...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "Tout va bien, monsieur? Est-ce que c'est... le colonel?";
			link.l1 = "Oui, Charlie, c'est le colonel. Tu arrives juste à temps - j'étais sur le point de venir te chercher moi-même.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Me chercher, Capitaine?.. Tout de suite? Pourquoi avez-vous parlé avec cet... homme si longtemps? Je pensais que vous étiez en difficulté, alors je suis venu moi-même.";
			link.l1 = "Correct. Nous sommes toujours en difficulté malgré la victoire. Et nous le serions encore si le colonel et moi n'avions pas trouvé une solution.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Avez-vous réussi à le convaincre de nous laisser tranquilles, monsieur ?";
			link.l1 = "Malheureusement, juste moi. Pas nous. Toi... tu iras avec lui, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "Quoi ?.. Mais pourquoi ?.. Nous avons gagné !";
			link.l1 = "Ne comprends-tu pas ? Nous ne pouvons pas continuer à gagner sans cesse - ils ne s'arrêteront pas tant qu'ils n'auront pas ta tête.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Je ne peux pas croire que tu fais ça au vieux Charlie, Capitaine. Tu es comme Dick. Vous m'avez tous les deux dit un jour que vous étiez mes amis. Et vous m'avez tous les deux abandonné, ainsi que tous ceux qui vous étaient proches.";
			link.l1 = "C'est le fardeau d'un capitaine, sa responsabilité. Je vois que tu ne peux pas comprendre cela car tout ce que tu avais à faire était de charger les canons avec des boulets.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Tu ne comprends pas?.. Peut-être que je ne suis tout simplement pas un traître comme toi ? Tu sais où tu devrais aller ?";
			link.l1 = "En Enfer ? Peut-être que tu as raison. Nous le méritons tous.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "Allez vous faire foutre, monsieur.";
			link.l1 = "... ";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Hilarant. J'ai failli rire. Tu as entendu ça, Brian ?\nParfois, entendre de simples paysans parler, c'est comme une brise légère et pas du tout agaçant. Tu as pris la bonne décision, Charles. Je comprends à quel point c'est dur pour toi. Mais console-toi en sachant que ni toi ni aucun de tes hommes ne souffrira désormais.";
			link.l1 = "J'espère que vous tiendrez cette promesse, Colonel.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Je suis un homme de parole. Le sort d'Abigail en est la preuve. Regarde Brian aussi. Un pirate français, mais il a fait le bon choix quand il était temps de rejoindre le bon camp. Et personne ne le touche tant qu'il nous sert fidèlement. Comme lui, tu avances dans la bonne direction, Capitaine de Maure.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "En parlant de partir. Je veux sortir d'ici dès que possible. Sur ce navire, sans aucun doute rapide, que vous m'avez promis, Colonel.";
			}
			else
			{
				link.l1 = "Je ne suis pas un pirate. Et je n'ai pas l'intention de rejoindre la flotte anglaise pour l'instant. Mais je compte bien réclamer la récompense promise.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "I won't hide it - it feels like tearing her from my heart. I'll have to spend on a new one, but perhaps it's worth it - too long have I been troubled by the thought that Charlie might spill the beans\nIf you don't talk or commit serious crimes against England, consider that we're no longer enemies. Enjoy the new ship; she's indeed beautiful. Goodbye, Charles. Brian - prepare a boat for us. Charlie - follow me as you have no say in the matter.";
				link.l1 = "Adieu.  Vous tous.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "Quel dommage, nous avons toujours besoin de gens capables, peu importe leur nationalité. Mais bien sûr, tu mérites toujours la récompense. Tu peux aller en toute sécurité à Port Royal - j'y arriverai avant tout autre navire sur ce ketch.";
				link.l1 = "J'espère bien. Et j'espère qu'il n'y aura pas d'escorte armée qui m'attend à Port Royal.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Tu doutes encore de ma parole ? Honte à toi. Tu as gagné la gratitude de toute la marine anglaise. Si jamais tu as besoin de quelque chose, ou que tu décides de nous rejoindre, contacte-moi, Capitaine de Maure.";
			link.l1 = "Une fois, j'ai essayé d'obtenir du soutien et des connexions avec les services de renseignement anglais. Ça n'a pas marché. Alors adieu, Colonel.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
