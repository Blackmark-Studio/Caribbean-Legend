// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous ? Demandez donc.","Je vous écoute, quelle est la question ?"),"C'est la deuxième fois que vous essayez de demander...","C'est la troisième fois que vous essayez de demander...","Quand cela va-t-il se terminer ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous continuez à me déranger !","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et mauvais moment."),"Vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Votre Excellence, je suis ici au sujet de l'officier emprisonné, Lope Montoro...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Vous avez déjà tout pris. Que voulez-vous de plus ?","Y a-t-il quelque chose que vous n'avez pas encore pris ?");
            link.l1 = RandPhraseSimple("Je regarde juste autour...","Je vérifie juste, j'ai peut-être oublié de prendre quelque chose...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Maudits ladrons ! Vous osez attaquer La Havane ?! Que voulez-vous ?!";
			link.l1 = "Pense un peu, tu comprendras.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "L'or, bien sûr ! A quoi d'autre pourraient s'intéresser des vauriens comme vous, sinon à l'or ?! Et nous n'en avons pas... Juste quelques mesures dans le magasin.";
			link.l1 = "Ha-ha... Non, nous ne sommes pas intéressés par l'or. Nous sommes venus ici pour l'ivoire... le noir. Me comprenez-vous?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && int(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ha ! J'ai soupçonné que vous étiez venu ici pour des esclaves. Mais ils sont situés dans le fort. Nos renforts arrivent maintenant et votre bande sera détruite en un rien de temps.";
				link.l1 = "Merde ! Très bien, restez ici et ne bougez pas... Éloignons-nous d'ici ! Putain...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "Mais comment... Comment le saviez-vous ?";
				link.l1 = "Ha ! Seul un imbécile pourrait rassembler 5000 esclaves en un seul endroit et espérer que personne ne le saurait. Ils puent d'ici jusqu'à cette satanée Tortuga... J'espère que vous comprenez que nous allons vous les retirer.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Très bien, vous avez gagné de toute façon et nous devons céder à votre violence. Mais n'espérez pas échapper à la justice après ce pillage et après avoir coulé deux navires de guerre espagnols.";
			link.l1 = "Ne te gonfle pas comme ça ou tu vas avoir une crise cardiaque. Assieds-toi ici et ne bouge pas...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(int(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(int(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(int(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "Comme c'est curieux... encore des plaintes ?";
			link.l1 = "Non-non, bien au contraire, votre Excellence. Lope est un vieil ami d'armée, nous avons combattu ensemble en Europe... J'aimerais beaucoup l'aider, et je suis venu demander votre assistance.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "Hm... Eh bien, je suppose que, puisque vous êtes venu à moi, vous connaissez déjà cette... histoire absurde ?";
			link.l1 = "Je le fais, votre Excellence.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Je vous suggère de contacter don Rosario Gusman. Lui, tout comme vous, souhaite aider don Lope Montero. Il a essayé de contacter la victime, cependant, les négociations n'ont pas porté leurs fruits. Rencontrez-le, il vous expliquera les détails. Vous pouvez trouver don Rosario dans les rues de quatre à huit heures de l'après-midi. Il effectue une inspection complète des postes de garde de la ville chaque jour.";
			link.l1 = "Gratitude, votre Excellence !";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
