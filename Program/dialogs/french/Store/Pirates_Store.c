// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Allez-y, que voulez-vous ?","Nous en parlions justement. Vous avez dû oublier...","C'est la troisième fois aujourd'hui que tu parles d'une question...","Écoutez, ceci est une boutique. Les gens achètent des choses ici. Ne me dérangez pas !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+", peut-être la prochaine fois.","D'accord, j'ai oublié pour une raison quelconque...","Oui, c'est vraiment la troisième fois...","Hum, je ne vais pas...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Ecoutez, "+npchar.name+", avez-vous vu Miguel Dichoso sur Isla Tesoro dernièrement?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = " "+npchar.name+", je suis ici de la part de Marcus Tyrex. Il a dit que vous aviez besoin d'un homme pour un travail.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+" , le 'Rosbohom' a été trouvé et capturé. Devons-nous commencer le déchargement et le comptage ?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Oui, je l'ai vu. Il a acheté des provisions pour son navire ici. C'était très récemment d'ailleurs. Vous vous êtes littéralement manqués de quelques jours. Au fait, il pourrait encore être dans cette colonie. Je ne suis pas un espion, vous savez. Renseignez-vous un peu plus et qui sait, vous pourriez bien trouver votre don.";
			link.l1 = "Très bien. Merci pour l'info !";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Précisément ! Heureusement que vous êtes arrivé à temps. Maintenant, laissez-moi vous expliquer le cœur du problème...";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(int(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "En ce moment un "+sTemp+", le vaisseau hollandais nommé 'Rosbohom', arrive dans nos eaux accompagné d'un navire de garde. Elle est chargée d'ébène et navigue depuis Willemstad pour rencontrer un autre navire de garde afin d'assurer une traversée sûre vers l'Europe. Je ne sais pas quelle route elle prend, via Sint Maarten ou via l'Espagnol, mais je connais les coordonnées de leur point de rendez-vous\nVotre mission est de trouver les Hollandais là-bas, d'aborder le marchand et de m'apporter sa cargaison. Je paierai dès que la cargaison sera livrée.";
			link.l1 = "Compris. Heure et lieu ?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = int(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = int(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+int(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" Nord et "+int(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+" Ouest. Cela doit être quelque part au Sud ou Sud-Ouest de l'Isla Tesoro, je ne suis pas bon en cela, je ne suis pas marin, mais vous l'êtes. Vous avez environ cinq jours pour faire le travail.";
			link.l1 = "Note... J'ai compris. Pas de perte de temps alors !";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Bon vent, capitaine. Je vous attendrai avec la cargaison.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = int(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = int(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(int(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", int(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", int(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Vous vous moquez de moi, jeune homme ? Vos cales ne contiennent pas une seule planche d'ébène ! C'est une tromperie insolente ! Sortez d'ici ! Je vais en informer Marcus ! Sortez !!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < int(int(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Te moques-tu de moi, garçon ? Tes cales ne contiennent que quelques échardes d'ébène ! C'est une supercherie insolente ! Va-t'en d'ici ! Je vais en informer Marcus ! Va-t'en !!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < int(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "Le Rosbohom avait au moins "+FindRussianQtyString(int(pchar.questTemp.Mtraxx.Crdn.Ebony))+" d'ébène. Pourquoi m'en as-tu apporté moins ?";
				link.l1 = "Eh bien... vous savez, j'ai dû m'en débarrasser d'une partie pendant le combat. Plus les rats, maudits soient-ils...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Très bien. Combien avez-vous ? "+FindRussianQtyString(iTotalTemp)+"Splendide ! Je vous paierai 150 pesos pour une pièce.";
			link.l1 = "150 pièces de huit ? Je suppose que cet ébène coûte bien plus cher.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Des rats ? Eh bien, eh bien... Mais d'accord. 100 pesos par pièce et vous êtes libre de partir.";
			link.l1 = "100 pesos seulement? C'est un vol!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Le vol est votre métier, capitaine, je suis un simple marchand. Prenez votre argent et ne continuons pas à nous disputer, vous avez déjà fait une belle somme en vendant une partie de ma cargaison ailleurs.";
			link.l1 = "Va te faire foutre alors !";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "Et vous avez raison, capitaine, mais d'abord, essayez de vendre des marchandises volées et je verrai combien d'autres marchands vous les paieront. Le prix qui vous est offert est très élevé. Deuxièmement, c'était mon tuyau, vous n'auriez jamais trouvé cette caravane par vous-même, de plus il y avait d'autres objets de valeur et marchandises dessus et je ne les réclame pas. Troisièmement, je vous donnerai les meilleures références aux yeux de Marcus Tyrex et cela coûte cher, croyez-moi. Et enfin, quatrièmement, un pauvre marchand doit bien vivre d'une manière ou d'une autre.";
			link.l1 = "Ho ! Je dois battre en retraite face à de tels arguments "+npchar.name+"Faisons le compte.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Splendide. Prenez vos pieces. Ce fut un plaisir. N'oubliez pas de visiter ma boutique de temps en temps. Puisse la mer vous etre favorable !";
			link.l1 = "Et toi dans ton commerce...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
