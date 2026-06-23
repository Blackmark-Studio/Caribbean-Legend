// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Недавно одним из солдат города был арестован и помещён под стражу Чарли Книппель. Он уже здесь, в одной из камер?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
			
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "Верно, а почему вы спрашиваете?";
			link.l1 = "Дело в том, что Чарли был одним из офицеров на моём корабле. Я бы хотел знать, в чём его обвиняют. Ребята, что забрали его, ничего не знают."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Правильно. Лишним людям это знать не положено. К сожалению, даже вам. Это государственная тайна, сэр.";
			link.l1 = "Значит, я так понимаю, ни о каком залоге и речи идти не может?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Именно. Понимаю прекрасно, что неприятно терять толкового человека, но ни вы, ни мы ничего не можем с этим поделать. Мне очень жаль.";
			link.l1 = "Если не залог... то что насчёт компенсации? Щедрой. Вам и всем вашим ребятам, чтобы никто не был обделён."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Взятка, значит? Это, конечно, смело с вашей стороны, капитан, но никакие деньги не спасут нас от гнева тех, кто узнает, что мы упустили Чарли.";
			link.l1 = "Возможно... Но могу я хотя бы поговорить с ним?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Почему бы и нет, в принципе. Вызволить его и сбежать вместе с ним вам всё равно не удастся, так что... прошу. Он в одной из камер. Найдёте, не заблудитесь.";
			link.l1 = "Ха, а если он расскажет мне, в чём его обвиняют, и выдаст эту самую государственную тайну, о которой вы так печётесь, господин офицер?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "На этот счёт я не волнуюсь. Ну, сами всё поймёте. Идите, поговорите со своим бывшим офицером, пока я не передумал.";
			link.l1 = "Да уж, благодарствую."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", int(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "В этом нет необходимости, капитан. Как я уже сказал, вас бросили бы в ту же клетку, что и этого болвана Чарли. Но, во-первых, господин губернатор оценил, что вы не стали препятствовать его аресту, а во-вторых, ему не очень пришёлся по душе визит ростовщика, от визга которого в приёмной едва не вылетели окна...";
			link.l1 = "Он просил меня арестовать?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "Не просил - требовал. А Его Светлости не нравится, когда от него что-то требуют. Так что этому денежному мешку было предложено убраться с глаз долой.";
			link.l1 = "Очень хорошо. А теперь..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "А теперь то же самое предлагается сделать и вам, капитан де Мор. И при этом не задавать вопросов, на которые вы всё равно не получите ответ.";
			link.l1 = "Я не уйду отсюда без Чарли Книппеля."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Прошу вас, сэр, дайте мне побеседовать с Чарли Книппелем. Или хотя бы узнать, в чём..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "В таком случае присоединитесь к нему. Причём, не в каталажке, а на том свете.";
			link.l1 = "Значит, он мёртв..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Вы чертовски догадливы, капитан. И, надеюсь, догадываетесь, что я не скажу вам ни кто, ни почему это сделал.";
			link.l1 = "Вот как?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Именно так и никак иначе. А теперь не испытывайте моё терпение - пока я не приказал бросить вас в камеру за убийство английского солдата.";
			link.l1 = "Да уж, учитывая, что выйти из ваших клеток удаётся далеко не каждому, оказаться бы там не хотелось. Желать всего доброго вам не стану."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Чарли Книппель уже ни с кем не побеседует. Разве что только с Создателем...";
			link.l1 = "Он мёртв?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "Приговор приведён в исполнение. Подробностей я вам сообщить не могу. И надеюсь, настаивать вы не станете - это может для вас плохо кончиться. И отнюдь не камерой. Я ясно выражаюсь, капитан де Мор?";
			link.l1 = "Более чем. Прощайте."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

