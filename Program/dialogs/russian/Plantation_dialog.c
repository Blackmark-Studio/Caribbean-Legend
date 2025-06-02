// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
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
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Я так устал - просто с ног валюсь.", "Нет больше сил так жить!"), RandPhraseSimple("Эта работа слишком тяжёлая для меня.", "Надсмотрщики уже не оставили живого места на моей шкуре!"));				
			link.l1 = RandPhraseSimple("Сочувствую, приятель.", "Мне жаль тебя.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Слушай, отстань от меня!", "Отвали."), RandPhraseSimple("Что тебе от меня нужно?!", "Катись к чёрту!"));				
			link.l1 = RandPhraseSimple("Гм...", "Ну-ну...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Все вопросы - к управляющему плантацией.", "Только не отвлекай рабов от работы своими разговорами, приятель."), RandPhraseSimple("Моя задача - гонять этих бездельников.", "Ну и жарища же сегодня... впрочем, как и всегда."));
			link.l1 = RandPhraseSimple("Понятно...", "Ясно...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("VOICE\Russian\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Пираты на нашей плантации?! Ну дела... Хватай его!!", "Это пират!! Держи его!!!");
					link.l1 = RandPhraseSimple("Пират, ну и что?..", "Хех, попробуйте схватить.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Хо-хо, да ведь ты ходишь под флагом "+NationNameGenitive(sti(pchar.nation))+"! Думаю, комендант обрадуется, когда мы сдадим ему тебя!", "Так-так, что-то у нас тут "+NationNameAblative(sti(pchar.nation))+" завоняло! Шпионишь, мерзавец? Пора тебя познакомить с нашим комендантом!");
				link.l1 = RandPhraseSimple("Сейчас я тебя познакомлю с моей саблей.", "Думаю, что я сначала сдам тебя чертям.");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("VOICE\Russian\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Пират?! Ну дела... Хватай его!!", "Это пират!! Держи его!!!");
						link.l1 = RandPhraseSimple("Да, пират, ну и что?..", "Хех, попробуйте схватить...");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Кто ты и что тебе здесь нужно?", "Стой! Что ты забыл здесь?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Я хочу пройти к управляющему плантацией для обсуждения торговых сделок. У меня есть торговая лицензия.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Я хочу пройти к управляющему плантацией для обсуждения торговых сделок.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Вызывающий доверие) Достопочтимые сеньоры, я здесь ради честной и взаимовыгодной торговли. Прошу, пропустите к владельцу плантации.";
						link.l2.go = "mtraxx_soldier_1";
						notification("Вызывающий доверие", "Trustworthy");
					}
				}
				else
				{
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Кто ты и что тебе здесь нужно?", "Стой! Что ты забыл здесь?");
					link.l1 = "Я хочу пройти к управляющему плантацией для обсуждения торговых сделок.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = "Лицензия? Постой-ка... Не смеши! Я узнал тебя! Твои портреты висят в каждой казарме, и за твою поимку обещана хорошая награда. Взять его!";
				link.l1 = RandPhraseSimple("Аргх!..", "Ну, ты сам напросился...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("VOICE\Russian\soldier_arest_1.wav");
				dialog.text = "Сейчас посмотрим... Ха! Твоя лицензия просрочена и поэтому недействительна. Пожалуй, надо сдать тебя в комендатуру, голубчик...";
				link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "Хорошо. Можешь проходить. Веди себя прилично и не приставай к рабам, а то им достанется из-за тебя.";
			link.l1 = "Не беспокойся, приятель.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
            dialog.text = "Торговых сделок? Ха-ха! Меня не проведёшь! Да от тебя на милю несёт "+NationNameAblative(sti(GetBaseHeroNation()))+"! Шпионишь, мерзавец? Пора тебе познакомиться с нашим комендантом.";
			link.l1 = "Нет, это тебе пора познакомиться с моей саблей.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Хорошо. Можешь проходить. Веди себя прилично и не приставай к рабам, а то им достанется из-за тебя.";
			link.l1 = "Не беспокойся, приятель.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Давай, проходи уже, не стой, как истукан!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "По какому делу зашли, сеньор?";
				link.l1 = TimeGreeting()+", сеньор. У меня к вам деловое предложение. В трюмах моего корабля находятся рабы, 50 штук. Не желаете ли их приобрести по сходной цене?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "По какому делу зашли, сеньор?";
			link.l1 = "Просто гулял по окрестностям Маракайбо и заглянул на вашу плантацию. Я уже ухожу.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "А, это опять вы, сеньор. Как ваши дела?";
				link.l1 = "Я к вам с деловым предложением. У вас на плантации производят сахар и какао. Я хочу приобрести вашу продукцию, но не за деньги, а в обмен на мои товары. Может, поторгуемся?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "А, это опять вы, сеньор. Как ваши дела?";
				link.l1 = "Я к вам с деловым предложением. У вас на плантации производят сахар и какао. Я хочу приобрести вашу продукцию, но не за деньги, а в обмен на мои товары. Может, поторгуемся?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "А, это опять вы, сеньор. Как ваши дела?";
			link.l1 = "Спасибо, всё отлично...";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Вынужден вас огорчить, сеньор, но в данный момент наша плантация в рабах не нуждается. Недавно капитан Эдуардо де Лосада обеспечил наши потребности висельниками-пиратами, захваченными им в боевом рейде. Так что...";
			link.l1 = "Пираты работают на вашей плантации? Ох, сеньор, и как вы можете спать спокойно?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "А, давайте... Я куплю ваших рабов. Вот только мне кажется, что вы не тот за кого себя выдаёте. Пройдёмте со мной в комендатуру, голубчик, и если я ошибаюсь, то полностью покрою ваши моральные издержки. А сейчас прошу меня извинить. Стража!";
				link.l1 = RandPhraseSimple("Мечтай, я живым не дамся!", "Только через мой труп!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Охрана у нас хорошая, так что бунта бояться нечего. Но в чём-то вы правы: эти канальи совсем не желают нормально работать. Я бы не покупал их, но дон губернатор так настойчиво просил уважить дона де Лосада... да и цену тот установил совсем невысокую.";
			link.l1 = "Понятно. Придётся идти в Лос-Текес... Да, сеньор, вы не позволите мне немного погулять по вашей плантации и осмотреть её? Возможно, я бы приобрёл вашу продукцию на продажу...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Вы торговец?";
			link.l1 = "Ну, в какой-то степени да. Профессиональным купцом я себя не назову, конечно, но от выгодной негоции никогда не отказываюсь.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Это интересно. Ну что же, я не возражаю против вашего присутствия. Гуляйте, смотрите. Если что-то надумаете - приходите, обсудим.";
			link.l1 = "Спасибо, сеньор. Думаю, мы ещё продолжим нашу беседу.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Почему бы и нет? Какие товары вы предлагаете на обмен?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "Пятьсот ящиков кофе.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "Пятьсот ящиков ванили.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "Пятьсот ящиков копры.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Пятьсот ящиков кофе? Так-так... Давайте прикинем... (считает) Я готов обменять ваш кофе на "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" мешков сахара и "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+" ящиков какао. Согласны?";
			link.l1 = "М-м-м... Я рассчитывал немного на большее... Но ладно. Я согласен!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Вызывающий доверие) Уважаемый, позвольте возразить! Я привёз вам товар высочайшего качества. И знаю цену каждой единицы и за него, и за то, что вы предлагаете в обмен. Я заслуживаю чуть большего количества груза с вашей стороны, сеньор. И всё равно эта сделка остаётся выгодной для вас, вы сами это знаете.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Вызывающий доверие", "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Пятьсот ящиков ванили? Так-так... Давайте прикинем... (считает) Я готов обменять вашу ваниль на "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" мешков сахара и "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+" ящиков какао. Согласны?";
			link.l1 = "М-м-м... Я рассчитывал немного на большее... Но ладно. Я согласен!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Вызывающий доверие) Уважаемый, позвольте возразить! Я привёз вам товар высочайшего качества. И знаю цену каждой единицы и за него, и за то, что вы предлагаете в обмен. Я заслуживаю чуть большего количества груза с вашей стороны, сеньор. И всё равно эта сделка остаётся выгодной для вас, вы сами это знаете.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Вызывающий доверие", "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Пятьсот ящиков копры? Так-так... Давайте прикинем... (считает) Я готов обменять вашу копру на "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" мешков сахара и "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+" ящиков какао. Согласны?";
			link.l1 = "М-м-м... Я рассчитывал немного на большее... Но ладно. Я согласен!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Вызывающий доверие) Уважаемый, позвольте возразить! Я привёз вам товар высочайшего качества. И знаю цену каждой единицы и за него, и за то, что вы предлагаете в обмен. Я заслуживаю чуть большего количества груза с вашей стороны, сеньор. И всё равно эта сделка остаётся выгодной для вас, вы сами это знаете.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Вызывающий доверие", "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Очень хорошо! Для нас обоих это выгодная сделка! Когда произведём обмен?";
			link.l1 = "Мне надо подготовить товар. Да и вам, наверное, тоже. Начнём завтра в четыре часа вечера - как раз к закату солнца мои люди перенесут вам на плантацию все ящики.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Договорились. Тогда до завтра, сеньор!";
			link.l1 = "До завтра...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "Ну вот, сеньор, мы и закончили. Если вам понадобится ещё сахар, или какао - жду вас. На продажу, на обмен - всегда пожалуйста!";
			link.l1 = "Если прибыль с этой негоции окажется достаточно весомой - мы с вами ещё встретимся. А сейчас позвольте откланяться - мне пора.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Всего доброго, сеньор!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Не похож ты на торговца, иностранец. Покажи лицензию.";
			link.l1 = "Увольте! Разве какая-то бумажка решает, торговать человеку, или нет? Они стоят слишком дорого! Я недавно этим занимаюсь, но торговля уже успела стать моей страстью! Пустите меня, и я хорошо о вас двоих выскажусь главному.";
			link.l1.go = "mtraxx_soldier_2";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Язык у тебя подвешен, жадюга. Ну хорошо, проходи. И не забудь сказать хозяину, то это мы тебе порекомендовали к нему зайти.";
			link.l1 = "Непременно. Благодарю.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "А вы хорошо ориентируетесь в актуальных ценах капитан! У вас явный талант к негоциации, пусть вы и выглядите, как новичок. Что ж, если вы и правда привезли первоклассный товар, то я и правда должен вам отгрузить чуть больше.";
			link.l1 = "Конечно, первоклассный, клянусь честью! Есть ещё кое-что, что я хотел бы у вас приобрести, сеньор.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "О, вот как? И что же?";
			link.l1 = "Кто. Не что. Я хочу купить у вас одного из ваших рабов в качестве домашнего слуги, это возможно?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Без проблем. Сейчас подберём вам кого-нибудь.";
			link.l1 = "Меня интересует конкретный раб. Тот, что со смазливой мордашкой. Такого не стыдно взять с собой на люди или держать рядом во время собственных приёмов - разливать и подавать вино дамам. Он представился мне, как Жан Пикар, мы уже поладили.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Да, на Жана Пикара есть спрос. И не только для розлива вина. Со мной уже связался некий влиятельный господин, англичанин. Один человек от него, как же его звали, Патторнсон? В общем, он доставил мне письмо.";
				link.l1 = "Однако ни Патторнсон, ни этот человек не явились пока что. А я готов выкупить у вас этого вашего Жана здесь и сейчас. Назовите цену - дамы уже ждут!";
				link.l1.go = "mtraxx_PlantVykup_10";
				notification("Проверка пройдена", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ах, поладили. Конечно, понимаю. Но, боюсь, вынужден вам отказать - Жан Пикар не продаётся. Мне жаль, сеньор.";
				link.l1 = "Вот как? Почему же? Я готов вам хорошенько за него заплатить. Скажите лишь, сколько.";
				link.l1.go = "mtraxx_PlantVykup_6";
				notification("Недостаточно развит навык (70)", SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Бесценно. У него уже есть покупатель. Которому я уже обещал эту сделку. Больше мне добавить нечего. Предлагаю вернуться к нашей изначальной сделке и произвести обмен.";
			link.l1 = "Хм, как скажете, сеньор.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Очень хорошо! Для нас обоих это выгодная сделка! Когда произведём обмен?";
			link.l1 = "Мне надо подготовить товар. Да и вам, наверное, тоже. Начнём завтра в четыре часа вечера - как раз к закату солнца мои люди перенесут вам на плантацию все ящики.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Договорились. Тогда до завтра, сеньор!";
			link.l1 = "До завтра...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Как вам будет угодно, сеньор. Цена, как понимаете, кусается. Пять сотен дублонов.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Это не проблема - прошу. Хороший домашний слуга ценнее, чем обычный раб - ну, это вы и так знаете.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "Загнули вы, конечно, сеньор. Но очень уж мне приглянулся этот раб. Ждите здесь. Если явится Патторнсон - скажите, что Пикара уже купили, ха-ха-ха!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Ваша правда. Я обо всём договорюсь, Пикар будет ожидать вас на выходе.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Если он явится со всей суммой - то навряд ли. Так что поспешите, капитан.";
			link.l1 = "Скоро вернусь.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Вы принесли золото за Жана Пикара, капитан? Время не терпит.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Мне это хорошо известно. Поэтому держите, вот ваше золото. А вы мне - моего нового домашнего слугу.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Всё ещё собираю - вы сами назначили такую цену, сеньор.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Первый раз вижу, чтобы человек столько тратил на приобретение слуги. Но одеты вы хорошо, видимо, привыкли к большим покупкам. Я сообщу своим людям, и Пикара приведут к дому.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
