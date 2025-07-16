void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "Ты кто "+GetSexPhrase("такой","такая")+", и какого дьявола тут околачиваешься?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Полегче, приятель. Я просто прогуливаюсь здесь, только и всего. И лезть не в свои дела не собираюсь.";
			}
			else
			{
				link.l1 = "Не знал"+GetSexPhrase("","а")+", что это твой маяк и твоя бухта. Повесь на одну из пальм вывеску с твоим именем или построй частокол - никто и не подумает лезть в твои владения.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Вот и проваливай отсюда! Сорвёшь нам сделку, спугнув клиента, и...";
			}
			else
			{
				dialog.text = "Послушай, "+GetSexPhrase("парень","девка")+", не заставляй нас с ребятами проверять, настолько же остёр твой клинок, насколько и твой язык... Просто исчезни и...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Ну, Фрэнки, который из них? Узнаёшь его?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "Нет... Эти рожи мне незнакомы, будь я проклят.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "Что?! Ты уверен?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Я что, по-твоему, слепой?! Говорю же, чт...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Чёрт возьми, какого дьявола?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Кто стрелял?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "За дураков нас держишь, осёл? Быстро положили оружие на землю, все вы! И ты, "+GetSexPhrase("щегол","пташка")+", в том числе.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Остынь, солдатик. Не мы это, не видишь что ли? Наши пушки там же где и были. И не трожь ты свою железяку!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Приказывать мне вздумал, скотина?! Под арест их, живо!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Ах ты! Не бывать этому. Парни, к оружию!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Эй, эй, поосторожнее! Кое-кто может и погибнуть, если ты продолжишь так яростно размахивать этой железкой.";
			link.l1 = "Ха, и кто же?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Я, конечно.";
			link.l1 = "Что за?.. Да кто ты такой?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "Именно этого я и добиваюсь. Продолжим.";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Я Томми! Томми Айронс. Наверное. А сама-то кто? Храбрая ты женщина, скажу я тебе, коли разгуливаешь в таком виде, хе-хе.";
				link.l1 = "Храбрая. И не побоюсь закрыть тебе рот, если придётся. Жарко мне всё время с детства, вот и одеваюсь полегче, а не чтобы тебя и тебе подобных радовать. Я "+GetFullName(pchar)+". Друзья могут звать меня Румбой, но тебя это точно не касается. И что значит это твоё 'наверное'?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Я Томми! Томми Айронс. Наверное. А сам-то кем будешь?";
				link.l1 = ""+GetFullName(pchar)+". И что значит это твоё 'наверное'?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Да то и значит. Память я потерял - приложили знатно так во время сражения. Знаешь, кто-то теряет её полностью. Вот прям без остатка, не частично. Я же счастливчик. Но забыл, как звать меня. К счастью, на шее у меня есть кулон, там написано 'Томас'. Но Томми мне больше нравится. А Айронс... Я сражался в рядах Железнобоких во славу Кромвеля, это я помню. Но Айронсайдс - больно громоздко. Айронс куда лучше.";
			link.l1 = "Ясно всё с тобой... Томми. Так скажи, а что это, собственно, было? Ты целился в кого-то конкретного? Попал? Промазал? Или просто для развлечения пальнул? Я уже ничему не удивлюсь.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "Попал, и ещё как попал! Во всех смыслах. Помнишь того гражданского? Он шёл по моему следу и привёл за собой солдат. Целый отряд, просто потому, что я переспал с его жёнушкой.";
			link.l1 = "Действительно попал, хех. Полагаю, он вас застукал?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ха, ты не поверишь! Нет. Эта дурёха потом ему призналась в измене - то ли совесть проснулась, то ли ей просто не понравилось, хе-хе. Что у этих баб в голове, чёрт их знает. Да и плевать на самом деле, ха-ха-ха!";
			link.l1 = ""+GetSexPhrase("Хм-м, странная она какая-то.","Мужчины... то вы не можете понять, что у нас в голове, то потом вовсе говорите, что вам плевать. Но в чём ты и прав, так это в том, что она поступила странно. Это явно не стоило обсуждать с мужем, если она и правда хотела спасти брак. А забыть, как страшный сон. Я бы именно так и сделала.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Вот-вот! А ещё про меня говорят, что со мной что-то не так. А солдат погибших жаль... я ведь и сам парень простой, из служивых. Я не говорил?";
			link.l1 = "Говорил. Из Железнобоких. Кромвель.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "А, да? Не помню уже, говорил, или нет. А знаешь, как я попал в Новый Свет? Рассказать?";
			link.l1 = "Нет, да и как-то не интересно, Томми. Не нужно.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Нужно, нужно. Сейчас расскажу.";
			link.l1 = "Ладно, чёрт с тобой, рассказывай.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Вот и не перебивай тогда! Так о чём я? Я ж ранение получил. И выбил себе отставку, поскольку был на стороне победивших. Но ты бы всё равно видел" + GetSexPhrase("","а") + " лица этих кабинетных крыс! До последнего думали, что я просто притворяюсь, а не потерял память. Всё о семье спрашивали.";
			link.l1 = "Ну а ты им что?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "А что я им? Сказал, что не помню. И не соврал - я их никогда не знал. Меня растила улица, простые работяги да служилые в трущобах. И ради них я и присоединился к Революции. Хотя людская неблагодарность, конечно, поражает - потеряй я руку или ногу, вынуждены были бы сразу дать отставку герою вроде меня. А я, между прочим, чуть голову не потерял, в прямом смысле!";
			link.l1 = "Ну а в Новый Свет-то как попал, герой ты наш?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "А ты сомневаешься? Сражался за простых людей - чем не герой? Надеюсь, однажды неженки вроде тебя на своей шкуре познают, что такое настоящая свобода!";
			link.l1 = "Хоть свобода и благо, почему-то это прозвучало от тебя, как угроза. Ладно, Томми, продолжай.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Ага. Отставку-то я получил после победы Революции, а потом понял, что делать-то ничего и не умею, кроме как стрелять да морды бить. И обратно в армию уже не попросишься - засмеют ведь, особенно после того, как поругался со всеми, чтобы выцарапать себе отставку. Хех, знаешь, мне кажется, что даже потеряй я как раз руку или ногу, всё равно бы ругаться пришлось - подумали бы, что я их где-то прячу, чтобы пришить потом суровой ниткой, ха-ха-ха!";
			link.l1 = "Забавно. Но ты так и не сказал, как ты оказался здесь.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Ой, как" + GetSexPhrase("ой","ая") + " же ты зануда. Тебе не говорили об этом, " + GetSexPhrase("юнец","девочка моя") + "? Я и так уже собирался к этому перейти. Делать мне было нечего на Родине, кроме как уток да оленей стрелять, так что я подался в Новый Свет. Походил с пиратами какое-то время забавы ради, а как надоело беззаконие творить - подался в наёмники.";
			link.l1 = "Не самая оригинальная история.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Может, у тебя есть получше? Ты мне лучше вот что скажи. Тебе телохранитель, случаем, не нужен? А то выглядишь ты как-то... слабовато. Беспокоюсь я за тебя, не пройдёшь ты такой далеко, хе-хе. Помни: королей " + GetSexPhrase("","и королев") + " делает свита! А свергают - из-за плохой свиты.";
			link.l1 = "И " + GetSexPhrase("каким же королём","какой же королевой") + " я стану с такой свитой, как ты? Корол" + GetSexPhrase("ём","евой") + " навозной кучи?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "Но-но! Я е" + GetSexPhrase("му","й") + " тут такое предложение делаю, а он" + GetSexPhrase("","а") + "...";
			link.l1 = "Пока я никакого предложения так и не получил" + GetSexPhrase("","а") + ". Сколько просишь за свои услуги... Томми?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "Двести пятьдесят дублонов сразу! Чтобы я убедился, что ты из себя что-то и сам" + GetSexPhrase("","а") + " представляешь, а не только строишь из себя невесть кого. Дворовые собаки порой ничем не хуже породистых, знаешь ли. А ежемесячно... думаю, договоримся.";
			link.l1 = "А ты не...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... обнаглел ли? Хех, я даже спорить с тобой не буду - сам"+GetSexPhrase("","а")+" видел"+GetSexPhrase("","а")+", как я попал в того рогоносца с маяка. С первого же выстрела! И никакого торга, если твоё недовольство было его началом - этим ты покажешь, что тебе просто-напросто не по карману такой профессионал, как я!";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "А вот и по карману! Двести пятьдесят золотых. Держи.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "С тем выстрелом тебе просто повезло. И ты решил воспользоваться этим и набить себе цену своим бахвальством. Обойдусь без такого 'профессионала' - много чести... и денег.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Ты прав, не по карману. Но только, потому что столько в карманах с собой не ношу. Будь здесь и никуда не уходи - схожу за золотом на корабль и вернусь.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "А ты не так плох" + GetSexPhrase("","а") + ", как я думал! Но ты уж постарайся, чтобы мне с тобой не было скучно! Да и талант ведь пропадёт так. Томми и " + pchar.name + "! Встряхнём этот Архипелаг!";
			link.l1 = "Научись соблюдать субординацию, это во-первых, Томми. А во-вторых - для тебя я капитан. Понял меня?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Хе, есть, капитан зануда, " + GetSexPhrase("сэр","мисс") + ".";
			link.l1 = "Ох, я уже чувствую, что начинаю жалеть об этом...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
				AddQuestUserData("BlackMark", "sSex", GetSexPhrase("ёс","есла"));
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
				AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("ся","ась"));
				AddQuestUserData("BlackMark", "sSex2", GetSexPhrase("был впечатлён","была впечатлена"));
			}
			
			// Продолжение через неделю в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Ну а ты просто идиот" + GetSexPhrase("","ка") + ", " + GetSexPhrase("юнец","девочка моя") + "! И совершенно не разбираешься в людях. Советую это исправить - такие долго не живут. Особенно на Архипелаге.";
			link.l1 = "Как-нибудь справлюсь и без тебя, Томми. Прощай.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Ты серьёзно? Здесь только что погибла куча солдат, гениальная твоя голова! Они наверняка пришлют ещё отряд через какое-то время. Нет, я, конечно, мог бы запереть дверь маяка и организовать оборону, но хочу ли я это делать? Нет и ещё раз нет.";
			link.l1 = "И что же ты предлагаешь?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Встретимся в местной пещере в сельве. Дам тебе пару дней, чтобы заработать на мои услуги - клинок ты держать умеешь, может, что и выйдет из этого.";
			link.l1 = "А теперь я скажу - ты серьёзно? Ты же там будешь, как крыса, загнанная в угол.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Только, если меня там искать целенаправленно, с большим отрядом. Так что, думаю, пронесёт. А теперь мне пора - наверняка уже скоро сюда ещё придут. Бывай!";
			link.l1 = "Угу, мне тоже пора, в таком случае.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Ага, вот и ты! Я уже начал было думать, что не твоё это - деньги зарабатывать. Иногда мне кажется, что люди подобные тебе с ними рождаются. А если нет - то дохнут в нищете, не проработав ни дня, как честные люди.";
			link.l1 = "Ну-ну, Томми. Не хочешь идти ко мне в команду - так не иди. Смотрю, тебе нравится сидеть в этой пещере.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Ты явно не прятал" + GetSexPhrase("ся","ась") + " и не устраивал" + GetSexPhrase("","а") + " засады за холмами и в ямах Ирландии во время сезона дождей, " + GetSexPhrase("юнец","девочка моя") + "! Но пойти с тобой всяко лучше, чем отсиживаться здесь. Впрочем, не обо мне сейчас - как там твои успехи с золотишком?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Вполне неплохо, а ты как думал? Держи своё золото.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Ещё не собрал" + GetSexPhrase("","а") + ". Решил" + GetSexPhrase("","а") + " проверить, не сбежал ли ты уже куда-нибудь.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Вот это уже другой разговор! Что делаем дальше... капитан?";
			link.l1 = "Для начала - покинем это сырое место, а то я сейчас чихать начну.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Эх, повоевать бы тебе с моё... Я вот в таких местах чувствую себя почти как дома.";
			link.l1 = "Смотрю, отставку получил и забыл об уважении да субординации, а, Томми? Ты не думай, я не побоюсь тебя этому заново научить, если придётся. А теперь идём.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Хе, Томми Айронс никогда не сбегал! И держит слово. А сдержишь ли его ты?";
			link.l1 = "Работаю над этим.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Как там твои успехи с золотишком?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Вполне неплохо, а ты как думал? Держи своё золото.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Ещё не собрал" + GetSexPhrase("","а") + ". Решил" + GetSexPhrase("","а") + " проверить, не сбежал ли ты уже куда-нибудь.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Слушай, капитан...";
			link.l1 = "Что такое, Томми?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "А у тебя не будет при себе лишнего патрона? Не пули, а полноценного, в бумажной обёртке.";
			link.l1 = "Какая-то очередная твоя шуточка? Я вроде регулярно даю тебе и пули, и патроны - что захочешь. И почему именно один патрон, а не горсть хотя бы?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Ты чего так в штыки воспринял" + GetSexPhrase("","а") + " мою просьбу? Я ж не жемчуга у тебя прошу, а просто патрон. Даже подождал, как в сельву выйдем, чтоб не отвлекать от дел в городе и не мешаться под ногами, как умалишённый какой-то, хе-хе. Так это... патрон есть?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Есть, есть. Держи. Только не вздумай с этим патроном надо мной как-нибудь шутить. Понял меня, Томми?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Прямо сейчас, при себе - нет. Я же не ношу в карманах один единственный патрон, размышляя, а вдруг Томми у меня его попросит?..";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Надо же, неплохо сказано, а ты у меня быстро учишься, хе-хе. Но, боюсь, на этом наши пути тогда расходятся.";
			link.l1 = "Ты что, серьёзно? Обиделся из-за патрона? Пойдём, на корабль сходим, раз он тебе так срочно нужен - хоть один, хоть десять, мне не жалко. Можешь даже сам наделать, сколько тебе нужно.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "Да не... Ничего в тебе, всё-таки, особенного. Хороший капитан всегда может снабдить свою команду всем, что ей нужно. Так что пойду я.";
			link.l1 = "А если бы мы были в открытом море и допили ром, а тебе ещё захотелось? Отвязал бы ялик и уплыл? Или так в воду прыгнул?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ха-ха-ха! Я, конечно, посмеялся, но сейчас даже хорошая шутка делу не поможет. Прощай, капитан зануда.";
			link.l1 = "Ну и чёрт с тобой, Томми. Прощай.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Ничего не могу обещать, хе-хе. Хорошая шутка всегда держит в тонусе. Но спасибо, конечно.";
			link.l1 = "Ладно, идём, шутник ты наш.";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Эй, капитан!";
			link.l1 = "Да, Томми?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "А ещё одного бумажного патрона у тебя не будет?";
			link.l1 = "А что стало с предыдущим? Да и в чём заключалась твоя шутка с патроном-то? Я весь месяц ждал" + GetSexPhrase("","а") + " от тебя какой-то дурацкой шутки, но так и не дождал" + GetSexPhrase("ся","ась") + ".";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "О, это будет убийственная шутка, поверь. Тебе понравится, хе-хе. Просто я ещё не собрал всё, что нужно. Ну так что насчёт патрона?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Держи. Надеюсь, мне и правда понравится твоя предстоящая шутка. И ты не ответил - куда предыдущий патрон дел? Я тебе и так их часто даю. Или патроны для боя ты держишь в одном месте, а для шуток - в другом?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Не ношу я с собой патроны для твоих дурацких шуток, Томми! Мог бы пару недель назад подумать головой и не один патрон попросить, а сразу целую партию!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "Я и подумал! Подумал, что тот, кто претендует на то, чтобы зваться моим капитаном, всегда держит всё необходимое для себя и команды.";
			link.l1 = "А я ни на что и не претендую, Томми. Я уже давно выбрал" + GetSexPhrase("","а") + " быть сам" + GetSexPhrase("им","ой") + " собой. Кому со мной по пути - прекрасно. На нет - и суда нет.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Хе, в этом мы с тобой похожи. Но к своему капитану у меня определённые требования. И более ты им не соответствуешь, " + GetSexPhrase("юнец","девочка моя") + ". На этом наши пути расходятся.";
			link.l1 = "Ты сейчас серьёзно? Из-за того, что у меня не оказалось чёртового бумажного патрона?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "Это не обсуждается. Обычно я советую людям делать то, что им по душе, и брать от жизни то, что им хочется. Тебе же посоветую побольше думать о своих людях. Прощай.";
			link.l1 = "А я тебе советую заняться головой - кажется, ты тогда приложился ещё сильнее, чем думал. Прощай, Томми.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Узнаешь ещё. Всему своё время, хе-хе.";
			link.l1 = "Ох и дурное у меня предчувствие, Томми...";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "У меня к тебе вопрос, капитан.";
			link.l1 = "Да, Томми, в чём дело?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "А так не догадал" + GetSexPhrase("ся","ась") + "? Быть догадливым весьма полезно по жизни, хе-хе. Ты, я, сельва... Примерно с месяц назад, тоже в сельве, у нас уже был такой разговор. Мне нужен ещё один бумажный патрон.";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Это уже становится забавной традицией, согласен? Месяц прошёл - Томми попросит патрон. Держи. Сколько же тебе их нужно для этой твоей шутки?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Да сколько уже можно, Томми?! Как долго это будет продолжаться?? Вам что, Железнобоким, выдавали всего по одному патрону, но перед каждым сражением?! Не обязан" + GetSexPhrase("","а") + " я всегда держать при себе хотя бы один патрон для твоих причуд, так и знай!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "Вообще-то, как мой капитан, ты обязан" + GetSexPhrase("","а") + " обеспечивать меня всем необходимым для сражений и не только.";
			link.l1 = "Ты явно что-то путаешь, Томми. Это ты обязан. Чётко соблюдать приказы своего капитана. Я всегда вас всех снабжаю всем необходимым - лекарствами, боеприпасами, ромом. В том, что ты не берёшь и не спрашиваешь патроны вовремя, а затем ведёшь себя, как попрошайка, виноват ты и только ты!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Ты так" + GetSexPhrase("ой","ая") + " умн" + GetSexPhrase("ый","ая") + ", а что же до сих пор ничего не добил" + GetSexPhrase("ся","ась") + " здесь? Я тебе скажу. Потому что ты не думаешь наперёд и ни к чему не готов" + GetSexPhrase("","а") + " никогда. А мнишь из себя невесть что, зануда. Я такого человека не признаю своим командиром, так что прощай.";
			link.l1 = "А ты вообще головой в целом не пользуешься! Скатертью дорога, шут проклятый!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Но так и не станет - этого достаточно, меня всё устраивает, хе-хе.";
			link.l1 = "Собрал, наконец, значит? Но для чего же?";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Да я просто шутил над тобой. Проверял, всё ждал, когда же в тебе снова проснётся недовольн" + GetSexPhrase("ый","ая") + " зануда.";
			link.l1 = "Странные у тебя шутки, Томми.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "И это тоже была шутка. На самом деле я их 'отбирал', а не 'собирал'. Я искал патрон, близкий к идеальному. Этот подойдёт. Да-а-а, с таким патроном пуля полетит далеко и по идеальной траектории. Совсем как тогда, когда я разнёс голову старины Ризли, ха-ха-ха!";
			link.l1 = "Старины Ризли, говоришь... Фрэнки-рогоносца, что ли? Кому ты голову у маяка отстрелил? Так, выходит, вы давно знакомы?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "Что? А-ать, чёрт, проболтался, ляпнул, не подумав. Да и наплевать - никогда не умел ни врать, ни секреты хранить.";
			link.l1 = "Я так понимаю, вторая пуля тоже предназначена кому-то весьма конкретному, верно, Томми?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Верно, верно, гениальная твоя голова. Что ж, я себя и свои цели знаю и не стыжусь. А потому мне как-то всё равно, что ты подумаешь, так что могу и рассказать, почему нет.";
			link.l1 = "Ну, рассказывай тогда. Мне явно не будет лишним узнать, что ты там задумал.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Ну так ты не перебивай тогда, как ты это обычно делаешь. Были со мной в роте два ублюдка - небезызвестный тебе Фрэнсис Ризли и Гэбриэл Кэллоу. Настоящие крысы! Даже больше, чем те кабинетные, что не хотели мне отставку давать, а таких, как понимаешь, ещё поискать надо.";
			link.l1 = "И что же они сделали? Особенно второй, Кэллоу. С его женой ты тоже переспал? И он также послал за тобой солдат в погоню?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Молчал" + GetSexPhrase("","а") + " бы, а? Хотя... я был бы не против, хе-хе. Но нет. Напали на нас, значит, сторонники короля. Тоже кавалерия. Их было намного больше. Гейб и Фрэнки бежали так, что пятки сверкали. А я остался с ребятами. И единственный выжил. Да и то - местами, как видишь. Многое забыл из детства и юности.";
			link.l1 = "И ты им хочешь отомстить за то, что они бежали? Понимаешь, не все бьются за идею. А выжить хотят все. Ну или почти все. Даже если кто-то сражается за Революцию, он мог туда попасть случайно. И пожалеть об этом.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ха, да если бы я охотился за каждой трусливой уткой - едва ли не весь мир пришлось бы перестрелять. Трусы - и чёрт с ними. Но они предали меня. Сказали всем, что я предал дело Революции и вырезал всю нашу роту по приказу сторонников короля. Соврал я тебе кое в чём, капитан.";
			link.l1 = "В чём же? Помимо того, что уже соврал о том, что Фрэнки тебя разыскивал только лишь из-за жены.";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "Но-но! Я не врал тебе, а просто умолчал. Знай разницу. А соврал я тебе в том, что никакой отставки и не было. А был трибунал. И повезло старине Томми - решили его не вешать, а отправить его на каменоломни в южные колонии. Барбадос, если быть точным.";
			link.l1 = "Да уж, повезло - так повезло. И сколько лет ты там проработал?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "А нисколько. Раз из-за этих крыс земная канцелярия меня приговорила, то небесная наверху решила спасти. И как только мы пересекли границы Архипелага, то сразу же ощутили его атмосферу - наш корабль взяли на абордаж пираты.";
			link.l1 = "Получается, вместо каменоломен и плантаций Барбадоса ты был продан пиратами в рабство? Ты говорил, что нисколько не проработал на каменоломнях.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "Я так-то сказал, что наверху решили меня спасти. Какое же это тогда спасение, хе-хе? Ты всё правильно понял" + GetSexPhrase("","а") + " - пираты одолели этих любителей издеваться над связанными и закованными людьми. Но бой всё равно был жаркий, не меньше здешнего треклятого солнца. И понесли наши спасители кое-какие потери. А потому предложили всем, кто пожелает, присоединиться к ним.";
			link.l1 = "И ты присоединился? Ты говорил, что ходил с пиратами.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "Да, чёрт возьми! И это были едва ли не лучшие годы моей жизни. Джек Миллз был капитаном с большой буквы - надеюсь, ты однажды станешь так" + GetSexPhrase("им","ой") + " же, как и он. А плавал на его 'Журавле' около двух лет, пока не...";
			link.l1 = "... пока не надоело творить беззаконие, как ты говорил? Почему же ты говоришь, что это были лучшие годы твоей жизни?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Эх... Да на самом деле, пока я не услышал о том, что те два предателя тоже оказались на Архипелаге. Да, да, да, сам знаю, говорил тебе, что надоело и прочая. И говорил, что мне плевать, что ты подумаешь. Так-то оно так, но я тебя ещё толком не знал. Как и не знал, как ты отреагируешь. Поэтому и сказал тогда несколько иные вещи.";
			link.l1 = "Да ты записной лжец, Томми! Но ладно, почему же с 'Журавля'-то ушёл?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Да потому что Джек хоть был и настоящим предводителем, но сказал, что не будет делать крюк ради одного человека - дожидаться его, играть с ним в месть и связываться с видными офицерами и властями вместо нападений на отдельные суда.";
			link.l1 = "Видными офицерами? Фрэнк вроде гражданский был.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Ну, не был, а стал. Он всегда был какой-то, знаешь, мутный. И в следующий раз, когда он попытался кое-кого подставить, его выгнали с позором. Он попытался поплавать на торговце, но не его это - честно работать. И в итоге он осел здесь.";
			link.l1 = "Всё равно не назвал" + GetSexPhrase("","а") + " бы его видным офицером.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Ну так ты о Гейбе-то не забывай. Он вон дома до лейтенанта дослужился. И получил назначение сюда, в Порт-Ройял, уже в качестве капитана корабля - пинка 'Принципио'.";
			link.l1 = "Не сказал" + GetSexPhrase("","а") + " бы, что звучит по-английски.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Верно подметил" + GetSexPhrase("","а") + "! Корабль переходил из рук в руки, что портовая девица, так что видал всякое - опять же, как она. Но не утратил ходовых качеств. Да и Гейб - умелый капитан, чёрт его побери.";
			link.l1 = "И Джек побоялся иметь дело с пинком? Так ли он хорош, как ты говоришь? На чём он сам ходил?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Хорош, хорош. Скорее, время тратить не хотел. К слову, о Джеке. Понравились мне парочка традиций, что впервые увидал у него - по доске пускать и вручать чёрные метки. Это натолкнуло меня на одну забавную идею в те дни.";
			link.l1 = "И какую же, Томми? Навряд ли бы он понял, передай ты ему чёрную метку. Так всё и было? Ты хотел вручить её, а он на тебя напал, как только завидел, после чего ты бежал на маяк, а он взял с собой отряд солдат, сказав им, что ты пират?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Мысль, конечно, интересная! И не так уж и далеко от истины, к тому же. По простой чёрной метке он бы ничего не понял. А вот по чёрной метке, сделанной из нашейного шёлкового платка, что был отличительной чертой только наших ребят - вполне. Я незаметно подложил ему её в карман. А потом сделал всё так, чтобы он увидел, как я иду на маяк. Дальше ты знаешь.";
			link.l1 = "А контрабандисты?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Случайно там оказались. Мне их даже немного жаль. Но только лишь немного, хе-хе.";
			link.l1 = "Как же, жаль ему, охотно верю.";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Ну, не о них сейчас. У нас есть рыба покрупнее и поважнее. Остаётся ещё Гейб. Тут будет посложнее. Нам нужно...";
			link.l1 = "Нам?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Ха-ха-ха, не это я имел ввиду, когда сказал, что хотел бы, чтобы ты был" + GetSexPhrase("","а") + " похож" + GetSexPhrase("","а") + " на Джека, капитан. Ну же, не будь занудой, я же вижу, как горят твои глаза!";
			link.l1 = "Скорее, мне и правда было несколько интересно узнать твою историю.";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ну, одно дело - узнать интересную историю, и совершенно другое - творить её самому! Так вот. Нам нужно будет оставить Гейбу ещё одну особую чёрную метку - она у меня есть. А затем пустим его по следу в бухту Портленд, где разберёмся с ним без лишних глаз и ушей.";
			link.l1 = "И где же мы её оставим?";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "В доме его, конечно! Что за вопрос? Он обзавёлся жильём в Порт-Ройяле. Так что в бухточке мы с тобою и причалим, чтобы сразу бежать с острова, если что-то пойдёт не так.";
			link.l1 = "А ты знаешь, где его дом?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Не-а. Но узнать это - невелика наука, поспрашиваем у трактирных забулдыг, эти и мать готовы продать, если купишь им чарочку-другую. Ну, что думаешь по поводу моего плана?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Что если он капитан корабля, приписанного к Ямайке, то и бывает он на нём в водах острова постоянно. Напасть под ложным флагом лучше, чем так сильно рисковать в самом городе.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Проверка пройдена", SKILL_SAILING);
				notification("Проверка пройдена", SKILL_ACCURACY);
				notification("Проверка пройдена", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Недостаточно развит навык (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Недостаточно развит навык (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Недостаточно развит навык (25)", SKILL_GRAPPLING);
			}
			link.l2 = "Что он не лишён недостатков, и ты многое оставляешь на удачу. Но в целом - осуществимо. Я с тобой, Томми. От одного избавился, не оставлять же другого?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "Думаю, что я не собираюсь участвовать в твоей мести и рисковать своими отношениями с Англией ради этой авантюры, где многое зависит от случая, Томми.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Рисковый ты человек, капитан! Ты мне наконец-то начинаешь нравиться. Всё бы ничего в твоей идее, но только Гейб на старичке 'Принципио' не такая уж и лёгкая добыча - гораздо опаснее других капитанов на подобном корабле.";
			link.l1 = "Я что, трус" + GetSexPhrase("","иха") + " по-твоему, что ли, Томми? Возьмём его на абордаж сами, там и поговоришь с ним по душам. И вручишь ему чёрную метку прямо перед тем, как он будет низложен.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Хех, ты-то, может, и не трус" + GetSexPhrase("","иха") + ", а вот он - да, хоть и умел. И на военного или даже пирата крупнее своего пинка сам не нападёт. А увидит вдали - спрячется под крылышком форта.";
			link.l1 = "Хм, а что насчёт торговых кораблей?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Да, это может сработать! Но, опять-таки, не крупнее барка или баркентины! Гейб мало того, что трусоват, так ещё и никогда не был настолько жадным, чтобы иногда это перевешивало.";
			link.l1 = "Будем надеяться, что сработает, Томми. Значит, барк или баркентина под ложным флагом, испанским или голландским. Идём, начнём подготовку ко встрече старых сослуживцев!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Я знал, что могу на тебя рассчитывать! Возможно, ты даже станешь однажды лучшим капитаном, чем был Джек. А насчёт удачи... Она привела меня к тому, что есть сейчас, так что я не прочь положиться на неё вновь. Тогда отправляемся?";
			link.l1 = "Да, не будем затягивать с этим. Чем раньше закончится это всё - тем лучше.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Хех, я, конечно, надеялся на обратное, но чего-то такого и ожидал - видать, кишка у тебя тонка для такого дела, "+GetSexPhrase("юнец","девочка моя")+". У любого настоящего капитана было хотя бы несколько случаев, как он незаметно разделывался с крысами из своих же. Или тех, кто не является официальным врагом.";
			link.l1 = "Видимо, я долж"+GetSexPhrase("ен","на")+" был"+GetSexPhrase("","а")+" повестись на эту провокацию и сказать, что я передумал" + GetSexPhrase("","а") + " и докажу тебе, что я настоящий капитан, а, Томми? Но я понимаю, как ты хочешь отомстить. И не буду заставлять уходить. Сколько времени тебе нужно на это? Доберусь к Ямайке к этому моменту.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ха-ха-ха, растёшь. Я почти готов уважать тебя за то, что не пов" + GetSexPhrase("ёлся","елась") + ". Но ждать и забирать меня потом не нужно - сам справлюсь. Сам начал, сам закончу. Всё-таки, я хочу видеть своим капитаном того, кто тоже на что-то готов ради меня. Так что прощай. Берегите Англию, ха-ха.";
			link.l1 = "Ты и правда странноват. "+GetSexPhrase("Готов ради тебя, хах... Как будто ты моя невеста","Я должна быть готова ради тебя? И кто из нас тут мужчина? Ты мне даже не жених, чтобы я ещё была на что-то ради тебя готова")+". Но как пожелаешь. Прощай! И удачи тебе с твоей местью, Томми.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Отлично, отсюда мы можем быстро убраться в случае чего. Возьми - передашь Гейбу от меня записку и чёрную метку, когда выяснишь, где он живёт и когда бывает дома.";
			link.l1 = "Ишь ты, раскомандовался, Томми. Я всё ещё твой капитан, забыл? А ты тут что будешь делать, пока я буду в городе?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Хех, забудешь тебя, зануда. А что, если Гейб увидит меня на улицах, не подумал" + GetSexPhrase("","а") + "? Или сразу тревогу поднимет, или вовсе скроется с острова ненадолго, трус проклятый. Не боись, я не собирался бездельничать на корабле, пока ты будешь в Порт-Ройяле. Я тут пока что засаду организую, хе-хе.";
			link.l1 = "Засаду, говоришь... Ладно тогда, Томми. Устрой хорошую встречу старому сослуживцу, ха-ха-ха!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "За твоё здоровье и за твою... и-ик...";
			link.l1 = "Слушай, приятель, а что в городе говорят про капитана Гэбриэла Кэллоу?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Про нашего с-старину Гейба?! Да только хорошее! А что, ик, такое?";
			link.l1 = "О, даже так? Рад" + GetSexPhrase("","а") + " это слышать. Да так, проблема возникла с пиратом одним. Комендант в основном только делами на суше занимается, а Его Светлость беспокоить не хочется - вдруг выгонит...";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Т-тогда тебе прямо туда, я тебе точно это говорю! Нет в городе капитана честнее и отважнее, чем Гейб! Он на хорошем счету у самого, ик, полковника д'Ойли. А ещё он плавает на корабле, когда-то принадлежавшем самому Николасу Шарпу, представляешь?";
			link.l1 = "Я ещё не настолько напил" + GetSexPhrase("ся","ась") + ", чтобы поверить в это, приятель.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "Д-да как же! Это же пинк 'Принципио'! Ни о чём, ик, не говорит?";
			link.l1 = "Ну, трофейный корабль, испанский, судя по всему, а что?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "А давно ли ты видел" + GetSexPhrase("","а") + " с-своими глазами пинк, а? И я уверен в том, что говорю, ик! Когда я трезвый, я точно так же его вижу.";
			link.l1 = "Ну, мало ли, может, заказ такой необычный.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "Нет, не мало ли! Никто не будет заказывать такое старьё, когда вокруг столько новых чертежей! Их уже почти как т-тридцать лет перестали строить на верфях! На нём плавал сам Ник, ик, говорю тебе!!";
			link.l1 = "Ладно-ладно, предположим, плавал, то есть, тьфу ты, ходил. И это корыто до сих не развалилось?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "нашем";
			else sStr = "вашем";
			dialog.text = "Ну, оно уже не такое быстрое, как в свои л-лучшие годы - прямо, как я после кружечки другой, ха-ха-ха! Но хороший капитан всё ещё сможет выжать из этого старичка что-нибудь. А ещё Гейб старается не подставлять его под прямые, ик, попадания.";
			link.l1 = "Так почему корабль не переименовали? Например, Корабль Его Величества 'Разящий', как его могли бы назвать при " + sStr + " старом режиме.";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Трац... трад... трад-традиция, ик, вот! Ник и сам его никогда не переименовывал после того, как бежал на нём с испанской плантации. Чтобы никогда не забывать пережитого. Эти испанцы - просто звери! И после одного боя у берегов Тендейлза...";
			if (startHeroType == 4)
			{
				link.l1 = "Тендейлза, да? Хах, последний раз я слышала это название лишь в детстве. Не думала, что кто-то всё ещё знает и помнит про эти заброшенные ныне скалы.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Тендейлза? Это вообще где?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Или это было у Хайрока... Н-нет, точно не у него... В общем, неважно! Ник одержал на пинке, на пинке, понимаешь?! Невероятную победу против брига 'Каракатица', что по его душу послал Десмонд Рэй Белтроп - барон Братства в те годы! Эти двое долго ещё портили потом друг другу кровь, пока Ник в итоге сам не пустил её Десмонду.";
			if (startHeroType == 4)
			{
				link.l1 = "Ого, впечатляет! Хотя, от Николаса иного и не ждёшь. Эх, вечно Шарпы и Белтропы то вместе, то порознь - видимо, история и правда повторяется время от времени.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Впечатляет. А как же Шарп расстался с кораблём? Продал на верфи?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Е-если бы. Ник после того абордажа оставил корабль, когда тот дал небольшую, ик, течь. А потом с большим приливом пинк принесло на берег, прямо неподалёку от города.";
			link.l1 = "Как будто кому-то была интересна эта развалина. Ладно ещё, если бы это была хотя бы каравелла или бриг...";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "О-однако военным всё же стало интересно! Практичные, ик, ребята. Увидели - корабль, под английским флагом. А название - испанское. И оставили, шутки ради или поленились. Ник через несколько лет почил, а корабль продолжал переходить из рук в руки среди военных и не только, поочерёдно. Но всегда - только кровавым путём.";
			link.l1 = "Завязывал бы ты. А то какая-то очередная байка про корабль-призрак получается. А Гейб ведь живой и настоящий. Так что пойду-ка я, пожалуй, к нему. Э-э, а куда идти-то, не знаешь?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ха-ха! Конечно, ик, знаю! Да все об этом знают! Старина Гейб живёт у старой ветряной м-мельницы. Просто обойди таверну, и подними голову вверх... и-ик!";
			link.l1 = "Значит, не заблужусь. А когда он дома бывает? А то служба, все дела.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "Это ты в-верно говоришь! Дел у него, ик, немало. Дома он бывает только по вечерам, с десяти. А встаёт ровно в шесть, каждый день, сам. Железная дисциплина! И тут же идёт к Его Светлости.";
			link.l1 = "Спасибо тебе большое! А то совсем уже житья никакого с этими пиратами.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Неужели ты... Румба? Я слышал о тебе... но ты раньше никогда не нападала на своих!";
				link.l1 = "И не нападаю. У меня нет проблем со своей страной. Только с тобой... Гейб.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Ты не торгаш...";
				link.l1 = "Только сейчас это понял, Гейб? А мне говорили, что ты осторожен и даже трусоват. Совсем жадность разум помутнила? Ни один торгаш не пойдёт навстречу тебе вместо того, чтобы избежать абордажа любой ценой.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "И какие же? Мы могли бы спокойно всё обсудить у меня или даже у тебя на шканцах. А ТЫ что здесь делаешь?.. Кажется, теперь мне всё понятно...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "И правда. Так кто ты такой? Хотя нет, чёрт с тобой. А вот ты...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Неужели... Томас, ты ли это?..";
			link.l1 = "О да, Гейб. И я пришёл наказать тебя за то, что ты тогда на меня наговорил.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Наказать?! Наговорил?! Следи за своим поганым языком, Томас! Если кто из нас и заслуживает наказания - это ты! Ты сказал, что приведёшь подкрепление! И мы ждали их, гибли под ударами королевской кавалерии! А ты!..";
			link.l1 = "А что я?! И я побежал за ними! Но меня догнал ещё один отряд! Чёртовы сторонники Карла были повсюду, мать их! Приложили меня так, что чуть не подох! Хорошо, что за мёртвого приняли. Но знаешь, что я успел увидеть, Гейб?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "Что же, Том? Ты уже готов любую небылицу выдумать, чтобы " + GetSexPhrase("этот идиот","эта дурёха") + " продолжал" + GetSexPhrase("","а") + " тебе верить?!";
			link.l1 = "Хе, этот человек меня всё равно не предаст. Ведь он" + GetSexPhrase("","а") + " же не крыса, как некоторые.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Да у не" + GetSexPhrase("го","ё") + " просто выбора нет! Напасть на корабль английского флота!";
			link.l1 = "О, у не" + GetSexPhrase("го","ё") + " был выбор с самого начала. И он" + GetSexPhrase("","а") + " выбрал" + GetSexPhrase("","а") + " помочь мне. И у вас с Фрэнком выбор был. Вы выбрали бежать, чтобы не подохнуть. А позже вернулись и нашли меня, полуживого. И рассказали вашу мерзкую ложь на трибунале. Вы знали, что никто не станет меня слушать, потому что меня ударили по голове, и я потерял память!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Тебя бы и так никто не послушал. Ты всегда был... стукнутым, Томас.";
			link.l1 = "О, то есть ты уже и не скрываешь того, что сделал в тот день. А у меня для тебя кое-что есть, Гейб. Чёрная метка. Но какой смысл её тебе давать сейчас, когда корабль захвачен, и мы вот-вот выпустим тебе кишки, хе-хе-хе-хе-хе...";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Ну что же, Гейб, ты низложен, хе-хе. Давно хотел это сказать. Жаль, что ты уже не слышишь. Хотя, может, даже и слышишь. В Аду.";
			link.l1 = "Полно, Томми. Хоть он это и не услышал, но он видел и знал, что это именно твоя затея и месть. И ничего не мог поделать с тем фактом, что мы вот-вот расправимся с ним.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Хех, а ведь ты права! Спасибо, что поддержала. Знаешь, я думал, что ты просто смазливая избалованная мордашка в откровенном наряде, которой купили корабль для небольших прогулок. А ты - чертовски хороший капитан! Уверен, ты бы дала фору даже Джеку!";
			}
			else
			{
				dialog.text = "Хех, а ведь ты прав! Чертовски верно! Спасибо, что помог мне в этом. Знаешь, мне кажется, что ты ничуть не хуже Джека, как капитан. Или даже лучше!";
			}
			link.l1 = "О, ты льстишь мне. Спасибо и тебе за такое сравнение. Наверное.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Отнюдь. Никакой лести. Как ты уже мог" + GetSexPhrase("","ла") + " заметить, я редко кого-либо вот так хвалю. Так что заткнись и порадуйся, что я о тебе такого хорошего мнения.";
			link.l1 = "Не сказал" + GetSexPhrase("","а") + " бы, что мне нравится то, как ты это подаёшь, пусть я и рад" + GetSexPhrase("","а") + " тому, что ты в целом думаешь обо мне, как о хорошем капитане. Но... субординация, Томми, субординация.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Ой, да перестань! Мне кажется, что произошедшее весьма сблизило нас, Элли, и мы с тобой можем стать большим, чем просто капитан и офицер. Признайся, не мне, так себе - ты тоже чувствуешь.";
				link.l1 = "Разве что в твоих мечтах, Томми. И я тебе не Элли. Но, думаю, теперь ты можешь называть меня Румбой.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Ой, да брось ты, зануда! Мне кажется, что мы с тобой уже не просто капитан и его офицер, а самые настоящие друзья. Ну разве ты не того же мнения?!";
				link.l1 = "Хех... Возможно. Всяко лучше, когда ты друг, нежели враг. А этикет и лизоблюдство - явно не твоё, и к этому остаётся лишь привыкнуть.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Ну вот, другое дело! У меня для тебя... подарок, капитан.";
			link.l1 = "Ого, надо же! И что это? Что? Ты хочешь, чтобы и я был" + GetSexPhrase("","а") + " низложен" + GetSexPhrase("","а") + ", а, Томми? Решил сам стать капитаном? Ха-ха-ха! Ты же говорил, что мы друзья.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "Да нет же, " + GetSexPhrase("придурок","дурёха") + ". Знаешь, я начинаю думать, что как только я вышил череп и кости на этом платке, он начал приносить мне удачу. Не могу объяснить. Мне как-то и раньше всегда везло. Бери. И ещё... коль захочешь, ты всегда можешь одолжить у меня мой верный палаш, и доспех... То, что от него осталось, ха-ха! Пригодится! Ты далеко пойдёшь. И я хочу быть свидетелем этого. А не хочу, чтобы тебя убило шальной пулей.";
			link.l1 = "Спасибо, дружище! Постараюсь. Ну а ты - смотри и восхищайся, ха-ха-ха!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Восхищаться, ага, конечно, ха-ха. Ладно. Что решил" + GetSexPhrase("","а") + " делать с этим кораблём? С одной стороны, толку от него уже мало. С другой - таких больше нет. И вряд ли уже когда-либо будут снова.";
			if (startHeroType == 4) 
			{
				link.l1 = "Пока ещё не решила... Знаешь, Томми. Я чувствую какую-то связь с этим кораблём. Не могу объяснить. Так что давай выкинем этот вонючий труп отсюда для начала. Если в трюме нет течи, то, скорее всего, я заберу этот корабль себе.";
			}
			else
			{
				link.l1 = "Не знаю, Томми. Ещё не решил. Ну а пока - давай избавимся от тела Гейба. На случай, если всё же оставим корабль себе.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Да уж, лихо ты уделал эту древнюю посудину, капитан! И хоть я и желал прикончить Гейба своими руками, но да не стану гневить Создателя.";
			link.l1 = "Это было бы лишним, Томми. Надеюсь, теперь твоя душенька довольна.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Ха, ещё бы! Спасибо, что помогла. Знаешь, Элли...";
				link.l1 = "Всегда пожалуйста, однако я тебе не Элли, Томас.";
			}
			else
			{
				dialog.text = "Никогда в жизни не был так счастлив! Спасибо, что помог мне в этом. Знаешь, мне кажется, что ты ничуть не хуже Джека, как капитан. Или даже лучше!";
				link.l1 = "О, ты льстишь мне. Спасибо и тебе за такое сравнение. Наверное.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Томас? Даже не Том, не то что Томми? Хех, какие мы серьёзные. Однако я хотел сказать, что ты не просто смазливая мордашка, выставляющая свои прелести напоказ, а настоящий капитан. Лучший, с которым я имел дело!";
				link.l1 = "Ну что же, спасибо, Том.";
			}
			else
			{
				dialog.text = "Отнюдь. Никакой лести. Как ты уже мог заметить, я редко кого-либо вот так хвалю. Так что заткнись и порадуйся, что я о тебе такого хорошего мнения.";
				link.l1 = "Не сказал бы, что мне нравится то, как ты это подаёшь, пусть я и рад тому, что ты в целом думаешь обо мне, как о хорошем капитане. Но... субординация, Томми, субординация.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Вот, уже Том, оттаиваешь потихоньку у меня, хе-хе. Это как раз то, что я ещё хотел тебе сказать. Мне кажется, что то, через что мы недавно прошли, очень сблизило... нас. Ты и сама это чувствуешь, не правда ли?";
				link.l1 = "Нас? Нет никаких “нас”, Томми, дорогой мой. И не будет. В первую очередь, я твой капитан. И всегда таковой и буду оставаться. Но ты можешь называть меня Румбой, если тебе от этого будет легче.";
			}
			else
			{
				dialog.text = "Ой, да брось ты, зануда! Мне кажется, что мы с тобой уже не просто капитан и его офицер, а самые настоящие друзья. Ну разве ты не того же мнения?!";
				link.l1 = "Хех... Возможно. Всяко лучше, когда ты друг, нежели враг. А этикет и лизоблюдство - явно не твоё, и к этому остаётся лишь привыкнуть.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Хех, как скажешь. Ну, вне зависимости от твоего ответа, я бы хотел вручить тебе подарок. В нашем случае - закрепить нашу дружбу. Держи.";
			}
			else
			{
				dialog.text = "Ну вот, другое дело! У меня для тебя... подарок, капитан.";
			}
			link.l1 = "Ого, надо же! И что это? Что? Ты хочешь, чтобы и я был"+GetSexPhrase("","а")+" низложен"+GetSexPhrase("","а")+", а, Томми? Решил сам стать капитаном? Ха-ха-ха! Ты же говорил, что мы друзья.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "Да нет же, "+GetSexPhrase("придурок","дурёха")+". Знаешь, я начинаю думать, что как только я вышил череп и кости на этом платке, он начал приносить мне удачу. Не могу объяснить. Мне как-то и раньше всегда везло. Бери. И ещё... коль захочешь, ты всегда можешь одолжить у меня мой верный палаш, и доспех... То, что от него осталось, ха-ха! Пригодится! Ты далеко пойдёшь. И я хочу быть свидетелем этого. А не чтобы тебя убило шальной пулей.";
			link.l1 = "Спасибо, дружище! Постараюсь. Ну а ты - смотри и восхищайся, ха-ха-ха!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Проверка чести пройдена", "None");				//"Reputation Check Passed"
			if (startHeroType == 4)
			{
				dialog.text = "Кому нужно в такое вре... Кхм-кхм, прошу прощения, мисс. " + TimeGreeting() + ". Чем я могу вам помочь? У вас очень встревоженный вид.";
			}
			else
			{
				dialog.text = "Кто, что? Кому нужно в такое время? Хм-м-м, у вас весьма озабоченный вид, сударь. Чем могу помочь?";
			}
			link.l1 = "Прошу прощения, я не собирал"+GetSexPhrase("ся","ась")+" тревожить ваш сон, капитан Кэллоу. Меня зовут " + GetFullName(pchar) + ", и я к вам от одного из ваших сослуживцев.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Ну, как это, не собирались, раз уж вы здесь? Уж не обворовать ли вы меня хотели? О ком речь? У меня их было очень много - как в Старом Свете, так и в Новом.";
			link.l1 = "Напротив - хотел"+GetSexPhrase("","а")+" кое-что оставить в одном из ваших сундуков. Или даже на столе, чтобы раньше заметили. Речь же пойдёт о человеке из очень давнего вашего прошлого. Вот, посмотрите и прочтите сами.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "Чёрная метка? Не припоминаю пиратов среди своих сослуживцев. Или кто-то из ребят в них подался? Шёлк?.. Неужели\n(читает) Томас... Удивлён, что человек вроде вас имеет дело с этим... подлецом.";
			link.l1 = "Я прошу прощения, но не вам называть его подлецом. Ведь это вы бежали с поля боя и оклеветали Тома. Возможно, вы потом раскаялись в содеянном и стали образцовым офицером уже на Архипелаге, но всё же.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Он вам так сказал? Неудивительно, он знал, какого человека искать - кого-то вроде вас, кто легко бы поверил. Язык-то у Томаса всегда был хорошо подвешен. Вы совершенно не знаете ни его, ни того, как всё было на самом деле, ни во что ввязываетесь. Могу рассказать - всё равно теперь не усну.";
			link.l1 = "Ну, просто послушать лишним никогда не бывает. Рассказывайте, капитан Кэллоу.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Значит, наш Томас сказал, что я сбежал, а потом оклеветал его? Ну так знайте, что всё было с точностью до наоборот! Когда к нам приближалась королевская кавалерия, Том сказал, что отправился за подкреплением. И мы не стали отступать, и ждали. Погибла почти вся наша рота! Сбеги он молча, мы могли бы отступить и выжить! А по итогу выжили только я, Фрэнки и Томас, будь он проклят.";
			link.l1 = "То есть вы хотите сказать...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "То есть я хочу сказать, что кровь наших ребят точно так же на руках Тома, как и на руках роялистов! Ему ещё повезло, что он был приговорён к каторге, а не повешению! И он ещё смеет мне таить обиду и вызывать на дуэль! Да он её недостоин!";
			link.l1 = "Значит, вы не явитесь туда? Вы же понимаете, что это будет означать. Законы чести писаны для всех.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Понимаю, конечно. И именно поэтому и явлюсь. Нужно закончить то, чего не захотел сделать наш республиканский суд из-за прошлых боевых заслуг Тома. А вы... вы выглядите достойным человеком, судар" + GetSexPhrase("ь","ыня") + ". Советую вам получше выбирать знакомых. И не иметь дел с Томом и ему подобными.";
			link.l1 = "Но Томас теперь мой подчинённый, офицер на корабле. "+GetSexPhrase("Я присмотрю за ним и не позволю творить новые бесчестья, если он переживёт встречу с вами.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "И как бы вы тогда поступили на моём месте, капитан Кэллоу?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Эх, да раз уж если Том смог убедить вас в том, что наговорил, то ему не составит труда сделать это снова.";
			link.l1 = ""+GetSexPhrase("Однако по законам чести я не могу предать его. И","Я")+" несу ответственность за своих людей. Я не буду ему уподобляться. И впредь буду внимательнее и критичнее относиться к нему, если он выживет.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "Тяжёлое решение. Но не буду вас переубеждать. Что же, до свидания, "+GetSexPhrase("сударь","мисс")+" - мне ещё готовиться ко встрече с Томом.";
			link.l1 = "До свидания, капитан Кэллоу.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Позвольте свершиться правосудию! Помогите мне одолеть Томаса, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+". Он редкий мерзавец и трус, но великолепный стрелок, это будет нелегко. Но вот вместе...";
			link.l1 = "Хм, помочь одолеть Тома? Много ли чести в такой дуэли? Вы можете разобраться сами, а я попросту не буду мешать.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Да зная его, меня навряд ли ждёт честная дуэль, и сидя верхом на заборе, вы лишь потворствуете несправедливости. Я ведь прав?";
			link.l1 = "Видимо, вы лучше меня знаете Тома, и какой он на самом деле. Ваша правда - в бухте Портленд он уже готовит засаду. И надеется на мою помощь - впрочем, как и вы сейчас.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Тогда это никакая не дуэль, а обычная драка. Но я не предлагаю вам убивать Томаса нам самим. Арестуем его! Я возьму солдат, и мы закончим то, что не смогли сделать в Старом Свете. А если его опять попытаются оправдать - я напишу письмо полковнику. Или даже приглашу его сюда уже к началу судебного процесса. Если он не захочет сложить оружие - сам виноват.";
			link.l1 = "Что ж, это уже звучит гораздо лучше.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Рад это слышать, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+"! Я понимаю, возможно, вам сейчас непросто принимать подобное решение, но уверяю вас - вы сделали правильный выбор. И, чтобы вы убедились в этом, я вам ещё кое-чем помогу.";
			link.l1 = "Надеюсь, что и правда правильный. Чем же, капитан Кэллоу?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Этим. Держите. Не дарю, но даю на время - Томас, как я уже говорил, весьма хороший боец, и лучше идти на него с хорошим оружием, а не ржавой железкой. Подарил мне эту красавицу сам полковник д'Ойли, но я предпочитаю палаши. Вам же, как мне кажется, она прекрасно подойдёт.";
			link.l1 = "Это точно. Великолепная рапира. Спасибо вам.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Не благодарите - одалживаю, а не дарю, помните? Ну а теперь отправляйтесь в бухту и как следует подыграйте нашему дорогому Тому, а я пока схожу за подмогой. До встречи на месте.";
			link.l1 = "До встречи, капитан Кэллоу.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Кто вы, мисс? Вы, верно, ошиблись адресом. Я, э-э, не заказывал никаких услуг на ночь.";
				link.l1 = "Элен МакАртур. И попридержите ваши желания в узде, мистер Кэллоу - я девушка приличная. Жарко мне от нашего климата, даже ночью. Не стыдно вам было такое говорить незнакомой девушке? Мне говорили о вас, как об образцовом офицере.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Кто вы, и что вам нужно? Не нравится мне ваша ухмылка, сударь.";
				link.l1 = "" + GetFullName(pchar) + ". А вы не слишком гостеприимны, мистер Кэллоу.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Посмотрел бы я на вас, если бы к вам в такое время пришли незнакомые люди.";
			link.l1 = "А мне сказали, что в другое время вас попросту не бывает дома.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Ну ещё бы, ведь у меня есть служба, долг и честный труд - слова, неизвестные вам, судя по вашему виду.";
			link.l1 = "Какая самоуверенность! Хотя, иначе бы вам не удалось убедить полковника д'Ойли и остальных в своей честности. Мне от вас ничего не нужно, Гейб, а вот одному вашему старому знакомому... держите.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Убедить? Гейб? Я бы попросил! Хотя, чувствую, это будет бесполезно. Чёрная метка? Так вы пират" + GetSexPhrase("","ка") + "? Погодите-ка... шёлк... может ли это быть\n(читает записку) Томас, чёртов мерзавец, ты так и не простил нас с Фрэнком за то, что мы на тебя доложили, ха-ха-ха!";
			link.l1 = "А кто-то бы подобное простил? И, теперь уже, я бы попросил" + GetSexPhrase("","а") + "! Том - мой офицер на корабле и заслуживает уважения. Он один из лучших стрелков Архипелага.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Я и не говорил, что он плохо стреляет. Вы, я вижу, плохо знаете Томаса. Это он предал всех нас. Но не вижу смысла даже распинаться перед вами - вы явно друг друга стоите.";
			link.l1 = "Вот и прекрасно. Россказни попридержите для д'Ойли и всяческих наивных простаков. Если вы и правда такой храбрец и человек чести, как про вас говорят, то вы обязаны принять вызов и явиться сейчас же. Так вы принимаете его?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Принимаю, принимаю. А теперь убирайтесь из моего дома, пока я не кликнул подмогу.";
			link.l1 = "С удовольствием, Гейб.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Ты чего так дёргаешься? Испугал" + GetSexPhrase("ся","ась") + ", что ли?";
				link.l1 = "Да кто угодно бы занервничал, увидев, как на него бежит человек с мушкетом - не сразу тебя узнал" + GetSexPhrase("","а") + ". Что ты здесь делаешь, Томми?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Как всё прошло? Эй, эй, ты чего остановил" + GetSexPhrase("ся","ась") + ", как вкопанн" + GetSexPhrase("ый","ая") + ", и смотришь на меня так? Напугал" + GetSexPhrase("","а") + ", хе-хе.";
				link.l1 = "Это ещё кто кого напугал! Ну кто так резко выбегает?! Мы же договаривались встречать гостей в бухте.";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Хех, ну, возможно. Да устал ждать - что наших дорогих гостей, что тебя. И решил, что это место больше подходит для хорошей засады. В конце концов, я ведь охотник, а не бретёр какой.";
			link.l1 = "Вот оно как...";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Ага. Так что, ты оставил гостинец в доме Гейба? Долго ты. Я бы в разы быстрее управился, если бы мне можно было появиться в городе. Чего это у тебя глазёнки бегают, а, капитан? Больше списать на то, что не ожидал меня увидеть, не выйдет.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Вызывающий доверие) Да нервничаю я. Гейб трус, но не дурак. Что, если сюда придёт целый взвод солдат вместо него? Или они сейчас потопят наш корабль?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Вызывающий доверие", "Trustworthy");
			}
			else
			{
				link.l2 = "Да Гейбу на глаза попал" + GetSexPhrase("ся","ась") + ", когда оставлял" + GetSexPhrase("","а") + " ему всё. Пришлось бежать.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Не открыта способность", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Хех, понимаю тебя - я и сам не до конца уверен, сработает ли. Для тебя что-то настолько серьёзное в первый раз, да? Ничего, бывает. Я всё предусмотрел. Если придут солдаты, и без Гейба - просто сваливаем. Если с Гейбом - я всажу ему пулю меж глаз, и опять же, сваливаем. Ну а если к бухте придёт корабль - бежим в Марун-Таун - туда они сунуться не посмеют, а там решим, что делать дальше.";
			link.l1 = "Вижу, ты и правда всё предусмотрел, Томми.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Ну а то! А теперь давай дожидаться нашего гостя...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ха-ха, да уж, вор из тебя - что из меня сторонник монархии! А почему это ты избегаешь смотреть мне в глаза... капитан? Вы ведь на самом деле трепались с Гейбом, да?";
			link.l1 = "Да нет же, что ты такое говоришь, о чём мне вообще с ним разговаривать...";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Да потому что вы все знатные болтуны. Только и можете, что лясы точить, а не делом заниматься. Ну, и что же тебе наговорил наш милый Гейб?";
			link.l1 = "А разве это имеет значение, Томми?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Откровенно говоря - нет. А вот не вонзишь ли ты мне нож в спину - да. Судя по всему, уже вонзил" + GetSexPhrase("","а") + ". Он ведь уговорил тебя встать на его сторону, когда всё начнётся, ведь так?";
			link.l1 = "Нет. Не совсем. Сложи оружие, Томми. И я обещаю, что с тобой ничего не случится. Максимум - отработаешь на каменоломнях. Я попрошу об этом Гейба. Если придётся - полковника д'Ойли.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Тоже мне благодетель" + GetSexPhrase("","ница") + ". Чтобы я выхаркал свои лёгкие за годы на каменоломне?! Больше я на тюремные корабли не вернусь. Никогда. Ну а ты... мне следовало догадаться, что ты - очередная крыса. Есть что-то такое в твоей внешности. Разберусь с тобой перв" + GetSexPhrase("ым","ой") + ", чтобы потом было проще с Гейбом.";
			link.l1 = "Ты не оставляешь нам всем выбора!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Ого, смотрю, вы уже справились, "+GetSexPhrase("сударь","сударыня")+". А я отряд собирал, думал, численный перевес заставит Тома подумать дважды и сложить оружие.";
			link.l1 = "А вы не спешили, капитан Кэллоу.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Говорю же вам, ребят собирал. Лучшие из лучших. Том ведь непростой соперник. Ну, вы это и сами знаете. Отличная работа, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+". "+GetSexPhrase("Я вами горжусь, молодой человек","Должен признать, в вас одинаково соединились красота, ум и мастерство, юная леди")+". Как я вам это сказал ещё при знакомстве, вы приняли верное решение. Теперь правосудие восторжествовало.";
			link.l1 = "Хорошая работа, которую сделали за вас. Ещё бы вы не гордились, ведь вы успешно забрали все каштаны из огня чужими руками.";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Ну, я тоже " + GetSexPhrase("непростой соперник","непростая соперница") + ", как вы могли только что заметить. Но благодарю вас, сэр. Правосудие - не пустой звук для меня.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "И это похвально, "+GetSexPhrase("молодой человек","девушка")+". Однако осталось сделать ещё кое-что для завершения этого прекрасного дня.";
			link.l1 = "Хм, и что же? Том ведь уже повержен.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "У вас осталось кое-что, что принадлежит мне. 'Одолжить, а не подарить', помните? Верните мне мою прекрасную итальянскую рапиру. Это ведь не просто зубочистка, а памятная вещь - подарок самого полковника д'Ойли.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Тут такое дело, капитан Кэдддоу... рапиры больше нет. Я её потерял. Мне очень жаль.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "А, конечно. Прошу. Не подумайте - я не собирал" + GetSexPhrase("ся","ась") + " её красть. Но врать не буду - хотел" + GetSexPhrase("","а") + " бы себе оставить. Но держите, капитан Кэллоу.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "У меня есть к вам предложение получше, капитан.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Но вы же сами называете её зубочисткой. Да и рапиры вы не любите. А я же, в свою очередь, заслуживаю награду.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Да кто угодно хотел оставить у себя эту красавицу! Благодарю, что вернули её мне. Многие бы заупрямились на вашем месте.";
			link.l1 = "Не благодарите, сэр - в конце концов, ведь это ваше. Полагаю, здесь мы с вами закончили?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "Мне это неинтересно. Просто верните рапиру, и мы с вами разойдёмся на хорошей ноте, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+".";
			link.l1 = "Я так понимаю, эта рапира вам дорога, потому что вы любите оружие с историей, мне правильно кажется? У меня как раз есть такое же, причём вы даже будете регулярно им пользоваться!";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Даже пользоваться буду? Вы так в этом уверены? Что ж, не обещаю, что мы договоримся, но я вас слушаю. Вы правы, мне интересно оружие с историей. Но эта рапира - подарок полковника. И поэтому так мне дорога.";
			link.l1 = "Вы ведь упоминали, что любите палаши. Держите. Он принадлежал нашему дорогому Томми. Только представьте, через что это оружие прошло за несколько лет. И через что ещё пройдёт вместе с вами.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Умеете вы убеждать, " + GetSexPhrase("юноша","девушка") + "! Орудовать палашом Томаса... какая ирония. Эх, ну что же - забирайте рапиру. Однако я отрываю её от сердца, так и знайте.";
			link.l1 = "Я рад" + GetSexPhrase("","а") + ", что мы смогли договориться. Думаю, на этом мы с вами прощаемся, капитан Кэллоу?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "ЧТО?! Да как это... Как можно было потерять целую, мать её, рапиру?! Вы "+GetSexPhrase("идиот, молодой человек","дура")+"!";
			link.l1 = "Успокойтесь, чёрт возьми! Это же просто рапира. Вы всё равно бы ею никогда не пользовались. Разве не главное, что мы одолели Тома?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Просто рапира?! Да она была моим сокровищем! Это подарок самого полковника д'Ойли! И плевать, что я ею не пользовался!";
			link.l1 = "Тогда вам не следовало давать её мне, разве нет?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "А вам бы сейчас следовало держать рот на замке, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+". Глядишь, разошлись бы мирно. Но теперь... теперь мне хочется преподать вам урок, "+GetSexPhrase("молодой человек","девушка")+".";
			link.l1 = "Да я видал я таких учителей в гробу, сударь.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Заслуживаете, само собой. Однако вы не можете отнять у офицера его именное наградное оружие просто потому, что когда-то помогли ему, согласны?";
			link.l1 = "Я бы согласил"+GetSexPhrase("ся","ась")+", но ведь вы ею всё равно не пользуетесь. У вас она будет висеть на гвозде. А со мной найдёт достойное её применение. Не будет же полковник д'Ойли проверять у вас, а не дели ли вы её куда, не правда ли?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Это не предмет для обсуждений, "+GetSexPhrase("молодой человек","девушка")+". Я вам с самого начала сказал - это не подарок. Отдайте рапиру. Сейчас же.";
			link.l1 = ""+GetSexPhrase("Я вам не ваш солдатик","А я не портовая девка")+", чтоб приказы мне отдавали. Я такой же капитан корабля, как и вы. Рапира остаётся у меня, нравится вам это, или нет.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Видимо, Томас успел на вас уже повлиять. Ну так умрите за эту рапиру, раз она вам так нужна!..";
			link.l1 = "Могу сказать то же самое!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Вот, возьмите. Мне это совершенно ни к чему. Ну а вам - на память о сегодняшнем дне. Постарайтесь впредь быть менее доверчивы. И не позволяйте всяким пройдохам вроде Томаса впутывать вас в свои грязные дела.";
			link.l1 = "Хех, вы мне вручаете чёрную метку, капитан Кэллоу?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Ну, мы ведь оба с вами не пираты, верно, "+pchar.name+"? Пусть будет напоминанием. Берегите себя, такие люди нужны Архипелагу. "+GetSexPhrase("Быть может, я предложил бы вступить в военный флот и написал рекомендацию полковнику д'Ойли...","")+"";
			link.l1 = "К сожалению, не могу принять ваше предложение, капитан.";
			if (startHeroType == 3)
			{
				link.l1 = "Хм, я подумаю об этом, хорошо так подумаю. Буду знать, к кому в таком случае обратиться, капитан.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Прощайте, сэр.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Как знаете. Что ж... до свидания, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+". Вы заслужили носить с собой то, что осталось от этого платка Железнобоких после рук Томаса. Прощайте.";
			link.l1 = "Прощайте, сэр.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Мне не нравится ваш тон, "+GetSexPhrase("мистер","мисс")+". К чему вы клоните?";
			link.l1 = "Вы тянули время, собирая своих 'лучших из лучших'. Для чего? Побить одного человека? Достаточно было взять первых попавшихся солдат, патрулировавших город в тот момент, и прийти мне на выручку!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Чтобы они стали пушечным мясом?! Том был не просто таким же солдатом, как они. У него были совершенно другие подготовка и опыт - он чёртов Железнобокий, как и я! Как вы этого не понимаете?";
			link.l1 = "О, напротив, понимаю. На этот случай были мы с вами - скрестить клинки с Томом, чтобы ребята его скрутили. А ещё вы сказали - такой же, как и вы. Вы ведь тоже Железнобокий. Одна рота. Вы так боялись сразиться с ним лично?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Да как вы смеете обвинять меня в трусости, "+GetSexPhrase("юноша","девушка")+"! Спросите любого - и вам подробно расскажут, какие подвиги я совершил ради этого города.";
			link.l1 = "Я ещё не закончил. И уже начинаю сомневаться, а своими ли руками были совершены эти ваши 'подвиги'? Вы просто хотели, чтобы мы с Томом перебили друг друга, а вы получили все лавры. В очередной раз.";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "Мне надоели ваши обвинения, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+". Хотите конфликт? Вы его получите. Прямо сейчас.";
			link.l1 = "Правда глаза колет, да... Гейб?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Гейб! Сколько лет, сколько зим! А у тебя всё такой же самодовольный вид, чёрт бы тебя побрал!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Томас! Ещё бы я не был доволен, ведь сегодня я наконец-то своими руками закончу то, что нашему правосудию не удалось добиться несколько лет назад. И, поскольку я в хорошем расположении духа, я разрешаю тебе сложить оружие и проследовать за нами. Возможно, тебя даже вновь отправят на каторгу. В таком случае я лично доставлю тебя, куда нужно.";
			link.l1 = "Хех, ну так попробуй заставь меня! Думаешь, парочка парней рядом с тобой меня остановит?!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "А кто сказал, что со мной только они? Я говорю сейчас о человеке, что стоит рядом с тобой.";
			link.l1 = "Что?..";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Томас-Томас-Томас, ты, как всегда, один-одинёшенек в этом мире. Мне тебя почти жаль!";
			link.l1 = "Проклятые крысы! Ублюдки!..";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "Что это значит?! Как прикажешь это понимать?!";
			link.l1 = "Томми, послушай...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "Это я как раз и делаю! Скажи мне, что он соврал!";
			link.l1 = "К сожалению, он прав. Сложи оружие. И никому сегодня не придётся умирать. Я лично замолвлю за тебя слово. Чтобы тебя не повесили, а отправили на заслуженное наказание. После которого ты вернёшься к честной жизни.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "Это решать не вам! И, уж тем более, не тебе! Спасибо, помог"+GetSexPhrase("","ла")+", чёрт бы тебя побрал! Да с таким командиром и враги не нужны! Очередная крыса...";
			link.l1 = "Перестань, Томми. Чего ты хотел? Не всем удаётся избежать каторги. Тебя бы преследовали потом всю твою жизнь.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = "Не преследовали бы, будь я на твоём корабле, если бы ты был" + GetSexPhrase("","а") + " готов встать горой за своих людей! Но это уже неважно. Будьте прокляты, все вы! Я выпущу твои трусливые кишки, крыс" + GetSexPhrase("ёныш","а") + ". И тебя, Гейб, я тоже постараюсь успеть забрать с собой...";
			link.l1 = "Стой, Томми, нет!..";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Отлично, справились, поздравляю вас, "+GetSexPhrase("молодой человек","девушка")+"! Я впечатлён, что вам удалось внушить Томасу, будто всё идёт по его плану - это не каждому по плечу.";
			link.l1 = "Эх, спасибо вам, конечно, капитан Кэллоу.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Вас что-то беспокоит, "+GetSexPhrase("мистер","мисс")+" "+pchar.lastname+"?";
			link.l1 = "Том... Он не просто злился, что я оказал" + GetSexPhrase("ся","ась") + " на вашей стороне. В его голосе было неподдельное отчаяние и непонимание, как будто...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "... как будто он здесь пострадавшая сторона. Это было ожидаемо. Запомните, " + pchar.name + ", и чудовище может испытывать боль. Но оно не перестаёт быть от этого чудовищем. Многие преступники зачастую искренне уверены в своих правоте и невиновности.";
			link.l1 = "Постараюсь об этом не забывать. Думаю, мы здесь закончили, верно, капитан?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "В целом - да, однако у нас ещё кое-что на повестке дня, "+GetSexPhrase("молодой человек","девушка")+".";
			link.l1 = "Вот как? И что же?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Да долго ты. Вот и решил проверить. Да и вообще, мне кажется, что лучше устроить засаду здесь, а не играть в дуэлянтов на берегу. Надеюсь, ты смог" + GetSexPhrase("","ла") + " найти дом Гейба и оставить всё на видном месте?";
			link.l1 = "Конечно, смог" + GetSexPhrase("","ла") + ", что я, дур" + GetSexPhrase("ачок","очка") + ", что ли, по-твоему? Вообще-то я твой капитан, Томми. Хорош же ты был бы, если бы позволил дур" + GetSexPhrase("ачку","очке") + " командовать собой.";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ха-ха-ха, ты не поверишь, как часто на службе приходится иметь дело с дураками в лице начальства! Но в нашем случае это, к счастью, не так. Ну хорошо. Ждём гостей. Готов" + GetSexPhrase("","а") + "?";
			link.l1 = "Ну, если сюда не явится весь флот или гарнизон Порт-Ройяля - то готов" + GetSexPhrase("","а") + ".";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Томас? Всё-таки, это и правда ты...";
			link.l1 = "Конечно, я, а ты ждал кого-то другого, Гейб? Хех, смотрю, ты побледнел, будто призрака увидал. А ещё ты разжирел по сравнению с тем, каким был в Старушке Англии.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Теперь я окончательно убедился - это и правда ты. Как всегда, грубишь. Но ничего, скоро я закрою твой грязный рот навсегда, скотина.";
			link.l1 = "Ха-ха-ха, как мы заговорили! Знаешь, ты меня даже разочаровал, Гейб. В очередной раз. Тебе явно нужно было взять с собой больше людей, чтобы справиться не то что с нами двумя, а со мной одним. Или тебе больше не дали, трус ты несчастный?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Довольно! Больше не вижу смысла нам разговаривать.";
			link.l1 = "В этом я с тобой согласен! " + pchar.name + "! К бою, капитан!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Хе, вот так-то! Покойся с миром, ублюдок.";
			link.l1 = "Ну, ты доволен, Томми? Знаешь, многим становится только хуже после того, как они отомстят.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ха, никогда не понимал таких неженок. Получить то, что желаешь больше всего на свете - и не быть при этом довольным. Доволен ли я? Да я просто счастлив, чёрт возьми! Из-за этих уродов у меня всё чуть не пошло наперекосяк.";
			link.l1 = "Ну, не пошло, и это главное. Больше тебе никому не нужно отомстить? Или меня ожидают ещё какие-нибудь подобные шуточки от тебя, как тогда, с подбором патрона?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Расслабься, больше никому. А по поводу шуточек - не знаю, не знаю, хе-хе. Но не переживай. В твоём их понимании больше никаких шуточек не будет.";
			link.l1 = "Тогда возвращаемся на корабль?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Мы бы на него и так вернулись, вне зависимости от того, есть мне ещё кому отомстить, или нет. Хотя погоди минутку...";
			link.l1 = "Ох, значит, ещё не всё...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "Да всё, всё. Я хочу тебе кое-что сказать. Я это очень мало кому говорю. И повторять не буду. Вздумаешь смеяться - крепко так на тебя обижусь.";
			link.l1 = "Обещаю не смеяться. Всё равно я от твоих шуток больше напрягаюсь, нежели смеюсь.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Вот и хорошо. Так вот. Я очень благодарен тебе, что решил" + GetSexPhrase("","а") + " помочь, а не поступил" + GetSexPhrase("","а") + ", как Джек. Ты настоящий друг, капитан. Спасибо. И ещё... коль захочешь, можешь одолжить мой верный палаш, и доспех... То, что от него осталось, ха-ха!";
			link.l1 = "Ну, и тебе спасибо за такие слова. Не каждый день услышишь что-то подобное от своих офицеров. Идём, дружище.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Да-а-а, капитан?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Ну что, Румба, на чьих костях сегодня спляшем?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Да, Элли?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Слушаю тебя, капитан.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Томми, я бы хотел тебя попросить кое о чём очень серьёзном. Есть один... каменный истукан краснокожих. И мне понадобится помощь. Я могу попросить о ней только самых близких друзей, вроде тебя. Новички или те, кому я ещё не слишком доверяю, не подойдут.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Томми, хорош чаек считать. Весь груз описал? Дай полный отчёт с прогнозом.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Томми, мне нужно, чтобы ты, начиная с этого дня, закупал определённые товары в портах.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Томми, отчитайся, пожалуйста, обо всём на корабле?";
					Link.l12 = "Томми, я очень устаю, ты не мог бы пополнять запасы определённых товаров в каждом порту?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Приготовь мне отчёт о состоянии корабля и всего, что на нём есть, Томми.";
					Link.l12 = "Ты не мог бы закупать определённые товары во время наших заходов в порт?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Пересчитай мне всё, что есть на корабле, и доложи об его состоянии в целом.";
					Link.l12 = "Мне нужно, чтобы ты докупал вот эти товары во время наших заходов в каждый порт.";
				}
			}
			//////
			Link.l1 = "Внимательно слушай мой приказ!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Непременно на чьих-нибудь. А пока что слушай мой приказ.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Слушай мой приказ... Томми.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Это хорошо, потому что у меня для тебя новый приказ, Томми.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Слушай мой приказ, Том.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Ничего, Томми, вольно.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Посмотрим, Томми, как пойдёт.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Нет, Том, ничего.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Да нет, ничего.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Ничего, всё в порядке.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "А я и не начинал их описывать. Скажи спасибо, что я вообще вместе с тобой считаю наши доходы да расходы. И с купцами обнаглевшими торгуюсь. А описи делать - это не моё, меня даже в армии не заставляли их делать.";
			Link.l1 = "Здесь тебе не армия, Томми. Но ладно, я тебя понял, не буду заствлять.";
			if (startHeroType == 4)
			{
				dialog.Text = "Я не писарь, Элли. Был у меня один знакомый, Дэниэл Кримзон, говорил всем, мол, писарь я, писарь, лишь пару раз бывал на стрельбище. А человек - зверь был. В общем, не мой случай, я и врать не буду. Не моё это - описи. Я и так ради тебя считаю наши доходы и расходы. Не злоупотребляй.";
				Link.l1 = "Ну хорошо, Томми, не буду.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Слушай, я не писарь. С простых бойцов вроде меня этого никто и никогда не требовал даже в армии. Давай не будем менять это правило.";
				Link.l1 = "Ладно, давай не будем.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Единственное, что я могу пересчитать - скольких наших врагов я перестрелял, ха-ха-ха. Да и то собьюсь со счёта. Я простой солдат, знаешь ли. Чёрт его знает, что с кораблём - большую часть жизни я был сухопутным.";
				Link.l1 = "Видимо, придётся самому.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Я тебе что, крыса тыловая, закупаться? Да мы этих трусов изнеженных презирали дома. Я, конечно, не благородие, но самоуважение сохранил.";
			link.l1 = "Ладно-ладно, нет так нет.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Я, знаешь ли, простой честный вояка был, а не снабженец, девочка моя. Так что понимаю в этом не слишком и не хочу начинать. Это всё равно, что я тебя попрошу собрать и разобрать мушкет. Да ещё на время.";
				Link.l1 = "Зато я могу назвать все части стоячего и бегучего такелажа на нашем судне наизусть. Но как скажешь, Том, тема закрыта.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Нет, не мог бы. Возможно, ты забыл или вовсе не знаешь этого, так что поясняю. Для тебя это было бы обычной задачей, но у нас, в армии, к снабженцам и тыловикам относятся не слишком-то и хорошо. Попрошу меня к ним не причислять.";
				Link.l1 = "Ха-ха, хорошо, хорошо.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Слушай, я, конечно, уважаю тебя, но переступать через себя и делать то, что не умею и терпеть не могу - не собираюсь. Я считать-то едва научился когда-то, а ты от меня хочешь, чтобы я был заправским снабженцем. Мы их, между прочим, недолюбливали - экономят на боеприпасах, воде, еде и её свежести.";
				Link.l1 = "Хм, ладно, забудем об этом.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Ой, приказ прямо-таки. Тебе так нравится муштра и все эти штучки? Лучше бы сразу сказал, что нужно сделать.","Ну ты прямо-таки, как сержант какой-то. Не идёт это тебе, ты слишком прекрасна для этого. Да и в армии бы не выжила и дня. Но я тебя слушаю.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Видимо, ты и правда большой любитель формы, муштры и прочего. Но ладно, продолжай.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "И какой же?";
			}
			
            Link.l1 = ""+GetSexPhrase("Никуда не иди и ничего не делай, просто наблюдай, понял меня? А то знаю я тебя.","Вот и стой в таком случае на месте, понял меня?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Просто стой здесь, никуда не отходи и ничего не трогай.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Стой здесь и никого не пропускай.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Следуй за мной и ни на что не отвлекайся - жёнушек чьих-нибудь или внезапно возникших сослуживцев.","Держись рядом, хорошо? В предстоящей заварушке мне бы хотелось, чтобы моя спина была прикрыта.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Следуй за мной. А то смотрю, ты задумался о чём-то.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Иди за мной, а то встал чего-то.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Мне нужно, чтобы ты стрелял из пистолета другими снарядами.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Мне нужно, чтобы в предстоящей схватке ты стрелял другими снарядами.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "В следующем бою будешь пользоваться другими снарядами.";
					}
				}	
			}
			
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Мне нужно, чтобы ты стрелял из мушкета другими снарядами.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Нужно изменить тип твоего приоритетного оружия для боя.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Мне бы хотелось, чтобы ты держал определённую дистанцию между собой и врагами.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Я бы хотел, чтобы ты держался на определённом расстоянии от врагов, Томми.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Соблюдай определённую дистанцию между собой и врагами, Томми.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Это какими? Надеюсь, ты тщательно отобрал каждый снаряд? А то кто знает, куда он полетит, хе-хе.","Для тебя - что угодно. Неважно, какие они будут, но никогда - не холостые, хе-хе.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Чую, намечается кое-что интересное! Хорошо, и какими же?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Опять пристреливаться... Ладно, какими?";
			}
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
		
		case "SetMusketBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			if(LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet))
			{
				rItem = ItemsFromID(sBullet);
				notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			}
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "В начале боя я буду доставать:";
			Link.l1 = "Холодное оружие";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Мушкет";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Даже если тебя будут избивать, хе-хе? Понял, будем наблюдать за этим.","Караульного из меня решила сделать? А если тебя будут избивать или ещё что?")+"";
            Link.l1 = ""+GetSexPhrase("Но-но! Разберёмся в случае чего.","Ну ты же не будешь просто смотреть на это, верно? Если ты и правда считаешь своего капитана таким прекрасным, как говоришь, то сделаешь что-нибудь.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Даже по нужде? Ладно-ладно, не смотри так, я тебя понял.";
				Link.l1 = "Уж надеюсь на это.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Понял тебя. Не боись, никто не пройдёт.";
				Link.l1 = "Если ты никого не проворонишь, конечно. Но хорошо.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Очень смешно. Но я тебя понял.","О, не волнуйся, твой тыл всегда под моим пристальным присмотром, хе-хе.")+"";
            Link.l1 = ""+GetSexPhrase("Вот и хорошо.","Боже, ты неисправим, Том.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Да вот пытаюсь вспомнить нечто очень важное. А потом понимаю, что даже не знаю, что именно, так как память-то потерял тогда, так что ничего не выйдет. Ладно, пойдём.";
				Link.l1 = "Остроумно, ничего не скажешь.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Ну так я стою, потому что ты сам мне ранее это приказал. Иду, иду.";
				Link.l1 = "Кхм, ладно-ладно.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Какую? Имей ввиду, что в поле больше, чем на двадцать метров, я не смогу вести прицельный огонь. Если, конечно, тебе нужно, чтобы я непременно попадал, хе-хе.","Как будто я сам горю желанием подходить вплотную к вонючим мужикам после твоего общества. Так какую? Но знай, что больше, чем на двадцать метров, я не смогу вести прицельный огонь. Никто не смог бы.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Хорошо, каком же? Но напоминаю, что больше, чем на двадцать метров, я в пылу сражения вести прицельный неспешный огонь не смогу.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Хорошо. Какую? Помни, что дальше, чем... впрочем, не маленькие мы уже с тобой оба, и так знаешь.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Тебе не стоит заниматься юмором.","Тебе ещё у меня учиться и учиться искусству шутки, девочка моя. Но ты определённо делаешь успехи!")+"";
				link.l1 = ""+GetSexPhrase("Странно, мне всегда говорили обратное.","Очень смешно, Томми.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Не самая твоя плохая шутка. Может, однажды ты даже перестанешь быть занудой, хе-хе.";
					Link.l1 = "Ну-ну.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ха-ха-ха, хорошая шутка.";
					Link.l1 = "Вообще-то я просто... ладно.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Что ж, тогда я буду просто стоять на месте и держать оборону. Если будешь биться с ними слишком далеко - сам"+GetSexPhrase("","а")+" виноват"+GetSexPhrase("","а")+", хе-хе.";
				link.l1 = "Не ёрничай, всё верно, именно этого я от тебя и хочу сейчас.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Хех, мог бы просто сказать, чтобы я держал оборону, а не говорить про расстояние там, цифры.";
					Link.l1 = "Ну, главное, что ты меня понял.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Понял, буду держать оборону здесь. Подводи их тогда ко мне поближе, чтоб отстреливать мог.";
					Link.l1 = "Непременно.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Слушай, я понимаю, конечно, что тебе бы хотелось, чтобы каждый мой выстрел был как тогда на маяке, но не выйдет. Там точка хорошая была. И спокойствие. В пылу боя так не получится.";
				link.l1 = "Хм, ну ладно. Тогда держись на расстоянии в двадцать ярдов.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Я знаю, что ты бы этого хотел, да все ребята бы этого хотели, но как тогда, на маяке - больше не получится. Мне понадобятся хорошая точка, ну и чтобы никто не мог до меня добраться, а то нервы сдадут.";
					Link.l1 = "Хм, ну ладно.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Я, конечно, отточил свои навыки с тех пор, но невозможное так и останется невозможным - в разгаре боя тот выстрел с маяка мне никак не повторить. Даже с колесным штуцером.";
					Link.l1 = "И невозможное возможно, Томми. Но ладно, нет - так нет.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Очень хорошо. Буду поддерживать именно такое расстояние, а если будем в таверне или пещере - выйду, чтобы его соблюдать, ха-ха.", "Постараюсь запомнить. Но имей ввиду, что палубы и замкнутые пространства продиктуют свои условия.");
			link.l1 = ""+GetSexPhrase("Несмешно, Томми. Действуй по обстоятельствам, но без шуточек и подстав.","Я знаю это, Томас, не тупая.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Постараюсь запомнить.";
				Link.l1 = "Хорошо, рассчитываю на тебя.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Есть, капитан.";
				Link.l1 = "Непременно.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Помощь в чём, украсть его? Только зачем? Я, конечно, польщён, но ты уже давно мог бы сказать всё. Давай, сплюнь.";
			link.l1 = "Следи за языком, а? Впрочем, чёрт с ним - мне на самом деле всё равно, как ты выражаешься, пока ты на моей стороне. Так вот, тот истукан. Через него можно... магическим образом попадать в другое место. Не смотри на меня так - я понимаю, как это звучит. Но я уже проходил через это и видел всё своими глазами. Это... безопасно, если выпить один эликсир.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Смотрю, ты уже выпил несколько. Хотя нет, вроде трезвый. А ещё про меня говорят, что я всё время несу околесицу...";
			link.l1 = "Ты пойдёшь со мной, или нет? Истукан должен перенести нас в древний город индейцев майя, и кто знает, что нас там ждёт? Ты один из тех, на кого, как я считаю, я могу положиться в трудную минуту. И сейчас такая минута как раз пришла.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Дурное у меня предчувствие насчёт всего этого. Не будь ты моим капитаном, сказал бы, что тебе место в лечебнице для душевнобольных. Ты ещё скажи, что Бог существует.";
			link.l1 = "Существует, Томми. И, как я к собственному удивлению обнаружил на этом Архипелаге, не только наш. Ты сам мог видеть, как тут творилась всякая чертовщина. И наверняка заметил влияние благословлённых или проклятых побрякушек.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Чертовщина есть и дома. И ей всегда было нормальное объяснение. Извини, капитан, но плясать вокруг каменных идолов я с тобой не стану. Перестрелять врагов - пожалуйста. Я, может, и потерял память, но вот рассудок - нет. По крайней мере, я так думаю.";
			link.l1 = "Ну, заставить я тебя не могу. Так что... как хочешь, Томми.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Да уже сомневаюсь, хватит ли тебе духу перестрелять их, храбрец ты наш, раз боишься к камню подойти.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ну-ну, губы-то не надувай. Ладно, если вернёшься после танцев вокруг этого своего... истукана, то я подумаю в следующий раз.";
			link.l1 = "Следующего раза уже может и не быть. Возвращайся на корабль, Том.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Я не боюсь, не подумай. Но своё чутьё привык слушать, оно за долгие годы меня не подводило. И сейчас оно говорит, что ничего хорошего из этого не выйдет. Да и вообще... Хотя ладно, а то ещё обидишься.";
			link.l1 = "Да говори уж.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Ну, изволь, в таком случае! Я соглашался сражаться бок о бок с тобой. А что, если, предположим, эта штуковина и правда работает? А если проклята? Умирать я за кого-то не собираюсь, уж извини.";
			link.l1 = "Вот ты и показал себя, Томми. Мне сейчас нужны были самые преданные люди. И теперь я вижу, что ты не один из них. Я иду туда. Ну а ты... делай, что хочешь.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Поглядите на него. Всё-таки обиделся.";
			link.l1 = "Закрой-ка свой рот. Если тебе с нами так противно - можешь не возвращаться на корабль.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Ого! Ты серьёзно? Впрочем, возможно, оно и к лучшему. Не по пути мне с занудами, которые даже шуток не понимают. В таком случае... прощай, ваше благородие.";
			link.l1 = "Прощай, Томми. И катись к чёрту.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 