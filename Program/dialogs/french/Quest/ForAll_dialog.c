void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nous n'avons rien à discuter.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoutez, je suis citoyen de cette ville et je vous demande de baisser votre lame.","Ecoute, je suis citoyen de cette ville et je te demanderais de baisser ta lame.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Bien...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, "+GetSexPhrase("copain","fille")+", courant avec une arme. Je peux devenir nerveux...","Je n'aime pas ça quand il y a "+GetSexPhrase("hommes","gens")+" marchant devant moi avec leur arme prête. Ça me fait peur...");
				link.l1 = RandPhraseSimple("Je l'ai.","Je l'ai.");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Allez, camarade, montre-moi tes poches.";
			link.l1 = "Quoi?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Vous m'avez entendu. Vite, moins de mots. Je n'aime pas parler...";
			link.l1 = "Merde ! Et  fait "+pchar.questTemp.different.FackWaitress.Name+" travailler avec vous ?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "Elle le fait, elle le fait... Donne-moi ton fric ou je te viderai les tripes !";
			link.l1 = "Non ! Je vais te vider les tripes !";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Prends mes pièces, salaud ! Mais tu ne t'échapperas pas de celle-là...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Bien sûr, rien à redire. Adieu, camarade. Et souviens-toi, tu n'es pas assez beau pour faire mouiller les serveuses. Sois plus malin la prochaine fois !";
			link.l1 = "Va déjà.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Comme vous le dites...";
			link.l1 = "Que je le fais...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Me voilà ! Me veux-tu, beau gosse ?";
			link.l1 = "Sacrebleu, ça a vite dégénéré...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Ne perdons pas notre temps !";
			link.l1 = "Eh, je ne pourrais pas être plus d'accord !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Bonne journée. Mon nom est "+GetFullName(npchar)+" Je suis un capitaine de "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Acc"))+" '"+npchar.Ship.name+"’."; 
			link.l1 = "Splendide ! Enfin, je vous ai trouvé.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Tu m'as trouvé?!";
			link.l1 = "Oui. Eh bien, j'ai apporté votre journal de bord, que vous avez oublié au bureau du port de "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Bon sang ! Maintenant je vois où je l'avais perdu. Cette perte a presque provoqué une mutinerie sur mon navire...";
			link.l1 = "Tout est bien qui finit bien. Prends ton journal de bord et parlons de mon argent.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Bonne synchronicité, je n'ai pas encore commencé un nouveau, donc je te paierai autant que possible. "+FindRussianMoneyString(sti(npchar.quest.money))+" et accepter quelques pièces de mes bijoux privés.";
				link.l1 = "Bien. Prends-le.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hum, tu sais, j'ai déjà commencé le nouveau journal de bord. Néanmoins, l'ancien garde encore de la valeur pour moi. Donc je te paierai "+FindRussianMoneyString(sti(npchar.quest.money))+" et accepte quelques bijoux de mon trésor privé.";
					link.l1 = "Marché conclu. Prends ton journal de bord.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "J'ai déjà commencé le nouveau journal de bord. Et transféré toutes les notes de l'ancien. Je n'en ai plus besoin, donc il n'y a pas d'argent pour toi.";
					link.l1 = "Super. Donc toute cette poursuite était pour rien.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Merci. Adieu, "+GetSexPhrase("pote","fille")+".";
			link.l1 = "À toi pareillement...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Ha, travaille ton synchronisme la prochaine fois.";
			link.l1 = "Vrai de vrai.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Je te salue sur le pont de mon navire. Pour être honnête, tu m'as foutu une sacrée frousse - je pensais que le Chasseur de Destriers Borgne était à mes trousses...";
				link.l1 = "Non, capitaine, je suis de bonne humeur aujourd'hui. Je suis ici pour vous aider.";
			}
			else
			{
				dialog.text = "Je vous salue sur le pont de mon navire !";
				link.l1 = "Ahoy, cap ! Je te cherchais.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Pourquoi?";
			link.l1 = "Vous avez oublié votre journal de bord chez le maître du port de "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gén")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Merde, alors c'était bien l'endroit ! Cette perte m'a déjà causé un tas d'emmerdes.";
				link.l1 = "Que diriez-vous d'une récompense ?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Merde, maintenant je vois où je l'avais perdu ! Merci, mais tu m'as cherché bien trop longtemps. J'ai déjà commencé le nouveau journal de bord. Néanmoins, les anciennes notes doivent encore être transférées dans le nouveau...";
					link.l1 = "Et combien?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "J'ai déjà commencé le nouveau journal de bord. Et transféré toutes les notes de l'ancien. Je n'en ai plus besoin.";
					link.l1 = "Alors tu n'as pas besoin d'un vieux journal ? Vraiment ?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Je peux te payer "+FindRussianMoneyString(sti(npchar.quest.money))+" et quelques-uns de mes bijoux. C'est tout ce que je peux me permettre.";
			link.l1 = "Très bien alors. Prends ton journal.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Merci encore. Adieu, camarade.";
			link.l1 = "Garde-le.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "C'est certain. Si tu poursuis quelqu'un, alors tu dois être plus rapide.";
			link.l1 = "Ne perdez pas vos journaux de bord pour commencer. Bien.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "Je pensais que nous étions tous installés.";
			link.l1 = "Oui, c'est vrai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Salutations. Que veux-tu?";
			link.l1 = "Ce n'est rien, je voulais juste entendre des nouvelles. As-tu quelque chose à vendre ?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Je n'ai rien à te vendre et je n'ai aucune nouvelle. Au fait, ta présence ici n'est pas souhaitable. Suis-je clair ?";
			link.l1 = "Tu es... Adieu alors, camarade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Je t'ai dit que tu n'avais rien à faire ici !";
			link.l1 = "Je vois...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Pourquoi m'as-tu attaqué?!";
			link.l1 = "Je dois rendre le navire à son propriétaire..";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Quel genre de propriétaire ? Je suis le propriétaire !";
			link.l1 = "Non, tu ne l'es pas. Je ne sais pas qui possede ce navire. Mais il a ete vole et je dois le ramener.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Merde! Mais ce n'est pas encore fini pour moi. Au moins, j'essaierai de te tuer...";
			link.l1 = "Essayer est tout ce que tu peux faire.";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "Salutations, "+GetAddress_Form(NPChar)+". Je vois que vous êtes capitaine de votre propre navire? Mon nom est "+GetFullName(npchar)+" et je veux vous proposer une affaire.";
			link.l1 = RandPhraseSimple("Je suis désolé, mais je dois y aller.","Je suis désolé, mais je n'ai pas le temps de parler avec vous.");
			link.l1.go = "SCQ_exit";
			link.l2 = "Je suis tout ouïe.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "Ecoute alors. "+SelectNB_battleText()+"\nJe ne dispose ni du temps ni de l'occasion pour le trouver. Parce qu'il ne se montre jamais ici. Je suppose que maintenant vous comprenez, vous voyez ce que je vais vous proposer ?";
						link.l1 = LinkRandPhrase("Je suppose que je dois retrouver quelqu'un et vous l'amener ?","Peut-être, trouver ce salaud et vous l'amener ?","Vous voulez que je trouve cet homme et que je l'amène ici ?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "Ecoute alors."+SelectNB_battleText()+"Je n'ai ni le temps ni l'occasion de le trouver. Car, il ne se montre jamais ici. Je suppose, tu le vois maintenant, tu vois ce que je vais te proposer ?";
						link.l1 = LinkRandPhrase("Je suppose que vous voulez que je retrouve quelqu'un et que je vous l'amène ?","Peut-être, trouver ce salaud et vous l'amener ?","Tu veux que je trouve cet homme et que je l'amène ici ?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "Ecoute donc. En fait, "+npchar.quest.text+" sert dans la marine en tant que capitaine. Il ne sait même pas que je suis ici aussi!\nJ'aimerais le rencontrer, mais je n'ai ni le temps ni l'occasion de le trouver...";
					link.l1 = "Je suppose que vous voulez que je trouve ce capitaine et que je lui parle de vous ?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "Pas tout à fait. Trouvez-le, mais il n'est pas nécessaire de l'amener ici. Tuez-le et cela suffira. Coulez-le avec son navire immonde, tirez-lui dessus, poignardez-le avec votre lame - cela m'importe peu, faites juste en sorte que ce salaud cesse d'empoisonner ce monde par sa présence. La récompense sera généreuse.";
			link.l1 = "Ha ! Assez facile. Dis-moi son nom et le nom de son navire.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" de la "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nommé "+npchar.quest.SeekCap.shipName+" . Il est un habitué du port de "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Je te paierai "+FindRussianMoneyString(sti(npchar.quest.money))+" en doublons d'or.";
			link.l1 = "C'est tout ce que j'ai besoin de savoir. Je serai attentif en mer. Et quand je trouverai votre ami, je le rendrai... 'abaissant la voix' ...pas tout à fait vivant.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "Ce n'est pas suffisant pour ce genre de travail.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "Je suis heureux que nous ayons conclu un marché. J'attendrai votre retour.";
			link.l1 = "Où pourrai-je te trouver ? Clarifions cela maintenant, je ne veux pas perdre de temps à te chercher.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "Chaque matin, j'assiste à un service dans l'église locale. Vous pouvez me trouver là-bas chaque jour de 8 à 9 heures du matin.";
			link.l1 = "Marché conclu ! Attendez-vous au résultat bientôt.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "Exactement. Trouvez-le et amenez-le-moi. Vivant. Je veux m'occuper de lui moi-même. Je vous récompenserai généreusement.";
			link.l1 = "Eh bien, je peux essayer de le trouver, mais j'ai besoin de détails.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "Le nom de ce salaud est "+npchar.quest.SeekCap.name+". Il sert à bord de "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nommé "+npchar.quest.SeekCap.shipName+", qui est sous le commandement de "+npchar.quest.SeekCap.capName+" . Le navire peut souvent être vu dans le port de "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Je te paierai pour ce travail "+FindRussianMoneyString(sti(npchar.quest.money))+" en doublons d'or.";
			link.l1 = "Cela suffit pour moi. Je serai attentif en haute mer.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "C'est pas assez pour ce genre de boulot.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "Je suis heureux que nous ayons conclu un accord. J'attendrai ton retour.";
			link.l1 = "Où pourrai-je te trouver ? Clarifions cela maintenant, je ne veux pas perdre de temps à te chercher.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "Chaque matin, j'assiste à un service dans l'église locale. Vous pouvez me trouver là-bas tous les jours de 8 à 9 heures.";
			link.l1 = "D'accord alors ! Attendez-vous au résultat bientôt.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "Exactement ! Trouvez-le et dites-lui que je vis dans cette ville. Je paierai pour vos services.";
			link.l1 = "Eh bien... Je peux essayer. Dis-moi les détails.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "Son nom est "+npchar.quest.SeekCap.capName+". Et il sert sur "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"'. Il visite souvent "+XI_ConvertString("Colony"+npchar.quest.Qcity)+" Je vous paierai pour ce travail "+FindRussianMoneyString(sti(npchar.quest.money))+" en doublons d'or.";
			link.l1 = "Marché conclu ! Je suppose que je trouverai votre ami assez tôt.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "Ce n'est pas assez pour moi.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "Je suis ravi que nous ayons conclu un accord. J'attendrai votre retour.";
			link.l1 = "Où pourrai-je te trouver ? Clarifions cela maintenant, je ne veux pas perdre de temps à te chercher.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "Je participe toujours au service du soir dans l'église locale. Vous pouvez m'y trouver tous les jours de 18 à 20 heures.";
			link.l1 = "Marché conclu ! Attendez-vous au résultat bientôt.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "Et? Que voulez-vous, monsieur?";
			link.l1 = "Es-tu capitaine "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "Oui, c'est moi. Qu'est-ce qu'il y a ?";
			link.l1 = "Un homme a un très grand intérêt pour vous, il s'appelle "+GetFullName(&characters[GetCharacterIndex("QueteCitoy_"+npchar.quest.cribCity)])+" . Vous vous souvenez ?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "J'ai entendu dire que tu avais beaucoup d'acajou dans ta cale. Je veux l'acheter. Me le vendras-tu ?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "C'est la première fois que j'entends ce nom. Vous vous êtes trompé d'une certaine manière, capitaine. Avons-nous terminé ?";
			link.l1 = "Hm. Bien, pardonne-moi...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "Oh vraiment? Mais il se souvient de vous très bien. Il a mentionné votre dette envers lui...";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "Quelle dette ? De quoi parlez-vous ?";
			link.l1 = "La dette d'honneur !";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "Vous vous trompez. Je ne commerce pas de bois. En avons-nous terminé ?";
			link.l1 = "Hm. Bien, excusez-moi...";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "Et? Que voulez-vous, monsieur?";
			link.l1 = "Es-tu capitaine "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Oui, c'est moi. Quel est le marché ?";
			link.l1 = "Y a-t-il un homme nommé "+sld.quest.SeekCap.name+" servir sous votre commandement ?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Oui. Il est l'un de mes officiers. Maintenant, dites-moi pourquoi vous demandez ?";
			link.l1 = "Bien sûr, je vais te le dire. Je cherche cet homme sur ordre des autorités de "+XI_ConvertString("Colony"+sld.city+"Gen")+", et j'ai le pouvoir de l'arrêter et de le livrer à "+XI_ConvertString("Colony"+sld.city)+"Je vous demande de m'aider dans cette affaire afin que nous puissions la régler pacifiquement.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "Vraiment? Et un tel homme sert dans mon équipage? Tu es sérieux?";
				link.l1 = "Ne t'embête pas avec ça, "+GetAddress_FormToNPC(NPChar)+"Je vais envoyer une chaloupe à votre navire et nous le prendrons nous-mêmes.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "Sans blague. Vous savez quoi, monsieur, je m'en moque éperdument de son passé. Cela ne me concerne pas. Et qui êtes-vous d'ailleurs ? Les autorités ? Vraiment ? Ha ! Je ne livre pas mes hommes à vous ni à quiconque d'autre. Cette conversation est terminée. Allez-vous en !";
				link.l1 = "Mauvais choix... Un choix terrible !";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "Fais ce que tu dois faire.";
			link.l1 = "Je m'en occupe.";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "Avons-nous terminé, capitaine ?";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "Bonne journée. Que voulez-vous, capitaine ?";
			link.l1 = "Vous êtes capitaine "+GetFullName(npchar)+", ai-je raison ?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "Tu as raison. As-tu quelque chose pour moi ?";
			link.l1 = "J'ai. Un homme nommé "+GetFullName(sld)+" te cherche. Il veut que tu lui rendes visite dès que possible. Il habite à "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "Ha ! Alors, il a aussi déménagé dans le Nouveau Monde ? Je devrais vraiment lui rendre visite... Merci pour l'information, monsieur !";
			link.l1 = "Je vous en prie. Mon travail sera payé par votre ami. Bonne chance, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "C'était un plaisir, "+GetAddress_Form(NPChar)+" !";
			link.l1 = "Le plaisir était pour moi, capitaine.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "Holà, "+GetAddress_Form(NPChar)+" . Que veux-tu?";
			link.l1 = "J'ai entendu dire que vous avez beaucoup de bois de séquoia dans votre cargaison et je veux l'acheter. Voulez-vous le vendre ?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "Vous vous trompez. Je ne fais aucun commerce de bois et votre visite ici me semble fort suspecte. Je pense que vous feriez mieux de quitter mon navire !";
			link.l1 = "Très bien, je demandais juste. Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "Voulez-vous des ennuis, monsieur ? Dois-je me répéter ?";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Pourquoi as-tu attaqué mon navire, scélérat ?";
			link.l1 = "Je suis ici pour vous transmettre les meilleures salutations de "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" , de l'homme nommé "+GetFullName(&characters[GetCharacterIndex("QueteCitoyen_"+npchar.quest.cribCity)])+". J'espere que vous comprenez la situation maintenant.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "Impossible ! Rien à perdre pour moi alors...";
			link.l1 = "Que dirais-tu de ta vie ?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "Pourquoi as-tu attaqué mon navire, vaurien ?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "Tu as des idées ? Je t'ai demandé de me donner ton officier paisiblement. Maintenant, je prends lui, toi et ta barcasse !";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "Il y a un vaurien sous votre commandement. Son nom est "+sld.quest.SeekCap.name+". Autorités de "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" sont vraiment impatients de le voir. Il sera arrêté et mis dans ma cale.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "Et c'est pour cela que tu as commis un massacre sur mon navire ? Salaud ! J'ai encore un peu de force... Je vais te tuer !";
			link.l1 = "Des hommes plus forts ont essayé...";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "Que dites-vous, capitaine ?  Avez-vous fait des progrès avec mon affaire ?";
			link.l1 = "Pas encore. Mais je m'en occupe.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "Que dis-tu, capitaine ? As-tu fait des progrès avec mon affaire ?";
					link.l1 = "Je le fais. Et tu vas aimer ça."+npchar.quest.SeekCap.capName+" est mort et son "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" est au fond de la mer.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "Que dites-vous, capitaine ? Avez-vous fait des progrès avec mon affaire ?";
					link.l1 = "Je le fais. Et tu vas aimer ça."+npchar.quest.SeekCap.Name+" est assis dans la cabine de mon navire en état d'arrestation.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "Ah, te voilà. Je suis heureux de te voir. J'ai été informé que tu as réussi dans ta mission !";
					link.l1 = "A ton ami t'a-t-il rendu visite ?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "Splendide ! Je savais que je pouvais compter sur vous. Tenez, prenez votre or. Vous l'avez mérité.";
			link.l1 = "Merci. Parle-moi à nouveau si tu rencontres un autre ennemi.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "Splendide ! Je vais ordonner à mes hommes de le retirer de votre navire immédiatement. Il ne s'échappera pas maintenant ! Voici, prenez votre or. Vous l'avez bien mérité.";
			link.l1 = "Merci. Adressez-vous à moi à tout moment pour un travail de ce genre.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "Oui, il était ici et m'a parlé de vous. Tenez, prenez votre or. Vous l'avez mérité.";
			link.l1 = "Mes remerciements. Adieu, monsieur !";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("Salutations, capitaine. Je veux demander votre aide.","Capitaine ! Pouvez-vous m'aider ? Je vous en prie.","Capitaine, je sollicite votre aide !");
			link.l1 = RandPhraseSimple("Je suis occupé.","Je suis pressé.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Quel est le problème ?","Dis-moi ce qui te tracasse. Peut-être pourrai-je t'aider.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Il y a un an, un capitaine a promis de m'emmener à "+XI_ConvertString("Colony"+SelectNotEnemyColony(NPChar)+"Acc")+". Mais pendant que j'étais sur son navire, j'ai été jeté dans la cale et vendu en esclavage ensuite. J'ai à peine survécu. J'ai frôlé la mort plusieurs fois... Quoi qu'il en soit, je veux rappeler à mon 'ami' que je suis toujours en vie."; // belamour gen
					link.l1 = "Que veux-tu dire ? Dis-moi exactement ce que tu veux.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "Ma femme a été enlevée. Un capitaine, un pirate comme on dit, la courtisait. Ma femme a dû rester à la maison pendant des jours, à cause de ses filatures. J'ai essayé de faire en sorte que les autorités de la ville nous aident, mais en vain. Et maintenant...";
					link.l1 = "Et maintenant ?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Tu sais, je cherche mon compatriote. Il y a trois ans, nous sommes arrivés ici ensemble d'Europe pour trouver une vie meilleure. Nous nous sommes perdus de vue. Mais il n'y a pas longtemps, j'ai entendu dire qu'il est maintenant capitaine marchand ! J'ai essayé de le retrouver moi-même, mais j'ai échoué.";
					link.l1 = "Alors ?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Je veux que tu le trouves et que tu le tues. Je le veux mort à tel point que je ne peux même pas manger...";
			link.l1 = "Je vois... Je suppose que je peux t'aider avec ça. Dis-moi son nom et le nom de son navire.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Désolé, mais cela ne m'intéresse pas.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" de la "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nommé "+npchar.quest.SeekCap.shipName+". Je te paierai  "+FindRussianMoneyString(sti(npchar.quest.money))+", plus tous mes bijoux."; // belamour gen
			link.l1 = "Je vois. Je serai attentif en mer. Si je trouve la cible... Considérez-le alors comme mort.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "Je ne ferai rien pour cette somme. Trouve un autre imbécile pour accomplir ta vengeance.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "C'est ce que j'espérais entendre ! Oh, je peux manger maintenant ! Enfin ! Je dois me procurer de la nourriture...";
			link.l1 = "Bon appétit. Je te trouverai une fois le travail terminé.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Je t'attendrai dans l'église locale.";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "J'étais trop oisif et le salaud a pris ma femme et l'a emmenée à bord de son navire. Je te demande de trouver ce scélérat !";
			link.l1 = "Hum, et pourquoi devrais-je me battre avec un camarade vaurien ?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "Je ne suis pas riche, mais ce sera mon plaisir de vous donner tous les objets de valeur que je possède ! Si vous libérez ma femme et me l'amenez, je vous paierai "+FindRussianMoneyString(sti(npchar.quest.money))+",  plus tous mes bijoux.";
			link.l1 = "D'accord, je suis partant. Dis-moi les détails. Son nom, son navire et comment s'appelle ta femme.";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "Non, camarade, je ne veux pas le faire pour une si petite somme. Je suis désolé...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "Son nom est "+npchar.quest.SeekCap.name+". Et le nom du bâtard est "+npchar.quest.SeekCap.capName+", il nage sur "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nommé "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Les merdes flottent, l'ami. Les capitaines voguent...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Oui, oui, je suis tellement désolé ! Je ne suis pas un marin, j'espère que vous comprendrez...";
			link.l1 = "C'est d'accord, ne t'en fais pas. Quoi qu'il en soit, je reviendrai dès que ce sera fait.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Merci beaucoup ! Je vous attendrai dans l'église locale. Mais je vous prie de vous dépêcher. Je m'inquiète vraiment pour ma femme...";
			link.l1 = "Ouais, je ne l'envie pas non plus.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "Le problème, c'est que mon ami n'a aucun domaine. Son navire est sa maison. Donc je ne peux pas le trouver, car il est toujours en mer. Et je ne peux pas me permettre des voyages inutiles, je dois gagner de l'argent pour vivre.";
			link.l1 = "Je ne peux pas vous aider, si vous n'avez pas d'argent...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Je peux te payer "+FindRussianMoneyString(sti(npchar.quest.money))+" et je te donnerai tous mes bijoux. C'est tout ce que je peux me permettre pour l'instant.";
			link.l1 = "Cette somme me convient. Je suis partant. En fait, vous pouvez me rejoindre en tant que passager, ainsi vous verrez votre ami dès que nous le trouverons.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "Ce n'est pas suffisant pour moi. Cherchez quelqu'un d'autre pour le faire.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "Non, je suppose que je resterais ici. Nous ne savons pas combien de temps ces recherches dureront et je pourrais perdre tout mon argent. J'ai un emploi ici.";
			link.l1 = "Je vois. Maintenant, dis-moi, qui est ton ami et sur quel navire est-il.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "Son nom est "+npchar.quest.SeekCap.capName+". Autant que je sache, il commande un "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Accord"))+" nommé "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Je vois. Eh bien, je parlerai de vous à votre ami si je le vois.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Merci. J'attendrai votre arrivée dans l'église locale. Vous recevrez vos pièces une fois le travail terminé.";
			link.l1 = "Bien sûr. Adieu alors, attendez-vous bientôt aux résultats.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "Bonne journée à vous, capitaine. Avez-vous déjà des résultats?";
			link.l1 = "Rappelle-moi ton problème...";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "Je suppose que j'ai été vengé. Est-ce exact ?";
					link.l1 = "Exactement. "+npchar.quest.SeekCap.capName+" est mort et son "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" est au fond de la mer.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Tu as trouvé ma femme ! Je n'arrive pas à le croire ! Puis-je ?";
					link.l1 = "Tu peux. Elle est mon passagere. Tu peux la ramener, si "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" c'est vraiment ta femme...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Bonne journée à vous, capitaine. Avez-vous trouvé mon camarade ?";
					link.l1 = "Je l'ai fait et lui ai parlé de vous.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Quoi ? Aurais-tu vraiment oublié que je t'ai demandé de venger le capitaine "+npchar.quest.SeekCap.capName+" pour une année de mon esclavage ?";
					link.l1 = "Non, je n'ai pas.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Je n'en crois pas mes oreilles ! As-tu oublié que je t'ai demandé de trouver et de libérer ma femme ? Elle a été capturée par le pirate nommé "+npchar.quest.SeekCap.capName+" !";
					link.l1 = "Je n'ai pas.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Attends une seconde... Aurais-tu oublié ta promesse de retrouver mon camarade nommé "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "Je n'ai pas.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Excellent, je ne me suis pas trompé sur vous ! Donc, comme je vous l'avais promis, voici votre "+FindRussianMoneyString(sti(npchar.quest.money))+" et des bijoux. Merci pour votre aide.";
			link.l1 = "Tu es le bienvenu...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "Oh mon Dieu ! Vous nous avez sauvés ! S'il vous plaît, prenez votre "+FindRussianMoneyString(sti(npchar.quest.money))+" et des bijoux. Et sachez que nous prierons pour vous à jamais !";
			link.l1 = "Priez si vous voulez. Je n'ai aucun problème avec ça.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "Splendide!... Tenez, prenez "+FindRussianMoneyString(sti(npchar.quest.money))+" et des bijoux. Et merci, capitaine.";
			link.l1 = "Vous êtes le bienvenu, ami. Adieu...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("Salutations, capitaine. Pouvez-vous m'aider ?","Capitaine ! Pouvez-vous aider une femme ? Seriez-vous assez aimable...","Capitaine, à l'aide "+GetSexPhrase("une fille","moi")+".");
			link.l1 = RandPhraseSimple("Je suis occupé.","Désolé, "+GetAddress_FormToNPC(NPChar)+", mais je n'ai pas de temps à perdre...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Quel est ton problème, "+GetAddress_FormToNPC(NPChar)+"?","Exposez vos problèmes, "+GetAddress_FormToNPC(NPChar)+". Je vais essayer de vous aider.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Mon mari est marchand, il livre des marchandises à chaque colonie autour. Il y a trois mois, il est parti en mer. Il n'est pas encore revenu !";
					link.l1 = "Penses-tu qu'il lui est arrivé quelque chose ?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("Capitaine, je vois que vous êtes un capitaine courageux, un parfait gredin","Capitaine, je vois que vous êtes une femme forte, capable de tenir tête à n'importe quel homme")+"...";
					link.l1 = "Et pourquoi dis-tu cela, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Capitaine, s'il vous plaît aidez-moi, je vous en supplie ! Mon mari a été capturé ! Pouvez-vous le sauver ?";
					link.l1 = "Attends une seconde, je ne comprends pas. Qui a été capturé par qui ?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "Je ne sais pas, mais j'espère encore qu'il est juste trop occupé pour m'écrire. Il aurait pu m'envoyer une lettre, il sait que je m'inquiète pour lui !";
			link.l1 = "Il n'est pas sûr en mer, tout pourrait arriver...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Exactement !  Vous comprenez de quoi je parle.  Vous avez l'air d'un "+GetSexPhrase("brave capitaine","courageuse fille")+", alors je veux te demander de retrouver mon mari. Je suis prête à te payer "+FindRussianMoneyString(sti(npchar.quest.money))+", de plus je te donnerai tous mes bijoux.";
			link.l1 = "Très bien. Je parlerai à votre mari de vos inquiétudes, si je le rencontre en mer ou ailleurs. Dites-moi son nom et le nom de son navire.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Je ne suis pas intéressé par une si petite somme.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "Son nom est "+npchar.quest.SeekCap.capName+". Il navigue sur un "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nommé "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "Je vois. Maintenant, tu dois attendre. Essaie de passer le plus de temps possible à l'église, afin que je puisse te trouver.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("Je dis cela, bon monsieur, parce que je veux vous engager pour faire le travail auquel vous êtes habitué... pour ainsi dire.","Je veux que tu m'aides. J'espère que tu me comprendras en tant que femme.")+"Un capitaine m'a agacé et je veux le voir mort.";
			link.l1 = "Et qu'a donc fait cette pauvre âme pour vous offenser ?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Ce salaud m’a trompée. Il a prétendu être amoureux de moi, il me courtisait même. Et la raison pour laquelle il faisait tout cela était d'obtenir quelque chose de précieux de mon mari ! Et quand le chien a eu son os, il m’a dit que ça ne signifiait rien... que nous étions juste amis !";
			link.l1 = "Hum, peut-être avait-il raison ?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Est-ce que j'ai l'air d'un idiot ?! Penses-tu que je ne vois pas la différence entre une cour et un simple baratin ?";
			link.l1 = "Bien sûr que si...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "Il m'a utilisé, ce scélérat ! Je ne lui pardonnerai jamais pour ça !";
			link.l1 = "Oui, les hommes sont juste comme ça. Mais peut-être pouvez-vous vous calmer ? Il n'y a rien de terrible là-dedans...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Rien d'horrible ?! "+GetSexPhrase("Tu es un moraliste en quelque sorte, tu n'es pas un vrai pirate !","Il semble que vous n'ayez jamais été dans une situation pareille ! Oh, oui, qui prendrait un tel risque... et moi, je ne suis qu'une pauvre femme faible...");
			link.l1 = "Très bien. Ça suffit. Je souhaite simplement savoir à quel point vos intentions sont sérieuses.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Merde, "+GetSexPhrase(" tu ne sais tout simplement pas à quoi ressemble la vengeance d'une femme rejetée ","tu es une femme et tu dois comprendre ce que c'est d'être rejetée ! Je veux une vengeance ")+"!";
			link.l1 = ""+GetSexPhrase("C'est vrai, jamais eu une telle expérience","Eh bien, tu sais, elle pleurerait juste un peu, casserait quelques verres et ce serait fini")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("Considérez-vous chanceux. La femme rejetée et déçue dans ses attentes est une furie, un diable en jupon ! Rien au monde ne pourrait adoucir sa colère","Et je ne suis pas comme elle. Rien ne pourrait adoucir ma colère")+"!\nAlors je veux que tu le tues toi-même. Et avant qu'il ne meure, il doit savoir qui paie pour sa mort...";
			link.l1 = "Hm, je ne sais même pas quoi dire... Et combien payez-vous ?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Tout ce que j'ai. Je te donnerai mes bijoux et "+FindRussianMoneyString(sti(npchar.quest.money))+"Marché conclu ?";
			link.l1 = "Je suis intéressé. Dites-moi son nom et le nom de son navire.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "Pas intéressé. Adieu.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "Le nom de ce vaurien est "+npchar.quest.SeekCap.capName+" et il navigue sur un "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Gén"))+" nommé "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Considérez cela fait, "+GetAddress_FormToNPC(NPChar)+" Attends-moi dans l'église locale. J'espère que tu te calmeras un peu...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "Je vais expliquer. Le problème est que mon mari, qui n'est qu'un homme ordinaire, a été capturé par des pirates ! Ils tuaient tout le monde et ils n'ont épargné personne...";
			link.l1 = "Il semble que le capitaine ait osé résister. Ils auraient autrement épargné l'équipage.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Peut-être, mais mon mari est une âme innocente. Il n'était là que comme passager. Il a dû leur dire qu'il est riche pour sauver sa vie. Les pirates l'ont épargné, il n'a même pas été mis dans une cale.";
			link.l1 = "Et comment le sais-tu?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Il a réussi à m'envoyer une lettre. Il a écrit qu'il se porte bien et qu'il est retenu dans une cabine, pas comme les autres prisonniers.";
			link.l1 = "Et que comptes-tu faire ? Cela ne peut pas continuer ainsi. Tôt ou tard, les pirates verront clair en lui.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Es-tu un pirate aussi ? Oui-oui, je sais... Je vous en supplie, aidez-nous, sauvez mon mari ! Il a décrit ce navire pirate et écrit le nom du capitaine. Il ne te sera pas difficile de les trouver !";
			link.l1 = "Ce n'est pas aussi simple que vous le pensez. Tous les prisonniers sont le butin légitime du capitaine qui a capturé votre mari, de plus cela prendra du temps.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Mais tu peux au moins essayer ! De plus, tu as assez de temps pour chercher. Mon mari n'est pas un imbécile et il prétend être un marchand du Vieux Monde, alors ces pirates ne lui demandent pas de pièces pour l'instant. Si tu le libères, je te donnerai tout ce que j'ai !";
			link.l1 = "Et qu'as-tu ?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Pas grand-chose, "+FindRussianMoneyString(sti(npchar.quest.money))+" et tous mes bijoux... Mais je prierai pour ton âme à jamais !";
			link.l1 = "Oui, ce n'est vraiment pas grand-chose... Bien, je suis prêt à t'aider.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Je suis désolé, mais cela ne me suffit pas.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Merci, merci beaucoup!";
			link.l1 = "Tu me remercieras, si je réussis, alors arrête. Tu ferais mieux de me dire le nom de ton mari et tout ce que tu sais sur ces pirates.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "Son nom est "+GetFullName(forName)+". Capitaine's "+npchar.quest.SeekCap.capName+", il navigue sur "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nommé "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Je vois. Eh bien, maintenant tu devrais attendre et espérer que je réussirai dans ma quête. Reste à l'église, attends et prie ...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, capitaine, je suis si heureux de te voir ! Dis-moi maintenant, qu'as-tu à me dire concernant ma tâche ?";
			link.l1 = "Hm, rappelle-moi, "+GetAddress_FormToNPC(NPChar)+", de quelle tâche parles-tu?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ah, capitaine, j'ai reçu une lettre de mon mari ! Il a écrit que vous l'avez trouvé.";
					link.l1 = "Oui, c'est correct, "+GetAddress_FormToNPC(NPChar)+".  Votre mari, "+npchar.quest.SeekCap.capName+",  est sain et sauf. Il est juste trop occupé...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "Que diriez-vous, capitaine ? Avez-vous fait ce que je vous ai demandé ? Est-ce que le capitaine "+npchar.quest.SeekCap.capName+" mort?";
					link.l1 = "Oui, il est mort, "+GetAddress_FormToNPC(NPChar)+"Je lui ai dit qui était la cause de sa mort. La dernière chose qu'il a entendue dans sa vie était ton nom.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Vous avez sauvé mon mari ! Je vous supplie de me dire que c'est vrai !";
					link.l1 = "Oui, c'est vrai. Il est sur mon navire en ce moment. Vous pouvez le voir si "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"est vraiment votre mari...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Avez-vous vraiment oublié que vous m'avez promis de retrouver mon mari ? Son nom est "+npchar.quest.SeekCap.capName+" !";
					link.l1 = "Oh, oui, bien sûr... Je n'ai pas oublié.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Je ne comprends pas ! As-tu oublié que tu dois tuer mon offenseur, un capitaine nommé "+npchar.quest.SeekCap.capName+"?!";
					link.l1 = "Oh s'il vous plaît, bien sûr que non. Votre commande est en cours, veuillez patienter...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Jesus, capitaine, as-tu oublié ta promesse de libérer mon mari ?";
					link.l1 = "Je n'ai pas. Te souviens-tu ... 'Attends et prie !'. Attends juste, "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Oh, dieu, je suis tellement reconnaissant ! Et oui, prends ton "+FindRussianMoneyString(sti(npchar.quest.money))+"Et merci encore !";
			link.l1 = "Hum, tu es le bienvenu...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Excellent ! Eh bien, prends ton "+FindRussianMoneyString(sti(npchar.quest.money))+" et des bijoux. Adieu...";
			link.l1 = "Adieu. ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Sûr que c'est lui ! Oh mon dieu, capitaine, je suis tellement reconnaissant. Prenez votre "+FindRussianMoneyString(sti(npchar.quest.money))+"Je prierai pour toi chaque jour de ma vie !";
			link.l1 = "Ça semble bien...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Salutations à ma confrérie. Tu veux quelque chose"+GetSexPhrase(", camarade ",",  fille")+"?";
					link.l1 = "Ton nom est "+GetFullName(npchar)+", ai-je raison ?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Oui, tu l'es !";
			link.l1 = "Quel dommage pour toi. Je vais te dire un nom et tu ferais mieux de le connaître."+GetFullName(&characters[GetCharacterIndex("QueteCitoy_ "+npchar.quest.cribCity)])+". Souviens-toi de lui ?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hum, je fais...";
			link.l1 = "Maintenant écoute, il est très en colère contre toi, l'ami. Il est temps de payer pour avoir vendu un homme libre à l'esclavage.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = " Payer ?! Qu'est-ce que tu racontes, bordel ? ";
			link.l1 = "Je veux dire que je vais te tuer là où tu te tiens.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Réfléchis-y, pour qui travailles-tu ?! Cet homme est misérable et sa place est à la plantation de sucre !";
			link.l1 = "Eh bien, cela ne vous regarde pas. Maintenant, vous devez répondre de ce que vous avez fait !";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho ! Je répondrai de la seule manière dont j'ai l'habitude !";
			link.l1 = "Continue...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "Que veux-tu ?";
			link.l1 = "Je veux te demander, prends-tu des passagers? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "Et comment cela vous concerne-t-il ?";
			link.l1 = "Juste pour demander.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Je te le demande juste... Écoute, tu ferais mieux de partir d'ici tant que je te donne encore cette opportunité. Je ne t'aime pas !";
			link.l1 = "D'accord, d'accord, calme-toi. Je m'en vais...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Nous avons déjà parlé, alors ne me teste pas !";
			link.l1 = "Je ne le ferai pas.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Salutations, collègue ! Veux-tu quelque chose ?";
			link.l1 = "J'aimerais savoir, n'as-tu pas emmené la femme de "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" nommé "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, tu as raison, elle est dans ma cabine ! Chaude donzelle, belles jambes d'ailleurs... Pourquoi demandes-tu ?";
			link.l1 = "Ami, cette femme est mariée. C'est mal.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "Et alors ? Je l'aime et c'est tout. Je ne laisserai pas un idiot en haillons s'immiscer dans notre relation juste parce qu'il est son mari !";
			link.l1 = "Laisse-moi te dire que les Frères n'approuvent pas des choses comme ça, et si certaines personnes entendent parler de ce que tu as fait, la marque noire te sera envoyée.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Vas-tu commencer à me faire un sermon ?";
			link.l1 = "Calmez-vous, je m'intéressais juste... Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Nous avons déjà discuté de la femme. Je ne veux pas en parler à nouveau !";
			link.l1 = "Peu importe...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Je suis ravi de saluer un collègue sur mon pont ! Que voulez-vous ?";
			link.l1 = "J'aimerais savoir si vous avez enlevé une femme de "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gén")+" du nom de"+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Eh bien, tu as raison, elle est dans ma cabine ! Sacree fille, de belles jambes d'ailleurs !... Pourquoi demandes-tu ?";
			link.l1 = "Ami, cette femme est mariée. C'est mal.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "Et alors ? Je l'aime et c'est tout. Je ne laisserai pas un vaurien s'immiscer dans notre relation juste parce qu'il est son mari !";
			link.l1 = "Permets-moi de te dire que les Frères n'approuvent pas ce genre de choses, et si certaines personnes entendent parler de ce que tu as fait, la marque noire te sera envoyée.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Tu vas commencer à me prêcher?";
			link.l1 = "Calmez-vous, je m'intéressais juste... Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Que veux-tu de moi, vermine?!";
			link.l1 = "Je suis ici pour la femme que tu as volée à son mari. Souviens-toi "+XI_ConvertString("Colony"+npchar.quest.cribCity)+"? Son nom est "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "Merde! Tu ne la verras jamais, tout comme tu ne verras jamais tes oreilles!";
			link.l1 = "Crétin. Je peux les voir dans un miroir. Et je vais te couper les tiens!";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Qui es-tu ?";
			link.l1 = "Bonjour. Je suis venu pour vous parce que votre mari m'a demandé de le faire. Maintenant vous êtes libre et je peux vous emmener à lui.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "Est-ce un rêve ?! Est-ce vrai ?!";
			link.l1 = "C'est, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Louez le Seigneur ! Je suis prêt, fuyons d'ici !";
			link.l1 = "D'accord, "+GetAddress_FormToNPC(NPChar)+", préparez-vous pour un retour en toute sécurité auprès de votre mari.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Bonjour ! Heureux de saluer un collègue sur le rivage...";
			link.l1 = TimeGreeting()+", j'ai des affaires à traiter avec vous.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Je vous écoute.";
			link.l1 = "Un de vos camarades vous cherche. Vous naviguiez ensemble et êtes arrivés ici depuis le Vieux Monde."+GetFullName(&characters[GetCharacterIndex("QuêteCitoyen_"+npchar.quest.cribCity)])+", tu te souviens ?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ha, bien sûr que oui ! Et où vit-il maintenant ?";
			link.l1 = "Dans "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Ça");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = "Merci! Vous savez, je pensais que vous étiez un pirate!";
			link.l1 = "Je le suis. En quelque sorte. Ou je ne le suis pas. Mais de toute façon, je suis de bonne humeur aujourd'hui, alors tu n'as rien à craindre. Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "Y a-t-il un problème ? Je suis désolé, je suis un peu nerveux...";
			link.l1 = "C'est bon, camarade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+". Que voulez-vous de moi? Je ne suis qu'un simple marchand et...";
			link.l1 = "Je sais, l'ami. Ne t'inquiète pas autant, on dit que ce n'est pas bon pour la santé. J'ai des affaires à traiter avec toi.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "Quel genre de commerce ?";
			link.l1 = "Un ami à vous vous cherche. Son nom est "+GetFullName(&characters[GetCharacterIndex("QuêteCitoyen_"+npchar.quest.cribCity)])+". Le connais-tu ?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Oh, enfin ! C'est formidable... Je suis vraiment désolé pour un accueil si brutal, mais je pensais que vous étiez un pirate.";
			link.l1 = "Je le suis. En quelque sorte. Ou je ne le suis pas. Mais quoi qu'il en soit, je suis de bonne humeur aujourd'hui, donc tu n'as rien à craindre. On m'a demandé de te livrer un message et j'ai fait le travail. Ton camarade vit à "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "N'est-ce pas quelque chose ! Vous êtes un homme honorable. Merci !";
			link.l1 = "Je vous en prie. Adieu et prends garde à toi, camarade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Bonjour. Vous désirez quelque chose ?";
			link.l1 = "Ton nom est "+GetFullName(npchar)+", ai-je raison ?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Oui, c'est moi.";
			link.l1 = "Ça semble probablement stupide, mais votre femme m'a demandé de vous dire qu'elle s'inquiète pour vous.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ha ! Je vois... En fait, j'étais trop occupé, il y a beaucoup d'offres rentables et je ne peux pas perdre de possibles revenus juste parce que ma femme s'inquiète trop.";
			link.l1 = "Mais tu pourrais au moins lui écrire une lettre et lui dire que tu vas bien.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Oui, tu as raison. Je vais lui écrire immédiatement ! Merci de participer à nos affaires familiales !";
			link.l1 = "Tu es le bienvenu, camarade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Bonne journée à vous. Comment puis-je vous aider ?";
			link.l1 = "Ton nom est "+GetFullName(npchar)+", ai-je raison ?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Oui, c'est moi.";
			link.l1 = "Ça semble probablement stupide, mais votre épouse m'a demandé de vous dire qu'elle s'inquiète pour vous.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Fuh, bon sang ! Je craignais que ce soit le chasseur de primes célèbre qui venait pour moi, Steve le Borgne qu'on l'appelle. Eh bien, c'est bien que je me sois trompé\nVous voyez, je suis tellement occupé avec mon travail et je ne peux pas consacrer de temps pour elle. J'ai des offres lucratives qui arrivent tout le temps et je ne peux pas les refuser à cause des inquiétudes de ma femme.";			
			link.l1 = "Tu as raison, certes. Mais tu pourrais au moins lui écrire une lettre et lui dire que tu vas bien.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Oui, tu as raison. Je le ferai dès le premier port... Merci de participer à nos affaires familiales !";
			link.l1 = "Tu es le bienvenu, camarade.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Vous avez mes remerciements, capitaine...";
			link.l1 = "Vous êtes le bienvenu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Content de te voir dans cette ville, capitaine. As-tu besoin de quelque chose de ma part ?";
			link.l1 = ""+GetSexPhrase("Tu sais, capitaine... Pff, je ne sais même pas comment dire !","Oui, j'ai.")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("Dis-le comme c'est.","Intéressant, et qu'est-ce que c'est?")+"";
			link.l1 = " J'ai une question pour vous. Connaissez-vous une femme nommee "+GetFullName(&characters[GetCharacterIndex("QueteCitoy_ "+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, je le sais. J'ai eu la malchance de la connaître. Une fille insensée, je peux te le dire...";
			link.l1 = "Hm... Oui, et cette sotte de fille m'a demandé de te tuer. C'est ça....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Balivernes.";
			link.l1 = ""+GetSexPhrase("Je suis d'accord. Mille pardons, mais il y a une prime sur ta tête","Ce n'est pas le cas. Il y a une prime")+"Et je vais le prendre.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho-ho !... Vous vous moquez de moi, capitaine ?";
			link.l1 = ""+GetSexPhrase("Non, mon ami.","N'allais même pas le faire !")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("Tu n'es pas mon ami, idiot! Tu ne peux même pas te dire capitaine. Tu es le jouet de cette furie insensée!","Merde ! Une furie en a engagé une autre ! Que diable se passe-t-il dans ce monde ?")+"!";
			link.l1 = ""+GetSexPhrase("Surveille ton langage, racaille.","Tu l'as utilisée, alors ne sois pas surpris qu'elle ait décidé de se venger.")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("L'ai-je touché au vif?","Solidarité féminine ?!")+"";
			link.l1 = "Finissons-en !";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "Je t'ai déjà parlé. Dégage, crétin !";
			link.l1 = "Cretin ?! Soit alors...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Content de vous voir à bord, capitaine. Que voulez-vous ?";
			link.l1 = "J'ai une question pour vous. Connaissez-vous une femme nommee "+GetFullName(&characters[GetCharacterIndex("QueteCitoy_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Hein, je le fais. J'ai eu la malchance de la connaître. Une fille insensée, je te le dis...";
			link.l1 = "Oui, et cette sotte de fille m'a demandé de te tuer.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Capitaine ne me fais pas rire. Si tu n'as pas de sérieuse affaire avec moi, alors je te dis adieu.";
			link.l1 = "Adieu, alors. Mais réfléchissez à ce que je vous ai dit.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Bien sûr, capitaine, comment cela pourrait-il être autrement?!";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Je ne veux plus discuter de cette affaire, capitaine. C'est bien trop ridicule.";
			link.l1 = "Quoi que tu dises...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "Que diable se passe-t-il ici ?! Pourquoi avez-vous attaqué mon navire ?";
			link.l1 = "À la demande de la dame nommée "+GetFullName(&characters[GetCharacterIndex("QueteCitoyen_"+npchar.quest.cribCity)])+". La connais-tu ?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Nom de Dieu !!! Je n'arrive pas à y croire...";
			link.l1 = "Tu dois le faire ! Tu ne connais pas les femmes, matelot ? Elles peuvent mordre.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Eh bien, je ne vais pas mourir comme ça. Merci pour la discussion, maintenant j'ai récupéré un peu de force.";
			link.l1 = "Ça ne te servira à rien.";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Heureux de te voir à bord. Puis-je t'aider ?";
			link.l1 = "Tu peux. Je cherche un homme nommé "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Cet homme est mon prisonnier et je compte le rançonner.";
			link.l1 = "Je veux l'emmener.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Malheureusement, c'est impossible. Si c'est tout, je vous prierais de quitter mon navire.";
			link.l1 = "D'accord, capitaine, comme vous dites.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Nous avons déjà parlé de mon prisonnier. Rien n'a changé.";
			link.l1 = "Je vois...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Enchanté de vous rencontrer. Puis-je vous aider ?";
			link.l1 = "Vous pouvez. Je cherche un homme nommé "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Cet homme est mon prisonnier et je compte demander une rançon pour lui.";
			link.l1 = "Je veux le prendre.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Je suis désolé mais ce n'est pas possible.";
			link.l1 = "Quel dommage...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Saperlipopette ! Que diable ?!";
			link.l1 = "J'ai besoin de ton prisonnier nommé "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha ! Pas question, seulement par-dessus mon cadavre !";
			link.l1 = "Puisque tu as demandé...";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Qui es-tu ?";
			link.l1 = "Je suis capitaine "+GetFullName(pchar)+"Ne t'inquiète pas, je suis ici pour te conduire à ta femme.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Diantre, je dois rêver !";
			link.l1 = "Je peux vous assurer que ce n'est pas le cas... Eh bien, tout est fini maintenant, éloignons-vous d'ici.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Je suis épuisé, aidez-moi.","Je n'ai plus de force pour vivre ainsi !"),RandPhraseSimple("Ce travail nous ronge vivants.","Les foutus gardes n'ont pas laissé un morceau de peau sur mon dos !"));				
				link.l1 = RandPhraseSimple("Quel dommage.","Oui, la vie est une garce.");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "Oh, capitaine, prends un siège avec moi. C'est moi qui offre!";
					link.l1 = "Mon plaisir.";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "Bonjour, capitaine. Vous êtes capitaine, n'est-ce pas ? Même un capitaine de la marine, peut-être ?\nOui, vous devez être habile à l'épée contrairement à mon fils bon à rien qui va mourir demain... À cause de ce bâtard lubrique qui a jeté son dévolu sur la dame de cœur de mon fils !";
						link.l1 = "Oui, je suis capitaine, et mon épée m'a déjà sauvé de nombreuses fois, mais qu'en est-il du reste de ton discours déprimant ? Veux-tu bien expliquer ?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "Salutations, capitaine. Permettez-moi de vous demander, ne seriez-vous pas un pirate par hasard ? Oh, bien sûr que non ! Vous ne l'êtes pas. Les pirates ont mauvaise mine, se comportent comme des animaux et cette puanteur...";
						link.l1 = "Gardes-tu rancune contre les pirates ?";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "Hé, toi ! Oui, toi, dis-moi, où sont tes manières ? Pourquoi diable te tiens-tu là et me déranges-tu ? Non, regarde-le, quel imbécile ! Je te parle ! Fais place ! Trop d'étrangers ici !";
							link.l1 = "Du calme, je ne voulais pas te déranger. Je te demande pardon.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "Surveille ton langage, ou je te le couperai, mon bon monsieur.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "Salutations, capitaine. J'ai quelque chose à vous demander. Vous ne resterez pas indifférent si vous êtes un homme d'honneur. \nAlors, allons droit au but : un noble est resté dans notre taverne il y a un mois. Il s'est avéré être un débauché et un salaud ! Encore pire, c'est un meurtrier !";
						link.l1 = "Autant que je me souvienne, la peine pour avoir assassiné un innocent est la potence. Être un débauché et un bâtard ne fera pas grand bien au tribunal non plus. Ai-je raison ?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "Capitaine, attendez, je vous en supplie. Vous avez l'air d'un escrimeur habile, bien meilleur que moi. Alors je veux vous demander de me remplacer.";
						link.l1 = "Intrigant. Continue.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "Je vous en prie, je vous supplie, ne partez pas ! Attendez... Ne voudriez-vous pas aider une pauvre âme dans une affaire qui nécessite l'intervention d'un officier militaire aussi courageux que vous-même ?\nLe fait est que j'ai eu une querelle concernant les plantations de raisin locales avec mon voisin, d'ailleurs, il est soupçonné d'avoir des relations avec des contrebandiers. Oui, oui, et il pourrait même avoir des affaires avec des pirates, comment aurait-il pu faire une telle fortune en si peu de temps autrement ?\nIl n'avait rien qu'une barque il y a un an et maintenant il veut prendre mes vignobles, vous écoutez ?! Mes vignobles !";
						link.l1 = "Je suis désolé pour vos vignobles. Honnêtement. Adieu.";
						link.l1.go = "exit";
						link.l2 = "Je vous demande pardon, mais ne pouvez-vous pas vous adresser aux autorités locales ?";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "Capitaine, capitaine, je vous en supplie ! Protégez l'honneur de la jeune fille innocente !";
						link.l1 = "Je n'ai pas le temps pour ça, jolie. Cherche quelqu'un d'autre...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "Salutations, ma dame. Ne tremblez pas ainsi ! Que s'est-il passé ?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "Bug. Informez les devs.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "Capitaine, j'ai été suivi de la manière la plus explicite par un officier de notre garnison. Vous avez sûrement entendu ces rumeurs immondes qu'il colporte à mon sujet, essayant de me couvrir de honte!\nHélas, je n'ai pas d'amis capables de protéger mon honnête nom! Je suis désespérée! Oh, Dieu, le voilà! Aidez-moi!";
			link.l1 = "Ne t'inquiète pas, je m'en chargerai.";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "Ah, te voilà, ma dame ! Encore un cavalier, je suppose ? Quand comptes-tu te ranger ? Peut-être jamais... Va travailler au bordel, c'est l'endroit le plus approprié pour toi...";
			link.l1 = "Officier, ferme ta bouche pleine d'insultes ou je te ferai taire à ma manière spéciale !";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "Hum... Qui es-tu ? A-ah, salé par la mer elle-même, le brave capitaine d'un petit bateau, ai-je raison ? Et qu'est-ce que tu comptes faire, petit marin ?";
			link.l1 = "Cette dame est mon amie ! Et je te lancerai un défi !";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "Quoi ?! Tu ne vas pas me défier à cause de ça...";
			link.l1 = "Assez ! Je t'attendrai près du phare dans deux heures. Et n'oublie pas d'apporter ton épée !";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "Ah, je sais tout, monsieur ! Vous ne comprenez même pas combien je vous suis reconnaissant ! Que le Seigneur vous protège !";
			link.l1 = "Je suis heureux d'avoir pu vous aider. Bonne chance !";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "Ah, tu es comme tous les autres, laisse-moi !";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+"... Je n'ose espérer, mais peut-être que ton épée pourrait protéger ma famille cette fois-ci ?\nComme je l'ai dit, mon fils n'est pas un escrimeur, mais il va se battre en duel dès le matin suivant. Ah, si ce n'était pas pour sa dame et ce maudit honneur\nMais il ne pouvait pas se dérober et maintenant il est condamné, ne le vois-tu pas ? Je suis désespéré, c'est mon fils unique et un héritier, c'est pourquoi je te demande de tuer le salaud qui a défié mon petit avant l'aube. Je ferai en sorte que cela vaille ton temps, tu peux compter là-dessus !\nTu trouveras l'homme à la taverne "+sTemp+" - là, où des salauds comme lui passent leur temps libre... Je vous en supplie...";
			link.l1 = "Je ne me soucie ni de toi ni de ton fils. Laisse-moi partir !";
			link.l1.go = "exit";
			link.l2 = "Hum ... Juste comme ça ? Très bien, nous verrons comment cela se termine.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "Voudrez-vous vraiment aider mon fils? Oh, "+GetAddress_Form(NPChar)+" ! Je prierai pour toi et ta chance !";
			link.l1 = "Je n'y vois pas de mal... Attends-moi !";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "Que diable voulez-vous de moi ? Je me repose ici et je ne veux pas être dérangé. Il y a plein de sièges libres et d'oreilles disponibles, alors laissez-moi tranquille, monsieur !";
			link.l1 = "Malheureusement, vous devrez interrompre votre repos jusqu'à des jours meilleurs.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "Quoi ?! Et qui es-tu pour me dire quoi faire ?!";
			link.l1 = "Tu m'as oublié, hein ? Mais moi, je me souviens de toi ! Et je dis que des vauriens comme toi empoisonnent notre monde rien que par leur présence !";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "Ah ?! Marin, il semble que tu es bien trop ivre ! C'est la première fois que je te vois ! Mais je ne vais pas ignorer ton comportement ! C'est ta dernière chance pour sauver ta vie misérable ! Présente tes excuses maintenant, hareng boursouflé, et j'oublierai ton discours insolent !";
			link.l1 = "Je ne fais d'excuses qu'aux hommes honorables, pas à des porcs immondes !";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "Putain de merde ! Tu cherches des ennuis, espèce de rat de latrines ?";
			link.l1 = "Je vais te fermer ta putain de gueule avec tes mots, rat! Je t'attendrai près du phare dans deux heures et n'oublie pas d'apporter cette merde rouillée que tu portes à ta ceinture!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "Ha !  J'y serai !";
			link.l1 = "À bientôt !";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "Oh, c'est toi ! Tu es vivant, ce qui signifie que...";
			link.l1 = "Oui, je le suis, et votre fils n'a pas besoin de se battre en duel demain matin...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "Quel beau jour ! Je devrais aller annoncer de bonnes nouvelles à ma femme !\nCapitaine, le destin lui-même vous a envoyé pour m'aider. Tenez, prenez ces pièces et acceptez la gratitude de notre famille !";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "Va-t'en, assassin d'enfants !";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "Moi ? Dieu merci, je vais bien, mais ma sœur n'a pas cette chance. Elle travaille dans une taverne\nIl y a un corsaire qui fréquente souvent l'endroit, un type très dangereux. Pirate ! Son navire est en mer depuis au moins une semaine. L'homme boit, menace les gens et promet de tuer quiconque essaie de le raisonner. Le pire, c'est que ma sœur m'a dit qu'il se vante de l'enlever et de l'emmener le diable sait où si elle ne satisfait pas ses souhaits immondes !\nJe ne sais pas quoi faire ! Les autorités ne se soucient pas d'une simple servante et les citoyens paisibles comme moi craignent ce corsaire. Aidez-nous à nous en débarrasser, je vous en prie !";
			link.l1 = "Je n'ai pas le temps de calmer les ivrognes dans les tavernes. Parlez au commandant, on le paie pour résoudre ces affaires.";
			link.l1.go = "exit";
			link.l2 = "Hum, un corsaire menaçant ? Très bien, je vais m'en occuper.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "Ah, merci, capitaine ! Je suis sûr qu'il vous écoutera comme un marin écoute un marin ! Faites-lui laisser ma soeur tranquille pour toujours ! Nous ne sommes pas riches mais nous vous paierons suffisamment pour vos peines !";
			link.l1 = "Très bien, très bien... Je suis en route pour résoudre vos problèmes. Attendez-moi !";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "Et alors ? As-tu parlé avec ce pirate ? Nous laissera-t-il tranquilles ?";
			link.l1 = "Attends un peu. Je m'en charge.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "Que veux-tu ? Ne vois-tu pas que je me repose ici ?";
			link.l1 = "Eh bien, eh bien... Voici le grand seigneur des chopes de bière, voleur de filles et tempête de cette petite ville en chair et en os, ai-je raison ? Et serais-tu aussi courageux en dehors de la ville ? Près du phare, un duel, dans deux heures ?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "Oh-ho-ho ! Prétends-tu être un héros ? Qu'importe, mon gars, je suis de bonne humeur aujourd'hui alors je te pardonne. Va m'acheter quelques pintes de bière !";
			link.l1 = "Je ne suis pas ton pote. Dois-je me répéter pour un imbécile comme toi ? Aurais-tu assez de courage pour te présenter à un duel comme tu en as pour te montrer à la taverne ?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "Tu me defies ?! Qu'est-ce qui ne va pas chez toi ? T'en as marre de la vie, tu veux mourir, gredin ? Très bien, si tu le veux vraiment, je marcherai jusqu'au phare, je t'arracherai les tripes et ensuite je détruirai cette maudite taverne aussi !";
			link.l1 = "La parole est bon marche, les epees ne le sont pas, alors n'oubliez pas d'en apporter une !";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "Et alors ? As-tu parlé avec ce pirate ? Nous laissera-t-il tranquilles ? Ma sœur m'a dit qu'il avait quitté la taverne et n'était pas revenu...";
			link.l1 = "Je l'ai fait. Le gaillard était un peu grossier, mais mes arguments étaient tout à fait raisonnables et persuasifs. Ta soeur n'a plus rien à craindre maintenant.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "C'est... est-ce terminé? Pouvons-nous respirer librement maintenant? Merci, capitaine! Et où... où est ce vaurien??";
			link.l1 = "Il... est sur son navire. Il a décidé de quitter cette ville dès que possible.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "Vous avez rendu un grand service aux citoyens de cette colonie ! Tenez, prenez cette récompense pour votre aide ! Elle est assez modeste, mais vous gagnerez le respect de tous mes amis et, croyez-moi, j'en ai beaucoup !";
			link.l1 = "Mes remerciements ! Bonne chance à toi et à ta sœur. Je lui souhaite de se marier avec un homme honorable. Adieu !";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "Oh, vraiment ? Et comment comptes-tu m'arrêter ?";
			link.l1 = " Avec mon epee bien sur, c'est la seule maniere convenable pour un cochon insolent comme toi.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "Splendide ! Je vous attendrai près du phare dans deux heures.";
			link.l1 = "Super ! J'y serai à coup sûr.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "Sors de mon chemin, lâche !";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "Capitaine, le salaud n'est pas si simple, Tom, mon vieil ami, est mort en duel contre lui, accusé de tricherie aux cartes ! Il était innocent, je le jure. Mais le gouverneur a dit qu'il n'y avait pas de crime dans ce maudit duel.";
			link.l1 = "Hm... C'est toute la faute de ton ami. Tricher aux cartes peut mal finir pour ta santé.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "Oui? Il y a déjà eu quatre tricheurs à la carte rien que ces deux dernières semaines dans notre ville. Et ils ont tous essayé de tromper notre noble? Que dirais-tu de cela? Selon moi, c'est ce noble qui est le tricheur. Si tu ne me crois pas, va donc vérifier par toi-même.";
			link.l1 = "Vous voulez jouer avec lui ? Non, je n'aime pas jouer. Pas question.";
			link.l1.go = "exit";
			link.l2 = "Je suppose que je vais le faire... Quelque chose ne va vraiment pas ici.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "Capitaine, moi et mes amis avons rassemblé une somme pour payer celui qui démasquera ce noble, et se vengera de lui pour tous ses actes. Je vous attendrai en ville pour vous donner votre récompense une fois la tâche accomplie.";
			link.l1 = "Je le ferai si ce que tu dis est vrai.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "Mes respects, monsieur ! Je vois un homme noble et peut-être... un joueur ? Envie d'une partie ?";
			link.l1 = "D'accord ! Parlons des enjeux. Que dirais-tu de 50 pièces ?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "Vous vous moquez probablement de moi ? Vous ne les avez pas !";
				link.l1 = "Tu as raison...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "Les enjeux sont indifférents, nous allons jouer, c'est la meilleure partie. J'ai presque oublié à quoi ressemblent les cartes, à cause des idiots locaux.";
				link.l1 = "Eh bien, commençons.";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "Alors, la mise est de 50 pièces.";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "Attendez un peu, qu'est-ce que c'est?.. Impossible! Monsieur, vous êtes un tricheur! Rendez-moi mes pièces!";
			link.l1 = "Vous devez avoir de solides raisons de me blâmer,  "+GetAddress_FormToNPC(NPChar)+" . Tu ferais mieux de les abattre tout de suite, ou c'est un duel !";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "Ah, comme ça ? Très bien, un duel alors ! Aujourd'hui, dans deux heures, près du phare !";
			link.l1 = "Marché conclu !";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "Des nouvelles, capitaine ?";
			link.l1 = "Tu avais raison, on m'a aussi accusé de tricherie, alors j'ai dû pourfendre le salaud en duel.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "Voià maintenant ? Je le savais ! Un grand merci de la part de moi et de mes amis ! Tenez, prenez votre récompense, capitaine.";
			link.l1 = "Merci.";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "Vous ai-je dit que je suis venu ici pour postuler à un poste de maître d'escrime ? Non ? Eh bien, le gouverneur local cherche un précepteur pour son neveu et cela me convient parfaitement. Je connais les rudiments de cet art, mais je ne l'ai jamais pratiqué en situation réelle. J'avais presque le poste en poche, mais il s'est avéré que le marchand local a rencontré un problème, un vaurien à l'air dangereux le menace. Le gouverneur m'a donné l'ordre de régler cette affaire afin de tester mes compétences professionnelles.";
			link.l1 = "Fais-le alors. Adieu.";
			link.l1.go = "exit";
			link.l2 = "Et que veut ce vaurien du marchand et pourquoi as-tu besoin de moi?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "Je pensais que cet homme était un mercenaire et que l'on pouvait toujours conclure un accord avec des mercenaires. Vieilles dettes ou peu importe... Mais cet homme était sérieux dans ses intentions de continuer à faire pression sur le marchand. Je voulais te demander d'aider le marchand et moi en le sauvant du mercenaire et en accomplissant les ordres du gouverneur\nJ'ai vraiment besoin de ce poste et je ne peux pas me débarrasser du mercenaire par moi-même. S'il te plaît, aide-moi et je te donnerai chaque pièce que j'ai économisée ou je serai contraint de quitter la ville en disgrâce !";
			link.l1 = "Bien, bien, je vais t'aider... 'maître d'escrime'.";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "Que veux-tu ? Ne vois-tu pas que je suis occupé ?!";
			link.l1 = "Embeter quelque marchand respectable et faire du boucan !?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "Bah ! Encore un protecteur ? Ce sera moins cher de me payer, plutôt que d'engager des gardes tous les jours. Je n'aime pas vraiment le travail de tueur par rapport à celui de recouvreur de dettes, alors si tu es un tel héros, viens au phare et nous nous mesurerons dans un duel. Et si tu ne l'es pas, ne t'avise plus de m'importuner.";
			link.l1 = "D'accord ! Je t'attendrai là-bas.";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "Il semble que tu sois encore plus lâche que moi...";
			link.l1 = "Oui, je le suis.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "Des nouvelles, capitaine?";
			link.l1 = "Le mercenaire est mort. J'espère que le poste est désormais le vôtre ?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "Oh, capitaine, mes remerciements ! Prenez votre récompense et je ferai rapport à notre gouverneur !";
			link.l1 = "Adieu... maître.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "Encore un ?";
			link.l1 = "À la tienne.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "Et plus encore !";
			link.l1 = "Attends un peu ! Où te précipites-tu ?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "Au diable les questions ! Bois !";
			link.l1 = "D'accord, mais peut-être me diras-tu plus tard ce qui t'est arrivé ?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "Es-tu vraiment intéressé ? Alors écoute tant que je peux encore parler ! Je ne pourrai plus m'exprimer dans quelques jours car je serai mort... Oui, mort ! Et c'est le rhum qu'il faut blâmer. Beaucoup de rhum et cet officier, apparemment envoyé par le diable au-dessus de ma tête !\nBien sûr, je ne me battrai pas avec le meilleur escrimeur de notre garnison et de toute la ville si j'étais sobre ou du moins pas aussi ivre. Mais maintenant ? Je suis condamné, fichu et je suis mort ! Je suis un tel imbécile...";
			link.l1 = "Oui, c'était trop stupide. Mais vous vous comporterez probablement plus intelligemment à l'avenir... si vous survivez au duel, bien sûr. Adieu.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "Se soûler n'est pas la meilleure option non plus, officier. Je suis sûr qu'une solution à ce problème existe.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "Quelle sorte de solution? Déserter et perdre ma réputation et mon uniforme d'officier? Ou me suicider pour éviter d'être découpé comme un cochon? Quel sera votre conseil?";
			link.l1 = "Ni l'un ni l'autre. Je vais vous aider et j'essaierai d'empêcher votre adversaire de vous infliger des dégâts avant l'heure de votre duel. Où puis-je le trouver ?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "Es-tu sérieux ? Tu vas le faire ?! Oh, je te jure, je te récompenserai comme il se doit !\nIl peut être trouvé en ville. Sa maîtresse vit ici, tous les officiers ont entendu parler d'elle, mais hélas, son adresse est inconnue... Donc, je parie que tu peux le trouver là aussi.";
			link.l1 = "Cela suffit. Attends-moi ici. Je vais aller discuter avec ce... 'meilleur bretteur'.";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "Avez-vous des nouvelles pour moi, monsieur ? Bonnes ou... ne sont-elles pas si bonnes ?";
			link.l1 = "Je n'ai pas encore de nouvelles. Attendez ici. Tout ira bien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "Avez-vous des nouvelles pour moi, monsieur ? Bonnes ou... ne sont-elles pas si bonnes ?";
			link.l1 = "C'est fini. Votre adversaire potentiel ne pourra plus nuire à quiconque... Vous êtes en sécurité maintenant. Mais j'espère que vous tirerez une leçon de cet événement et que vous ne serez pas agressif envers des gens que vous ne connaissez pas.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "N'es-tu pas en train de te moquer de moi, n'est-ce pas ? Je... Je suis vraiment reconnaissant, "+GetAddress_Form(NPChar)+"  ! Tenez, prenez tout ce que j'ai. C'est mon salaire, prenez tout !\nUne leçon, vous dites ? Oui, sacrebleu, vous avez raison ! Cela ne se reproduira plus jamais ! Je vous le promets, et merci encore de m'avoir donné une autre chance !";
			link.l1 = "Très bien alors. Adieu, officier...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "Merci encore, "+GetAddress_Form(NPChar)+", pour votre aide !";
			link.l1 = "Tu es toujours le bienvenu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "Eh, que diable ? Que fais-tu dans les appartements de ma dame ? Va-t'en d'ici ou je te tirerai dehors par la force !";
			link.l1 = "Je vais où bon me semble et je n'ai pas l'intention de te dénoncer pour un tel comportement ! Par la force ? Essaye donc !";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "Quelle insolence ! Effronterie inouïe ! Monsieur, vous vous trompez vraiment ! Quittez cette maison immédiatement ou je jure que vous regretterez d'être en vie !";
			link.l1 = "Les paroles ne coûtent rien ! C'est toi qui le regretteras, pas moi, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "Vraiment? Prenez garde alors! Si je vous tue dans cette maison, ce sera un meurtre. Donc votre mort ne ternira pas mon nom, les hommes d'honneur règlent ce genre d'affaire près d'un phare !\nJe vous défie, "+GetAddress_Form(NPChar)+", espèce d'insolent ! Tu répondras de tes paroles ! Alors, un duel dans deux heures ?";
			link.l1 = "D'accord, "+GetAddress_FormToNPC(NPChar)+" gars audacieux.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "Alors assure-toi d'y être au bon moment. Tu as encore le temps de commander un requiem à notre prêtre.";
			link.l1 = "Un requiem pour toi ? Tu ne vaux pas un seul peso. À bientôt près du phare !";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "Fiche le camp !";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Vous parlez du gouverneur ? Ha ! 'Le jugement de Dieu', c'est ce que le gouverneur m'a dit en réponse à mes plaintes ! Duel ! Qu'en pensez-vous ? Je suis juste un planteur tranquille, amoureux de la paix, pas un bandit ni un combattant.  Cela sera un meurtre, pas un duel ! Et vous, sans aucun doute, êtes meilleur que moi dans ce genre de choses. Par conséquent, je vous demande d'agir en tant que mon représentant pour le duel à venir. Croyez-moi, je ne resterai pas en dette.";
			link.l1 = "Quand est le duel ?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "Aujourd'hui avant minuit près du phare. M'aideras-tu?";
			link.l1 = "D'accord, je t'aiderai. Attends-moi en ville !";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "Dis-moi ce qui s'est passé là-bas ? Est-ce que nous... Je suis désolé, as-tu gagné ?";
			link.l1 = "Je suis sûr qu'il vous intéressera de savoir qu'il y avait une embuscade. Peut-être que votre voisin a décidé de se réassurer en invitant quelques représentants de plus au lieu d'un, et tous étaient des bandits aguerris. Heureusement, je suis un escrimeur expérimenté.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "Quel salaud ! Maintenant, je suppose que notre gouverneur n'aura aucune raison de refuser ma demande d'arrêter le vaurien ! Merci ! Prenez votre récompense et je dois aller à la résidence.";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "C'est amusant de jouer sans bugs, puisque ces saloperies sont difficiles à trouver.";
			link.l1 = "Détends-toi, j'informerai les développeurs.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "Ah, te voilà. Voici mes amis et seconds. On commence ?";
					link.l1 = "Je suis à votre service !";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "Tous sont rassemblés. Es-tu prêt?";
					link.l1 = "Oui, nous pouvons commencer !";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "Enfin! Je pensais déjà que j'avais dû marcher un si long chemin pour rien... Finissons-en vite, j'ai laissé une chope de rhum et une belle donzelle chaude à la taverne!";
					link.l1 = "Je suis sûr que tu n'auras plus besoin de l'un ou de l'autre !";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "Alors, tu as décidé de venir ? Enfin ! Commençons alors !";
					link.l1 = "Ne te précipite pas ainsi, tu pourrais tomber sur une lame.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "Et voici mes seconds, monsieur. Prépare-toi à mourir !";
					link.l1 = "Après vous.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "Nous y voilà. Préparez votre épée, monsieur !";
					link.l1 = "Volontiers, que le meilleur homme gagne !";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "Excellent, tout le monde est arrivé... Commençons, monsieur !";
					link.l1 = "Dansons !";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "Et qui es-tu ? Tu n'as pas l'air d'un citoyen ordinaire, l'ami...";
					link.l1 = "Alors ? J'ai un duel arrangé avec toi ?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "Ha ! Un duel ! Il semble que tu sois notre client. Les gars, poignardons-le et allons chercher notre récompense. Eventrez-le !";
			link.l1 = "Une embuscade ? Quelle pathétique tentative, vous aurez besoin de bien plus que cela pour m'abattre...";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "N'imagine point que nous te laisserons occire notre ami et t'en tirer ainsi ! Aux armes !";
				link.l1 = "J'aurais dû m'attendre à cela de la part d'un salaud aussi misérable !";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "Capitaine, l'honneur est rétabli, vous avez gagné. Mais permettez-moi de vous donner un bon conseil - quittez la ville et ne revenez pas ici pendant quelque temps...";
				link.l1 = "Et quel est le problème ??";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "C'était tout par honneur et maintenant allons-y et prenons notre ami.";
				link.l1 = "Bien sûr, je ne vous arrêterai pas...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "Le problème, c'est que vous avez tué un serviteur de notre commandant. C'était un mauvais homme et personne ne regrettera sa mort... mais le commandant l'aimait vraiment et il ne vous pardonnera jamais la mort de son ami.";
			link.l1 = "Merci pour un conseil, je vais sûrement en tenir compte. Adieu.";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
