// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			SetAchievement("Test_Ach");
			PlaySound("VOICE\Russian\LE\Greguar\Greguar_01.wav");
			dialog.text = "Рад приветствовать вас в колониях, сударь! Позвольте представиться: "+GetFullName(pchar)+". Вы из Европы? Впервые у нас?";
			link.l1 = "Здравствуйте, месье. Моё имя — "+GetFullName(pchar)+". Да, я только-только с корабля.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Увидев благородного дворянина, я счёл своим долгом предложить помощь. Здесь, в Новом Свете, свои порядки — и их незнание может дорого стоить, а благородные люди вроде нас с вами должны помогать друг другу. Вы не поверите, сколько здесь собралось всякого рода сброда, готового предать ближнего ради горсти монет\n"+
			"Позволите мне провести вас по городу и кратко ввести в курс дела?";
			link.l1 = "Это весьма благородно, месье! Я с радостью приму ваше предложение.";
			link.l1.go = "guide_2";
			link.l2 = "Спасибо за заботу, сударь, я действительно признателен вам, но думаю, что без труда разберусь во всём сам.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Как вам будет угодно, месье. В любом случае, я был рад нашему знакомству. Благородные люди столь редки в этой глуши. Всего доброго и удачи вам!";
			link.l1 = "И вам тоже, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Замечательно! Жизнь на Карибах незатейлива, а каждое поселение построено по одним правилам. Если вы освоитесь в Сен-Пьере — освоитесь и в любом другом городе.";
			link.l1 = "";
			link.l1.go = "guide_tavern";			
		break;
		
		case "guide_tavern":
			dialog.text = "Таверна — сердце порта. Здесь вы найдёте ночлег, ром, слухи и сможете нанять матросов с офицерами. А ещё — сыграть в карты, найти работу или воспользоваться услугами контрабандистов и торговцев картами сокровищ.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Товары для личного пользования всегда можно прикупить на рынке. У оружейника — оружие, доспехи и боеприпасы, у травницы — целебные настойки. Цыганки и монахи торгуют амулетами, а старьёвщик продаёт всякое барахло, полезное тем, кто не гнушается мастерить своими руками.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Бордель. Нет лекарства для тела лучше, чем любовные утехи в объятиях умелой женщины. Если здоровье пошатнулось — загляните сюда, развейтесь, получите порцию ласки и почувствуете себя другим человеком.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Дом ростовщика. Можно занять или вложить деньги, обменять песо на дублоны. А ещё — это лучшее место, чтобы продавать драгоценности.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Тюрьма. Настоящих преступников тут немного — в основном всякий сброд. Если захотите найти работу среди отбросов общества — поговорите с комендантом. За небольшую взятку он может пропустить к камерам.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Дворец самого главного лица в колонии — губернатора. Деловые люди и капитаны заходят сюда за серьёзной работой. Быть в хороших отношениях с губернатором — большое дело, ведь от него во многом зависит, как к вам будет относиться вся его нация.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Вы куда-то торопитесь, и я вас отвлекаю?";
			link.l1 = "Ну... наверное, так. Месье, я прибыл сюда, чтобы найти своего брата. Говорят, он где-то в Сен-Пьере. Он важная птица, и наверняка известен губернатору...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "А-а, понимаю. Нашего губернатора зовут Жак Дьель дю Парке. Уверен, он примет вас без отлагательств.";
			link.l1 = "А у кого ещё я могу поспрашивать о брате? Может, не стоит тревожить Его Светлость?";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Если ваш брат действительно известен на Мартинике — поспрашивайте прохожих на улицах. Может, кто-то подскажет. Кстати, как его зовут?";
			link.l1 = "Мишель де Монпе.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "Это имя мне встречалось, но, увы, я не имел чести быть представленным лично. Попробуйте спросить в городе — или отправляйтесь прямиком к губернатору. Удачи, месье. Мы с вами ещё обязательно увидимся и поболтаем!";
			link.l1 = "Спасибо, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "О, это снова вы, мой друг! Вижу, вас допустили в святая святых Сен-Пьера — твердыню мальтийских рыцарей. По всему видно — вы птица высокого полёта. Нашли брата?";
			link.l1 = "Да уж, нашёл...";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Простите за навязчивость, месье, но мне показалось, что я не слышу радости в вашем голосе...";
			link.l1 = "Это так, сударь. Я рассчитывал убраться отсюда назад, во Францию, ближайшим судном, но судьба, похоже, решила поиздеваться надо мной: остаюсь здесь надолго... нет, чёрт возьми — на неведомо долгий срок! И, представляете, впридачу должен стать моряком, пхе!";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Почему-то я не удивлён. Я уже слышал о вашем приключении на пинасе 'Улисс'. Не унывайте — быть владельцем собственного судна и капитаном весьма почётно. Вы ведь собираетесь купить корабль?";
			link.l1 = "Да, чёрт возьми, именно это и должен сделать... Осталось только найти верфь и как-то собрать деньги. А ведь я не знаю ни где верфь, ни как управлять кораблём, ни где взять денег — ничего!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "С деньгами, увы, помочь не смогу — сам сейчас на мели. Но вот в остальных вопросах — к вашим услугам. Готовы продолжить экскурсию?";
			link.l1 = "Да, пожалуй, ведь недаром говорят: знания — сила.";
			link.l1.go = "guide_25";
			link.l2 = "Спасибо от всего сердца, месье, но дальше я разберусь сам.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "Рад был нашему знакомству. А насчёт денег на корабль — поговорите с влиятельными людьми города. Например, с купцом в магазине\n"+
			"Удачи, "+pchar.name+" — дерзайте, и всё у вас получится.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Тогда следуйте за мной! Начнём с самого основного — с кораблей.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Верфь. Здесь покупают и чинят корабли. Выбор невелик — в основном мелочь, но иногда попадаются серьёзные суда. Также тут можно купить пушки и украсить паруса.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Пирс — ворота в море. Как только обзаведётесь кораблём — вас тут будет ждать шлюпка. А пока рекомендую нанять штурмана, казначея и канонира — с ними вы будете чувствовать себя увереннее в море.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Здесь можно оставить корабль на стоянку, а также найти честную работу для капитана: фрахт, сопровождение, доставка почты. Чем больше заданий вы выполняете — тем выгоднее они становятся.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Магазин. Капитаны бывают здесь чаще всего — за провизией, ромом, лекарствами, порохом и боеприпасами. Если нужного товара нет — ищите контрабандистов в таверне. Но помните: без хорошего казначея торговать — пустая трата времени и денег.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Если пирс — ворота в море, то здесь — ворота в дикую местность. Опасно, но совершенно необходимо в тех случаях когда вам надо попасть в форт, найти сокровища или перейти по суше в другое поселение.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Учитывайте, что не во всех колониях вам будут рады. Если вы не хотите дожидаться ночи, чтобы проникнуть во враждебную колонию, то сначала поднимите другой флаг на корабле, а дальше уже либо полагайтесь на свой навык скрытности, либо покупайте торговую лицензию.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Вы — отличный слушатель, мой друг. Как насчёт немного поразвлечься? Предлагаю тренировочный бой за воротами.";
			link.l1 = "Конечно! Это будет как нельзя кстати.";
			link.l1.go = "guide_47";
			link.l2 = "Спасибо от всего сердца, месье, но дальше я разберусь сам.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Мой друг, как я полагаю, вы не новичок в фехтовальном деле?";
			link.l1 = "Ха! Один абордаж я уже пережил и даже...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Вот и отлично. Начнём?";
			link.l1 = "Потанцуем!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "Вот, это я понимаю - человек знает, с какой стороны шпагу держать. Вы молодец, монсеньор. Теперь вам только побольше практики - у вас есть все шансы стать настоящим мастером меча.";
			link.l1 = "Спасибо! Что теперь?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "Практики, значит... Практики?! Вы что, сговорились все?! Мне осточертел этот покровительственный тон, который я только и слышу с тех пор, как сошёл на берег этой дыры!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Вот, так намного лучше! Видите - стоило сосредоточиться - и всё получилось. Теперь вам нужно больше практики - и вы легко станете умелым фехтовальщиком.";
			link.l1 = "Спасибо! Что теперь?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "Этот бой закончился не в вашу пользу, месье. Двигайтесь быстрее, парируйте мои удары, отскакивайте назад или в сторону. Желаете реванш?";
			link.l1 = "Конечно! Не ждите пощады, монсеньор!";
			link.l1.go = "guide_56";
			link.l2 = "Нет, с меня, пожалуй, довольно. На этом закончим наш урок фехтования. Что теперь?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "Два-ноль в мою пользу, "+pchar.name+"! Не давайте перехватывать у себя инициативу. Ловите мои удары финтом. Если видите, что я хочу нанести пробивающий - отскакивайте назад, либо парируйте, не стойте в блоке. Ещё разок!";
			link.l1 = "Идите сюда, сударь, и я наконец преподам вам урок!";
			link.l1.go = "guide_56";
			link.l2 = "Нет, с меня, пожалуй, довольно. На этом закончим наш урок фехтования. Что теперь?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "Да, что-то слабоваты вы, "+pchar.name+". Но не огорчайтесь сильно: у вас ещё будет масса времни и возможностей отточить своё мастерство. Но будьте предельно осторожны и не лезьте попусту на рожон, пока не научитесь владеть шпагой получше.";
			link.l1 = "Я приму ваши слова к сведению, монсеньор, но хочу сказать, что вам всего лишь просто повезло! Эта проклятая жара меня совсем из колеи выбила, не то я бы вам показал!.. Ладно, закончим наш урок фехтования. Что теперь?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "А теперь нам пора попрощаться, сударь. Очень рад был нашему знакомству. Надеюсь, моя экскурсия и тренировка оказались полезными для вас, и полученные знания пригодятся вам в дальнейшем. Возможно, мы с вами ещё когда-нибудь встретимся\nА насчёт денег - поговорите с влиятельными людьми нашего города: купцом в магазине, барменом в таверне, ростовщиком, чиновником в портовом управлении, поспрашивайте других людей на улице, сходите в форт, джунгли - так и найдёте работу, либо иной способ разжиться серебром да золотом\nУдачи, "+pchar.name+", дерзайте - и всё у вас получится.";
			link.l1 = "Благодарю вас, монсеньор. Взаимно был рад знакомству. Всего доброго вам!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Не забывайтесь, месье! Держите себя в руках! Я не потерплю дерзостей в свой адрес!\nВпрочем, я понимаю, что этот срыв - реакция на совершенно новую для вас обстановку, поэтому на сей раз я сделаю исключение и прощу вам истерику. Впредь думайте, что и кому говорите. А теперь прощайте, месье де Мор.";
			link.l1 = "Ну уж нет, месье Валинье. Будь мы в Лувре, вы прикусили бы язык! Пора уже и мне преподать провинции урок. Защищайтесь!";
			link.l1.go = "guide_65";
		break;
		
		case "guide_65":
			DialogExit();
			
			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE*10+300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}