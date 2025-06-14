// Эркюль Тонзаг, он же Плешивый Гастон
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Ну, здравствуй, " + pchar.name + ". Рад тебя видеть!";
				link.l1 = "Гастон!? Это ты?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Здравствуй, " + pchar.name + ". Я уже в курсе о твох делах - Джон мне всё рассказал. Я, даже, право, не знаю, что и сказать. Я восхищён!";
				link.l1 = "Приятно слышать похвалу из твоих уст, Эркюль!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Добрый день. У вас ко мне дело?";
			link.l1 = "Нет. Вероятно, я ошибся. Прошу меня извинить. До свидания.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Ты знал меня под этим именем. Но моё настоящее имя - Эркюль. Эркюль Тонзаг.";
			link.l1 = "Вот это да! Я тоже рад тебя видеть... А я тебя и не узнал в пылу драки. Ты вовремя подоспел ко мне на выручку.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "После твоего отбытия, я буквально на следующий день получил известия, что Флитвуд значительно усилил охрану своего дома. Предполагая, что за этим может крыться некая ловушка, или что-то подобное, я немедленно на своём корабле 'Сумрак' выдвинулся на Антигуа. И, как видишь, не зря.";
			link.l1 = "Это точно. Я еле управился с гвардейцами внутри дома, на бой на улице сил уже не хватило... немного не хватило.";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "После этой бойни, Флитвуд объявил розыск голландского шпиона - они приняли тебя именно за голландца. У Флитвуда старая вражда с ними... Плохо было то, что один из солдат в доме остался жив и запомнил твоё лицо. Впрочем, эта проблема уже решена - я сегодня доделал то, что начал ты. Больше этот солдат уже никого не опознает...";
			link.l1 = "Ты его - того? Понятно...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Да. А пока ты валялся без сознания у Джона, я приложил нашему дружку, Флитвуду, но тут вышла промашка. Я ослепил его, бросив перец в глаза, и рубанул, прежде чем он успел обнажить клинок. Но этот гад носит под мундиром пурпан... это и спасло его. Сейчас он отлёживается у себя в доме, под усиленной охраной. Очень плохо, что он остался жив.";
			link.l1 = "Так твоя основная задача на Антигуа - убрать Флитвуда?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Ну, в общем, да. Но теперь это, похоже, невыполнимо - дом всегда на замке, в нём дежурит полдюжины отборных гвардейцев, и пропускают к Флитвуду только его доверенное лицо - старого артиллериста Чарли, по прозвищу Книппель.";
			link.l1 = "Уже что-то...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Постой-ка... Ты что, задумал вмешаться в это дело?";
			link.l1 = "А почему бы и нет? Разве тебе не нужна помощь? Ты спас меня, и я хочу помочь.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "А почему нет? Вы люди серьёзные. А серьёзные люди платят щедро. Я как раз ищу работу.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Поверь мне, парень, ты с этим не справишься. Ты молодец, добытый тобой журнал помог мне спланировать покушение на Флитвуда, ты здорово покрошил в капусту гвардейцев, но до Флитвуда тебе не добраться. Даже я не представляю теперь, как это сделать.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Я подумаю. Время у меня есть. Вот только жаль, корабль мой арестовали, да и команды не осталось.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Я подумаю. Время у меня есть, и корабль тоже.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Поверь мне, парень, ты с этим не справишься. Ты молодец, добытый тобой журнал помог мне спланировать покушение на Флитвуда, ты здорово покрошил в капусту гвардейцев, но до Флитвуда тебе не добраться. Даже я не представляю теперь, как это сделать.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Я подумаю. Время у меня есть. Вот только жаль, корабль мой арестовали, да и команды не осталось.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Я подумаю. Время у меня есть, и корабль тоже.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Не переживай по поводу этого. Когда твою лоханку взяли под стражу, я собрал весь твой офицерский состав и часть матросов на своём 'Сумраке'. Они знают, что ты жив и остались на службе. В качестве награды за журнал я передаю тебе в постоянное пользование свой корабль 'Сумрак'.";
			link.l1 = "Спасибо! Я в долгу не останусь.";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "Сумрак";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Да, я хочу передать тебе деньги за журнал. Вот 15 000 - больше у меня на данный момент нет, к сожалению. Потом сочтёмся.";
			link.l1 = "Не надо. Этого хватит. Если бы не ты, мне бы и эти деньги уже не понадобились.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Ладно, " + pchar.name + ", мне пора идти. В Бриджтаун я пока не намерен возвращаться. Если я тебе сильно понадоблюсь - поспрашивай Джона. Счастливо!";
			link.l1 = "Удачи, Эркюль!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "За ликвидацию Флитвуда я хочу подарить тебе этот доспех - он надёжно защитит тебя в схватках. А теперь пойдём к Джону. У него к тебе серьёзный разговор - он хочет предложить тебе... одно дело.";
			link.l1 = "За подарок спасибо! Хорошо, пойдём...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Капитан, у меня тоже к тебе дело. Я собирался учить тебя ремеслу, но вижу, что мне самому есть чему у тебя поучиться на старости лет. Возьми меня к себе офицером на корабль - не пожалеешь.";
			link.l1 = "С удовольствием, Эркюль! Добро пожаловать в команду!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Эркюль, я не могу представить себя в роли твоего босса. Спасибо за предложение, но я не могу себе позволить командовать тобой.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Ну, как скажешь, " + pchar.name + ". Бывай. Может, ещё встретимся. Приятно было с тобой работать!";
			link.l1 = "И тебе всего хорошего, дружище!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Слушаю, тебя, кэп. Что скажешь?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Эркюль, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдёшь со мной?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Эркюль, дай мне полный отчёт о корабле.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Я хочу, чтобы во время стоянки в колонии ты закупал товары.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "У меня есть для тебя несколько приказов.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Слушай мой приказ!";
            Link.l1.go = "stay_follow";
			link.l2 = "Пока ничего. Вольно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Капитан, ты прости, но пересчётом товаров, ценами и прочими циферками я не занимаюсь. Вот Йохан ван Мерден - он может, но вряд ли он поменяет сушу на палубу корабля...";
			Link.l1 = "Да, ты прав, Эркюль. Эх, нужен казначей...";
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Капитан, я за свою жизнь только провиант да ром закупал, когда был трактирщиком на Барбадосе. И то там я брал нормальную еду, а не сухари да солонину. Так что извини, но с этим не ко мне.";
			link.l1 = "Хм, может превратить корабль в таверну... Да шучу я, Эркюль. Ладно, буду закупать сам.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Внимательно слушаю.";
			Link.l1 = "Это касается абордажа.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Это касается твоего корабля.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Пока ничего.";
			Link.l8.go = "exit";
			//NPChar.id = "Tonzag"; 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не брал корабли на абордаж. Побереги себя и свою команду.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Мне нужно чтобы ты брал вражеские корабли на абордаж.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не менял свой корабль после абордажа. Он слишком ценен.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Когда будешь брать врагов на абордаж, посмотри, вдруг кораблик приличный будет, тогда бери себе.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "Какие приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Нужно изменить тип боеприпаса для твоего огнестрельного оружия.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Ты чертовски удачлив, кэп. Я рад, что присоединился к тебе тогда, у Джона. И проглоти меня акула, если я не поддержу тебя и в этом предприятии!";
			link.l1 = "Спасибо, Эркюль! Я рад, что не ошибся в тебе.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Когда мы будем отправляться?";
			link.l1 = "Немного позже. А пока подготовимся к походу.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Уже ничего, кэп. Если бы это было связано с нашим делом, то нас бы уже резали на пыточном столе.\nЕжели сразу не ведут на допрос, то дело, видать, не срочное.\nЛибо подстава, либо вымогательство.\nНас специально помаринуют пару дней, ничего не объясняя. А потом придут с предложением, которое мы примем.";
			link.l1 = "Личный опыт?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "А можно сделать так, чтобы пришли с подобным предложением вот прямо сейчас?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Ну разумеется. Груох однажды заплатили родственники одного смертника, чтобы избавить его от прощальных ласок палача Тринидада.\nОна заплатила коменданту за право погулять по казематам. Обычное дело - многие платят солдатне за возможность безнаказанно и без свидетелей издеваться на людьми, которые не могут дать сдачи.\nСмертник погиб тихо и без мучений. Чистая и достойная работа.";
			link.l1 = "Груох? Кто это?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Простите, кэп. Не то место и не то время.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Можно попробовать. Давайте подождём кормёжки и я перекинусь парой слов с караульным. Видите-ли, обыскивать нормально они так и не научились. Эх.";
			link.l1 = "Что такое?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Странное чувство, кэп. Даже я бы сказал, предчувствие. Извините и давайте поговорим позже.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Я что-то пропустил, капитан?";
			link.l1 = "Да ничего особенного, обычный день в море. Ну ты даёшь, старый дьявол! Запачкал только ты тут мне всё.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "Кровь смывается холодной водой, капитан. Нам нужно с вами поговорить.";
			link.l1 = "Думаешь? Только было бы недурно сначала пережить этот день.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Я тоже рад тебя видеть, Румба. Капитан, не буду вам мешать, позже поговорим.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Привет, Рыжик. Капитан, не буду вам мешать, позже поговорим.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Капитан, не буду вам мешать, позже поговорим.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Готовы выслушать меня, кэп?";
			link.l1 = "Давно пора поговорить, Эркюль. Я только сейчас понял, что почти ничего о тебе не знаю.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Значит пришло время познакомится. Ранние годы опустим, хотя бы потому, что рассказывать о них и нечего: солдат-победитель, солдат-побеждённый, дезертир, мародёр... ну вы знаете, как оно бывает.";
			link.l1 = "Не знаю, но пока звучит достаточно обыденно.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Карьерных возможностей после такого боевого пути у меня было немного: бандит, висельник или гвардеец достойной Голландской Вест-Индской Компании. Я выбрал, как вы понимаете, последнее.";
			link.l1 = "Оттуда ты тоже дезертировал?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Напротив, я сделал там карьеру. Получил предложение вступить в боевое крыло разведывательного отделения Компании, где и познакомился со своей будущей женой.";
			link.l1 = "Пока всё звучит достаточно мирно... особенно если сильно не задумываться о методах голландцев.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Огромные деньги честно не заработаешь, а с конкуренцией бороться можно разными методами. Да, мы отвечали за применение особых методов...";
			link.l1 = "Догадываюсь, о чём идёт речь...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Да, могло быть что угодно: от пиратства до поджогов складов с товаром. В конечном итоге, дело вскрылось, и нас пришлось закрыть... На бумаге, конечно же. Так и родилась Лига, известная и подконтрольная только избранным руководителям высшего звена Компании. У карибского висельника, который хоть что-то стоит, было только два пути: пиратство или Лига. И в Лиге обычно платили лучше\nВ основном, Лига работала по-прежнему на голландцев, но могла брать и сторонние заказы...";
			link.l1 = "Это кое-что объясняет...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "И это Лига подстроила историю на Тортуге. А потом и тот десант...";
			link.l1 = "Это всё я уже понял. Но почему?..";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Потому что из Лиги нет пути назад, и из воды сухим не выйти, кэп. Я хотел уйти на покой, и попытался это сделать. Как видите, не очень успешно.";
			link.l1 = "Ты хочешь сказать, что твои бывшие коллеги пошли на огромные денежные затраты и гибель почти сотни человек, сожгли брандер и рискнули своим боевым кораблём ради того, чтобы... убить тебя за дезертирство?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "Я слишком много знаю о Лиге и был в ней не последним человеком, капитан. Меня нельзя просто так отпустить, и им надо это наглядно продемонстрировать, чтобы ни у кого больше не возникало идеи оставить дело... Они пытались добраться до меня и раньше... Уже довольно давно... Они убили мою жену и обезобразили меня, пусть и дорогой для себя ценой. У этой истории нет счастливого конца, капитан, и не будет. Только прикажите - и я покину экипаж и встречу их в следующей раз сам, один.";
			link.l1 = "Не говори глупостей, Эркюль... А какую роль сыграл во всём Лукас Роденбург? Он же наверняка был замешан в этих делах! Ваша, то есть его, 'организация', Лига...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Разные структуры, капитан, хотя часто подчинялись одному человеку, работали плотно и в одной упряжке. Но особые агенты Роденбурга наносили точечные эффективные удары, а Лига осуществляла массовые акции. И ныне Лига - реальность, а организации нет, вы же сами знаете: я перед вами, а Джон Мердок уехал, Лонгвэй сбежал, Ван Берг на дне морском, Роденбург казнён... Впрочем, этому покойному мерзавцу я был обязан. Он приметил меня в Лиге, а потом, когда я попытался её оставить, вытащил из неприятностей и сделал своим порученцем. Конечно, другим это не понравилось, но ослушаться его никто не посмел... А потом, при известных обстоятельствах, он решил избавиться от нас с Мердоком, но в дело вступили вы, и взяли меня на службу\nИ я подумал, что вот он, второй шанс покончить с прошлым... Вы переиграли Роденбурга, Лига в результате утратила покровителя, опасность ниоткуда больше не грозит... Но, конечно же, я ошибся... Старый дурак... Но хватит об этом, капитан. Давайте думать, что делать дальше, если, конечно, вы действительно не собираетесь высаживать меня в первом же порту.";
			link.l1 = "Не собираюсь. Я полагаю, у тебя есть план?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Ничего особенного на самом деле. Мы никогда не вырежем их всех, но можем нанести им такие потери, что больше охоты чинить мне... нам неприятности у них не возникнет.";
			link.l1 = "И как это сделать? У них есть лагерь?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Крупный оплот - вряд ли, было бы слишком приметно и опасно для Лиги. А под потерями я имею в виду не людские потери - на людей им плевать, а вот золото потерять им очень не понравится. Деньги от Компании им больше не поступают, так? Вряд ли Лига нашла себе нового покровителя, так что приходится им выжимать золото в другом месте.";
			link.l1 = "И что это за место?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Я не знаю, капитан.";
			link.l1 = "Эркюль, но ты только что говорил, что тебя преследуют как раз по причине того, что ты слишком много знаешь!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Дайте подумать... Возможно, Лига сейчас как-то оперирует против испанцев. Они - первый кандидат из тех, кого можно прижать по-крупному. Кстати, у Роденбурга всегда было полное взаимопонимание с кастильскими толстосумами, бывало, что он направлял им парней из Лиги для разных делишек, и всегда запрещал причинять им хоть малейший вред, что, кстати, ребятам не очень нравилось...";
			link.l1 = "Полное взаимопонимание, говоришь?.. А тот идальго и его палец, который ты заставил меня тащить к тебе в таверну?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "Это особый случай, сторонний заказ. Если тебя мучает совесть, капитан, то можешь её успокоить - этот дон получил по заслугам... А сейчас я о другом: после того, как работодатель исчез, деятели Лиги могли дать волю своим желаниям и попробовать урвать солидный кусок из испанского пирога. Благодаря работе с испанцами при Роденбурге они знают, где и что брать.";
			link.l1 = "Хм... Возможно, ты и прав. Но к испанским банкирам, насколько мне известно, никто особо не вламывается, оперировать против испанцев на море - тут как удача повернётся... Может быть, следует искать какое-нибудь испанское предприятие? Факторию?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Разумное предположение, капитан... У нас есть ещё зацепки?";
			link.l1 = "Хм... корабль, который на нас сегодня напал, ушёл на юг...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "Вряд ли его кэп нас ещё побеспокоит, но он должен предупредить остальных, что дела пошли плохо и, возможно, перевезти личный состав в другое место. Что-то ещё?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Да, у меня был милый разговор с комендантом тюрьмы на Тортуге... Он что-то упоминал о материке.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "Нет, больше ничего.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Отлично, кэп! Юг, материк, испанцы - значит, найдем их быстро. Отправляемся? И спасибо, что выслушал.";
			link.l1 = "Да, интересный разговор у нас вышел... Отправляемся!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Негусто, но таким людям, как мы, этого хватит. Идём на юг? Искать испанское коммерческое предприятие? И спасибо, что выслушал.";
			link.l1 = "Да, интересный разговор у нас вышел... Отправляемся!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Смотрите, капитан. Вот так они работают.";
			link.l1 = "И ты тоже так работал?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Идёмте, посмотрим что внутри.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Жаркое было дело, капитан. Это логово мы зачистили, хоть оно, конечно, и не последнее...";
			link.l1 = "А что рудник, Эркюль?! Все эти люди снаружи?! Их ведь тоже 'зачистили'! И о чём говорил этот мерзавец?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Давайте обсудим позже, капитан. Их командир выжил, мы должны его допросить.";
			link.l1 = "А если он ничего не знает?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "Знает он всё. Сами рассудите: они нас ждали, вывезли всё золото и устранили свидетелей. Значит, у них был план. Я сам приведу мерзавца в ваш трюм и заодно осмотрюсь тут. Вы тоже поглядывайте по сторонам, возможно, они слишком спешили и что-то да упустили.";
			link.l1 = "Хорошо, но, когда мы вернёмся, нас ждёт серьёзный разговор!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Хорошие новости, капитан.";
			link.l1 = "Я не вижу ничего хорошего в нашей ситуации, Эркюль. Идём, нам надо поговорить наедине.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Даже так? Так точно, капитан.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Вижу, что разговор у нас будет серьёзный, капитан.";
			link.l1 = "Да, и говорить буду я. Первое. Ты не находишь, что у нас вырисовывается определённая тенденция? Гора мертвецов преследует нас, куда бы мы не отправились! Сначала ты получил заряд картечи в брюхо, а на следующий день более сотни людей, хороших и не совсем, погибло в... я даже морским сражением назвать это не могу! На днях было вырезано целое поселение, а сегодня мы этот счёт ещё несколько расширили, укокошив кучу народа в шахтах.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Конечно, меня беспокоит, насколько вырастет эта гора уже завтра, но по-настоящему меня страшит то, что вся эта кровь льётся из-за одного человека. И этот человек занимает не последнюю должность в моей команде!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "Второе. Ты мне лгал, Эркюль. Ни один дезертир не стоит тех усилий, которые прикладывают бывшие коллеги для твоего устранения. Что там орал наш пленник в шахтах? Предатель? Порто-Белло? Груох? Ты что-то натворил, Эркюль, и на этот раз я хочу знать правду.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Правду? А правда в том, капитан, что я действительно дезертировал, вместе со своей женой Груох. Мадам Тонзаг не хотела бросать Лигу, она любила ту жизнь, но ещё больше любила меня. Мы должны были порешить одного испанского идальго, но тот сделал предложение получше. Это был наш шанс, и я, вместе с ней, ушёл к нему на службу. Конечно же, в Лиге решили, что мы погибли на задании, и отправили в Порто-Белло вторую группу - доделать работу и отомстить.";
			link.l1 = "И ты их всех убил?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "Сначала они убили Груох и обезобразили меня. Идальго больше не хотел иметь со мной дел и выкинул на улицу. И вот тут меня подобрал Роденбург...";
			link.l1 = "И как мне теперь тебе доверять? Ты дезертировал из армии, дезертировал из Лиги, убил своих же подельников! Будет подходящий случай - и меня предашь?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Да, я дезертировал, я нарушил контракт, я положил пару десятков членов Лиги. Но я усвоил этот урок, капитан. И потом, мертвец не может никого предать, а я уже давно умер, ещё в Порто-Белло. И, возможно, именно поэтому меня так трудно сейчас убить.";
			link.l1 = "На сегодня достаточно, пусть мне и кажется, что ты всё равно что-то недоговариваешь.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Мне самому заняться пленником, или вы тоже хотите поучаствовать?";
			link.l1 = "Пошли, я сам его допрошу.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "Нет уж, такие дела не по мне. Увидимся у меня в каюте через полчаса!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Кто у вас сейчас за главного? Арно?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "Эта скотина дорвалась до власти? Быстро же вы скатываетесь до обычной банды уголовников...";
			link.l1 = "Что за Остин?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "Банда Остина была знаменита тем, что заманивала вольных капитанов во всякую глушь, резала их и полностью избавляла труп от любых денег и побрякушек. Верное дело, искателей приключений у нас полно, так что никто особо не хватится. Но нашла коса на камень: с одним кэпом у них вышла промашка, так что свинтил наш головорез со своими ребятами под крыло Компании. Мы держали его поводке и спускали только тогда, когда нужно было решать вопросы быстро и без фантазии.";
			link.l1 = "Вряд ли с таким человеком получится договориться.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "Это уж точно. Если делом сейчас заправляют он и его люди, то очень скоро Лига превратится в очередную банду.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "Интересный вышел у вас разговор.";
			link.l1 = "Ещё бы знать, сколько в нём правды... Что с бойней в Порто-Белло? Если он не врал, то значит, что в нашем последнем разговоре ты опять умудрился опустить ещё пару фактов из своей прославленной биографии.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "В Порто-Белло было жарко, капитан. Я дрался за свою жизнь, за жизнь нанимателя, за жизнь моей жены, мне было некогда считать убитых и оплакивать каждого не вовремя высунувшегося на улицу крестьянина.";
			link.l1 = "Именно в таком порядке защищал?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "Нет, конечно. Её - прежде всего. Всегда.";
			link.l1 = "И что думаешь? Стоит ли отправляться в Каракас?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Я бы не стал, капитан. И вам не советую. Лиге вы теперь не враг, ну а я им стал не интересен, по крайней мере на время, пока нахожусь у вас на службе. И потом, есть у меня чувство мерзкое на душе\nПлохо будет, если мы туда пойдём. Очень плохо. Эта история с несчастливым концом. Но я буду с вами до конца, капитан.";
			link.l1 = "Я подумаю.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "Кстати, ты был прав: они не успели достаточно хорошо прибраться на руднике. Вот, смотри.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Офицерский журнал... зашифрован, но шифр старый, я его знаю\nНичего интересного, похоже, это был журнал нашего бывшего пленника. Теперь понятно, почему он так охотно пошёл на разговор. Смотрите, здесь есть указания на припрятанный клад! Ублюдок явно собирался на пенсию и был готов слинять в любой момент!";
			link.l1 = "И где этот схрон?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "Вы знаете этот остров, капитан. В его водах вы лишили жизни Ван Берга.";
			link.l1 = "Хорошо, это недалеко, так что заглянем. А по поводу Каракаса я ещё не решил, но, думаю, месяц у нас есть.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Как прикажете, капитан. Я с вами до конца.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "Дело сделано, капитан. Остин сейчас в Каракасе, думаю, месяц у нас есть.";
			link.l1 = "По порядку. Что рассказал пленный? Кто такой Остин? И зачем нам идти в Каракас?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "Банда Остина была знаменита тем, что заманивала вольных капитанов во всякую глушь, резала их и полностью избавляла труп от любых денег и ценностей. Верное дело, искателей приключений у нас много, так что никто особо не хватится. Но нашла коса на камень: с одним кэпом у них вышла промашка, так что свинтил наш головорез со своими ребятами под крыло Компании. Мы держали его поводке и спускали только тогда, когда нужно было решать вопросы быстро и без фантазии.";
			link.l1 = "Вряд ли с таким человеком получится договориться.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "Это уж точно. Если делом сейчас заправляют он и его люди, то очень скоро Лига превратится в очередную банду. Но я бы не стал отправляться в Каракас, кэп.";
			link.l1 = "Серьёзно? Ты боишься?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "Не в этом дело, капитан. Перед тем, как умереть от ран, пленник сообщил, что Лиге вы теперь не враг, ну а я им стал не интересен, по крайней мере на время, пока нахожусь у вас на службе. Требование оставить нас в покое исходит от какого-то нового влиятельного патрона Лиги\nА Каракас... Есть у меня чувство мерзкое на душе. Плохо будет, если мы туда пойдём. Очень плохо. Эта история с несчастливым концом. Но я буду с вами до конца, капитан.";
			link.l1 = "Я подумаю. Хотелось бы, конечно, разобраться с этой историей раз и навсегда, но, возможно, ты и прав. Сомневаюсь, что после событий последней недели они к нам посмеют ещё сунуться.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "Кстати, ты был прав: они не успели достаточно хорошо прибраться на руднике. Вот, смотри.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Офицерский журнал... зашифрован, но шифр старый, я его знаю\nНичего интересного, похоже, это был журнал нашего бывшего пленника. Смотрите, здесь есть указания на припрятанный клад! Ублюдок явно собирался на пенсию и был готов слинять в любой момент!";
			link.l1 = "И где этот схрон?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "Вы знаете этот остров, капитан. В его водах вы лишили жизни Ван Берга.";
			link.l1 = "Хорошо, это недалеко, так что заглянем. А по поводу Каракаса я ещё не решил, но, думаю, ты прав, и месяц на раздумья у нас есть.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Как прикажете, капитан.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Стойте, капитан. Дальше я пойду один.";
			link.l1 = "Это почему же? Геройствовать захотел? Поздно, ты эту кашу заварил, но жрать её придётся нам всем вместе.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Не придётся. Хватит вам расплачиваться за мои ошибки, капитан. Вы были правы, куда бы я не пошёл, гибнут люди и льётся невинная кровь. А если мы зайдём в эту церковь вместе, то повторится Порто-Белло, а я этого не хочу.";
			link.l1 = "Что на самом деле там случилось?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Бойня. Я хотел уйти на покой, кэп: взять золото, жену и уехать домой, в Каркассон. Я знал, что Лига пошлёт ещё людей доделать мою работу и взял щедрую награду авансом у своего нового патрона. А потом мне только оставалось столкнуть лбами городскую стражу, бывших подельников и нового нанимателя. Под шумок можно было бы не только скрыться с деньгами, но и, например, ограбить пару особо жирных котов Порто-Белло, которых я заранее себе заприметил.";
			link.l1 = "Хороший план, хотя я бы сделал по-другому: слишком многое может пойти не так.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Я сам не ангел, но твой подход даже меня заставляет содрогнутся. Меня удивляет, что ты ещё не предал меня, как ты предал и Лигу, и идальго, и даже свою жену.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Всё пошло не так. Всё же, стрелять из 3-х фунтовки в сторону губернаторского дворца было ошибкой. Самого его только поцарапало, но вот его дочке-красавице потом, как говорят, отрезали обе ноги по колено, чтобы спасти. Ответ был страшный: началась кровавая баня, в которой погибло очень-очень много людей, капитан. Сейчас вы смотрите на последнего живого свидетеля тех событий, а другого не так давно вы порезали сами.";
			link.l1 = "Объясни.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Если бы мадам Тонзаг была ещё жива, то обязательно бы предал, капитан. Я  - живой мертвец и следую за вами, поскольку другого мне не осталось в этом мире. Сейчас вы смотрите на последнего живого свидетеля тех событий, а другого не так давно вы порезали сами.";
			link.l1 = "Объясни.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Простите меня, капитан, за то, что недоговаривал вам всю дорогу. Когда мы только познакомились, я думал, что вы - очередной отморозок, вроде меня. И знаете, что я сделал первым делом? Отправил вас подчищать за собой: убить того испанского дона, которого я сначала не стал убивать, а потом не захотел защищать и решил предать. Тот самый идальго Родригес...";
			link.l1 = "А палец его тебе был зачем нужен?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Тут без сюрпризов. Просто проверка, капитан. Мы набирали десятки таких молодых головорезов, как вы, каждый год. Проверку на элементарную честность проходили единицы, да и те гибли в первых же операциях. Вы и сами не должны были пережить историю с кражей журнала Флитвуда. Я собирался просто зайти в дом, добить выживших и забрать журнал.";
			link.l1 = "Если память меня не подводит, история повернулась немного не так.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = " Это верно, кэп. Не знаю, что меня сподвигло вам помочь, но вы с такой жаждой жизни дрались с Лисами, что ненадолго заразили этой жизнью даже меня. А в итоге вы, сами того не зная, меня спасли. Не будь вас - гнил бы я уже в могиле по воле Роденбурга или ещё какой сволочи. Вы ничего не должны мне, кэп. И дальше я вас не пущу. Это моё дело, моё искупление.";
			link.l1 = "Как скажешь, Эркюль. Больно терять такого бойца, но ты сам себя потерял уже давным-давно и не стоишь новой крови. Мне ты тоже ничего не должен, и я надеюсь, что ты обретёшь искупление в этой церквушке.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Хорошая речь, Эркюль. Иди к дьяволу! Если ты не заметил, то твои проблемы с недавних пор стали и моими. Ты - мой офицер, и только я буду решать, достоин ты прощения или нет. Так что придётся тебе побыть с нами ещё немного и заслужить своё искупление ратными подвигами в составе моего экипажа!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Спасибо за всё, капитан. Прощайте!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Так точно, капитан!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "Много я отморозков видел на своём веку, капитан, но впервые меня внутри перекрутило от ужаса. Как думаете: если чудовище поменьше убьёт чудовище большое, то можно ли считать это искуплением?";
			link.l1 = "Разбавляют ли ром водой? Расскажи мне, как выяснишь. Пойдём, тут мы закончили.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}