// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("В городе поднята тревога. Похоже, и мне пора браться за оружие...", "Уж не за тобой ли носится вся городская стража?.. Ко мне, солдаты!!!", "У меня приюта ты не найдёшь. Зато найдёшь несколько дюймов холодной стали под ребро!"), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","мерзавка") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца! Стража!!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Похоже, тебе жить надоело...", "Хех, и не живётся же спокойно мирным гражданам " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Отправляйся в ад!", "Хех, жить тебе осталось несколько секунд..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "А-а-а! А, это вы... Кто вы так"+GetSexPhrase("ой","ая")+"? Что вы забыли на кладбище?";
				link.l1 = "Меня зовут "+GetFullName(pchar)+". А вы кто такой и что здесь делаете? И почему вы так перепугались?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "Ну как? Вы посмотрели? Убедились?";
				link.l1 = "Нет, я ещё не спускался в крипту. Подожди, я всё проверю.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "Ну как? Вы посмотрели? Убедились?";
				link.l1 = "Ага, убедил"+GetSexPhrase("ся","ась")+"! Вы были правы!";
				link.l1.go = "Lantern_10";
				link.l2 = "Всё оказалось немного не так, как вы предполагали.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Добрый день, моряч"+GetSexPhrase("ок","ка")+"! Меня зовут "+GetFullName(npchar)+", и я - единственный живой обитатель сего места, хе-хе. Впрочем, все там будем... Зачем пожаловали?", "Здравствуйте! Давненько я не видал живого человека... Позвольте представиться - "+GetFullName(npchar)+", а это кладбище - моё последнее пристанище в этой жизни. Видимо, тут же меня и похоронят. Чем могу служить?");
				link.l1 = "Здравствуй, "+npchar.name+"! Моё имя - "+GetFullName(pchar)+", и я капитан. Вот, ходил"+GetSexPhrase("","а")+" по джунглям и забр"+GetSexPhrase("ёл","ела")+" сюда. Думаю, загляну в этот уютный домик, посмотрю, кто не боится здесь жить...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, "+GetSexPhrase("мой старый знакомый","моя старая знакомая")+", капитан "+GetFullName(pchar)+"! Проходите, проходите!";
				link.l1 = "Приветствую, дружище! Рад"+GetSexPhrase("","а")+" тебя видеть. Тебе ещё не снятся по ночам пляшущие скелеты и мертвецы с медяками на глазах?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "А чего же тут бояться-то, капитан? Бояться живых надо, а мёртвые не кусаются. Эх! Когда-то у меня была совсем другая жизнь, а теперь вот моя забота - это кладбище. Приглядываю за могилками. А также приторговываю всякой всячиной...";
			link.l1 = "А чем ты торгуешь, скажи пожалуйста?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "Что привело вас ко мне на сей раз?";
			link.l1 = "Давай посмотрим, что у тебя есть сегодня в продаже.";
			link.l1.go = "trade";
			link.l2 = "Я вот что "+ GetSexPhrase("хотел","хотела") +" спросить...";
			link.l2.go = "quests";
			link.l3 = "Ничего серьёзного. Просто "+GetSexPhrase("зашёл","зашла")+" поздороваться.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "У меня много свободного времени, поэтому я люблю побродить по окрестным джунглям и собрать полезные травки. Потом я продаю их в городе. За них платят сущие гроши, но всё же лучше, чем ничего. Иногда я нахожу занятные камни. Нет, не самоцветы, но мастеровым они почему-то бывают нужны\nНу, и самые разные предметы мне дают мои друзья...";
			link.l1 = "Друзья? То есть, ты перепродаешь то, что тебе привозят?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "О-хо-хо... Нет, они мне всё предоставляют бесплатно. Какие ещё могут быть друзья у кладбищенского сторожа, если не покойники?";
			link.l1 = "Гм... ты что, обираешь мертвецов?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "Не обираю, а снимаю вещи, которые им уже не нужны. Здесь же разные люди похоронены. Многие без роду-племени и не из наших мест. Привезёт комендант из города труп - 'на, "+npchar.name+", похорони с миром'. Или бродяг каких окаянных стража перебьёт, а старый "+npchar.name+" предает их бренные тела земле по христианскому обычаю.";
			link.l1 = "Ясно. Деньги, как говорится, не пахнут. Ладно, покажи мне свои товары.";
			link.l1.go = "trade";
			link.l2 = "Понятно. Мне пора идти. Приятно было познакомиться!";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Да ты "+ GetSexPhrase("вор, милейший! Стража, держи его","воровка! Стража, держи её") +"!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи "+ GetSexPhrase("вора","воровку") +"!!!", "Стража! Грабят!!! Держи "+ GetSexPhrase("вора","воровку") +"!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Ффух, так вы просто "+GetSexPhrase("путник","путница")+"... Меня зовут "+GetFullName(npchar)+", я смотритель этого Богом забытого места.";
			link.l1 = "Зачем же вы так о кладбище? Скорее, наоборот, Господь наш именно отсюда и забирает к себе праведных после погребения.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "Зато неправедные, судя по всему, после погребения остаются здесь! Последние пару ночей по ночам из крипты доносится какой-то шум. И стоны разносятся такие, что аж дрожь берёт... Не иначе заблудшая душа покоя найти не может! Я теперь сплю только днём - а ночью ни выйти из своей сторожки не могу, ни уснуть...";
			link.l1 = "Шум, стоны? Так там же, кроме покойников, никого нет.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "Вот и я о том же, понимаете? Шли бы вы отсюда, пока привидение вас не почуяло... А то потом спать не сможете, как я.";
			link.l1 = "Хм, да, пожалуй, я лучше покину это место.";
			link.l1.go = "Lantern_04";
			link.l2 = "Может быть я смогу вам помочь? Давайте я ночью посмотрю, что там за шум?";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Вы в своём уме?! Я вижу, что у вас есть оружие, но как вы собрались сражаться им против нечисти? А если вы там и поляжете - это что же тогда, призрак на свободу выйдет, да ещё и вас к себе в слуги подымет?";
			link.l1 = "Ну, это уже суеверия...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Какие суеверия - здесь вам не благочестивая земля Европы, будь она неладна. Тут туземцы эти краснорожие, они всякое могут наколдовать - а нам тут жить теперь!";
			link.l1 = "И всё же я попробую. Дождусь ночи, а затем спущусь в крипту.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Хорошо, будь по-вашему. Но если к рассвету не вернётесь - я закрою всё на ключ, забаррикадирую и уберусь отсюда восвояси! Хоть матросом палубу драить, хоть портовым рабочим ящики таскать - но сюда всё одно не вернусь!";
			link.l1 = "Да успокойтесь вы... Всё обойдётся.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Подождите... Возьмите фонарь. У меня второй есть. А вам пригодится. Там же темень непроглядная!";
			link.l1 = "Спасибо, фонарь в таком месте и правда пригодится.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			//Log_Info("Вы получили 'Фонарь'");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			AddQuestUserData("NoiseCemetery", "sSex", GetSexPhrase("","а"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Прав? Что же там было, рассказывайте!";
			link.l1 = "Там бродил неупокоенный дух женщины! По счастью, я испросил"+GetSexPhrase("","а")+" в церкви благословения для своего клинка на умерщвление нечестивых, поэтому всё получилось. Больше этот дух вас не потревожит.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Господи, спаси наши грешные души! А я ведь говорил! А вы мне не верили!";
			link.l1 = "Да, и я искренне об этом сожалею. Но теперь всё будет хорошо: я окропил"+GetSexPhrase("","а")+" это место святой водой, и ни один дух теперь не посмеет восстать из могилы. Можете спать спокойно.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Большое вам спасибо! Вы не представляете, что это для меня значит! Вот, возьмите, пожалуйста. Здесь немного, но я не могу оставить вас без благодарности.";
			link.l1 = "Спасибо, не откажусь. Удачи вам!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			AddQuestUserData("NoiseCemetery", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "Не так? А как тогда, чёрт по... Ой, то есть, слава Богу, там всё оказалось?";
			link.l1 = "Никакого призрака там не было и в помине. Просто одна парочка выбрала этот склеп местом для своих свиданий. Их родители против этого союза, поэтому они искали, где уединиться.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Уединиться? Ну, молодёжь! Ну пусть только придут сюда ещё раз! Я либо розгами их обоих выдеру, либо закрою в этом склепе, чтобы там они и остались!!!";
			link.l1 = "Они сюда уже больше не вернутся. Я сказал"+GetSexPhrase("","а")+" им, что их маленькие шалости не на шутку пугают местного сторожа. Они не хотели этого. А замок на двери, кстати, всё равно сломан.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "Ничего, я его заменю. Ну, попадись они мне.";
			link.l1 = "Не злитесь так. Все мы были в этом возрасте. Они сюда приходили не потому, что это лучшее место для свиданий.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "Так-то оно так... А, ладно, Бог с ними. Спасибо вам, что не оставили старика в беде. Вот, возьмите, пожалуйста. Здесь немного, но я не могу оставить вас без благодарности.";
			link.l1 = "Спасибо, не откажусь. Удачи вам!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			AddQuestUserData("NoiseCemetery", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}