// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Я бы хотел поговорить с вами об одном из ваших должников.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "А что, с кем-то из них что-то случилось? Внимательно вас слушаю, сударь.";
			if (int(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Честь) Пока что, к счастью, ничего. Это Чарли по прозвищу Книппель.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l1 = "(Честь) А у вас кишка не тонка - так спокойно со мной говорить. Послали людей за моим человеком, а теперь...";
				link.l1.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Чарли? Но он больше не является моим должником. Его долг был давно уплачен, сэр.";
			link.l1 = "Вот как? А кем же, если не секрет?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "Отчего же, не секрет. Его капитаном, Ричардом Флитвудом. Настоящий джентльмен, всем бы таких друзей, как он.";
			link.l1 = "Видите ли, сейчас капитаном Чарли являюсь я. Мистер Флитвуд... перевёл его ко мне на службу. Приятно знать, что он выполнил своё обещание и заплатил вам.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Вы, сэр? Так вот почему вы спрашивали.";
			link.l1 = "Не только поэтому. Вы ведь хорошо знаете Чарли? Как и многие другие в городе. Его буквально только что арестовали, а ранее за ним посылали наёмников. У вас есть предположения, из-за чего? В конце концов, вы общаетесь с весьма... разнообразным кругом лиц.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Чарли арестован? Вы меня удивили, сэр, мне ничего об этом не известно. Как и о его... недругах. Он хороший человек.";
			link.l1 = "Не поспоришь. Что ж, спасибо и на этом. Надеюсь, комендант согласится принять от меня залог.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "Я тоже на это надеюсь. На случай, если вам будет не хватать, можете снова заглянуть - ради Чарли я предоставлю вам хорошие условия.";
			link.l1 = "Ха-ха, вы серьёзно? Видимо, ростовщик в любой ситуации таковым и останется. Я могу позволить себе залог. До свидания.";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "Послал людей? За вашим человеком? Но зачем? О чём вы?..";
			link.l1 = "Не отнекивайтесь. Лучше сознайтесь, и мы с вами всё уладим, как нормальные люди. А будете изображать удивление и устраивать подлости за моей спиной - я буду вынужден разговаривать с вами по-плохому.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "В-вы явно ошиблись!.. Стража!!! Меня грозятся убить!";
			link.l1 = "Чёрт!";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

