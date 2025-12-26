// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Добрый день. Я бы хотел"+ GetSexPhrase("","а") +" узнать, куда отправился капитан Франсуа Гонтьер на своём корвете. У меня для него важное поручение.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Я торговец, пришёл из Каракаса, и меня там ваш коллега из местного портового управления попросил передать вам какую-то корреспонденцию...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Да, я по поводу оплаты.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;
		
		case "Portobello_ratP_1":
			dialog.text = "Важное дело, говорите? Ну, раз так, давайте посмотрим. Так... Франсуа Гонтьер, корвет '" + pchar.questTemp.Slavetrader.ShipName + "'... Судя по записям, сеньор Гонтьер направился на Ямайку.";
			link.l1 = "Спасибо! Вы мне очень помогли!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "А-а, ну наконец-то! А вы, говорите, торговец? Опять они пытаются на курьерах сэкономить и откладывают отправку до последнего... Ага, ну точно! Так и есть. И вот как я должен им снарядить эскадру в такие сроки?..";
			link.l1 = "Безответственные, наверное...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Это ещё не то слово! Ну да ладно, что делать. Встретим вовремя... Это я о своём, не обращайте внимания. Слушайте, а вы случайно обратно не собираетесь?";
			link.l1 = "Ну, вообще-то я собирался продать здесь товар, а потом - да, отправиться обратно в Каракас...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Отлично! Сейчас я напишу им ответ и попрошу вас передать его обратно. Так... Доставьте его, пожалуйста, в течение десяти суток, иначе они уже не успеют ничего сделать вовремя... И назовите ваше имя.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Меня зовут "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "Меня зовут Андреас Гарсия.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Минуточку... Записал. Вот, держите. Помните: десять суток! А я пока почитаю подробнее то, что вы мне привезли.";
			link.l1 = "Да, я запомнил. Всего доброго!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Подождите-ка... Ничего не понимаю... Ещё раз, как вы сказали, вас зовут?..";
			link.l1 = "Меня?.. Ну... А почему это так важно?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Режим исследования: таймер отключён.");
			dialog.text = "Это очень важно! Здесь сказано... Так... "+n+" "+month+"... Нет, не то... 12, 50, 69, 55... Да где же... А, вот! Письмо должен доставить капитан "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". А вас, вы сказали, зовут... "+GetFullName(pchar)+"?";
			link.l1 = "Ошибка какая-то, наверное, вышла...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "Нет, ошибки быть не может. Отдайте мне ответное письмо, которое я вам дал. Нужно разобраться!";
			link.l1 = "Да ладно вам... Я его доставлю, всё будет в порядке.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Сейчас же верните мне письмо! Стража!!!";
			link.l1 = "Вот же упрямец какой!";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			if (CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				TakeNationLicence(HOLLAND);
				log_info("Торговая лицензия аннулирована!");
			}
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "Минуточку... Да, совпадает. Тогда вас же я и запишу в ответном письме. Вот, держите. Помните: десять суток! А я пока почитаю подробнее то, что вы мне привезли.";
			link.l1 = "Да, я запомнил. Всего доброго!";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "Оплаты?..";
			link.l1 = "В Каракасе ваш коллега сказал мне, что вы заплатите за доставку письма.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Нет, ну они совсем там с ума сошли! Я теперь ещё и платить за них должен!";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "И сколько они вам пообещали?";
			link.l1 = "Пять тысяч песо.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "Десять тысяч песо.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Они там, видно, решили за мой счёт жить... Мало того, что не хотят тратиться на курьеров, поручая такие дела попутным торговым судам, так ещё и расходы на меня вешают! Я напишу на них жалобу в Гавану!";
			link.l1 = "Я понимаю ваше негодование, сеньор, но мне-то как быть?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Они там, видно, решили за мой счёт жить... Мало того, что не хотят тратиться на курьеров, поручая такие дела попутным торговым судам, так ещё и расходы на меня вешают! Я напишу на них жалобу в Гавану!";
			link.l1 = "Я понимаю ваше негодование, сеньор, но мне-то как быть?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Ладно, вы не виноваты в жадности чиновников Каракаса. Но у меня с собой сейчас просто нет таких денег. А бюджет только завтра должен прийти... Подождите здесь, пожалуйста, я сейчас схожу до ростовщика - и сразу вернусь.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Режим исследования: таймер отключён.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Прошу прощения за ожидание. Вот ваши "+makeint(pchar.questTemp.SharkGoldFleet)+" песо. А за ответ в таком случае они с вами в Каракасе сами расплатятся. Скажите, что я так и передал.";
			link.l1 = "Хорошо, я передам. Спасибо вам и всего доброго!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}