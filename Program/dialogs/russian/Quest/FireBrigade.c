
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("", "Женщина... И капитан! Теперь я видел всё. Мадемуазель, вы прекрасны. Жаль, что ваша красота принесла столько горя Короне Франции\n") + "Вот чем заканчиваются приказы Пуанси. Один - в тюрьме. Другой - или присоединиться к нему, или сгинет сегодня в бою.";
			link.l1 = "Вы явно не на своем месте. Зачем отправили такого офицера и такой прекрасный корабль выполнять грязную работу охотника за головами?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Приказы не обсуждаются, они исполняются. Если бы каждый капитан выбирал, какие приказы достойны - у нас не было бы флота.";
			link.l1 = "Скажите это своим людям.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Вы загнали меня в угол и пытаетесь надломить мою преданность короне. Очень низкий поступок, учитывая обстоятельства. Давайте закончим этот разговор звоном клинков, а не болтовней?";
			link.l1 = "(Харизма) Есть и третий путь. Хватит вам выполнять грязную работу, недостойную офицера. Присоединяйтесь ко мне - и я покажу вам другой мир.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "Я предоставлю вам такую возможность.";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Недостаточно развит навык (80)", SKILL_LEADERSHIP);
                dialog.text = "К предателям везде относятся одинаково. И я им не стану.";
                link.l1 = "У вас был шанс, и вы его упустили. К бою!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Проверка пройдена", SKILL_LEADERSHIP);
            dialog.text = "Я давал клятву верности короне, а не напыщенным накрахмаленным куркулям, отправляющим нас на смерть ради решения их личных проблем. Но вы - враг моей страны, и я не могу закрыть на это глаза.";
			link.l1 = "Мои грехи перед вашей страной я могу искупить хоть завтра - достаточно заплатив посреднику. Это говорит больше о вашем начальстве, чем обо мне.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "Это правда. И я устал с этим мириться. Я готов перейти под ваше командование, если вы пообещаете больше не трогать французов.";
			link.l1 = "Я не знаю, с кем пересекутся наши пути, и не могу этого гарантировать. Но искренне постараюсь проливать поменьше крови. Добро пожаловать в команду, офицер " + NPChar.name + "!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "Так вот как выглядит враг рода людского. Надеюсь, ты гордишься этим званием, пират" + GetSexPhrase("","ка") + ". Тебе пришлось немало потрудится, чтобы заслужить его\nСогласно подсчетам Каса-де-Контратасьон, на твоем счету " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " судов под флагом испанской Короны. И сегодня мой прекрасный корабль его пополнит" + GetSexPhrase(".","\nГоре Испанскому флоту! Мы терпели лишения от болезней, кумовства, коварства врагов... Но чтобы от женщины?");
			link.l1 = "Ты остался один, твоя команда мертва. Да и сам ты уже мёртв, просто ещё этого не понял.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
			dialog.text = "Жаль, что это задание получил не де Альба. Он бы справился лучше. Но я все-таки попытаюсь доделать работу.";
			link.l1 = "Ты достойный сын своего отечества. Приготовься встретиться с его героями, сеньор.";
			link.l1.go = "Alonso_2";
			link.l2 = "Охотник стал добычей. Так что зря ты тут распинался - старо как мир.";
			link.l2.go = "Alonso_3";
		break;

		case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
			dialog.text = "Благодарю за эту передышку, но теперь говорить будет моя шпага.";
			link.l1 = "К бою!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
			dialog.text = "Благодарю за эту передышку, но теперь говорить будет моя шпага.";
			link.l1 = "Готовься к смерти!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            NPChar.Unpushable = "";
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name + "! Это имя настолько часто стало мелькать в сводках, что мне уже кажется, будто мы давно знакомы", "Мисс МакАртур! А ваш патрон знает, чем вы занимаетесь? А, неважно. Уверен, он и станет моим следующим заданием") + "\nТебе повезло: мое начальство слишком любит срочные депеши с приказами, которые противоречат текущим. Не был бы я уже занят зачисткой старой команды с Антигуа... Ну, да ладно. Хватит. Ты отвлекаешь меня от настоящей работы.";
			link.l1 = "Ты меня - тоже.";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "Книппель мне в корму, не успел! Будь мои старые кости чуть растропнее, сам бы отправил этого ублюдка к праотцам. Спасибо тебе, кэп. И от моего почившего патрона - тоже спасибо!";
			link.l1 = "Ты кто? Пленник? Это мои ребята тебя освободили?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Чарли Книппель собственной персоной. Да я лучший канонир английского флота!";
			link.l1 = "Кортни успел рассказать, что долго тебя выслеживал. В чем там дело?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Много лет я служил у бравого английского капитана по имени Ричард Флитвуд. С ним я провел немало успешных сражений, славно послужив нашей истинной страсти - английскому флоту, но в один момент все изменилось\nВоротнички из Лондона использовали нас втёмную. Напали мы на своих. Замарали свои мундиры, подчищая за другими. И вот наша очередь настала...";
			link.l1 = "Не осуждаю. Жизнь - штука сложная, особенно если человек не сам себе хозяин.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Можно сказать, тебя настигли тени старых грехов?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Я не жалею, что служил своей стране. Просто... обидно как-то, кэп. Особенно - за патрона и жену его, бедняжку.";
			link.l1 = "Что теперь?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "Зря вы так... с колкостями своими! Цену за свои грехи мы уже заплатили сполна!";
			link.l1 = "Что теперь?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Теперь я человек без имени и без родины. Могу податься куда хочу, да пока что-то некуда. И не с кем. Везде нужны канониры, да не везде есть пушки.";
			link.l1 = "Давай ко мне. Не скажу, что с английским флотом у меня сложились хорошие отношения, но я уважаю его лучших представителей.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Пушки у меня есть. Если ты и вправду так хорош, то у меня в команде всегда найдется место для настоящего профессионала.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "Дома меня ждет петля, у испанцев и голландцев - тоже, а французов я недолюбливаю. Ну а вам, судя по всему, не хватает толкового канонира. Я в деле, капитан. Отправлюсь в каюту при первой возможности. Заходите как-нибудь, найдем о чем позвенеть книппелями.";
			link.l1 = "Добро пожаловать на борт.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "Ну уж нет. Я лучше реквизирую шлюпку и затеряюсь в самой глубокой дыре на архипелаге. Спасибо за спасение, капитан, и прощайте.";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            npchar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "Ты не быть тот, кто должен дойти сюда. Мэйфенг - клык Компания. Моя эскадра - карающий нож. Ты их сломать. " + GetSexPhrase("Один", "Одна") + ". Это... не часто бывать.";
			link.l1 = "Вас отправили за мной, как за зверем. Я и драл" + GetSexPhrase("ся", "ась") + " как загнанный зверь. Когда выбор - сражаться или умереть, мыслишь проще. В конце концов, остался один вопрос: смогу ли я дойти до каюты легендарной шебеки - или нет.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Быть странно — видеть женщину в такой бой. В Поднебесной женщина не вести флот. Но ты не хуже. Быть даже страшнее\n") + "Ты знать, кто командовать? Ты ждать меня?";
			link.l1 = "Да. Мэйфенг - корабль с историей. Когда я переш" + GetSexPhrase("ёл","ла") + " дорогу Голландии, я знал" + GetSexPhrase("","а") + ": рано или поздно тебя отправят по мою душу. Почётный был бы конец... но погляди, как лихо всё обернулось.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Знание врага и себя - быть ключ к победа. Значит, ты сделать выбор. Встретить моя эскадра на своих условиях. Быть готов к смерть. Но ты выиграть. Теперь моя жизнь в твоих руках. Почему не добить?";
			link.l1 = "(Харизма) Потому что не вижу смысла топить легендарного капитана из-за амбиций Компании. Я был" + GetSexPhrase("","а") + " на твоём месте — пешкой. Служил" + GetSexPhrase("","а") + " чужим интересам, носил" + GetSexPhrase("","а") + " чужие приказы. Я предлагаю тебе то, что сам" + GetSexPhrase("","а") + " когда-то выбрал" + GetSexPhrase("","а") + ": свободу.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Потому что у каждого капитана должно быть последнее слово. К бою!";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("Недостаточно развит навык (50)", SKILL_LEADERSHIP);
			dialog.text = "Свобода - это не то, что дают. Это то, что берут. И не каждый, кто говорить о выборе, способен его предложить. Есть дороги, которые нельзя не пройти. Есть приказы, которые нельзя не оставить невыполненными. Моя дорога — здесь. Мой приказ — стоять до конца.";
			link.l1 = "Значит, ты выбираешь смерть?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "Нет. Я выбираю остаться собой.";
			link.l1 = "Тогда в бой!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Проверка пройдена", SKILL_LEADERSHIP);
			dialog.text = "Ты не как Роденбург. Он смотреть на меня как на инструмент. Ты - как на равный. Принесение себя в жертву - не быть добродетель. Я готов услышать твои условия.";
			link.l1 = "Всё просто. Будь штурманом на моём флагмане. Или, если пожелаешь, получишь свой корабль и пойдёшь под моим флагом. Ты больше не будешь подчищать хвосты за Компанией и прятать их скелеты в шкаф. Я свобод" + GetSexPhrase("ен","на") + " - и предлагаю разделить эту свободу со мной.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "Моя много видеть: кровь, золото, предательство. Компания платить - но не уважать. Давать корабль - но держать в цепь. Ты... давать выбор. Если ты держать слово - Лонгвэй больше не быть охотник за чужая воля. Он быть человек. Быть капитан. Или рядом с капитан, что знать, куда плыть.";
			link.l1 = "Добро пожаловать в команду, штурман Лонгвэй.";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
            sld = GetCharacter(NPC_GenerateCharacter("Longway_FP", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = StringFromKey("QuestsUtilite_42");
			sld.lastname = StringFromKey("QuestsUtilite_43");
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.currentnode = "Longway_officer";
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
            sTemp = GetGeneratedItem("blade_41");
            GiveItem2Character(sld, sTemp);
            EquipCharacterbyItem(sld, sTemp);
            sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
            if(sTemp != "")
            {
                GiveItem2Character(sld,   sTemp);
                EquipCharacterbyItem(sld, sTemp);
                sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
                LAi_SetCharacterBulletType(sld, sTemp);
                LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
                sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
                if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
            }
			TakeNItems(sld, "potion2", 1);
            sld.quest.meeting = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*200; // Артефакт
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP    = 60.0;
			sld.Health.maxHP = 60.0;
            sld.CanTakeMushket = true;
			SetCharacterPerk(sld, "ShipEscape");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

            NPChar.lifeday = 0;
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

            AddDialogExitQuest("pchar_back_to_player");
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
